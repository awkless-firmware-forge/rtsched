/* SPDX-FileCopyrightText: 2025 Jason Pena <jasonpena@awkless.com>
 * SPDX-License-Identifier: MIT
 */

#ifndef RTSCHED_RINGBUF_H
#define RTSCHED_RINGBUF_H

#include <stdint.h>
#include <stdbool.h>
#include <util/atomic.h>

#define RINGBUF_CAPACITY 16
#define RINGBUF_MASK (RINGBUF_CAPACITY - 1)

#define RINGBUF_OK 0
#define RINGBUF_OVERFLOW 1
#define RINGBUF_UNDERFLOW 2

struct RingBuf {
	uint8_t buf[RINGBUF_CAPACITY];
	volatile unsigned int head;
	volatile unsigned int tail;
};

#define ringbuf_init() { .buf = {0}, .head = 0, .tail = 0 }

void
ringbuf_flush(struct RingBuf *rbuf);

int
ringbuf_get(struct RingBuf *rbuf, uint8_t *item);

int
ringbuf_put(struct RingBuf *rbuf, uint8_t item);

static inline bool
ringbuf_is_empty(struct RingBuf *rbuf)
{
	bool result = false;
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		result = rbuf->head == rbuf->tail;
	}
	return result;
}

static inline bool
ringbuf_is_full(struct RingBuf *rbuf)
{
	bool result = false;
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		result = ((rbuf->head + 1) & RINGBUF_MASK) == rbuf->tail;
	}
	return result;
}

#endif /* RTSCHED_RINGBUF_H */
