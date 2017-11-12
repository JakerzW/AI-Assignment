#include "../headers/enemy.h"
#include "../headers/surface.h"

void Enemy::init(std::shared_ptr<Surface> screen, int enemyNumber)
{
	s_enemyImage = Surface::loadBmp("vs2012/images/enemy.bmp");
	setNodeImage(s_enemyImage.get());
	s_screen = screen;
	switch(enemyNumber)
	{
		case 1:
		{	
			s_startPosX = 20;
			s_startPosY = 4;
			break;
		}
		case 2:
		{
			s_startPosX = 20;
			s_startPosY = 20;
			break;
		}
	}
	setPosX(s_startPosX);
	setPosY(s_startPosY);
}

