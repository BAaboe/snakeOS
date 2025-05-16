#include <stddef.h>

#include "font.h"
#include "drivers/vga.h"

void putchar(int x, int y, char letter, unsigned char color){
	unsigned char* where = ((unsigned char*)VRAM) + PITCH*y + x;
	const unsigned char* letter_bitmap; 
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


void putstring(int x, int y, char* string, unsigned char color){
	while (*(string)) {
		putchar(x, y, *string, color);
		x += 8;
		string++;
	}
}
