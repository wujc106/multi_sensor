/*!
    \file    ui_objects.h
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

#ifndef UI_OBJECTS_H
#define UI_OBJECTS_H

#include "lvgl.h"
#include "lang/aic_lang.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    lv_obj_t *obj;
    lv_obj_t *ui_screen_Label_Title;
    lv_obj_t *ui_screen_Label_Time;
    lv_obj_t *ui_screen_Label_Status;
    lv_obj_t *ui_screen_Arc_Value;
    lv_obj_t *ui_screen_Label_Value;
    lv_obj_t *ui_screen_Label_Unit;
    lv_obj_t *ui_screen_Label_Channel;
    lv_obj_t *ui_screen_Label_TempName_Tile;
    lv_obj_t *ui_screen_Label_TempName;
    lv_obj_t *ui_screen_Label_TempValue;
    lv_obj_t *ui_screen_Label_TempUnit;
    lv_obj_t *ui_screen_Label_HumName_Tile;
    lv_obj_t *ui_screen_Label_HumName;
    lv_obj_t *ui_screen_Label_HumValue;
    lv_obj_t *ui_screen_Label_HumUnit;
    lv_obj_t *ui_screen_Label_DoseName_Tile;
    lv_obj_t *ui_screen_Label_DoseName;
    lv_obj_t *ui_screen_Label_DoseValue;
    lv_obj_t *ui_screen_Label_DoseUnit;
    lv_obj_t *ui_screen_Label_BatName_Tile;
    lv_obj_t *ui_screen_Label_BatName;
    lv_obj_t *ui_screen_Label_BatValue;
    lv_obj_t *ui_screen_Label_BatUnit;

} screen_t;

typedef struct {
    lv_obj_t *obj;
    lv_obj_t *ui_screen_1_Label_Title;
    lv_obj_t *ui_screen_1_Label_Time;
    lv_obj_t *ui_screen_1_Btn_Curve;
    lv_obj_t *ui_screen_1_Btn_Settings;
    lv_obj_t *ui_screen_1_Btn_State;
    lv_obj_t *ui_screen_1_Btn_Info;

} screen_1_t;

typedef struct {
    lv_obj_t *obj;
    lv_obj_t *ui_screen_2_Label_Title;
    lv_obj_t *ui_screen_2_Label_Time;
    lv_obj_t *ui_screen_2_Label_Channel;
    lv_obj_t *ui_screen_2_Chart_1;
    lv_obj_t *ui_screen_2_Label_Stat;

} screen_2_t;

typedef struct {
    lv_obj_t *obj;
    lv_obj_t *ui_screen_3_Label_Title;
    lv_obj_t *ui_screen_3_Label_Time;
    lv_obj_t *ui_screen_3_Container_Channel;
    lv_obj_t *ui_screen_3_Label_ChannelName;
    lv_obj_t *ui_screen_3_Label_ChannelValue;
    lv_obj_t *ui_screen_3_Container_P1;
    lv_obj_t *ui_screen_3_Label_P1Name;
    lv_obj_t *ui_screen_3_Label_P1Value;
    lv_obj_t *ui_screen_3_Container_P2;
    lv_obj_t *ui_screen_3_Label_P2Name;
    lv_obj_t *ui_screen_3_Label_P2Value;

} screen_3_t;

typedef struct {
    lv_obj_t *obj;
    lv_obj_t *ui_screen_4_Label_Title;
    lv_obj_t *ui_screen_4_Label_Time;
    lv_obj_t *ui_screen_4_Btn_Standby;
    lv_obj_t *ui_screen_4_Btn_Running;
    lv_obj_t *ui_screen_4_Btn_PowerOff;
    lv_obj_t *ui_screen_4_Label_CurrentTag;

} screen_4_t;

typedef struct {
    lv_obj_t *obj;
    lv_obj_t *ui_screen_5_Label_Title;
    lv_obj_t *ui_screen_5_Label_Time;
    lv_obj_t *ui_screen_5_RowName_38;
    lv_obj_t *ui_screen_5_Label_ModelValue;
    lv_obj_t *ui_screen_5_RowName_70;
    lv_obj_t *ui_screen_5_Label_SwValue;
    lv_obj_t *ui_screen_5_RowName_102;
    lv_obj_t *ui_screen_5_Label_HwValue;
    lv_obj_t *ui_screen_5_RowName_134;
    lv_obj_t *ui_screen_5_Label_SensorValue;
    lv_obj_t *ui_screen_5_RowName_166;
    lv_obj_t *ui_screen_5_Label_SnValue;
    lv_obj_t *ui_screen_5_RowName_198;
    lv_obj_t *ui_screen_5_Label_RunValue;

} screen_5_t;

typedef struct {
    bool auto_del;
    screen_t screen;
    screen_1_t screen_1;
    screen_2_t screen_2;
    screen_3_t screen_3;
    screen_4_t screen_4;
    screen_5_t screen_5;
} ui_manager_t;

static inline screen_t *screen_get(ui_manager_t *ui)
{
    return &ui->screen;
}

static inline screen_1_t *screen_1_get(ui_manager_t *ui)
{
    return &ui->screen_1;
}

static inline screen_2_t *screen_2_get(ui_manager_t *ui)
{
    return &ui->screen_2;
}

static inline screen_3_t *screen_3_get(ui_manager_t *ui)
{
    return &ui->screen_3;
}

static inline screen_4_t *screen_4_get(ui_manager_t *ui)
{
    return &ui->screen_4;
}

static inline screen_5_t *screen_5_get(ui_manager_t *ui)
{
    return &ui->screen_5;
}

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif // UI_OBJECTS_H
