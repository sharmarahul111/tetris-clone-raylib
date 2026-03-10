#include "definition.h"
#include "pieces.h"
#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
void game_loop(void);
void draw_outlines(void);
void draw_grid(void);
void fill_grid(void);
void draw_block(void);
void update_block(void);
void merge_block(void);
void next_piece(void);
void handle_input(void);
void check_rows(void);
void eliminate_row(int r);
void draw_score(void);
void draw_next_block(void);
void game_over(void);

Cell grid[GRID_ROWS][GRID_COLS];
Block block;
int next_piece_type = 0;
// int saved_block_type = 0;
int blockX = 3;
int blockY = 0;
int rotation = 0;
int frame = 0;
int speed = 10;
int score = 0;
bool is_game_over = false;
char score_text[5];
int main() {
	// Initializing
	// srand(time(0));
	SetRandomSeed(time(0));
	printf("Running...\n");
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Tetris Clone");
	SetTargetFPS(FRAME_RATE);
	fill_grid();
	// set a random piece to start with
	next_piece_type = GetRandomValue(0, PIECE_COUNT-1);
	next_piece();

	// Game loop
	while (!WindowShouldClose()) {
		game_loop();
		frame++;
	}
	CloseWindow();
	return 0;
}
void game_loop() {
	if(!is_game_over) update_block();
	BeginDrawing();
	ClearBackground(BLACK);
	draw_grid();
	draw_outlines();
	draw_block();
	draw_score();
	draw_next_block();
	 if(is_game_over) {
		game_over();
	}
	DrawFPS(2, 20);
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
			grid[i][j].color = BLACK;
			grid[i][j].data = 0;
		}
	}
}

void draw_block() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (block.piece.data[rotation][i][j] != 0) {
				int posX = SIDEBAR_WIDTH + (blockX + j) * CELL_SIZE;
				int posY = (blockY + i) * CELL_SIZE;
				DrawRectangle(posX + 4, posY + 4, CELL_SIZE - 4, CELL_SIZE - 4, block.color);
			}
		}
	}
}

void update_block() {
	bool can_go_down = true;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			// check if block can go down
			int gridX = blockX + j;
			int gridY = blockY + i;
			if (block.piece.data[rotation][i][j] != 0 && (gridY >= GRID_ROWS - 1 || (grid[gridY + 1][gridX].data != 0))) {
				can_go_down = false;
				merge_block();
				next_piece();
				blockY = 0;
				break;
			}
		}
	}
	if (can_go_down && frame % speed == 0) {
		blockY += 1;
	}
	handle_input();
	check_rows();
}
void merge_block() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			int gridX = blockX + j;
			int gridY = blockY + i;
			if (block.piece.data[rotation][i][j] != 0 && gridY < GRID_ROWS) {
				if(gridY == 0) {
					// game_over();
					is_game_over = true;
				}
				grid[gridY][gridX].data = 1;
				grid[gridY][gridX].color = block.color;
			}
		}
	}
}
void next_piece() {
	block = pieces_preset(next_piece_type);
	next_piece_type = GetRandomValue(0, PIECE_COUNT-1);
	blockX = 3;
	rotation = 0;
	blockY = 0;
}

void handle_input() {
	if (IsKeyDown(KEY_RIGHT) && frame % 3 == 0) {
		bool can_go_right = true;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				// check if block can go right
				int gridX = blockX + j;
				int gridY = blockY + i;
				if (block.piece.data[rotation][i][j] != 0 && (gridX >= GRID_COLS - 1 || (grid[gridY][gridX + 1].data != 0))) {
					can_go_right = false;
					break;
				}
			}
		}
		if (can_go_right) {
			blockX += 1;
		}
	}

	if (IsKeyDown(KEY_LEFT) && frame % 3 == 0) {
		bool can_go_left = true;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				// check if block can go left
				int gridX = blockX + j;
				int gridY = blockY + i;
				if (block.piece.data[rotation][i][j] != 0 && (gridX <= 0 || (grid[gridY][gridX - 1].data != 0))) {
					can_go_left = false;
					break;
				}
			}
		}
		if (can_go_left) {
			blockX -= 1;
		}
	}

	if (IsKeyDown(KEY_UP) && frame % 5 == 0) {
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
						(grid[gridY][gridX].data != 0)
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

	if (IsKeyDown(KEY_DOWN) && frame % 2 == 0){
		speed = 1;
	} else {
		speed = 10;
	}
}

void check_rows(){
	for (int i=GRID_ROWS-1; i>=0; i--) {
		bool can_clear = true;
		for (int j=0; j<GRID_COLS; j++) {
			if (grid[i][j].data == 0) {
				can_clear = false;
				break;
			}
		}
		if (can_clear) {
			// TODO: add bonus score
			score += 10;
			eliminate_row(i);
		}
	}
}

void eliminate_row(int r){
	// start with r, because bottom cells aren't affected
	// and go till 1, since 0 doens't need any change (index)
	for (int i=r; i>0; i--) {
		for (int j=0; j<GRID_COLS; j++) {
			grid[i][j] = grid[i-1][j];
		}
	}
}

void draw_outlines(){
	DrawRectangleLines(SIDEBAR_WIDTH + 2, 2, BOARD_WIDTH - 2, WINDOW_HEIGHT - 2, GREEN);
}

void draw_score(){
	sprintf(score_text, "%d", score);
	DrawText("SCORE:", 20, WINDOW_HEIGHT-100, 30, GREEN);
	DrawText(score_text, 20, WINDOW_HEIGHT-60, 30, GREEN);
}

void draw_next_block(){
	Block b = pieces_preset((next_piece_type));
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (b.piece.data[0][i][j] != 0) {
				int posX = 30+j*CELL_SIZE;
				int posY = 200+i*CELL_SIZE;
				DrawText("NEXT\nPIECE:", 30, 100, 30, GREEN);
				DrawRectangle(posX + 4, posY + 4, CELL_SIZE - 4, CELL_SIZE - 4, b.color);
			}
		}
	}
}

void game_over(){
	int width = 300;
	int height = 200;
	int x = (WINDOW_WIDTH-width)/2;
	int y = (WINDOW_HEIGHT-height)/2;
	char text[] = "GAME OVER";
	DrawRectangle(x, y, width, height, BLACK);
	DrawRectangleLines(x, y, width, height, GREEN);
	sprintf(score_text, "%d", score);
	DrawText(text, x+(width-MeasureText(text, 40))/2, y+30, 40, GREEN);
	DrawText(score_text, x+(width-MeasureText(score_text, 70))/2, y+90, 70, GREEN);
}