#include <iostream>
#include <SDL.h>
using namespace std;

int main() {
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;

	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		cout << "SDL init failed." << endl;
		return 1;
	}

	SDL_Window *window = SDL_CreateWindow(
			"Particle Fire Explosion",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_OPENGL
			);

	if(window == NULL){
		SDL_Quit();
		return 2;
	}

	// the last arg is responsible for refreshing from top-left corner to top-right, then next row, etc.
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	SDL_Texture *texture = SDL_CreateTexture(
			renderer,
			SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_STATIC,
			SCREEN_WIDTH,
			SCREEN_HEIGHT
			);
	if(renderer == NULL){
		cout << "Could not create renderer" << endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 3;
	}
	if(texture == NULL){
		cout << "Could not create texture" << endl;
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 4;
	}

	// SDL defines this because an int may not be the same size on all operating systems
	// also, a buffer is an area of memory
	Uint32 *buffer = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
	// memset allows you to set a block of memory with a particular value
	// 0xFF is hexadecimal for 255
	memset(buffer, 0, SCREEN_WIDTH*SCREEN_HEIGHT*sizeof(Uint32));

	// setting an individual pixel
	// setting all 4 bytes to FFs
	buffer[30000] = 0xFFFFFFFF;

	for(int i=0; i < SCREEN_WIDTH*SCREEN_HEIGHT; i++){
		// this does same thing as memset, which is slower because for loop is slower
		buffer[i] = 0xFF0000FF;
	}

	// the pitch (last arg)
	SDL_UpdateTexture(texture, NULL, buffer, SCREEN_WIDTH * sizeof(Uint32));
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	SDL_RenderPresent(renderer);

	bool quit = false;
	SDL_Event event;
	while(!quit){
		// Update particles
		// Draw particles
		// Check for messages/events

		while(SDL_PollEvent(&event)){
			if(event.type == SDL_QUIT){
				quit = true;
			}
		}
	}

	delete [] buffer;
	// destroy texture first because it's using the renderer, just as a child class calls destructor first
	SDL_DestroyRenderer(renderer);
	SDL_DestroyTexture(texture);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
