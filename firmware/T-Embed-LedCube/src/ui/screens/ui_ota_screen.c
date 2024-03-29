// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.0
// LVGL version: 8.2.0
// Project name: LedCubeDisplay

#include "../ui.h"

void ui_ota_screen_screen_init(void)
{
    ui_ota_screen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_ota_screen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_ota_device_name_text = lv_label_create(ui_ota_screen);
    lv_obj_set_width(ui_ota_device_name_text, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_ota_device_name_text, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_ota_device_name_text, 0);
    lv_obj_set_y(ui_ota_device_name_text, -57);
    lv_obj_set_align(ui_ota_device_name_text, LV_ALIGN_CENTER);
    lv_label_set_text(ui_ota_device_name_text, "Led Cube");
    lv_obj_set_style_text_font(ui_ota_device_name_text, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ota_text = lv_label_create(ui_ota_screen);
    lv_obj_set_width(ui_ota_text, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_ota_text, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_ota_text, 0);
    lv_obj_set_y(ui_ota_text, -28);
    lv_obj_set_align(ui_ota_text, LV_ALIGN_CENTER);
    lv_label_set_text(ui_ota_text, "Over the Air Update");
    lv_obj_set_style_text_font(ui_ota_text, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_progress_bar = lv_bar_create(ui_ota_screen);
    lv_obj_set_width(ui_progress_bar, 293);
    lv_obj_set_height(ui_progress_bar, 46);
    lv_obj_set_x(ui_progress_bar, 2);
    lv_obj_set_y(ui_progress_bar, 23);
    lv_obj_set_align(ui_progress_bar, LV_ALIGN_CENTER);

    ui_progress_text = lv_label_create(ui_progress_bar);
    lv_obj_set_width(ui_progress_text, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_progress_text, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_progress_text, LV_ALIGN_CENTER);
    lv_label_set_text(ui_progress_text, "0%");
    lv_obj_set_style_text_color(ui_progress_text, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_progress_text, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_progress_text, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

}
