#include "Bullet.h"


Bullet::Bullet(Vector2 p, Vector2 m,Texture* texture,float distance): _p(p), _m(m), _texture(texture),_distance(distance)
{
	_direction = newVector2(1,1);
	_direction.x = (m.x - p.x)/distance;
	_direction.y = (m.y - p.y)/distance;
	moving = true;
	Delete = false;
}
void Bullet::move(int width, int height)
{
	if(moving)
	{
		_p.x += _direction.x * 700 * 0.01f;
		_p.y += _direction.y * 700 * 0.01f;
		if(_p.x > width || _p.x < 0 || _p.y < 0 || _p.y > height)
		{
			Delete = true;
		}
	}
}
void Bullet::draw()
{
	GFX::drawRect(32,32,_p.x,_p.y,_texture->getTexture());
}
Bullet::~Bullet(void)
{
	delete _texture;
}


bool Bullet::getDelete()
{
	return Delete;
}


Vector2 Bullet::getPosition()
{
	return _p;
}
void Bullet::setDelete(bool a)
{
	Delete = a;
}
