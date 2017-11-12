#pragma once
#include "..\headers\node.h"

class Path : public Node
{
	private:
		std::shared_ptr<Surface> s_pathImage;
	public:
		void init(std::shared_ptr<Surface> screen);
};
