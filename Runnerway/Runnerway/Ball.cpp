#include "stdafx.h"

extern Terrain terrain;
extern GLuint texture[21];
extern GLubyte *pBytes; // 데이터를 가리킬 포인터
extern BITMAPINFO *info; // 비트맵 헤더 저장할 변수

Ball::Ball()
{
	x = 0.0f, y = 3.0f, z = 0.0f;
	radius = 5.0f;
	rotZ = 0.0f;
	speed = 20.0f;
	standard = 0.0f;
	dir = 1;

	isJump = false;
	JumpTime = 0;
	accelTime = 0;
}

Ball::~Ball()
{
}

void Ball::Update()
{

	if (GetIsJump())
	{
		SetRotZ(GetRotZ() - GetSpeed());
		SetPosZ(GetPosZ() - 1 * PI * GetRadius() / (360 / GetSpeed()) - 1.0f);

		if (GetTime() < 10)
			SetPosY(GetPosY() + 2);
		else if (GetTime() >= 10 && GetTime() < 25)
		{
			float ty = terrain.GetHeightOnTile(GetPosZ());
			if (y <= ty)
			{
				y = ty;
				SetIsJump(false);
				SetTime(0);
			}
			else 
				SetPosY(GetPosY() - 1);
		}
		else
		{
			SetIsJump(false);
			SetTime(0);
		}

		SetTime(GetTime() + 1);
	}
	else
	{
		if (GetPosZ() > -900)
		{
			SetRotZ(GetRotZ() - GetSpeed());
			SetPosZ(GetPosZ() - 1 * PI * GetRadius() / (360 / GetSpeed()));

			SetPosY(GetRadius() + terrain.GetHeightOnTile(GetPosZ()));

			TexTimer += 1;
			if (TexTimer > 1000)
			{
				TexIdx++;
				TexTimer = 0;
			}
			TexIdx = TexIdx % 7 + 11;    //11~17  -> 0~6

		}
		else;// cout << "스테이지 클리어!" << endl;
	}
}

void Ball::DrawBall()
{
	glPushMatrix();
	{
		WHITE;

		// 자동 매핑 설정 
		glEnable(GL_TEXTURE_GEN_S);
		glEnable(GL_TEXTURE_GEN_T);

		// 구 매핑
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
		glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
		glBindTexture(GL_TEXTURE_2D, texture[TexIdx]);

		glTranslatef(x, 0.0f, 0.0f);
		glTranslatef(0.0f, y, 0.0f);
		glTranslatef(0.0f, 0.0f, z);
		glRotatef(rotZ, 1.0f, 0.0f, 0.0f);
		glRotatef(rotY, 0.0f, 1.0f, 0.0f);
		glRotatef(rotX, 0.0f, 0.0f, 1.0f);
		glutSolidSphere(radius, 20, 10);

		// 자동 매핑 해제
		glDisable(GL_TEXTURE_GEN_S);
		glDisable(GL_TEXTURE_GEN_T);
	}
	glPopMatrix();
}


void Ball::ParticleStart(MyVec* pos, int type)
{
	if (!m_bParticle)
	{
		Particletype = type;

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
	for (auto d : m_vParticles)
	{
		glPushMatrix();
		glTranslated(d.GetPos()->x, d.GetPos()->y, d.GetPos()->z);

		// 텍스처를 객체에 맵핑
		glBindTexture(GL_TEXTURE_2D, texture[Particletype]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-0.5f, -0.5f, -0.5f);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-0.5f, 0.5f, -0.5f);

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(0.5f, 0.5f, -0.5f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(0.5f, -0.5f, -0.5f);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, texture[Particletype]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-0.5f, -0.5f, 0.5f);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-0.5f, 0.5f, 0.5f);

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(0.5f, 0.5f, 0.5f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(0.5f, -0.5f, 0.5f);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, texture[Particletype]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-0.5f, -0.5f, -0.5f);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-0.5f, 0.5f, -0.5f);

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(-0.5f, 0.5f, 0.5f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-0.5f, -0.5f, 0.5f);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, texture[Particletype]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0.5f, -0.5f, -0.5f);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(0.5f, 0.5f, -0.5f);

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(0.5f, 0.5f, 0.5f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(0.5f, -0.5f, 0.5f);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, texture[Particletype]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-0.5f, -0.5f, -0.5f);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-0.5f, -0.5f, 0.5f);

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(0.5f, -0.5f, 0.5f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(0.5f, -0.5f, -0.5f);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, texture[Particletype]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-0.5f, 0.5f, -0.5f);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-0.5f, 0.5f, 0.5f);

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(0.5f, 0.5f, 0.5f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(0.5f, 0.5f, -0.5f);
		glEnd();
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
		glBindTexture(GL_TEXTURE_2D, texture[6]);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(0.1f, -0.1f, -0.1f);

		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(0.1f, 0.1f, -0.1f);

		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(0.1f, 0.1f, 0.1f);

		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(0.1f, -0.1f, 0.1f);
		glEnd();
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

	speed = 20.0f + 4 * accelTime;

	if (speed <= 20.0f)
	{
		accelTime = 0;
		speed = 20.0f;
	}
}

void Ball::TitleMove()
{
	if (GetTime() < 5)
		SetPosY(GetPosY() + 1);
	else if (GetTime() >= 5 && GetTime() < 9)
	{
		SetPosY(GetPosY() - 1);
	}
	else
	{
		SetTime(0);
	}

	SetTime(GetTime() + 1);
}

void Ball::ResultMove()
{
	if (x > 10.0f)
		dir *= -1;
	else if (x < -10.0f)
		dir *= -1;

	x += dir;
}