#ifndef _PLAYER_H
#define _PLAYER_H
#include <vector>
#include "GFX.h"
#include "Texture.h"
#include "Item.h"
#include "Weapon.h"
#include "Bullet.h"
#include "Vector2.h"
#include <math.h>
class Player
{
public:
	Player(int x, int y, Texture* texture);
	~Player(void);
	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();
	void setHealth(int a);
	int getHealth();
	std::vector<Item*>* getItems();
	void addItems(Item* item);
	std::vector<Weapon*>* getWeapons();
	void addWeapons(Weapon* weapon);
	void draw();
	void setTexture(Texture* texture);
	void setX(int a);
	void setY(int a);
	int getX();
	int getY();
	int getSize();
	int getDirection();
	void setDirection(int a);
	void shoot(int x, int y,Texture* texture);
	Item* getSelectedItem();
	void setSelectedItem(Item* item);
	Weapon* getSelectedWeapon();
	void setSelectedWeapon(Weapon* weapon);
	void drawBullets();
	void updateBullets(int width, int height);
	void reload();
	bool getCanFire();
	std::vector<Bullet*>* getBullets();

private:
	std::vector<Item*>* _items;
	std::vector<Weapon*>* _weapons;
	int _x;
	int _y;
	int _size;
	Texture* _texture;
	int _speed;
	int _health;
	int _direction;
	Item* _selected;
	Weapon* _selectedWeapon;
	std::vector<Bullet*>* bullets;
	bool canFire;
	int fireCounter;
};

#endif