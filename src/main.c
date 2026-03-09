#include "definition.h"
#include "pieces.h"
#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void game_loop(void);
void draw_grid(void);
void fill_grid(void);
void draw_block(void);
void update_block(float dt);
void merge_block(void);
void next_piece(void);

Cell grid[GRID_ROWS][GRID_COLS];
Block block;
Vector2 block_pos;
int main() {
	// Initializing
	srand(time(0));
	printf("Running...\n");
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Tetris Clone");
	SetTargetFPS(6);
	fill_grid();
	block = pieces_preset(0);

	// Game loop
	while (!WindowShouldClose()) {
		game_loop();
	}
	CloseWindow();
	return 0;
}
void game_loop() {
	float dt = GetFrameTime();
	update_block(dt);
	BeginDrawing();
	ClearBackground(BLACK);
	draw_grid();
	draw_block();
	EndDrawing();
}
void draw_grid() {
	for (int i = 0; i < GRID_ROWS; i++) {
		for (int j = 0; j < GRID_COLS; j++) {
			int posX = SIDEBAR_WIDTH + j * CELL_SIZE;
			int posY = i * CELL_SIZE;
			DrawRectangle(posX + 4, posY + 4, CELL_SIZE - 4, CELL_SIZE - 4, grid[i][j].color);
		}
	}
}

void fill_grid() {
	for (int i = 0; i < GRID_ROWS; i++) {
		for (int j = 0; j < GRID_COLS; j++) {
			if (i == 19) {
				grid[i][j].color = GREEN;
				grid[i][j].data = 1;
			} else if (i == 18 && (j % 2 == 0 || j % 3 == 0)) {
				grid[i][j].color = GREEN;
				grid[i][j].data = 1;
			} else if (i == 17 && j % 4 == 0) {
				grid[i][j].color = GREEN;
				grid[i][j].data = 1;
			} else {
				grid[i][j].color = BLACK;
				grid[i][j].data = 0;
			}
		}
	}
}

void draw_block() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (block.piece.data[0][i][j] != 0) {
				int posX = SIDEBAR_WIDTH + (block_pos.x + j) * CELL_SIZE;
				int posY = (block_pos.y + i) * CELL_SIZE;
				DrawRectangle(posX + 4, posY + 4, CELL_SIZE - 4, CELL_SIZE - 4, block.color);
			}
		}
	}
}

void update_block(float dt) {
	bool can_go_down = true;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			// check if block can go down
			int gridX = (int)block_pos.x + j;
			int gridY = (int)block_pos.y + i;
			if (block.piece.data[0][i][j] != 0 && (gridY >= GRID_ROWS - 1 || (grid[gridY + 1][gridX].data != 0))) {
				can_go_down = false;
				merge_block();
				next_piece();
				block_pos.y = 0;
				break;
			}
		}
	}
	if (can_go_down) {
		block_pos.y += (int)(dt * 10);
	}
}
void merge_block() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			int gridX = (int)block_pos.x + j;
			int gridY = (int)block_pos.y + i;
			if (block.piece.data[0][i][j] != 0) {
				grid[gridY][gridX].data = 1;
				grid[gridY][gridX].color = block.color;
			}
		}
	}
}
void next_piece() {
	// randomize piece and x axis
	int piece = rand()%PIECE_COUNT;
	block = pieces_preset(piece);
	block_pos = (Vector2){3, 0};
}