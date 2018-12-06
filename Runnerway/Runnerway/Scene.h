#pragma once

enum STATE { TITLE, LOBBY, MAP1, MAP2, RESULT };

class Scene {
public:
	virtual Scene *update(void) = 0;
	virtual void draw() = 0;
};

class Title : public Scene {
public:
	Scene *update(void);
	void draw();
};

class Lobby : public Scene {
public:
	Scene *update(void);
	void draw();
};

class Play : public Scene {
public:
	Scene *update(void);
	void draw();
};

class Result : public Scene {
public:
	Scene *update(void);
	void draw();
};

void update();
void draw();