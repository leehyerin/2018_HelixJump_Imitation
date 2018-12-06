#include <GL/freeglut.h>
#include "Input.cpp"
#include "Ground.h"

Camera camera;
Ball ball;
Ground ground;

bool isJump = false;
int time = 0;

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


	camera.CameraPos();
	glEnable(GL_CULL_FACE); 
	ball.DrawBall();
	glDisable(GL_CULL_FACE);
	ground.Draw();

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
	ball.SetRotZ(ball.GetRotZ() - ball.GetSpeed());
	ball.SetPosZ(ball.GetPosZ() - 1 * PI * ball.GetRadius() / (360 / ball.GetSpeed()));

	if (isJump)
	{
		if (time < 5)
			ball.SetPosY(ball.GetPosY() + 1);
		else if (time >= 5 && time < 10)
			ball.SetPosY(ball.GetPosY() - 1);
		else
		{
			isJump = false;
			time = 0;
		}

		time++;
	}

	glutPostRedisplay();
	glutTimerFunc(100, TimerFunction, 1);
}
