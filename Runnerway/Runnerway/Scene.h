#pragma once

enum STATE { TITLE, LOBBY, MAP1, MAP2, RESULT };

class Scene {
public:
	virtual void Init() = 0;
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
public:
	Play();
	virtual void Init();
	Scene *update(void);
	void draw();
};

class Result : public Scene {
public:
	virtual void Init();
	Scene *update(void);
	void draw();
};

