#include <SDL/SDL.h>
#undef main
#ifdef _MSC_VER
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "../headers/node.h"
#include "../headers/surface.h"
#include "../headers/player.h"
#include "../headers/enemy.h"

#include <iostream>
#include <memory>
#include <string>
#include <vector>	
#include <set>

#define GRIDWIDTH 25
#define GRIDHEIGHT 25
#define NODEWIDTH 25
#define NODEHEIGHT 25

std::shared_ptr<Surface> s_tileImage;
std::shared_ptr<Surface> s_pathImage;
std::shared_ptr<Surface> s_screen;

std::vector<Node> m_allNodes;
//std::vector<Node> m_queue;

Player player;
Enemy enemy;

void draw();

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	  
	s_screen = Surface::setVideoMode();
	s_tileImage = Surface::loadBmp("vs2012/images/tile.bmp");
	s_pathImage = Surface::loadBmp("vs2012/images/path.bmp");

	//Initialise classes and variables
	
	player.init(s_screen);
	enemy.init(s_screen);

	//Create the nodes
	for (size_t y = 0; y < GRIDHEIGHT; y++)
	{
		for (size_t x = 0; x < GRIDWIDTH; x++)
		{
			Node node;
			/*if (player.getStartingPosX() == x && player.getStartingPosY() == y)
			{
				node.setNodeOpen(false);
				node.setNodeType(1);
				node.setNodeImage(s_playerImage.get());
			}
			else if (enemy.getStartingPosX() == x && enemy.getStartingPosY() == y)
			{
				node.setNodeOpen(false);
				node.setNodeType(2);
				node.setNodeImage(s_enemyImage.get());
			}
			else 
			{
				node.setNodeImage(s_tileImage.get());
			}*/
			node.setNodeImage(s_tileImage.get());
			node.s_screen = s_screen;
			node.setPosX(x);
			node.setPosY(y);
			m_allNodes.push_back(node);
		}
	}

	//Neighbouring
	int i = 0;
	for (size_t y = 0; y < GRIDHEIGHT; y++)	//CHECK NOTES
	{
		for (size_t x = 0; x < GRIDWIDTH; x++)
		{
			//ABOVE LEFT
			if (x > 0 && y > 0)
			{
				m_allNodes.at(i).neighbours.push_back(&m_allNodes.at(i - (GRIDWIDTH + 1)));
			}
			else
			{
				m_allNodes.at(i).neighbours.push_back(NULL);
			}
			//ABOVE
			if (y > 0)
			{
				m_allNodes.at(i).neighbours.push_back(&m_allNodes.at(i - GRIDWIDTH));
			}
			else
			{
				m_allNodes.at(i).neighbours.push_back(NULL);
			}
			//ABOVE RIGHT
			if (x < (GRIDWIDTH - 1) && y > 0)
			{
				m_allNodes.at(i).neighbours.push_back(&m_allNodes.at(i - (GRIDWIDTH - 1)));
			}
			else
			{
				m_allNodes.at(i).neighbours.push_back(NULL);
			}
			//LEFT
			if (x > 0)
			{
				m_allNodes.at(i).neighbours.push_back(&m_allNodes.at(i - 1));
			}
			else
			{
				m_allNodes.at(i).neighbours.push_back(NULL);
			}
			//RIGHT
			if (x < (GRIDWIDTH - 1))
			{
				m_allNodes.at(i).neighbours.push_back(&m_allNodes.at(i + 1));
			}
			else
			{
				m_allNodes.at(i).neighbours.push_back(NULL);
			}
			//BELOW LEFT
			if (x > 0 && y < (GRIDHEIGHT - 1))
			{
				m_allNodes.at(i).neighbours.push_back(&m_allNodes.at(i + (GRIDWIDTH- 1)));
			}
			else
			{
				m_allNodes.at(i).neighbours.push_back(NULL);
			}
			//BELOW
			if (y < (GRIDHEIGHT - 1))
			{
				m_allNodes.at(i).neighbours.push_back(&m_allNodes.at(i + GRIDWIDTH));
			}
			else
			{
				m_allNodes.at(i).neighbours.push_back(NULL);
			}
			//BELOW RIGHT
			if (x < (GRIDWIDTH - 1) && y < (GRIDHEIGHT - 1))
			{
				m_allNodes.at(i).neighbours.push_back(&m_allNodes.at(i + (GRIDWIDTH + 1)));
			}
			else
			{
				m_allNodes.at(i).neighbours.push_back(NULL);
			}
			i++;
		}
	}

	//ALL INITIALISATION NEEDS TO HAPPEN BEFORE THE LOOP	

	bool quitGame = false;

	while (!quitGame)
	{
		draw();
				
		SDL_Event userInput;
		while (SDL_PollEvent(&userInput))
		{
			switch (userInput.type)
			{
				case SDL_KEYDOWN:
					switch (userInput.key.keysym.sym)
					{
					case SDLK_ESCAPE:
						quitGame = true;
						break;
					case SDLK_UP:
						if (player.getY() > 0)
							player.setPosY(player.getY() - 1);
						break;
					case SDLK_DOWN:
						if (player.getY() < (GRIDHEIGHT - 1))
							player.setPosY(player.getY() + 1);
						break;
					case SDLK_LEFT:
						if (player.getX() > 0)
							player.setPosX(player.getX() - 1);
						break;
					case SDLK_RIGHT:
						if (player.getX() < (GRIDWIDTH - 1))
							player.setPosX(player.getX() + 1);
						break;
					}
			}
		}		
	}	

	#ifdef _MSC_VER
		//Sleep(10000);
	#else
		sleep(3);
	#endif

	return 0;
}

void draw()
{
	//Draw basic tile nodes
	for (size_t i = 0; i < m_allNodes.size(); i++)
	{
		m_allNodes.at(i).drawNode();
	}
	player.drawNode();
	enemy.drawNode();
	s_screen->flip();
}

std::vector<Node*> bfs(std::vector<Node> &allNodes, Player* player, Enemy* enemy)
{
	std::vector<Node*> open;
	std::set<Node*> closed;
	std::vector<Node*> neighbours;
	std::vector<Node*> parents;

	Node* startN;
	Node* endN;
	Node* currentN;
	Node* currentNeighbourN;

	bool inOpen = false;

	for (size_t i = 0; i < allNodes.size(); i++)
	{
		//Sets the start and end nodes to the player and enemy nodes
		if ((enemy->getPosX() == allNodes.at(i).getPosX()) && (enemy->getPosY() == allNodes.at(i).getPosY()))
		{
			startN = &allNodes.at(i);
			currentN = &allNodes.at(i);
		}
		if ((player->getPosX() == allNodes.at(i).getPosX()) && (player->getPosY() == allNodes.at(i).getPosY()))
		{
			endN = &allNodes.at(i);
		}
	}

	open.push_back(currentN);

	//Break out clause
	while (open.size() != 0)
	{
		std::cout << "Chris sucks willies.\n";

		open.erase(open.begin());

		if (currentN == endN)
		{
			while (currentN != startN)
			{
				parents.push_back(currentN->getParentNode());
				currentN = currentN->getParentNode();
			}
		}
	}

	neighbours = currentN->getNeighbours();

	for (size_t i = 0; i < neighbours.size(); i++)
	{
		currentNeighbourN = neighbours.at(i);

		if (closed.find(currentNeighbourN) != closed.end())
		{
			continue;
		}

		for (size_t i = 0; i < open.size(); i++)
		{
			if (open.at(i) == currentNeighbourN)
			{
				inOpen = true;
				break;
			}
		}

		if (inOpen == false)
		{
			currentNeighbourN->setParentNode(currentN);
			open.push_back(currentNeighbourN);
		}

		closed.insert(currentN);
	}

	return parents;
}
