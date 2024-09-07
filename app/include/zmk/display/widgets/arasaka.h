/*
 * Copyright (c) 2024 The ZMK Contributors
 *
 * SPDX-License-Identifier: MIT
 */

#pragma once

#include <lvgl.h>
#include <zephyr/kernel.h>

struct zmk_widget_arasaka {
    sys_snode_t node;
    lv_obj_t *obj;
    lv_anim_t anim;
    int32_t step;
};

int zmk_widget_arasaka_init(struct zmk_widget_arasaka *widget, lv_obj_t *parent);
lv_obj_t *zmk_widget_arasaka_obj(struct zmk_widget_arasaka *widget);
