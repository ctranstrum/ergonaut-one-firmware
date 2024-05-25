/*
 * Copyright (c) 2020 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#include <zmk/display.h>
#include <zmk/display/widgets/kb_logo.h>
#include <lvgl.h>

#ifndef LV_ATTRIBUTE_MEM_ALIGN
#define LV_ATTRIBUTE_MEM_ALIGN
#endif

#ifndef LV_ATTRIBUTE_IMG_SPLITKB
#define LV_ATTRIBUTE_IMG_SPLITKB
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_SPLITKB uint8_t splitkb_map[] = {
  0xff, 0xff, 0xff, 0xff, 	/*Color of index 0*/
  0x00, 0x00, 0x00, 0xff, 	/*Color of index 1*/

  0xc0, 0x00, 0xc0, 0x00, 0xc0, 0x40,
  0xc0, 0xc0, 0xc0, 0xc0, 0xc6, 0xd8,
  0xcc, 0xfc, 0xd8, 0xee, 0xf0, 0xc6,
  0xe0, 0xee, 0xcc, 0x7c, 0x86, 0x38,
};

const lv_img_dsc_t splitkb_logo = {
  .header.cf = LV_IMG_CF_INDEXED_1BIT,
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = 14,
  .header.h = 12,
  .data_size = 32,
  .data = splitkb_map,
};

LV_IMG_DECLARE(splitkb_logo);

#ifndef LV_ATTRIBUTE_IMG_TOTEM
#define LV_ATTRIBUTE_IMG_TOTEM
#endif

const LV_ATTRIBUTE_MEM_ALIGN LV_ATTRIBUTE_LARGE_CONST LV_ATTRIBUTE_IMG_TOTEM uint8_t totem_map[] = {
  0xff, 0xff, 0xff, 0xff, 	/*Color of index 0*/
  0x00, 0x00, 0x00, 0xff, 	/*Color of index 1*/

  0x70, 0x20, 0x26, 0x29, 0x29, 0x09, 0xe6,
  0x40, 0x57, 0x50, 0x5c, 0x10, 0x17, 0x00,
  0x7c, 0x54, 0x54, 0x54, 0x54, 0x00, 0xf8,
};

const lv_img_dsc_t totem_logo = {
  .header.cf = LV_IMG_CF_INDEXED_1BIT,
  .header.always_zero = 0,
  .header.reserved = 0,
  .header.w = 8,
  .header.h = 21,
  .data_size = 29,
  .data = totem_map,
};

LV_IMG_DECLARE(totem_logo);

static sys_slist_t widgets = SYS_SLIST_STATIC_INIT(&widgets);

int zmk_widget_kb_logo_init(struct zmk_widget_kb_logo *widget, lv_obj_t *parent) {
    widget->obj = lv_label_create(parent);

    lv_obj_set_size(widget->obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);

    lv_obj_t *logo = lv_img_create(widget->obj);
    lv_obj_align(logo, LV_ALIGN_TOP_LEFT, 1, 1);
    lv_img_set_src(logo, &splitkb_logo);

    sys_slist_append(&widgets, &widget->node);

    widget_kb_logo_init();
    return 0;
}

lv_obj_t *zmk_widget_kb_logo_obj(struct zmk_widget_kb_logo *widget) {
    return widget->obj;
}
