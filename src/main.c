/* SPDX-FileCopyrightText: 2025 Jason Pena <jasonpena@awkless.com>
 * SPDX-License-Identifier: MIT
 */

#include <avr/io.h>

void
usart_init(void)
{
	UCSR0B = (1 << TXEN0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
	UBRR0L = 103;
}

void
usart_putchar(unsigned char ch)
{
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = ch;
}

int
main(void)
{
	usart_init();
	while (1)
		usart_putchar('A');
	return 0;
}
