#ifndef PRINTING_H
#define PRINTING_H
#include <stdint.h>

void putchar(int x, int y, char letter, uint8_t color);
void putstring(int x, int y, char* string, uint8_t color);
void puthexb(int x, int y, uint8_t hex, uint8_t color);

#endif // !PRINTING_H
