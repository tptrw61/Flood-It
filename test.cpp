#include "flood.h"
#include <stdio.h>
#include <time.h>

#define TURNS 30

void dispColor(Color c) {
	if (c == Color::RED)
		printf("\033[48;2;255;0;0m");
	else if (c == Color::GREEN)
		printf("\033[48;2;0;255;0m");
	else if (c == Color::YELLOW)
		printf("\033[48;2;255;255;0m");
	else if (c == Color::BLUE)
		printf("\033[48;2;0;0;255m");
	else if (c == Color::MAGENTA)
		printf("\033[48;2;255;0;255m");
	else if (c == Color::CYAN)
		printf("\033[48;2;0;255;255m");
}

void dispGame(Flood& game) {
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			dispColor(game.getColor(i, j));
			printf("  ");
		}
		printf("\033[0m\n");
	}
}

int main() {
	int seed = time(0);
	printf("SEED: %d\n", seed);
	Flood game(seed);
	int inp;
	while (!game.hasFinished() && game.getTurns() < TURNS) {
		dispGame(game);
		printf("\033[38;2;0;0;0m");
		dispColor(Color::RED); printf("1");
		dispColor(Color::BLUE); printf("2");
		dispColor(Color::GREEN); printf("3");
		dispColor(Color::YELLOW); printf("4");
		dispColor(Color::CYAN); printf("5");
		dispColor(Color::MAGENTA); printf("6");
		printf("\033[0m TURNS: %02d/%d\n", game.getTurns(), TURNS);
		printf("enter number: ");
		scanf("%d", &inp);
		game.chooseColor(Color(inp-1));
	}
	dispGame(game);

	return 0;
}
