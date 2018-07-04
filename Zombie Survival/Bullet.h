#ifndef _BULLET_H
#define _BULLET_H
#include "Vector2.h"
#include "GFX.h"
#include "Texture.h"
class Bullet
{
public:
	Bullet(Vector2 p, Vector2 m,Texture* texture, float distance);
	void move(int width,int height);
	void draw();
	~Bullet(void);
	bool getDelete();
	void setDelete(bool a);
	Vector2 getPosition();
private:
	Vector2 _p;
	Vector2 _m;
	Texture* _texture;
	float _distance;
	Vector2 _direction;
	bool moving;
	bool Delete;
};

#endif