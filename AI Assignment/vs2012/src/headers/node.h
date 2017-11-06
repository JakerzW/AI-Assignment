#pragma once
#include <memory>
#include <vector>
class Surface;

class Node
{
	private: 
		int m_posX;
		int m_posY;
		int c_gridHeight = 25;
		int c_gridWidth = 25;
		int c_nodeWidth = 25;
		int c_nodeHeight = 25;
		bool m_nodeOpen;
		int m_nodeType;

		Surface* s_surface;
	public:				
		std::shared_ptr<Surface> s_screen;
		int drawNode();
		int getPosX();
		int getPosY();
		void setPosX(int x);
		void setPosY(int x);
		void setNeighbours(std::vector<Node> nodes);
		void setNodeType(int typeVal);
		void setNodeBool(bool boolVal);
		int getNodeType();
		void Node::setNodeImage(Surface* surfaceImage);
		Surface* Node::getImage();
		std::vector<Node*> neighbours;
};
