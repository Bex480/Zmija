#include "SDL.h"
#include "Screen.h"
#include "Snake.h"
#include "Food.h"
#include "Wall.h"
#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

bool holdGame(Screen& screen, int millis) {
	int startTime = SDL_GetTicks();
	bool quit = false;
	while (SDL_GetTicks() - startTime < millis && !quit) {
		if (screen.eventHandler() == Screen::Action::QUIT)
			quit = true;
	}
	return quit;
}

bool pauseGame(Screen& screen, bool& pause) {
	int startTime = SDL_GetTicks();
	bool quit = false;
	while (!quit && pause) {
		int action = screen.eventHandler();
		switch (action) {
		case Screen::Action::QUIT:
			quit = true;
			break;
		case Screen::Action::PAUSE:
			pause = false;
			break;
		}

	}
	return quit;
}

void resetLevel(Snake& snake, Food& food, bool& starting) {
	snake.reset();
	food = Food();
	starting = true;
}

void createWalls(vector<Wall*>& walls) {
	const int N_HORIZONTAL = Screen::S_WIDTH / Wall::WALL_WIDTH;
	const int N_VERTICAL = Screen::S_HEIGHT / Wall::WALL_WIDTH;

	for (int i = 0; i < N_HORIZONTAL; i++) {
		Wall* upperWall = new Wall(i * Wall::WALL_WIDTH, 0);
		Wall* lowerWall = new Wall(i * Wall::WALL_WIDTH, Screen::S_HEIGHT - Wall::WALL_WIDTH);
		walls.push_back(upperWall);
		walls.push_back(lowerWall);
	}
	for (int i = 1; i < N_VERTICAL - 1; i++) {
		Wall* leftmostWall = new Wall(0, i * Wall::WALL_WIDTH);
		Wall* rightmostWall = new Wall(Screen::S_WIDTH - Wall::WALL_WIDTH, i * Wall::WALL_WIDTH);
		walls.push_back(leftmostWall);
		walls.push_back(rightmostWall);
	}
}

void drawWalls(vector<Wall*>& walls, Screen& screen) {
	for (auto wall : walls)
		wall->draw(screen);
}

void freeWalls(vector<Wall*>& walls) {
	for (auto wall : walls)
		delete wall;
	walls.clear();
}

int main(int argc, char** argv) {
	srand(time(NULL));

	Screen screen;
	Snake snake;
	Food food;
	vector<Wall*> walls;
	createWalls(walls);


	if (!screen.init()) {
		SDL_Log("Error initializing screen");
		return -1;
	}

	bool quit = false;
	bool starting = true;
	bool pause = false;

	while (!quit) {
		
		screen.clear();
		screen.setBackround(screen);
		snake.draw(screen);
		food.draw(screen);
		drawWalls(walls, screen);
		screen.update();

		if (starting) {
			quit = holdGame(screen, 1000);
			starting = false;
		}

		switch (screen.eventHandler()) {
		case Screen::Action::QUIT:
			quit = true;
			break;
		case Screen::Action::PAUSE:
			pause = true;
			break;
		case Screen::Action::MOVE_UP:
			if (!snake.snake_hasUpdated)
				snake.updateDirection(Snake::Direction::UP);
			break;
		case Screen::Action::MOVE_DOWN:
			if (!snake.snake_hasUpdated)
				snake.updateDirection(Snake::Direction::DOWN);
			break;
		case Screen::Action::MOVE_LEFT:
			if (!snake.snake_hasUpdated)
				snake.updateDirection(Snake::Direction::LEFT);
			break;
		case Screen::Action::MOVE_RIGHT:
			if (!snake.snake_hasUpdated)
				snake.updateDirection(Snake::Direction::RIGHT);
			break;
		}

		if (pause)
			quit = pauseGame(screen, pause);

		int elapsed = SDL_GetTicks();

		if (elapsed / 10 % 6 == 0) {
			if (!snake.move())
				resetLevel(snake, food, starting);
			else {
				if (snake.collidesWith(food)) {
					food = Food();
					snake.addBody();
				}

				for (auto wall : walls)
					if (snake.collidesWith(*wall))
						resetLevel(snake, food, starting);

				for (int i = 1; i < snake.snake_body.size(); i++)
					if (snake.collidesWith(*snake.snake_body[i]))
						resetLevel(snake, food, starting);
			}
		}

	}

	freeWalls(walls);
	screen.close();

	return 0;
}