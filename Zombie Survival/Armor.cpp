#include "Armor.h"


Armor::Armor(int x, int y, Texture* texture, int health): Item(x,y,texture,"Armor"),_health(health), destroyed(false)
{
}


Armor::~Armor(void)
{
}
	
int Armor::getHealth()
{
	return _health;
}

void Armor::setDestroyed(bool a)
{
	destroyed = a;
}

bool Armor::getDestroyed()
{
	return destroyed;
}
