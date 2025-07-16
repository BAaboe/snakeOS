#include "drivers/vga.h"
#include "printing.h"
#include "time.h"
#include "util.h"
#include "keyboard.h"
#include "drivers/pc_speaker.h"
#include <stdint.h>

#define BOX_SIZE 10
#define MAX_NUM_PARTS HEIGHT/BOX_SIZE*WIDTH/BOX_SIZE

typedef enum direction {
	UP,
	DOWN,
	LEFT,
	RIGHT,
} direction_t;

typedef struct {
	uint16_t x;
	uint16_t y;
} snake_part;

void handle_input(direction_t* direction){
	Latest_Key_Change* latest_key_change = get_latest_key_change();
	if (latest_key_change->pressed->extended_byte) {
		switch (latest_key_change->pressed->scan_code) {
			case 0x48:
				if (*direction != DOWN) *direction = UP;
				break;
			case 0x4B:
				if (*direction != RIGHT) *direction = LEFT;
				break;
			case 0x4D:
				if (*direction != LEFT) *direction = RIGHT;
				break;
			case 0x50:
				if (*direction != UP) *direction = DOWN;
				break;
			default:
				break;

		}
	}	
}

static void make_board(){
	for (int y=0; y<HEIGHT; y+=BOX_SIZE){
		for (int x=0; x<WIDTH; x+=BOX_SIZE){
			uint8_t color = 0x07;
			color += ((y/BOX_SIZE + x/BOX_SIZE)%2)*0x10;

			color = 0x01;
			
			uint8_t* where = (uint8_t*)(VRAM) + y*PITCH + x;
			vga_fill_rect(where, BOX_SIZE, BOX_SIZE, color);
		}
	}
}

uint16_t game_loop(snake_part* apple, snake_part* parts) {
	srand(get_time());
	direction_t direction = RIGHT;

	for(int i = 0; i < MAX_NUM_PARTS+1; i++){
		snake_part part = {0, 0};
		parts[i] = part;
	}

	int num_parts = 1;

	apple->x = (rand()%(WIDTH/BOX_SIZE))*BOX_SIZE;
	apple->y = (rand()%(HEIGHT/BOX_SIZE))*BOX_SIZE;

	make_board();

	float time = get_time();

	uint8_t lost = 0;

	while(!lost){
		float ntime = get_time();
		if(ntime-time > 250){
			time = ntime;

			make_board();

			//Movement and drawing of the snake body
			handle_input(&direction);
			
			for(int i = num_parts-1; i > 0; i--){
				parts[i].x = parts[i-1].x;
				parts[i].y = parts[i-1].y;

				uint8_t* where = (uint8_t*)(VRAM) + parts[i].y*PITCH + parts[i].x;
				vga_fill_rect(where, BOX_SIZE, BOX_SIZE, 0x0a);
			}

			switch (direction) {
				case UP:
					parts[0].y -= BOX_SIZE;
					break;
				case DOWN:
					parts[0].y += BOX_SIZE;
					break;
				case LEFT:
					parts[0].x -= BOX_SIZE;
					break;
				case RIGHT:
					parts[0].x += BOX_SIZE;
					break;
			}

			// Colision detection
			if(parts[0].x == apple->x && parts[0].y == apple->y) {
				beep();
				num_parts++;
				apple->x = (rand()%(WIDTH/BOX_SIZE))*BOX_SIZE;
				apple->y = (rand()%(HEIGHT/BOX_SIZE))*BOX_SIZE;
			}

			for(int i = 1; i<num_parts; i++){
				if(parts[0].x == parts[i].x && parts[0].y == parts[i].y) {
					lost = 1;
					break;
				}
			}

			if (parts[0].x < 0 || parts[0].x >= WIDTH || parts[0].y < 0 || parts[0].y >= HEIGHT) {
				lost = 1;
				break;
			}

			// Drawing

			uint8_t* where = (uint8_t*)(VRAM) + parts[0].y*PITCH + parts[0].x;
			vga_fill_rect(where, BOX_SIZE, BOX_SIZE, 0x0a);

			where = (uint8_t*)(VRAM) + apple->y*PITCH + apple->x;
			vga_fill_rect(where, BOX_SIZE, BOX_SIZE, 0x28);

			int score = num_parts-1;
			char* str_score = "Score: 000";

			str_score[7] = score/100 + '0';
			score -= 100*(score/100);

			str_score[8] = score/10 + '0';
			score -= 10*(score/10);

			str_score[9] = score + '0';
			
			putstring(WIDTH/2 - 40, 0, str_score, 0x0a);
			
		}
	}

	return num_parts-1;
}

void death_music() {
	play_sound(392);
	wait(20);
	stop_sound();
	wait(50);
	play_sound(392);
	wait(20);
	stop_sound();
	wait(50);
	play_sound(392);
	wait(20);
	stop_sound();
	wait(50);
	play_sound(311);
	wait(500);
	stop_sound();
}

void death(uint16_t score, snake_part* apple, snake_part* parts){
	make_board();

	for(int i = score; i > 0; i--){
		uint8_t* where = (uint8_t*)(VRAM) + parts[i].y*PITCH + parts[i].x;
		vga_fill_rect(where, BOX_SIZE, BOX_SIZE, 0x0a);
	}

	putstring(WIDTH/2-36, HEIGHT/4, "GAME OVER", 0x28);
	char* str_score = "Score: 000";

	str_score[7] = score/100 + '0';
	score -= 100*(score/100);

	str_score[8] = score/10 + '0';
	score -= 10*(score/10);

	str_score[9] = score + '0';
	
	putstring(WIDTH/2 - 40, HEIGHT/3, str_score, 0x0a);
	
	death_music();


	while (1) {
		Latest_Key_Change* key_change = get_latest_key_change();
		if (!key_change->pressed->extended_byte && key_change->pressed->scan_code == 0x1C) {
			beep();
			return;
		}
	}
}

void start_screen() {
	make_board();
	putstring(WIDTH/2 - 20, HEIGHT/4, "SNAKE", 0x0a);
	putstring(WIDTH/2 - 80, HEIGHT/3 , "PRESS ENTER TO START", 0x0a);
	while (1) {
		Latest_Key_Change* key_change = get_latest_key_change();
		if (!key_change->pressed->extended_byte && key_change->pressed->scan_code == 0x1C) {
			beep();
			return;
		}
	}
}


void kernel_main(){
	snake_part parts[MAX_NUM_PARTS+1];
	snake_part apple;
	start_screen();
	while (1) {
		

		uint16_t score = game_loop(&apple, parts);

		death(score, &apple, parts);
	}
}



void handle_pic(){
	putstring(0, 0, "PIC", 0x0a);
	return;
}
