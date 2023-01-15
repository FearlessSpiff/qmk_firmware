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
    _SET = 5,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEF] = LAYOUT(
        DE_J, DE_L,        DE_U,        DE_A,        DE_Q,        DE_W, DE_B,        DE_D,        DE_G,         DE_Z,
        DE_C, ALT_T(DE_R), CTL_T(DE_I), SFT_T(DE_E), DE_O,        DE_M, SFT_T(DE_N), CTL_T(DE_T), ALGR_T(DE_S), DE_H,
        DE_V, DE_X,        DE_UDIA,     DE_ADIA,     DE_ODIA,     DE_P, DE_F,        DE_COMM,     DE_DOT,       DE_K,
                                        DE_P,        DE_Q,        DE_Q, DE_P
    )
};
