#define VIDEO_MEMORY 0xb8000

void print_vga(char* buffer){
	char* vid_buffer = (char*)VIDEO_MEMORY;
	while(*buffer){
		*vid_buffer++ = *buffer++;
		*vid_buffer++ = 0x0e;
	}
}

void main(){
	char* t = "Benjamin er insane!!";
	print_vga(t);

}
