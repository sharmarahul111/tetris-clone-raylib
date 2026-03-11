#include "controls.h"
#include "definition.h"
#include <raylib.h>
extern int speed, blockX, blockY, rotation;
extern float t;
extern bool is_paused;
extern Sound technologia;
extern int grid[GRID_ROWS][GRID_COLS];
extern Block block;
void handle_input() {
	if (IsKeyPressed(KEY_RIGHT)) {
		move_right();
	}
	if (IsKeyPressed(KEY_LEFT)) {
		move_left();
	}
	if (IsKeyPressed(KEY_UP)) {
		rotate_piece();
	}
	if(IsKeyPressed(KEY_SPACE)) {
		PlaySound(technologia);
		is_paused = !is_paused;
	}
	if (IsKeyDown(KEY_DOWN)){
		speed = 1;
	} else {
		speed = 15;
	}
}

void rotate_piece(){
	bool can_rotate = true;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			// check if block can go left
			int gridX = blockX + j;
			int gridY = blockY + i;
			if (
				block.piece.data[(rotation + 1) % 4][i][j] != 0 &&
				(
					(gridX < 0 || gridX >= GRID_COLS) ||
					(gridY >= GRID_ROWS) ||
					(grid[gridY][gridX] != 0)
				)
			) {
				can_rotate = false;
				break;
			}
		}
	}
	if (can_rotate) {
		rotation = (rotation + 1) % 4;
	}
}

void move_right(){
	bool can_go_right = true;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			// check if block can go right
			int gridX = blockX + j;
			int gridY = blockY + i;
			if (block.piece.data[rotation][i][j] != 0 && (gridX >= GRID_COLS - 1 || (grid[gridY][gridX + 1] != 0))) {
				can_go_right = false;
				break;
			}
		}
	}
	if (can_go_right) {
		blockX += 1;
	}
}

void move_left(){
	bool can_go_left = true;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			// check if block can go left
			int gridX = blockX + j;
			int gridY = blockY + i;
			if (block.piece.data[rotation][i][j] != 0 && (gridX <= 0 || (grid[gridY][gridX - 1] != 0))) {
				can_go_left = false;
				break;
			}
		}
	}
	if (can_go_left) {
		blockX -= 1;
	}
}