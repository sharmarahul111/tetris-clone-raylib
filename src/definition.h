#ifndef DEFINITION
#define DEFINITION
#include <raylib.h>
#define GRID_COLS 10
#define GRID_ROWS 20
#define CELL_SIZE 30
#define BOARD_WIDTH (GRID_COLS * CELL_SIZE)
#define BOARD_HEIGHT (GRID_ROWS * CELL_SIZE)
#define SIDEBAR_WIDTH 200
#define WINDOW_WIDTH (BOARD_WIDTH + SIDEBAR_WIDTH)
#define WINDOW_HEIGHT BOARD_HEIGHT
#define PIECE_COUNT 7
#define FRAME_RATE 60

typedef struct {
	// data[rotation][y][x]
	int data[4][4][4];
} Piece;
typedef struct {
	Piece piece;
	Color color;
} Block;
#endif