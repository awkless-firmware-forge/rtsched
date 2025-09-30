/* SPDX-FileCopyrightText: 2025 Jason Pena <jasonpena@awkless.com>
 * SPDX-License-Identifier: MIT
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stddef.h>

#include "serial.h"
#include "ringbuf.h"

static struct RingBuf txrbuf = ringbuf_init();

void
serial_init(unsigned int baud)
{
	unsigned int ubrr = F_CPU / 16 / baud - 1;
	UBRR0H = (uint8_t)(ubrr >> 8);
	UBRR0L = (uint8_t)ubrr;
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	/* INVARIANT: Frame format is 8-bit data with 2-bit stop. */
	UCSR0C = (1 << USBS0) | (3 << UCSZ00);
}

void
serial_putchar(char c)
{
	if (c == '\n')
		serial_putchar('\r');

	while (ringbuf_put(&txrbuf, (uint8_t)c) == -RINGBUF_OVERFLOW);
	UCSR0B |= (1 << UDRIE0);
}

void
serial_puts(const char *str)
{
	while (*str != '\0')
		serial_putchar(*str++);
}

ISR(USART_UDRE_vect)
{
	uint8_t data = 0;
	if (ringbuf_get(&txrbuf, &data) == RINGBUF_OK)
		UDR0 = data;
	else
		UCSR0B &= ~(1 << UDRIE0);
}
