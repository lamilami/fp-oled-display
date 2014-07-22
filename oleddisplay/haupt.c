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

	oled_draw_rectangle(2, 2, 38, 26);
	oled_draw_rectangle(6, 6, 50, 36);
	oled_draw_rectangle(4, 4, 42, 16);
	oled_puts("FP", 2, 4);

	oled_display();

	while (1) {
		if ((UCSR0A & (1 << RXC0)) && 1) {
			PORTC |= 1 << PC4;
			uart_gets(uart_field);
			update = 1;
			PORTC &= ~(1 << PC4);
		}

		if(update) {
			oled_puts(uart_field, 5, 3);
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
