#pragma once

enum STATE { TITLE, PLAY, RESULT };

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

class Play : public Scene {
	//타이머
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
	//타이머
	char buffer[10];

	GLubyte *m_bitmap;
	BITMAPINFO *m_bitInfo;

	clock_t start, finish;
	float duration;

	int m_Min{ 0 };
	int m_Sec{ 0 };

public:
	Result() {}
	Result(int min, int sec) { m_Min = min; m_Sec = sec; }
	void SetTime(int min, int sec) { m_Min = min; m_Sec = sec; }

	virtual void Init();
	Scene *update(void);
	void draw();
	void DrawTimer();
};
