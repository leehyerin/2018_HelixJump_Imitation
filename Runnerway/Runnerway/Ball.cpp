#include "stdafx.h"

Ball::Ball()
{
	x = 0.0f, y = 5.0f, z = 0.0f;
	radius = 5.0f;
	rotZ = 0.0f;
	speed = 10.0f;

	isJump = false;
	time = 0;
}

Ball::~Ball()
{
}

void Ball::DrawBall()
{
	glPushMatrix();
	{
		WHITE;
		glTranslatef(x, 0.0f, 0.0f);
		glTranslatef(0.0f, y, 0.0f);
		glTranslatef(0.0f, 0.0f, z);
		glRotatef(rotZ, 1.0f, 0.0f, 0.0f);
		glRotatef(rotY, 0.0f, 1.0f, 0.0f);
		glRotatef(rotX, 0.0f, 0.0f, 1.0f);
		glutSolidSphere(radius, 20, 10);
		BLACK;
		glutWireSphere(radius, 20, 10);
	}
	glPopMatrix();
}


void Ball::ParticleStart(MyVec* pos)
{
	if (!m_bParticle)
	{
		m_bParticle = true;
		m_Timer = 0;

		for (int j = 0; j < 20; ++j)
			m_vParticles.push_back(Particle{ pos->x,pos->y,pos->z });
	}
}

void Ball::ParticleProcess()
{
	if (m_bParticle)
	{
		for (unsigned int i = 0; i < m_vParticles.size(); ++i)
		{
			++m_Timer;
			m_vParticles[i].Update();
		}
		if (m_Timer == 200)
		{
			m_bParticle = false;
			m_Timer = 0;
			m_vParticles.clear();
		}
		ParticleDraw();
	}
}

void Ball::ParticleDraw()
{
	CYAN;
	for (auto d : m_vParticles)
	{
		glPushMatrix();
		glTranslated(d.GetPos()->x, d.GetPos()->y, d.GetPos()->z);
		glutSolidCube(1.0);
		glPopMatrix();
	}
}
