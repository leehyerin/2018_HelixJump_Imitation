#include "stdafx.h"
#include "Input.cpp"

Camera camera;

Scene *scene = new Title();
int scenenum = 0;

void update();
void draw();

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

	glEnable(GL_DEPTH_TEST);
	glutMainLoop (); 
} 

GLvoid drawScene( GLvoid ) 
{ 
	glClearColor(0.5f, 0.5f, 1.f, 0.5f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

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
}

void draw()
{
	scene->draw();
}