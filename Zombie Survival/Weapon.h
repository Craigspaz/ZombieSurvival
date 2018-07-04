#ifndef _WEAPON
#define _WEAPON
#include "Item.h"
#include <iostream>
#include <string>
class Weapon : public Item
{
public:
	Weapon(int x, int y,std::string name, int damage, int type, int ammo, Texture* texture);
	~Weapon(void);
	int getDamage();
	void setDamage(int a);
	int getType();
	int getAmmo();
	void setAmmo(int a);
private:
	int _damage;
	int _type;
	int _ammo;
};

#endif