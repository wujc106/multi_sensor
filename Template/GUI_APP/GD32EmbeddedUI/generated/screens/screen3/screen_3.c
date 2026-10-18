/*!
    \file    screen_3.c
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
#include "screen_3.h"
#include "screen_3_event.h"


/* lv_scr_load_anim(auto_del = true) destroys the previous screen, but ui_manager keeps
 * the cached pointers. Clear them on delete so they never dangle and the screen can be
 * re-created on demand. */
static void screen_3_deleted_cb(lv_event_t *e)
{
    ui_manager_t *ui = (ui_manager_t *)lv_event_get_user_data(e);

    memset(screen_3_get(ui), 0, sizeof(screen_3_t));
}




void screen_3_create(ui_manager_t *ui)
{
    screen_3_t *scr = screen_3_get(ui);

    if (scr->obj) {
        screen_3_update_current_language();
        return;
    }

    /* Init scr->obj */
    scr->obj = lv_obj_create(NULL);
    lv_obj_add_event_cb(scr->obj, screen_3_deleted_cb, LV_EVENT_DELETE, ui);
    lv_obj_set_scrollbar_mode(scr->obj, LV_SCROLLBAR_MODE_OFF);

    /* Set style of scr->obj */
    lv_obj_set_style_bg_color(scr->obj, lv_color_hex(0x0D1620), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(scr->obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    scr->ui_screen_3_Label_Title = lv_label_create(scr->obj);
    lv_obj_set_pos(scr->ui_screen_3_Label_Title, 8, 8);
    lv_obj_set_size(scr->ui_screen_3_Label_Title, 104, 18);
    lv_label_set_text(scr->ui_screen_3_Label_Title, "参数设置");
    lv_obj_set_style_text_align(scr->ui_screen_3_Label_Title, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_long_mode(scr->ui_screen_3_Label_Title, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_color(scr->ui_screen_3_Label_Title, lv_color_hex(0xE8EEF2), LV_PART_MAIN | LV_STATE_DEFAULT);
    LV_FONT_DECLARE(font_notosanscjksc_regular_14_b49ae336_fb3f);
    lv_obj_set_style_text_font(scr->ui_screen_3_Label_Title, &font_notosanscjksc_regular_14_b49ae336_fb3f, LV_PART_MAIN | LV_STATE_DEFAULT);

    scr->ui_screen_3_Label_Time = lv_label_create(scr->obj);
    lv_obj_set_pos(scr->ui_screen_3_Label_Time, 244, 8);
    lv_obj_set_size(scr->ui_screen_3_Label_Time, 68, 18);
    lv_label_set_text(scr->ui_screen_3_Label_Time, "14:32:05");
    lv_obj_set_style_text_align(scr->ui_screen_3_Label_Time, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_long_mode(scr->ui_screen_3_Label_Time, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_color(scr->ui_screen_3_Label_Time, lv_color_hex(0x91A8B5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(scr->ui_screen_3_Label_Time, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
    LV_FONT_DECLARE(font_notosanscjksc_regular_14_b49ae336_fb3f);
    lv_obj_set_style_text_font(scr->ui_screen_3_Label_Time, &font_notosanscjksc_regular_14_b49ae336_fb3f, LV_PART_MAIN | LV_STATE_DEFAULT);

    scr->ui_screen_3_Container_Channel = lv_obj_create(scr->obj);
    lv_obj_set_pos(scr->ui_screen_3_Container_Channel, 12, 36);
    lv_obj_set_size(scr->ui_screen_3_Container_Channel, 296, 56);
    lv_obj_set_scrollbar_mode(scr->ui_screen_3_Container_Channel, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_color(scr->ui_screen_3_Container_Channel, lv_color_hex(0x16242F), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(scr->ui_screen_3_Container_Channel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(scr->ui_screen_3_Container_Channel, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(scr->ui_screen_3_Container_Channel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(scr->ui_screen_3_Container_Channel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(scr->ui_screen_3_Container_Channel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(scr->ui_screen_3_Container_Channel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(scr->ui_screen_3_Container_Channel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    scr->ui_screen_3_Label_ChannelName = lv_label_create(scr->ui_screen_3_Container_Channel);
    lv_obj_set_pos(scr->ui_screen_3_Label_ChannelName, 12, 18);
    lv_obj_set_size(scr->ui_screen_3_Label_ChannelName, 110, 20);
    lv_label_set_text(scr->ui_screen_3_Label_ChannelName, "测量对象");
    lv_obj_set_style_text_align(scr->ui_screen_3_Label_ChannelName, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_long_mode(scr->ui_screen_3_Label_ChannelName, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_color(scr->ui_screen_3_Label_ChannelName, lv_color_hex(0xE8EEF2), LV_PART_MAIN | LV_STATE_DEFAULT);
    LV_FONT_DECLARE(font_notosanscjksc_regular_14_b49ae336_fb3f);
    lv_obj_set_style_text_font(scr->ui_screen_3_Label_ChannelName, &font_notosanscjksc_regular_14_b49ae336_fb3f, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_flag(scr->ui_screen_3_Label_ChannelName, LV_OBJ_FLAG_IGNORE_LAYOUT);

    scr->ui_screen_3_Label_ChannelValue = lv_label_create(scr->ui_screen_3_Container_Channel);
    lv_obj_set_pos(scr->ui_screen_3_Label_ChannelValue, 110, 15);
    lv_obj_set_size(scr->ui_screen_3_Label_ChannelValue, 170, 25);
    lv_label_set_text(scr->ui_screen_3_Label_ChannelValue, "剂量率");
    lv_obj_set_style_text_align(scr->ui_screen_3_Label_ChannelValue, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_long_mode(scr->ui_screen_3_Label_ChannelValue, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_color(scr->ui_screen_3_Label_ChannelValue, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(scr->ui_screen_3_Label_ChannelValue, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
    LV_FONT_DECLARE(font_notosanscjksc_regular_18_b49ae336_fb3f);
    lv_obj_set_style_text_font(scr->ui_screen_3_Label_ChannelValue, &font_notosanscjksc_regular_18_b49ae336_fb3f, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_flag(scr->ui_screen_3_Label_ChannelValue, LV_OBJ_FLAG_IGNORE_LAYOUT);

    scr->ui_screen_3_Container_P1 = lv_obj_create(scr->obj);
    lv_obj_set_pos(scr->ui_screen_3_Container_P1, 12, 102);
    lv_obj_set_size(scr->ui_screen_3_Container_P1, 296, 56);
    lv_obj_set_scrollbar_mode(scr->ui_screen_3_Container_P1, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_color(scr->ui_screen_3_Container_P1, lv_color_hex(0x16242F), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(scr->ui_screen_3_Container_P1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(scr->ui_screen_3_Container_P1, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(scr->ui_screen_3_Container_P1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(scr->ui_screen_3_Container_P1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(scr->ui_screen_3_Container_P1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(scr->ui_screen_3_Container_P1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(scr->ui_screen_3_Container_P1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    scr->ui_screen_3_Label_P1Name = lv_label_create(scr->ui_screen_3_Container_P1);
    lv_obj_set_pos(scr->ui_screen_3_Label_P1Name, 12, 18);
    lv_obj_set_size(scr->ui_screen_3_Label_P1Name, 110, 20);
    lv_label_set_text(scr->ui_screen_3_Label_P1Name, "预警值");
    lv_obj_set_style_text_align(scr->ui_screen_3_Label_P1Name, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_long_mode(scr->ui_screen_3_Label_P1Name, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_color(scr->ui_screen_3_Label_P1Name, lv_color_hex(0xE8EEF2), LV_PART_MAIN | LV_STATE_DEFAULT);
    LV_FONT_DECLARE(font_notosanscjksc_regular_14_b49ae336_fb3f);
    lv_obj_set_style_text_font(scr->ui_screen_3_Label_P1Name, &font_notosanscjksc_regular_14_b49ae336_fb3f, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_flag(scr->ui_screen_3_Label_P1Name, LV_OBJ_FLAG_IGNORE_LAYOUT);

    scr->ui_screen_3_Label_P1Value = lv_label_create(scr->ui_screen_3_Container_P1);
    lv_obj_set_pos(scr->ui_screen_3_Label_P1Value, 110, 15);
    lv_obj_set_size(scr->ui_screen_3_Label_P1Value, 170, 25);
    lv_label_set_text(scr->ui_screen_3_Label_P1Value, "1.60 µSv/h");
    lv_obj_set_style_text_align(scr->ui_screen_3_Label_P1Value, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_long_mode(scr->ui_screen_3_Label_P1Value, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_color(scr->ui_screen_3_Label_P1Value, lv_color_hex(0xEF9F27), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(scr->ui_screen_3_Label_P1Value, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
    LV_FONT_DECLARE(font_notosanscjksc_regular_18_b49ae336_fb3f);
    lv_obj_set_style_text_font(scr->ui_screen_3_Label_P1Value, &font_notosanscjksc_regular_18_b49ae336_fb3f, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_flag(scr->ui_screen_3_Label_P1Value, LV_OBJ_FLAG_IGNORE_LAYOUT);

    scr->ui_screen_3_Container_P2 = lv_obj_create(scr->obj);
    lv_obj_set_pos(scr->ui_screen_3_Container_P2, 12, 168);
    lv_obj_set_size(scr->ui_screen_3_Container_P2, 296, 56);
    lv_obj_set_scrollbar_mode(scr->ui_screen_3_Container_P2, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_color(scr->ui_screen_3_Container_P2, lv_color_hex(0x16242F), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(scr->ui_screen_3_Container_P2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(scr->ui_screen_3_Container_P2, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(scr->ui_screen_3_Container_P2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(scr->ui_screen_3_Container_P2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(scr->ui_screen_3_Container_P2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(scr->ui_screen_3_Container_P2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(scr->ui_screen_3_Container_P2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    scr->ui_screen_3_Label_P2Name = lv_label_create(scr->ui_screen_3_Container_P2);
    lv_obj_set_pos(scr->ui_screen_3_Label_P2Name, 12, 18);
    lv_obj_set_size(scr->ui_screen_3_Label_P2Name, 110, 20);
    lv_label_set_text(scr->ui_screen_3_Label_P2Name, "报警值");
    lv_obj_set_style_text_align(scr->ui_screen_3_Label_P2Name, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_long_mode(scr->ui_screen_3_Label_P2Name, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_color(scr->ui_screen_3_Label_P2Name, lv_color_hex(0xE8EEF2), LV_PART_MAIN | LV_STATE_DEFAULT);
    LV_FONT_DECLARE(font_notosanscjksc_regular_14_b49ae336_fb3f);
    lv_obj_set_style_text_font(scr->ui_screen_3_Label_P2Name, &font_notosanscjksc_regular_14_b49ae336_fb3f, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_flag(scr->ui_screen_3_Label_P2Name, LV_OBJ_FLAG_IGNORE_LAYOUT);

    scr->ui_screen_3_Label_P2Value = lv_label_create(scr->ui_screen_3_Container_P2);
    lv_obj_set_pos(scr->ui_screen_3_Label_P2Value, 110, 15);
    lv_obj_set_size(scr->ui_screen_3_Label_P2Value, 170, 25);
    lv_label_set_text(scr->ui_screen_3_Label_P2Value, "2.00 µSv/h");
    lv_obj_set_style_text_align(scr->ui_screen_3_Label_P2Value, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_label_set_long_mode(scr->ui_screen_3_Label_P2Value, LV_LABEL_LONG_WRAP);
    lv_obj_set_style_text_color(scr->ui_screen_3_Label_P2Value, lv_color_hex(0xE24B4A), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(scr->ui_screen_3_Label_P2Value, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN | LV_STATE_DEFAULT);
    LV_FONT_DECLARE(font_notosanscjksc_regular_18_b49ae336_fb3f);
    lv_obj_set_style_text_font(scr->ui_screen_3_Label_P2Value, &font_notosanscjksc_regular_18_b49ae336_fb3f, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_flag(scr->ui_screen_3_Label_P2Value, LV_OBJ_FLAG_IGNORE_LAYOUT);


    screen_3_register_events(ui);
}

void screen_3_update_language(lang_type_t lang)
{
    screen_3_t *scr = screen_3_get(&ui_manager);
    if (!scr->obj)
        return;
    aic_set_language(lang);
    (void)scr;
}

void screen_3_update_current_language(void)
{
    screen_3_update_language(aic_get_language());
}
