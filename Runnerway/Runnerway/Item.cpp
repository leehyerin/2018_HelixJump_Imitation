#include "stdafx.h"

void Item::SetColor(float R, float G, float B)
{
	m_Color.x = R;
	m_Color.y = G;
	m_Color.z = B;
}

void Item::Draw()
{
	glColor3f(m_Color.x, m_Color.y, m_Color.z);
	CCube::Draw();
}