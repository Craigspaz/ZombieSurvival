#include "Player.h"


Player::Player(int x, int y, Texture* texture):_x(x), _y(y), _texture(texture), _size(32),_speed(3), _direction(3),canFire(true),fireCounter(0), _health(100)
{
	_items = new std::vector<Item*>();
	bullets = new std::vector<Bullet*>();
}
Player::~Player(void)
{
	delete _texture;
	delete _selectedWeapon;
	delete bullets;
	delete _items;
	delete _weapons;
}
void Player::moveRight()
{
	_x += _speed;
}
void Player::moveLeft()
{
	_x -= _speed;
}
void Player::moveUp()
{
	_y -= _speed;
}
void Player::moveDown()
{
	_y += _speed;
}
void Player::setHealth(int a)
{
	_health = a;
}
int Player::getHealth()
{
	return _health;
}
std::vector<Item*>* Player::getItems()
{
	return _items;
}
void Player::addItems(Item* item)
{
	_items->push_back(item);
}

void Player::draw()
{
	GFX::drawRect(_size,_size,_x,_y,_texture->getTexture());
}


void Player::setTexture(Texture* texture)
{
	_texture = texture;
}

void Player::setX(int a)
{
	_x = a;
}
void Player::setY(int a)
{
	_y = a;
}
int Player::getX()
{
	return _x;
}
int Player::getY()
{
	return _y;
}

int Player::getSize()
{
	return _size;
}


int Player::getDirection()
{
	return _direction;
}

void Player::updateBullets(int width, int height)
{
	int counter = 0;
	for(std::vector<Bullet*>::iterator i = bullets->begin(); i != bullets->end(); i++)
	{
		(*i)->move(width,height);
		if((*i)->getDelete() == true)
		{
			bullets->erase(i);
			break;
		}
		counter++;
	}
}


void Player::setDirection(int a)
{
	_direction = a;
}

void Player::shoot(int x, int y,Texture* texture)
{
	if(canFire && getSelectedWeapon()->getAmmo() > 0)
	{
		bullets->push_back(new Bullet(newVector2(_x,_y),newVector2(x,y),texture,sqrt(pow(x-_x,2.0)+pow(y-_y,2.0))));
		getSelectedWeapon()->setAmmo(getSelectedWeapon()->getAmmo() - 1);
		canFire = false;
	}
}


Item* Player::getSelectedItem()
{
	return _selected;
}
void Player::setSelectedItem(Item* item)
{
	_selected = item;
}


std::vector<Weapon*>* Player::getWeapons()
{
	return _weapons;
}
void Player::addWeapons(Weapon* weapon)
{
	_weapons->push_back(weapon);
}


Weapon* Player::getSelectedWeapon()
{
	return _selectedWeapon;
}
void Player::setSelectedWeapon(Weapon* weapon)
{
	_selectedWeapon = weapon;
}


void Player::drawBullets()
{
	for(std::vector<Bullet*>::iterator i = bullets->begin(); i != bullets->end(); i++)
	{
		(*i)->draw();
	}
}

void Player::reload()
{
	if (fireCounter >= 15)
	{
		std::cout << "FireCounter is at " << 15 << std::endl;
		canFire = true;
		fireCounter = 0;
	}
	else
	{
		canFire = false;
		fireCounter += 1;
	}
}

bool Player::getCanFire()
{
	return canFire;
}


std::vector<Bullet*>* Player::getBullets()
{
	return bullets;
}