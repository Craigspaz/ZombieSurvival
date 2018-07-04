#include "Vector2.h"
Vector2 addVector3(Vector2 a, Vector2 b)
{
	Vector2 sum;
	sum.x = a.x + a.y;
	sum.y = a.y + a.y;
	return sum;
}

Vector2 newVector2(float x, float y)
{
	Vector2 n;
	n.x = x;
	n.y = y;
	return n;
}