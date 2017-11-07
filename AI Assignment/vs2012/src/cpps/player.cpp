#include "../headers/player.h"

void Player::setStartingPos()
{
	m_xPos = s_startPosX * c_nodeWidth;
	m_yPos = s_startPosY * c_nodeWidth;
}

int Player::getStartingPosX()
{
	return s_startPosX;
}

int Player::getStartingPosY()
{
	return s_startPosY;
}


