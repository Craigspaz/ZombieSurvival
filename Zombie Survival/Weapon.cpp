#include "Weapon.h"


Weapon::Weapon(int x,int y,std::string name, int damage, int type, int ammo,Texture* texture) : Item(x,y,texture,name) , _damage(damage), _ammo(ammo), _type(type)
{

}


Weapon::~Weapon(void)
{

}


int Weapon::getDamage()
{
	return _damage;
}
void Weapon::setDamage(int a)
{
	_damage = a;
}
int Weapon::getType()
{
	return _type;
}
int Weapon::getAmmo()
{
	return _ammo;
}
void Weapon::setAmmo(int a)
{
	_ammo = a;
}
