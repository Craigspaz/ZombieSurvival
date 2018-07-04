#include "Item.h"
#include "GFX.h"


Item::Item(int x, int y, Texture* texture, std::string name): _x(x), _y(y), _texture(texture), _size(32), _name(name), isEquipped(false)
{

}

void Item::draw()
{
	GFX::drawRect(_size,_size,_x,_y, _texture->getTexture());
}

void Item::setX(int a)
{
	_x = a;
}
void Item::setY(int a)
{
	_y = a;
}
int Item::getX()
{
	return _x;
}
int Item::getY()
{
	return _y;
}


Item::~Item(void)
{
	delete _texture;
}


bool Item::getIsOnGround()
{
	return isOnGround;
}
void Item::setIsOnGround(bool a)
{
	isOnGround = a;
}

std::string Item::getName()
{
	return _name;
}

bool Item::getEquippedState()
{
	return isEquipped;
}
