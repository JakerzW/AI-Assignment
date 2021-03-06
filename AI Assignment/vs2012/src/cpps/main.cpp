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
#include "../headers/path.h"

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
std::shared_ptr<Surface> s_pathImage2;
std::shared_ptr<Surface> s_screen;

std::vector<Node> m_allNodes;

Player player;
Enemy enemy1;
Enemy enemy2;

void draw(std::vector<Node*> path1, std::vector<Node*> path2);
std::vector<Node*> bfs(std::vector<Node> &allNodes, Player* player, Enemy* enemy);

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	  
	s_screen = Surface::setVideoMode();
	s_tileImage = Surface::loadBmp("vs2012/images/tile.bmp");
	s_pathImage = Surface::loadBmp("vs2012/images/path.bmp");
	s_pathImage2 = Surface::loadBmp("vs2012/images/path2.bmp");

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
			//node.setNodeImage(s_tileImage.get());
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
			//RIGHT
			if (x < (GRIDWIDTH - 1))
			{
				m_allNodes.at(i).neighbours.push_back(&m_allNodes.at(i + 1));
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
			//BELOW
			if (y < (GRIDHEIGHT - 1))
			{
				m_allNodes.at(i).neighbours.push_back(&m_allNodes.at(i + GRIDWIDTH));
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
			//LEFT
			if (x > 0)
			{
				m_allNodes.at(i).neighbours.push_back(&m_allNodes.at(i - 1));
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
	draw(bfs(m_allNodes, &player, &enemy1), bfs(m_allNodes, &player, &enemy2));

	while (!quitGame)
	{	
		
		SDL_Event userInput;
		//SDL_WaitEvent(&userInput);
		bool playerMoved = false;
		bool enemy1StateChanged = false;
		bool enemy2StateChanged = false;
		
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
								playerMoved = true;
							}
							break;
						}
						case SDLK_DOWN:
						{
							if (player.getY() < (GRIDHEIGHT - 1))
							{
								player.setPosY(player.getY() + 1);
								playerMoved = true;
							}
							break;
						}
						case SDLK_LEFT:
						{
							if (player.getX() > 0)
							{
								player.setPosX(player.getX() - 1);
								playerMoved = true;
							}
							break;
						}
						case SDLK_RIGHT:
						{
							if (player.getX() < (GRIDWIDTH - 1))
							{
								player.setPosX(player.getX() + 1);
								playerMoved = true;
							}
							break;
						}
					}
			}
			if (playerMoved)
			{	
				
				if ((std::abs(player.getPosX() - enemy1.getPosX()) < 300) && (std::abs(player.getPosY() - enemy1.getPosY()) < 300) && !enemy1StateChanged)
				{
					enemy1.changeState(1);
					enemy1StateChanged = true;
				}
				if ((std::abs(player.getPosX() - enemy2.getPosX()) < 300) && (std::abs(player.getPosY() - enemy2.getPosY()) < 300) && !enemy2StateChanged)
				{
					enemy2.changeState(1);
					enemy2StateChanged = true;
				}
				if ((player.getPosX() == enemy1.getPosX()) && (player.getPosY() == enemy1.getPosY()) ||
					(player.getPosX() == enemy2.getPosX()) && (player.getPosY() == enemy2.getPosY()))
				{
					quitGame = true;
					enemy1.changeState(0);
					enemy1StateChanged = false;
					enemy2.changeState(0);
					enemy2StateChanged = false;
				}
				std::vector<Node*> enemy1Path = bfs(m_allNodes, &player, &enemy1);
				std::vector<Node*> enemy2Path = bfs(m_allNodes, &player, &enemy2);
				enemy1.move(enemy1Path);
				enemy2.move(enemy2Path);
				draw(bfs(m_allNodes, &player, &enemy1), bfs(m_allNodes, &player, &enemy2));
				playerMoved = false;
			}
		}
		
	}	

	#ifdef _MSC_VER
		//Sleep(1000);
	#else
		sleep(3);
	#endif

	return 0;
}

void drawPath(std::vector<Node*> path, std::shared_ptr<Surface> image)
{
	for (size_t i = 0; i < m_allNodes.size(); i++)
	{
		for (size_t j = 0; j < path.size(); j++)
		{
			if ((m_allNodes.at(i).getPosX() == path.at(j)->getPosX()) && (m_allNodes.at(i).getPosY() == path.at(j)->getPosY()))
			{
				std::cout << "Drawing path node " << i << std::endl;
				std::cout << "Path node x: " << m_allNodes.at(i).getPosX() << " and y: " << m_allNodes.at(i).getPosY() << std::endl;
				m_allNodes.at(i).setNodeImage(image.get());
				m_allNodes.at(i).drawNode();
			}
		}
	}
}

void draw(std::vector<Node*> path1, std::vector<Node*> path2)
{
	//Draw basic tile nodes
	for (size_t i = 0; i < m_allNodes.size(); i++)
	{
		m_allNodes.at(i).setNodeImage(s_tileImage.get());
		m_allNodes.at(i).drawNode();
	}
	if (enemy1.getState() == 1)
	{
		drawPath(path1, s_pathImage);
	}
	if (enemy2.getState() == 1)
	{
		drawPath(path2, s_pathImage2);
	}
	player.drawNode();
	enemy1.drawNode();
	enemy2.drawNode();

	s_screen->flip();
}

std::vector<Node*> bfs(std::vector<Node> &allNodes, Player* player, Enemy* enemy)
{
	std::vector<Node*> open;
	std::set<Node*> closed;
	std::vector<Node*> neighbours;
	std::vector<Node*> parents;

	Node* current;
	Node* start = nullptr;
	Node* end = nullptr;
	Node* neighbour;

	bool inOpen = false;

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

	while (open.size() != 0)
	{
		current = open.front();

		open.erase(open.begin());

		if (current == end)
		{
			while (current != start)
			{
				std::cout << "I am trying to trace back parents\n";
				parents.push_back(current->getParentNode());
				current = current->getParentNode();
			}
			std::cout << "I am returning parents after their creation";
			return parents;
		}

		neighbours = current->getNeighbours();

		for (size_t i = 0; i < neighbours.size(); i++)
		{
			neighbour = neighbours.at(i);

			if (closed.find(neighbour) != closed.end())
			{
				continue;
			}
			for (size_t t = 0; t < open.size(); t++)
			{
				if (open.at(t) == neighbour)
				{
					inOpen = true;
					break;
				}
			}
			if (inOpen == false)
			{
				if (neighbour == nullptr)
				{
					continue;
				}
				neighbour->setParentNode(current);
				open.push_back(neighbour);

				closed.insert(current);
			}
			inOpen = false;
		}
	}
	std::cout << "I am outputting parents\n";
	return parents;
}

//std::vector<Node*> bfs(std::vector<Node> nodes, Enemy* enemy, Player* player)
//{
//	std::vector<Node*> open;
//	std::set<Node*> closed;
//	std::vector<Node*> neighbours;
//	std::vector<Node*> parentNodes;
//
//	//int posX = enemy->GetPosX();
//	//int posY = enemy->GetPosY();
//
//	//std::cout << posX << "\n";
//	//std::cout << posY << "\n";
//
//	Node* sNode;
//	Node* cNode;
//	Node* eNode;
//	Node* cnNode;
//	bool inOpen = false;
//
//	for (size_t i = 0; i < nodes.size(); i++)
//	{
//		if (enemy->getPosX() == nodes.at(i).getPosX()
//			&& enemy->getPosY() == nodes.at(i).getPosY())
//		{
//			sNode = &nodes.at(i);
//			cNode = &nodes.at(i);
//			break;
//		}
//	}
//
//	for (size_t i = 0; i < nodes.size(); i++)
//	{
//		if (player->getPosX() == nodes.at(i).getPosX()
//			&& player->getPosY() == nodes.at(i).getPosY())
//		{
//			eNode = &nodes.at(i);
//			break;
//		}
//	}
//
//	open.push_back(cNode);
//
//	while (open.size() != 0)
//	{
//		cNode = open.front();
//
//		open.erase(open.begin());
//
//
//
//		if (cNode == eNode)
//		{
//			while (cNode != sNode)
//			{
//				parentNodes.push_back(cNode->getParentNode());
//				cNode = cNode->getParentNode();
//			}
//			//DrawPath(parentNodes);
//		}
//		7; //This is a seven (deal with it)
//
//		neighbours = cNode->getNeighbours();
//
//		for (size_t i = 0; i < neighbours.size(); i++)
//		{
//			cnNode = neighbours.at(i);
//
//			if (closed.find(cnNode) != closed.end())
//			{
//				continue;
//			}
//			for (size_t t = 0; t < open.size(); t++)
//			{
//
//				if (open.at(t) == cnNode)
//				{
//					inOpen = true;
//					break;
//				}
//			}
//			if (inOpen == false)
//			{
//
//				if (cnNode == nullptr)
//				{
//					continue;
//				}
//
//				cnNode->setParentNode(cNode);
//				open.push_back(cnNode);
//
//				closed.insert(cNode);
//
//
//			}
//
//			inOpen = false;
//		}
//
//
//		std::cout << cNode << "   -   ";
//		std::cout << cNode->getPosX() << " - ";
//		std::cout << cNode->getPosY() << "\n";
//
//	}
//	return parentNodes;
//}

