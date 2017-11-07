#pragma once
#include "node.h"

class Player : public Node
{
	private:
		int m_xPos;
		int m_yPos;
		int s_startPosX = 4;
		int s_startPosY = 4;
	public:
		void setStartingPos();
		int getStartingPosX();
		int getStartingPosY();

};