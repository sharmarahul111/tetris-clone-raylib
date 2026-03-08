#include "definition.h"
#include "block_preset.h"
#include <raylib.h>
#include <stdio.h>
void game_loop(void);
void draw_grid(void);
void fill_grid(void);
void draw_block(void);

Cell grid[GRID_ROWS][GRID_COLS];
Block current_block;
Vector2 block_pos;
int main() {
	// Initializing
	printf("Running...\n");
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Tetris Clone");
	SetTargetFPS(10);
	fill_grid();
	current_block = block_preset(1);

	// Game loop
	while (!WindowShouldClose()) {
		game_loop();
	}
	CloseWindow();
	return 0;
}
void game_loop() {
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
			} else if (i == 18 && (j % 2 == 0 || j % 3 == 0)) {
				grid[i][j].color = GREEN;
			} else if (i == 17 && j % 4 == 0) {
				grid[i][j].color = GREEN;
			} else {
				grid[i][j].color = BLACK;
			}
		}
	}
}

void draw_block() {
	for (int i = 0; i < current_block.preset.height; i++) {
		for (int j = 0; j < current_block.preset.width; j++) {
			if (current_block.preset.data[i][j] != 0) {
				int posX = SIDEBAR_WIDTH + (block_pos.x + j) * CELL_SIZE;
				int posY = (block_pos.y + i) * CELL_SIZE;
				DrawRectangle(posX + 4, posY + 4, CELL_SIZE - 4, CELL_SIZE - 4, current_block.color);
			}
		}
	}
}