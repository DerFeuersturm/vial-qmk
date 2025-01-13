// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT_h(
        KC_F8 , KC_F9 , KC_F10,
        KC_F11 , KC_F12 , KC_F13 , KC_F14,
        KC_F15 , KC_F16 , KC_F17 , KC_F18 
    )
};

const uint16_t PROGMEM encoder_map[][1][2] = {
 [0] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)}
};

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        
    case 0: 
        rgblight_mode (6);
        break;
    case 1:
        rgblight_mode (1);
        rgblight_setrgb (0x00,  0x00, 0xFF);
        break;
    case 2:
        rgblight_mode (1);
        rgblight_setrgb (0xFF,  0x00, 0xFF);
        break;
    case 3:
        rgblight_mode (1);
        rgblight_setrgb (0x00,  0xFF, 0x00);
        break;

    }
  return state;
};

#include "midi.h"

// CC-Werte in einem Array speichern
uint8_t cc_values[8] = {0}; // 8 Elemente, initialisiert auf 0

extern MidiDevice midi_device; 

enum custom_keycodes {
    CC_1_DEC = QK_KB_0,
    CC_1_INC,
    CC_2_DEC,
    CC_2_INC,
    CC_3_DEC,
    CC_3_INC,
    CC_4_DEC,
    CC_4_INC,
    CC_5_DEC,
    CC_5_INC,
    CC_6_DEC,
    CC_6_INC,
    CC_7_DEC,
    CC_7_INC,
    CC_8_DEC,
    CC_8_INC
};

// Hilfsfunktion zum Verarbeiten von CC-Werten
void adjust_cc(uint8_t index, bool increment) {
    if (index < 8) { // Sicherstellen, dass der Index im Array-Bereich ist
        if (increment && cc_values[index] < 127) {
            cc_values[index]++;
        } else if (!increment && cc_values[index] > 0) {
            cc_values[index]--;
        }
        midi_send_cc(&midi_device, 0, 20 + index, cc_values[index]); // CC-Wert senden
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case CC_1_INC: adjust_cc(0, true); return false;
            case CC_1_DEC: adjust_cc(0, false); return false;
            case CC_2_INC: adjust_cc(1, true); return false;
            case CC_2_DEC: adjust_cc(1, false); return false;
            case CC_3_INC: adjust_cc(2, true); return false;
            case CC_3_DEC: adjust_cc(2, false); return false;
            case CC_4_INC: adjust_cc(3, true); return false;
            case CC_4_DEC: adjust_cc(3, false); return false;
            case CC_5_INC: adjust_cc(4, true); return false;
            case CC_5_DEC: adjust_cc(4, false); return false;
            case CC_6_INC: adjust_cc(5, true); return false;
            case CC_6_DEC: adjust_cc(5, false); return false;
            case CC_7_INC: adjust_cc(6, true); return false;
            case CC_7_DEC: adjust_cc(6, false); return false;
            case CC_8_INC: adjust_cc(7, true); return false;
            case CC_8_DEC: adjust_cc(7, false); return false;
        }
    }
    return true; // Unverarbeitete Keycodes weitergeben
}



