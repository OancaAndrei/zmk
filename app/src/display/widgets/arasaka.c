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
#include <zmk/events/layer_state_changed.h>
#include <zmk/event_manager.h>
#include <zmk/endpoints.h>
#include <zmk/keymap.h>

#if IS_ENABLED(CONFIG_ZMK_DISPLAY_WORK_QUEUE_DEDICATED)
#error "Arasaka logo widget only works with the system work queue currently"
#endif

static sys_slist_t widgets = SYS_SLIST_STATIC_INIT(&widgets);

const void **images;

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

const void *arasaka_logo[] = {&arasaka_1, &arasaka_2,  &arasaka_3, &arasaka_4,
                              &arasaka_5, &arasaka_6,  &arasaka_7, &arasaka_8,
                              &arasaka_9, &arasaka_10, &arasaka_11};

const void *qr_code[] = {&arasaka_12, &arasaka_13, &arasaka_14, &arasaka_15,
                         &arasaka_16, &arasaka_17, &arasaka_18, &arasaka_19};

void set_img_src(void *var, int32_t val) {
    lv_obj_t *img = (lv_obj_t *)var;
    lv_img_set_src(img, images[val]);
}

void update_arasaka(struct zmk_widget_arasaka *widget) {
    LOG_DBG("update_arasaka");

    lv_anim_del(widget->obj, set_img_src);
    lv_anim_init(&widget->anim);
    lv_anim_set_time(&widget->anim, 500);
    lv_anim_set_repeat_delay(&widget->anim, 2000);
    lv_anim_set_var(&widget->anim, widget->obj);
    lv_anim_set_values(&widget->anim, 0, 10);
    lv_anim_set_exec_cb(&widget->anim, set_img_src);
    lv_anim_set_repeat_count(&widget->anim, LV_ANIM_REPEAT_INFINITE);
    images = arasaka_logo;
    lv_anim_start(&widget->anim);
}

// int arasaka_listener(const zmk_event_t *eh) {
//     struct zmk_widget_arasaka *widget;
//     SYS_SLIST_FOR_EACH_CONTAINER(&widgets, widget, node) {
//         update_arasaka(widget);
//     }
//     return ZMK_EV_EVENT_BUBBLE;
// }

// ZMK_LISTENER(zmk_widget_arasaka, arasaka_listener)
// ZMK_SUBSCRIPTION(zmk_widget_arasaka, zmk_layer_state_changed);

int zmk_widget_arasaka_init(struct zmk_widget_arasaka *widget, lv_obj_t *parent) {
    widget->obj = lv_img_create(parent);

    lv_obj_align(widget->obj, LV_ALIGN_CENTER, 0, 0);
    update_arasaka(widget);

    sys_slist_append(&widgets, &widget->node);

    return 0;
}

lv_obj_t *zmk_widget_arasaka_obj(struct zmk_widget_arasaka *widget) { return widget->obj; }
