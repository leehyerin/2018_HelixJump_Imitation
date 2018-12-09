#pragma once

enum STATE { TITLE, LOBBY, MAP1, MAP2, RESULT };

class Scene {
public:
	virtual void Init() = 0;
	virtual void OnBGM() {};
	virtual Scene *update(void) = 0;
	virtual void draw() = 0;
};

class Title : public Scene {
public:
	virtual void Init();
	Scene *update(void);
	void draw();
};

class Lobby : public Scene {
public:
	virtual void Init();
	Scene *update(void);
	void draw();
};

class Play : public Scene {
	//≈∏¿Ã∏”
	char buffer[10];

	//UI
	GLfloat xscale{ 0.0 }, yscale{ 3.0 };

	GLubyte *m_bitmap;
	BITMAPINFO *m_bitInfo;

	clock_t start, finish;
	float duration;

	int m_Min{ 0 };
	int m_Sec{ 0 };

	float m_Progressbar{ 0 };
public:
	Play();
	virtual void Init();
	virtual void OnBGM();
	void Timer();
	int GetTimerMin() { return m_Min; }
	int GetTimerSec() { return m_Sec; }
	Scene *update(void);
	void draw();
	void DrawTimer();
	void DrawProgressbar();
};

class Result : public Scene {
public:
	virtual void Init();
	Scene *update(void);
	void draw();
};

