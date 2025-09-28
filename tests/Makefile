# SPDX-FileCopyrightText: 2025 Jason Pena <jasonpena@awkless.com>
# SPDX-License-Identifier: MIT

CC := gcc
INC_FLAGS := -I../src -I../extern/acutest/include
CFLAGS := -std=c99 -Wall -Wextra -Os -pedantic $(INC_FLAGS)
LDFLAGS :=

SRC := ../src/ringbuf.c
TAP := test_ringbuf.c
OBJ := $(SRC:.c=.o)
BIN := $(TAP:.c=)

##! Test Targets

.PHONY: all
all: clean test ## Build and run all tests by default

.PHONY: init
init: ## Intitialize external modules
	@git submodule update --recursive --init

.PHONY: test
test: $(OBJ) $(BIN) ## Build and run all tests
	./$(BIN)

.SUFFIXES: .c
	$(CC) $(CFLAGS) $< $(OBJ) -o $@ $(LDFLAGS)

.SUFFIXES: .c .o
.c.o:
	$(CC) $(CFLAGS) -c -o $@ $< $(LDFLAGS)

.PHONY: help
help: ## Generate options and targets
	@awk -f ../tools/mkhelp.awk Makefile

.PHONY: clean
clean: ## Clean up auxiliary development files
	@rm -rf $(BIN) *.o ../src/*.o ../*.elf ../*.hex
