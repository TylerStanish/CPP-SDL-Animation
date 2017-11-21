/*
 * Screen.h
 *
 *  Created on: Nov 20, 2017
 *      Author: tylerstanish
 */

#ifndef SCREEN_H_
#define SCREEN_H_

#include <SDL.h>
#include <iostream>

namespace tss {

class Screen {
public:
	const static int SCREEN_WIDTH = 800;
	const static int SCREEN_HEIGHT = 600;
private:
	// member variables are usually prefixed with m_
	SDL_Window *m_window;
	SDL_Renderer *m_renderer;
	SDL_Texture *m_texture;
	Uint32 *m_buffer;

public:
	Screen();
	bool init();
	bool processEvents();
	void close();
};

} /* namespace tss */

#endif /* SCREEN_H_ */
