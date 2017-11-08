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

int Node::getX()
{
	return m_x;
}

int Node::getY()
{
	return m_y;
}

void Node::setPosX(int x)
{
	m_x = x;
	m_posX = x * c_nodeWidth;
}

void Node::setPosY(int y)
{
	m_y = y;
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

void Node::setNeighbours(std::vector<Node> allNodes)
{
	//NEIGHBOURING
	int i = 0;
	for (size_t y = 0; y < c_gridHeight; y++)	//CHECK NOTES
	{
		for (size_t x = 0; x < c_gridWidth; x++)
		{
			//ABOVE LEFT
			if (x > 0 && y > 0)
			{
				allNodes.at(i).neighbours.push_back(&allNodes.at(i - (c_gridWidth + 1)));
			}
			else
			{
				allNodes.at(i).neighbours.push_back(NULL);
			}
			//ABOVE
			if (y > 0)
			{
				allNodes.at(i).neighbours.push_back(&allNodes.at(i - c_gridWidth));
			}
			else
			{
				allNodes.at(i).neighbours.push_back(NULL);
			}
			//ABOVE RIGHT
			if (x < (c_gridWidth - 1) && y > 0)
			{
				allNodes.at(i).neighbours.push_back(&allNodes.at(i - (c_gridWidth - 1)));
			}
			else
			{
				allNodes.at(i).neighbours.push_back(NULL);
			}
			//LEFT
			if (x > 0)
			{
				allNodes.at(i).neighbours.push_back(&allNodes.at(i - 1));
			}
			else
			{
				allNodes.at(i).neighbours.push_back(NULL);
			}
			//RIGHT
			if (x < (c_gridWidth - 1))
			{
				allNodes.at(i).neighbours.push_back(&allNodes.at(i + 1));
			}
			else
			{
				allNodes.at(i).neighbours.push_back(NULL);
			}
			//BELOW LEFT
			if (x > 0 && y < (c_gridHeight - 1))
			{
				allNodes.at(i).neighbours.push_back(&allNodes.at(i + (c_gridWidth - 1)));
			}
			else
			{
				allNodes.at(i).neighbours.push_back(NULL);
			}
			//BELOW
			if (y < (c_gridHeight - 1))
			{
				allNodes.at(i).neighbours.push_back(&allNodes.at(i + c_gridWidth));
			}
			else
			{
				allNodes.at(i).neighbours.push_back(NULL);
			}
			//BELOW RIGHT
			if (x < (c_gridWidth - 1) && y < (c_gridHeight - 1))
			{
				allNodes.at(i).neighbours.push_back(&allNodes.at(i + (c_gridWidth + 1)));
			}
			else
			{
				allNodes.at(i).neighbours.push_back(NULL);
			}
			i++;
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
