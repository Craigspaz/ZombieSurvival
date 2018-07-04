#include "Enemy.h"


Enemy::Enemy(Vector2 position, Texture* texture, int size,int speed,int health, int damage,Vector2 playerPosition,float distance) : _position(position), _texture(texture), _size(size), _speed(speed), _health(health), _damage(damage), isDead(false)
{
	hurtPlayer = false;
	_direction = newVector2(1,1);
	_direction.x = (playerPosition.x - _position.x)/distance;
	_direction.y = (playerPosition.y - _position.y)/distance;
	moving = true;
	_distance = distance;
}
void Enemy::draw()
{
	GFX::drawRect(_size,_size,_position.x,_position.y,_texture->getTexture());
}
void Enemy::move(Vector2 p)
{
	_direction.x = (p.x - _position.x)/_distance;
	_direction.y = (p.y - _position.y)/_distance;
	if(moving)
	{
		_position.x += _direction.x * 200 * 0.01f;
		_position.y += _direction.y * 200 * 0.01f;
		//_position.x += _direction.x * _speed * 100 * 0.01f;
		//_position.y += _direction.y * _speed * 100 * 0.01f;
		if(_position.x == p.x && _position.y == p.y)
		{
			isDead = true;
			hurtPlayer = true;
		}
	}
}
int Enemy::getSize()
{
	return _size;
}
int Enemy::getHealth()
{
	return _health;
}
void Enemy::setHealth(int a)
{
	_health = a;
}
int Enemy::getDamage()
{
	return _damage;
}
Vector2 Enemy::getPosition()
{
	return _position;
}

Enemy::~Enemy(void)
{
	delete _texture;
}


bool Enemy::getHurtPlayer()
{
	return hurtPlayer;
}
bool Enemy::Dead()
{
	return isDead;
}


void Enemy::setHurtPlayer(bool a)
{
	hurtPlayer = a;
}
void Enemy::setDead(bool a)
{
	isDead = a;
}

float Enemy::getDistance()
{
	return _distance;
}
