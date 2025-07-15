#include "printing.h"

void de(){
	putstring(0, 0, "Division by zero", 0x28);
}
void of(){
	putstring(0, 0, "Overflow", 0x28);
}
void np(){
	putstring(0, 0, "Segment not present", 0x28);
}
void sse(){
	putstring(0, 0, "Stack-Segment Fault", 0x28);
}
void df(){
	putstring(0, 0, "Double Fault", 0x28);
}

void ac(){
	putstring(0, 0, "Alignment Check", 0x28);
}

void cp(){
	putstring(0, 0, "Control Protection Exeception", 0x28);
}

void other_error(){
	putstring(0, 0, "Other error", 0x28);
}
