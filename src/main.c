#include <raylib.h>
#include <stdio.h>
#include "definition.h"
void game_loop(void);
void draw_grid(void);
void fill_grid(void);
Block block_preset(int type);

Cell grid[GRID_ROWS][GRID_COLS];
Block current_block;
int main() {
	// Initializing
	printf("Running...\n");
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Tetris Clone");
	SetTargetFPS(10);
	fill_grid();

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
	EndDrawing();
}
void draw_grid() {
	for (int i = 0; i < GRID_ROWS; i++) {
		for (int j = 0; j < GRID_COLS; j++) {
			int posX = SIDEBAR_WIDTH + j * CELL_SIZE;
			int posY = i * CELL_SIZE;
			DrawRectangle(posX + 4, posY + 4, CELL_SIZE - 4, CELL_SIZE - 4, grid[i][j]);
		}
	}
}
void fill_grid() {
	for (int i = 0; i < GRID_ROWS; i++) {
		for (int j = 0; j < GRID_COLS; j++) {
			if (i == 19) {
				grid[i][j] = GREEN;
			} else if (i == 18 && (j % 2 == 0 || j % 3 == 0)) {
				grid[i][j] = GREEN;
			} else if (i == 17 && j % 4 == 0) {
				grid[i][j] = GREEN;
			} else {
				grid[i][j] = BLACK;
			}
		}
	}
}
