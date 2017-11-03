#pragma once
#include <memory>
#include <vector>
#include "surface.h"

class allNodes
{
	private:
		int c_nodeWidth = 25;
		int c_nodeHeight = 25;
	
	public:
		allNodes();
		~allNodes();
		void setupNodes(std::shared_ptr<Surface> screen, std::shared_ptr<Surface> image);
		std::vector<Node> m_allNodes;
};