#pragma once
#include <SDL\SDL.h>
#ifdef _MSC_VER
#include <windows.h>
#else
#include <unistd.h>
#endif
#include <vector>
#include "node.h"

#include <iostream>
#include <memory>
#include <string>

class Surface
{
public:
	static std::shared_ptr<Surface> setVideoMode();
	static std::shared_ptr<Surface> loadBmp(std::string path);
	void blit(std::weak_ptr<Surface> dest, int x, int y);
	void flip();

private:
	std::shared_ptr<SDL_Surface> surface;
	static void screenDeleter(SDL_Surface *surface);
	static void surfaceDeleter(SDL_Surface *surface);
};
