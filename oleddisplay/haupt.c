#include "global.h"

int main(void) {
	wdt_disable();

	char uart_field[35] = { 0 };
	uint8_t update = 0;

	DDRC |= (1 << PC3 | 1 << PC4);

	PORTC |= 1 << PC3;
	_delay_ms(1000);
	PORTC &= ~(1 << PC3);

	uart_init(9600);
	oled_init();
	oled_display_clear();

	oled_draw_rectangle(0, 0, 36, 24);

	oled_send(0x00, 0); // low col
	oled_send(0x10, 0); // hi col
	oled_send(0xB0, 0); // Page

	oled_send(0xAE, 0); // DISPLAY OFF
	oled_read(1);
	oled_send(0xAF, 0); // DISPLAY OFF
	oled_read(1);

	while (1) {
		if ((UCSR0A & (1 << RXC0)) && 1) {
			PORTC |= 1 << PC4;
			uart_gets(uart_field);
			update = 1;
			PORTC &= ~(1 << PC4);
		}

		if(update) {
			oled_display_clear();
			oled_puts(uart_field, 1, 1);
			update = 0;
		}

		if (uart_strings_equal("kill", uart_field)) {
			wdt_enable(4);
			while (1)
				;
		}
	}
	return 0;
}
