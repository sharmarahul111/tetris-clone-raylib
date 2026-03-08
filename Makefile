CC := gcc
CFLAGS := -Wall -Wextra -Wshadow -Wpedantic -g

SRC := $(wildcard src/*.c)
OBJS := $(patsubst src/%.c, build/%.o, $(SRC))

all: build/tetris-clone

build:
	mkdir -p build

build/tetris-clone: $(OBJS) | build
	@echo "Building binary..."
	@$(CC) $(CFLAGS) $^ -o $@

build/%.o: src/%.c | build
	@echo "Compiling..." $<
	@$(CC) $(CFLAGS) -c $< -o $@

run: all
	@./build/tetris-clone

clean:
	rm -rf build/*