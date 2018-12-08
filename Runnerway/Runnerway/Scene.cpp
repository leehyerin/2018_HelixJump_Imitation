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

MCIDEVICEID dwID1, dwID2, dwID3;

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
	OnBGM();
	Init();
	terrain.InitStage1();
}

void Play::Init()
{
	float x, z;
	float height = 0;

	x = 10, z = -20;
	height = terrain.GetHeightOnTile(z);
	vItems.push_back(Item(x, height + 5, z, 10.0, 0));

	x = -10, z = -60;
	height = terrain.GetHeightOnTile(z);
	vItems.push_back(Item(x, height + 5, z, 10.0, 1));

	x = 7, z = -150;
	height = terrain.GetHeightOnTile(z);
	vItems.push_back(Item(x, height + 5, z, 10.0, 0));

	x = 10, z = -205;
	height = terrain.GetHeightOnTile(z);
	vItems.push_back(Item(x, height + 5, z, 10.0, 1));

	x = 19, z = -280;
	height = terrain.GetHeightOnTile(z);
	vItems.push_back(Item(x, height + 5, z, 10.0, 0));

	x = 19, z = -300;
	height = terrain.GetHeightOnTile(z);
	vItems.push_back(Item(x, height + 5, z, 10.0, 1));

	x = -15, z = -350;
	height = terrain.GetHeightOnTile(z);
	vItems.push_back(Item(x, height + 5, z, 10.0, 0));

	x = -115, z = -550;
	height = terrain.GetHeightOnTile(z);
	vItems.push_back(Item(x, height + 10, z, 10.0, 1));

	x = -130, z = -600;
	height = terrain.GetHeightOnTile(z);
	vItems.push_back(Item(x, height + 10, z, 10.0, 0));
	//-------------------------------------------------
	//-------------------------------------------------
	x = -20, z = -50;
	height = terrain.GetHeightOnTile(z);
	vObstacles.push_back(Obstacle(x, height + 2, z, 4));

	x = -10, z = -65;
	height = terrain.GetHeightOnTile(z);
	vObstacles.push_back(Obstacle(x, height + 2, z, 4));

	x = -10, z = -85;
	height = terrain.GetHeightOnTile(z);
	vObstacles.push_back(Obstacle(x, height + 2, z, 4));

	x = -8, z = -88;
	height = terrain.GetHeightOnTile(z);
	vObstacles.push_back(Obstacle(x, height + 2, z, 4));

	x = 0, z = -110;
	height = terrain.GetHeightOnTile(z);
	vObstacles.push_back(Obstacle(x, height + 2, z, 4));

	x = -10, z = -150;
	height = terrain.GetHeightOnTile(z);
	vObstacles.push_back(Obstacle(x, height + 2, z, 4));

	///-------횡 구간-------
	x = 0, z = -185;
	height = terrain.GetHeightOnTile(z);
	vObstacles.push_back(Obstacle(x, height + 2, z, 4));

	z = 200;
	height = terrain.GetHeightOnTile(z);
	vObstacles.push_back(Obstacle(x, height + 2, z, 4));

	z = 210;
	height = terrain.GetHeightOnTile(z);
	vObstacles.push_back(Obstacle(x, height + 2, z, 4));

	z = 230;
	height = terrain.GetHeightOnTile(z);
	vObstacles.push_back(Obstacle(x, height + 2, z, 4));
	///-------종 구간-------
	x = -7, z = -250;
	height = terrain.GetHeightOnTile(z);
	vObstacles.push_back(Obstacle(x, height + 2, z, 4));

	x = 12, z = -300;
	height = terrain.GetHeightOnTile(z);
	vObstacles.push_back(Obstacle(x, height + 4, z, 4));

	x = -17, z = -385;
	height = terrain.GetHeightOnTile(z);
	vObstacles.push_back(Obstacle(x, height + 4, z, 4));
	///-------횡 구간-------
	x = -60, z = -500;
	height = terrain.GetHeightOnTile(z);
	vObstacles.push_back(Obstacle(x, 6, z, 4));



	///-------갈림길--------
	x = 155, z = -600;
	height = terrain.GetHeightOnTile(z);
	vObstacles.push_back(Obstacle(x, height + 2, z, 4));


}

void Play::OnBGM()
{
	//// 파일 열기
	MCI_OPEN_PARMS mciOpen;   // MCI_OPEN_PARAMS 구조체 변수 
	mciOpen.lpstrDeviceType = "waveaudio";  // mpegvideo : mp3, waveaudio : wav, avivideo : avi
	mciOpen.lpstrElementName = "Resources/Beat.wav"; // 파일이름
	mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE | MCI_OPEN_TYPE, (DWORD)(LPVOID)&mciOpen);

	// 재생
	MCI_PLAY_PARMS mciPlay;
	dwID1 = mciOpen.wDeviceID;
	mciSendCommand(dwID1, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&mciPlay);//MCI_NOTIFY : 기본, MCI_DGV_PLAY_REPEAT : 반복

																				  /////////////////////////////////////////////////////////////////////////////////////

																				  // 파일 열기
	MCI_OPEN_PARMS walkingOnSnow;   // MCI_OPEN_PARAMS 구조체 변수 
	walkingOnSnow.lpstrDeviceType = "waveaudio";
	walkingOnSnow.lpstrElementName = "Resources/walkingOnsnow.wav";
	mciSendCommand(0, MCI_OPEN,
		MCI_OPEN_ELEMENT | MCI_OPEN_TYPE | MCI_OPEN_TYPE,
		(DWORD)(LPVOID)&walkingOnSnow);

	// 재생
	MCI_PLAY_PARMS mciPlay2;
	dwID2 = walkingOnSnow.wDeviceID;
	mciSendCommand(dwID2, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&mciPlay2);
	/////////////////////////////////////////////////////////////////////////////////////


}

void Play::Timer()
{
	//m_Min = t->tm_min;
	//m_Sec = t->tm_sec;
	auto a = localtime(&m_timer);
	cout << t-a << endl;;
	t = localtime(&m_timer);

}

Scene *Play::update(void)
{
	// 초기화 함수 필요 //
	Timer();

	m_Progressbar = ball.GetPosZ() / -1000.0f;

	if (particleTime < 3)
		particleTime++;
	else if (particleTime >= 3)
	{
		ball.RunParitcle();
		particleTime = 0;
	}


	//-----------갈림길 부분에서 방향에 따라 x를 바꿔주는 부분------------
	if (ball.GetPosZ() <= -450)
	{
		float X = terrain.GetXNearTile(ball.GetPosX(), ball.GetPosZ());
		ball.CompareAddPosX(prevTerrainX, X);  //
		prevTerrainX = X;
	}
	//갈림길 끝에 닿으면 갈림길 시작으로 보내는 부분
	if (ball.GetPosZ() <-580.f && ball.GetPosX() > 0.f)
	{
		ball.SetPosX(0.f); ball.SetPosZ(-430.f);
		prevTerrainX = 0.f;
	}
	//------------------------------------------------------------

	ball.SetRotY(-terrain.GetYDegreeOnTile(ball.GetPosX(), ball.GetPosZ()));

	ball.Update();

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
			sndPlaySoundA("Resources/Explosion.wav", SND_ASYNC);
			accelTime = 0;
			ball.SetSpeed(10.0f);
			ItemCol[0] = false;

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

	if (ObCol)
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
			//cout << "col!" << endl;
			sndPlaySoundA("	Resources/dash.wav", SND_ASYNC);

			if (vItems[d].GetItemType() == 0)	// 아이템 먹었을 경우
			{
				ItemCol[0] = true;
			}

			if (vItems[d].GetItemType() == 1)	// 아이템 먹었을 경우
			{
				ItemCol[1] = true;
				//sndPlaySoundA("	Resources/dash.wav", SND_ASYNC);
			}
			vItems.erase(vItems.begin() + d);//아이템 지우기
			break;
		}
	for (auto d : vItems)
		d.Draw();

	if (ItemCol[0] && !ObCol)
	{
		accelTime++;

		ball.Accelartion(accelTime);

		if (accelTime > 27)
		{
			accelTime = 0;
			ball.SetSpeed(10.0f);
			ItemCol[0] = false;
		}
	}
	if (ItemCol[1])
	{
		for (unsigned int d = 0; d < vObstacles.size(); ++d)
		{
			if (vObstacles[d].GetPos()->z > ball.GetPosZ() - 100.0f && vObstacles[d].GetPos()->z < ball.GetPosZ())
			{
				ball.ParticleStart(vObstacles[d].GetPos());

				vObstacles.erase(vObstacles.begin() + d); //장애물 지우기
			}
		}

		ItemCol[1] = false;
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
