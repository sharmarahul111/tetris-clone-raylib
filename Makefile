CC := gcc
CFLAGS := -Wall -Wextra -Wshadow -Wpedantic -g
SRC := $(wildcard src/*.c)
OBJS := $(patsubst src/%.c, build/%.o, $(SRC))
all: build/tetris-clone
build/tetris-clone: $(OBJS)
	@echo "Building binary..."
	@$(CC) $(CFLAGS) $^ -o $@
build/%.o: src/%.c
	@echo "Compiling..." $<
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -r build/*.o build/tetris-clone
