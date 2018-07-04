#include "Block.h"


Block::Block(int x, int y, Texture* texture,int type) : _x(x), _y(y), _texture(texture), _type(type), _size(32)
{

}
Block::~Block(void)
{

}
void Block::draw()
{
	GFX::drawRect(_size,_size,_x * _size,_y * _size,_texture->getTexture());
}
int Block::getX()
{
	return _x;
}
int Block::getY()
{
	return _y;
}
void Block::setX(int a)
{
	_x = a;
}
void Block::setY(int a)
{
	_y = a;
}