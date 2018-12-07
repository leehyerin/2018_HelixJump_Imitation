#include "stdafx.h"

void Item::Draw()
{
	glColor3f(m_Color.x, m_Color.y, m_Color.z);

	CCube::Draw();
}