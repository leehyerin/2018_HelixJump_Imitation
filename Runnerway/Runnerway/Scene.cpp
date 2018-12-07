#include "stdafx.h"

extern int scenenum;
extern Camera camera;
Ball ball;
Ground ground;
vector<Item> vItems;
vector<Obstacle> vObstacles;

int KnockbackTime = 0;
int accelTime = 0;
int particleTime = 0;
bool ObCol = false;
bool ItemCol[3] = { false, };

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
	//장애물 초기화. 대충 넣었음
	float x, z;
	float height = 0;
	//x = 0, z = -1;
	//height = ground.GetHeightOnTile(x, z);
	//vObstacles.push_back(Obstacle(x, height + 2, z, 4));

	x = 0, z =-20;
	height = ground.GetHeightOnTile(x, z);
	vObstacles.push_back(Obstacle(x, height + 2, z, 4));

	//x = 8, z = -80;
	//height = ground.GetHeightOnTile(x, z);
	//vObstacles.push_back(Obstacle(x, height + 2, z, 4));

	x = -10, z = -156;
	height = ground.GetHeightOnTile(x, z);
	vObstacles.push_back(Obstacle(x, height + 2, z, 4));

	x = -3, z = -185;
	height = ground.GetHeightOnTile(x, z);
	vObstacles.push_back(Obstacle(x, height + 2, z, 4));

	x = -7, z = -250;
	height = ground.GetHeightOnTile(x, z);
	vObstacles.push_back(Obstacle(x, height + 2, z, 4));

	x = 12, z = -300;
	height = ground.GetHeightOnTile(x, z);
	vObstacles.push_back(Obstacle(x, height + 2, z, 4));
}

Scene *Play::update(void)
{
	// 초기화 함수 필요 //

	if (particleTime < 5)
		particleTime++;
	else if (particleTime >= 5)
	{
		ball.RunParitcle();
		particleTime = 0;
	}

	ball.SetPosY(ball.GetRadius()+ ground.GetHeightOnTile(ball.GetPosX(), ball.GetPosZ()));

	ball.SetRotY(-ground.YDegreeOnTile(ball.GetPosX(), ball.GetPosZ()));
	ball.SetRotZ(ball.GetRotZ() - ball.GetSpeed());
	ball.SetPosZ(ball.GetPosZ() - 1 * PI * ball.GetRadius() / (360 / ball.GetSpeed()));

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
	ground.Draw(camera.GetLorB());
	ball.RunParticleDraw();

	//----------------Obstacles---------------------
	for (unsigned int d = 0; d < vObstacles.size(); ++d)
		if (vObstacles[d].CheckCollPlayerbyItem(ball.GetPosX(), ball.GetPosY(), ball.GetPosZ(), ball.GetRadius()))
		{
			accelTime = 0;
			ball.SetSpeed(10.0f);
			ItemCol[1] = false;

			ball.ParticleStart(vObstacles[d].GetPos());

			// 넉백
			ball.SetPosZ(ball.GetPosZ() + 2.0f);
			ball.SetSpeed(0.0f);

			ObCol = true;

			vObstacles.erase(vObstacles.begin() + d); //장애물 지우기
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

			if (vItems[d].GetItemType() == 1)	// 아이템 먹었을 경우
				ItemCol[1] = true;

			vItems.erase(vItems.begin() + d);//아이템 지우기
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
