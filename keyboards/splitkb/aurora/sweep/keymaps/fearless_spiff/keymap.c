/* Copyright 2022 splitkb.com <support@splitkb.com>
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
#include "keymap_german.h"


enum layers {
    _DEF = 0,
    _NAV = 1,
    _SYM = 2,
    _NUM = 3,
    _FN  = 4,
    _SET = 5
};


enum custom_keycodes {
    M_LCK    = SAFE_RANGE,
    M_GO_SRC,
    M_RUN
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case M_LCK:
        if (record->event.pressed) {
            SEND_STRING(SS_LGUI("L"));
        }
        break;
    case M_GO_SRC:
        if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_F1) SS_UP(X_LALT) SS_DELAY(2000) SS_TAP(X_RETN));
        }
        break;
    case M_RUN:
        if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_LALT) SS_DOWN(X_LSFT) SS_TAP(X_F10) SS_UP(X_LSFT) SS_UP(X_LALT));
        }
        break;
    }
    return true;
};


enum combos {
  C_TAB,
  C_RETN,
  C_GUI
};

const uint16_t PROGMEM tab_combo[]  = {DE_J, LT(_NAV, DE_C), COMBO_END};
const uint16_t PROGMEM retn_combo[] = {DE_H, DE_K, COMBO_END};
const uint16_t PROGMEM gui_combo[]  = {MO(_NUM), KC_LSFT, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  [C_TAB] = COMBO(tab_combo, KC_TAB),
  [C_RETN] = COMBO(retn_combo, KC_RETN),
  [C_GUI] = COMBO(gui_combo, KC_LGUI)
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEF] = LAYOUT(
        DE_J,           DE_L,        DE_U,        DE_A,        DE_Q,              DE_W,             DE_B,        DE_D,        DE_G,         DE_Z,
        LT(_NAV, DE_C), ALT_T(DE_R), CTL_T(DE_I), SFT_T(DE_E), DE_O,              DE_M,             SFT_T(DE_N), CTL_T(DE_T), ALGR_T(DE_S), DE_H,
        DE_V,           DE_X,        DE_UDIA,     DE_ADIA,     DE_ODIA,           DE_P,             DE_F,        DE_COMM,     DE_DOT,       DE_K,
                                                  MO(_NUM),    KC_LSFT,           LT(_SYM, KC_SPC), KC_BSPC
    ),
    [_NAV] = LAYOUT(
        KC_ESC,  M_LCK,   M_RUN,   M_GO_SRC, _______,          KC_PGUP, KC_HOME, KC_UP,   KC_END,   DE_Y,
        _______, _______, _______, _______,  _______,          KC_PGDN, KC_LEFT, KC_DOWN, KC_RIGHT, KC_RETN,
        KC_LSFT, _______, _______, _______,  _______,          _______, _______, _______, _______,  DE_SS,
                                   _______,  _______,          _______, KC_DEL
    ),
    [_SYM] = LAYOUT(
        DE_CIRC, DE_UNDS, DE_LCBR, DE_RCBR,        DE_SECT,        DE_EXLM, DE_LABK,        DE_RABK, DE_EQL,  DE_AMPR,
        DE_BSLS, DE_SLSH, DE_LPRN, SFT_T(DE_RPRN), DE_ASTR,        DE_QUES, SFT_T(DE_LBRC), DE_RBRC, DE_MINS, DE_COLN,
        DE_ACUT, DE_DLR,  DE_PIPE, DE_TILD,        DE_HASH,        DE_PLUS, DE_PERC,        DE_DQUO, DE_QUOT, DE_SCLN,
                                   _______,        _______,        _______,  _______
    ),
    [_NUM] = LAYOUT(
        _______,       _______,       _______,       MO(_SET),      _______,          DE_SLSH, KC_7, KC_8, KC_9, DE_MINS,
        OSM(MOD_LGUI), OSM(MOD_LALT), OSM(MOD_LCTL), OSM(MOD_LSFT), _______,          DE_ASTR, KC_4, KC_5, KC_6, DE_PLUS,
        _______,       _______,       _______,       MO(_FN),       _______,          DE_SCLN, KC_1, KC_2, KC_3, KC_0,
                                                     _______,       _______,          DE_COLN, DE_DOT
    ),
    [_FN] = LAYOUT(
        _______, _______, _______, _______, _______,          _______, KC_F7, KC_F8, KC_F9, _______,
        _______, _______, _______, _______, _______,          _______, KC_F4, KC_F5, KC_F6, _______,
        _______, _______, _______, _______, _______,          _______, KC_F1, KC_F2, KC_F3, KC_F10,
                                   _______, _______,          KC_F11,  KC_F12
    ),
    [_SET] = LAYOUT(
        _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______,
        QK_RBT,  QK_BOOT, _______, _______, _______,          _______, _______, _______, _______, _______,
                                   _______, _______,          _______, _______
    )
};
