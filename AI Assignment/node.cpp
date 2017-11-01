#include "node.h"
#include "surface.h"
#include <SDL/SDL.h>
#include <vector>
#define NODEWIDTH 25;
#define NODEHEIGHT 25;

int Node::drawNode()
{
	s_surface->blit(s_screen, m_PosX, m_PosY);
	return 0;
}

int Node::getPosX()
{
	return m_PosX;
}

int Node::getPosY()
{
	return m_PosY;
}

void Node::setPosX(int x)
{
	m_PosX = x * NODEWIDTH;
}

void Node::setPosY(int y)
{
	m_PosY = y * NODEHEIGHT;
}

void Node::setSurface(Surface* surfaceImage)
{
	s_surface = surfaceImage;
}

Surface* Node::getImage()
{
	return s_surface;
}

/*void Node::setNeighbours(std::vector<Node> nodes)
{
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
			else if ((y == 0) && (x == (GRIDWIDTH - 1))) //Top Right Corner
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
}*/