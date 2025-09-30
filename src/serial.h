/* SPDX-FileCopyrightText: 2025 Jason Pena <jasonpena@awkless.com>
 * SPDX-License-Identifier: MIT
 */

#ifndef RTSCHED_SERIAL_H
#define RTSCHED_SERIAL_H

void
serial_init(unsigned int baud);

void
serial_putchar(char c);

void
serial_puts(const char *str);

#endif /* RTSCHED_SERIAL_H */
