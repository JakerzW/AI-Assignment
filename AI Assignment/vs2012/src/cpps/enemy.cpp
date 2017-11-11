#include "../headers/enemy.h"
#include "../headers/surface.h"

void Enemy::init(std::shared_ptr<Surface> screen)
{
	s_enemyImage = Surface::loadBmp("vs2012/images/enemy.bmp");
	setNodeImage(s_enemyImage.get());
	s_screen = screen;
	setPosX(s_startPosX);
	setPosY(s_startPosY);
}

