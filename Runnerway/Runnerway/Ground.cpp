#include "stdafx.h"
#define CURVATURE 0.15f //°î·ü

Ground::Ground()
{
	float angle = 0;
	float Floordegree = 0;
	float radius = 20;

	float x{ 0 }, y{ 0 }, z{ 0 };

	for (z = 0.0; z > -80.0; z -= 0.25)
	{
		Floordegree += CURVATURE;
		y += 0.1f;
		vMap.push_back(Map{ MyVec{ x, y, z }, Floordegree });
	}

	for (z = -80.0; z > -160.0; z -= 0.25)
	{
		Floordegree -= CURVATURE;

		vMap.push_back(Map{ MyVec{ x, 0.f, z }, Floordegree });
	}

	for (z = -160.0; z > -240.0; z -= 0.25)
	{
		Floordegree += CURVATURE;

		vMap.push_back(Map{ MyVec{ x, 0.f, z }, Floordegree });
	}

	for (z = -240.0; z > -320.0; z -= 0.25)
	{
		Floordegree -= CURVATURE;

		vMap.push_back(Map{ MyVec{ x, 0.f, z }, Floordegree });
	}

	for (z = -320.0; z > -400.0; z -= 0.25)
	{
		Floordegree += CURVATURE;

		vMap.push_back(Map{ MyVec{ x, 0.f, z }, Floordegree });
	}

	for (z = -400.0; z > -480.0; z -= 0.25)
	{
		Floordegree -= CURVATURE;

		vMap.push_back(Map{ MyVec{ x, 0.f, z }, Floordegree });
	}
}

Ground::~Ground()
{
}

void Ground::Draw(bool b) //true Á¾ 
{
	SOIL;
	if (b)
	{
		for (auto d : vMap)
			DrawHorizonQuads(d.m_pos.x, d.m_pos.y, d.m_pos.z, d.m_degree);
	}
	else 
	{
		for (auto d : vMap)
			DrawVerticalQuads(d.m_pos.x, d.m_pos.y, d.m_pos.z);
	}
}

void Ground::DrawHorizonQuads(float x, float y, float z, float degree)
{
	glPushMatrix();
	{
		glTranslatef(x , y, z - 0.5f);
		glRotatef(degree, 0, 1, 0);	
		glRotatef(y, 1, 0, 0);

		glBegin(GL_QUADS);
		{
			glVertex3f(+30.f, 0, 0.f);
			glVertex3f(+30.f, 0, 1.f);
			glVertex3f(-30.f, 0, 1.f);
			glVertex3f(-30.f, 0, 0.f);
		}
		glEnd();
	}
	glPopMatrix();
}

void Ground::DrawVerticalQuads(float x, float y, float z)
{
	glPushMatrix();
	{
		glBegin(GL_QUADS);
		{
			glVertex3f(x, y, z);
			glVertex3f(x, y, z + 1.f);
			glVertex3f(x, -30.f, z + 1.f);
			glVertex3f(x, -30.f, 0.f);
		}
		glEnd();
	}
	glPopMatrix();
}

float Ground::YDegreeOnTile(float x, float fz)
{
	int i;
	float z = -fz;

	int t = floor(z);
	double mod = z - t;

	if (mod < 0.25f) i = 0;
	else if(mod < 0.5f) i = 1;
	else if(mod < 0.75f) i = 2;
	else i = 3;

	float Z = -(t + i * 0.25f);

	for (auto d : vMap)
	{
		if (d.m_pos.z == Z)
		{
			return d.m_degree; break;
		}
	}
	return 0.0f;
}

float Ground::GetHeightOnTile(float x, float fz)
{
	int i;
	float z = -fz;

	int t = floor(z);
	double mod = z - t;

	if (mod < 0.25f) i = 0;
	else if (mod < 0.5f) i = 1;
	else if (mod < 0.75f) i = 2;
	else i = 3;

	float Z = -(t + i * 0.25f);

	for (auto d : vMap)
	{
		if (d.m_pos.z == Z)
		{
			return d.m_pos.y; break;
		}
	}
	return 0.0f;
}
