// Copyright 2023
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

// Hyper key is defined as Ctrl+Alt+Shift+Gui
#define HYPR_A HYPR(KC_A)
#define HYPR_B HYPR(KC_B)
#define HYPR_C HYPR(KC_C)

// Colors for each key
#define RED_COLOR 0, 255, 255
#define GREEN_COLOR 85, 255, 255
#define BLUE_COLOR 170, 255, 255

// Time in ms to show the color (adjust as needed)
#define COLOR_TIMEOUT 300

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(HYPR_A, HYPR_B, HYPR_C)
};

// Tracks which color to display (per key)
static uint32_t key_timer[3] = {0, 0, 0};
static bool key_active[3] = {false, false, false};

// Initialize LEDs to off
void keyboard_post_init_user(void) {
#ifdef RGBLIGHT_ENABLE
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom(0, 0, 0);
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
#endif
}

// Handle key press to trigger RGB
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    uint8_t key_index = 255;

    // Determine which key was pressed
    if (keycode == HYPR_A) key_index = 0;
    else if (keycode == HYPR_B) key_index = 1;
    else if (keycode == HYPR_C) key_index = 2;

    if (key_index < 3) {
        if (record->event.pressed) {
            // Set the timer and activate the key
            key_timer[key_index] = timer_read32();
            key_active[key_index] = true;

            // Set the LED color based on which key was pressed
            switch (key_index) {
                case 0: // Key 1 - Red
                    rgblight_sethsv_noeeprom(RED_COLOR);
                    break;
                case 1: // Key 2 - Green
                    rgblight_sethsv_noeeprom(GREEN_COLOR);
                    break;
                case 2: // Key 3 - Blue
                    rgblight_sethsv_noeeprom(BLUE_COLOR);
                    break;
            }
        }
    }

    return true; // Continue with normal key processing
}

// Check timers periodically to turn off the LEDs
void housekeeping_task_user(void) {
    for (uint8_t i = 0; i < 3; i++) {
        if (key_active[i] && timer_elapsed32(key_timer[i]) > COLOR_TIMEOUT) {
            key_active[i] = false;
            // Turn off LEDs if all keys are inactive
            if (!key_active[0] && !key_active[1] && !key_active[2]) {
                rgblight_sethsv_noeeprom(0, 0, 0);
            }
        }
    }
}
