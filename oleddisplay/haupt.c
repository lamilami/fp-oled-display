#include "global.h"

volatile uint8_t tempflag = 0;

int main(void) {
	wdt_disable();

	char uart_field[MAX_ARRAYSIZE + 1] = { 0 };
	char tfeld[10];
	int16_t temperature = 0;

	uint8_t update = 0;

	PORTB |= 1 << PB1;
	DDRB |= (1 << PB3 | 1 << PB1);

	DDRC |= (1 << PC3 | 1 << PC4);

	PORTC |= 1 << PC3;
	_delay_ms(1000);
	PORTC &= ~(1 << PC3);
	_delay_ms(1000);

	uart_init(9600);

	oled_init();
	oled_display_clear();

	oled_puts("Tiger", 4, 1);
	oled_puts("Bär", 4, 18);
	oled_draw_circle(64, 32, 12);
	oled_draw_circle(64, 32, 1);
	oled_draw_pixel(59, 26);
	oled_draw_pixel(69, 26);
	oled_draw_line(61, 39, 67, 39);
	oled_draw_pixel(60, 38);
	oled_draw_pixel(68, 38);
	oled_draw_pixel(59, 37);
	oled_draw_pixel(69, 37);
	oled_draw_line(64, 20, 64, 10);
	oled_draw_line(76, 32, 86, 32);
	oled_draw_line(64, 44, 64, 54);
	oled_draw_line(52, 32, 40, 32);
	oled_draw_line(73, 24, 80, 15);
	oled_draw_line(73, 40, 80, 49);
	oled_draw_line(55, 24, 48, 15);
	oled_draw_line(55, 40, 48, 49);

	TCCR1B |= (1 << CS12 | 1 << CS10);
	TIMSK1 |= (1 << TOIE1);

	sei();

	while (1) {
		if ((UCSR0A & (1 << RXC0)) && 1) {
			PORTC |= 1 << PC4;
			uart_gets(uart_field);
			update = 1;
			PORTC &= ~(1 << PC4);

			if (uart_strings_equal("reset", uart_field)) {
				wdt_enable(4);
				while (1)
					;
			}
		}
		if (update) {
			oled_puts(uart_field, 4, 1);
			update = 0;
		}

		if (tempflag) {
			tempflag = 0;
			temperature = w1_tempmeas();
			w1_temp_to_array(temperature, tfeld, 1);
			oled_puts(tfeld, 8, 9);
			oled_puts("°C", 8, 13);
		}

	}
	return 0;
}

ISR (TIMER1_OVF_vect) {
	tempflag = 1;
}
