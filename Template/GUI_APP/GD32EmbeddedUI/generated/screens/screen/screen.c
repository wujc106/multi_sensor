/*!
    \file    screen.c
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
#include "screen.h"
#include "screen_event.h"


/* lv_scr_load_anim(auto_del = true) destroys the previous screen, but ui_manager keeps
 * the cached pointers. Clear them on delete so they never dangle and the screen can be
 * re-created on demand. */
static void screen_deleted_cb(lv_event_t *e)
{
    ui_manager_t *ui = (ui_manager_t *)lv_event_get_user_data(e);

    memset(screen_get(ui), 0, sizeof(screen_t));
}




void screen_create(ui_manager_t *ui)
{
    screen_t *scr = screen_get(ui);

    if (scr->obj) {
        screen_update_current_language();
        return;
    }

    /* Init scr->obj */
    scr->obj = lv_obj_create(NULL);
    lv_obj_add_event_cb(scr->obj, screen_deleted_cb, LV_EVENT_DELETE, ui);
    lv_obj_set_scrollbar_mode(scr->obj, LV_SCROLLBAR_MODE_OFF);

    /* Set style of scr->obj */
    lv_obj_set_style_bg_color(scr->obj, lv_color_hex(0x0D1620), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(scr->obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    scr->ui_screen_Label_Title = lv_label_create(scr->obj);
    lv_obj_set_pos(scr->ui_screen_Label_Title, 8, 8);
    lv_obj_set_size(scr->ui_screen_Label_Title, 104, 18);
    lv_label_set_text(scr->ui_screen_Label_Title, "辐射监测仪");
    lv_obj_set_style_text_align(scr->ui_screen_Label_Title, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_long_mode(scr->ui_screen_Label_Title, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_color(scr->ui_screen_Label_Title, lv_color_hex(0xE8EEF2), LV_PART_MAIN | LV_STATE_DEFAULT);
    LV_FONT_DECLARE(font_notosanscjksc_regular_14_b49ae336_fb3f);
    lv_obj_set_style_text_font(scr->ui_screen_Label_Title, &font_notosanscjksc_regular_14_b49ae336_fb3f, LV_PART_MAIN | LV_STATE_DEFAULT);

    scr->ui_screen_Label_Time = lv_label_create(scr->obj);
    lv_obj_set_pos(scr->ui_screen_Label_Time, 244, 8);
    lv_obj_set_size(scr->ui_screen_Label_Time, 68, 18);
    lv_label_set_text(scr->ui_screen_Label_Time, "14:32:05");
    lv_obj_set_style_text_align(scr->ui_screen_Label_Time, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_long_mode(scr->ui_screen_Label_Time, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_color(scr->ui_screen_Label_Time, lv_color_hex(0x91A8B5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(scr->ui_screen_Label_Time, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
    LV_FONT_DECLARE(font_notosanscjksc_regular_14_b49ae336_fb3f);
    lv_obj_set_style_text_font(scr->ui_screen_Label_Time, &font_notosanscjksc_regular_14_b49ae336_fb3f, LV_PART_MAIN | LV_STATE_DEFAULT);

    scr->ui_screen_Label_Status = lv_label_create(scr->obj);
    lv_obj_set_pos(scr->ui_screen_Label_Status, 118, 8);
    lv_obj_set_size(scr->ui_screen_Label_Status, 70, 18);
    lv_label_set_text(scr->ui_screen_Label_Status, "正常");
    lv_obj_set_style_text_align(scr->ui_screen_Label_Status, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_long_mode(scr->ui_screen_Label_Status, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_color(scr->ui_screen_Label_Status, lv_color_hex(0x97C459), LV_PART_MAIN | LV_STATE_DEFAULT);
    LV_FONT_DECLARE(font_notosanscjksc_regular_14_b49ae336_fb3f);
    lv_obj_set_style_text_font(scr->ui_screen_Label_Status, &font_notosanscjksc_regular_14_b49ae336_fb3f, LV_PART_MAIN | LV_STATE_DEFAULT);

    scr->ui_screen_Arc_Value = lv_arc_create(scr->obj);
    lv_obj_set_pos(scr->ui_screen_Arc_Value, 16, 44);
    lv_obj_set_size(scr->ui_screen_Arc_Value, 132, 132);
    lv_arc_set_range(scr->ui_screen_Arc_Value, 0, 100);
    lv_arc_set_bg_angles(scr->ui_screen_Arc_Value, 135, 45);
    lv_arc_set_mode(scr->ui_screen_Arc_Value, LV_ARC_MODE_NORMAL);
    lv_arc_set_value(scr->ui_screen_Arc_Value, 25);

    scr->ui_screen_Label_Value = lv_label_create(scr->obj);
    lv_obj_set_pos(scr->ui_screen_Label_Value, 28, 94);
    lv_obj_set_size(scr->ui_screen_Label_Value, 108, 30);
    lv_label_set_text(scr->ui_screen_Label_Value, "0.86");
    lv_obj_set_style_text_align(scr->ui_screen_Label_Value, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_long_mode(scr->ui_screen_Label_Value, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_color(scr->ui_screen_Label_Value, lv_color_hex(0xE8EEF2), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(scr->ui_screen_Label_Value, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    LV_FONT_DECLARE(font_notosanscjksc_regular_26_b49ae336_fb3f);
    lv_obj_set_style_text_font(scr->ui_screen_Label_Value, &font_notosanscjksc_regular_26_b49ae336_fb3f, LV_PART_MAIN | LV_STATE_DEFAULT);

    scr->ui_screen_Label_Unit = lv_label_create(scr->obj);
    lv_obj_set_pos(scr->ui_screen_Label_Unit, 28, 126);
    lv_obj_set_size(scr->ui_screen_Label_Unit, 108, 14);
    lv_label_set_text(scr->ui_screen_Label_Unit, "µSv/h");
    lv_obj_set_style_text_align(scr->ui_screen_Label_Unit, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_long_mode(scr->ui_screen_Label_Unit, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_color(scr->ui_screen_Label_Unit, lv_color_hex(0x91A8B5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(scr->ui_screen_Label_Unit, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    LV_FONT_DECLARE(font_notosanscjksc_regular_12_b49ae336_fb3f);
    lv_obj_set_style_text_font(scr->ui_screen_Label_Unit, &font_notosanscjksc_regular_12_b49ae336_fb3f, LV_PART_MAIN | LV_STATE_DEFAULT);

    scr->ui_screen_Label_Channel = lv_label_create(scr->obj);
    lv_obj_set_pos(scr->ui_screen_Label_Channel, 16, 184);
    lv_obj_set_size(scr->ui_screen_Label_Channel, 132, 16);
    lv_label_set_text(scr->ui_screen_Label_Channel, "剂量率");
    lv_obj_set_style_text_align(scr->ui_screen_Label_Channel, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_long_mode(scr->ui_screen_Label_Channel, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_color(scr->ui_screen_Label_Channel, lv_color_hex(0x91A8B5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(scr->ui_screen_Label_Channel, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    LV_FONT_DECLARE(font_notosanscjksc_regular_14_b49ae336_fb3f);
    lv_obj_set_style_text_font(scr->ui_screen_Label_Channel, &font_notosanscjksc_regular_14_b49ae336_fb3f, LV_PART_MAIN | LV_STATE_DEFAULT);

    scr->ui_screen_Label_TempName_Tile = lv_obj_create(scr->obj);
    lv_obj_set_pos(scr->ui_screen_Label_TempName_Tile, 156, 36);
    lv_obj_set_size(scr->ui_screen_Label_TempName_Tile, 158, 44);
    lv_obj_set_scrollbar_mode(scr->ui_screen_Label_TempName_Tile, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_color(scr->ui_screen_Label_TempName_Tile, lv_color_hex(0x16242F), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(scr->ui_screen_Label_TempName_Tile, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(scr->ui_screen_Label_TempName_Tile, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(scr->ui_screen_Label_TempName_Tile, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(scr->ui_screen_Label_TempName_Tile, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(scr->ui_screen_Label_TempName_Tile, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(scr->ui_screen_Label_TempName_Tile, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(scr->ui_screen_Label_TempName_Tile, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    scr->ui_screen_Label_TempName = lv_label_create(scr->ui_screen_Label_TempName_Tile);
    lv_obj_set_pos(scr->ui_screen_Label_TempName, 8, 12);
    lv_obj_set_size(scr->ui_screen_Label_TempName, 56, 19);
    lv_label_set_text(scr->ui_screen_Label_TempName, "温度");
    lv_obj_set_style_text_align(scr->ui_screen_Label_TempName, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_long_mode(scr->ui_screen_Label_TempName, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_color(scr->ui_screen_Label_TempName, lv_color_hex(0x91A8B5), LV_PART_MAIN | LV_STATE_DEFAULT);
    LV_FONT_DECLARE(font_notosanscjksc_regular_14_b49ae336_fb3f);
    lv_obj_set_style_text_font(scr->ui_screen_Label_TempName, &font_notosanscjksc_regular_14_b49ae336_fb3f, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_flag(scr->ui_screen_Label_TempName, LV_OBJ_FLAG_IGNORE_LAYOUT);

    scr->ui_screen_Label_TempValue = lv_label_create(scr->ui_screen_Label_TempName_Tile);
    lv_obj_set_pos(scr->ui_screen_Label_TempValue, 66, 9);
    lv_obj_set_size(scr->ui_screen_Label_TempValue, 48, 25);
    lv_label_set_text(scr->ui_screen_Label_TempValue, "26.8");
    lv_obj_set_style_text_align(scr->ui_screen_Label_TempValue, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_long_mode(scr->ui_screen_Label_TempValue, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_color(scr->ui_screen_Label_TempValue, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(scr->ui_screen_Label_TempValue, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
    LV_FONT_DECLARE(font_notosanscjksc_regular_18_b49ae336_fb3f);
    lv_obj_set_style_text_font(scr->ui_screen_Label_TempValue, &font_notosanscjksc_regular_18_b49ae336_fb3f, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_flag(scr->ui_screen_Label_TempValue, LV_OBJ_FLAG_IGNORE_LAYOUT);

    scr->ui_screen_Label_TempUnit = lv_label_create(scr->ui_screen_Label_TempName_Tile);
    lv_obj_set_pos(scr->ui_screen_Label_TempUnit, 115, 14);
    lv_obj_set_size(scr->ui_screen_Label_TempUnit, 40, 16);
    lv_label_set_text(scr->ui_screen_Label_TempUnit, "°C");
    lv_obj_set_style_text_align(scr->ui_screen_Label_TempUnit, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_long_mode(scr->ui_screen_Label_TempUnit, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_color(scr->ui_screen_Label_TempUnit, lv_color_hex(0x91A8B5), LV_PART_MAIN | LV_STATE_DEFAULT);
    LV_FONT_DECLARE(font_notosanscjksc_regular_12_b49ae336_fb3f);
    lv_obj_set_style_text_font(scr->ui_screen_Label_TempUnit, &font_notosanscjksc_regular_12_b49ae336_fb3f, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_flag(scr->ui_screen_Label_TempUnit, LV_OBJ_FLAG_IGNORE_LAYOUT);

    scr->ui_screen_Label_HumName_Tile = lv_obj_create(scr->obj);
    lv_obj_set_pos(scr->ui_screen_Label_HumName_Tile, 156, 88);
    lv_obj_set_size(scr->ui_screen_Label_HumName_Tile, 158, 44);
    lv_obj_set_scrollbar_mode(scr->ui_screen_Label_HumName_Tile, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_color(scr->ui_screen_Label_HumName_Tile, lv_color_hex(0x16242F), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(scr->ui_screen_Label_HumName_Tile, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(scr->ui_screen_Label_HumName_Tile, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(scr->ui_screen_Label_HumName_Tile, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(scr->ui_screen_Label_HumName_Tile, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(scr->ui_screen_Label_HumName_Tile, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(scr->ui_screen_Label_HumName_Tile, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(scr->ui_screen_Label_HumName_Tile, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    scr->ui_screen_Label_HumName = lv_label_create(scr->ui_screen_Label_HumName_Tile);
    lv_obj_set_pos(scr->ui_screen_Label_HumName, 8, 12);
    lv_obj_set_size(scr->ui_screen_Label_HumName, 56, 19);
    lv_label_set_text(scr->ui_screen_Label_HumName, "湿度");
    lv_obj_set_style_text_align(scr->ui_screen_Label_HumName, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_long_mode(scr->ui_screen_Label_HumName, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_color(scr->ui_screen_Label_HumName, lv_color_hex(0x91A8B5), LV_PART_MAIN | LV_STATE_DEFAULT);
    LV_FONT_DECLARE(font_notosanscjksc_regular_14_b49ae336_fb3f);
    lv_obj_set_style_text_font(scr->ui_screen_Label_HumName, &font_notosanscjksc_regular_14_b49ae336_fb3f, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_flag(scr->ui_screen_Label_HumName, LV_OBJ_FLAG_IGNORE_LAYOUT);

    scr->ui_screen_Label_HumValue = lv_label_create(scr->ui_screen_Label_HumName_Tile);
    lv_obj_set_pos(scr->ui_screen_Label_HumValue, 66, 9);
    lv_obj_set_size(scr->ui_screen_Label_HumValue, 48, 25);
    lv_label_set_text(scr->ui_screen_Label_HumValue, "58.2");
    lv_obj_set_style_text_align(scr->ui_screen_Label_HumValue, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_long_mode(scr->ui_screen_Label_HumValue, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_color(scr->ui_screen_Label_HumValue, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(scr->ui_screen_Label_HumValue, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
    LV_FONT_DECLARE(font_notosanscjksc_regular_18_b49ae336_fb3f);
    lv_obj_set_style_text_font(scr->ui_screen_Label_HumValue, &font_notosanscjksc_regular_18_b49ae336_fb3f, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_flag(scr->ui_screen_Label_HumValue, LV_OBJ_FLAG_IGNORE_LAYOUT);

    scr->ui_screen_Label_HumUnit = lv_label_create(scr->ui_screen_Label_HumName_Tile);
    lv_obj_set_pos(scr->ui_screen_Label_HumUnit, 115, 14);
    lv_obj_set_size(scr->ui_screen_Label_HumUnit, 40, 16);
    lv_label_set_text(scr->ui_screen_Label_HumUnit, "%RH");
    lv_obj_set_style_text_align(scr->ui_screen_Label_HumUnit, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_long_mode(scr->ui_screen_Label_HumUnit, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_color(scr->ui_screen_Label_HumUnit, lv_color_hex(0x91A8B5), LV_PART_MAIN | LV_STATE_DEFAULT);
    LV_FONT_DECLARE(font_notosanscjksc_regular_12_b49ae336_fb3f);
    lv_obj_set_style_text_font(scr->ui_screen_Label_HumUnit, &font_notosanscjksc_regular_12_b49ae336_fb3f, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_flag(scr->ui_screen_Label_HumUnit, LV_OBJ_FLAG_IGNORE_LAYOUT);

    scr->ui_screen_Label_DoseName_Tile = lv_obj_create(scr->obj);
    lv_obj_set_pos(scr->ui_screen_Label_DoseName_Tile, 156, 140);
    lv_obj_set_size(scr->ui_screen_Label_DoseName_Tile, 158, 44);
    lv_obj_set_scrollbar_mode(scr->ui_screen_Label_DoseName_Tile, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_color(scr->ui_screen_Label_DoseName_Tile, lv_color_hex(0x16242F), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(scr->ui_screen_Label_DoseName_Tile, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(scr->ui_screen_Label_DoseName_Tile, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(scr->ui_screen_Label_DoseName_Tile, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(scr->ui_screen_Label_DoseName_Tile, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(scr->ui_screen_Label_DoseName_Tile, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(scr->ui_screen_Label_DoseName_Tile, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(scr->ui_screen_Label_DoseName_Tile, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    scr->ui_screen_Label_DoseName = lv_label_create(scr->ui_screen_Label_DoseName_Tile);
    lv_obj_set_pos(scr->ui_screen_Label_DoseName, 8, 12);
    lv_obj_set_size(scr->ui_screen_Label_DoseName, 56, 19);
    lv_label_set_text(scr->ui_screen_Label_DoseName, "累计剂量");
    lv_obj_set_style_text_align(scr->ui_screen_Label_DoseName, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_long_mode(scr->ui_screen_Label_DoseName, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_color(scr->ui_screen_Label_DoseName, lv_color_hex(0x91A8B5), LV_PART_MAIN | LV_STATE_DEFAULT);
    LV_FONT_DECLARE(font_notosanscjksc_regular_14_b49ae336_fb3f);
    lv_obj_set_style_text_font(scr->ui_screen_Label_DoseName, &font_notosanscjksc_regular_14_b49ae336_fb3f, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_flag(scr->ui_screen_Label_DoseName, LV_OBJ_FLAG_IGNORE_LAYOUT);

    scr->ui_screen_Label_DoseValue = lv_label_create(scr->ui_screen_Label_DoseName_Tile);
    lv_obj_set_pos(scr->ui_screen_Label_DoseValue, 66, 9);
    lv_obj_set_size(scr->ui_screen_Label_DoseValue, 48, 25);
    lv_label_set_text(scr->ui_screen_Label_DoseValue, "12.4");
    lv_obj_set_style_text_align(scr->ui_screen_Label_DoseValue, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_long_mode(scr->ui_screen_Label_DoseValue, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_color(scr->ui_screen_Label_DoseValue, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(scr->ui_screen_Label_DoseValue, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
    LV_FONT_DECLARE(font_notosanscjksc_regular_18_b49ae336_fb3f);
    lv_obj_set_style_text_font(scr->ui_screen_Label_DoseValue, &font_notosanscjksc_regular_18_b49ae336_fb3f, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_flag(scr->ui_screen_Label_DoseValue, LV_OBJ_FLAG_IGNORE_LAYOUT);

    scr->ui_screen_Label_DoseUnit = lv_label_create(scr->ui_screen_Label_DoseName_Tile);
    lv_obj_set_pos(scr->ui_screen_Label_DoseUnit, 115, 14);
    lv_obj_set_size(scr->ui_screen_Label_DoseUnit, 40, 16);
    lv_label_set_text(scr->ui_screen_Label_DoseUnit, "µSv");
    lv_obj_set_style_text_align(scr->ui_screen_Label_DoseUnit, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_long_mode(scr->ui_screen_Label_DoseUnit, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_color(scr->ui_screen_Label_DoseUnit, lv_color_hex(0x91A8B5), LV_PART_MAIN | LV_STATE_DEFAULT);
    LV_FONT_DECLARE(font_notosanscjksc_regular_12_b49ae336_fb3f);
    lv_obj_set_style_text_font(scr->ui_screen_Label_DoseUnit, &font_notosanscjksc_regular_12_b49ae336_fb3f, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_flag(scr->ui_screen_Label_DoseUnit, LV_OBJ_FLAG_IGNORE_LAYOUT);

    scr->ui_screen_Label_BatName_Tile = lv_obj_create(scr->obj);
    lv_obj_set_pos(scr->ui_screen_Label_BatName_Tile, 156, 192);
    lv_obj_set_size(scr->ui_screen_Label_BatName_Tile, 158, 44);
    lv_obj_set_scrollbar_mode(scr->ui_screen_Label_BatName_Tile, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_color(scr->ui_screen_Label_BatName_Tile, lv_color_hex(0x16242F), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(scr->ui_screen_Label_BatName_Tile, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(scr->ui_screen_Label_BatName_Tile, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(scr->ui_screen_Label_BatName_Tile, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(scr->ui_screen_Label_BatName_Tile, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(scr->ui_screen_Label_BatName_Tile, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(scr->ui_screen_Label_BatName_Tile, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(scr->ui_screen_Label_BatName_Tile, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    scr->ui_screen_Label_BatName = lv_label_create(scr->ui_screen_Label_BatName_Tile);
    lv_obj_set_pos(scr->ui_screen_Label_BatName, 8, 12);
    lv_obj_set_size(scr->ui_screen_Label_BatName, 56, 19);
    lv_label_set_text(scr->ui_screen_Label_BatName, "电池");
    lv_obj_set_style_text_align(scr->ui_screen_Label_BatName, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_long_mode(scr->ui_screen_Label_BatName, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_color(scr->ui_screen_Label_BatName, lv_color_hex(0x91A8B5), LV_PART_MAIN | LV_STATE_DEFAULT);
    LV_FONT_DECLARE(font_notosanscjksc_regular_14_b49ae336_fb3f);
    lv_obj_set_style_text_font(scr->ui_screen_Label_BatName, &font_notosanscjksc_regular_14_b49ae336_fb3f, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_flag(scr->ui_screen_Label_BatName, LV_OBJ_FLAG_IGNORE_LAYOUT);

    scr->ui_screen_Label_BatValue = lv_label_create(scr->ui_screen_Label_BatName_Tile);
    lv_obj_set_pos(scr->ui_screen_Label_BatValue, 66, 9);
    lv_obj_set_size(scr->ui_screen_Label_BatValue, 48, 25);
    lv_label_set_text(scr->ui_screen_Label_BatValue, "87");
    lv_obj_set_style_text_align(scr->ui_screen_Label_BatValue, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_long_mode(scr->ui_screen_Label_BatValue, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_color(scr->ui_screen_Label_BatValue, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(scr->ui_screen_Label_BatValue, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
    LV_FONT_DECLARE(font_notosanscjksc_regular_18_b49ae336_fb3f);
    lv_obj_set_style_text_font(scr->ui_screen_Label_BatValue, &font_notosanscjksc_regular_18_b49ae336_fb3f, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_flag(scr->ui_screen_Label_BatValue, LV_OBJ_FLAG_IGNORE_LAYOUT);

    scr->ui_screen_Label_BatUnit = lv_label_create(scr->ui_screen_Label_BatName_Tile);
    lv_obj_set_pos(scr->ui_screen_Label_BatUnit, 115, 14);
    lv_obj_set_size(scr->ui_screen_Label_BatUnit, 40, 16);
    lv_label_set_text(scr->ui_screen_Label_BatUnit, "%");
    lv_obj_set_style_text_align(scr->ui_screen_Label_BatUnit, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_long_mode(scr->ui_screen_Label_BatUnit, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_color(scr->ui_screen_Label_BatUnit, lv_color_hex(0x91A8B5), LV_PART_MAIN | LV_STATE_DEFAULT);
    LV_FONT_DECLARE(font_notosanscjksc_regular_12_b49ae336_fb3f);
    lv_obj_set_style_text_font(scr->ui_screen_Label_BatUnit, &font_notosanscjksc_regular_12_b49ae336_fb3f, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_flag(scr->ui_screen_Label_BatUnit, LV_OBJ_FLAG_IGNORE_LAYOUT);


    screen_register_events(ui);
}

void screen_update_language(lang_type_t lang)
{
    screen_t *scr = screen_get(&ui_manager);
    if (!scr->obj)
        return;
    aic_set_language(lang);
    (void)scr;
}

void screen_update_current_language(void)
{
    screen_update_language(aic_get_language());
}
