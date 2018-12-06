#pragma once
//----------------Include----------------
#include <vector>
#include "Ball.h"
using namespace std;



//----------------Default----------------
#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 700



//----------------Color-----------------
#define RED				glColor3f(1.f, 0.f, 0.f)
#define WHITE			glColor3f(1.f, 1.f, 1.f)
#define GREEN			glColor3f(0.0f, 1.0f, 0.0f)
#define BLACK			glColor3f(0.0f, 0.0f, 0.0f)
#define YELLOW			glColor3f(1.0f, 1.0f, 0.0f)
#define BLUE				glColor3f(0.0f, 0.0f, 1.0f)
#define CYAN				glColor3f(0.0f, 1.0f, 1.0f)
#define MAGENTA		glColor3f(1.0f, 0.0f, 1.0f)
#define BROWN			glColor3f(0.6f, 0.3f, 0.06f)
#define SOIL				glColor3f(0.5f, 0.4f, 0.22f)

//----------------Check----------------
#define CheckBoundary(min,max,val) ((min<=val) && (val<=max))? true: false 
#define CheckCollRectbyPoint(rX,rY,pX,pY) 	((rX - 10 <= pX) && (pX <= rX + 10) && (rY - 10 <= pY) && (pY <= rY + 10))? true:  false

//----------------Function----------------
GLvoid Reshape(int, int);
GLvoid drawScene(GLvoid);
void TimerFunction(int);
void Keyboard(unsigned char, int, int);
void SpecialKeyboard(int, int, int);