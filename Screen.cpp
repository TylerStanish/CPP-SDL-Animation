/*
 * Screen.cpp
 *
 *  Created on: Nov 20, 2017
 *      Author: tylerstanish
 */

#include "Screen.h"

namespace tss {

Screen::Screen() :
	m_window(NULL),
	m_renderer(NULL),
	m_texture(NULL),
	m_buffer(NULL){

}

bool Screen::init(){
	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		// use SDL_GetError for more info
		return false;
	}

	m_window = SDL_CreateWindow(
			"Particle Fire Explosion",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_OPENGL
			);

	if(m_window == NULL){
		SDL_Quit();
		return false;
	}

	// the last arg is responsible for refreshing from top-left corner to top-right, then next row, etc.
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
	m_texture = SDL_CreateTexture(
			m_renderer,
			SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_STATIC,
			SCREEN_WIDTH,
			SCREEN_HEIGHT
			);
	if(m_renderer == NULL){
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return false;
	}
	if(m_texture == NULL){
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return false;
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

	SDL_UpdateTexture(m_texture, NULL, buffer, SCREEN_WIDTH * sizeof(Uint32));
		SDL_RenderClear(m_renderer);
		SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
		SDL_RenderPresent(m_renderer);
	return true;
}

bool Screen::processEvents(){
	return false;
}

void Screen::close(){
	delete []  m_buffer;
	// destroy texture first because it's using the renderer, just as a child class calls destructor first
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyTexture(m_texture);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

} /* namespace tss */
