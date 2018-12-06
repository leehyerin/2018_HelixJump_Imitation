#include <GL/freeglut.h>
#include "MyHeader.h"
#include "Input.cpp"
#include "Math.h"
#include "Ground.h"

Ball cBall;
Ground cGround;
double dx{0}, dy{ 0 }, z{ -50 };
void CameraReset();

int main(int argc, char *argv[]) 
{ 
	//초기화 함수들 
	glutInit (&argc, argv); 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition ( 0, 0 ); 	
	glutInitWindowSize ( WINDOW_WIDTH, WINDOW_HEIGHT ); 	
	glutCreateWindow ( "Runnerway" ); 	
	glutDisplayFunc (drawScene );
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

	cGround.Draw();
	glEnable(GL_CULL_FACE);
	cBall.DrawBall();
	glDisable(GL_CULL_FACE);


	glutSwapBuffers();
}

GLvoid Reshape(int w, int h) 
{ 
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(60, (double)WINDOW_WIDTH / (double)WINDOW_HEIGHT, 1.0, 1000.0);

	glTranslated(0, 0, z);
	glTranslated(dx, 0, 0);

	glRotated(30, 1, 0, 0);	
	glRotated(dy,0, 1, 0);
}

void CameraReset()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(90, (double)WINDOW_WIDTH / (double)WINDOW_HEIGHT, 1.0, 1000.0);

	glTranslated(0, 0, z);
	glRotated(dx, 1, 0, 0);

	glRotated(20, 1, 0, 0);
	glRotated(dy, 0, 1, 0);
}

void TimerFunction(int value)
{	CameraReset();

	cBall.SetRotZ(cBall.GetRotZ() - 3);
	cBall.SetPosZ(cBall.GetPosZ() - 1 * PI * cBall.GetRadius() / 120);

	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}
