#ifndef _AMMO_H
#define _AMMO_H
#include "Vector2.h"
#include "Item.h"
#include "GFX.h"
class Ammo : public Item
{
public:
	Ammo(Vector2 position, int amount,Texture* texture);
	int getAmmo();
	~Ammo(void);
private:
	Vector2 _position;
	int _ammount;
};
#endif