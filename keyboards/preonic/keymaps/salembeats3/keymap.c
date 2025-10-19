/*
 * Salembeats3 keymap – encoder layout adapted for non-encoder Preonic revisions.
 * Derived from salembeats2encoder keymap; all encoder-specific functionality has
 * been removed/replaced so it builds on a classic Preonic without a rotary
 * encoder.  The physical encoder press key has been replaced by KC_F1 in the
 * matrix for better parity with earlier non-encoder layouts.
 */

#include QMK_KEYBOARD_H
#include "muse.h"

// State tracking for hyper combo (both lowers + symbol mode)
static bool left_lower_held = false;
static bool right_lower_held = false;
static bool symbol_mode_active = false;
static bool hyper_combo_triggered = false;

// Double-tap detection state for LEFT_LOWER and RIGHT_LOWER
static uint16_t left_lower_press_timer = 0;
static uint16_t left_lower_tap_timer = 0;
static uint8_t  left_lower_tap_count = 0;
static bool     left_lower_interrupted = false;

static uint16_t right_lower_press_timer = 0;
static uint16_t right_lower_tap_timer = 0;
static uint8_t  right_lower_tap_count = 0;
static bool     right_lower_interrupted = false;

enum preonic_layers {
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

enum preonic_keycodes {
  QWERTY = SAFE_RANGE,
  SYMBOL_MODE,
  HYPER_B
};

#define LEFT_LOWER MO(_LEFT_LOWER)
#define LEFT_RAISE MO(_LEFT_RAISE)
#define RIGHT_LOWER MO(_RIGHT_LOWER)
#define RIGHT_RAISE MO(_RIGHT_RAISE)

#define ___x___ KC_NO

// Helper to emit a Hyper chord with the provided keycode
static inline void send_hyper_chord(uint16_t kc) {
  register_code(KC_LCTL);
  register_code(KC_LSFT);
  register_code(KC_LALT);
  register_code(KC_LGUI);
  register_code(kc);
  unregister_code(kc);
  unregister_code(KC_LGUI);
  unregister_code(KC_LALT);
  unregister_code(KC_LSFT);
  unregister_code(KC_LCTL);
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT_preonic_grid(
    KC_F1,                    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,      KC_F7,   KC_F8,   KC_F9,       KC_F10,  KC_F11,                 KC_F12,
    LT(NUMPAD_LAYER, KC_TAB), KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,        KC_O,    KC_P,                   KC_MINS,
    CTL_T(KC_ESC),            KC_A,    KC_S,    KC_D,    KC_F,    KC_G,       KC_H,    KC_J,    KC_K,        KC_L,    LT(NAV_LAYER, KC_SCLN), CTL_T(KC_ENT),
    KC_LSFT,                  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,       KC_N,    KC_M,    KC_COMM,     KC_DOT,  KC_SLSH,                KC_RSFT,
    SYMBOL_MODE,              LEFT_RAISE,       KC_LALT, KC_LGUI, LEFT_LOWER, KC_SPC,  KC_SPC,  RIGHT_LOWER, KC_RGUI, KC_RALT, RIGHT_RAISE,   SYMBOL_MODE
),

[_LEFT_LOWER] = LAYOUT_preonic_grid(
    KC_F1,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, KC_AMPR, KC_PIPE, KC_DQUO, KC_GRV , KC_EXLM, KC_EXLM, KC_QUOT, KC_DQUO, KC_PIPE, KC_AMPR, _______,
    _______, KC_LT,   KC_LCBR, KC_LPRN, KC_LBRC, KC_EQL,  KC_EQL,  KC_RBRC, KC_RPRN, KC_RCBR, KC_GT,   _______,
    _______, KC_MINS, KC_PLUS, KC_SLSH, KC_ASTR, KC_BSLS, KC_BSLS, KC_ASTR, KC_SLSH, KC_PLUS, KC_MINS, _______,
    _______, _______, _______, _______, _______, KC_SPC,  KC_BSPC, _______, _______, _______, _______, _______
),

[_RIGHT_LOWER] = LAYOUT_preonic_grid(
    KC_F1,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, KC_AMPR, KC_PIPE, KC_DQUO, KC_GRV , KC_EXLM, KC_EXLM, KC_QUOT, KC_DQUO, KC_PIPE, KC_AMPR, _______,
    _______, KC_LT,   KC_LCBR, KC_LPRN, KC_LBRC, KC_EQL,  KC_EQL,  KC_RBRC, KC_RPRN, KC_RCBR, KC_GT,   _______,
    _______, KC_MINS, KC_PLUS, KC_SLSH, KC_ASTR, KC_BSLS, KC_BSLS, KC_ASTR, KC_SLSH, KC_PLUS, KC_MINS, _______,
    _______, _______, _______, _______, _______, KC_SPC,  KC_BSPC, _______, _______, _______, _______, _______
),

[_LEFT_RAISE] = LAYOUT_preonic_grid(
    KC_F1,          _______,      _______,      _______,      _______,      _______,      _______,      _______,     _______,       _______,      _______,      _______,
    _______,        _______,      LGUI(KC_F17), LGUI(KC_F18), LGUI(KC_F19), LSFT(KC_F17), LSFT(KC_F18), LGUI(KC_F17), LGUI(KC_F18), LGUI(KC_F19), _______,      _______,
    _______,        LSA(KC_F17),  LCA(KC_F17),  LCA(KC_F18),  LCA(KC_F19),  LSFT(KC_F19), LSFT(KC_F13), LCA(KC_F17), LCA(KC_F18),   LCA(KC_F19),  LSA(KC_F18),  _______,
    LCTL(KC_F17),   LCTL(KC_F18), LCTL(KC_F19), LCTL(KC_F13), KC_F17,       KC_F18,       KC_F19,       KC_F13,      LALT(KC_F17),  LALT(KC_F18), LALT(KC_F19), LALT(KC_F13),
    _______,        _______,      _______,      _______,      _______,      MEH(KC_F17),  MEH(KC_F17),  _______,     _______,       _______,      _______,      _______
),

[_RIGHT_RAISE] = LAYOUT_preonic_grid(
    KC_F1,          _______,      _______,      _______,      _______,      _______,      _______,      _______,     _______,       _______,      _______,      _______,
    _______,        _______,      LGUI(KC_F17), LGUI(KC_F18), LGUI(KC_F19), LSFT(KC_F17), LSFT(KC_F18), LGUI(KC_F17), LGUI(KC_F18), LGUI(KC_F19), _______,      _______,
    _______,        LSA(KC_F17),  LCA(KC_F17),  LCA(KC_F18),  LCA(KC_F19),  LSFT(KC_F19), LSFT(KC_F13), LCA(KC_F17), LCA(KC_F18),   LCA(KC_F19),  LSA(KC_F18),  _______,
    LCTL(KC_F17),   LCTL(KC_F18), LCTL(KC_F19), LCTL(KC_F13), KC_F17,       KC_F18,       KC_F19,       KC_F13,      LALT(KC_F17),  LALT(KC_F18), LALT(KC_F19), LALT(KC_F13),
    _______,        _______,      _______,      _______,      _______,      MEH(KC_F17),  MEH(KC_F17),  _______,     _______,       _______,      _______,      _______
),

[_DOUBLE_LOWER] = LAYOUT_preonic_grid(
    KC_F1,   _______, _______, _______, _______, _______, _______, _______,  _______,  _______, _______, _______,
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,    KC_F9,    KC_F10,  KC_F11,  KC_F12 ,
    _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______,  _______,  _______, _______, _______
),

[_DOUBLE_RAISE] = LAYOUT_preonic_grid(
    KC_F1,          _______,      _______,      _______,      _______,      _______,     _______,     _______,     _______,      _______,      _______,      _______,
    _______,        _______,      _______,      _______,      _______,      _______,     _______,     _______,     _______,      _______,      _______,      _______,
    _______,        _______,      LGUI(KC_F17), LGUI(KC_F18), LGUI(KC_F19), LSA(KC_F17), LSA(KC_F18), LCA(KC_F17), LCA(KC_F18),  LCA(KC_F19),  _______,      _______,
    LCTL(KC_F17),   LCTL(KC_F18), LCTL(KC_F19), LCTL(KC_F13), KC_F17,       KC_F18,      KC_F19,      KC_F13,      LALT(KC_F17), LALT(KC_F18), LALT(KC_F19), LALT(KC_F13),
    _______,        _______,      _______,      _______,      _______,      _______,     _______,     _______,     _______,      _______,      _______,      _______
),

[NAV_LAYER] = LAYOUT_preonic_grid(
    KC_F1,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                 _______,
    ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___,                 ___x___,
    _______, ___x___, KC_HOME, KC_PGUP, KC_PGDN, KC_END,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, LT(NAV_LAYER, KC_SCLN),  _______,
    _______, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___,                 _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                 _______
),

[NUMPAD_LAYER] = LAYOUT_preonic_grid(
  KC_F1,   _______, _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______,
  _______, _______, _______, _______, _______, _______, KC_NUM_LOCK, KC_P7  , KC_P8  , KC_P9  , KC_PPLS, KC_PSLS,
  _______, _______, _______, _______, _______, _______, _______,     KC_P4  , KC_P5  , KC_P6  , KC_PPLS, KC_PAST,
  _______, _______, _______, _______, _______, _______, _______,     KC_P1  , KC_P2  , KC_P3  , KC_PENT, KC_PMNS,
  _______, _______, _______, _______, _______, _______, _______,     KC_P0  , KC_P0  , KC_PDOT, KC_PENT, KC_MUTE
),

[SYMBOL_LAYER] = LAYOUT_preonic_grid(
  KC_F1,   _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______,
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
  // Track interruptions while a LOWER key is held to distinguish taps vs holds with other key activity
  if (record->event.pressed) {
    if (left_lower_held && keycode != LEFT_LOWER) {
      left_lower_interrupted = true;
    }
    if (right_lower_held && keycode != RIGHT_LOWER) {
      right_lower_interrupted = true;
    }
  }

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
        symbol_mode_active = true;

        // Check for hyper combo after activating symbol mode
        if (left_lower_held && right_lower_held && symbol_mode_active && !hyper_combo_triggered) {
          // Emit hyper + b
          register_code(KC_LCTL);
          register_code(KC_LSFT);
          register_code(KC_LALT);
          register_code(KC_LGUI);
          register_code(KC_B);
          unregister_code(KC_B);
          unregister_code(KC_LGUI);
          unregister_code(KC_LALT);
          unregister_code(KC_LSFT);
          unregister_code(KC_LCTL);
          hyper_combo_triggered = true;
          return false;
        }
      } else {
        layer_off(SYMBOL_LAYER);
        symbol_mode_active = false;
        hyper_combo_triggered = false;  // Reset when symbol mode is deactivated
      }
      return false;
      break;
    case LEFT_LOWER:
      if (record->event.pressed) {
        // Reset stale first-tap window
        if (left_lower_tap_count == 1 && timer_elapsed(left_lower_tap_timer) > TAPPING_TERM) {
          left_lower_tap_count = 0;
        }

        // Double-tap detection (second tap press): only when clean tap and not conflicting
        if (left_lower_tap_count == 1 && timer_elapsed(left_lower_tap_timer) <= TAPPING_TERM && !left_lower_interrupted && !symbol_mode_active && !right_lower_held) {
          send_hyper_chord(KC_A);
          left_lower_tap_count = 0;
          left_lower_interrupted = false;
          return false; // swallow this press so layer doesn't flicker
        }

        left_lower_held = true;
        left_lower_interrupted = false;
        left_lower_press_timer = timer_read();

        // Check for hyper combo after left lower is pressed
        if (left_lower_held && right_lower_held && symbol_mode_active && !hyper_combo_triggered) {
          // Emit hyper + b
          register_code(KC_LCTL);
          register_code(KC_LSFT);
          register_code(KC_LALT);
          register_code(KC_LGUI);
          register_code(KC_B);
          unregister_code(KC_B);
          unregister_code(KC_LGUI);
          unregister_code(KC_LALT);
          unregister_code(KC_LSFT);
          unregister_code(KC_LCTL);
          hyper_combo_triggered = true;
          return false;
        }
      } else {
        uint16_t held_ms = timer_elapsed(left_lower_press_timer);

        // Count a clean tap if released quickly without pressing other keys, and not during conflicting modes
        if (held_ms <= TAPPING_TERM && !left_lower_interrupted && !symbol_mode_active && !right_lower_held) {
          if (left_lower_tap_count == 0) {
            left_lower_tap_count = 1;
            left_lower_tap_timer = timer_read();
          }
        } else {
          left_lower_tap_count = 0;
        }

        left_lower_held = false;
        hyper_combo_triggered = false;  // Reset when left lower is released
      }
      break;
    case RIGHT_LOWER:
      if (record->event.pressed) {
        // Reset stale first-tap window
        if (right_lower_tap_count == 1 && timer_elapsed(right_lower_tap_timer) > TAPPING_TERM) {
          right_lower_tap_count = 0;
        }

        // Double-tap detection (second tap press): only when clean tap and not conflicting
        if (right_lower_tap_count == 1 && timer_elapsed(right_lower_tap_timer) <= TAPPING_TERM && !right_lower_interrupted && !symbol_mode_active && !left_lower_held) {
          send_hyper_chord(KC_C);
          right_lower_tap_count = 0;
          right_lower_interrupted = false;
          return false; // swallow this press so layer doesn't flicker
        }

        right_lower_held = true;
        right_lower_interrupted = false;
        right_lower_press_timer = timer_read();

        // Check for hyper combo after right lower is pressed
        if (left_lower_held && right_lower_held && symbol_mode_active && !hyper_combo_triggered) {
          // Emit hyper + b
          register_code(KC_LCTL);
          register_code(KC_LSFT);
          register_code(KC_LALT);
          register_code(KC_LGUI);
          register_code(KC_B);
          unregister_code(KC_B);
          unregister_code(KC_LGUI);
          unregister_code(KC_LALT);
          unregister_code(KC_LSFT);
          unregister_code(KC_LCTL);
          hyper_combo_triggered = true;
          return false;
        }
      } else {
        uint16_t held_ms = timer_elapsed(right_lower_press_timer);

        // Count a clean tap if released quickly without pressing other keys, and not during conflicting modes
        if (held_ms <= TAPPING_TERM && !right_lower_interrupted && !symbol_mode_active && !left_lower_held) {
          if (right_lower_tap_count == 0) {
            right_lower_tap_count = 1;
            right_lower_tap_timer = timer_read();
          }
        } else {
          right_lower_tap_count = 0;
        }

        right_lower_held = false;
        hyper_combo_triggered = false;  // Reset when right lower is released
      }
      break;
    case HYPER_B:
      if (record->event.pressed) {
        register_code(KC_LCTL);
        register_code(KC_LSFT);
        register_code(KC_LALT);
        register_code(KC_LGUI);
        register_code(KC_B);
        unregister_code(KC_B);
        unregister_code(KC_LGUI);
        unregister_code(KC_LALT);
        unregister_code(KC_LSFT);
        unregister_code(KC_LCTL);
      }
      return false;
      break;
  }

  // Check for hyper combo: both lowers held + symbol mode active
  if (left_lower_held && right_lower_held && symbol_mode_active && !hyper_combo_triggered && record->event.pressed) {
    // Emit hyper + b
    register_code(KC_LCTL);
    register_code(KC_LSFT);
    register_code(KC_LALT);
    register_code(KC_LGUI);
    register_code(KC_B);
    unregister_code(KC_B);
    unregister_code(KC_LGUI);
    unregister_code(KC_LALT);
    unregister_code(KC_LSFT);
    unregister_code(KC_LCTL);
    hyper_combo_triggered = true;
    return false;
  }

  return true;
}

void dip_update(uint8_t index, bool active) {
}

void matrix_scan_user(void) {
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
} 