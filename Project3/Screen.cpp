#include "SDL.h"
#include "Screen.h"
#include <iostream>

typedef const unsigned int cint;

using namespace std;

cint Screen::S_WIDTH = 800;
cint Screen::S_HEIGHT = 600;

Screen::Screen() : s_window(NULL), s_renderer(NULL), s_texture(NULL), s_mainBuffer(NULL) {}

bool Screen::init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		cout << "INIT Error! 1" << endl;
		return false;
	}
	
	s_window = SDL_CreateWindow("ZMIJA", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, S_WIDTH, S_HEIGHT, SDL_WINDOW_SHOWN);

	if (!s_window) {
		SDL_Log("Window ERROR!");
		SDL_Log("%s", SDL_GetError());
		SDL_Quit();
		return false;
	}

	s_renderer = SDL_CreateRenderer(s_window, -1, SDL_RENDERER_PRESENTVSYNC);

	if (!s_renderer) {
		SDL_Log("Renderer ERROR!");
		SDL_Log("%s", SDL_GetError());
		SDL_DestroyWindow(s_window);
		SDL_Quit();
		return false;
	}

	s_texture = SDL_CreateTexture(s_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, S_WIDTH, S_HEIGHT);

	if (!s_texture) {
		SDL_Log("Texture ERROR!");
		SDL_Log("%s", SDL_GetError());
		SDL_DestroyRenderer(s_renderer);
		SDL_DestroyWindow(s_window);
		SDL_Quit();
		return false;
	}

	s_mainBuffer = new Uint32[S_WIDTH * S_HEIGHT];

	clear();

	return true;
}

int Screen::eventHandler() {
	SDL_Event event;

	int action = -1;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			case SDL_QUIT:
				action = Action::QUIT;
				break;

			case SDL_KEYDOWN:
				switch (event.key.keysym.sym) {
					case SDLK_LEFT:
						action = Action::MOVE_LEFT;
						break;
					case SDLK_RIGHT:
						action = Action::MOVE_RIGHT;
						break;
					case SDLK_UP:
						action = Action::MOVE_UP;
						break;
					case SDLK_DOWN:
						action = Action::MOVE_DOWN;
						break;
					case SDLK_RETURN:
						action = Action::PAUSE;
						break;
				}
				break;
		}
	}

	return action;
}

void Screen::update() {
	SDL_UpdateTexture(s_texture, NULL, s_mainBuffer, S_WIDTH * sizeof(Uint32));
	SDL_RenderClear(s_renderer);
	SDL_RenderCopy(s_renderer, s_texture, NULL, NULL);
	SDL_RenderPresent(s_renderer);
}

void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue) {
	if (x >= 0 && x < S_WIDTH && y >= 0 && y < S_HEIGHT) {
		Uint32 color = 0;
		color += red;
		color <<= 8;
		color += green;
		color <<= 8;
		color += blue;
		color <<= 8;
		color += 255;
		s_mainBuffer[y * S_WIDTH + x] = color;
	}
}

void Screen::setBackround(Screen& screen) {
	for (int i = 0; i < S_WIDTH; i++)
		for (int j = 0; j < S_HEIGHT; j++)
			screen.setPixel(i, j, 255, 255, 255);
}

void Screen::clear() {
	memset(s_mainBuffer, 0, S_WIDTH * S_HEIGHT * sizeof(Uint32));
}

void Screen::close() {
	delete[] s_mainBuffer;

	SDL_DestroyTexture(s_texture);
	SDL_DestroyRenderer(s_renderer);
	SDL_DestroyWindow(s_window);
	SDL_Quit();
}

