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

Player player;
Enemy enemy1;
Enemy enemy2;

void draw(std::vector<Node*> path);
std::vector<Node*> bfs(std::vector<Node> &allNodes, Player* player, Enemy* enemy);

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	  
	s_screen = Surface::setVideoMode();
	s_tileImage = Surface::loadBmp("vs2012/images/tile.bmp");
	s_pathImage = Surface::loadBmp("vs2012/images/path.bmp");

	//Initialise classes and variables
	
	player.init(s_screen);
	enemy1.init(s_screen, 1);
	enemy2.init(s_screen, 2);

	//Create the nodes
	for (size_t y = 0; y < GRIDHEIGHT; y++)
	{
		for (size_t x = 0; x < GRIDWIDTH; x++)
		{
			Node node;
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
						{
							if (player.getY() > 0)
							{
								player.setPosY(player.getY() - 1);
								enemy1.move();
								enemy2.move();
							}
							break;
						}
						case SDLK_DOWN:
						{
							if (player.getY() < (GRIDHEIGHT - 1))
							{
								player.setPosY(player.getY() + 1);
								enemy1.move();
								enemy2.move();
							}
							break;
						}
						case SDLK_LEFT:
						{
							if (player.getX() > 0)
							{
								player.setPosX(player.getX() - 1);
								enemy1.move();
								enemy2.move();
							}
							break;
						}
						case SDLK_RIGHT:
						{
							if (player.getX() < (GRIDWIDTH - 1))
							{
								player.setPosX(player.getX() + 1);
								enemy1.move();
								enemy2.move();
							}
							break;
						}
					}
			}
		}
		//std::vector<Node*> path = bfs(m_allNodes, &player, &enemy);
		draw(bfs(m_allNodes, &player, &enemy2));
		//Sleep(10000);
		if ((player.getPosX() == enemy1.getPosX()) && (player.getPosY() == enemy1.getPosY()) || (player.getPosX() == enemy2.getPosX()) && (player.getPosY() == enemy2.getPosY()))
		{
			quitGame = true;
		}
	}	

	#ifdef _MSC_VER
		//Sleep(10000);
	#else
		sleep(3);
	#endif

	return 0;
}

void draw(std::vector<Node*> path)
{
	//Draw basic tile nodes
	for (size_t i = 0; i < m_allNodes.size(); i++)
	{
		m_allNodes.at(i).drawNode();
	}
	player.drawNode();
	enemy1.drawNode();
	enemy2.drawNode();
	for (size_t i = 0; i < path.size(); i++)
	{
		path.at(i)->setNodeImage(s_pathImage.get());
		path.at(i)->drawNode();
	}
	s_screen->flip();
}

//std::vector<Node*> bfs(std::vector<Node> &allNodes, Player* player, Enemy* enemy)
//{
//	std::vector<Node*> open;
//	std::set<Node*> closed;
//	std::vector<Node*> neighbours;
//	std::vector<Node*> parents;
//
//	Node* startN;
//	Node* endN;
//	Node* currentN;
//	Node* currentNeighbourN;
//
//	
//
//	for (size_t i = 0; i < allNodes.size(); i++)
//	{
//		//Sets the start and end nodes to the player and enemy nodes
//		if ((enemy->getPosX() == allNodes.at(i).getPosX()) && (enemy->getPosY() == allNodes.at(i).getPosY()))
//		{
//			startN = &allNodes.at(i);
//		}
//		if ((player->getPosX() == allNodes.at(i).getPosX()) && (player->getPosY() == allNodes.at(i).getPosY()))
//		{
//			endN = &allNodes.at(i);
//		}
//	}
//
//	currentN = startN;
//	open.push_back(currentN);
//
//	//Break out clause
//	while (open.size() != 0)
//	{
//		std::cout << "I'm stuck in the loop!\n";
//
//		open.erase(open.begin());
//
//		if (currentN == endN)
//		{
//			open.clear();
//			while (currentN != startN)
//			{
//				parents.push_back(currentN->getParentNode());
//				currentN = currentN->getParentNode();
//			}
//			return parents;
//		}
//
//		neighbours = currentN->getNeighbours();
//
//		for (size_t i = 0; i < neighbours.size(); i++)
//		{
//			bool inOpen = false;
//
//			currentNeighbourN = neighbours.at(i);
//
//			if (closed.find(currentNeighbourN) != closed.end())
//			{
//				continue;
//			}
//
//			for (size_t n = 0; n < open.size(); n++)
//			{
//				if (open.at(n) == currentNeighbourN)
//				{
//					inOpen = true;
//					break;
//				}
//			}
//
//			if (inOpen == false)
//			{	
//				if (currentNeighbourN != nullptr)
//				{
//					currentNeighbourN->setParentNode(currentN);
//					open.push_back(currentNeighbourN);
//				}
//			}
//			closed.insert(currentN);
//			//currentN = currentNeighbourN;
//		}
//	}
//
//	return parents;
//}

std::vector<Node*> bfs(std::vector<Node> &allNodes, Player* player, Enemy* enemy)
{
	std::vector<Node*> open;
	std::vector<Node*> closed;
	std::vector<Node*> neighbours;
	std::vector<Node*> parents;

	Node* current;
	Node* start;
	Node* end;
	Node* neighbour;

	for (size_t i = 0; i < allNodes.size(); i++)
	{
		//Sets the start and end nodes to the player and enemy nodes
		if ((enemy->getPosX() == allNodes.at(i).getPosX()) && (enemy->getPosY() == allNodes.at(i).getPosY()))
		{
			start = &allNodes.at(i);
		}
		if ((player->getPosX() == allNodes.at(i).getPosX()) && (player->getPosY() == allNodes.at(i).getPosY()))
		{
			end = &allNodes.at(i);
		}
	}
	//Set the start node as the current node and put it into the open queue
	current = start;
	open.push_back(current);

	//Do the search until all nodes in the open vector have been searched through
	while (open.size() != 0)
	{
		//Remove the first start node
		open.erase(open.begin());

		//When the end is reached, trace back to the start node, pushing all those nodes into the parent vector
		if (current == end)
		{
			open.clear;
			while (current != start)
			{
				parents.push_back(current->getParentNode());
				current = current->getParentNode();
			}
			return parents;
			//Return the parents path and end the function
		}

		neighbours = current->getNeighbours();

		for (size_t i = 0; i < neighbours.size(); i++)
		{
			bool inOpen = neighbours.at(i)->getInOpen();

			if (!inOpen)
			{
				neighbours.at(i)->setInOpen(true);
				open.push_back(neighbours.at(i));
			}
		}
	}
}
