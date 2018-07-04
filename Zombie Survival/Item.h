#ifndef _ITEM_H
#define _ITEM_H
#include "Texture.h"
#include <iostream>
#include <string>
class Item
{
public:
	Item(int x, int y,Texture* texture,std::string name);
	~Item(void);
	void draw();
	void setX(int a);
	void setY(int a);
	int getX();
	int getY();
	bool getIsOnGround();
	void setIsOnGround(bool a);
	std::string getName();
	bool getEquippedState();
private:
	int _x;
	int _y;
	Texture* _texture;
	int _size;
	bool isOnGround;
	std::string _name;
	bool isEquipped;
};

#endif