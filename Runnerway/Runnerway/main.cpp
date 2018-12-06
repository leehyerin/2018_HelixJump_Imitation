#include "stdafx.h"
#include "Input.cpp"

Camera camera;
Ball ball;
Ground ground;
vector<Item> vItems;
vector<Obstacle> vObstacles;

Scene *scene = new Title();
int scenenum = 0;

int main(int argc, char *argv[]) 
{ 
	//초기화 함수들 
	glutInit (&argc, argv); 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition ( 0, 0 ); 	
	glutInitWindowSize ( WINDOW_WIDTH, WINDOW_HEIGHT ); 	
	glutCreateWindow ( "Runnerway" ); 	
	glutDisplayFunc (drawScene);
	glutReshapeFunc (Reshape);	
	glutTimerFunc(100, TimerFunction, 1);

	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecialKeyboard);

	//--------Init----------
	vItems.push_back(Item(0.0, 5.0, -20.0, 10.0));
	vItems.push_back(Item(10.0, 5.0, -60.0, 10.0));
	vItems.push_back(Item(-10.0, 5.0, -100.0, 10.0));
	vItems.push_back(Item(10.0, 5.0, -120.0, 10.0));
	vItems.push_back(Item(10.0, 5.0, -160.0, 10.0));

	vObstacles.push_back(Obstacle(0, 5, 0, 5));
	//---------------------

	glEnable(GL_DEPTH_TEST);
	glutMainLoop (); 
} 

GLvoid drawScene( GLvoid ) 
{ 
	glClearColor(0.5f, 0.5f, 1.f, 0.5f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	draw();

	glutSwapBuffers();
}

GLvoid Reshape(int w, int h) 
{ 
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, (double)WINDOW_WIDTH / (double)WINDOW_HEIGHT, 1.0, 1000.0);
}

void TimerFunction(int value)
{
	update();

	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}
