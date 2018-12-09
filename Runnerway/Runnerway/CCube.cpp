#include "stdafx.h"

extern GLuint texture[21];

CCube::CCube()

{
}

CCube::CCube(float x, float y, float z, double r)
{
	m_Pos = { x,y,z };
	m_Radius = r;
}

CCube::~CCube()
{
}

void CCube::Draw(int num, float size)
{
	glPushMatrix();
	{
		glTranslated(m_Pos.x, m_Pos.y, m_Pos.z);
		// ≈ÿΩ∫√≥∏¶ ∞¥√ºø° ∏ «Œ
		glBindTexture(GL_TEXTURE_2D, texture[num]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-size, -size, -size);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-size, size, -size);

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(size, size, -size);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(size, -size, -size);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, texture[num]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-size, -size, size);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-size, size, size);

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(size, size, size);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(size, -size, size);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, texture[num]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-size, -size, -size);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-size, size, -size);

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-size, size, size);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-size, -size, size);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, texture[num]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(size, -size, -size);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(size, size, -size);

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(size, size, size);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(size, -size, size);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, texture[num]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-size, -size, -size);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-size, -size, size);

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(size, -size, size);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(size, -size, -size);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, texture[num]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-size, size, -size);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-size, size, size);

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(size, size, size);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(size, size, -size);
		glEnd();
	}
	glPopMatrix();
}

bool CCube::CheckCollPlayerbyItem(float x, float y, float z, float radius)
{
	if (CheckCollRectbyLine(m_Pos.x, x, m_Radius, radius))
		if (CheckCollRectbyLine(m_Pos.y, y, m_Radius, radius))
			if (CheckCollRectbyLine(m_Pos.z, z, m_Radius, radius))  return true;

	return false;
}
