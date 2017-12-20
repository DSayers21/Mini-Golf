//Open GL includes
#include <GL/glew.h>
#include <glm/glm.hpp>
//Includes
#include <iostream>
#include <string>
//My Includes
#include <MainComp.h>
#include "MiniGolf.h"

#include "GolfCourse.h"

#ifdef _WIN32
#undef main
#endif
const int COLOR_MODE_CYAN = 0;
int gColorMode = COLOR_MODE_CYAN;

int main(int argc, char** argv)
{
	std::string Title = "Advanced Programming Assignment";
	D3DEngine::MainComp m_MainComp(Title, 1200, 800, 120, new MiniGolf());

	/*bool quit = false;
	SDL_Event event;

	SDL_Init(SDL_INIT_VIDEO);
	TTF_Init();

	SDL_Window * window = SDL_CreateWindow("SDL_ttf in SDL2",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640,
		480, 0);
	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);
	TTF_Font * font = TTF_OpenFont("Fonts/OpenSans-Bold.ttf", 25);
	SDL_Color color = { 255, 255, 255 };
	SDL_Surface * surface = TTF_RenderText_Solid(font,
		"Welcome to Gigi Labs", color);
	SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);

	int texW = 0;
	int texH = 0;
	SDL_QueryTexture(texture, NULL, NULL, &texW, &texH);
	SDL_Rect dstrect = { 0, 0, texW, texH };

	while (!quit)
	{
		SDL_WaitEvent(&event);

		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}

		SDL_RenderCopy(renderer, texture, NULL, &dstrect);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	TTF_CloseFont(font);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();

	return 0;*/


	return 0;
}