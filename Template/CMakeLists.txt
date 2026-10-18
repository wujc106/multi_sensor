# =============================================================================
# CMakeLists.txt — 由 mcudeva 自动生成
#
#   [mcudeva:auto] 区：自动生成，重新生成 / 同步 .project.json 时会被整体覆盖，
#                      请勿直接修改（改动会丢失）。
#   [mcudeva:user] 区：用户自定义区，重新生成时原样保留，
#                      请把所有手写的 CMake 语句写在这些区域内。
#
# =============================================================================

# ==== [mcudeva:auto] BEGIN project (hash:6430c5c9) ====
cmake_minimum_required(VERSION 3.20)

project(Template C ASM)

set(LINKER_SCRIPT gd32f5hc_flash.ld)
# ==== [mcudeva:auto] END project ====

# ---- [mcudeva:user] BEGIN prologue — 用户自定义区，重新生成时保留，可自由修改 ----
# 可在此设置前置变量 / option()，作用于后续所有自动区
# ---- [mcudeva:user] END prologue ----

# ==== [mcudeva:auto] BEGIN flags (hash:67170a13) ====
# 编译参数
set(MCU_FLAGS "-mcpu=cortex-m33 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16")

set(CMAKE_C_FLAGS
    "${MCU_FLAGS} -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -std=gnu11"
    CACHE STRING "" FORCE)

set(CMAKE_ASM_FLAGS "${MCU_FLAGS} -x assembler-with-cpp" CACHE STRING "" FORCE)

# 各配置编译标志（按 CMAKE_BUILD_TYPE 自动叠加）
set(CMAKE_C_FLAGS_DEBUG "-O0 -g3" CACHE STRING "" FORCE)
set(CMAKE_C_FLAGS_RELEASE "-O0 -g" CACHE STRING "" FORCE)

set(CMAKE_EXE_LINKER_FLAGS
    "${MCU_FLAGS} \
     -T${LINKER_SCRIPT} \
     -Wl,--print-memory-usage \
     -Xlinker --gc-sections \
     -Wl,-Map=${PROJECT_NAME}.map \
     --specs=nano.specs \
     --specs=nosys.specs \
     -L${CMAKE_SOURCE_DIR}/ldscripts \
     -Wl,--no-warn-rwx-segments"
    CACHE STRING "" FORCE)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# ==== [mcudeva:auto] END flags ====

# ---- [mcudeva:user] BEGIN flags — 用户自定义区，重新生成时保留，可自由修改 ----
# 可在此追加编译/链接选项，例如 set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
# ---- [mcudeva:user] END flags ----

# ==== [mcudeva:auto] BEGIN definitions (hash:1083dca1) ====
# 预处理器宏定义
add_compile_definitions(
    USE_STDPERIPH_DRIVER
    SYS_NS
    GD32F5HC
    FW_DEBUG_ERR_REPORT
    GD_ECLIPSE_GCC
    LV_LVGL_H_INCLUDE_SIMPLE
    LV_DEMO_CONF_INCLUDE_SIMPLE
)
# ==== [mcudeva:auto] END definitions ====

# ---- [mcudeva:user] BEGIN definitions — 用户自定义区，重新生成时保留，可自由修改 ----
# 可在此追加宏定义，例如 add_compile_definitions(MY_FLAG=1)
# ---- [mcudeva:user] END definitions ----

# ==== [mcudeva:auto] BEGIN includes (hash:dcd66fc6) ====
# 头文件路径
set(INC_DIRS
    ${CMAKE_SOURCE_DIR}/../Firmware/CMSIS
    ${CMAKE_SOURCE_DIR}/../Utilities
    ${CMAKE_SOURCE_DIR}/../Utilities/BSP_Drive
    ${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl
    ${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/port
    ${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src
    ${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src
    ${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos
    ${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/examples
    ${CMAKE_SOURCE_DIR}/../Firmware/GD32W51x_F5HC_standard_peripheral/Include
    ${CMAKE_SOURCE_DIR}/../Firmware/CMSIS/GD/GD32W51x_F5HC/Include
    ${CMAKE_SOURCE_DIR}/../Firmware/CMSIS/GD/GD32W51x_F5HC/Source/ARM
    ${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/tick
    ${CMAKE_SOURCE_DIR}/.
    ${CMAKE_SOURCE_DIR}/GUI_APP/GD32EmbeddedUI
    ${CMAKE_SOURCE_DIR}/GUI_APP/GD32EmbeddedUI/custom
    ${CMAKE_SOURCE_DIR}/GUI_APP/GD32EmbeddedUI/generated
)
# ==== [mcudeva:auto] END includes ====

# ---- [mcudeva:user] BEGIN includes — 用户自定义区，重新生成时保留，可自由修改 ----
# 可在此追加头文件路径，例如 list(APPEND INC_DIRS ${CMAKE_SOURCE_DIR}/my_inc)
# ---- [mcudeva:user] END includes ----

# ==== [mcudeva:auto] BEGIN sources (hash:6d42260e) ====
# 源文件列表
set(SOURCES)
list(APPEND SOURCES
    "${CMAKE_SOURCE_DIR}/gd32w51x_f5hc_it.c"
    "${CMAKE_SOURCE_DIR}/main.c"
    "${CMAKE_SOURCE_DIR}/systick.c"
    "${CMAKE_SOURCE_DIR}/../Firmware/CMSIS/GD/GD32W51x_F5HC/Source/system_gd32w51x_f5hc.c"
    "${CMAKE_SOURCE_DIR}/../Firmware/CMSIS/GD/GD32W51x_F5HC/Source/gd32w51x_f5hc_err_report.c"
    "${CMAKE_SOURCE_DIR}/../Firmware/GD32W51x_F5HC_standard_peripheral/Source/gd32w51x_f5hc_adc.c"
    "${CMAKE_SOURCE_DIR}/../Firmware/GD32W51x_F5HC_standard_peripheral/Source/gd32w51x_f5hc_cau.c"
    "${CMAKE_SOURCE_DIR}/../Firmware/GD32W51x_F5HC_standard_peripheral/Source/gd32w51x_f5hc_cau_aes.c"
    "${CMAKE_SOURCE_DIR}/../Firmware/GD32W51x_F5HC_standard_peripheral/Source/gd32w51x_f5hc_cau_des.c"
    "${CMAKE_SOURCE_DIR}/../Firmware/GD32W51x_F5HC_standard_peripheral/Source/gd32w51x_f5hc_cau_tdes.c"
    "${CMAKE_SOURCE_DIR}/../Firmware/GD32W51x_F5HC_standard_peripheral/Source/gd32w51x_f5hc_crc.c"
    "${CMAKE_SOURCE_DIR}/../Firmware/GD32W51x_F5HC_standard_peripheral/Source/gd32w51x_f5hc_ctc.c"
    "${CMAKE_SOURCE_DIR}/../Firmware/GD32W51x_F5HC_standard_peripheral/Source/gd32w51x_f5hc_dbg.c"
    "${CMAKE_SOURCE_DIR}/../Firmware/GD32W51x_F5HC_standard_peripheral/Source/gd32w51x_f5hc_dci.c"
    "${CMAKE_SOURCE_DIR}/../Firmware/GD32W51x_F5HC_standard_peripheral/Source/gd32w51x_f5hc_dma.c"
    "${CMAKE_SOURCE_DIR}/../Firmware/GD32W51x_F5HC_standard_peripheral/Source/gd32w51x_f5hc_efuse.c"
    "${CMAKE_SOURCE_DIR}/../Firmware/GD32W51x_F5HC_standard_peripheral/Source/gd32w51x_f5hc_exti.c"
    "${CMAKE_SOURCE_DIR}/../Firmware/GD32W51x_F5HC_standard_peripheral/Source/gd32w51x_f5hc_fmc.c"
    "${CMAKE_SOURCE_DIR}/../Firmware/GD32W51x_F5HC_standard_peripheral/Source/gd32w51x_f5hc_fwdgt.c"
    "${CMAKE_SOURCE_DIR}/../Firmware/GD32W51x_F5HC_standard_peripheral/Source/gd32w51x_f5hc_gpio.c"
    "${CMAKE_SOURCE_DIR}/../Firmware/GD32W51x_F5HC_standard_peripheral/Source/gd32w51x_f5hc_hau.c"
    "${CMAKE_SOURCE_DIR}/../Firmware/GD32W51x_F5HC_standard_peripheral/Source/gd32w51x_f5hc_hau_sha_md5.c"
    "${CMAKE_SOURCE_DIR}/../Firmware/GD32W51x_F5HC_standard_peripheral/Source/gd32w51x_f5hc_hpdf.c"
    "${CMAKE_SOURCE_DIR}/../Firmware/GD32W51x_F5HC_standard_peripheral/Source/gd32w51x_f5hc_i2c.c"
    "${CMAKE_SOURCE_DIR}/../Firmware/GD32W51x_F5HC_standard_peripheral/Source/gd32w51x_f5hc_icache.c"
    "${CMAKE_SOURCE_DIR}/../Firmware/GD32W51x_F5HC_standard_peripheral/Source/gd32w51x_f5hc_misc.c"
    "${CMAKE_SOURCE_DIR}/../Firmware/GD32W51x_F5HC_standard_peripheral/Source/gd32w51x_f5hc_pkcau.c"
    "${CMAKE_SOURCE_DIR}/../Firmware/GD32W51x_F5HC_standard_peripheral/Source/gd32w51x_f5hc_pmu.c"
    "${CMAKE_SOURCE_DIR}/../Firmware/GD32W51x_F5HC_standard_peripheral/Source/gd32w51x_f5hc_qspi.c"
    "${CMAKE_SOURCE_DIR}/../Firmware/GD32W51x_F5HC_standard_peripheral/Source/gd32w51x_f5hc_rcu.c"
    "${CMAKE_SOURCE_DIR}/../Firmware/GD32W51x_F5HC_standard_peripheral/Source/gd32w51x_f5hc_rtc.c"
    "${CMAKE_SOURCE_DIR}/../Firmware/GD32W51x_F5HC_standard_peripheral/Source/gd32w51x_f5hc_sdio.c"
    "${CMAKE_SOURCE_DIR}/../Firmware/GD32W51x_F5HC_standard_peripheral/Source/gd32w51x_f5hc_spi.c"
    "${CMAKE_SOURCE_DIR}/../Firmware/GD32W51x_F5HC_standard_peripheral/Source/gd32w51x_f5hc_sqpi.c"
    "${CMAKE_SOURCE_DIR}/../Firmware/GD32W51x_F5HC_standard_peripheral/Source/gd32w51x_f5hc_syscfg.c"
    "${CMAKE_SOURCE_DIR}/../Firmware/GD32W51x_F5HC_standard_peripheral/Source/gd32w51x_f5hc_timer.c"
    "${CMAKE_SOURCE_DIR}/../Firmware/GD32W51x_F5HC_standard_peripheral/Source/gd32w51x_f5hc_trng.c"
    "${CMAKE_SOURCE_DIR}/../Firmware/GD32W51x_F5HC_standard_peripheral/Source/gd32w51x_f5hc_tsi.c"
    "${CMAKE_SOURCE_DIR}/../Firmware/GD32W51x_F5HC_standard_peripheral/Source/gd32w51x_f5hc_tzpcu.c"
    "${CMAKE_SOURCE_DIR}/../Firmware/GD32W51x_F5HC_standard_peripheral/Source/gd32w51x_f5hc_usart.c"
    "${CMAKE_SOURCE_DIR}/../Firmware/GD32W51x_F5HC_standard_peripheral/Source/gd32w51x_f5hc_wwdgt.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/BSP_Drive/lcd_driver.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/BSP_Drive/gd32f5hcr_eval.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/core/lv_disp.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/core/lv_event.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/core/lv_group.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/core/lv_indev.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/core/lv_indev_scroll.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/core/lv_obj.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/core/lv_obj_class.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/core/lv_obj_draw.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/core/lv_obj_pos.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/core/lv_obj_scroll.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/core/lv_obj_style.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/core/lv_obj_style_gen.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/core/lv_obj_tree.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/core/lv_refr.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/core/lv_theme.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/draw/lv_draw.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/draw/lv_draw_arc.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/draw/lv_draw_img.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/draw/lv_draw_label.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/draw/lv_draw_layer.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/draw/lv_draw_line.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/draw/lv_draw_mask.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/draw/lv_draw_rect.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/draw/lv_draw_transform.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/draw/lv_draw_triangle.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/draw/lv_img_buf.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/draw/lv_img_cache.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/draw/lv_img_decoder.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/draw/sw/lv_draw_sw.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/draw/sw/lv_draw_sw_arc.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/draw/sw/lv_draw_sw_blend.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/draw/sw/lv_draw_sw_dither.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/draw/sw/lv_draw_sw_gradient.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/draw/sw/lv_draw_sw_img.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/draw/sw/lv_draw_sw_layer.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/draw/sw/lv_draw_sw_letter.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/draw/sw/lv_draw_sw_line.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/draw/sw/lv_draw_sw_polygon.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/draw/sw/lv_draw_sw_rect.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/draw/sw/lv_draw_sw_transform.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/extra/lv_extra.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/extra/layouts/flex/lv_flex.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/extra/layouts/grid/lv_grid.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/extra/libs/bmp/lv_bmp.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/extra/libs/ffmpeg/lv_ffmpeg.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/extra/libs/freetype/lv_freetype.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/extra/libs/fsdrv/lv_fs_fatfs.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/extra/libs/fsdrv/lv_fs_littlefs.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/extra/libs/fsdrv/lv_fs_posix.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/extra/libs/fsdrv/lv_fs_stdio.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/extra/libs/fsdrv/lv_fs_win32.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/extra/libs/gif/gifdec.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/extra/libs/gif/lv_gif.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/extra/libs/png/lodepng.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/extra/libs/png/lv_png.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/extra/libs/qrcode/lv_qrcode.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/extra/libs/qrcode/qrcodegen.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/extra/libs/rlottie/lv_rlottie.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/extra/libs/sjpg/lv_sjpg.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/extra/libs/sjpg/tjpgd.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/extra/libs/tiny_ttf/lv_tiny_ttf.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/extra/others/fragment/lv_fragment.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/extra/others/fragment/lv_fragment_manager.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/extra/others/gridnav/lv_gridnav.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/extra/others/ime/lv_ime_pinyin.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/extra/others/imgfont/lv_imgfont.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/extra/others/monkey/lv_monkey.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/extra/others/msg/lv_msg.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/extra/others/snapshot/lv_snapshot.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/extra/themes/basic/lv_theme_basic.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/extra/themes/default/lv_theme_default.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/extra/themes/mono/lv_theme_mono.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/extra/widgets/animimg/lv_animimg.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/extra/widgets/calendar/lv_calendar.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/extra/widgets/calendar/lv_calendar_header_arrow.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/extra/widgets/calendar/lv_calendar_header_dropdown.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/extra/widgets/chart/lv_chart.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/extra/widgets/colorwheel/lv_colorwheel.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/extra/widgets/imgbtn/lv_imgbtn.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/extra/widgets/keyboard/lv_keyboard.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/extra/widgets/led/lv_led.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/extra/widgets/list/lv_list.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/extra/widgets/menu/lv_menu.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/extra/widgets/meter/lv_meter.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/extra/widgets/msgbox/lv_msgbox.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/extra/widgets/span/lv_span.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/extra/widgets/spinbox/lv_spinbox.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/extra/widgets/spinner/lv_spinner.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/extra/widgets/tabview/lv_tabview.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/extra/widgets/tileview/lv_tileview.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/extra/widgets/win/lv_win.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/font/lv_font.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/font/lv_font_dejavu_16_persian_hebrew.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/font/lv_font_fmt_txt.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/font/lv_font_loader.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/font/lv_font_montserrat_8.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/font/lv_font_montserrat_10.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/font/lv_font_montserrat_12.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/font/lv_font_montserrat_12_subpx.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/font/lv_font_montserrat_14.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/font/lv_font_montserrat_16.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/font/lv_font_montserrat_18.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/font/lv_font_montserrat_20.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/font/lv_font_montserrat_22.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/font/lv_font_montserrat_24.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/font/lv_font_montserrat_26.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/font/lv_font_montserrat_28.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/font/lv_font_montserrat_28_compressed.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/font/lv_font_montserrat_30.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/font/lv_font_montserrat_32.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/font/lv_font_montserrat_34.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/font/lv_font_montserrat_36.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/font/lv_font_montserrat_38.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/font/lv_font_montserrat_40.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/font/lv_font_montserrat_42.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/font/lv_font_montserrat_44.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/font/lv_font_montserrat_46.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/font/lv_font_montserrat_48.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/font/lv_font_simsun_16_cjk.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/font/lv_font_unscii_8.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/font/lv_font_unscii_16.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/hal/lv_hal_disp.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/hal/lv_hal_indev.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/hal/lv_hal_tick.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/misc/lv_anim.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/misc/lv_anim_timeline.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/misc/lv_area.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/misc/lv_async.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/misc/lv_bidi.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/misc/lv_color.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/misc/lv_fs.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/misc/lv_gc.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/misc/lv_ll.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/misc/lv_log.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/misc/lv_lru.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/misc/lv_math.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/misc/lv_mem.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/misc/lv_printf.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/misc/lv_style.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/misc/lv_style_gen.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/misc/lv_templ.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/misc/lv_timer.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/misc/lv_tlsf.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/misc/lv_txt.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/misc/lv_txt_ap.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/misc/lv_utils.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/widgets/lv_arc.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/widgets/lv_bar.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/widgets/lv_btn.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/widgets/lv_btnmatrix.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/widgets/lv_canvas.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/widgets/lv_checkbox.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/widgets/lv_dropdown.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/widgets/lv_img.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/widgets/lv_label.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/widgets/lv_line.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/widgets/lv_objx_templ.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/widgets/lv_roller.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/widgets/lv_slider.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/widgets/lv_switch.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/widgets/lv_table.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/src/widgets/lv_textarea.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/port/lv_port_disp.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/port/lv_port_indev.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/benchmark/lv_demo_benchmark.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/benchmark/assets/img_benchmark_cogwheel_alpha16.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/benchmark/assets/img_benchmark_cogwheel_argb.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/benchmark/assets/img_benchmark_cogwheel_chroma_keyed.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/benchmark/assets/img_benchmark_cogwheel_indexed16.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/benchmark/assets/img_benchmark_cogwheel_rgb.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/benchmark/assets/img_benchmark_cogwheel_rgb565a8.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/benchmark/assets/lv_font_bechmark_montserrat_12_compr_az.c.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/benchmark/assets/lv_font_bechmark_montserrat_16_compr_az.c.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/benchmark/assets/lv_font_bechmark_montserrat_28_compr_az.c.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/widgets/lv_demo_widgets.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/widgets/assets/img_clothes.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/widgets/assets/img_demo_widgets_avatar.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/widgets/assets/img_lvgl_logo.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/music/lv_demo_music.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/music/lv_demo_music_list.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/music/lv_demo_music_main.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/music/assets/img_lv_demo_music_btn_corner_large.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/music/assets/img_lv_demo_music_btn_list_pause.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/music/assets/img_lv_demo_music_btn_list_pause_large.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/music/assets/img_lv_demo_music_btn_list_play.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/music/assets/img_lv_demo_music_btn_list_play_large.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/music/assets/img_lv_demo_music_btn_loop.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/music/assets/img_lv_demo_music_btn_loop_large.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/music/assets/img_lv_demo_music_btn_next.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/music/assets/img_lv_demo_music_btn_next_large.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/music/assets/img_lv_demo_music_btn_pause.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/music/assets/img_lv_demo_music_btn_pause_large.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/music/assets/img_lv_demo_music_btn_play.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/music/assets/img_lv_demo_music_btn_play_large.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/music/assets/img_lv_demo_music_btn_prev.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/music/assets/img_lv_demo_music_btn_prev_large.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/music/assets/img_lv_demo_music_btn_rnd.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/music/assets/img_lv_demo_music_btn_rnd_large.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/music/assets/img_lv_demo_music_corner_left.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/music/assets/img_lv_demo_music_corner_left_large.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/music/assets/img_lv_demo_music_corner_right.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/music/assets/img_lv_demo_music_corner_right_large.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/music/assets/img_lv_demo_music_cover_1.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/music/assets/img_lv_demo_music_cover_1_large.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/music/assets/img_lv_demo_music_cover_2.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/music/assets/img_lv_demo_music_cover_2_large.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/music/assets/img_lv_demo_music_cover_3.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/music/assets/img_lv_demo_music_cover_3_large.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/music/assets/img_lv_demo_music_icon_1.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/music/assets/img_lv_demo_music_icon_1_large.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/music/assets/img_lv_demo_music_icon_2.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/music/assets/img_lv_demo_music_icon_2_large.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/music/assets/img_lv_demo_music_icon_3.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/music/assets/img_lv_demo_music_icon_3_large.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/music/assets/img_lv_demo_music_icon_4.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/music/assets/img_lv_demo_music_icon_4_large.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/music/assets/img_lv_demo_music_list_border.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/music/assets/img_lv_demo_music_list_border_large.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/music/assets/img_lv_demo_music_logo.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/music/assets/img_lv_demo_music_slider_knob.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/music/assets/img_lv_demo_music_slider_knob_large.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/music/assets/img_lv_demo_music_wave_bottom.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/music/assets/img_lv_demo_music_wave_bottom_large.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/music/assets/img_lv_demo_music_wave_top.c"
    "${CMAKE_SOURCE_DIR}/../Utilities/Third_Party/lvgl/lvgl_src/demos/music/assets/img_lv_demo_music_wave_top_large.c"
    "${CMAKE_SOURCE_DIR}/GUI_APP/GD32EmbeddedUI/custom/gui_app.c"
    "${CMAKE_SOURCE_DIR}/GUI_APP/GD32EmbeddedUI/generated/image/img_bluetoothon_fit_36x34.c"
    "${CMAKE_SOURCE_DIR}/GUI_APP/GD32EmbeddedUI/generated/image/img_brightness_fit_36x34.c"
    "${CMAKE_SOURCE_DIR}/GUI_APP/GD32EmbeddedUI/generated/image/img_clock_fit_36x34.c"
    "${CMAKE_SOURCE_DIR}/GUI_APP/GD32EmbeddedUI/generated/image/img_wifi_fit_36x34.c"
    "${CMAKE_SOURCE_DIR}/GUI_APP/GD32EmbeddedUI/generated/lang/aic_lang.c"
    "${CMAKE_SOURCE_DIR}/GUI_APP/GD32EmbeddedUI/generated/lang/font_list.c"
    "${CMAKE_SOURCE_DIR}/GUI_APP/GD32EmbeddedUI/generated/screens/screen/screen.c"
    "${CMAKE_SOURCE_DIR}/GUI_APP/GD32EmbeddedUI/generated/screens/screen/screen_event.c"
    "${CMAKE_SOURCE_DIR}/GUI_APP/GD32EmbeddedUI/generated/screens/screen1/screen_1.c"
    "${CMAKE_SOURCE_DIR}/GUI_APP/GD32EmbeddedUI/generated/screens/screen1/screen_1_event.c"
    "${CMAKE_SOURCE_DIR}/GUI_APP/GD32EmbeddedUI/generated/screens/screen2/screen_2.c"
    "${CMAKE_SOURCE_DIR}/GUI_APP/GD32EmbeddedUI/generated/screens/screen2/screen_2_event.c"
    "${CMAKE_SOURCE_DIR}/GUI_APP/GD32EmbeddedUI/generated/screens/screen3/screen_3.c"
    "${CMAKE_SOURCE_DIR}/GUI_APP/GD32EmbeddedUI/generated/screens/screen3/screen_3_event.c"
    "${CMAKE_SOURCE_DIR}/GUI_APP/GD32EmbeddedUI/generated/screens/screen4/screen_4.c"
    "${CMAKE_SOURCE_DIR}/GUI_APP/GD32EmbeddedUI/generated/screens/screen4/screen_4_event.c"
    "${CMAKE_SOURCE_DIR}/GUI_APP/GD32EmbeddedUI/generated/screens/screen5/screen_5.c"
    "${CMAKE_SOURCE_DIR}/GUI_APP/GD32EmbeddedUI/generated/screens/screen5/screen_5_event.c"
    "${CMAKE_SOURCE_DIR}/GUI_APP/GD32EmbeddedUI/generated/screens/screen6/screen_6.c"
    "${CMAKE_SOURCE_DIR}/GUI_APP/GD32EmbeddedUI/generated/screens/screen6/screen_6_event.c"
    "${CMAKE_SOURCE_DIR}/GUI_APP/GD32EmbeddedUI/generated/screens/event.c"
    "${CMAKE_SOURCE_DIR}/GUI_APP/GD32EmbeddedUI/generated/theme/theme.c"
    "${CMAKE_SOURCE_DIR}/GUI_APP/GD32EmbeddedUI/generated/ui_init.c"
    "${CMAKE_SOURCE_DIR}/GUI_APP/GD32EmbeddedUI/generated/ui_util.c"
    "${CMAKE_SOURCE_DIR}/GUI_APP/GD32EmbeddedUI/generated/image/gif_wave.c"
    "${CMAKE_SOURCE_DIR}/GUI_APP/GD32EmbeddedUI/generated/image/img_20260805_154005_fit_78x102.c"
    "${CMAKE_SOURCE_DIR}/GUI_APP/GD32EmbeddedUI/generated/image/img_20260901_191444_fit_107x89.c"
    "${CMAKE_SOURCE_DIR}/GUI_APP/GD32EmbeddedUI/generated/screens/screen7/screen_7.c"
    "${CMAKE_SOURCE_DIR}/GUI_APP/GD32EmbeddedUI/generated/screens/screen7/screen_7_event.c"
    "${CMAKE_SOURCE_DIR}/GUI_APP/GD32EmbeddedUI/generated/font/font_notosanscjksc_regular_14_b49ae336.c"
    "${CMAKE_SOURCE_DIR}/GUI_APP/GD32EmbeddedUI/generated/font/font_notosanscjksc_regular_14_b49ae336_fb3f.c"
    "${CMAKE_SOURCE_DIR}/GUI_APP/GD32EmbeddedUI/generated/font/font_notosanscjksc_regular_16_b49ae336.c"
    "${CMAKE_SOURCE_DIR}/GUI_APP/GD32EmbeddedUI/generated/font/font_notosanscjksc_regular_16_b49ae336_fb3f.c"
    "${CMAKE_SOURCE_DIR}/GUI_APP/GD32EmbeddedUI/generated/image/img_balloon_fit_30x26.c"
    "${CMAKE_SOURCE_DIR}/GUI_APP/GD32EmbeddedUI/generated/image/img_drawing_fit_30x26.c"
    "${CMAKE_SOURCE_DIR}/GUI_APP/GD32EmbeddedUI/generated/image/img_fireworks_fit_30x26.c"
    "${CMAKE_SOURCE_DIR}/GUI_APP/GD32EmbeddedUI/generated/image/img_rocket_fit_30x26.c"
    "${CMAKE_SOURCE_DIR}/GUI_APP/GD32EmbeddedUI/generated/image/img_shape_fit_30x26.c"
    "${CMAKE_SOURCE_DIR}/GUI_APP/GD32EmbeddedUI/generated/image/img_slide_fit_30x26.c"
    "${CMAKE_SOURCE_DIR}/GUI_APP/GD32EmbeddedUI/generated/image/img_tv_fit_30x26.c"
    "${CMAKE_SOURCE_DIR}/GUI_APP/GD32EmbeddedUI/generated/image/img_warning_fit_30x26.c"
    "${CMAKE_SOURCE_DIR}/gcc_startup/startup_gd32f5hc.S"
)

# ==== [mcudeva:auto] END sources ====

# ---- [mcudeva:user] BEGIN sources — 用户自定义区，重新生成时保留，可自由修改 ----
# 可在此增删源文件，例如 list(APPEND SOURCES ${CMAKE_SOURCE_DIR}/my/extra.c)
# ---- [mcudeva:user] END sources ----

# ==== [mcudeva:auto] BEGIN target (hash:57a9b457) ====
set(TARGET_ELF ${PROJECT_NAME}.elf)

add_executable(${TARGET_ELF}
    ${SOURCES}
)

target_include_directories(${TARGET_ELF} PRIVATE ${INC_DIRS})

# ==== [mcudeva:auto] END target ====

# ---- [mcudeva:user] BEGIN target — 用户自定义区，重新生成时保留，可自由修改 ----
# 可在此写 target_* 命令，例如 target_link_libraries(${TARGET_ELF} PRIVATE m)
# ---- [mcudeva:user] END target ----

# ==== [mcudeva:auto] BEGIN post-build (hash:7d6fc976) ====
# 构建后处理
set(TARGET_HEX ${PROJECT_NAME}.hex)
set(TARGET_BIN ${PROJECT_NAME}.bin)
set(TARGET_LST ${PROJECT_NAME}.lst)

add_custom_command(TARGET ${TARGET_ELF} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex   $<TARGET_FILE:${TARGET_ELF}> ${TARGET_HEX}
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${TARGET_ELF}> ${TARGET_BIN}
    COMMAND ${CMAKE_OBJDUMP} --source --all-headers --demangle --line-numbers --wide
            $<TARGET_FILE:${TARGET_ELF}> > ${TARGET_LST}
    COMMAND ${CMAKE_SIZE} --format=berkeley $<TARGET_FILE:${TARGET_ELF}>
    COMMENT "Generating ${TARGET_HEX}, ${TARGET_BIN}, ${TARGET_LST}"
    BYPRODUCTS ${TARGET_HEX} ${TARGET_BIN} ${TARGET_LST}
)
# ==== [mcudeva:auto] END post-build ====

# ---- [mcudeva:user] BEGIN epilogue — 用户自定义区，重新生成时保留，可自由修改 ----
# 可在此追加自定义 target / include(user.cmake) 等收尾语句
# ---- [mcudeva:user] END epilogue ----
