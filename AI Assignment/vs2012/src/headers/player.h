#pragma once
#include "node.h"

class Player : public Node
{
	private:
		int m_xPos;
		int m_yPos;
		int s_startPosX;
		int s_startPosY;
	public:
		void setStartingPos();
};