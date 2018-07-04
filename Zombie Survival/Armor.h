#ifndef _ARMOR_H
#define _ARMOR_H
#include <iostream>
#include "Item.h"
class Armor : public Item
{
public:
	Armor(int x, int y, Texture* texture, int health);
	~Armor(void);
	int getHealth();
	void setDestroyed(bool a);
	bool getDestroyed();
private:
	int _health;
	bool destroyed;
};

#endif