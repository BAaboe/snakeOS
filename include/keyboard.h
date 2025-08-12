#include <stdint.h>

typedef struct Scan_Code {
	uint8_t extended_byte;
	uint8_t scan_code;
} Scan_Code;

typedef struct Latest_Key_Change {
	Scan_Code* pressed;
	Scan_Code* released;
	Scan_Code* last_scan_code;
} Latest_Key_Change;

Latest_Key_Change* get_latest_key_change(void);
void init_keybord();
