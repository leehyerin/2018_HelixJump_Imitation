#include "stdafx.h"

extern int scenenum;
extern Camera camera;
Ball ball;
Ground ground;
vector<Item> vItems;
vector<Obstacle> vObstacles;


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
	x = 0, z = -1;
	height = ground.GetHeightOnTile(x, z);
	vObstacles.push_back(Obstacle(x, height + 2, z, 4));

	x = 0, z =-20;
	height = ground.GetHeightOnTile(x, z);
	vObstacles.push_back(Obstacle(x, height + 2, z, 4));

	x = 8, z = -80;
	height = ground.GetHeightOnTile(x, z);
	vObstacles.push_back(Obstacle(x, height + 2, z, 4));

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

	//------------------Items----------------------
	for (unsigned int d = 0; d < vItems.size(); ++d)
		if (vItems[d].CheckCollPlayerbyItem(ball.GetPosX(), ball.GetPosY(), ball.GetPosZ(), ball.GetRadius()))
		{
			cout << "col!" << endl;
			ball.SetSpeed(20);			// 아이템 먹었을 경우

			vItems.erase(vItems.begin() + d);//아이템 지우기
			break;
		}
	for (auto d : vItems)
		d.Draw();
	

	//----------------Obstacles---------------------
	for (unsigned int d = 0; d < vObstacles.size(); ++d)
		if (vObstacles[d].CheckCollPlayerbyItem(ball.GetPosX(), ball.GetPosY(), ball.GetPosZ(), ball.GetRadius()))
		{
			ball.ParticleStart(vObstacles[d].GetPos());
			// 넉백,,
			vObstacles.erase(vObstacles.begin() + d); //장애물 지우기
			break;
		}
	for (auto d : vObstacles)
		d.Draw();
	
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
