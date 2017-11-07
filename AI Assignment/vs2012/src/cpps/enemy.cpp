#include "../headers/enemy.h"

void Enemy::setStartingPos()
{
	m_posX = s_startPosX * c_nodeWidth;
	m_posY = s_startPosY * c_nodeWidth;
}

int Enemy::getStartingPosX()
{
	return s_startPosX;
}

int Enemy::getStartingPosY()
{
	return s_startPosY;
}

