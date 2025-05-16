#ifndef VGA_H
#define VGA_H

#define VRAM 0xA0000

#define HEIGHT 200 // In pixels
#define WIDTH 320 // In pixels
#define PITCH 320 // In bytes
#define DEPTH 8 // In bits
#define PIXELWIDTH 1 // In bytes


void vga_fill_rect(unsigned char* where, unsigned char w, unsigned char h, unsigned char c);

void vga_fill_screen(unsigned char color);

#endif // !VGA_H
