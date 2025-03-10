# Makefile
CC := gcc
CFLAGS := -Wall -Wextra -Werror -pedantic -Iinclude
SOURCES := $(shell find src -type f -name '*.c')
TARGETS := libVec.a 
BUILD_DIR := build

_TARGETS = $(addprefix $(BUILD_DIR)/, $(TARGETS))
_OBJS = $(patsubst src/%.c, $(BUILD_DIR)/%.o, $(SOURCES))

all: $(_TARGETS)
	mv $(BUILD_DIR)/libVec.a .

$(_TARGETS): $(_OBJS)
	ar rcs $@ $^

$(_OBJS): $(BUILD_DIR)/%.o: src/%.c
	$(shell [ -d $(dir $@) ] || mkdir -p $(dir $@))
	$(CC) -c $< -o $@ $(CFLAGS)

$(BUILD_DIR):
	$(shell [ -d $(BUILD_DIR) ] || mkdir -p $(BUILD_DIR))

test: all
	$(CC) test/test.c -o vecTest -L. -lVec $(CFLAGS)
	./vecTest

clean:
	rm -rf build/
	rm $(TARGETS)

.PHONY: clean test all
