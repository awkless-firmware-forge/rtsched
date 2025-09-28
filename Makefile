# SPDX-FileCopyrightText: 2025 Jason Pena <jasonpena@awkless.com>
# SPDX-License-Identifier: MIT

##! Options

AVRDUDE := avrdude
OBJCOPY := avr-objcopy
CC := avr-gcc
MAKE := make

MCU = atmega328p
F_CPU = 16000000UL
PROGRAMMER = arduino
PORT = /dev/ttyUSB0
PORT_BAUD = 115200
SERIAL_BAUD = 9600

AVRDUDEFLAGS := -p $(MCU) -c $(PROGRAMMER) -P $(PORT) -b $(PORT_BAUD)
OBJCOPYFLAGS := -j .text -j .data -O ihex
INC_FLAGS := -Isrc/
CFLAGS := -std=c99 -Wall -Wextra -Os -pedantic -DF_CPU=$(F_CPU) -mmcu=$(MCU) \
	  -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums \
	  -ffunction-sections -fdata-sections -Wl,--gc-sections
LDFLAGS :=

SRC := src/ringbuf.c src/main.c
OBJ := $(SRC:.c=.o)

##! Development Targets

.PHONY: all
all: init clean rtsched.hex ## Build flashable firmware in full

.PHONY: init
init: ## Intitialize external modules
	@git submodule update --recursive --init

rtsched.hex: rtsched.elf ## Generate Intel HEX of firmware for upload
	$(OBJCOPY) $(OBJCOPYFLAGS) $^ $@

rtsched.elf: $(OBJ) ## Generate ELF of firmware to get Intel HEX from
	$(CC) $(CFLAGS) $(INC_FLAGS) -o $@ $^ $(LDFLAGS)

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) $(INC_FLAGS) -c -o $@ $< $(LDFLAGS)

.PHONY: upload
upload: ## Flash source code to MCU via programmer
	$(AVRDUDE) $(AVRDUDEFLAGS) -U flash:w:$<

##! Maintenance Targets

.PHONY: test
test: ## Build and run unit tests natively
	@$(MAKE) -C tests

.PHONY: serial
serial: ## Connect to serial port to view MCU output through USART
	tio $(PORT) --baudrate $(SERIAL_BAUD) \
		--databits 8 \
		--flow none \
		--stopbits 1 \
		--parity none

.PHONY: help
help: ## Generate options and targets
	@awk -f tools/mkhelp.awk Makefile

.PHONY: clean
clean: ## Clean up auxiliary MCU development files
	@rm -rf src/*.o *.elf *.hex

.PHONY:
dist-clean: clean ## Clean up all auxiliary files, i.e., full reset
	@$(MAKE) -C tests clean
