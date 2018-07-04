#include "Ammo.h"


Ammo::Ammo(Vector2 position, int amount, Texture* texture) : Item((int)position.x,(int)position.y,texture,"Ammo"), _position(position), _ammount(amount)
{

}


Ammo::~Ammo(void)
{
}

int Ammo::getAmmo()
{
	return _ammount;
}
