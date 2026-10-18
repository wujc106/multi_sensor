/*!
    \file    gui_app.c

    \version 2026-10-15 multi_sensor custom UI logic (radiation monitor)

    Pages: 0=home 1=menu 2=curve 3=settings 4=device-state 5=info
    Keys:  K1(KEY_USER_1)=next focus / cycle channel
           K2(KEY_USER_2)=confirm / cycle preset value
           K3(KEY_TAMPER_WAKEUP)=back
    Simulator keys: Right/Down=K1  Enter=K2  Esc=K3 (forwarded by simulator/main.c)
*/

/* the GD32EmbeddedUI simulator is built by host MinGW GCC; ARM toolchains do not define _WIN32 */
#if defined(_WIN32)
#define GUI_APP_SIMULATOR 1
#else
#define GUI_APP_SIMULATOR 0
#endif

#if GUI_APP_SIMULATOR
#include <time.h>
#else
#include "gd32f5hcr_eval.h"
#endif

#include <stdlib.h>
#include <string.h>

#include "gui_app.h"
#include "ui_init.h"

void load_page(uint8_t page);

/*
    注意：预编译 LVGL 库的 lv_snprintf 不支持 %f（LV_SPRINTF_USE_FLOAT=0，遇到会段错误）。
    浮点数一律用整数运算格式化（fmt_1/fmt_2），字符串拼接用 append_str，不要在
    lv_snprintf 的格式串里出现 %f / %s。
*/

#define PAGE_COUNT 6U
#define KEY_DEBOUNCE_MS 250U

#define COL_NORMAL 0x28B6A5U
#define COL_WARN   0xEF9F27U
#define COL_ALARM  0xE24B4AU
#define COL_GREEN  0x639922U
#define COL_TEXT   0xE8EEF2U
#define COL_MUTED  0x91A8B5U
#define COL_FOCUSED 0x28B6A5U

#define CURVE_POINTS 20U
#define CH_DOSE 0U
#define CH_TEMP 1U
#define CH_HUM  2U
#define CH_COUNT 3U

typedef enum {
    KEY_NEXT = GUI_APP_KEY_NEXT,
    KEY_OK   = GUI_APP_KEY_OK,
    KEY_BACK = GUI_APP_KEY_BACK
} app_key_t;

typedef enum {
    PAGE_HOME = 0U,
    PAGE_MENU,
    PAGE_CURVE,
    PAGE_SET,
    PAGE_STATE,
    PAGE_INFO
} page_t;

typedef enum {
    DEV_RUNNING = 0U,
    DEV_STANDBY,
    DEV_OFF
} dev_state_t;

typedef struct {
    const char *name;
    const char *unit;
    float value;
    float warn;      /* dose only: derived, alarm * 0.8 */
    float alarm;     /* dose: alarm threshold; temp/hum: unused */
    float vmin;      /* temp/hum: lower limit */
    float vmax;      /* temp/hum: upper limit */
    bool use_warn;   /* true: warn+alarm, false: min+max */
} channel_cfg_t;

static channel_cfg_t cfg[CH_COUNT] = {
    /* name     unit     value  warn  alarm vmin   vmax  use_warn */
    { "剂量率", "µSv/h", 0.86f, 6.40f, 8.00f, 0.0f, 8.0f, true  },
    { "温度",   "°C",    26.8f, 0.0f,  0.0f, 16.0f, 30.0f, false },
    { "湿度",   "%RH",   58.2f, 0.0f,  0.0f, 30.0f, 70.0f, false },
};

/* 剂量率报警值预设：3/5/8 递进；100µ 以下只保留 3/8；≥1000µ 显示为 mSv/h */
static const float DOSE_ALARMS[] = { 3.0f, 8.0f, 30.0f, 80.0f, 300.0f, 500.0f, 800.0f, 3000.0f, 5000.0f, 8000.0f };
static const float TEMP_MINS[]   = { -10.0f, 0.0f, 10.0f, 16.0f, 20.0f };
static const float TEMP_MAXS[]   = { 30.0f, 40.0f, 50.0f, 60.0f, 80.0f };
static const float HUM_MINS[]    = { 20.0f, 30.0f, 40.0f };
static const float HUM_MAXS[]    = { 60.0f, 70.0f, 80.0f, 90.0f };

typedef struct {
    const float *alarm_p; uint8_t alarm_n; uint8_t alarm_i;
    const float *min_p;   uint8_t min_n;   uint8_t min_i;
    const float *max_p;   uint8_t max_n;   uint8_t max_i;
} preset_t;

static preset_t pr[CH_COUNT] = {
    { DOSE_ALARMS, 10U, 1U, NULL,      0U, 0U, NULL,     0U, 0U },
    { NULL,        0U, 0U,  TEMP_MINS, 5U, 3U, TEMP_MAXS, 5U, 1U },
    { NULL,        0U, 0U,  HUM_MINS,  3U, 1U, HUM_MAXS,  4U, 1U },
};

#define WARN_RATIO_NUM 4U   /* warn = alarm * 4/5 = 80% */
#define WARN_RATIO_DEN 5U

static uint8_t current_page = PAGE_HOME;
static dev_state_t dev_state = DEV_RUNNING;
static uint8_t home_channel = CH_DOSE;
static uint8_t curve_channel = CH_DOSE;
static uint8_t set_channel = CH_DOSE;
static uint8_t set_row;             /* 0=channel row, 1=P1, 2=P2 */
static uint8_t menu_focus;

static float curve_buf[CH_COUNT][CURVE_POINTS];
static uint8_t curve_head;          /* next write index */
static float dose_acc = 12.4f;      /* accumulated dose, µSv */
static uint8_t battery = 87U;
static uint32_t run_seconds = 128U * 3600U;
static lv_chart_series_t *curve_series;

static const char *const PAGE_NAMES[PAGE_COUNT] = {
    "screen", "screen_1", "screen_2", "screen_3", "screen_4", "screen_5"
};
static const char *const DEV_STATE_NAMES[] = { "运行", "待机", "关机" };
/* 注意：状态文字只用工程内 14 号字体已有的汉字（运行/待机/关机均来自状态页静态文本），
   "运行中/已关机"的 中/已 不在字体子集里，真机会显示为空白 */

/* ---------------- small helpers ---------------- */

static uint32_t level_color(uint8_t level)
{
    if (level >= 2U) return COL_ALARM;
    if (level == 1U) return COL_WARN;
    return COL_NORMAL;
}

/* 0=normal 1=warning 2=alarm of one channel */
static uint8_t channel_level(uint8_t ch)
{
    channel_cfg_t *c = &cfg[ch];

    if (c->use_warn) {
        if (c->value >= c->alarm) return 2U;
        if (c->value >= c->warn) return 1U;
        return 0U;
    }
    if (c->value > c->vmax || c->value < c->vmin) return 2U;
    return 0U;
}

static uint8_t overall_level(void)
{
    uint8_t level = 0U;
    uint8_t ch;

    for (ch = 0U; ch < CH_COUNT; ch++) {
        uint8_t l = channel_level(ch);
        if (l > level) level = l;
    }
    return level;
}

static void set_label_color(lv_obj_t *label, uint32_t rgb)
{
    lv_obj_set_style_text_color(label, lv_color_hex(rgb), LV_PART_MAIN);
}

/* format float with 1 decimal place, integer math only */
static void fmt_1(char *out, int size, float v)
{
    int32_t scaled = (int32_t)(v * 10.0f + ((v >= 0.0f) ? 0.5f : -0.5f));
    int32_t ip = scaled / 10;
    int32_t fp = scaled % 10;

    if (fp < 0) fp = -fp;
    if (scaled < 0 && ip == 0) {
        lv_snprintf(out, size, "-0.%d", (int)fp);
    } else {
        lv_snprintf(out, size, "%d.%d", (int)ip, (int)fp);
    }
}

/* format float with 2 decimal places, integer math only */
static void fmt_2(char *out, int size, float v)
{
    int32_t scaled = (int32_t)(v * 100.0f + ((v >= 0.0f) ? 0.5f : -0.5f));
    int32_t ip = scaled / 100;
    int32_t fp = scaled % 100;

    if (fp < 0) fp = -fp;
    if (scaled < 0 && ip == 0) {
        lv_snprintf(out, size, "-0.%02d", (int)fp);
    } else {
        lv_snprintf(out, size, "%d.%02d", (int)ip, (int)fp);
    }
}

/* safely append src to dst */
static void append_str(char *dst, int size, const char *src)
{
    strncat(dst, src, size - strlen(dst) - 1);
}

/* 剂量率显示格式：≥1000 µSv/h 自动切换为 mSv/h（unit 返回对应单位字符串，可为 NULL） */
static void fmt_dose(char *val, int vsize, float uv, const char **unit)
{
    if (uv >= 1000.0f) {
        fmt_2(val, vsize, uv / 1000.0f);
        if (unit != NULL) *unit = "mSv/h";
    } else {
        fmt_2(val, vsize, uv);
        if (unit != NULL) *unit = "µSv/h";
    }
}

static void set_button_current(lv_obj_t *btn, bool current)
{
    if (current) {
        lv_obj_add_state(btn, LV_STATE_CHECKED);
        lv_obj_set_style_bg_color(btn, lv_color_hex(0x1E3A2CU), LV_PART_MAIN | LV_STATE_CHECKED);
    } else {
        lv_obj_clear_state(btn, LV_STATE_CHECKED);
    }
}

/* ---------------- home page ---------------- */

static void update_home(void)
{
    screen_t *scr = screen_get(&ui_manager);
    channel_cfg_t *c = &cfg[home_channel];
    uint8_t ch_level = channel_level(home_channel);
    uint8_t dev_level = overall_level();
    int32_t lo, hi, pct;
    char buf[24];

    /* gauge */
    if (c->use_warn) {
        lo = 0;
        hi = (c->alarm > 0.01f) ? (int32_t)(c->alarm * 100.0f + 0.5f) : 100;
    } else {
        lo = (int32_t)(c->vmin * 10.0f);
        hi = (int32_t)(c->vmax * 10.0f);
    }
    pct = (int32_t)(c->value * ((c->use_warn) ? 100.0f : 10.0f));
    if (hi > lo) {
        pct = (pct - lo) * 100 / (hi - lo);
    } else {
        pct = 0;
    }
    if (pct < 0) pct = 0;
    if (pct > 100) pct = 100;
    lv_arc_set_value(scr->ui_screen_Arc_Value, (int16_t)pct);
    lv_obj_set_style_arc_color(scr->ui_screen_Arc_Value, lv_color_hex(level_color(ch_level)),
                               LV_PART_INDICATOR);

    if (c->use_warn) {
        const char *unit_str = c->unit;

        fmt_dose(buf, sizeof(buf), c->value, &unit_str);
        lv_label_set_text(scr->ui_screen_Label_Value, buf);
        set_label_color(scr->ui_screen_Label_Value, level_color(ch_level));
        lv_label_set_text(scr->ui_screen_Label_Unit, unit_str);
    } else {
        fmt_1(buf, sizeof(buf), c->value);
        lv_label_set_text(scr->ui_screen_Label_Value, buf);
        set_label_color(scr->ui_screen_Label_Value, level_color(ch_level));
        lv_label_set_text(scr->ui_screen_Label_Unit, c->unit);
    }
    lv_label_set_text(scr->ui_screen_Label_Channel, c->name);

    /* fixed tiles: number and unit are separate labels (unit in small font) */
    fmt_1(buf, sizeof(buf), cfg[CH_TEMP].value);
    lv_label_set_text(scr->ui_screen_Label_TempValue, buf);
    lv_label_set_text(scr->ui_screen_Label_TempUnit, "°C");
    fmt_1(buf, sizeof(buf), cfg[CH_HUM].value);
    lv_label_set_text(scr->ui_screen_Label_HumValue, buf);
    lv_label_set_text(scr->ui_screen_Label_HumUnit, "%RH");
    fmt_2(buf, sizeof(buf), dose_acc);
    lv_label_set_text(scr->ui_screen_Label_DoseValue, buf);
    lv_label_set_text(scr->ui_screen_Label_DoseUnit, "µSv");
    lv_snprintf(buf, sizeof(buf), "%u", battery);
    lv_label_set_text(scr->ui_screen_Label_BatValue, buf);
    lv_label_set_text(scr->ui_screen_Label_BatUnit, "%");

    /* device status text: level of all channels + power state */
    if (dev_state == DEV_RUNNING) {
        static const char *const status_text[] = { "正常", "预警", "报警" };
        uint32_t txt_col = (dev_level == 0U) ? COL_GREEN : level_color(dev_level);

        lv_label_set_text(scr->ui_screen_Label_Status, status_text[dev_level]);
        set_label_color(scr->ui_screen_Label_Status, txt_col);
    } else {
        lv_label_set_text(scr->ui_screen_Label_Status, DEV_STATE_NAMES[dev_state]);
        set_label_color(scr->ui_screen_Label_Status, COL_MUTED);
    }
}

/* ---------------- curve page ---------------- */

static void curve_range(int32_t *lo, int32_t *hi)
{
    channel_cfg_t *c = &cfg[curve_channel];

    if (c->use_warn) {
        *lo = 0;
        *hi = (int32_t)(c->alarm * 1.2f + 0.5f);
        if (*hi < 1) *hi = 1;
    } else {
        *lo = (int32_t)(c->vmin - 2.0f);
        *hi = (int32_t)(c->vmax + 2.0f);
    }
}

/* 图表数值缩放：lv_coord_t 为 16 位有符号数（≤32767）。
   剂量率大档位（报警值 ≥ 3000µSv/h）时 ×10 会使量程溢出，降为 ×1 */
static int curve_scale(uint8_t ch)
{
    channel_cfg_t *c = &cfg[ch];

    if (c->use_warn) {
        return (c->alarm <= 2700.0f) ? 10 : 1;
    }
    return 100;   /* 温湿度沿用 ×100，量程远小于 32767 */
}

static void update_curve_chart(void)
{
    screen_2_t *scr = screen_2_get(&ui_manager);
    channel_cfg_t *c = &cfg[curve_channel];
    int sc = curve_scale(curve_channel);
    int32_t lo, hi;
    float fmin = 1e9f, fmax = -1e9f, fsum = 0.0f;
    uint16_t i;
    char buf[64];
    char tmp[16];

    for (i = 0U; i < CURVE_POINTS; i++) {
        float v = curve_buf[curve_channel][(curve_head + i) % CURVE_POINTS];

        lv_chart_set_value_by_id(scr->ui_screen_2_Chart_1, curve_series, i, (lv_coord_t)(v * (float)sc));
        if (v < fmin) fmin = v;
        if (v > fmax) fmax = v;
        fsum += v;
    }
    curve_range(&lo, &hi);
    lv_chart_set_range(scr->ui_screen_2_Chart_1, LV_CHART_AXIS_PRIMARY_Y, (lv_coord_t)(lo * sc), (lv_coord_t)(hi * sc));
    lv_chart_refresh(scr->ui_screen_2_Chart_1);

    strcpy(buf, "min ");
    if (c->use_warn) {
        fmt_2(tmp, sizeof(tmp), fmin);
    } else {
        fmt_1(tmp, sizeof(tmp), fmin);
    }
    append_str(buf, sizeof(buf), tmp);
    append_str(buf, sizeof(buf), "   max ");
    if (c->use_warn) {
        fmt_2(tmp, sizeof(tmp), fmax);
    } else {
        fmt_1(tmp, sizeof(tmp), fmax);
    }
    append_str(buf, sizeof(buf), tmp);
    append_str(buf, sizeof(buf), "   avg ");
    if (c->use_warn) {
        fmt_2(tmp, sizeof(tmp), fsum / CURVE_POINTS);
    } else {
        fmt_1(tmp, sizeof(tmp), fsum / CURVE_POINTS);
    }
    append_str(buf, sizeof(buf), tmp);
    lv_label_set_text(scr->ui_screen_2_Label_Stat, buf);
}

static void update_curve_channel(void)
{
    screen_2_t *scr = screen_2_get(&ui_manager);
    channel_cfg_t *c = &cfg[curve_channel];
    const char *unit_str = c->unit;
    char val[16];
    char buf[24];

    strcpy(buf, c->name);
    if (c->use_warn) {
        fmt_dose(val, sizeof(val), c->value, &unit_str);
    }
    append_str(buf, sizeof(buf), " ");
    append_str(buf, sizeof(buf), unit_str);
    lv_label_set_text(scr->ui_screen_2_Label_Channel, buf);
    set_label_color(scr->ui_screen_2_Label_Channel, level_color(channel_level(curve_channel)));
    update_curve_chart();
}

/* ---------------- settings page ---------------- */

static void update_set_labels(void)
{
    screen_3_t *scr = screen_3_get(&ui_manager);
    channel_cfg_t *c = &cfg[set_channel];
    char buf[24];

    lv_label_set_text(scr->ui_screen_3_Label_ChannelValue, c->name);
    if (c->use_warn) {
        const char *unit_str;

        lv_label_set_text(scr->ui_screen_3_Label_P1Name, "预警值");
        fmt_dose(buf, sizeof(buf), c->warn, &unit_str);
        append_str(buf, sizeof(buf), " ");
        append_str(buf, sizeof(buf), unit_str);
        lv_label_set_text(scr->ui_screen_3_Label_P1Value, buf);
        set_label_color(scr->ui_screen_3_Label_P1Value, COL_WARN);
        lv_label_set_text(scr->ui_screen_3_Label_P2Name, "报警值");
        fmt_dose(buf, sizeof(buf), c->alarm, &unit_str);
        append_str(buf, sizeof(buf), " ");
        append_str(buf, sizeof(buf), unit_str);
        lv_label_set_text(scr->ui_screen_3_Label_P2Value, buf);
        set_label_color(scr->ui_screen_3_Label_P2Value, COL_ALARM);
    } else {
        lv_label_set_text(scr->ui_screen_3_Label_P1Name, "最小值");
        fmt_1(buf, sizeof(buf), c->vmin);
        append_str(buf, sizeof(buf), " ");
        append_str(buf, sizeof(buf), c->unit);
        lv_label_set_text(scr->ui_screen_3_Label_P1Value, buf);
        set_label_color(scr->ui_screen_3_Label_P1Value, COL_NORMAL);
        lv_label_set_text(scr->ui_screen_3_Label_P2Name, "最大值");
        fmt_1(buf, sizeof(buf), c->vmax);
        append_str(buf, sizeof(buf), " ");
        append_str(buf, sizeof(buf), c->unit);
        lv_label_set_text(scr->ui_screen_3_Label_P2Value, buf);
        set_label_color(scr->ui_screen_3_Label_P2Value, COL_ALARM);
    }

    lv_obj_set_style_border_color(scr->ui_screen_3_Container_Channel, lv_color_hex(
        (set_row == 0U) ? COL_FOCUSED : 0x000000U), LV_PART_MAIN);
    lv_obj_set_style_border_width(scr->ui_screen_3_Container_Channel,
        (set_row == 0U) ? 3 : 0, LV_PART_MAIN);
    lv_obj_set_style_border_color(scr->ui_screen_3_Container_P1, lv_color_hex(
        (set_row == 1U) ? COL_FOCUSED : 0x000000U), LV_PART_MAIN);
    lv_obj_set_style_border_width(scr->ui_screen_3_Container_P1, (set_row == 1U) ? 3 : 0, LV_PART_MAIN);
    lv_obj_set_style_border_color(scr->ui_screen_3_Container_P2, lv_color_hex(
        (set_row == 2U) ? COL_FOCUSED : 0x000000U), LV_PART_MAIN);
    lv_obj_set_style_border_width(scr->ui_screen_3_Container_P2, (set_row == 2U) ? 3 : 0, LV_PART_MAIN);
}

/* cycle one preset table, wraps around */
static uint8_t preset_next_idx(uint8_t idx, uint8_t count)
{
    return (uint8_t)((idx + 1U) % count);
}

static void settings_key(app_key_t key)
{
    channel_cfg_t *c = &cfg[set_channel];
    preset_t *p = &pr[set_channel];

    if (key == KEY_NEXT) {
        set_row = (uint8_t)((set_row + 1U) % 3U);
    } else if (key == KEY_OK) {
        if (set_row == 0U) {
            set_channel = (uint8_t)((set_channel + 1U) % CH_COUNT);
        } else if (c->use_warn) {
            /* both dose rows cycle the alarm preset; warn follows at 80% */
            p->alarm_i = preset_next_idx(p->alarm_i, p->alarm_n);
            c->alarm = p->alarm_p[p->alarm_i];
            c->warn = c->alarm * WARN_RATIO_NUM / WARN_RATIO_DEN;
        } else if (set_row == 1U) {
            p->min_i = preset_next_idx(p->min_i, p->min_n);
            c->vmin = p->min_p[p->min_i];
            if (c->vmin >= c->vmax) {
                c->vmax = c->vmin + 10.0f;
            }
        } else {
            p->max_i = preset_next_idx(p->max_i, p->max_n);
            c->vmax = p->max_p[p->max_i];
            if (c->vmax <= c->vmin) {
                c->vmin = c->vmax - 10.0f;
            }
        }
    } else if (key == KEY_BACK) {
        load_page(PAGE_MENU);
        return;
    }
    update_set_labels();
    update_home();
}

/* ---------------- device state page ---------------- */

static uint8_t state_focus;

static void update_state_page(void)
{
    screen_4_t *scr = screen_4_get(&ui_manager);
    lv_coord_t tag_y[3] = { 53, 113, 173 };

    set_button_current(scr->ui_screen_4_Btn_Standby, dev_state == DEV_STANDBY);
    set_button_current(scr->ui_screen_4_Btn_Running, dev_state == DEV_RUNNING);
    set_button_current(scr->ui_screen_4_Btn_PowerOff, dev_state == DEV_OFF);
    lv_obj_set_y(scr->ui_screen_4_Label_CurrentTag, tag_y[dev_state]);
}

static void state_page_key(app_key_t key)
{
    if (key == KEY_NEXT) {
        state_focus = (uint8_t)((state_focus + 1U) % 3U);
    } else if (key == KEY_OK) {
        dev_state = (dev_state_t)state_focus;
        update_home();
    } else if (key == KEY_BACK) {
        load_page(PAGE_MENU);
        return;
    }
    update_state_page();
}

/* ---------------- navigation ---------------- */

static void set_menu_focus(void)
{
    screen_1_t *s1 = screen_1_get(&ui_manager);
    lv_obj_t *objs[4];
    uint8_t i;

    objs[0] = s1->ui_screen_1_Btn_Curve;
    objs[1] = s1->ui_screen_1_Btn_Settings;
    objs[2] = s1->ui_screen_1_Btn_State;
    objs[3] = s1->ui_screen_1_Btn_Info;
    for (i = 0U; i < 4U; i++) {
        lv_obj_set_style_outline_width(objs[i], (i == menu_focus) ? 2 : 0, LV_PART_MAIN);
        lv_obj_set_style_outline_color(objs[i], lv_color_hex(COL_FOCUSED), LV_PART_MAIN);
        lv_obj_set_style_outline_pad(objs[i], 1, LV_PART_MAIN);
    }
}

void load_page(uint8_t page)
{
    lv_obj_t *next;

    if (page >= PAGE_COUNT || page == current_page) {
        return;
    }

    next = ui_get_screen_by_name(PAGE_NAMES[page]);
    if (next == NULL) {
        return;
    }
    lv_scr_load_anim(next, LV_SCR_LOAD_ANIM_MOVE_LEFT, 150, 0, false);
    current_page = page;

    if (page == PAGE_MENU) {
        set_menu_focus();
    } else if (page == PAGE_CURVE) {
        update_curve_channel();
    } else if (page == PAGE_SET) {
        update_set_labels();
    } else if (page == PAGE_STATE) {
        state_focus = (uint8_t)dev_state;
        update_state_page();
    }
}

static void handle_key(app_key_t key)
{
    switch (current_page) {
    case PAGE_HOME:
        if (key == KEY_NEXT) {
            home_channel = (uint8_t)((home_channel + 1U) % CH_COUNT);
            update_home();
        } else if (key == KEY_OK) {
            load_page(PAGE_MENU);
        }
        break;
    case PAGE_MENU:
        if (key == KEY_NEXT) {
            menu_focus = (uint8_t)((menu_focus + 1U) % 4U);
            set_menu_focus();
        } else if (key == KEY_OK) {
            static const uint8_t dest[4] = { PAGE_CURVE, PAGE_SET, PAGE_STATE, PAGE_INFO };
            load_page(dest[menu_focus]);
        } else if (key == KEY_BACK) {
            load_page(PAGE_HOME);
        }
        break;
    case PAGE_CURVE:
        if (key == KEY_NEXT) {
            curve_channel = (uint8_t)((curve_channel + 1U) % CH_COUNT);
            update_curve_channel();
        } else if (key == KEY_BACK) {
            load_page(PAGE_MENU);
        }
        break;
    case PAGE_SET:
        settings_key(key);
        break;
    case PAGE_STATE:
        state_page_key(key);
        break;
    case PAGE_INFO:
        if (key == KEY_BACK) {
            load_page(PAGE_MENU);
        }
        break;
    default:
        break;
    }
}

/* ---------------- data simulation ---------------- */

static float rnd_sym(void)
{
    return ((float)(rand() % 2001) - 1000.0f) / 1000.0f;   /* -1.0 .. +1.0 */
}

static void push_curve_sample(uint8_t ch, float v)
{
    curve_buf[ch][curve_head] = v;
}

static void data_timer_cb(lv_timer_t *timer)
{
    (void)timer;
    static bool seeded;
    uint8_t ch;

    if (!seeded) {
        /* 勿用 time()：Keil 目标端无标准 time 实现，改用 LVGL tick 作种子 */
        srand((unsigned)lv_tick_get());
        seeded = true;
    }
    if (dev_state != DEV_RUNNING) {
        return;
    }

    /* random walk around nominal values */
    cfg[CH_DOSE].value += rnd_sym() * 0.04f;
    if (cfg[CH_DOSE].value < 0.05f) cfg[CH_DOSE].value = 0.05f;
    if (cfg[CH_DOSE].value > 3.0f) cfg[CH_DOSE].value = 3.0f;

    cfg[CH_TEMP].value += rnd_sym() * 0.08f;
    if (cfg[CH_TEMP].value < 18.0f) cfg[CH_TEMP].value = 18.0f;
    if (cfg[CH_TEMP].value > 35.0f) cfg[CH_TEMP].value = 35.0f;

    cfg[CH_HUM].value += rnd_sym() * 0.4f;
    if (cfg[CH_HUM].value < 20.0f) cfg[CH_HUM].value = 20.0f;
    if (cfg[CH_HUM].value > 90.0f) cfg[CH_HUM].value = 90.0f;

    dose_acc += cfg[CH_DOSE].value * 0.5f / 3600.0f;
    if (battery > 0U && (rand() % 500) == 0) battery--;

    for (ch = 0U; ch < CH_COUNT; ch++) {
        push_curve_sample(ch, cfg[ch].value);
    }
    curve_head = (uint8_t)((curve_head + 1U) % CURVE_POINTS);

    if (current_page == PAGE_HOME) {
        update_home();
    } else if (current_page == PAGE_CURVE) {
        update_curve_chart();
    }
}

static void time_timer_cb(lv_timer_t *timer)
{
    (void)timer;
    screen_t *s0 = screen_get(&ui_manager);
    screen_1_t *s1 = screen_1_get(&ui_manager);
    screen_2_t *s2 = screen_2_get(&ui_manager);
    screen_3_t *s3 = screen_3_get(&ui_manager);
    screen_4_t *s4 = screen_4_get(&ui_manager);
    screen_5_t *s5 = screen_5_get(&ui_manager);
    lv_obj_t *time_labels[PAGE_COUNT] = {
        s0->ui_screen_Label_Time, s1->ui_screen_1_Label_Time, s2->ui_screen_2_Label_Time,
        s3->ui_screen_3_Label_Time, s4->ui_screen_4_Label_Time, s5->ui_screen_5_Label_Time
    };
    unsigned int hour = 0U, minute = 0U, second = 0U;
    uint8_t i;
    char buf[16];

#if GUI_APP_SIMULATOR
    time_t now = time(NULL);
    struct tm *lt = localtime(&now);

    if (lt != NULL) {
        hour = (unsigned int)lt->tm_hour;
        minute = (unsigned int)lt->tm_min;
        second = (unsigned int)lt->tm_sec;
    }
#else
    /* Keil 目标端：模板工程未初始化 RTC，且 libopt 未含 rtc 头文件，
       这里用 lv_tick 计算开机时长显示；如需真实时钟，请在 main.c 初始化 RTC
       并在此改回 rtc_current_time_get()（需自行 #include "gd32w51x_f5hc_rtc.h"） */
    unsigned int total_sec = lv_tick_get() / 1000U;

    hour = (total_sec / 3600U) % 100U;
    minute = (total_sec / 60U) % 60U;
    second = total_sec % 60U;
#endif

    run_seconds++;
    lv_snprintf(buf, sizeof(buf), "%02u:%02u:%02u", hour, minute, second);
    for (i = 0U; i < PAGE_COUNT; i++) {
        lv_label_set_text(time_labels[i], buf);
    }

    lv_snprintf(buf, sizeof(buf), "%u h", run_seconds / 3600U);
    lv_label_set_text(s5->ui_screen_5_Label_RunValue, buf);
}

/* ---------------- public hooks ---------------- */

/* 串口帧解析后调用：注入实测值（帧格式示例：AA 55 | ch(1B) | value(float LE) | checksum）
   接真实传感器时，停用 data_timer_cb 随机游走，仅保留本接口刷新 */
void gui_app_sensor_feed(int channel, float value)
{
    if ((uint8_t)channel >= CH_COUNT) {
        return;
    }
    cfg[channel].value = value;
    push_curve_sample((uint8_t)channel, value);
    curve_head = (uint8_t)((curve_head + 1U) % CURVE_POINTS);
    if (current_page == PAGE_HOME) {
        update_home();
    } else if (current_page == PAGE_CURVE) {
        update_curve_chart();
    }
}

/* simulator keyboard hook (called from simulator/main.c WndProc) */
void gui_app_sim_key(int key)
{
    if (key == GUI_APP_KEY_NEXT || key == GUI_APP_KEY_OK || key == GUI_APP_KEY_BACK) {
        handle_key((app_key_t)key);
    }
}

/* ---------------- hardware key polling (K1/K2/K3) ---------------- */

#if !GUI_APP_SIMULATOR
static uint8_t previous_key_state[KEYn] = {1U, 1U, 1U};
static unsigned long last_key_tick[KEYn];

static bool key_pressed(key_typedef_enum key)
{
    uint8_t key_state = gd_eval_key_state_get(key);
    unsigned long current_tick = lv_tick_get();

    if (key_state == 0U && previous_key_state[key] != 0U &&
        current_tick - last_key_tick[key] >= KEY_DEBOUNCE_MS) {
        last_key_tick[key] = current_tick;
        previous_key_state[key] = key_state;
        return true;
    }

    previous_key_state[key] = key_state;
    return false;
}

static void key_navigation_timer_cb(lv_timer_t *timer)
{
    (void)timer;

    if (key_pressed(KEY_USER_1)) {
        handle_key(KEY_NEXT);
    }
    if (key_pressed(KEY_USER_2)) {
        handle_key(KEY_OK);
    }
    if (key_pressed(KEY_TAMPER_WAKEUP)) {
        handle_key(KEY_BACK);
    }
}
#endif

/* ---------------- init ---------------- */

void custom_init(void)
{
    uint8_t ch, i;
    screen_2_t *s2 = screen_2_get(&ui_manager);

#if !GUI_APP_SIMULATOR
    gd_eval_key_init(KEY_TAMPER_WAKEUP, KEY_MODE_GPIO);
    gd_eval_key_init(KEY_USER_1, KEY_MODE_GPIO);
    gd_eval_key_init(KEY_USER_2, KEY_MODE_GPIO);
    lv_timer_create(key_navigation_timer_cb, 20, NULL);
#endif

    /* initial curve buffers with nominal values */
    for (ch = 0U; ch < CH_COUNT; ch++) {
        for (i = 0U; i < CURVE_POINTS; i++) {
            curve_buf[ch][i] = cfg[ch].value;
        }
    }
    curve_series = lv_chart_get_series_next(s2->ui_screen_2_Chart_1, NULL);
    lv_chart_set_point_count(s2->ui_screen_2_Chart_1, CURVE_POINTS);
    lv_chart_set_type(s2->ui_screen_2_Chart_1, LV_CHART_TYPE_LINE);

    /* containers should not scroll or capture clicks */
    {
        lv_obj_t *panels[] = {
            s2->ui_screen_2_Chart_1,
            screen_get(&ui_manager)->ui_screen_Label_TempName_Tile,
            screen_get(&ui_manager)->ui_screen_Label_HumName_Tile,
            screen_get(&ui_manager)->ui_screen_Label_DoseName_Tile,
            screen_get(&ui_manager)->ui_screen_Label_BatName_Tile,
            screen_3_get(&ui_manager)->ui_screen_3_Container_Channel,
            screen_3_get(&ui_manager)->ui_screen_3_Container_P1,
            screen_3_get(&ui_manager)->ui_screen_3_Container_P2,
        };
        for (i = 0U; i < sizeof(panels) / sizeof(panels[0]); i++) {
            lv_obj_clear_flag(panels[i], LV_OBJ_FLAG_SCROLLABLE);
            lv_obj_clear_flag(panels[i], LV_OBJ_FLAG_CLICKABLE);
        }
    }

    lv_timer_create(data_timer_cb, 500, NULL);
    lv_timer_create(time_timer_cb, 1000, NULL);

    update_home();
    update_curve_channel();
    update_set_labels();
    update_state_page();
    set_menu_focus();
}
