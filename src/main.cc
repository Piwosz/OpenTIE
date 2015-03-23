/*
 * main.cc
 *
 *  Created on: 22 mar 2015
 *      Author: mac
 */

#include <exception>
#include <iostream>
#include <cassert>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include "resources_fs.h"
#include "assets/strings.h"
#include "varchar.h"

int main(int argc, char *kargv[]) {
	assert(tie::unit::test_varchar());
	tie::lfd::Storage storage;
	storage.LoadTieDirectory("/Users/mac/Desktop/tie/resources");
//	storage.GetAssetByName<tie::assets::TagStrings>("resource/battle1.lfd/battle1");

	SDL_Window* window = nullptr;
	SDL_GLContext context = nullptr;

	if (auto res = SDL_Init(SDL_INIT_VIDEO)) {
		std::cerr << SDL_GetError() << std::endl;
		return res;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	window = SDL_CreateWindow("OpenTIE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (!window) {
		std::cerr << SDL_GetError() << std::endl;
		return 1;
	}

	context = SDL_GL_CreateContext(window);
	if (!context) {
		std::cerr << SDL_GetError() << std::endl;
		return 2;
	}

	auto ret = glewInit();
	if (GLEW_OK != ret) {
		std::cerr << glewGetErrorString(ret) << std::endl;
		return ret;
	}

	SDL_Event e;
	bool quit = false;
	while (!quit) { //Handle events on queue
		while (SDL_PollEvent(&e) != 0) { //User requests quit
			if (e.type == SDL_QUIT) { quit = true; } //Handle keypress with current mouse position
		}
//		SDL_GL_SwapWindow(window);
	}
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}

