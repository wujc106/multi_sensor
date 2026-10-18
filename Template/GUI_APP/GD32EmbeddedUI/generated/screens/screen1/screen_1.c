/*!
    \file    screen_1.c
*/

/*
    Copyright (c) 2026, GigaDevice Semiconductor Inc.

    All rights reserved.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#include <string.h>

#include "ui_objects.h"
#include "ui_init.h"
#include "screen_1.h"
#include "screen_1_event.h"


/* lv_scr_load_anim(auto_del = true) destroys the previous screen, but ui_manager keeps
 * the cached pointers. Clear them on delete so they never dangle and the screen can be
 * re-created on demand. */
static void screen_1_deleted_cb(lv_event_t *e)
{
    ui_manager_t *ui = (ui_manager_t *)lv_event_get_user_data(e);

    memset(screen_1_get(ui), 0, sizeof(screen_1_t));
}




void screen_1_create(ui_manager_t *ui)
{
    screen_1_t *scr = screen_1_get(ui);

    if (scr->obj) {
        screen_1_update_current_language();
        return;
    }

    /* Init scr->obj */
    scr->obj = lv_obj_create(NULL);
    lv_obj_add_event_cb(scr->obj, screen_1_deleted_cb, LV_EVENT_DELETE, ui);
    lv_obj_set_scrollbar_mode(scr->obj, LV_SCROLLBAR_MODE_OFF);

    /* Set style of scr->obj */
    lv_obj_set_style_bg_color(scr->obj, lv_color_hex(0x0D1620), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(scr->obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    scr->ui_screen_1_Label_Title = lv_label_create(scr->obj);
    lv_obj_set_pos(scr->ui_screen_1_Label_Title, 8, 8);
    lv_obj_set_size(scr->ui_screen_1_Label_Title, 104, 18);
    lv_label_set_text(scr->ui_screen_1_Label_Title, "主菜单");
    lv_obj_set_style_text_align(scr->ui_screen_1_Label_Title, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_long_mode(scr->ui_screen_1_Label_Title, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_color(scr->ui_screen_1_Label_Title, lv_color_hex(0xE8EEF2), LV_PART_MAIN | LV_STATE_DEFAULT);
    LV_FONT_DECLARE(font_notosanscjksc_regular_14_b49ae336_fb3f);
    lv_obj_set_style_text_font(scr->ui_screen_1_Label_Title, &font_notosanscjksc_regular_14_b49ae336_fb3f, LV_PART_MAIN | LV_STATE_DEFAULT);

    scr->ui_screen_1_Label_Time = lv_label_create(scr->obj);
    lv_obj_set_pos(scr->ui_screen_1_Label_Time, 244, 8);
    lv_obj_set_size(scr->ui_screen_1_Label_Time, 68, 18);
    lv_label_set_text(scr->ui_screen_1_Label_Time, "14:32:05");
    lv_obj_set_style_text_align(scr->ui_screen_1_Label_Time, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_long_mode(scr->ui_screen_1_Label_Time, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_color(scr->ui_screen_1_Label_Time, lv_color_hex(0x91A8B5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(scr->ui_screen_1_Label_Time, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
    LV_FONT_DECLARE(font_notosanscjksc_regular_14_b49ae336_fb3f);
    lv_obj_set_style_text_font(scr->ui_screen_1_Label_Time, &font_notosanscjksc_regular_14_b49ae336_fb3f, LV_PART_MAIN | LV_STATE_DEFAULT);

    scr->ui_screen_1_Btn_Curve = lv_btn_create(scr->obj);
    lv_obj_set_pos(scr->ui_screen_1_Btn_Curve, 12, 34);
    lv_obj_set_size(scr->ui_screen_1_Btn_Curve, 296, 42);

    lv_obj_t *ui_screen_1_Btn_Curve_label = lv_label_create(scr->ui_screen_1_Btn_Curve);
    lv_label_set_text(ui_screen_1_Btn_Curve_label, "数据曲线");
    lv_label_set_long_mode(ui_screen_1_Btn_Curve_label, LV_LABEL_LONG_WRAP);
    lv_obj_center(ui_screen_1_Btn_Curve_label);
    lv_obj_set_style_bg_color(scr->ui_screen_1_Btn_Curve, lv_color_hex(0x16242F), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(scr->ui_screen_1_Btn_Curve, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(scr->ui_screen_1_Btn_Curve, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(scr->ui_screen_1_Btn_Curve, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(scr->ui_screen_1_Btn_Curve, lv_color_hex(0xE8EEF2), LV_PART_MAIN | LV_STATE_DEFAULT);
    LV_FONT_DECLARE(font_notosanscjksc_regular_14_b49ae336_fb3f);
    lv_obj_set_style_text_font(scr->ui_screen_1_Btn_Curve, &font_notosanscjksc_regular_14_b49ae336_fb3f, LV_PART_MAIN | LV_STATE_DEFAULT);

    scr->ui_screen_1_Btn_Settings = lv_btn_create(scr->obj);
    lv_obj_set_pos(scr->ui_screen_1_Btn_Settings, 12, 86);
    lv_obj_set_size(scr->ui_screen_1_Btn_Settings, 296, 42);

    lv_obj_t *ui_screen_1_Btn_Settings_label = lv_label_create(scr->ui_screen_1_Btn_Settings);
    lv_label_set_text(ui_screen_1_Btn_Settings_label, "参数设置");
    lv_label_set_long_mode(ui_screen_1_Btn_Settings_label, LV_LABEL_LONG_WRAP);
    lv_obj_center(ui_screen_1_Btn_Settings_label);
    lv_obj_set_style_bg_color(scr->ui_screen_1_Btn_Settings, lv_color_hex(0x16242F), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(scr->ui_screen_1_Btn_Settings, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(scr->ui_screen_1_Btn_Settings, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(scr->ui_screen_1_Btn_Settings, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(scr->ui_screen_1_Btn_Settings, lv_color_hex(0xE8EEF2), LV_PART_MAIN | LV_STATE_DEFAULT);
    LV_FONT_DECLARE(font_notosanscjksc_regular_14_b49ae336_fb3f);
    lv_obj_set_style_text_font(scr->ui_screen_1_Btn_Settings, &font_notosanscjksc_regular_14_b49ae336_fb3f, LV_PART_MAIN | LV_STATE_DEFAULT);

    scr->ui_screen_1_Btn_State = lv_btn_create(scr->obj);
    lv_obj_set_pos(scr->ui_screen_1_Btn_State, 12, 138);
    lv_obj_set_size(scr->ui_screen_1_Btn_State, 296, 42);

    lv_obj_t *ui_screen_1_Btn_State_label = lv_label_create(scr->ui_screen_1_Btn_State);
    lv_label_set_text(ui_screen_1_Btn_State_label, "设备状态");
    lv_label_set_long_mode(ui_screen_1_Btn_State_label, LV_LABEL_LONG_WRAP);
    lv_obj_center(ui_screen_1_Btn_State_label);
    lv_obj_set_style_bg_color(scr->ui_screen_1_Btn_State, lv_color_hex(0x16242F), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(scr->ui_screen_1_Btn_State, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(scr->ui_screen_1_Btn_State, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(scr->ui_screen_1_Btn_State, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(scr->ui_screen_1_Btn_State, lv_color_hex(0xE8EEF2), LV_PART_MAIN | LV_STATE_DEFAULT);
    LV_FONT_DECLARE(font_notosanscjksc_regular_14_b49ae336_fb3f);
    lv_obj_set_style_text_font(scr->ui_screen_1_Btn_State, &font_notosanscjksc_regular_14_b49ae336_fb3f, LV_PART_MAIN | LV_STATE_DEFAULT);

    scr->ui_screen_1_Btn_Info = lv_btn_create(scr->obj);
    lv_obj_set_pos(scr->ui_screen_1_Btn_Info, 12, 190);
    lv_obj_set_size(scr->ui_screen_1_Btn_Info, 296, 42);

    lv_obj_t *ui_screen_1_Btn_Info_label = lv_label_create(scr->ui_screen_1_Btn_Info);
    lv_label_set_text(ui_screen_1_Btn_Info_label, "设备信息");
    lv_label_set_long_mode(ui_screen_1_Btn_Info_label, LV_LABEL_LONG_WRAP);
    lv_obj_center(ui_screen_1_Btn_Info_label);
    lv_obj_set_style_bg_color(scr->ui_screen_1_Btn_Info, lv_color_hex(0x16242F), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(scr->ui_screen_1_Btn_Info, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(scr->ui_screen_1_Btn_Info, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(scr->ui_screen_1_Btn_Info, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(scr->ui_screen_1_Btn_Info, lv_color_hex(0xE8EEF2), LV_PART_MAIN | LV_STATE_DEFAULT);
    LV_FONT_DECLARE(font_notosanscjksc_regular_14_b49ae336_fb3f);
    lv_obj_set_style_text_font(scr->ui_screen_1_Btn_Info, &font_notosanscjksc_regular_14_b49ae336_fb3f, LV_PART_MAIN | LV_STATE_DEFAULT);


    screen_1_register_events(ui);
}

void screen_1_update_language(lang_type_t lang)
{
    screen_1_t *scr = screen_1_get(&ui_manager);
    if (!scr->obj)
        return;
    aic_set_language(lang);
    (void)scr;
}

void screen_1_update_current_language(void)
{
    screen_1_update_language(aic_get_language());
}
