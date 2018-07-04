#ifndef _GFX_H
#define _GFX_H
#include <stdlib.h>
#include <iostream>
#include <glut.h>
#include <string>
#include <cstring>
#include <GLFW\glfw3.h>
#include <math.h>
#include <cmath>
class GFX
{
public:
	GFX();
	~GFX();

	static void drawRect(float x, float y, float xx, float yy, GLuint texture);
	static void drawRect(float x, float y, float xx, float yy);
	static void drawLine(float x, float y, float xx, float yy, GLuint texture);
	static void drawLine(float x, float y, float xx, float yy);
	static void drawString(float x, float y, const char* text, float r, float g, float b);
	static void drawCircle(float x, float y, float r);
	static void drawCircle(float x, float y,float r, GLuint texture);
	//static void drawString(float x, float y, std::string text, float r, float g, float b);
};

#endif