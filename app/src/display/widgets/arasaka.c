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

#define ARASAKA_IDLE_GLITCH_CHANCE 90

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
LV_IMG_DECLARE(arasaka_info_0);
LV_IMG_DECLARE(arasaka_info_1);
LV_IMG_DECLARE(arasaka_info_2);
LV_IMG_DECLARE(arasaka_info_3);
LV_IMG_DECLARE(arasaka_info_4);
LV_IMG_DECLARE(arasaka_info_5);
LV_IMG_DECLARE(arasaka_info_6);
LV_IMG_DECLARE(arasaka_info_7);
LV_IMG_DECLARE(arasaka_info_8);
LV_IMG_DECLARE(arasaka_info_9);
LV_IMG_DECLARE(arasaka_info_10);
LV_IMG_DECLARE(arasaka_info_11);
LV_IMG_DECLARE(arasaka_info_12);
LV_IMG_DECLARE(arasaka_info_13);
LV_IMG_DECLARE(arasaka_info_14);
LV_IMG_DECLARE(arasaka_info_15);
LV_IMG_DECLARE(arasaka_info_16);
LV_IMG_DECLARE(arasaka_info_17);
LV_IMG_DECLARE(arasaka_info_18);
LV_IMG_DECLARE(arasaka_info_19);
LV_IMG_DECLARE(arasaka_info_20);
LV_IMG_DECLARE(arasaka_info_21);
LV_IMG_DECLARE(arasaka_info_22);
LV_IMG_DECLARE(arasaka_info_23);
LV_IMG_DECLARE(arasaka_info_24);
LV_IMG_DECLARE(arasaka_info_25);
LV_IMG_DECLARE(arasaka_info_26);
LV_IMG_DECLARE(arasaka_info_27);
LV_IMG_DECLARE(arasaka_info_28);
LV_IMG_DECLARE(arasaka_info_29);
LV_IMG_DECLARE(arasaka_info_30);
LV_IMG_DECLARE(arasaka_info_31);
LV_IMG_DECLARE(arasaka_info_32);
LV_IMG_DECLARE(arasaka_info_33);
LV_IMG_DECLARE(arasaka_info_34);
LV_IMG_DECLARE(arasaka_info_35);
LV_IMG_DECLARE(arasaka_info_36);
LV_IMG_DECLARE(arasaka_info_37);
LV_IMG_DECLARE(arasaka_info_38);
LV_IMG_DECLARE(arasaka_info_39);
LV_IMG_DECLARE(arasaka_info_40);
LV_IMG_DECLARE(arasaka_info_41);
LV_IMG_DECLARE(arasaka_info_42);
LV_IMG_DECLARE(arasaka_info_43);
LV_IMG_DECLARE(arasaka_info_44);
LV_IMG_DECLARE(arasaka_info_45);
LV_IMG_DECLARE(arasaka_info_46);
LV_IMG_DECLARE(arasaka_info_47);
LV_IMG_DECLARE(arasaka_info_48);
LV_IMG_DECLARE(arasaka_info_49);

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
    // arasaka_info [19-69]
    &arasaka_info_0,
    &arasaka_info_1,
    &arasaka_info_2,
    &arasaka_info_3,
    &arasaka_info_4,
    &arasaka_info_5,
    &arasaka_info_6,
    &arasaka_info_7,
    &arasaka_info_8,
    &arasaka_info_9,
    &arasaka_info_10,
    &arasaka_info_11,
    &arasaka_info_12,
    &arasaka_info_13,
    &arasaka_info_14,
    &arasaka_info_15,
    &arasaka_info_16,
    &arasaka_info_17,
    &arasaka_info_18,
    &arasaka_info_19,
    &arasaka_info_20,
    &arasaka_info_21,
    &arasaka_info_22,
    &arasaka_info_23,
    &arasaka_info_24,
    &arasaka_info_25,
    &arasaka_info_26,
    &arasaka_info_27,
    &arasaka_info_28,
    &arasaka_info_29,
    &arasaka_info_30,
    &arasaka_info_31,
    &arasaka_info_32,
    &arasaka_info_33,
    &arasaka_info_34,
    &arasaka_info_35,
    &arasaka_info_36,
    &arasaka_info_37,
    &arasaka_info_38,
    &arasaka_info_39,
    &arasaka_info_40,
    &arasaka_info_41,
    &arasaka_info_42,
    &arasaka_info_43,
    &arasaka_info_44,
    &arasaka_info_45,
    &arasaka_info_46,
    &arasaka_info_47,
    &arasaka_info_48,
    &arasaka_info_49,
};

int32_t lv_anim_path_linear_glitch(const lv_anim_t *a) {
    int32_t new_value = lv_anim_path_linear(a);

    // Add the glitch effect.
    int8_t glitch_chance = lv_rand(0, 100);
    int16_t glitch = lv_rand(-5, 5) * (glitch_chance / ARASAKA_IDLE_GLITCH_CHANCE);

    new_value += glitch;
    if (new_value < a->start_value) new_value = a->start_value;
    if (new_value > a->end_value) new_value = a->end_value;

    return new_value;
}

int32_t lv_anim_path_idle_glitch(const lv_anim_t *a) {
    int8_t glitch_chance = lv_rand(0, 100);

    if (glitch_chance < ARASAKA_IDLE_GLITCH_CHANCE) {
        return a->end_value;
    };

    return lv_rand(a->start_value, a->end_value);
}

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
    lv_anim_set_values(&widget->anim, 0, 10);
    lv_anim_set_path_cb(&widget->anim, lv_anim_path_idle_glitch);
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
    lv_anim_set_values(&widget->anim, 11, 18);
    lv_anim_set_path_cb(&widget->anim, lv_anim_path_idle_glitch);
    lv_anim_set_time(&widget->anim, 2000);

    lv_anim_start(&widget->anim);
}

void arasaka_anim_run_info_glitch(struct zmk_widget_arasaka *widget) {
    lv_anim_set_values(&widget->anim, 19, 69);
    lv_anim_set_path_cb(&widget->anim, lv_anim_path_linear_glitch);
    lv_anim_set_time(&widget->anim, 3000);

    lv_anim_start(&widget->anim);
}

void arasaka_anim_on_finish(lv_anim_t *a) {
    struct zmk_widget_arasaka *widget = (struct zmk_widget_arasaka *)lv_anim_get_user_data(a);

    widget->step = (widget->step + 1) % 5;

    if (widget->step == 0) {
        arasaka_anim_run_glitch(widget);
    } else if (widget->step == 1) {
        arasaka_anim_run_idle_logo(widget);
    } else if (widget->step == 2) {
        arasaka_anim_run_qr_code_glitch(widget);
    } else if (widget->step == 3) {
        arasaka_anim_run_qr_code_idle(widget);
    } else if (widget->step == 4) {
        arasaka_anim_run_info_glitch(widget);
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
