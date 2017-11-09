#pragma once
#include "node.h"

class GameObject : public Node
{
	protected:
		int m_xPos;
		int m_yPos;
		int m_state = 0;
		int s_startPosX;
		int s_startPosY;

	public:
		int getState();
		void changeState(int stateVal);
		int getStartingPosX();
		int getStartingPosY();

};