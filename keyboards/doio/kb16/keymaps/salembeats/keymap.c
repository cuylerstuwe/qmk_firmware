/* Copyright 2022 DOIO
 * Copyright 2022 HorrorTroll <https://github.com/HorrorTroll>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

// OLED animation
#include "lib/layer_status/layer_status.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum layer_names {
    _BASE,
    _FN,
    _FN1,
    _FN2
};

// enum layer_keycodes { };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
    _______,        _______,        _______,        _______,        HYPR(KC_Z),     // First row + top-left knob press
    LCTL(KC_F17),   LCTL(KC_F18),   LCTL(KC_F19),   LCTL(KC_F13),   HYPR(KC_U),     // Second row + top-right knob press
    KC_F17,         KC_F18,         KC_F19,         KC_F13,         TO(1),          // Third row + large knob press
    LALT(KC_F17),   LALT(KC_F18),   LALT(KC_F19),   LALT(KC_F13)                    // Fourth row
),
    [1] = LAYOUT(
    _______,        _______,        _______,        _______,        HYPR(KC_Z),     // First row + top-left knob press
    LGUI(KC_F17),   LGUI(KC_F18),   LGUI(KC_F19),   LGUI(KC_F13),   HYPR(KC_U),     // Second row + top-right knob press
    LCA(KC_F17),    LCA(KC_F18),    LCA(KC_F19),    LCA(KC_F13),    TO(2),          // Third row + large knob press
    LSA(KC_F17),    LSA(KC_F18),    LSA(KC_F19),    LSA(KC_F13)                     // Fourth row
),
    [2] = LAYOUT(
    _______,        _______,        _______,        _______,        HYPR(KC_Z),     // First row + top-left knob press
    LAG(KC_F17),    LAG(KC_F18),    LAG(KC_F19),    LAG(KC_F13),    HYPR(KC_U),     // Second row + top-right knob press
    LCAG(KC_F17),   LCAG(KC_F18),   LCAG(KC_F19),   LCAG(KC_F13),   TO(3),          // Third row + large knob press
    MEH(KC_F17),    MEH(KC_F18),    MEH(KC_F19),    MEH(KC_F13)                     // Fourth row
),
    [3] = LAYOUT(
    _______,        _______,        _______,        _______,        HYPR(KC_Z),     // First row + top-left knob press
    HYPR(KC_F17),   HYPR(KC_F18),   HYPR(KC_F19),   HYPR(KC_F13),   HYPR(KC_U),     // Second row + top-right knob press
    LSFT(KC_F17),   LSFT(KC_F18),   LSFT(KC_F19),   LSFT(KC_F13),   TO(0),          // Third row + large knob press
    LCTL(KC_F17),   LCTL(KC_F18),   LCTL(KC_F19),   LCTL(KC_F13)                    // Fourth row
),
/*
       ┌───┬───┬───┬───┐   ┌───┐ ┌───┐
       │ 1 │ 2 │ 3 │ 4 │   │Ply│ │TO1│
       ├───┼───┼───┼───┤   └───┘ └───┘
       │ 5 │ 6 │ 7 │ 8 │
       ├───┼───┼───┼───┤
       │ 9 │ 0 │ ↑ │Ent│      ┌───┐
       ├───┼───┼───┼───┤      │Mut│
       │Fn2│ ← │ ↓ │ → │      └───┘
       └───┴───┴───┴───┘
       ┌───┬───┬───┬───┐   ┌───┐ ┌───┐
       │ ! │ @ │ # │ $ │   │   │ │   │
       ├───┼───┼───┼───┤   └───┘ └───┘
       │ % │ ^ │ & │ * │
       ├───┼───┼───┼───┤
       │ ( │ ) │   │   │      ┌───┐
       ├───┼───┼───┼───┤      │   │
       │   │   │   │   │      └───┘
       └───┴───┴───┴───┘
*/
    /*  Row:    0         1        2        3         4      */
//    [_BASE] = LAYOUT(
//                KC_1,     KC_2,    KC_3,    KC_4,     KC_MPLY,
//                KC_5,     KC_6,    KC_7,    KC_8,     TO(_FN),
//                KC_9,     KC_0,    KC_UP,   KC_ENT,   KC_MUTE,
//                MO(_FN2), KC_LEFT, KC_DOWN, KC_RIGHT
//            ),

/*
       ┌───┬───┬───┬───┐   ┌───┐ ┌───┐
       │   │   │   │   │   │   │ │   │
       ├───┼───┼───┼───┤   └───┘ └───┘
       │   │   │   │   │
       ├───┼───┼───┼───┤
       │   │   │   │   │      ┌───┐
       ├───┼───┼───┼───┤      │   │
       │   │   │   │   │      └───┘
       └───┴───┴───┴───┘
*/
    /*  Row:    0        1        2        3        4       */
//    [_FN] = LAYOUT(
//                _______, _______, _______, _______, _______,
//                _______, _______, _______, _______, TO(_FN1),
//                _______, _______, _______, _______, _______,
//                _______, _______, _______, _______
//            ),

/*
       ┌───┬───┬───┬───┐   ┌───┐ ┌───┐
       │   │   │   │   │   │   │ │   │
       ├───┼───┼───┼───┤   └───┘ └───┘
       │   │   │   │   │
       ├───┼───┼───┼───┤
       │   │   │   │   │      ┌───┐
       ├───┼───┼───┼───┤      │   │
       │   │   │   │   │      └───┘
       └───┴───┴───┴───┘
*/
    /*  Row:    0        1        2        3        4       */
//    [_FN1] = LAYOUT(
//                _______, _______, _______, _______, _______,
//                _______, _______, _______, _______, TO(_FN2),
//                _______, _______, _______, _______, _______,
//                _______, _______, _______, _______
//            ),

/*
       ┌───┬───┬───┬───┐   ┌───┐ ┌───┐
       │Spi│Spd│   │   │   │   │ │TO0│
       ├───┼───┼───┼───┤   └───┘ └───┘
       │Sai│Sad│   │   │
       ├───┼───┼───┼───┤
       │Tog│Mod│Hui│   │      ┌───┐
       ├───┼───┼───┼───┤      │   │
       │   │Vai│Hud│Vad│      └───┘
       └───┴───┴───┴───┘
*/
    /*  Row:    0        1        2        3        4        */
//    [_FN2] = LAYOUT(
//                RGB_SPI, RGB_SPD, _______, QK_BOOT, _______,
//                RGB_SAI, RGB_SAD, _______, _______, TO(_BASE),
//                RGB_TOG, RGB_MOD, RGB_HUI, _______, _______,
//                _______, RGB_VAI, RGB_HUD, RGB_VAD
//            ),
};

#ifdef OLED_ENABLE
    bool oled_task_user(void) {
        render_layer_status();

        return true;
    }
#endif

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_BASE] = { ENCODER_CCW_CW(HYPR(KC_X), HYPR(KC_Y)), ENCODER_CCW_CW(HYPR(KC_S), HYPR(KC_T)), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_FN] = { ENCODER_CCW_CW(HYPR(KC_X), HYPR(KC_Y)), ENCODER_CCW_CW(HYPR(KC_S), HYPR(KC_T)), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_FN1] = { ENCODER_CCW_CW(HYPR(KC_X), HYPR(KC_Y)), ENCODER_CCW_CW(HYPR(KC_S), HYPR(KC_T)), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_FN2] = { ENCODER_CCW_CW(HYPR(KC_X), HYPR(KC_Y)), ENCODER_CCW_CW(HYPR(KC_S), HYPR(KC_T)), ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
//    [_FN]   = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
//    [_FN1]  = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
//    [_FN2]  = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
};
#endif
