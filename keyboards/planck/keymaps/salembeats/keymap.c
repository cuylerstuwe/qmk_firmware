/* Copyright 2015-2017 Jack Humbert
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
#include "muse.h"

extern keymap_config_t keymap_config;

enum planck_layers {
  _QWERTY,
  _LEFT_LOWER,
  _LEFT_RAISE,
  _RIGHT_LOWER,
  _RIGHT_RAISE,
  _DOUBLE_LOWER,
  _DOUBLE_RAISE,
  NAV_LAYER,
  NUMPAD_LAYER,
  SYMBOL_LAYER
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  SYMBOL_MODE,
};

#define LEFT_LOWER MO(_LEFT_LOWER)
#define LEFT_RAISE MO(_LEFT_RAISE)
#define RIGHT_LOWER MO(_RIGHT_LOWER)
#define RIGHT_RAISE MO(_RIGHT_RAISE)

#define _______ KC_TRNS
#define ___x___ KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT_planck_grid(
    LT(NUMPAD_LAYER, KC_TAB), KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,        KC_O,    KC_P,                   KC_MINS,
    CTL_T(KC_ESC),            KC_A,    KC_S,    KC_D,    KC_F,    KC_G,       KC_H,    KC_J,    KC_K,        KC_L,    LT(NAV_LAYER, KC_SCLN), CTL_T(KC_ENT),
    KC_LSFT,                  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,       KC_N,    KC_M,    KC_COMM,     KC_DOT,  KC_SLSH,                KC_RSFT,
    SYMBOL_MODE,              LEFT_RAISE,       KC_LALT, KC_LGUI, LEFT_LOWER, KC_SPC,  KC_SPC,  RIGHT_LOWER, KC_RGUI, KC_RALT, RIGHT_RAISE,   SYMBOL_MODE
),

[_LEFT_LOWER] = LAYOUT_planck_grid(
        _______, KC_AMPR, KC_PIPE, KC_DQUO, KC_GRV , KC_EXLM, KC_EXLM, KC_QUOT, KC_DQUO, KC_PIPE, KC_AMPR, _______,
		_______, KC_LT,   KC_LCBR, KC_LPRN, KC_LBRC, KC_EQL,  KC_EQL,  KC_RBRC, KC_RPRN, KC_RCBR, KC_GT,   _______,
		_______, KC_MINS, KC_PLUS, KC_SLSH, KC_ASTR, KC_BSLS, KC_BSLS, KC_ASTR, KC_SLSH, KC_PLUS, KC_MINS, _______,
		_______, _______, _______, _______, _______, KC_BSPC, KC_BSPC, _______, _______, _______, _______, _______
),

[_RIGHT_LOWER] = LAYOUT_planck_grid(
        _______, KC_AMPR, KC_PIPE, KC_DQUO, KC_GRV , KC_EXLM, KC_EXLM, KC_QUOT, KC_DQUO, KC_PIPE, KC_AMPR, _______,
		_______, KC_LT,   KC_LCBR, KC_LPRN, KC_LBRC, KC_EQL,  KC_EQL,  KC_RBRC, KC_RPRN, KC_RCBR, KC_GT,   _______,
		_______, KC_MINS, KC_PLUS, KC_SLSH, KC_ASTR, KC_BSLS, KC_BSLS, KC_ASTR, KC_SLSH, KC_PLUS, KC_MINS, _______,
		_______, _______, _______, _______, _______, KC_BSPC, KC_BSPC, _______, _______, _______, _______, _______
),

[_LEFT_RAISE] = LAYOUT_planck_grid(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

[_RIGHT_RAISE] = LAYOUT_planck_grid(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

[_DOUBLE_LOWER] = LAYOUT_planck_grid(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,    KC_F9,    KC_F10,  KC_F11,  KC_F12 ,
    _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______, _______, _______
),

[_DOUBLE_RAISE] = LAYOUT_planck_grid(
        _______, RESET,   _______, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD,  RGB_VAI, RGB_VAD, KC_DEL ,
        _______, _______, _______, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  _______,  _______, _______, _______,
        _______, _______, _______, _______, _______, MI_ON,   MI_OFF, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______
),

[NAV_LAYER] = LAYOUT_planck_grid(
	___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___,                 ___x___,
	_______, ___x___, KC_HOME, KC_PGUP, KC_PGDN, KC_END,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, LT(NAV_LAYER, KC_SCLN),  _______,
	_______, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___,                 _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                 _______
),

[NUMPAD_LAYER] = LAYOUT_planck_grid(
  _______, _______, _______, _______, _______, _______, KC_NUM_LOCK, KC_P7  , KC_P8  , KC_P9  , KC_PPLS, KC_PSLS,
  _______, _______, _______, _______, _______, _______, _______,     KC_P4  , KC_P5  , KC_P6  , KC_PPLS, KC_PAST,
  _______, _______, _______, _______, _______, _______, _______,     KC_P1  , KC_P2  , KC_P3  , KC_PENT, KC_PMNS,
  _______, _______, _______, _______, _______, _______, _______,     KC_P0  , KC_P0  , KC_PDOT, KC_PENT, KC_MUTE
),

[SYMBOL_LAYER] = LAYOUT_planck_grid(
  _______, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)

};

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _LEFT_LOWER, _RIGHT_LOWER, _DOUBLE_LOWER);
    state = update_tri_layer_state(state, _LEFT_RAISE, _RIGHT_RAISE, _DOUBLE_RAISE);
    return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case SYMBOL_MODE:
      if (record->event.pressed) {
        layer_on(SYMBOL_LAYER);
      } else {
        layer_off(SYMBOL_LAYER);
      }
      return false;
      break;
  }
  return true;
}

void dip_update(uint8_t index, bool active) {
}

void matrix_init_user(void) {
    rgblight_setrgb(0, 0, 0); // Adjust RGB values as needed, e.g., (0, 255, 0) for green
}
void matrix_scan_user(void) {
    rgblight_setrgb(0, 0, 0); // Continuously sets RGB values to off
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case LEFT_LOWER:
    case RIGHT_LOWER:
    case LEFT_RAISE:
    case RIGHT_RAISE:
      return false;
    default:
      return true;
  }
