#include "../headers/node.h"
#include "../headers/surface.h"
#include <SDL/SDL.h>
#include <vector>

int Node::drawNode()
{
	s_surface->blit(s_screen, m_posX, m_posY);
	return 0;
}

int Node::getPosX()
{
	return m_posX;
}

int Node::getPosY()
{
	return m_posY;
}

void Node::setPosX(int x)
{
	m_posX = x * c_nodeWidth;
}

void Node::setPosY(int y)
{
	m_posY = y * c_nodeHeight;
}

void Node::setNodeImage(Surface* surfaceImage)
{
	s_surface = surfaceImage;
}

Surface* Node::getImage()
{
	return s_surface;
}

void Node::setNeighbours(std::vector<Node> nodes)
{
	//NEIGHBOURING
	int i = 0;
	for (size_t y = 0; y < c_gridHeight; y++)
	{
		for (size_t x = 0; x < c_gridWidth; x++)
		{
			i++;
			
			//RIGHT AND LEFT
			if (x == (c_gridWidth - 1))	//Left
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
				nodes.at(i).neighbours.push_back(&nodes.at(i + c_gridWidth));
			}
			else if (y == (c_gridHeight - 1))	//Up
			{
				nodes.at(i).neighbours.push_back(&nodes.at(i - c_gridWidth));
			}
			else	//Down and Up
			{
				nodes.at(i).neighbours.push_back(&nodes.at(i + c_gridWidth));
				nodes.at(i).neighbours.push_back(&nodes.at(i - c_gridWidth));
			}

			//DIAGONALS
			if ((y == 0) && (x == 0)) //Top Left Corner
			{
				nodes.at(i).neighbours.push_back(&nodes.at(i + (c_gridWidth + 1)));
			}
			else if ((y == 0) && (x > 0) && (x < (c_gridWidth - 1))) //Top Row
			{
				nodes.at(i).neighbours.push_back(&nodes.at(i + (c_gridWidth + 1)));
				nodes.at(i).neighbours.push_back(&nodes.at(i + (c_gridWidth - 1)));
			}
			else if ((y == 0) && (x == (c_gridWidth - 1))) //Top Right Corner
			{
				nodes.at(i).neighbours.push_back(&nodes.at(i + (c_gridWidth - 1)));
			}
			else if ((x == 0) && (y > 0) && (y < (c_gridHeight - 1)))	//Left Hand Side
			{
				nodes.at(i).neighbours.push_back(&nodes.at(i - (c_gridWidth - 1)));
				nodes.at(i).neighbours.push_back(&nodes.at(i + (c_gridWidth + 1)));
			}
			else if ((y > 0) && (y < (c_gridHeight - 1)) && (x > 0) && (x < (c_gridWidth - 1))) //Middle
			{
				nodes.at(i).neighbours.push_back(&nodes.at(i - (c_gridWidth + 1)));
				nodes.at(i).neighbours.push_back(&nodes.at(i - (c_gridWidth - 1)));
				nodes.at(i).neighbours.push_back(&nodes.at(i + (c_gridWidth - 1)));
				nodes.at(i).neighbours.push_back(&nodes.at(i + (c_gridWidth + 1)));
			}
			else if ((x == (c_gridWidth - 1)) && (y > 0) && (y < (c_gridHeight - 1))) //Right Hand Side
			{
				nodes.at(i).neighbours.push_back(&nodes.at(i - (c_gridWidth + 1)));
				nodes.at(i).neighbours.push_back(&nodes.at(i + (c_gridWidth - 1)));
			}
			else if ((x == 0) && (y == (c_gridHeight - 1))) //Bottom Left Corner
			{
				nodes.at(i).neighbours.push_back(&nodes.at(i - (c_gridWidth - 1)));
			}
			else if ((y == (c_gridHeight - 1)) && (x > 0) && (x < (c_gridWidth - 1))) //Bottom Row
			{
				nodes.at(i).neighbours.push_back(&nodes.at(i - (c_gridWidth + 1)));
				nodes.at(i).neighbours.push_back(&nodes.at(i - (c_gridWidth - 1)));
			}
			else if ((x == (c_gridWidth - 1)) && (y == (c_gridHeight - 1))) //Bottom Right Corner
			{
				nodes.at(i).neighbours.push_back(&nodes.at(i - (c_gridWidth + 1)));
			}
		}
	}
}

void Node::setNodeType(int typeVal)
{
	m_nodeType = typeVal;
}

void Node::setNodeOpen(bool boolVal)
{
	m_nodeOpen = boolVal;
}

int Node::getNodeType()
{
	return m_nodeType;
}
