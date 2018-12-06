#include "stdafx.h"

extern int scenenum;
extern Ball ball;
extern Scene *scene;
extern Camera camera;
extern Ground ground;
extern vector<Item> vItems;
extern vector<Obstacle> vObstacles;

Scene *Title::update(void)
{
	if (scenenum == 1)
		return new Lobby();

	return this;
}

void Title::draw(void)
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

Scene *Play::update(void)
{
	// 초기화 함수 필요 //

	ball.SetRotZ(ball.GetRotZ() - ball.GetSpeed());
	ball.SetPosZ(ball.GetPosZ() - 1 * PI * ball.GetRadius() / (360 / ball.GetSpeed()));

	if (ball.GetIsJump())
	{
		if (ball.GetTime() < 5)
			ball.SetPosY(ball.GetPosY() + 1);
		else if (ball.GetTime() >= 5 && ball.GetTime() < 10)
			ball.SetPosY(ball.GetPosY() - 1);
		else
		{
			ball.SetIsJump(false);
			ball.SetTime(0);
		}

		ball.SetTime(ball.GetTime() + 1);
	}

	//
	ball.SetRotY(ground.YDegreeOnTile(ball.GetPosX(), ball.GetPosZ()));
	//

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
	ground.Draw();

	//------------------Draw----------------------
	for (unsigned int d = 0; d < vItems.size(); ++d)
		if (vItems[d].CheckCollPlayerbyItem(ball.GetPosX(), ball.GetPosY(), ball.GetPosZ(), ball.GetRadius()))
		{
			cout << "col!" << endl;
			vItems.erase(vItems.begin() + d);//아이템 겟!
		}
	for (auto d : vItems)
		d.Draw();
	//--------------------------------------------
	for (unsigned int d = 0; d < vObstacles.size(); ++d)
		if (vObstacles[d].CheckCollPlayerbyItem(ball.GetPosX(), ball.GetPosY(), ball.GetPosZ(), ball.GetRadius()))
		{
			cout << "col!" << endl;//장애물 충돌!
								   //vObstacles.erase(vObstacles.begin() + d);
		}
	for (auto d : vObstacles)
		d.Draw();
	//--------------------------------------------
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

void update()
{
	Scene *next = scene->update();

	if (next != scene)
	{
		delete scene;
		scene = next;
	}
}

void draw()
{
	scene->draw();
}