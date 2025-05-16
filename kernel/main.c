#include "drivers/vga.h"


static void make_board(){
	unsigned char box_size = 10;
	for (int y=0; y<HEIGHT; y+=box_size){
		for (int x=0; x<WIDTH; x+=box_size){
			unsigned char color = 0x07;
			color += ((y/box_size + x/box_size)%2)*0x10;
			
			unsigned char* where = (unsigned char*)(VRAM) + y*PITCH + x;
			vga_fill_rect(where, box_size, box_size, color);
		}
	}
}

void kernel_main(){
	//clear_screen();
	make_board();
	//vga_fill_rect(0, 0, 10, 10, 0x07);
	//vga_fill_rect(10, 0, 10, 10, 0x17);
}
