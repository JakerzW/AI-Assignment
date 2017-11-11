#pragma once
#include "gameObject.h"

class Enemy : public GameObject
{
	private:
		int s_startPosX = 20;
		int s_startPosY = 20;
		std::shared_ptr<Surface> s_enemyImage;
	public:
		void init(std::shared_ptr<Surface> screen);
};
