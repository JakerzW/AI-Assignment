#pragma once
#include <memory>
#include <vector>
class Surface;

class Node
{
	private: 
		int m_PosX;
		int m_PosY;

		Surface* s_surface;
	public:				
		std::shared_ptr<Surface> s_screen;
		int drawNode();
		int getPosX();
		int getPosY();
		void setPosX(int x);
		void setPosY(int x);
		void setNeighbours(std::vector<Node> nodes;);
		void Node::setSurface(Surface* surfaceImage);
		Surface* Node::getImage();
		std::vector<Node*> neighbours;
};
