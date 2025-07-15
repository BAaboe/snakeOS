#include "printing.h"
#include "util.h"
#include "keyboard.h"
#include <stdint.h>


static Scan_Code latest_key_press = {0, 0};
static Scan_Code latest_key_release = {0, 0};

static Latest_Key_Change latest_key_change = {&latest_key_press, &latest_key_release};

static uint8_t extended_byte = 0;


void handle_keyboad_interupt(){
	uint8_t scan_code = inb(0x60);

	if (extended_byte) {
		if (scan_code >= 0xB0){
			latest_key_release.extended_byte = 1;
			latest_key_release.scan_code = scan_code;
		} else {
			latest_key_press.extended_byte = 1;
			latest_key_press.scan_code = scan_code;
		}
		extended_byte = 0;
	} else {
		if (scan_code == 0xE0) {
			extended_byte = 1;
		} else {
			if (scan_code >= 0x81){
				latest_key_release.extended_byte = 1;
				latest_key_release.scan_code = scan_code;
			} else {
				latest_key_press.extended_byte = 1;
				latest_key_press.scan_code = scan_code;
			}

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
