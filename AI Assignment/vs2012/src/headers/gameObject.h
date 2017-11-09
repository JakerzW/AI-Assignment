#pragma once
#include "src/headers/node.h"

class GameObject : public Node
{
	private:
		int m_xPos;
		int m_yPos;
		int s_startPosX = 4;
		int s_startPosY = 4;
		int m_state = 0;
	public:
		//int getState();
		//void changeState(int stateVal);
		int getStartingPosX();
		int getStartingPosY();

};