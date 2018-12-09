#include "stdafx.h"
#include "Scene.h"

extern int scenenum;
extern Camera camera;
Ball ball;
Terrain terrain;
vector<Item> vItems;
vector<Obstacle> vObstacles;
extern GLuint texture[21];
extern Light light;

int KnockbackTime = 0;
int accelTime = 0;
int particleTime = 0;
int ResultTime = 0;
bool ObCol = false;
bool ItemCol[3] = { false, };

float prevTerrainX = 0;
float tmpY = 0;

MCIDEVICEID dwID1, dwID2, dwID3;

extern GLubyte * LoadDIBitmap(const char* filename, BITMAPINFO** info);

void Title::Init()
{
}

Scene *Title::update(void)
{
	ball.TitleMove();

	if (scenenum == 1)
	{
		ball.SetPosX(0);
		ball.SetPosY(3);
		ball.SetPosZ(0);
		return new Play();
	}

	return this;
}

void Title::draw(void)
{
	camera.TitleCamera();

	glEnable(GL_CULL_FACE);
	//
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-30.0f, 0.0f, -30.0f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-30.0f, 0.0f, 30.0f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(30.0f, 0.0f, 30.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(30.0f, 0.0f, -30.0f);
	glEnd();

	//
	glBindTexture(GL_TEXTURE_2D, texture[19]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-3.0f, 12.0f, 10.0f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-3.0f, 9.0f, 10.0f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(3.0f, 9.0f, 10.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(3.0f, 12.0f, 10.0f);
	glEnd();

	//
	glBindTexture(GL_TEXTURE_2D, texture[18]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-5.0f, 3.0f, 10.0f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-5.0f, 0.0f, 10.0f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(5.0f, 0.0f, 10.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(5.0f, 3.0f, 10.0f);
	glEnd();


	ball.DrawBall();
	glDisable(GL_CULL_FACE);
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
	vItems.push_back(Item(x, height + 25, z, 10.0, 0));

	x = -10, z = -60;
	height = terrain.GetHeightOnTile(z);
	vItems.push_back(Item(x, height + 25, z, 10.0, 1));

	x = 7, z = -150;
	height = terrain.GetHeightOnTile(z);
	vItems.push_back(Item(x, height + 21, z, 10.0, 0));

	x = 10, z = -205;
	height = terrain.GetHeightOnTile(z);
	vItems.push_back(Item(x, height + 20, z, 10.0, 1));

	x = 0, z = -280;
	height = terrain.GetHeightOnTile(z);
	vItems.push_back(Item(x, height + 20, z, 10.0, 0));

	x = 0, z = -300;
	height = terrain.GetHeightOnTile(z);
	vItems.push_back(Item(x, height + 20, z, 10.0, 1));

	x = -15, z = -350;
	height = terrain.GetHeightOnTile(z);
	vItems.push_back(Item(x, height + 20, z, 10.0, 1));

	x = 15, z = -420;
	height = terrain.GetHeightOnTile(z);
	vItems.push_back(Item(x, height + 20, z, 10.0, 0));

	///-------갈림길-------

	x = -115, z = -550;
	height = terrain.GetHeightOnTile(z);
	vItems.push_back(Item(x, height + 20, z, 10.0, 1));

	x = -130, z = -600;
	height = terrain.GetHeightOnTile(z);
	vItems.push_back(Item(x, height + 20, z, 10.0, 0));

	x = -140, z = -730;
	height = terrain.GetHeightOnTile(z);
	vItems.push_back(Item(x, height + 20, z, 10.0, 0));
	//-------------------------------------------------------------------
	//-------------------------------------------------------------------
	x = -20, z = -50;
	height = terrain.GetHeightOnTile(z);
	vObstacles.push_back(Obstacle(x, height + 25, z, 4));

	x = -10, z = -65;
	height = terrain.GetHeightOnTile(z);
	vObstacles.push_back(Obstacle(x, height + 25, z, 4));

	x = -10, z = -85;
	height = terrain.GetHeightOnTile(z);
	vObstacles.push_back(Obstacle(x, height + 25, z, 4));

	x = -8, z = -88;
	height = terrain.GetHeightOnTile(z);
	vObstacles.push_back(Obstacle(x, height + 23, z, 4));

	x = 0, z = -110;
	height = terrain.GetHeightOnTile(z);
	vObstacles.push_back(Obstacle(x, height + 21, z, 4));

	x = -10, z = -150;
	height = terrain.GetHeightOnTile(z);
	vObstacles.push_back(Obstacle(x, height + 25, z, 4));

	///-------횡 구간-------
	x = 0, z = -185;
	height = terrain.GetHeightOnTile(z);
	vObstacles.push_back(Obstacle(x, height + 25, z, 4));

	z = -200;
	height = terrain.GetHeightOnTile(z);
	vObstacles.push_back(Obstacle(x, height + 25, z, 4));

	z = -205;
	height = terrain.GetHeightOnTile(z);
	vObstacles.push_back(Obstacle(x, height + 2, z, 4));

	z = -240;
	height = terrain.GetHeightOnTile(z);
	vObstacles.push_back(Obstacle(x, height + 2, z, 4));

	z = -250;
	height = terrain.GetHeightOnTile(z);
	vObstacles.push_back(Obstacle(x, 15, z, 4));

	x = 12, z = -300;
	height = terrain.GetHeightOnTile(z);
	vObstacles.push_back(Obstacle(x, height + 4, z, 4));

	///-------종 구간-------
	x = -17, z = -385;
	height = terrain.GetHeightOnTile(z);
	vObstacles.push_back(Obstacle(x, height + 4, z, 4));


	///-------갈림길-------
	x = -60, z = -520;
	height = terrain.GetHeightOnTile(z);
	vObstacles.push_back(Obstacle(x, 6, z, 4));
	//오른쪽

	x = 30, z = -470;
	height = terrain.GetHeightOnTile(z);
	vObstacles.push_back(Obstacle(x, height + 8, z, 4));

	x = 45, z = -480;
	height = terrain.GetHeightOnTile(z);
	vObstacles.push_back(Obstacle(x, height + 4, z, 4));

	x = 145, z = -5500;
	height = terrain.GetHeightOnTile(z);
	vObstacles.push_back(Obstacle(x, height + 4, z, 4));

	x = 160, z = -580;
	height = terrain.GetHeightOnTile(z);
	vObstacles.push_back(Obstacle(x, height + 4, z, 4));

	x = 170, z = -600;
	height = terrain.GetHeightOnTile(z);
	vObstacles.push_back(Obstacle(x, height + 2, z, 4));

	///-------종 구간--------


	///-------횡 구간--------
	x = -135, z = -650;
	height = terrain.GetHeightOnTile(z);
	vObstacles.push_back(Obstacle(x, height + 2, z, 4));

	x = -125, z = -700;
	height = terrain.GetHeightOnTile(z);
	vObstacles.push_back(Obstacle(x, 8, z, 4));

	///-------종 구간--------
	x = -140, z = -800;
	height = terrain.GetHeightOnTile(z);
	vObstacles.push_back(Obstacle(x, height + 27, z, 4));

	x = -165, z = -850;
	height = terrain.GetHeightOnTile(z);
	vObstacles.push_back(Obstacle(x, height + 22, z, 4));

	x = -150, z = -880;
	height = terrain.GetHeightOnTile(z);
	vObstacles.push_back(Obstacle(x, height + 20, z, 4));

	x = -155, z = -900;
	height = terrain.GetHeightOnTile(z);
	vObstacles.push_back(Obstacle(x, height + 20, z, 4));

	x = -165, z = -920;
	height = terrain.GetHeightOnTile(z);
	vObstacles.push_back(Obstacle(x, height + 20, z, 4));
	//
	start = clock();
	finish = 0.0f;
	duration = 0.f;
	//
}

void Play::OnBGM()
{
	// 파일 열기
	//MCI_OPEN_PARMS mciOpen;   // MCI_OPEN_PARAMS 구조체 변수 
	//mciOpen.lpstrDeviceType = "waveaudio";  // mpegvideo : mp3, waveaudio : wav, avivideo : avi
	//mciOpen.lpstrElementName = "Resources/Beat.wav"; // 파일이름
	//mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE | MCI_OPEN_TYPE, (DWORD)(LPVOID)&mciOpen);

	//// 재생
	//MCI_PLAY_PARMS mciPlay;
	//dwID1 = mciOpen.wDeviceID;
	//mciSendCommand(dwID1, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&mciPlay);//MCI_NOTIFY : 기본, MCI_DGV_PLAY_REPEAT : 반복

	///////////////////////////////////////////////////////////////////////////////////////

	//// 파일 열기
	//MCI_OPEN_PARMS walkingOnSnow;   // MCI_OPEN_PARAMS 구조체 변수 
	//walkingOnSnow.lpstrDeviceType = "waveaudio";
	//walkingOnSnow.lpstrElementName = "Resources/walkingOnsnow.wav";
	//mciSendCommand(0, MCI_OPEN,
	//   MCI_OPEN_ELEMENT | MCI_OPEN_TYPE | MCI_OPEN_TYPE,
	//   (DWORD)(LPVOID)&walkingOnSnow);

	//// 재생
	//MCI_PLAY_PARMS mciPlay2;
	//dwID2 = walkingOnSnow.wDeviceID;
	//mciSendCommand(dwID2, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&mciPlay2);
	///////////////////////////////////////////////////////////////////////////////////


}

void Play::Timer()
{
	if (ball.GetPosZ() > -900)
	{
		finish = clock();

		duration = finish - start;
		int allsec = duration / CLOCKS_PER_SEC;

		m_Min = allsec / 60;
		m_Sec = allsec % 60;
	}
}

Scene *Play::update(void)
{
	// 초기화 함수 필요 //
	Timer();
	DrawTimer();
	DrawProgressbar();

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
	if (ball.GetPosZ() <-530.f && ball.GetPosX() > 0.f)
	{
		ball.SetPosX(0.f); ball.SetPosZ(-430.f);
		prevTerrainX = 0.f;
	}
	//------------------------------------------------------------

	ball.SetRotY(-terrain.GetYDegreeOnTile(ball.GetPosX(), ball.GetPosZ()));

	ball.Update();

	if (ball.GetPosZ() <= -900.0f)
		ResultTime++;

	if (ResultTime > 30)
		scenenum = 2;

	if (scenenum == 2)
	{
		ResultTime = 0;
		particleTime = 0;

		ball.SetPosX(0);
		ball.SetPosY(3);
		ball.SetPosZ(0);
		return new Result();
	}

	return this;
}

void Play::draw(void)
{
	light.TurnOnAmbientLight();
	light.TurnOnSnowmanLight();

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
			ItemCol[0] = false;
			accelTime = 0;

			int type = static_cast<Obstacle*>(&vObstacles[d])->GetType();

			ball.ParticleStart(vObstacles[d].GetPos(), type);
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
			ball.SetSpeed(20.0f);
			KnockbackTime = 0;
			ObCol = false;
		}
	}

	//------------------Items----------------------
	for (unsigned int d = 0; d < vItems.size(); ++d)
		if (vItems[d].CheckCollPlayerbyItem(ball.GetPosX(), ball.GetPosY(), ball.GetPosZ(), ball.GetRadius()))
		{
			sndPlaySoundA("   Resources/dash.wav", SND_ASYNC);

			if (vItems[d].GetItemType() == 0)   // 아이템 먹었을 경우
			{
				ItemCol[0] = true;
			}

			if (vItems[d].GetItemType() == 1)   // 아이템 먹었을 경우
			{
				ItemCol[1] = true;
				sndPlaySoundA("   Resources/dash.wav", SND_ASYNC);
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
			ball.SetSpeed(20.0f);
			ItemCol[0] = false;
		}
	}
	if (ItemCol[1])
	{
		for (unsigned int d = 0; d < vObstacles.size(); ++d)
		{
			if (vObstacles[d].GetPos()->z > ball.GetPosZ() - 100.0f && vObstacles[d].GetPos()->z < ball.GetPosZ())
			{
				ball.ParticleStart(vObstacles[d].GetPos(), static_cast<Obstacle*>(&vObstacles[d])->GetType());

				vObstacles.erase(vObstacles.begin() + d); //장애물 지우기
			}
		}

		ItemCol[1] = false;
	}


	//--------------------------------------------
	ball.ParticleProcess();

}

void Play::DrawTimer()
{
	glDisable(GL_LIGHTING);

	BLUE;
	int len, sec, min;

	_itoa(m_Min, buffer, 10);
	char add[] = " :";
	strcat(buffer, add);

	glRasterPos3f(75, 150, -100);
	len = (int)strlen(buffer);
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, buffer[i]);

	//
	sec = GetTimerSec();
	_itoa(m_Sec, buffer, 10);

	glRasterPos3f(90, 150, -100);

	m_bitmap = LoadDIBitmap("Resources/progress.bmp", &m_bitInfo);

	len = (int)strlen(buffer);
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, buffer[i]);
	//
	glEnable(GL_LIGHTING);

}

void Play::DrawProgressbar()
{
	glClearColor(0, 0, 0, 1);

	m_Progressbar = ball.GetPosZ() / -1000.0f;

	glDisable(GL_LIGHTING);
	WHITE;
	glRasterPos3f(-140, 180, -120);
	glPixelZoom(xscale * 10, yscale);

	glDrawPixels(40, 10, GL_RGB, GL_UNSIGNED_BYTE, m_bitmap);
	xscale = m_Progressbar;
	glEnable(GL_LIGHTING);
}


//////////////////////////////////////////////////////////////////////////////
void Result::Init()
{
}

Scene *Result::update(void)
{

	ball.ResultMove();

	if (scenenum == 0)
	{
		ball.SetPosX(0);
		ball.SetPosY(3);
		ball.SetPosZ(0);
		return new Title();
	}

	return this;
}

void Result::draw(void)
{

	camera.ResultCamera();

	glBindTexture(GL_TEXTURE_2D, texture[20]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-10.0f, 35.f, 7.0f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-10.0f, 11.f, 10.0f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(10.0f, 11.f, 10.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(10.0f, 35.f, 7.0f);
	glEnd();


	glEnable(GL_CULL_FACE);
	//	
	DrawTimer();

	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-30.0f, 0.0f, -30.0f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-30.0f, 0.0f, 30.0f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(30.0f, 0.0f, 30.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(30.0f, 0.0f, -30.0f);
	glEnd();

	ball.DrawBall();


	glDisable(GL_CULL_FACE);


}

void Result::DrawTimer()
{
	glDisable(GL_LIGHTING);

	BLUE;
	int len;

	_itoa(m_Min, buffer, 10);
	char add[] = " :";
	strcat(buffer, add);

	glRasterPos3f(-2, 25, 10);
	len = (int)strlen(buffer);
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, buffer[i]);

	//
	_itoa(m_Sec, buffer, 10);

	glRasterPos3f(2, 25, 10);

	len = (int)strlen(buffer);
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, buffer[i]);
	//
	glEnable(GL_LIGHTING);
}