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
#include "../headers/player.h"
#include "../headers/enemy.h"

#include <iostream>
#include <memory>
#include <string>

int main(int argc, char *argv[])
{
  std::shared_ptr<Surface> image;
  std::shared_ptr<Surface> screen;
  
  SDL_Init(SDL_INIT_EVERYTHING);

	  screen = Surface::setVideoMode();

	  std::vector<Node> m_allNodes;
	  Player player;
	  Enemy enemy;

	  //Create the nodes
	  for (size_t y = 0; y < GRIDHEIGHT; y++)
	  {
		  for (size_t x = 0; x < GRIDWIDTH; x++)
		  {
			  image = Surface::loadBmp("vs2012/images/tile.bmp");

			  Node node;
			  node.setNodeImage(image.get());
			  node.s_screen = screen;
			  node.setPosX(x);
			  node.setPosY(y);
			  m_allNodes.push_back(node);
		  }
	  }

	  for (size_t i = 0; i < m_allNodes.size(); i++)
	  {
		  //Check the coords against the node being checked - if they match, replace the info with the player/enemy info

	  }

	  //THIS NEEDS TO BE IN LOOP - ALL INITIALISATION NEEDS TO HAPPEN BEFORE THE LOOP

	  //Draw basic tile nodes
	  for (size_t i = 0; i < m_allNodes.size(); i++)
	  {
		  m_allNodes.at(i).drawNode();
		  //Image selection needs to be done here
	  }

	  //Check to draw player node
	  for (size_t i = 0; i < m_allNodes.size(); i++)
	  {
		  //if (player.getPosX() == m_allNodes.at(i).getPosX())
			 // //do something;
			 // ;
	  }


  screen->flip();

#ifdef _MSC_VER
  Sleep(10000);
#else
  sleep(3);
#endif

  return 0;
}


