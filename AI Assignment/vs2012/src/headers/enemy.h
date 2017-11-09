#pragma once
#include "src/headers/gameObject.h"

class Enemy : public GameObject
{
	private:
		int m_posX;
		int m_posY;
		int s_startPosX = 20;
		int s_startPosY = 20;
		int m_state = 0;
	public:
		
		void setStartingPos();
		int getStartingPosX();
		int getStartingPosY();
};
