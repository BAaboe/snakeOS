#include <stddef.h>
#include <stdint.h>

#include "font.h"
#include "drivers/vga.h"

void putchar(int x, int y, char letter, uint8_t color){
	uint8_t* where = ((uint8_t*)VRAM) + PITCH*y + x;
	const uint8_t* letter_bitmap; 
	letter_bitmap = FONT[letter];
	for (size_t i=0; i<8; i++){
		for (size_t j=0; j<8; j++){
			if (letter_bitmap[i]&(1<<j)){
				where[j] = color;
			}
		}
		where += PITCH;
	}
}


void putstring(int x, int y, char* string, uint8_t color){
	while (*(string)) {
		putchar(x, y, *string, color);
		x += 8;
		string++;
	}
}

void puthexb(int x, int y, uint8_t hex, uint8_t color) {
	char hex_str[5] = "0x00\0";

	char asci_code = hex/0x10 + '0';
	asci_code += 7*(asci_code/58);
	hex_str[2] = asci_code;
	
	asci_code = hex%0x10 + '0';
	asci_code += 7*(asci_code/58);
	hex_str[3] = asci_code;

	putstring(x, y, hex_str, color);
}
