#include <raylib.h>
#include <stdio.h>
#define GRID_COLS 10
#define GRID_ROWS 20
#define CELL_SIZE 30
#define BOARD_WIDTH (GRID_COLS * CELL_SIZE)
#define BOARD_HEIGHT (GRID_ROWS * CELL_SIZE)
#define SIDEBAR_WIDTH 200
#define WINDOW_WIDTH (BOARD_WIDTH + SIDEBAR_WIDTH)
#define WINDOW_HEIGHT BOARD_HEIGHT

typedef struct {
	int width;
	int height;
	int data[5][5];
	Color color;
} Block;
typedef Color Cell;
Cell grid[GRID_ROWS][GRID_COLS];
void game_loop(void);
void draw_grid(void);
void fill_grid(void);
int main() {
	// Initializing
	printf("Running...\n");
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Tetris Clone");
	SetTargetFPS(60);
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
			if (i==19) {
				grid[i][j] = GREEN;
			} else if (i==18 && (j%2==0 || j%3==0)) {
				grid[i][j] = GREEN;
			} else if (i==17 && j%4==0) {
				grid[i][j] = GREEN;
			} else {
				grid[i][j] = BLACK;
			}
		}
	}
}