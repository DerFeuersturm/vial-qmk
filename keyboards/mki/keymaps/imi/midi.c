#include "midi.h"

MidiDevice midi_device; // Define the MIDI device

void midi_send_cc(MidiDevice* device, uint8_t chan, uint8_t num, uint8_t val) {
    midi_send(0xB0 | (chan & 0x0F)); // Control Change message
    midi_send(num & 0x7F);           // CC number
    midi_send(val & 0x7F);           // CC value
}