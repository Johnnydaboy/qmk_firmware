/* Copyright 2022 ziptyze
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

#include "quantum.h"
#include <stdbool.h>
#include <stdint.h>
#include QMK_KEYBOARD_H
#define SPAM_DELAY 1000

enum layer_names {
    _BASE,
    _FN1,
    _FN2
};

enum custom_keycodes {
    REPEAT_KEY = SAFE_RANGE,
};

bool spam_active = false;
uint32_t spam_timer = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
      case REPEAT_KEY:
        if (record->event.pressed) {
          spam_active = !spam_active;  // Toggle spamming
          spam_timer = timer_read();
        } else {
            // when keycode QMKBEST is released
        }
        break;
    }
    return true;
};

void matrix_scan_user(void) {
  if (spam_active && timer_elapsed(spam_timer) > SPAM_DELAY) {
    SEND_STRING("QMK \b\b\b\b"); // Send 'QMK ' then four backspaces
    spam_timer = timer_read();  // Reset spam timer
  }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    
  [_BASE] = LAYOUT_60_ansi(
    QK_GESC , KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,   KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,   KC_BSPC,
    KC_TAB  , KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,  KC_BSLS,
    MO(_FN1), KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,           KC_ENT,
    KC_LSFT , KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH,                    KC_RSFT,
    KC_LCTL , KC_LGUI, KC_LALT,                            KC_SPC,                            KC_RALT, KC_RGUI, TG(_FN2), KC_RCTL
  ),

  [_FN1] = LAYOUT_60_ansi(
    KC_GRV , KC_F1,   KC_F2  ,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGUP,   KC_UP, KC_PGDN,  KC_PSCR, KC_SCRL, KC_PAUS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT,   KC_INS,  KC_DEL,          KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_END, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,                   KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,                             KC_TRNS, KC_TRNS, KC_TRNS, QK_BOOT
  ),

  [_FN2] = LAYOUT_60_ansi(
    KC_TRNS , TG(REPEAT_KEY),  REPEAT_KEY, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_PGUP,   KC_UP, KC_PGDN,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT,  KC_TRNS, KC_TRNS,          KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,                   KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS,                            KC_TRNS,                             KC_TRNS, KC_TRNS, KC_TRNS, QK_BOOT
  ),
};
