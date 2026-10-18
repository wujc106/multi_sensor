/*!
    \file    screen_5.c
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
#include "screen_5.h"
#include "screen_5_event.h"


/* lv_scr_load_anim(auto_del = true) destroys the previous screen, but ui_manager keeps
 * the cached pointers. Clear them on delete so they never dangle and the screen can be
 * re-created on demand. */
static void screen_5_deleted_cb(lv_event_t *e)
{
    ui_manager_t *ui = (ui_manager_t *)lv_event_get_user_data(e);

    memset(screen_5_get(ui), 0, sizeof(screen_5_t));
}




void screen_5_create(ui_manager_t *ui)
{
    screen_5_t *scr = screen_5_get(ui);

    if (scr->obj) {
        screen_5_update_current_language();
        return;
    }

    /* Init scr->obj */
    scr->obj = lv_obj_create(NULL);
    lv_obj_add_event_cb(scr->obj, screen_5_deleted_cb, LV_EVENT_DELETE, ui);
    lv_obj_set_scrollbar_mode(scr->obj, LV_SCROLLBAR_MODE_OFF);

    /* Set style of scr->obj */
    lv_obj_set_style_bg_color(scr->obj, lv_color_hex(0x0D1620), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(scr->obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    scr->ui_screen_5_Label_Title = lv_label_create(scr->obj);
    lv_obj_set_pos(scr->ui_screen_5_Label_Title, 8, 8);
    lv_obj_set_size(scr->ui_screen_5_Label_Title, 104, 18);
    lv_label_set_text(scr->ui_screen_5_Label_Title, "设备信息");
    lv_obj_set_style_text_align(scr->ui_screen_5_Label_Title, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_long_mode(scr->ui_screen_5_Label_Title, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_color(scr->ui_screen_5_Label_Title, lv_color_hex(0xE8EEF2), LV_PART_MAIN | LV_STATE_DEFAULT);
    LV_FONT_DECLARE(font_notosanscjksc_regular_14_b49ae336_fb3f);
    lv_obj_set_style_text_font(scr->ui_screen_5_Label_Title, &font_notosanscjksc_regular_14_b49ae336_fb3f, LV_PART_MAIN | LV_STATE_DEFAULT);

    scr->ui_screen_5_Label_Time = lv_label_create(scr->obj);
    lv_obj_set_pos(scr->ui_screen_5_Label_Time, 244, 8);
    lv_obj_set_size(scr->ui_screen_5_Label_Time, 68, 18);
    lv_label_set_text(scr->ui_screen_5_Label_Time, "14:32:05");
    lv_obj_set_style_text_align(scr->ui_screen_5_Label_Time, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_long_mode(scr->ui_screen_5_Label_Time, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_color(scr->ui_screen_5_Label_Time, lv_color_hex(0x91A8B5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(scr->ui_screen_5_Label_Time, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
    LV_FONT_DECLARE(font_notosanscjksc_regular_14_b49ae336_fb3f);
    lv_obj_set_style_text_font(scr->ui_screen_5_Label_Time, &font_notosanscjksc_regular_14_b49ae336_fb3f, LV_PART_MAIN | LV_STATE_DEFAULT);

    scr->ui_screen_5_RowName_38 = lv_label_create(scr->obj);
    lv_obj_set_pos(scr->ui_screen_5_RowName_38, 14, 38);
    lv_obj_set_size(scr->ui_screen_5_RowName_38, 110, 14);
    lv_label_set_text(scr->ui_screen_5_RowName_38, "设备型号");
    lv_obj_set_style_text_align(scr->ui_screen_5_RowName_38, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_long_mode(scr->ui_screen_5_RowName_38, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_color(scr->ui_screen_5_RowName_38, lv_color_hex(0x91A8B5), LV_PART_MAIN | LV_STATE_DEFAULT);
    LV_FONT_DECLARE(font_notosanscjksc_regular_12_b49ae336_fb3f);
    lv_obj_set_style_text_font(scr->ui_screen_5_RowName_38, &font_notosanscjksc_regular_12_b49ae336_fb3f, LV_PART_MAIN | LV_STATE_DEFAULT);

    scr->ui_screen_5_Label_ModelValue = lv_label_create(scr->obj);
    lv_obj_set_pos(scr->ui_screen_5_Label_ModelValue, 126, 37);
    lv_obj_set_size(scr->ui_screen_5_Label_ModelValue, 180, 16);
    lv_label_set_text(scr->ui_screen_5_Label_ModelValue, "MS-5200 辐射检测仪");
    lv_obj_set_style_text_align(scr->ui_screen_5_Label_ModelValue, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_long_mode(scr->ui_screen_5_Label_ModelValue, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_color(scr->ui_screen_5_Label_ModelValue, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(scr->ui_screen_5_Label_ModelValue, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
    LV_FONT_DECLARE(font_notosanscjksc_regular_14_b49ae336_fb3f);
    lv_obj_set_style_text_font(scr->ui_screen_5_Label_ModelValue, &font_notosanscjksc_regular_14_b49ae336_fb3f, LV_PART_MAIN | LV_STATE_DEFAULT);

    scr->ui_screen_5_RowName_70 = lv_label_create(scr->obj);
    lv_obj_set_pos(scr->ui_screen_5_RowName_70, 14, 70);
    lv_obj_set_size(scr->ui_screen_5_RowName_70, 110, 14);
    lv_label_set_text(scr->ui_screen_5_RowName_70, "软件版本");
    lv_obj_set_style_text_align(scr->ui_screen_5_RowName_70, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_long_mode(scr->ui_screen_5_RowName_70, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_color(scr->ui_screen_5_RowName_70, lv_color_hex(0x91A8B5), LV_PART_MAIN | LV_STATE_DEFAULT);
    LV_FONT_DECLARE(font_notosanscjksc_regular_12_b49ae336_fb3f);
    lv_obj_set_style_text_font(scr->ui_screen_5_RowName_70, &font_notosanscjksc_regular_12_b49ae336_fb3f, LV_PART_MAIN | LV_STATE_DEFAULT);

    scr->ui_screen_5_Label_SwValue = lv_label_create(scr->obj);
    lv_obj_set_pos(scr->ui_screen_5_Label_SwValue, 126, 69);
    lv_obj_set_size(scr->ui_screen_5_Label_SwValue, 180, 16);
    lv_label_set_text(scr->ui_screen_5_Label_SwValue, "V1.0.0-beta");
    lv_obj_set_style_text_align(scr->ui_screen_5_Label_SwValue, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_long_mode(scr->ui_screen_5_Label_SwValue, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_color(scr->ui_screen_5_Label_SwValue, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(scr->ui_screen_5_Label_SwValue, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
    LV_FONT_DECLARE(font_notosanscjksc_regular_14_b49ae336_fb3f);
    lv_obj_set_style_text_font(scr->ui_screen_5_Label_SwValue, &font_notosanscjksc_regular_14_b49ae336_fb3f, LV_PART_MAIN | LV_STATE_DEFAULT);

    scr->ui_screen_5_RowName_102 = lv_label_create(scr->obj);
    lv_obj_set_pos(scr->ui_screen_5_RowName_102, 14, 102);
    lv_obj_set_size(scr->ui_screen_5_RowName_102, 110, 14);
    lv_label_set_text(scr->ui_screen_5_RowName_102, "硬件版本");
    lv_obj_set_style_text_align(scr->ui_screen_5_RowName_102, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_long_mode(scr->ui_screen_5_RowName_102, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_color(scr->ui_screen_5_RowName_102, lv_color_hex(0x91A8B5), LV_PART_MAIN | LV_STATE_DEFAULT);
    LV_FONT_DECLARE(font_notosanscjksc_regular_12_b49ae336_fb3f);
    lv_obj_set_style_text_font(scr->ui_screen_5_RowName_102, &font_notosanscjksc_regular_12_b49ae336_fb3f, LV_PART_MAIN | LV_STATE_DEFAULT);

    scr->ui_screen_5_Label_HwValue = lv_label_create(scr->obj);
    lv_obj_set_pos(scr->ui_screen_5_Label_HwValue, 126, 101);
    lv_obj_set_size(scr->ui_screen_5_Label_HwValue, 180, 16);
    lv_label_set_text(scr->ui_screen_5_Label_HwValue, "V2.1");
    lv_obj_set_style_text_align(scr->ui_screen_5_Label_HwValue, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_long_mode(scr->ui_screen_5_Label_HwValue, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_color(scr->ui_screen_5_Label_HwValue, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(scr->ui_screen_5_Label_HwValue, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
    LV_FONT_DECLARE(font_notosanscjksc_regular_14_b49ae336_fb3f);
    lv_obj_set_style_text_font(scr->ui_screen_5_Label_HwValue, &font_notosanscjksc_regular_14_b49ae336_fb3f, LV_PART_MAIN | LV_STATE_DEFAULT);

    scr->ui_screen_5_RowName_134 = lv_label_create(scr->obj);
    lv_obj_set_pos(scr->ui_screen_5_RowName_134, 14, 134);
    lv_obj_set_size(scr->ui_screen_5_RowName_134, 110, 14);
    lv_label_set_text(scr->ui_screen_5_RowName_134, "传感器类型");
    lv_obj_set_style_text_align(scr->ui_screen_5_RowName_134, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_long_mode(scr->ui_screen_5_RowName_134, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_color(scr->ui_screen_5_RowName_134, lv_color_hex(0x91A8B5), LV_PART_MAIN | LV_STATE_DEFAULT);
    LV_FONT_DECLARE(font_notosanscjksc_regular_12_b49ae336_fb3f);
    lv_obj_set_style_text_font(scr->ui_screen_5_RowName_134, &font_notosanscjksc_regular_12_b49ae336_fb3f, LV_PART_MAIN | LV_STATE_DEFAULT);

    scr->ui_screen_5_Label_SensorValue = lv_label_create(scr->obj);
    lv_obj_set_pos(scr->ui_screen_5_Label_SensorValue, 126, 133);
    lv_obj_set_size(scr->ui_screen_5_Label_SensorValue, 180, 16);
    lv_label_set_text(scr->ui_screen_5_Label_SensorValue, "盖革管 GM-J305");
    lv_obj_set_style_text_align(scr->ui_screen_5_Label_SensorValue, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_long_mode(scr->ui_screen_5_Label_SensorValue, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_color(scr->ui_screen_5_Label_SensorValue, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(scr->ui_screen_5_Label_SensorValue, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
    LV_FONT_DECLARE(font_notosanscjksc_regular_14_b49ae336_fb3f);
    lv_obj_set_style_text_font(scr->ui_screen_5_Label_SensorValue, &font_notosanscjksc_regular_14_b49ae336_fb3f, LV_PART_MAIN | LV_STATE_DEFAULT);

    scr->ui_screen_5_RowName_166 = lv_label_create(scr->obj);
    lv_obj_set_pos(scr->ui_screen_5_RowName_166, 14, 166);
    lv_obj_set_size(scr->ui_screen_5_RowName_166, 110, 14);
    lv_label_set_text(scr->ui_screen_5_RowName_166, "序列号");
    lv_obj_set_style_text_align(scr->ui_screen_5_RowName_166, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_long_mode(scr->ui_screen_5_RowName_166, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_color(scr->ui_screen_5_RowName_166, lv_color_hex(0x91A8B5), LV_PART_MAIN | LV_STATE_DEFAULT);
    LV_FONT_DECLARE(font_notosanscjksc_regular_12_b49ae336_fb3f);
    lv_obj_set_style_text_font(scr->ui_screen_5_RowName_166, &font_notosanscjksc_regular_12_b49ae336_fb3f, LV_PART_MAIN | LV_STATE_DEFAULT);

    scr->ui_screen_5_Label_SnValue = lv_label_create(scr->obj);
    lv_obj_set_pos(scr->ui_screen_5_Label_SnValue, 126, 165);
    lv_obj_set_size(scr->ui_screen_5_Label_SnValue, 180, 16);
    lv_label_set_text(scr->ui_screen_5_Label_SnValue, "SN20261015001");
    lv_obj_set_style_text_align(scr->ui_screen_5_Label_SnValue, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_long_mode(scr->ui_screen_5_Label_SnValue, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_color(scr->ui_screen_5_Label_SnValue, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(scr->ui_screen_5_Label_SnValue, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
    LV_FONT_DECLARE(font_notosanscjksc_regular_14_b49ae336_fb3f);
    lv_obj_set_style_text_font(scr->ui_screen_5_Label_SnValue, &font_notosanscjksc_regular_14_b49ae336_fb3f, LV_PART_MAIN | LV_STATE_DEFAULT);

    scr->ui_screen_5_RowName_198 = lv_label_create(scr->obj);
    lv_obj_set_pos(scr->ui_screen_5_RowName_198, 14, 198);
    lv_obj_set_size(scr->ui_screen_5_RowName_198, 110, 14);
    lv_label_set_text(scr->ui_screen_5_RowName_198, "累计运行");
    lv_obj_set_style_text_align(scr->ui_screen_5_RowName_198, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_long_mode(scr->ui_screen_5_RowName_198, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_color(scr->ui_screen_5_RowName_198, lv_color_hex(0x91A8B5), LV_PART_MAIN | LV_STATE_DEFAULT);
    LV_FONT_DECLARE(font_notosanscjksc_regular_12_b49ae336_fb3f);
    lv_obj_set_style_text_font(scr->ui_screen_5_RowName_198, &font_notosanscjksc_regular_12_b49ae336_fb3f, LV_PART_MAIN | LV_STATE_DEFAULT);

    scr->ui_screen_5_Label_RunValue = lv_label_create(scr->obj);
    lv_obj_set_pos(scr->ui_screen_5_Label_RunValue, 126, 197);
    lv_obj_set_size(scr->ui_screen_5_Label_RunValue, 180, 16);
    lv_label_set_text(scr->ui_screen_5_Label_RunValue, "128 h");
    lv_obj_set_style_text_align(scr->ui_screen_5_Label_RunValue, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_long_mode(scr->ui_screen_5_Label_RunValue, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_color(scr->ui_screen_5_Label_RunValue, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(scr->ui_screen_5_Label_RunValue, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
    LV_FONT_DECLARE(font_notosanscjksc_regular_14_b49ae336_fb3f);
    lv_obj_set_style_text_font(scr->ui_screen_5_Label_RunValue, &font_notosanscjksc_regular_14_b49ae336_fb3f, LV_PART_MAIN | LV_STATE_DEFAULT);


    screen_5_register_events(ui);
}

void screen_5_update_language(lang_type_t lang)
{
    screen_5_t *scr = screen_5_get(&ui_manager);
    if (!scr->obj)
        return;
    aic_set_language(lang);
    (void)scr;
}

void screen_5_update_current_language(void)
{
    screen_5_update_language(aic_get_language());
}
