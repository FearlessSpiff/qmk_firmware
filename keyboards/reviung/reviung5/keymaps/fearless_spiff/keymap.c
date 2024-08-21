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
enum layer_names { _BASE };

enum custom_keycodes { JIG };
enum next_action { UP_DOWN, LEFT_RIGHT };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(JIG, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE)};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code_delay(KC_VOLD, 10);
        } else {
            tap_code_delay(KC_VOLU, 10);
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
                    jig_mode = false;
                    // rgblight_setrgb(RGB_PURPLE);
                    rgblight_disable();
                } else {
                    jig_mode = true;
                    rgblight_enable();
                    rgblight_mode(1);
                    rgblight_setrgb(RGB_RED);
                }
            }
            break;
    }
    return true;
}

int randomMs(int min, int max) {
    return rand() % (max - min + 1) + min;
}

enum next_action nextAction   = UP_DOWN;
int              sleepCounter = 0;
int              sleepTo      = 10000;

void matrix_scan_user(void) {
    if (jig_mode) {
        if (sleepCounter >= sleepTo && nextAction == UP_DOWN) {
            tap_code(KC_MS_UP);
            tap_code(KC_MS_DOWN);
            nextAction   = LEFT_RIGHT;
            sleepCounter = 0;
            sleepTo      = randomMs(10000, 30000);
        } else if (sleepCounter >= sleepTo && nextAction == LEFT_RIGHT) {
            tap_code(KC_MS_LEFT);
            tap_code(KC_MS_RIGHT);
            nextAction   = UP_DOWN;
            sleepCounter = 0;
            sleepTo      = randomMs(10000, 30000);
        } else {
            SEND_STRING(SS_DELAY(1));
            sleepCounter++;
        }
    }
}
