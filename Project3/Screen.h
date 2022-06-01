#include "SDL.h"

#ifndef SCREEN_H
#define SCREEN_H

typedef const unsigned int cint;

class Screen {
public:
	Screen();

	enum Action{ QUIT, PAUSE, MOVE_UP, MOVE_DOWN, MOVE_LEFT, MOVE_RIGHT };
	static cint S_WIDTH;
	static cint S_HEIGHT;

	SDL_Window * s_window;
	SDL_Renderer * s_renderer;
	SDL_Texture * s_texture;
	Uint32 * s_mainBuffer;

	bool init();

	int eventHandler();

	void update();

	void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);

	void setBackround(Screen& screen);

	void clear();
	void close();
};

#endif // !SCREEN_H

