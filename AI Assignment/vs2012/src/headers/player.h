#pragma once
#include "gameObject.h"

class Player : public GameObject
{
	private:
		int s_startPosX = 4;
		int s_startPosY = 4;
		std::shared_ptr<Surface> s_playerImage;
	public:
		void init(std::shared_ptr<Surface> screen);

};