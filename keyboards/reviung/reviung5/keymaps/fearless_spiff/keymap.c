/* Copyright 2021 gtips
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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _LOWER,
};

enum custom_keycodes { JIG };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE]  = LAYOUT(TG(_LOWER), KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE),
    [_LOWER] = LAYOUT(_______, RGB_TOG, LCTL(KC_C), LCTL(KC_V), JIG)};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (IS_LAYER_ON(_LOWER)) {
            tap_code16((clockwise == true) ? KC_WH_D : KC_WH_U);
        } else {
            tap_code((clockwise == true) ? KC_VOLD : KC_VOLU);
        }
    }
    return true;
}

bool jig_mode = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case JIG:
            if (record->event.pressed) {
                if (jig_mode) {
                    SEND_STRING(SS_DELAY(15));
                    jig_mode = false;
                    rgblight_setrgb(RGB_PURPLE);
                } else {
                    SEND_STRING(SS_DELAY(15));
                    jig_mode = true;
                    rgblight_setrgb(RGB_RED);
                }
            }
            break;
    }
    return true;
}

void matrix_scan_user(void) {
    if (jig_mode) {
        SEND_STRING(SS_DELAY(10));
        tap_code(KC_MS_UP);
        tap_code(KC_MS_DOWN);
        SEND_STRING(SS_DELAY(30));
        tap_code(KC_MS_LEFT);
        tap_code(KC_MS_RIGHT);
    }
}
