#include "stdafx.h"

void Item::Draw()
{
	if (m_Type == DASH)
		YELLOW;
	else if (m_Type == BOMB)
		BLUE;
	else if (m_Type == ANSWER)
		RED;

	CCube::Draw();
}