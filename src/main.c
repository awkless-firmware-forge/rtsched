/* SPDX-FileCopyrightText: 2025 Jason Pena <jasonpena@awkless.com>
 * SPDX-License-Identifier: MIT
 */

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

#include "serial.h"

int
main(void)
{
	sei();
	serial_init(9600);
	while (1) {
		serial_puts("Hello world! My name is Jason!\n");
	}

	return 0;
}
