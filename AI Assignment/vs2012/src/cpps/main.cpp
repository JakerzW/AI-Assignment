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
  std::shared_ptr<Surface> tileImage;
  std::shared_ptr<Surface> playerImage;
  std::shared_ptr<Surface> enemyImage;
  std::shared_ptr<Surface> pathImage;
  std::shared_ptr<Surface> screen;
  
  SDL_Init(SDL_INIT_EVERYTHING);

	  screen = Surface::setVideoMode();
	  tileImage = Surface::loadBmp("vs2012/images/tile.bmp");
	  playerImage = Surface::loadBmp("vs2012/images/player.bmp");
	  enemyImage = Surface::loadBmp("vs2012/images/enemy.bmp");
	  pathImage = Surface::loadBmp("vs2012/images/path.bmp");

	  std::vector<Node> m_allNodes;
	  Player player;
	  player.setStartingPos();
	  Enemy enemy;
	  enemy.setStartingPos();

	  //Create the nodes
	  for (size_t y = 0; y < GRIDHEIGHT; y++)
	  {
		  for (size_t x = 0; x < GRIDWIDTH; x++)
		  {
			  Node node;
			  if (player.getStartingPosX() == x && player.getStartingPosY() == y)
			  {
				  node.setNodeOpen(false);
				  node.setNodeType(1);
				  node.setNodeImage(playerImage.get());
			  }
			  //else if (enemy.getStartingPosX() == x && enemy.getStartingPosY() == y)
			  else if (x == 20 && y == 20)
			  {
				  node.setNodeOpen(false);
				  node.setNodeType(2);
				  node.setNodeImage(enemyImage.get());
			  }
			  else 
			  {
				  node.setNodeImage(tileImage.get());
			  } 
			  node.s_screen = screen;
			  node.setPosX(x);
			  node.setPosY(y);
			  m_allNodes.push_back(node);
		  }
	  }

	  //for (size_t i = 0; i < m_allNodes.size(); i++)
	  //{
		 // //Check the coords against the node being checked - if they match, replace the info with the player/enemy info
		 // if ((m_allNodes.at(i).getPosX() == player.getPosX()) && (m_allNodes.at(i).getPosY() == player.getPosY()))
		 // {
			//  m_allNodes.at(i).setNodeOpen(false);
			//  m_allNodes.at(i).setNodeType(1);
			//  m_allNodes.at(i).setNodeImage(playerImage.get());
		 // }
		 // else if ((m_allNodes.at(i).getPosX() == enemy.getPosX()) && (m_allNodes.at(i).getPosY() == enemy.getPosY()))
		 // {
			//  m_allNodes.at(i).setNodeOpen(false);
			//  m_allNodes.at(i).setNodeType(2);
			//  m_allNodes.at(i).setNodeImage(enemyImage.get());
		 // }
	  //}

	  //THIS NEEDS TO BE IN LOOP - ALL INITIALISATION NEEDS TO HAPPEN BEFORE THE LOOP

	  //Draw basic tile nodes
	  for (size_t i = 0; i < m_allNodes.size(); i++)
	  {
		  m_allNodes.at(i).drawNode();
		  //Image selection needs to be done here
	  }
	  
  screen->flip();

#ifdef _MSC_VER
  Sleep(10000);
#else
  sleep(3);
#endif

  return 0;
}


