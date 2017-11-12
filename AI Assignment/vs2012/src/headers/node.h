#pragma once
#include <memory>
#include <vector>
class Surface;

class Node
{
	public: 
		std::shared_ptr<Surface> s_screen;
		std::vector<Node*> neighbours;
		
	protected: 
		int m_posX;
		int m_posY;
		int m_x;
		int m_y;
		bool m_nodeOpen = true;
		int m_nodeType = 0;
		Surface* s_surface;
		int c_gridHeight = 25;
		int c_gridWidth = 25;
		int c_nodeWidth = 25;
		int c_nodeHeight = 25;
		Node* m_parentNode;

	public:
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
		void setParentNode(Node* pNode);
		Node* getParentNode();
		std::vector<Node*> getNeighbours();
		void Node::setNodeImage(Surface* surfaceImage);
		Surface* Node::getImage();
};
