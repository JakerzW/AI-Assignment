#pragma once
#include <memory>
#include <vector>
class Surface;

class Node
{
	private: 
		int m_posX;
		int m_posY;
		int m_x;
		int m_y;
		bool m_nodeOpen = true;
		int m_nodeType = 0;
		Surface* s_surface;
	public:				
		int c_gridHeight = 25;
		int c_gridWidth = 25;
		int c_nodeWidth = 25;
		int c_nodeHeight = 25;
		std::shared_ptr<Surface> s_screen;
		int drawNode();
		int getPosX();
		int getPosY();
		int getX();
		int getY();
		void setPosX(int x);
		void setPosY(int x);
		void setNodeType(int typeVal);
		void setNodeOpen(bool boolVal);
		int getNodeType();
		void Node::setNodeImage(Surface* surfaceImage);
		Surface* Node::getImage();
		std::vector<Node*> neighbours;
};
