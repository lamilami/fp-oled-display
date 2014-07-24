#include "global.h"

int main(void) {
	wdt_disable();

	char uart_field[MAX_ARRAYSIZE+1] = { 0 };
	uint8_t line, col;
	uint8_t update = 0;

	DDRC |= (1 << PC3 | 1 << PC4);

	PORTC |= 1 << PC3;
	_delay_ms(1000);
	PORTC &= ~(1 << PC3);
	_delay_ms(1000);

	uart_init(9600);

	oled_init();
	oled_display_clear();

	oled_puts("Tiger", 2, 2);
	oled_puts("Bär", 2, 15);
	oled_draw_rectangle(4, 6, 36, 17);
	oled_draw_rectangle(81, 6, 102, 17);

	while (1) {
		if ((UCSR0A & (1 << RXC0)) && 1) {
			PORTC |= 1 << PC4;
			uart_gets(uart_field);
			update = 1;
			PORTC &= ~(1 << PC4);
		}

		if (uart_strings_equal("reset", uart_field)) {
			wdt_enable(4);
			while (1)
				;
		}

		if (update) {
			// Zeilenangabe auslesen
			if (uart_field[0] >= '1' && uart_field[0] <= '8') {
				line = uart_field[0] - '0';
			}
			else {
				line = 1;
			}

			// Spaltenangabe auslesen
			if (uart_field[3] == '*' && uart_field[2] >= '1' && uart_field[2] <= '9') {
				col = uart_field[2] - '0';
			}
			else {
				if (uart_field[4] == '*' && uart_field[2] >= '1' && uart_field[2] <= '2'
						&& uart_field[3] >= '0' && uart_field[3] <= '9') {
					col = 10 * (uart_field[2] - '0') + (uart_field[3] - '0');
				}
				else {
					col = 1;
				}
			}

			uint8_t i=0, isave = 0;
			while(uart_field[i] != '*' && i<MAX_ARRAYSIZE-1) i++;
			if(i<MAX_ARRAYSIZE) {
				i++;
				isave = i;
			}
			while(uart_field[i] != '*' && i<MAX_ARRAYSIZE-1) i++;
			if(i<MAX_ARRAYSIZE) {
				i++;
				isave = i;
			}

			uint8_t j;
			for(j=0; j<MAX_ARRAYSIZE-isave-1; j++) {
				uart_field[j] = uart_field[j+isave];
			}
			uart_field[j+1] = '\0';

			oled_puts(uart_field, line, col);
			update = 0;
		}

	}
	return 0;
}
