#include "flood.h"
#include <stdint.h>
#include <vector>
#include <queue>

#define ix(r, c) (GRID_X*r+c)

static uint32_t xorshift(uint32_t *state) {
	uint32_t x = *state;
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	return *state = x;
}
class Quad {
public:
	int left, right, top, bottom;
	Quad() { left = right = top = bottom = 0; }
	Quad(int right, int top, int left, int bottom) {
		this->left = left;
		this->right = right;
		this->top = top;
		this->bottom = bottom;
	}
};
static Quad getSides(int index) {
	int row = index / GRID_X;
	int col = index % GRID_X;
	Quad q(index+1, index-GRID_X, index-1, index+GRID_X);
	if (row == 0)
		q.top = -1;
	else if (row == GRID_X-1)
		q.bottom = -1;
	if (col == 0)
		q.left = -1;
	else if (col == GRID_X-1)
		q.right = -1;
	return q;
}

Flood::Flood() : Flood(1) {}
Flood::Flood(int seed) {
	uint32_t state = uint32_t(seed == 0 ? 1 : seed);
	uint32_t max = (uint32_t(-1) / 6) * 6;
	auto rnd = [max](uint32_t *state) -> Color {
		uint32_t r;
		do
			r = xorshift(state);
		while (r > max);
		return Color(r % 6);
	};
	for (int i = 0; i < 10; i++)
		rnd(&state);
	for (int i = 0; i < GRID_X*GRID_Y; i++) {
		grid[i] = rnd(&state);
	}
	Color cur = grid[0];
	chooseColor(Color::NONE);
	chooseColor(cur);
	turns = 0;
}
Flood::~Flood() {}

Color Flood::getColor(int row, int col) {
	if (row < 0 || row >= GRID_Y || col < 0 || col >= GRID_X)
		return Color::NONE;
	return grid[ix(row, col)];
}

void Flood::chooseColor(Color color) {
	if (color == grid[0])
		return;
	turns++;
	std::vector<bool> inq(GRID_X * GRID_Y);
	for (int i = 0; i < GRID_X * GRID_Y; i++)
		inq[i] = 0;
	Color c = grid[0];
	Quad quad;
	std::queue<int> q;
	q.push(0);
	inq[0] = 1;
	int cur;
	while(!q.empty()) {
		cur = q.front();
		q.pop();
		grid[cur] = color;
		quad = getSides(cur);
		if (quad.left != -1) {
			if (grid[quad.left] == c && !inq[quad.left]) {
				inq[quad.left] = 1;
				q.push(quad.left);
			}
		}
		if (quad.top != -1) {
			if (grid[quad.top] == c && !inq[quad.top]) {
				inq[quad.top] = 1;
				q.push(quad.top);
			}
		}
		if (quad.bottom != -1) {
			if (grid[quad.bottom] == c && !inq[quad.bottom]) {
				inq[quad.bottom] = 1;
				q.push(quad.bottom);
			}
		}
		if (quad.right != -1) {
			if (grid[quad.right] == c && !inq[quad.right]) {
				inq[quad.right] = 1;
				q.push(quad.right);
			}
		}
	}
	progress = 0;
	for (bool b : inq)
		progress += b;
}

bool Flood::hasFinished() {
	Color c = grid[0];
	for (int i = 1; i < GRID_X * GRID_Y; i++)
		if (grid[i] != c)
			return false;
	return true;
}

int Flood::getTurns() {
	return turns;
}

int Flood::getProgress() {
	return progress;
}
