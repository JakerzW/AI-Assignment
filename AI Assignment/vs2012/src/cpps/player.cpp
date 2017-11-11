#include "../headers/player.h"
#include "../headers/surface.h"

void Player::init(std::shared_ptr<Surface> screen)
{
	s_playerImage = Surface::loadBmp("vs2012/images/player.bmp");
	setNodeImage(s_playerImage.get());
	s_screen = screen;
	setPosX(s_startPosX);
	setPosY(s_startPosY);
}




