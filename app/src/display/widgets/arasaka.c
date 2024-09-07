/*
 * Copyright (c) 2024 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#include <zmk/display.h>
#include <zmk/display/widgets/arasaka.h>
#include <zmk/event_manager.h>

#if IS_ENABLED(CONFIG_ZMK_DISPLAY_WORK_QUEUE_DEDICATED)
#error "Arasaka logo widget only works with the system work queue currently"
#endif

static sys_slist_t widgets = SYS_SLIST_STATIC_INIT(&widgets);

LV_IMG_DECLARE(arasaka_1);
LV_IMG_DECLARE(arasaka_2);
LV_IMG_DECLARE(arasaka_3);
LV_IMG_DECLARE(arasaka_4);
LV_IMG_DECLARE(arasaka_5);
LV_IMG_DECLARE(arasaka_6);
LV_IMG_DECLARE(arasaka_7);
LV_IMG_DECLARE(arasaka_8);
LV_IMG_DECLARE(arasaka_9);
LV_IMG_DECLARE(arasaka_10);
LV_IMG_DECLARE(arasaka_11);
LV_IMG_DECLARE(arasaka_12);
LV_IMG_DECLARE(arasaka_13);
LV_IMG_DECLARE(arasaka_14);
LV_IMG_DECLARE(arasaka_15);
LV_IMG_DECLARE(arasaka_16);
LV_IMG_DECLARE(arasaka_17);
LV_IMG_DECLARE(arasaka_18);
LV_IMG_DECLARE(arasaka_19);

const void *images[] = {
    // arasaka_logo [0-10]
    &arasaka_1,
    &arasaka_2,
    &arasaka_3,
    &arasaka_4,
    &arasaka_5,
    &arasaka_6,
    &arasaka_7,
    &arasaka_8,
    &arasaka_9,
    &arasaka_10,
    &arasaka_11,
    // qr_code [11-18]
    &arasaka_19,
    &arasaka_18,
    &arasaka_17,
    &arasaka_16,
    &arasaka_15,
    &arasaka_14,
    &arasaka_13,
    &arasaka_12,
};

void set_img_src(void *var, int32_t val) {
    lv_obj_t *img = (lv_obj_t *)var;
    lv_img_set_src(img, images[val]);
}

void arasaka_anim_run_glitch(struct zmk_widget_arasaka *widget) {
    lv_anim_set_values(&widget->anim, 0, 10);
    lv_anim_set_path_cb(&widget->anim, lv_anim_path_bounce);
    lv_anim_set_time(&widget->anim, 500);

    lv_anim_start(&widget->anim);
}

void arasaka_anim_run_idle_logo(struct zmk_widget_arasaka *widget) {
    lv_anim_set_values(&widget->anim, 10, 10);
    lv_anim_set_path_cb(&widget->anim, lv_anim_path_linear);
    lv_anim_set_time(&widget->anim, 5000);

    lv_anim_start(&widget->anim);
}

void arasaka_anim_run_qr_code_glitch(struct zmk_widget_arasaka *widget) {
    lv_anim_set_values(&widget->anim, 11, 18);
    lv_anim_set_path_cb(&widget->anim, lv_anim_path_bounce);
    lv_anim_set_time(&widget->anim, 500);

    lv_anim_start(&widget->anim);
}

void arasaka_anim_run_qr_code_idle(struct zmk_widget_arasaka *widget) {
    lv_anim_set_values(&widget->anim, 18, 18);
    lv_anim_set_path_cb(&widget->anim, lv_anim_path_linear);
    lv_anim_set_time(&widget->anim, 5000);

    lv_anim_start(&widget->anim);
}

void arasaka_anim_on_finish(lv_anim_t *a) {
    struct zmk_widget_arasaka *widget = (struct zmk_widget_arasaka *)lv_anim_get_user_data(a);

    widget->step = (widget->step + 1) % 4;

    if (widget->step == 0) {
        arasaka_anim_run_glitch(widget);
    } else if (widget->step == 1) {
        arasaka_anim_run_idle_logo(widget);
    } else if (widget->step == 2) {
        arasaka_anim_run_qr_code_glitch(widget);
    } else if (widget->step == 3) {
        arasaka_anim_run_qr_code_idle(widget);
    }
}

int zmk_widget_arasaka_init(struct zmk_widget_arasaka *widget, lv_obj_t *parent) {
    widget->step = 0;

    widget->obj = lv_img_create(parent);
    lv_obj_align(widget->obj, LV_ALIGN_CENTER, 0, 0);

    lv_anim_init(&widget->anim);
    lv_anim_set_var(&widget->anim, widget->obj);
    lv_anim_set_exec_cb(&widget->anim, set_img_src);
    lv_anim_set_path_cb(&widget->anim, lv_anim_path_linear);
    lv_anim_set_user_data(&widget->anim, widget);
    lv_anim_set_deleted_cb(&widget->anim, arasaka_anim_on_finish);

    arasaka_anim_on_finish(&widget->anim);

    sys_slist_append(&widgets, &widget->node);

    return 0;
}

lv_obj_t *zmk_widget_arasaka_obj(struct zmk_widget_arasaka *widget) { return widget->obj; }
