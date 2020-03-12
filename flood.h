#pragma once

#define GRID_X 15
#define GRID_Y 15

enum Color {
	RED = 0, BLUE, GREEN, YELLOW, CYAN, MAGENTA,
	NONE = -1
};

class Flood {
private:
	Color grid[GRID_X * GRID_Y];
	int turns;
	int progress;
public:
	Flood();
	Flood(int seed);
	~Flood();
	Color getColor(int row, int col);
	void chooseColor(Color color);
	bool hasFinished();
	int getTurns();
	int getProgress();
};
