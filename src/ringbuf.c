/* SPDX-FileCopyrightText: 2025 Jason Pena <jasonpena@awkless.com>
 * SPDX-License-Identifier: MIT
 */

#include <string.h>

#include "ringbuf.h"

void
ringbuf_init(struct RingBuf *rbuf)
{
	rbuf->head = 0;
	rbuf->tail = 0;
	rbuf->size = 0;
}

bool
ringbuf_is_empty(struct RingBuf *rbuf)
{
	return rbuf->size == 0;
}

uint8_t
ringbuf_get(struct RingBuf *rbuf)
{
	if (ringbuf_is_empty(rbuf))
		return 0;

	uint8_t item = *rbuf->buf[rbuf->tail];
	rbuf->tail = (rbuf->tail + 1) % RINGBUF_CAPACITY;
	--rbuf->size;

	return item;
}

void
ringbuf_put(struct RingBuf *rbuf, uint8_t item)
{
	if (rbuf->size >= RINGBUF_CAPACITY)
		return;

	*rbuf->buf[rbuf->head] = item;
	rbuf->head = (rbuf->head + 1) % RINGBUF_CAPACITY;
	++rbuf->size;
}

void
ringbuf_flush(struct RingBuf *rbuf)
{
	memset(rbuf->buf, 0, sizeof *rbuf->buf * RINGBUF_CAPACITY);
	rbuf->head = 0;
	rbuf->tail = 0;
	rbuf->size = 0;
}
