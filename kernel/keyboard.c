#include "printing.h"
#include "util.h"
#include "keyboard.h"
#include <stdint.h>


static Scan_Code latest_key_press = {0, 0};
static Scan_Code latest_key_release = {0, 0};
static Scan_Code latest_key_press_or_release = {0, 0};

static Latest_Key_Change latest_key_change = {&latest_key_press, &latest_key_release, &latest_key_press_or_release};

static uint8_t extended_byte = 0;

void init_keybord() {
	uint8_t status;
	while(1){
		outb(0x60, 0xF0);
		io_wait();
		outb(0x60, 2);
		io_wait();
		status = inb(0x60);
		if(status != 0xfe) break;
	}
	status = inb(0x60);
	puthexb(0, 0, status, 0x0e);
}
void handle_keyboad_interupt(){
	uint8_t scan_code = inb(0x60);

	if (extended_byte) {
		if (scan_code >= 0xB0){
			latest_key_release.extended_byte = 1;
			latest_key_release.scan_code = scan_code;
			latest_key_press_or_release = latest_key_release;
		} else {
			latest_key_press.extended_byte = 1;
			latest_key_press.scan_code = scan_code;
			latest_key_press_or_release = latest_key_press;
		}
		extended_byte = 0;
	} else {
		if (scan_code == 0xE0) {
			extended_byte = 1;
		} else {
			if (scan_code >= 0x81){
				latest_key_release.extended_byte = 0;
				latest_key_release.scan_code = scan_code;
				latest_key_press_or_release = latest_key_release;
			} else {
				latest_key_press.extended_byte = 0;
				latest_key_press.scan_code = scan_code;
				latest_key_press_or_release = latest_key_press;
			}

		}

		// Real Hardware

		if (extended_byte) {
			
		}
	}


	// char scan_code_str[4] = "0x00";

	// scan_code_str[2] = scan_code/0x10+'0';
	// scan_code_str[3] = scan_code%0x10+'0';
	// putstring(0, 0, scan_code_str, 0x0a);
}

Latest_Key_Change* get_latest_key_change(){
	return &latest_key_change;
}
