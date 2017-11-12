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

void Node::setParentNode(Node* pNode)
{
	m_parentNode = pNode;
}

Node* Node::getParentNode()
{
	return m_parentNode;
}

std::vector<Node*> Node::getNeighbours()
{
	return neighbours;
}
