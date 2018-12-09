#include "stdafx.h"
#define CURVATURE 0.15f //곡률

extern GLuint texture[6];

Terrain::Terrain()
{
}

Terrain::~Terrain()
{
}

void Terrain::InitStage1()
{
	float Floordegree = 0;
	float x{ 0 }, y{ 0 }, z{ 0 };

	//---------------------종 구간-------------------------
	for (z = 0.0; z > -80.0; z -= 0.25)
	{
		Floordegree += CURVATURE;
		y += 0.08f;
		vMap.push_back(Map{ MyVec{ x, y, z }, Floordegree });
	}

	for (z = -80.0; z > -160.0; z -= 0.25)
	{
		Floordegree -= CURVATURE;
		y -= 0.08f;
		vMap.push_back(Map{ MyVec{ x, y, z }, Floordegree });
	}
	//---------------------횡 구간-------------------------
	Floordegree = 0;
	for (z = -160.0; z > -240.0; z -= 0.25)
	{
		y -= 0.03f;
		vMap.push_back(Map{ MyVec{ x, y, z }, Floordegree });
	}

	for (z = -240.0; z > -320.0; z -= 0.25)
	{
		y += 0.03f;
		vMap.push_back(Map{ MyVec{ x, y, z }, Floordegree });
	}
	//---------------------종 구간-------------------------
	for (z = -320.0; z > -400.0; z -= 0.25)
	{
		Floordegree += CURVATURE;
		y += 0.03f;
		vMap.push_back(Map{ MyVec{ x, y, z }, Floordegree });
	}

	for (z = -400.0; z > -450.0; z -= 0.25)
	{
		Floordegree -= CURVATURE;
		y -= 0.03f;
		vMap.push_back(Map{ MyVec{ x, y, z }, Floordegree });
	}
	//---------------------갈림길-------------------------
	///왼쪽--맞는 길
	x = 0.f; Floordegree = 30;
	for (z = -450.0; z > -600.0; z -= 0.25)
	{
		Floordegree -= 0.1f;
		x -= 0.25f;
		vMap.push_back(Map{ MyVec{ x, y, z }, Floordegree });
	}
	float tx{ x }, ty{ y };
	float tFloordegree = Floordegree;

	///오른쪽
	x = 0.f; Floordegree = -30;
	for (z = -450.0; z > -600.0; z -= 0.25)
	{
		Floordegree += 0.1f;
		y -= 0.01;
		x += 0.25f;
		vMap.push_back(Map{ MyVec{ x, y, z }, Floordegree });
	}
	//---------------------종 구간-------------------------
	x = tx;   y = ty;
	Floordegree = tFloordegree;

	for (z = -600.0; z > -680.0; z -= 0.25)
	{
		Floordegree += CURVATURE;
		y += 0.03f;
		vMap.push_back(Map{ MyVec{ x, y, z }, Floordegree });
	}
	//---------------------횡 구간-------------------------
	for (z = -680.0; z > -780.0; z -= 0.25)
	{
		vMap.push_back(Map{ MyVec{ x, y, z }, Floordegree });
	}
	//---------------------종 구간-------------------------
	for (z = -780.0; z > -900.0; z -= 0.25)
	{
		vMap.push_back(Map{ MyVec{ x, y, z }, Floordegree });
	}

	for (z = -900.0; z > -1000.0; z -= 0.25)
	{
		Floordegree += CURVATURE;
		y -= 0.03f;
		vMap.push_back(Map{ MyVec{ x, y, z }, Floordegree });
	}
}

void Terrain::InitStage2()
{
}

void Terrain::Draw(bool b) //true 종 
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

void Terrain::DrawHorizonQuads(float x, float y, float z, float degree)
{
	glPushMatrix();
	{
		glTranslatef(x, y, z - 0.5f);
		glRotatef(degree, 0, 1, 0);
		glRotatef(y, 1, 0, 0);

		glBindTexture(GL_TEXTURE_2D, texture[4]);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(+30.f, 0, 0.f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(+30.f, 0, 1.f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(-30.f, 0, 1.f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-30.f, 0, 0.f);
		}
		glEnd();
	}
	glPopMatrix();
}

void Terrain::DrawVerticalQuads(float x, float y, float z)
{
	glPushMatrix();
	{
		glBindTexture(GL_TEXTURE_2D, texture[4]);
		glBegin(GL_QUADS);
		{
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(x, y, z);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(x, y, z + 1.f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(x, -30.f, z + 1.f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(x, -30.f, 0.f);
		}
		glEnd();
	}
	glPopMatrix();
}

float Terrain::GetYDegreeOnTile(float x, float fz)
{
	float Z = GetZNearTile(-fz);

	for (auto d : vMap)
	{
		if (d.m_pos.z == Z)
		{
			return d.m_degree; break;
		}
	}
	return 0.0f;
}

float Terrain::GetHeightOnTile(float fz)
{
	float Z = GetZNearTile(-fz);

	for (auto d : vMap)
	{
		if (d.m_pos.z == Z)
		{
			return d.m_pos.y; break;
		}
	}
	return 0.0f;
}

float Terrain::GetXNearTile(float ballX, float ballZ)
{
	float BALLZ = ballZ;

	float Z = GetZNearTile(-BALLZ);

	for (auto d : vMap)
	{
		if (d.m_pos.z == Z)
		{
			if (ballX <= 0)            //x가 음수일 때는 왼쪽 길, 양수일 때는 오른쪽 길
			{
				return  d.m_pos.x;
			}
			else
			{
				return  -d.m_pos.x;
			}
		}
	}
	return 0.0f;
}

float Terrain::GetZNearTile(float z)
{
	float Z;

	int i = 0;
	int t = floor(z);
	double mod = z - t;

	if (mod < 0.25f) i = 0;
	else if (mod < 0.5f) i = 1;
	else if (mod < 0.75f) i = 2;
	else i = 3;

	Z = -(t + i * 0.25f);
	return Z;
}