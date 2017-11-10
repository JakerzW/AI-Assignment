#include "..\headers\gameObject.h"

int GameObject::getState()
{
	return m_state;
}

void GameObject::changeState(int stateVal)
{
	m_state = stateVal;
}

int GameObject::getStartingPosX()
{
	return s_startPosX;
}

int GameObject::getStartingPosY()
{
	return s_startPosY;
}


