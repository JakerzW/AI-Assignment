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

void Enemy::move(std::vector<Node*> path)
{
	switch (m_state)
	{
		case 0:
		{
			//Wandering
			int dir = rand() % 4;
			bool dirValid = true;
			bool moveMade = false;
			while (dirValid && !moveMade)
			{
				switch (dir)
				{
					case 0:
					{
						if (getY() > 0)
						{
							setPosY(getY() - 1);
							moveMade = true;
						}
						else
							dirValid = false;
						break;
					}
					case 1:
					{
						if (getX() < c_gridWidth - 1)
						{
							setPosX(getX() + 1);
							moveMade = true;
						}
						else
							dirValid = false;
						break;
					}
					case 2:
					{
						if (getY() < (c_gridHeight - 1))
						{
							setPosY(getY() + 1);
							moveMade = true;
						}
						else
							dirValid = false;
						break;
					}
					case 3:
					{	
						if (getX() > 0)
						{
							setPosX(getX() - 1);
							moveMade = true;
						}
						else
							dirValid = false;
						break;
					}
				}
			}

			break;
		}
		case 1:
		{
			//Chase
			int x = path.at(path.size() - 2)->getPosX() / c_nodeWidth;
			setPosX(x);
			int y = (path.at(path.size() - 2)->getPosY() / c_nodeHeight);
			setPosY(y);
			break;
		}
		default: 
			break;
	}
}

int Enemy::getState()
{
	return m_state;
}

void Enemy::changeState(int stateVal)
{
	m_state = stateVal;
}

