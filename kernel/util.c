#include "util.h"
#include <stdint.h>


// Taken from https://wiki.osdev.org/Random_Number_Generator
static unsigned long int next = 1;  // NB: "unsigned long int" is assumed to be 32 bits wide

int rand(void) {
    next = next * 1103515245 + 12345;
    return (unsigned int) (next / 65536) % 32768;
}

void srand(unsigned int seed) {
    next = seed;
}
