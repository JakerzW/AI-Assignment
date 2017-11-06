#pragma once
#include "node.h"

class Enemy : public Node
{
	private:
		int m_posX;
		int m_posY;
		int s_startPosX;
		int s_startPosY;

	public:
		void setStartingPos();
};
