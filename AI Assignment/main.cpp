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

#include "node.h"
#include "surface.h"

#include <iostream>
#include <memory>
#include <string>

int main(int argc, char *argv[])
{
  std::shared_ptr<Surface> image;
  std::shared_ptr<Surface> screen;
  

  SDL_Init(SDL_INIT_EVERYTHING);

  screen = Surface::setVideoMode();
  image = Surface::loadBmp("tile.bmp");

  std::vector<Node> nodes;
  

	  for (size_t y = 0; y < GRIDHEIGHT; y++)
	  {
		  for (size_t x = 0; x < GRIDWIDTH; x++)
		  {
			  Node node;
			  node.setSurface(image.get());
			  node.s_screen = screen;
			  node.setPosX(x);
			  node.setPosY(y);
			  //node.setNeighbours(nodes);
			  nodes.push_back(node);
			  
		  }
	  }


	  //NEIGHBOURING
	  int i = 0;
	  for (size_t y = 0; y < GRIDHEIGHT; y++)
	  {
		  for (size_t x = 0; x < GRIDWIDTH; x++)
		  {
			  //RIGHT AND LEFT
			  if (x == (GRIDWIDTH - 1))	//Left
			  {
				  nodes.at(i).neighbours.push_back(&nodes.at(i - 1));
			  }
			  else if (x == 0) //Right
			  {
				  nodes.at(i).neighbours.push_back(&nodes.at(i + 1));
			  }
			  else	//Left and Right
			  {
				  nodes.at(i).neighbours.push_back(&nodes.at(i - 1));
				  nodes.at(i).neighbours.push_back(&nodes.at(i + 1));
			  }

			  //UP AND DOWN
			  if (y == 0)	//Down
			  {
				  nodes.at(i).neighbours.push_back(&nodes.at(i + GRIDWIDTH));
			  }
			  else if (y == (GRIDHEIGHT - 1))	//Up
			  {
				  nodes.at(i).neighbours.push_back(&nodes.at(i - GRIDWIDTH));
			  }
			  else	//Down and Up
			  {
				  nodes.at(i).neighbours.push_back(&nodes.at(i + GRIDWIDTH));
				  nodes.at(i).neighbours.push_back(&nodes.at(i - GRIDWIDTH));
			  }

			  //DIAGONALS
			  if ((y == 0) && (x == 0)) //Top Left Corner
			  {
				  nodes.at(i).neighbours.push_back(&nodes.at(i + (GRIDWIDTH + 1)));
			  }
			  else if ((y == 0) && (x > 0) && (x < (GRIDWIDTH - 1))) //Top Row
			  {
				  nodes.at(i).neighbours.push_back(&nodes.at(i + (GRIDWIDTH + 1)));
				  nodes.at(i).neighbours.push_back(&nodes.at(i + (GRIDWIDTH - 1)));
			  }
			  else if ((y == 0) && (x == (GRIDWIDTH -1))) //Top Right Corner
			  {
				  nodes.at(i).neighbours.push_back(&nodes.at(i + (GRIDWIDTH - 1)));
			  }
			  else if ((x == 0) && (y > 0) && (y < (GRIDHEIGHT - 1)))	//Left Hand Side
			  {
				  nodes.at(i).neighbours.push_back(&nodes.at(i - (GRIDWIDTH - 1)));
				  nodes.at(i).neighbours.push_back(&nodes.at(i + (GRIDWIDTH + 1)));
			  }
			  else if ((y > 0) && (y < (GRIDHEIGHT - 1)) && (x > 0) && (x < (GRIDWIDTH - 1))) //Middle
			  {
				  nodes.at(i).neighbours.push_back(&nodes.at(i - (GRIDWIDTH + 1)));
				  nodes.at(i).neighbours.push_back(&nodes.at(i - (GRIDWIDTH - 1)));
				  nodes.at(i).neighbours.push_back(&nodes.at(i + (GRIDWIDTH - 1)));
				  nodes.at(i).neighbours.push_back(&nodes.at(i + (GRIDWIDTH + 1)));
			  }
			  else if ((x == (GRIDWIDTH - 1)) && (y > 0) && (y < (GRIDHEIGHT - 1))) //Right Hand Side
			  {
				  nodes.at(i).neighbours.push_back(&nodes.at(i - (GRIDWIDTH + 1)));
				  nodes.at(i).neighbours.push_back(&nodes.at(i + (GRIDWIDTH - 1)));
			  }
			  else if ((x == 0) && (y == (GRIDHEIGHT - 1))) //Bottom Left Corner
			  {
				  nodes.at(i).neighbours.push_back(&nodes.at(i - (GRIDWIDTH - 1)));
			  }
			  else if ((y == (GRIDHEIGHT - 1)) && (x > 0) && (x < (GRIDWIDTH - 1))) //Bottom Row
			  {
				  nodes.at(i).neighbours.push_back(&nodes.at(i - (GRIDWIDTH + 1)));
				  nodes.at(i).neighbours.push_back(&nodes.at(i - (GRIDWIDTH - 1)));
			  }
			  else if ((x == (GRIDWIDTH - 1)) && (y == (GRIDHEIGHT - 1))) //Bottom Right Corner
			  {
				  nodes.at(i).neighbours.push_back(&nodes.at(i - (GRIDWIDTH + 1)));
			  }
			  i++;
		  }
	  }

	  /*
	  Pseudocode for breadth first search:

	  Set up a queue
	  Set up a list for visited nodes

	  While the queue is not empty or node not found do
		Add node to visited list
		If not the node you're looking for do nothing
		If node you are looking for end the search
		Increment node number				
	  */


	  for (size_t i = 0; i < nodes.size(); i++)
	  {
		  nodes.at(i).drawNode();
	  }

  screen->flip();

#ifdef _MSC_VER
  Sleep(10000);
#else
  sleep(3);
#endif

  return 0;
}
