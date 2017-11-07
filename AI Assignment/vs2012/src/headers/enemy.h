#pragma once
#include "node.h"

class Enemy : public Node
{
	private:
		int m_posX;
		int m_posY;
		int s_startPosX = 20;
		int s_startPosY = 20;

	public:
		void setStartingPos();
		int getStartingPosX();
		int getStartingPosY();
};
