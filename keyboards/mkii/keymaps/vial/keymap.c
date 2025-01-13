// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[0] = LAYOUT_h(
        KC_F8 , KC_F9 , KC_F10 , KC_F11 , KC_F12,
        KC_F13 , KC_F14,
        KC_F15 , KC_F16,
        KC_F17 , KC_F18,
        KC_F1 , KC_F2,
        KC_F3 , KC_F4  
    )
};

const uint16_t PROGMEM encoder_map[][4][2] = {
 [0] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
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

#include "analog.h"


static uint8_t last_midi_values[4] = {0, 0, 0, 0};
static const uint8_t threshold = 2; // Define a threshold to filter out minor fluctuations

void matrix_scan_user(void) {
    uint16_t pot_values[4];
    uint8_t midi_values[4];

    // Read analog values from four potentiometers
    pot_values[0] = analogReadPin(GP26); // Replace F4 with your analog pin
    pot_values[1] = analogReadPin(GP27); // Replace F5 with your analog pin
    pot_values[2] = analogReadPin(GP28); // Replace F6 with your analog pin
    pot_values[3] = analogReadPin(GP29); // Replace F7 with your analog pin

    // Scale 10-bit ADC to 7-bit MIDI
    for (int i = 0; i < 4; i++) {
        midi_values[i] = (pot_values[i] * 127) / 1023;
    }

    // Send MIDI CC commands if values have changed significantly
    for (int i = 0; i < 4; i++) {
        if (abs(midi_values[i] - last_midi_values[i]) > threshold) {
            midi_send_cc(&midi_device, 0, i + 1, midi_values[i]); // Send MIDI CC command
            last_midi_values[i] = midi_values[i]; // Update the last value
        }
    }
}




