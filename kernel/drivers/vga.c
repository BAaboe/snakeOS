#include <stddef.h>

#include "drivers/vga.h"
#include "font.h"


void vga_fill_rect(unsigned char* where, unsigned char w, unsigned char h, unsigned char c){
	for (int i=0; i<h; i++){
		for (int j=0; j<w; j++){
			where[j] = c;
		}
		where += PITCH;
	}
}

void vga_fill_screen(unsigned char color){
	unsigned char* vram = (unsigned char*)VRAM;
	for (int y=0; y<HEIGHT; y++){
		for (int x=0; x<WIDTH; x++){
			vram[PITCH*y + x] = color;
		}
	}
}
