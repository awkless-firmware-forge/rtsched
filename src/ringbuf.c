/* SPDX-FileCopyrightText: 2025 Jason Pena <jasonpena@awkless.com>
 * SPDX-License-Identifier: MIT
 */

#include <string.h>
#include <util/atomic.h>

#include "ringbuf.h"

int
ringbuf_get(struct RingBuf *rbuf, uint8_t *item)
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		if (ringbuf_is_empty(rbuf))
			return -RINGBUF_UNDERFLOW;

		*item = rbuf->buf[rbuf->tail];
		rbuf->tail = (rbuf->tail + 1) & RINGBUF_MASK;
	}

	return RINGBUF_OK;
}

int
ringbuf_put(struct RingBuf *rbuf, uint8_t item)
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		if (ringbuf_is_full(rbuf))
			return -RINGBUF_OVERFLOW;

		rbuf->buf[rbuf->head] = item;
		rbuf->head = (rbuf->head + 1) & RINGBUF_MASK;
	}

	return RINGBUF_OK;
}

void
ringbuf_flush(struct RingBuf *rbuf)
{
	ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
		memset(rbuf->buf, 0, sizeof rbuf->buf);
		rbuf->head = 0;
		rbuf->tail = 0;
	}
}
