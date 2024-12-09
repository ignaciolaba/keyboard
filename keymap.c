/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "keymap_spanish_latin_america.h"
#include <stdio.h>
#include "handlers.c"
#include "glcdfont.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       ES_TAB,    ES_Q,    ES_W,    ES_E,    ES_R,    ES_T,                         ES_Y,    ES_U,    ES_I,    ES_O,   ES_P,  ES_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      ES_LSFT,    ES_A,    ES_S,    ES_D,    ES_F,    ES_G,                         ES_H,    ES_J,    ES_K,    ES_L, ES_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      ES_LGUI, ES_Z,    ES_X,    ES_C,    ES_V,    ES_B,                           ES_N,    ES_M, ES_COMM,  ES_DOT, ES_MINS,  ES_LALT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          ES_LOPT,   MO(1),  ES_SPC,     ES_ENT,   MO(2), ES_LCTL
                                
                                      //`--------------------------'  `--------------------------'

  ),

  [1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       ES_ESC,    ES_F1,    ES_F2,    ES_F3,    ES_F4,    ES_F5,                 ES_EXLM, ES_LCBR,  ES_UP,  ES_LPRN,  ES_RPRN, ES_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      ES_LSFT, ES_F6   , ES_F7  , ES_F8,   ES_F9,  ES_F10,                      ES_LBRC,  ES_LEFT, ES_DOWN, ES_RIGHT, ES_SCLN, ES_QUES,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      ES_LGUI, ES_F11, ES_F12, XXXXXXX, XXXXXXX, XXXXXXX,                      ES_RBRC, ES_SLSH, ES_EQUAL, ES_PLUS, ES_LABK, ES_RABK,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          ES_LOPT, _______,  ES_SPC,     ES_ENT,   MO(3), ES_LCTL
                                      //`--------------------------'  `--------------------------'
  ),

  [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       ES_ESC, ES_EXLM,   ES_AT, ES_NUMB,  ES_DLR, ES_PERC,                      ES_CIRC, ES_AMPR, ES_ASTR, ES_LPRN, ES_RPRN, ES_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      ES_LSFT, XXXXXXX, XXXXXXX, ES_MUTE, ES_VOLD, ES_VOLU,                      ES_MINS,  ES_EQL, ES_LBRC, ES_RBRC, ES_BSLS,  ES_GRV,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      ES_LCTL, XXXXXXX, XXXXXXX, ES_MPRV, ES_MSTP, ES_MNXT,                      ES_UNDS, ES_PLUS, ES_LCBR, ES_RCBR, ES_PIPE, ES_TILD,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          ES_LOPT,   MO(3),  ES_SPC,     ES_ENT, _______, ES_LCTL
                                      //`--------------------------'  `--------------------------'
  ),

  [3] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        QK_BOOT, RGB_M_K, RGB_M_SN, RGB_M_SW, RGB_M_R, RGB_M_B,                      ES_EQL, ES_7, ES_8, ES_9, ES_PAST, ES_PSLS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, RGB_M_P, RGB_M_X,                      XXXXXXX, ES_4, ES_5, ES_6, ES_PLUS, ES_MINS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_M_G, RGB_M_T,                        ES_0, ES_1, ES_2, ES_3, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          ES_LOPT, _______,  ES_SPC,     ES_ENT, _______, ES_LCTL
                                      //`--------------------------'  `--------------------------'
  )
  
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_accents(keycode, record->event.pressed, record)) {
        return false;
    }

    if (record->event.pressed) {
        uprintf("Key pressed: %u\n", keycode);
    }

    return true;
}


#ifdef OLED_ENABLE
// OLED initialization
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return is_keyboard_master() ? rotation : OLED_ROTATION_180;
}

// Function to render the current layer
void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_ln_P(PSTR("QWERTY"), false);
            break;
        case 1:
            oled_write_ln_P(PSTR("Coding"), false);
            break;
        case 2:
            oled_write_ln_P(PSTR("Numpad"), false);
            break;
        case 3:
            oled_write_ln_P(PSTR("Adjust"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Unknown"), false);
            break;
    }
}

// Main OLED task
bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        oled_write_ln_P(PSTR("Keylog active..."), false);
    } else {
        oled_write_ln_P(PSTR("ILU Display"), false);
    }
    return false;
}
#endif

