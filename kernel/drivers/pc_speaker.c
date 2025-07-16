#include "util.h"
#include "pc_speaker.h"
#include "time.h"

void play_sound(uint32_t freq) {
	// Set frequency
	uint32_t div = 1193180 / freq;
	outb(0x43, 0xb6);
	outb(0x42, (uint8_t)div);
	outb(0x42, (uint8_t)(div>>8));

	// Start speaker
	uint8_t in = inb(0x61);
	outb(0x61, in | 3);
}

void stop_sound() {
	uint8_t in = inb(0x61);
	outb(0x61, in & 0xFC);
}

void beep() {
	play_sound(600);
	wait(10);
	stop_sound();
}
