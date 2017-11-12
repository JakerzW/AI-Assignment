#pragma once
#include "gameObject.h"

class Enemy : public GameObject
{
	private:
		int s_startPosX;
		int s_startPosY;
		int m_state = 0;
		std::shared_ptr<Surface> s_enemyImage;
	public:
		void init(std::shared_ptr<Surface> screen, int enemyNumber);
		void move();
		int getState();
		void changeState(int stateVal);
};
