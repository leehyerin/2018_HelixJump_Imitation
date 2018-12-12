#include "stdafx.h"
#include "Input.cpp"
Camera camera;

Scene *scene = new Title();
int scenenum = 0;
GLuint texture[21];
GLubyte *pBytes; // 데이터를 가리킬 포인터
BITMAPINFO *info; // 비트맵 헤더 저장할 변수

Light light;

GLubyte *m_bitmap1;
BITMAPINFO *m_bitInfo1;

void update();
void draw();

void DrawSky();

GLubyte * LoadDIBitmap(const char* filename, BITMAPINFO** info);
void LoadTexture();
int min, sec;

int main(int argc, char *argv[])
{
	//초기화 함수들 
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Runnerway");

	LoadTexture();

	glutDisplayFunc(drawScene);
	glutReshapeFunc(Reshape);
	glutTimerFunc(100, TimerFunction, 1);

	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeyboard);

	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}

GLvoid drawScene(GLvoid)
{
	glClearColor(0.5f, 0.5f, 1.f, 0.5f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	update();
	draw();

	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(120, (double)WINDOW_WIDTH / (double)WINDOW_HEIGHT, 1.0, 1000.0);
}

void TimerFunction(int value)
{
	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}

void update()
{
	Scene *next = scene->update();

	if (next != scene)
	{
		delete scene;
		scene = next;
	}
	if (scenenum == RESULT)
		static_cast<Result*> (scene)->SetTime(min, sec);
}

void draw()
{
	if (scenenum == TITLE || scenenum == RESULT)
		DrawSky();
	glEnable(GL_LIGHTING);

	scene->draw();

	if (scenenum == PLAY)
	{
		DrawSky();
		min = static_cast<Play*> (scene)->GetTimerMin();
		sec = static_cast<Play*> (scene)->GetTimerSec();
	}
	if (scenenum == RESULT)
		static_cast<Result*> (scene)->DrawTimer();
}

void DrawSky()
{
	WHITE;
	float z = ball.GetPosZ();


	//----left----
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-500.0f, -300.0f, -250.0f + z);

	glTexCoord2f(0.25f, 0.0f);
	glVertex3f(-500.0f, 700.0f, -250.0f + z);

	glTexCoord2f(0.25f, 1.0f);
	glVertex3f(-500.0f, 700.0f, 500.0f + z);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-500.0f, -300.0f, 500.0f + z);
	glEnd();
	//----Right----
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.25f, 0.0f);
	glVertex3f(500.0f, -300.0f, -250.0f + z);

	glTexCoord2f(0.5f, 0.0f);
	glVertex3f(500.0f, 700.0f, -250.0f + z);

	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(500.0f, 700.0f, 500.0f + z);

	glTexCoord2f(0.25f, 1.0f);
	glVertex3f(500.0f, -300.0f, 500.0f + z);
	glEnd();
	//----Back-----
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.5f, 0.0f);
	glVertex3f(-500.0f, -300.0f, 250.0f + z);

	glTexCoord2f(0.75f, 0.0f);
	glVertex3f(-500.0f, 700.0f, 250.0f + z);

	glTexCoord2f(0.75f, 1.0f);
	glVertex3f(500.0f, 700.0f, 250.0f + z);

	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(500.0f, -300.0f, 250.0f + z);
	glEnd();
	//----Front-----
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.75f, 0.0f);
	glVertex3f(-500.0f, -300.0f, -250.0f + z);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-500.0f, 700.0f, -250.0f + z);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(500.0f, 700.0f, -250.0f + z);

	glTexCoord2f(0.75f, 1.0f);
	glVertex3f(500.0f, -300.0f, -250.0f + z);
	glEnd();

	//----down----
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.25f, 1.0f);
	glVertex3f(-500.0f, -300.0f, -250.0f + z);

	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(-500.0f, -300.0f, 500.0f + z);

	glTexCoord2f(0.5f, 0.0f);
	glVertex3f(500.0f, -300.0f, 500.0f + z);

	glTexCoord2f(0.25f, 0.0f);
	glVertex3f(500.0f, -300.0f, -250.0f + z);
	glEnd();
	//----up----
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(0.25f, 0.0f);
	glVertex3f(-500.0f, 700.0f, -250.0f + z);

	glTexCoord2f(0.5f, 0.0f);
	glVertex3f(-500.0f, 700.0f, 500.0f + z);

	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(500.0f, 700.0f, 500.0f + z);

	glTexCoord2f(0.25f, 1.0f);
	glVertex3f(500.0f, 700.0f, -250.0f + z);
	glEnd();
}


inline GLubyte * LoadDIBitmap(const char* filename, BITMAPINFO** info)
{
	FILE *fp;
	GLubyte *bits;
	int bitsize, infosize;
	BITMAPFILEHEADER header;

	// 바이너리 읽기 모드로 파일을 연다 
	if ((fp = fopen(filename, "rb")) == NULL)
		return NULL;

	// 비트맵 파일 헤더를 읽는다. 
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1)
	{
		fclose(fp);
		return NULL;
	}

	// 파일이 BMP 파일인지 확인한다.
	if (header.bfType != 'MB')
	{
		fclose(fp);
		return NULL;
	}

	// BITMAPINFOHEADER 위치로 간다.
	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);

	// 비트맵 이미지 데이터를 넣을 메모리 할당을 한다.
	if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL)
	{
		fclose(fp);
		exit(0);
		return NULL;
	}

	// 비트맵 인포 헤더를 읽는다. 
	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize)
	{
		free(*info);
		fclose(fp);
		return NULL;
	}

	// 비트맵의 크기 설정
	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth*(*info)->bmiHeader.biBitCount + 7) / 8.0 *  abs((*info)->bmiHeader.biHeight);

	// 비트맵의 크기만큼 메모리를 할당한다.
	if ((bits = (unsigned char *)malloc(bitsize)) == NULL)
	{
		free(*info);
		fclose(fp);
		return NULL;
	}

	// 비트맵 데이터를 bit(GLubyte 타입)에 저장한다.
	if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize)
	{
		free(*info);
		free(bits);
		fclose(fp);
		return NULL;
	}

	fclose(fp);
	return bits;
}


void LoadTexture()
{
	glGenTextures(21, texture);

	// 스카이박스 1
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	pBytes = LoadDIBitmap("Resources/Textures/wideTex.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 1914, 720, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 스카이박스 2
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	pBytes = LoadDIBitmap("background2.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 1600, 1280, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//눈사람2
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	pBytes = LoadDIBitmap("Resources/Textures/snowww.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 538, 396, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 아이템
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	pBytes = LoadDIBitmap("Resources/item.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 616, 616, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 바닥
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	pBytes = LoadDIBitmap("Resources/Load.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 276, 233, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 눈사람
	glBindTexture(GL_TEXTURE_2D, texture[5]);
	pBytes = LoadDIBitmap("Resources/snowman.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 538, 396, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 파티클
	glBindTexture(GL_TEXTURE_2D, texture[6]);
	pBytes = LoadDIBitmap("Resources/Particle.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 254, 233, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	// 장애물-꽃2
	glBindTexture(GL_TEXTURE_2D, texture[7]);
	pBytes = LoadDIBitmap("Resources/Textures/pflower.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 418, 418, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	// 장애물-꽃3
	glBindTexture(GL_TEXTURE_2D, texture[8]);
	pBytes = LoadDIBitmap("Resources/Textures/rflower.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 227, 222, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 장애물-꽃4
	glBindTexture(GL_TEXTURE_2D, texture[9]);
	pBytes = LoadDIBitmap("Resources/Textures/wflower.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 300, 260, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 장애물-꽃1
	glBindTexture(GL_TEXTURE_2D, texture[10]);
	pBytes = LoadDIBitmap("Resources/Textures/bigflower.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 394, 378, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 눈사람
	glBindTexture(GL_TEXTURE_2D, texture[11]);
	pBytes = LoadDIBitmap("Resources/Textures/snow0.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 538, 396, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 눈사람
	glBindTexture(GL_TEXTURE_2D, texture[12]);
	pBytes = LoadDIBitmap("Resources/Textures/snow1.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 538, 396, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 눈사람
	glBindTexture(GL_TEXTURE_2D, texture[13]);
	pBytes = LoadDIBitmap("Resources/Textures/snow2.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 538, 396, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 눈사람
	glBindTexture(GL_TEXTURE_2D, texture[14]);
	pBytes = LoadDIBitmap("Resources/Textures/snow3.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 538, 396, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 눈사람
	glBindTexture(GL_TEXTURE_2D, texture[15]);
	pBytes = LoadDIBitmap("Resources/Textures/snow4.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 538, 396, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	// 눈사람
	glBindTexture(GL_TEXTURE_2D, texture[15]);
	pBytes = LoadDIBitmap("Resources/Textures/snow4.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 538, 396, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	// 눈사람
	glBindTexture(GL_TEXTURE_2D, texture[16]);
	pBytes = LoadDIBitmap("Resources/Textures/snow5.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 538, 396, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	// 눈사람
	glBindTexture(GL_TEXTURE_2D, texture[17]);
	pBytes = LoadDIBitmap("Resources/Textures/snow6.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 538, 396, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// press 어쩌구
	glBindTexture(GL_TEXTURE_2D, texture[18]);
	pBytes = LoadDIBitmap("Resources/pets.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 93, 399, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 타이틀
	glBindTexture(GL_TEXTURE_2D, texture[19]);
	pBytes = LoadDIBitmap("Resources/title.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 211, 479, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// 결과
	glBindTexture(GL_TEXTURE_2D, texture[20]);
	pBytes = LoadDIBitmap("Resources/result.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 400, 400, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}