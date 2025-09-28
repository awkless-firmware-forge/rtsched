/* SPDX-FileCopyrightText: 2025 Jason Pena <jasonpena@awkless.com>
 * SPDX-License-Identifier: MIT
 */

#ifndef RTSCHED_RINGBUF_H
#define RTSCHED_RINGBUF_H

#include <stdint.h>
#include <stdbool.h>

#define RINGBUF_CAPACITY 16

struct RingBuf {
	uint8_t *buf[RINGBUF_CAPACITY];
	unsigned int head;
	unsigned int tail;
	unsigned int size;
};

void
ringbuf_init(struct RingBuf *rbuf);

bool
ringbuf_is_empty(struct RingBuf *rbuf);

uint8_t
ringbuf_get(struct RingBuf *rbuf);

void
ringbuf_put(struct RingBuf *rbuf, uint8_t item);

void
ringbuf_flush(struct RingBuf *rbuf);

#endif /* RTSCHED_RINGBUF_H */
