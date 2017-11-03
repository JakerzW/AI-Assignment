#include <SDL/SDL.h>
#undef main

//#define GRIDWIDTH 25
//#define GRIDHEIGHT 25

#ifdef _MSC_VER
#include <windows.h>
#else
#include <unistd.h>
#endif
#include <vector>

#include "../headers/node.h"
#include "../headers/surface.h"
#include "../headers/allNodes.h"

#include <iostream>
#include <memory>
#include <string>

int main(int argc, char *argv[])
{
  std::shared_ptr<Surface> image;
  std::shared_ptr<Surface> screen;
  
  SDL_Init(SDL_INIT_EVERYTHING);

  allNodes allNodes;
  allNodes.setupNodes(screen, image);

	  for (size_t i = 0; i < allNodes.m_allNodes.size(); i++)
	  {
		  allNodes.m_allNodes.at(i).drawNode();
	  }

  screen->flip();

#ifdef _MSC_VER
  Sleep(10000);
#else
  sleep(3);
#endif

  return 0;
}
