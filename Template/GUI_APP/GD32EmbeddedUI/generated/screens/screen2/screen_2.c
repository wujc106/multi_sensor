/*!
    \file    screen_2.c
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
#include "screen_2.h"
#include "screen_2_event.h"


/* lv_scr_load_anim(auto_del = true) destroys the previous screen, but ui_manager keeps
 * the cached pointers. Clear them on delete so they never dangle and the screen can be
 * re-created on demand. */
static void screen_2_deleted_cb(lv_event_t *e)
{
    ui_manager_t *ui = (ui_manager_t *)lv_event_get_user_data(e);

    memset(screen_2_get(ui), 0, sizeof(screen_2_t));
}




void screen_2_create(ui_manager_t *ui)
{
    screen_2_t *scr = screen_2_get(ui);

    if (scr->obj) {
        screen_2_update_current_language();
        return;
    }

    /* Init scr->obj */
    scr->obj = lv_obj_create(NULL);
    lv_obj_add_event_cb(scr->obj, screen_2_deleted_cb, LV_EVENT_DELETE, ui);
    lv_obj_set_scrollbar_mode(scr->obj, LV_SCROLLBAR_MODE_OFF);

    /* Set style of scr->obj */
    lv_obj_set_style_bg_color(scr->obj, lv_color_hex(0x0D1620), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(scr->obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    scr->ui_screen_2_Label_Title = lv_label_create(scr->obj);
    lv_obj_set_pos(scr->ui_screen_2_Label_Title, 8, 8);
    lv_obj_set_size(scr->ui_screen_2_Label_Title, 104, 18);
    lv_label_set_text(scr->ui_screen_2_Label_Title, "数据曲线");
    lv_obj_set_style_text_align(scr->ui_screen_2_Label_Title, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_long_mode(scr->ui_screen_2_Label_Title, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_color(scr->ui_screen_2_Label_Title, lv_color_hex(0xE8EEF2), LV_PART_MAIN | LV_STATE_DEFAULT);
    LV_FONT_DECLARE(font_notosanscjksc_regular_14_b49ae336_fb3f);
    lv_obj_set_style_text_font(scr->ui_screen_2_Label_Title, &font_notosanscjksc_regular_14_b49ae336_fb3f, LV_PART_MAIN | LV_STATE_DEFAULT);

    scr->ui_screen_2_Label_Time = lv_label_create(scr->obj);
    lv_obj_set_pos(scr->ui_screen_2_Label_Time, 244, 8);
    lv_obj_set_size(scr->ui_screen_2_Label_Time, 68, 18);
    lv_label_set_text(scr->ui_screen_2_Label_Time, "14:32:05");
    lv_obj_set_style_text_align(scr->ui_screen_2_Label_Time, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_long_mode(scr->ui_screen_2_Label_Time, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_color(scr->ui_screen_2_Label_Time, lv_color_hex(0x91A8B5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(scr->ui_screen_2_Label_Time, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
    LV_FONT_DECLARE(font_notosanscjksc_regular_14_b49ae336_fb3f);
    lv_obj_set_style_text_font(scr->ui_screen_2_Label_Time, &font_notosanscjksc_regular_14_b49ae336_fb3f, LV_PART_MAIN | LV_STATE_DEFAULT);

    scr->ui_screen_2_Label_Channel = lv_label_create(scr->obj);
    lv_obj_set_pos(scr->ui_screen_2_Label_Channel, 8, 30);
    lv_obj_set_size(scr->ui_screen_2_Label_Channel, 200, 18);
    lv_label_set_text(scr->ui_screen_2_Label_Channel, "剂量率 µSv/h");
    lv_obj_set_style_text_align(scr->ui_screen_2_Label_Channel, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_long_mode(scr->ui_screen_2_Label_Channel, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_color(scr->ui_screen_2_Label_Channel, lv_color_hex(0x28B6A5), LV_PART_MAIN | LV_STATE_DEFAULT);
    LV_FONT_DECLARE(font_notosanscjksc_regular_14_b49ae336_fb3f);
    lv_obj_set_style_text_font(scr->ui_screen_2_Label_Channel, &font_notosanscjksc_regular_14_b49ae336_fb3f, LV_PART_MAIN | LV_STATE_DEFAULT);

    scr->ui_screen_2_Chart_1 = lv_chart_create(scr->obj);
    lv_obj_set_pos(scr->ui_screen_2_Chart_1, 36, 54);
    lv_obj_set_size(scr->ui_screen_2_Chart_1, 276, 146);
    lv_chart_set_type(scr->ui_screen_2_Chart_1, LV_CHART_TYPE_LINE);
    lv_chart_set_point_count(scr->ui_screen_2_Chart_1, 20);
    lv_chart_set_div_line_count(scr->ui_screen_2_Chart_1, 3, 5);
    lv_chart_set_range(scr->ui_screen_2_Chart_1, LV_CHART_AXIS_PRIMARY_Y, 0, 200);

    lv_chart_set_axis_tick(scr->ui_screen_2_Chart_1, LV_CHART_AXIS_PRIMARY_Y, 5, 0, 5, 0, true, 30);
    lv_chart_set_range(scr->ui_screen_2_Chart_1, LV_CHART_AXIS_SECONDARY_Y, 0, 200);

    lv_chart_set_axis_tick(scr->ui_screen_2_Chart_1, LV_CHART_AXIS_PRIMARY_X, 4, 0, 5, 0, false, 12);


    lv_chart_series_t * ui_screen_2_Chart_1_ser0 = lv_chart_add_series(scr->ui_screen_2_Chart_1, lv_color_hex(0x28B6A5), LV_CHART_AXIS_PRIMARY_Y);
    lv_chart_set_value_by_id(scr->ui_screen_2_Chart_1, ui_screen_2_Chart_1_ser0, 0, 50);
    lv_chart_set_value_by_id(scr->ui_screen_2_Chart_1, ui_screen_2_Chart_1_ser0, 1, 70);
    lv_chart_set_value_by_id(scr->ui_screen_2_Chart_1, ui_screen_2_Chart_1_ser0, 2, 60);
    lv_chart_set_value_by_id(scr->ui_screen_2_Chart_1, ui_screen_2_Chart_1_ser0, 3, 90);
    lv_chart_set_value_by_id(scr->ui_screen_2_Chart_1, ui_screen_2_Chart_1_ser0, 4, 80);
    lv_chart_set_value_by_id(scr->ui_screen_2_Chart_1, ui_screen_2_Chart_1_ser0, 5, 110);
    lv_chart_set_value_by_id(scr->ui_screen_2_Chart_1, ui_screen_2_Chart_1_ser0, 6, 70);
    lv_chart_set_value_by_id(scr->ui_screen_2_Chart_1, ui_screen_2_Chart_1_ser0, 7, 60);
    lv_chart_set_value_by_id(scr->ui_screen_2_Chart_1, ui_screen_2_Chart_1_ser0, 8, 80);
    lv_chart_set_value_by_id(scr->ui_screen_2_Chart_1, ui_screen_2_Chart_1_ser0, 9, 1);
    lv_chart_set_value_by_id(scr->ui_screen_2_Chart_1, ui_screen_2_Chart_1_ser0, 10, 90);
    lv_chart_set_value_by_id(scr->ui_screen_2_Chart_1, ui_screen_2_Chart_1_ser0, 11, 70);
    lv_chart_set_value_by_id(scr->ui_screen_2_Chart_1, ui_screen_2_Chart_1_ser0, 12, 50);
    lv_chart_set_value_by_id(scr->ui_screen_2_Chart_1, ui_screen_2_Chart_1_ser0, 13, 80);
    lv_chart_set_value_by_id(scr->ui_screen_2_Chart_1, ui_screen_2_Chart_1_ser0, 14, 90);
    lv_chart_set_value_by_id(scr->ui_screen_2_Chart_1, ui_screen_2_Chart_1_ser0, 15, 120);
    lv_chart_set_value_by_id(scr->ui_screen_2_Chart_1, ui_screen_2_Chart_1_ser0, 16, 80);
    lv_chart_set_value_by_id(scr->ui_screen_2_Chart_1, ui_screen_2_Chart_1_ser0, 17, 70);
    lv_chart_set_value_by_id(scr->ui_screen_2_Chart_1, ui_screen_2_Chart_1_ser0, 18, 90);
    lv_chart_set_value_by_id(scr->ui_screen_2_Chart_1, ui_screen_2_Chart_1_ser0, 19, 86);
    lv_obj_set_style_bg_color(scr->ui_screen_2_Chart_1, lv_color_hex(0x101C26), LV_PART_MAIN | LV_STATE_DEFAULT);

    scr->ui_screen_2_Label_Stat = lv_label_create(scr->obj);
    lv_obj_set_pos(scr->ui_screen_2_Label_Stat, 8, 208);
    lv_obj_set_size(scr->ui_screen_2_Label_Stat, 304, 16);
    lv_label_set_text(scr->ui_screen_2_Label_Stat, "min 0.42   max 1.35   avg 0.87");
    lv_obj_set_style_text_align(scr->ui_screen_2_Label_Stat, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_long_mode(scr->ui_screen_2_Label_Stat, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_color(scr->ui_screen_2_Label_Stat, lv_color_hex(0x91A8B5), LV_PART_MAIN | LV_STATE_DEFAULT);
    LV_FONT_DECLARE(font_notosanscjksc_regular_12_b49ae336_fb3f);
    lv_obj_set_style_text_font(scr->ui_screen_2_Label_Stat, &font_notosanscjksc_regular_12_b49ae336_fb3f, LV_PART_MAIN | LV_STATE_DEFAULT);


    screen_2_register_events(ui);
}

void screen_2_update_language(lang_type_t lang)
{
    screen_2_t *scr = screen_2_get(&ui_manager);
    if (!scr->obj)
        return;
    aic_set_language(lang);
    (void)scr;
}

void screen_2_update_current_language(void)
{
    screen_2_update_language(aic_get_language());
}
