#include "stdafx.h"

Ball::Ball()
{
	x = 0.0f, y = 5.0f, z = 0.0f;
	radius = 5.0f;
	rotZ = 0.0f;
	speed = 15.0f;

	isJump = false;
	JumpTime = 0;
	accelTime = 0;
}

Ball::~Ball()
{
}

void Ball::Update()
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
	BLACK;
	for (auto d : m_vParticles)
	{
		glPushMatrix();
		glTranslated(d.GetPos()->x, d.GetPos()->y, d.GetPos()->z);
		glutSolidCube(1.0);
		glPopMatrix();
	}
}

void Ball::RunParitcle()
{
	srand((unsigned int)time(NULL));

	if (speed > 0.0f)
	{
		for(int i = 0; i < 6; ++i)
			runParticles.push_back(Particle{ (double)(rand() % 6 + x), (double)(rand() % 3 + y), z, 35 });
	}
}

void Ball::RunParticleDraw()
{
	WHITE;
	for (particleIter = runParticles.begin(); particleIter != runParticles.end();)
	{
		glPushMatrix();
		particleIter->SetPos(particleIter->GetPos()->x, particleIter->GetPos()->y + 0.1f, particleIter->GetPos()->z + 0.1f);
		particleIter->SetTime(particleIter->GetTime() - 1);
		glTranslated(particleIter->GetPos()->x, particleIter->GetPos()->y, particleIter->GetPos()->z);
		glutSolidCube(0.1);
		glPopMatrix();

		if (particleIter->GetTime() <= 0)
			particleIter = runParticles.erase(runParticles.begin());
		else
			++particleIter;
	}
}

void Ball::Accelartion(int time)
{
	if (time < 15)
		accelTime++;
	else if (time >= 15)
		accelTime--;

	speed = 10.0f + 4 * accelTime;

	if (speed <= 10.0f)
	{
		accelTime = 0;
		speed = 10.0f;
	}
}