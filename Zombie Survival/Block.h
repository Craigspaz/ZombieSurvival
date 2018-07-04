#ifndef _BLOCK_H
#define _BLOCK_H
#include "GFX.h"
#include "Texture.h"
class Block
{
public:
	Block(int x, int y, Texture* texture,int type);
	~Block(void);
	void draw();
	int getX();
	int getY();
	void setX(int a);
	void setY(int a);
private:
	int _x;
	int _y;
	Texture* _texture;
	int _type;
	int _size;
};

#endif