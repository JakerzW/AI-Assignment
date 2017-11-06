#pragma once
#include <memory>
#include <vector>
class Surface;

class Node
{
	private: 
		int m_PosX;
		int m_PosY;
		int c_gridHeight = 25;
		int c_gridWidth = 25;
		int c_nodeWidth = 25;
		int c_nodeHeight = 25;

		Surface* s_surface;
	public:				
		std::shared_ptr<Surface> s_screen;
		int drawNode();
		int getPosX();
		int getPosY();
		void setPosX(int x);
		void setPosY(int x);
		void setNeighbours(std::vector<Node> nodes);
		void Node::setNodeImage(Surface* surfaceImage);
		Surface* Node::getImage();
		std::vector<Node*> neighbours;
};
