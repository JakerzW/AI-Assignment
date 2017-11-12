#include "..\headers\path.h"
#include "..\headers\surface.h"

void Path::init(std::shared_ptr<Surface> screen)
{
	s_pathImage = Surface::loadBmp("vs2012/images/path.bmp");
	setNodeImage(s_pathImage.get());
	s_screen = screen;
}
