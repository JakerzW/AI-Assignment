#include "../headers/allNodes.h"
#include "../headers/node.h"

allNodes::allNodes()
{
}

allNodes::~allNodes()
{
}

void allNodes::setupNodes(std::shared_ptr<Surface> screen, std::shared_ptr<Surface> image)
{
	screen = Surface::setVideoMode();
	image = Surface::loadBmp("tile.bmp");
	
	//Create the nodes
	for (size_t y = 0; y < c_nodeHeight; y++)
	{
		for (size_t x = 0; x < c_nodeWidth; x++)
		{
			Node node;
			node.setSurface(image.get());
			node.s_screen = screen;
			node.setPosX(x);
			node.setPosY(y);
			m_nodes.push_back(node);
		}
	}
}
