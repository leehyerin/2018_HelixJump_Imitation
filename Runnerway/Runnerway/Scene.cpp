enum STATE { TITLE, PLAY, RESULT };

class Title {
	void update();
};

class Play {
	void update();
};

class Result {
	void update();
};

STATE state;

Title *title = new Title();
Play *play = new Play();
Result *result = new Result();

void update()
{
	switch (state)
	{
	case TITLE:
		title->update();
		break;

	case PLAY:
		play->update();
		break;

	case RESULT:
		result->update();
		break;
	}
}