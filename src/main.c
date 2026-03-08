#include <stdio.h>
#include <raylib.h>
#define GRID_COLS 10
#define GRID_ROWS 20
#define CELL_SIZE 30
#define BOARD_WIDTH  (GRID_COLS * CELL_SIZE)
#define BOARD_HEIGHT (GRID_ROWS * CELL_SIZE)
#define SIDEBAR_WIDTH 200
#define WINDOW_WIDTH  (BOARD_WIDTH + SIDEBAR_WIDTH)
#define WINDOW_HEIGHT BOARD_HEIGHT
void game_loop(void);
int main(){
	int GRID[GRID_ROWS][GRID_COLS];
	printf("Running...\n");
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Tetris Clone");
	SetTargetFPS(60);
	while(!WindowShouldClose()){
		game_loop();
	}
	CloseWindow();
	return 0;
}
void game_loop(){
	BeginDrawing();
	DrawRectangle(20, 20, CELL_SIZE, CELL_SIZE, BLUE);
	EndDrawing();
}