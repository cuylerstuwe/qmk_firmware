// Copyright 2023
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(A(KC_R), A(KC_U), A(KC_S))
};

/* Simple RGB lighting configuration */
#ifdef RGBLIGHT_ENABLE
void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom(HSV_PURPLE);
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
}
#endif
