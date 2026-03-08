#include "definition.h"
#include "pieces.h"
#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>
void game_loop(void);
void draw_grid(void);
void fill_grid(void);
void draw_block(void);
void update_block(float dt);

Cell grid[GRID_ROWS][GRID_COLS];
Block block;
Vector2 block_pos;
int main() {
	// Initializing
	printf("Running...\n");
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Tetris Clone");
	SetTargetFPS(4);
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
			if (block.piece.data[0][i][j] !=0 && grid[(int)block_pos.y+i+1][(int)block_pos.x+j].data != 0) {
				can_go_down = false;
				// integrate block function call
				break;
			}
		}
	}
	if (can_go_down)
		block_pos.y++;
}