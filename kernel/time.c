#define MS_PER_TICK 54.9254

static volatile int tick = 0;

void time_tick(){
	tick++;
}

int get_tick(){
	return tick;
}

float get_time(){
	return tick*MS_PER_TICK;
}

void wait(int ms) {
	int time = get_time();
	while(get_time()-time < ms);
}
