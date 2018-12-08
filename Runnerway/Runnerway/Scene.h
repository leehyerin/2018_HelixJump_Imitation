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
	time_t m_timer = time(NULL);
	struct tm * t = localtime(&m_timer);
	int m_Min;
	int m_Sec;

	float m_Progressbar{ 0 };
public:
	Play();
	virtual void Init();
	virtual void OnBGM();
	void Timer();

	Scene *update(void);
	void draw();
};

class Result : public Scene {
public:
	virtual void Init();
	Scene *update(void);
	void draw();
};

