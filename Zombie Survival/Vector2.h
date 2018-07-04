#ifndef _VECTOR2_H
#define _VECTOR2_H
#include <iostream>
#include <GLFW\glfw3.h>
typedef struct {
	float x;
	float y;
}Vector2;

Vector2 newVector2(float x, float y);
Vector2 addVector2(Vector2 a, Vector2 b);
#endif