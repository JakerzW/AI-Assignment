#include <SDL/SDL.h>
#undef main

#define GRIDWIDTH 25
#define GRIDHEIGHT 25

#ifdef _MSC_VER
#include <windows.h>
#else
#include <unistd.h>
#endif
#include <vector>

#include "../headers/node.h"
#include "../headers/surface.h"

#include <iostream>
#include <memory>
#include <string>

int main(int argc, char *argv[])
{
  std::shared_ptr<Surface> image;
  std::shared_ptr<Surface> screen;
  
  SDL_Init(SDL_INIT_EVERYTHING);

	  screen = Surface::setVideoMode();
	  image = Surface::loadBmp("vs2012/images/tile.bmp");

	  std::vector<Node> m_allNodes;

	  //Create the nodes
	  for (size_t y = 0; y < GRIDHEIGHT; y++)
	  {
		  for (size_t x = 0; x < GRIDWIDTH; x++)
		  {
			  Node node;
			  node.setNodeImage(image.get());
			  node.s_screen = screen;
			  node.setPosX(x);
			  node.setPosY(y);
			  m_allNodes.push_back(node);
		  }
	  }

	  //Draw nodes
	  for (size_t i = 0; i < m_allNodes.size(); i++)
	  {
		  m_allNodes.at(i).drawNode();
	  }


  screen->flip();

#ifdef _MSC_VER
  Sleep(10000);
#else
  sleep(3);
#endif

  return 0;
}


