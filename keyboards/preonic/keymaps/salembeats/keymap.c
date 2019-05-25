/**
 * Cuyler's (salembeats)
 * Preonic Layout (keymap.c)
 * 
*/

#include QMK_KEYBOARD_H
#define MIDI_ADVANCED
#include "midi.h"
#include "process_midi.h"
#include <LUFA/Drivers/USB/USB.h>
#include "qmk_midi.h"

#ifdef AUDIO_ENABLE
	#include "song_list.h"
#endif

enum preonic_layers {
	_QWERTY,
	_LOWER,
	_RAISE,
	_SUPER_RAISE,
	_SUPER_LOWER,
	NAV_LAYER,
	_ADJUST,
	_NUMPAD
};

// Key aliases for legibility
#define _______ KC_TRNS
#define ___x___ KC_NO

#define DESKMAN LWIN(KC_TAB)
#define LEFTDSK LCTL(LWIN(KC_LEFT))
#define RGHTDSK LCTL(LWIN(KC_RIGHT))

#define WINLEFT LWIN(KC_LEFT)
#define WINUP   LWIN(KC_UP)
#define WINDOWN LWIN(KC_DOWN)
#define WINRGHT LWIN(KC_RIGHT)

#define PREVWIN LALT(KC_ESC)
#define NEXTWIN LALT(LSFT(KC_ESC))

enum preonic_keycodes {
	QWERTY = SAFE_RANGE,
	LOWER,
	LOWER2,
	RAISE,
	RAISE2,
	MCC_50,
	MCC_51,
	MCC_52,
	MCC_53,
	MCC_54,
	MCC_55,
	MCC_56,
	MCC_57,
	MACRO_OPEN_CLOSE_CURLY,
	MACRO_OPEN_CLOSE_SQUARE,
	MACRO_DOUBLE_COLON,
	MACRO_DOUBLE_AND,
	MACRO_DOUBLE_OR,
	MACRO_SKINNY_ARROW,
	MACRO_THICK_ARROW,
	MACRO_DOUBLE_UNEQUAL,
	MACRO_DOUBLE_EQUAL,
	MACRO_TRIPLE_UNEQUAL,
	MACRO_TRIPLE_EQUAL,
	MACRO_OPENING_MULTILINE_COMMENT,
	MACRO_CLOSING_MULTILINE_COMMENT,
	MACRO_C_STYLE_COMMENT,
	MACRO_LESS_OR_EQUAL,
	MACRO_GREATER_OR_EQUAL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Base.

	 *  ┌-----+-----┬-----┬-----┬-----┬-----┬-----┬-----┬-----┬-----┬-----┬-----┐
	 *  │ `~  │  1! │  2@ │  3# │  4$ │  5% │  6^ │  7& │  8* │  9( │  0) │  -_ │
	 *  ├-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┤
	 *  │Tab#P│  Q  │  W  │  E  │  R  │  T  │  Y  │  U  │  I  │  O  │  P  │  \  │
	 *  ├-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┤
	 *  │⌃ Esc│  A  │  S  │  D  │  F  │  G  │  H  │  J  │  K  │  L  │; Nav│^ Ent│
	 *  ├-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┤
	 *  │  ⇧ │  Z  │  X  │  C  │  V  │  B  │  N  │  M  │ ,<  │ .>  │ /?  │ ⇧ │
	 *  ├-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┤
	 *  │Ctrl │ Win │ Alt │ ↓↓↓ │  ↓  │ Spc | Spc |  ↑  │ ↑↑↑ │ Alt │ Win │ Ctrl│
	 *  └-----┴-----┴-----┴-----┴-----┴-----┴-----┴-----┴-----┴-----┴-----┴-----┘
	 */
[_QWERTY] = LAYOUT_preonic_grid( \
	KC_GRV,              KC_1,      KC_2,    KC_3,    KC_4,  KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,                   KC_MINS,       \
	LT(_NUMPAD, KC_TAB), KC_Q,      KC_W,    KC_E,    KC_R,  KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,                   KC_BSLS,       \
	CTL_T(KC_ESC),       KC_A,      KC_S,    KC_D,    KC_F,  KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    LT(NAV_LAYER, KC_SCLN), CTL_T(KC_ENT), \
	KC_LSFT,             KC_Z,      KC_X,    KC_C,    KC_V,  KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                KC_RSFT,       \
	KC_LCTRL,            KC_LWIN,   KC_LALT, LOWER2,  LOWER, KC_SPC,  KC_SPC,  RAISE,   RAISE2,  KC_RALT, KC_RWIN,                KC_RCTRL       \
),

/* Enclosing pairs, backspace, functions. (LOWER)

	 *  ┌-----+-----┬-----┬-----┬-----┬-----┬-----┬-----┬-----┬-----┬-----┬-----┐
	 *  │ F1  │ F2  │ F3  │ F4  │ F5  │ F6  │ F7  │ F8  │ F9  │ F10 │ F11 │ F12 │
	 *  ├-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┤
	 *  │     │  &  │  |  │  "  │  '  │  !  │  !  │  '  │  "  │  |  │  &  │Bkspc│
	 *  ├-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┤
	 *  │     │  <  │  {  │  (  │  [  │  =  │  =  │  ]  │  )  │  }  │  >  │  '  │
	 *  ├-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┤
	 *  │     │  -  │  +  │  /  │  *  │  \  │  \  │  *  │  /  │  +  │  -  │     │
	 *  ├-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┤
	 *  │     │     │     │     │>> <<│ Spc |Bkspc|     │     │     │     │     │
	 *  └-----+-----┴-----┴-----┴-----┴-----┴-----┴-----┴-----┴-----┴-----┴-----┘
	 */
[_LOWER] = LAYOUT_preonic_grid( \
		KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  \
		_______, KC_AMPR, KC_PIPE, KC_DQUO, KC_QUOT, KC_EXLM, KC_EXLM, KC_QUOT, KC_DQUO, KC_PIPE, KC_AMPR, KC_BSPC, \
		_______, KC_LT,   KC_LCBR, KC_LPRN, KC_LBRC, KC_EQL,  KC_EQL,  KC_RBRC, KC_RPRN, KC_RCBR, KC_GT,   KC_QUOT, \
		_______, KC_MINS, KC_PLUS, KC_SLSH, KC_ASTR, KC_BSLS, KC_BSLS, KC_ASTR, KC_SLSH, KC_PLUS, KC_MINS, _______, \
		_______, _______, _______, _______, _______, KC_SPC,  KC_BSPC, _______, _______, _______, _______, _______  \
	),

/* Common prgramming keywords. (SUPER LOWER)
const * 
var * 
let *
function *
class *
string
if *
else *
while *
for *
return *
enum
true *
false *
null *
undefined *

	 *  ┌-----+-----┬-----┬-----┬-----┬-----┬-----┬-----┬-----┬-----┬-----┬-----┐
	 *  │     │     |     │     │     │     │     │     │     │     │     │     │
	 *  ├-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┤
	 *  │     │     │     │     │     │     │     │     │     │     │     │     │
	 *  ├-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┤
	 *  │     │     │     │     │     │     │     │     │     │     │     │     │
	 *  ├-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┤
	 *  │     │     │     │     │     │     │     │     │     │     │     │     │
	 *  ├-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┤
	 *  │     │     │     │>> <<│     │     |     │     │     │     │     │     │
	 *  └-----+-----┴-----┴-----┴-----┴-----┴-----┴-----┴-----┴-----┴-----┴-----┘
	 */
[_SUPER_LOWER] = LAYOUT_preonic_grid( \
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
	),


/* Enclosing pairs, backspace, functions. (RAISE)

	 *  ┌-----+-----┬-----┬-----┬-----┬-----┬-----┬-----┬-----┬-----┬-----┬-----┐
	 *  │ F13 │ F14 | F15 │ F16 │ F17 │ F18 │ F19 │ F20 │ F21 │ F22 │ F23 │ F24 │
	 *  ├-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┤
	 *  │     │  &  │  |  │  "  │  '  │  !  │  !  │  '  │  "  │  |  │  &  │Bkspc│
	 *  ├-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┤
	 *  │     │  <  │  {  │  (  │  [  │  =  │  =  │  ]  │  )  │  }  │  >  │  '  │
	 *  ├-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┤
	 *  │     │  -  │  +  │  /  │  *  │  \  │  \  │  *  │  /  │  +  │  -  │     │
	 *  ├-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┤
	 *  │     │     │     │     │     │ Spc |Bkspc│>> <<│     │     │     │     │
	 *  └-----+-----┴-----┴-----┴-----┴-----┴-----┴-----┴-----┴-----┴-----┴-----┘
	 */
[_RAISE] = LAYOUT_preonic_grid( \
		KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_F21,  KC_F22,  KC_F23,  KC_F24,  \
		_______, KC_AMPR, KC_PIPE, KC_DQUO, KC_QUOT, KC_EXLM, KC_EXLM, KC_QUOT, KC_DQUO, KC_PIPE, KC_AMPR, KC_BSPC, \
		_______, KC_LT,   KC_LCBR, KC_LPRN, KC_LBRC, KC_EQL,  KC_EQL,  KC_RBRC, KC_RPRN, KC_RCBR, KC_GT,   KC_QUOT, \
		_______, KC_MINS, KC_PLUS, KC_SLSH, KC_ASTR, KC_BSLS, KC_BSLS, KC_ASTR, KC_SLSH, KC_PLUS, KC_MINS, _______, \
		_______, _______, _______, _______, _______, KC_SPC,  KC_BSPC, _______, _______, _______, _______, _______  \
	),

/* Common programming symbols. (SUPER RAISE)

	 *  ┌-----+-----┬-----┬-----┬-----┬-----┬-----┬-----┬-----┬-----┬-----┬-----┐
	 *  │     │     |  {} │     │  [] │  :: │ ::  │ []  │     │ {}  │     │     │
	 *  ├-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┤
	 *  │     │  && │  || │  -> │  => │ !=  │ !== │ =>  │ ->  │ ||  │ &&  │     │
	 *  ├-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┤
	 *  │     │open/│  // │  <= │  >= │ ==  │ === │ >=  │ <=  │ //  │clos/│     │ 
	 *  ├-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┤
	 *  │     │     │     │     │     │     │     │     │     │     │     │     │
	 *  ├-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┤
	 *  │     │     │     │     │     │     |     │     │>> <<│     │     │     │
	 *  └-----+-----┴-----┴-----┴-----┴-----┴-----┴-----┴-----┴-----┴-----┴-----┘
	 */
[_SUPER_RAISE] = LAYOUT_preonic_grid( \
		_______, _______,                         MACRO_OPEN_CLOSE_CURLY,    _______,             MACRO_OPEN_CLOSE_SQUARE, MACRO_DOUBLE_COLON,   MACRO_DOUBLE_COLON,   MACRO_OPEN_CLOSE_SQUARE, _______,             MACRO_OPEN_CLOSE_CURLY, _______,                         _______, \
		_______, MACRO_DOUBLE_AND,                MACRO_DOUBLE_OR,           MACRO_SKINNY_ARROW,  MACRO_THICK_ARROW,       MACRO_DOUBLE_UNEQUAL, MACRO_TRIPLE_UNEQUAL, MACRO_THICK_ARROW,       MACRO_SKINNY_ARROW,  MACRO_DOUBLE_OR,        MACRO_DOUBLE_AND,                _______, \
		_______, MACRO_OPENING_MULTILINE_COMMENT, MACRO_C_STYLE_COMMENT,     MACRO_LESS_OR_EQUAL, MACRO_GREATER_OR_EQUAL,  MACRO_DOUBLE_EQUAL,   MACRO_TRIPLE_EQUAL,   MACRO_GREATER_OR_EQUAL,  MACRO_LESS_OR_EQUAL, MACRO_C_STYLE_COMMENT,  MACRO_CLOSING_MULTILINE_COMMENT, _______, \
		_______, _______,                         _______,                   _______,             _______,                 _______,              _______,              _______,                 _______,             _______,                _______,                         _______, \
		_______, _______,                         _______,                   _______,             _______,                 _______,              _______,              _______,                 _______,             _______,                _______,                         _______  \
	),

/* Navigation. (;)
	 *
	 *  ┌-----+-----┬-----┬-----┬-----┬-----┬-----┬-----┬-----┬-----┬-----┬-----┐
	 *  │     │     │     │     │     │     │     │     │     │     │     │     │
	 *  ├-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┤
	 *  │     │     │     │     │     │     │     │     │     │     │     │     │
	 *  ├-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┤
	 *  │     │     │Home │PgUp │PgDn │ End │  ←  │  ↓  │  ↑  │  →  │>> <<│     │
	 *  ├-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┼-----┤
	 *  │     │     │     │     │     │     │     │     │     │     │     │     │
	 *  ├-----┼-----┼-----┼-----┼-----┼-----┴-----┼-----┼-----┼-----┼-----┼-----┤
	 *  │     │     │     │     │     │           │     │     │     │     │     │
	 *  └-----┴-----┴-----┴-----┴-----┴-----------┴-----┴-----┴-----┴-----┴-----┘
	 */
	[NAV_LAYER] = LAYOUT_preonic_grid( \
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                _______, \
		___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___,                ___x___, \
		_______, ___x___, KC_HOME, KC_PGUP, KC_PGDN, KC_END,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, LT(NAV_LAYER, KC_SCLN), _______, \
		_______, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, ___x___,                _______, \
		_______, _______, _______, _______, ___x___, ___x___, ___x___, ___x___, _______, _______, _______,                _______  \
	),

/* Reset, standard backspace/delete block, MIDI CCs 50-57 as 'tap buttons'. (LOWER + RAISE)

 * ,-----------------------------------------------------------------------------------.
 * |Reset |      |      |      |      |      |      |      |      |      |      | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      | CC50 |      |      | CC51 |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      | CC50 | CC51 | CC52 | CC53 |      |      | CC54 | CC55 | CC56 | CC57 |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      | >><< |             | >><< |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_preonic_grid( \
	RESET,   _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, KC_DEL, \
	_______, _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, KC_BSPC,  \
	_______, _______, _______,  _______, MCC_50,  _______, _______, MCC_51,  _______, _______, _______, _______, \
	_______, MCC_50,  MCC_51,  MCC_52,  MCC_53,  _______, _______, MCC_54,  MCC_55,  MCC_56,  MCC_57,  _______, \
	_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
),

/* Numpad, media control, desktop and window control.

 * ,-----------------------------------------------------------------------------------.
 * |      |<- Win|v Win |^ Win | Win->|      |      | Num  |  /   |  *   |  -   | Vol+ |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | >><< |<-Dsk |DskMan| Dsk->|      |      |      |  7   |  8   |  9   |  +   | Vol- |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |PrvWin|NxtWin|      |      |  4   |  5   |  6   |  +   | Mute |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |  1   |  2   |  3   |Enter | Prev |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |PlyTgl| Stop |  0   |  0   |  .   |Enter | Next |
 * `-----------------------------------------------------------------------------------'
 */
[_NUMPAD] = LAYOUT_preonic_grid( \
	___x___,             WINLEFT, WINDOWN, WINUP,   WINRGHT, ___x___, ___x___, KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS, KC_VOLU, \
	LT(_NUMPAD, KC_TAB), LEFTDSK, DESKMAN, RGHTDSK, ___x___, ___x___, ___x___, KC_P7,   KC_P8,   KC_P9,   KC_PPLS, KC_VOLD,  \
	___x___,             ___x___, ___x___, PREVWIN, NEXTWIN, ___x___, ___x___, KC_P4,   KC_P5,   KC_P6,   KC_PPLS, KC_MUTE, \
	___x___,             ___x___, ___x___, ___x___, ___x___, ___x___, ___x___, KC_P1,   KC_P2,   KC_P3,   KC_PENT, KC_MPRV, \
	___x___,             ___x___, ___x___, ___x___, ___x___, KC_MPLY, KC_MSTP, KC_P0,   KC_P0,   KC_PDOT, KC_PENT, KC_MNXT  \
)


};

#ifdef AUDIO_ENABLE

	float my_song[][2] = SONG(ZELDA_PUZZLE);
	float my_song_2[][2] = SONG(ZELDA_TREASURE);

#endif

void cc_button_press(uint8_t cc) {
	midi_send_cc(&midi_device, 0, cc, 127);
	midi_send_cc(&midi_device, 0, cc, 0);
}

void send_cc_if_pressed(uint8_t cc, keyrecord_t *record) {
	if(record->event.pressed) {
		cc_button_press(cc);
	}
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
				case MCC_50:
					send_cc_if_pressed(50, record);
					return false;
					break;
				case MCC_51:
					send_cc_if_pressed(51, record);
					return false;
					break;
				case MCC_52:
					send_cc_if_pressed(52, record);
					return false;
					break;
				case MCC_53:
					send_cc_if_pressed(53, record);
					return false;
					break;
				case MCC_54:
					send_cc_if_pressed(54, record);
					return false;
					break;
				case MCC_55:
					send_cc_if_pressed(55, record);
					return false;
					break;
				case MCC_56:
					send_cc_if_pressed(56, record);
					return false;
					break;
				case MCC_57:
					send_cc_if_pressed(57, record);
					return false;
					break;
				case QWERTY:
					if (record->event.pressed) {
						set_single_persistent_default_layer(_QWERTY);
					}
					return false;
					break;
				case LOWER:
					if (record->event.pressed) {
						layer_on(_LOWER);
						update_tri_layer(_LOWER, _RAISE, _ADJUST);
					} else {
						layer_off(_LOWER);
						update_tri_layer(_LOWER, _RAISE, _ADJUST);
					}
					return false;
					break;
				case RAISE:
					if (record->event.pressed) {
						layer_on(_RAISE);
						update_tri_layer(_LOWER, _RAISE, _ADJUST);
					} else {
						layer_off(_RAISE);
						update_tri_layer(_LOWER, _RAISE, _ADJUST);
					}
					return false;
					break;
				case RAISE2:
					if (record->event.pressed) {
						#ifdef AUDIO_ENABLE
							PLAY_SONG(my_song);
						#endif
						layer_on(_SUPER_RAISE);
					} else {
						layer_off(_SUPER_RAISE);
					}
					return false;
					break;
				case LOWER2:
					if (record->event.pressed) {
						#ifdef AUDIO_ENABLE
							PLAY_SONG(my_song_2);
						#endif
						layer_on(_SUPER_LOWER);
					} else {
						layer_off(_SUPER_LOWER);
					}
					return false;
					break;
				case MACRO_OPEN_CLOSE_CURLY:
					if(record->event.pressed) { SEND_STRING("{}"); }
					return false;
					break;
				case MACRO_OPEN_CLOSE_SQUARE:
					if(record->event.pressed) { SEND_STRING("[]"); }
					return false;
					break;
				case MACRO_DOUBLE_COLON:
					if(record->event.pressed) { SEND_STRING("::"); }
					return false;
					break;
				case MACRO_DOUBLE_AND:
					if(record->event.pressed) { SEND_STRING("&&"); }
					return false;
					break;
				case MACRO_DOUBLE_OR:
					if(record->event.pressed) { SEND_STRING("||"); }
					return false;
					break;
				case MACRO_SKINNY_ARROW:
					if(record->event.pressed) { SEND_STRING("->"); }
					return false;
					break;
				case MACRO_THICK_ARROW:
					if(record->event.pressed) { SEND_STRING("=>"); }
					return false;
					break;
				case MACRO_DOUBLE_UNEQUAL:
					if(record->event.pressed) { SEND_STRING("!="); }
					return false;
					break;
				case MACRO_DOUBLE_EQUAL:
					if(record->event.pressed) { SEND_STRING("=="); }
					return false;
					break;
				case MACRO_TRIPLE_UNEQUAL:
					if(record->event.pressed) { SEND_STRING("!=="); }
					return false;
					break;
				case MACRO_TRIPLE_EQUAL:
					if(record->event.pressed) { SEND_STRING("==="); }
					return false;
					break;
				case MACRO_OPENING_MULTILINE_COMMENT:
					if(record->event.pressed) { SEND_STRING("/*"); }
					return false;
					break;
				case MACRO_CLOSING_MULTILINE_COMMENT:
					if(record->event.pressed) { SEND_STRING("*/"); }
					return false;
					break;
				case MACRO_C_STYLE_COMMENT:
					if(record->event.pressed) { SEND_STRING("//"); }
					return false;
					break;
				case MACRO_LESS_OR_EQUAL:
					if(record->event.pressed) { SEND_STRING("<="); }
					return false;
					break;
				case MACRO_GREATER_OR_EQUAL:
					if(record->event.pressed) { SEND_STRING(">="); }
					return false;
					break;
			}
	return true;
};
