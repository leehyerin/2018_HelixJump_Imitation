#include "stdafx.h"

extern int scenenum;
extern Camera camera;
Ball ball;
Terrain terrain;
vector<Item> vItems;
vector<Obstacle> vObstacles;

int KnockbackTime = 0;
int accelTime = 0;
int particleTime = 0;
bool ObCol = false;
bool ItemCol[3] = { false, };

float prevTerrainX = 0;
float tmpY = 0;

void Title::Init()
{
}

Scene *Title::update(void)
{
	if (scenenum == 1)
		return new Lobby();

	return this;
}

void Title::draw(void)
{
}

void Lobby::Init()
{
}

Scene *Lobby::update(void)
{
	if (scenenum == 2)
		return new Play();

	return this;
}

void Lobby::draw(void)
{
}


//////////////////////////////////////////////////////////////////////////////
Play::Play()
{
	Init();
}

void Play::Init()
{
	vItems.push_back(Item(0.0, 5.0, -20.0, 10.0,1));
	vItems.push_back(Item(10.0, 5.0, -60.0, 10.0,1));
	vItems.push_back(Item(-10.0, 5.0, -100.0, 10.0,1));
	vItems.push_back(Item(10.0, 5.0, -120.0, 10.0,1));
	vItems.push_back(Item(10.0, 5.0, -160.0, 10.0,1));
	//-------------------------------------------------
	//��ֹ� �ʱ�ȭ. ���� �־���
	float x, z;
	float height = 0;

	x = 10, z =-50;
	height = terrain.GetHeightOnTile(x, z);
	vObstacles.push_back(Obstacle(x, height + 2, z, 4));

	x = -10, z = -156;
	height = terrain.GetHeightOnTile(x, z);
	vObstacles.push_back(Obstacle(x, height + 2, z, 4));

	x = -3, z = -185;
	height = terrain.GetHeightOnTile(x, z);
	vObstacles.push_back(Obstacle(x, height + 2, z, 4));

	x = -7, z = -250;
	height = terrain.GetHeightOnTile(x, z);
	vObstacles.push_back(Obstacle(x, height + 2, z, 4));

	x = 12, z = -300;
	height = terrain.GetHeightOnTile(x, z);
	vObstacles.push_back(Obstacle(x, height + 2, z, 4));
}

Scene *Play::update(void)
{
	// �ʱ�ȭ �Լ� �ʿ� //

	if (particleTime < 3)
		particleTime++;
	else if (particleTime >= 3)
	{
		ball.RunParitcle();
		particleTime = 0;
	}

	//
	ball.SetPosY(ball.GetRadius()+ terrain.GetHeightOnTile(ball.GetPosX(), ball.GetPosZ()));
	
	//-----------������ �κп��� ���⿡ ���� x�� �ٲ��ִ� �κ�------------
	if (ball.GetPosZ() <= -450)   
	{
		float X = terrain.GetXNearTile(ball.GetPosX(), ball.GetPosZ());
		ball.CompareAddPosX(prevTerrainX, X);  //
		prevTerrainX = X;
	}
	//������ ���� ������ ������ �������� ������ �κ�
	if (ball.GetPosZ() <- 580.f && ball.GetPosX() > 0.f)
	{
		ball.SetPosX(0.f); ball.SetPosZ(-430.f);
		prevTerrainX = 0.f;
	}
	//------------------------------------------------------------

	ball.SetRotY(-terrain.GetYDegreeOnTile(ball.GetPosX(), ball.GetPosZ()));
	ball.SetRotZ(ball.GetRotZ() - ball.GetSpeed());
	ball.SetPosZ(ball.GetPosZ() - 1 * PI * ball.GetRadius() / (360 / ball.GetSpeed()));

	// ����
	if (ball.GetIsJump())
	{
		if (ball.GetTime() < 5)
			ball.SetPosY(ball.GetPosY() + 1);
		else if (ball.GetTime() >= 5 && ball.GetTime() < 9)
			ball.SetPosY(ball.GetPosY() - 1);
		else
		{
			ball.SetIsJump(false);
			ball.SetTime(0);
		}

		ball.SetTime(ball.GetTime() + 1);
	}

	if (scenenum == 3)
		return new Result();

	return this;
}

void Play::draw(void)
{
	camera.CameraPos();
	glEnable(GL_CULL_FACE);
	ball.DrawBall();
	glDisable(GL_CULL_FACE);
	terrain.Draw(camera.GetLorB());
	ball.RunParticleDraw();

	//----------------Obstacles---------------------
	for (unsigned int d = 0; d < vObstacles.size(); ++d)
		if (vObstacles[d].CheckCollPlayerbyItem(ball.GetPosX(), ball.GetPosY(), ball.GetPosZ(), ball.GetRadius()))
		{
			accelTime = 0;
			ball.SetSpeed(10.0f);
			ItemCol[1] = false;

			ball.ParticleStart(vObstacles[d].GetPos());

			// �˹�
			ball.SetPosZ(ball.GetPosZ() + 2.0f);
			ball.SetSpeed(0.0f);

			ObCol = true;

			vObstacles.erase(vObstacles.begin() + d); //��ֹ� �����
			break;
		}
	for (auto d : vObstacles)
		d.Draw();

	if (ObCol && !ItemCol[1])
	{
		KnockbackTime++;

		if (KnockbackTime > 20)
		{
			ball.SetSpeed(10.0f);
			KnockbackTime = 0;
			ObCol = false;
		}
	}


	//------------------Items----------------------
	for (unsigned int d = 0; d < vItems.size(); ++d)
		if (vItems[d].CheckCollPlayerbyItem(ball.GetPosX(), ball.GetPosY(), ball.GetPosZ(), ball.GetRadius()))
		{
			cout << "col!" << endl;

			if (vItems[d].GetItemType() == 1)	// ������ �Ծ��� ���
				ItemCol[1] = true;

			vItems.erase(vItems.begin() + d);//������ �����
			break;
		}
	for (auto d : vItems)
		d.Draw();

	if (ItemCol[1] && !ObCol)
	{
		accelTime++;

		ball.Accelartion(accelTime);
		
		if (accelTime > 27)
		{
			accelTime = 0;
			ball.SetSpeed(10.0f);
			ItemCol[1] = false;
		}
	}

	
	//--------------------------------------------
	ball.ParticleProcess();
}


//////////////////////////////////////////////////////////////////////////////
void Result::Init()
{
}

Scene *Result::update(void)
{
	if (scenenum == 0)
		return new Title();

	return this;
}

void Result::draw(void)
{
}
