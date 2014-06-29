#include "global.h"

int main(void) {
	oled_init();
	oled_display_clear();
	oled_puts("Test", 1, 1);

	while(1) {

	}
	return 0;
}
