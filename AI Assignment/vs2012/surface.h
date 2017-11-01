#pragma once
#include <SDL\SDL.h>

class Surface
{
public:
	static std::shared_ptr<Surface> setVideoMode()
	{
		std::shared_ptr<Surface> rtn;

		rtn.reset(new Surface());
		rtn->surface.reset(SDL_SetVideoMode(800, 600, 32, SDL_SWSURFACE), screenDeleter);

		return rtn;
	}

	static std::shared_ptr<Surface> loadBmp(std::string path)
	{
		std::shared_ptr<Surface> rtn;

		rtn.reset(new Surface());
		rtn->surface.reset(SDL_LoadBMP(path.c_str()), surfaceDeleter);

		return rtn;
	}

	void blit(std::weak_ptr<Surface> dest)
	{
		SDL_Rect rect = { 0 };

		SDL_BlitSurface(surface.get(), NULL, dest.lock()->surface.get(), &rect);
	}

	void flip()
	{
		SDL_Flip(surface.get());
	}

private:
	std::shared_ptr<SDL_Surface> surface;

	static void screenDeleter(SDL_Surface *surface)
	{
		std::cout << "SDL_Quit" << std::endl;
		SDL_Quit();
	}

	static void surfaceDeleter(SDL_Surface *surface)
	{
		std::cout << "SDL_FreeSurface" << std::endl;
		SDL_FreeSurface(surface);
	}

};
