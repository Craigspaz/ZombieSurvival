#ifndef _ENEMY_H
#define _ENEMY_H
#include "Vector2.h"
#include "GFX.h"
#include "Texture.h"
class Enemy
{
public:
	Enemy(Vector2 position, Texture* texture, int size,int speed,int health, int damage,Vector2 playerPosition,float distance);
	void draw();
	void move(Vector2 playerPosition);
	int getSize();
	int getHealth();
	void setHealth(int a);
	int getDamage();
	Vector2 getPosition();
	bool getHurtPlayer();
	void setHurtPlayer(bool a);
	void setDead(bool a);
	bool Dead();
	float getDistance();
	~Enemy(void);

private:
	Vector2 _position;
	Texture* _texture;
	int _size;
	int _speed;
	int _health;
	int _damage;
	Vector2 _direction;
	bool moving;
	bool isDead;
	bool hurtPlayer;
	float _distance;
};

#endif