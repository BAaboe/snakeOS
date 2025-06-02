#include "drivers/vga.h"
#include "printing.h"
#include "time.h"


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
	int x, y = 0;

	make_board();
	unsigned char* where = (unsigned char*)(VRAM) + y*PITCH + x;
	vga_fill_rect(where, 10, 10, 0x0a);

	float time = get_time();

	while(1){
		float ntime = get_time();
		if(ntime-time > 1000){
			time = ntime;
			x+=10;
			y+=(x/WIDTH)*10;
			x%=WIDTH;
			make_board();
			unsigned char* where = (unsigned char*)(VRAM) + y*PITCH + x;
			vga_fill_rect(where, 10, 10, 0x0a);
		}
	}
}

void handle_pic(){
	putstring(0, 0, "PIC", 0x0a);
	return;
}
