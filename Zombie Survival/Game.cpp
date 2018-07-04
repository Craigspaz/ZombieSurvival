#define _WIN32_WINNT 0x0500
#include "Game.h"
#include <Windows.h>
#include <MMSystem.h>
#include <iostream>
#include <fstream>
#include <conio.h>


Game::Game(int width, int height) :
_width(width), _height(height),
_keyboard(&Keyboard::getKeyboard()),
_mouse(&Mouse::getMouse()),
state(MAIN_MENU),
hoverOverExitButton_Main_Menu(false),
hoverOverExitButton_Pause_Menu(false),
hoverOverPlayButton_Main_Menu(false),
hoverOverWaveStartButton_Game(false),
hoverOverHighScores_Main_Menu(false),
textureWidth(256),
textureHeight(64),
hoverOverResumeButton_Pause_Menu(false),
enemyCounter(0),
maxEnemyCounter(0),
itemCounter(0),
gameOver(false),
score(0),
addedScore(false),
pauseMenuTime(0),
endpauseMenuTime(0),
elapsedPauseMenuTime(0),
armorCounter(0),
lengthSums(0),
lengthCounter(0),
averageLength(0)
{
	if (_width == 1920)
	{
		textureWidth = 512;
	}
	if (_height == 1080)
	{
		textureHeight = 128;
	}	
	textures = new Textures();
	world = new std::vector<Block*>();	
	enemies = new std::vector<Enemy*>();
	ammo = new std::vector<Ammo*>();
	armor = new std::vector<Armor*>();
	highScores = new std::vector<std::string>();
	for(int x = 0; x < 60; x++)
	{
		for(int y = 0; y < 60; y++)
		{
			world->push_back(new Block(x,y,textures->getDirt2Texture(),0));
		}
	}
	_player = new Player((_width / 2), (_height / 2),textures->getPlayerFrontTexture());
	Weapon* weapon = new Weapon(0,0,"Test Weapon",5,0,20,textures->getAirTexture());
	_player->setSelectedWeapon(weapon);
	PlaySound((LPCSTR)TEXT("res/audio/Adventure_Meme.wav"), NULL, SND_ASYNC);
}


Game::~Game()
{
	_keyboard->destroyKeyboard();
	_mouse->destroyMouse();
	delete textures;
	delete ammo;
	delete world;
	delete enemies;
	delete highScores;
	delete _player;
}

float sign(Vector2 p1, Vector2 p2, Vector2 p3)
{
	return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

bool PointInTriangle(Vector2 pt, Vector2 v1, Vector2 v2, Vector2 v3)
{
	bool b1, b2, b3;

	b1 = sign(pt,v1,v2) < 0.0f;
	b2 = sign(pt,v2,v3) < 0.0f;
	b3 = sign(pt,v3,v1) < 0.0f;
	return ((b1 == b2) && (b2 == b3));
}
void Game::update()
{
	if (state == MAIN_MENU)
	{
		if (_mouse->getX() > _width / 2 - (textureWidth / 2) && _mouse->getX() < _width / 2 + (textureWidth / 2) && _mouse->getY() > _height / 3 - (textureHeight / 2) && _mouse->getY() < _height / 3 + (textureHeight / 2))
		{
			hoverOverPlayButton_Main_Menu = true;
			if (_mouse->getMouseState(GLFW_MOUSE_BUTTON_1) == true)
			{
				std::cout << "Play Button Pressed\n";
				hoverOverPlayButton_Main_Menu = false;
				hoverOverExitButton_Main_Menu = false;
				hoverOverExitButton_Pause_Menu = false;
				hoverOverWaveStartButton_Game = false;
				hoverOverResumeButton_Pause_Menu = false;
				hoverOverHighScores_Main_Menu = false;
				state = GAME;
				start = clock();
			}
		}
		else
		{
			hoverOverPlayButton_Main_Menu = false;
		}
		if (_mouse->getX() > _width / 2 - (textureWidth / 2) && _mouse->getX() < _width / 2 + (textureWidth / 2) && _mouse->getY() > _height / 3 + textureHeight && _mouse->getY() < _height / 3 + textureHeight + (textureHeight))
		{
			hoverOverHighScores_Main_Menu = true;
			if (_mouse->getMouseState(GLFW_MOUSE_BUTTON_1) == true)
			{
				std::cout << "HighScores Button Pressed\n";
				hoverOverPlayButton_Main_Menu = false;
				hoverOverExitButton_Main_Menu = false;
				hoverOverExitButton_Pause_Menu = false;
				hoverOverWaveStartButton_Game = false;
				hoverOverResumeButton_Pause_Menu = false;
				hoverOverHighScores_Main_Menu = false;
				state = HIGHSCORES;
			}
		}
		else
		{
			hoverOverHighScores_Main_Menu = false;
		}
		if (_mouse->getX() > _width / 2 - (textureWidth / 2) && _mouse->getX() < _width / 2 + (textureWidth / 2) && _mouse->getY() > 2 * _height / 3 - (textureHeight / 2) && _mouse->getY() < 2 * _height / 3 + (textureHeight / 2))
		{
			hoverOverExitButton_Main_Menu = true;
			if (_mouse->getMouseState(GLFW_MOUSE_BUTTON_1) == true)
			{
				std::cout << "Exit Button Pressed\n";
				hoverOverPlayButton_Main_Menu = false;
				hoverOverExitButton_Main_Menu = false;
				hoverOverExitButton_Pause_Menu = false;
				hoverOverWaveStartButton_Game = false;
				hoverOverResumeButton_Pause_Menu = false;
				hoverOverHighScores_Main_Menu = false;
				exit(0);
			}
		}
		else
		{
			hoverOverExitButton_Main_Menu = false;
		}

		if (_mouse->getX() > 0 && _mouse->getX() < /*testBlock->getSize()*/ 32 * 2 && _mouse->getY() > 0 && _mouse->getY() <  /*testBlock->getSize()*/ 32 * 2 && _mouse->getMouseState(GLFW_MOUSE_BUTTON_1) == true)
		{
			state = OPTIONS;
		}
	}
	else if (state == GAME)
	{		
		if (_keyboard->getKeyState(GLFW_KEY_ESCAPE))
		{
			state = PAUSE_MENU;
			pauseMenuTime = clock();
			std::cout << "Open Pause Menu\n";
		}

		if(_keyboard->getKeyState(GLFW_KEY_W))
		{
			_player->moveUp();
			_player->setTexture(textures->getPlayerBackTexture());
			_player->setDirection(1);
		}
		if(_keyboard->getKeyState(GLFW_KEY_A))
		{
			_player->moveLeft();
			_player->setTexture(textures->getPlayerLeftTexture());
			_player->setDirection(0);
		}
		if(_keyboard->getKeyState(GLFW_KEY_S))
		{
			_player->moveDown();
			_player->setTexture(textures->getPlayerFrontTexture());
			_player->setDirection(3);
		}
		if(_keyboard->getKeyState(GLFW_KEY_D))
		{
			_player->moveRight();
			_player->setTexture(textures->getPlayerRightTexture());
			_player->setDirection(2);
		}

		if(_player->getDirection() == 0)
		{
			Vector2 mouse = newVector2(_mouse->getX(),_mouse->getY());
			Vector2 p1 = newVector2(0,0);
			Vector2 p2 = newVector2(0,_height);
			Vector2 p3 = newVector2(_player->getX(),_player->getY());

			if(PointInTriangle(mouse,p1,p2,p3) && _mouse->getMouseState(GLFW_MOUSE_BUTTON_1))
			{
				_player->shoot(_mouse->getX(),_mouse->getY(),textures->getSettings());
				//PlaySound(TEXT("res/audio/M1 Garand Single-SoundBible.com-1941178963.wav"), NULL, SND_FILENAME);
			}
		}else if(_player->getDirection() == 1)
		{
			Vector2 mouse = newVector2(_mouse->getX(),_mouse->getY());
			Vector2 p1 = newVector2(0,0);
			Vector2 p2 = newVector2(_width,0);
			Vector2 p3 = newVector2(_player->getX(),_player->getY());
			if(PointInTriangle(mouse,p1,p2,p3) && _mouse->getMouseState(GLFW_MOUSE_BUTTON_1))
			{
				_player->shoot(_mouse->getX(),_mouse->getY(),textures->getSettings());
			}
		}else if(_player->getDirection() == 2)
		{
			Vector2 mouse = newVector2(_mouse->getX(),_mouse->getY());
			Vector2 p1 = newVector2(_width,0);
			Vector2 p2 = newVector2(_width,_height);
			Vector2 p3 = newVector2(_player->getX(),_player->getY());
			if(PointInTriangle(mouse,p1,p2,p3) && _mouse->getMouseState(GLFW_MOUSE_BUTTON_1))
			{
				_player->shoot(_mouse->getX(),_mouse->getY(),textures->getSettings());
			}
		}else if(_player->getDirection() == 3)
		{
			Vector2 mouse = newVector2(_mouse->getX(),_mouse->getY());
			Vector2 p1 = newVector2(0,_height);
			Vector2 p2 = newVector2(_width,_height);
			Vector2 p3 = newVector2(_player->getX(),_player->getY());
			if(PointInTriangle(mouse,p1,p2,p3) && _mouse->getMouseState(GLFW_MOUSE_BUTTON_1))
			{
				_player->shoot(_mouse->getX(),_mouse->getY(),textures->getSettings());
			}
		}
		_player->updateBullets(_width,_height);
		if(_player->getCanFire() == false)
		{
			_player->reload();
		}

		if(itemCounter >= 300)
		{
			ammo->push_back(new Ammo(newVector2(rand() % _width,rand() % _height),rand() % 20 + 1,textures->getAmmoTexture()));
			itemCounter = 0;
		}else
		{
			itemCounter++;
		}

		if(armorCounter >= 900)
		{
			armor->push_back(new Armor(rand() % _width, rand() % _height,textures->getArmorTexture(),rand() % 50 + 1));
			armorCounter = 0;
		}else
		{
			armorCounter++;
		}
		if(enemyCounter >= 60)
		{
			int x = rand() % _width;
			int y = rand() & _height;
			int r = rand() % 20;

			if(r < 5)
			{
				y = 0;
			}else if(r > 5 && r <= 10)
			{
				x = 0;
			}else if(r > 10)
			{
				x = _width;
			}else
			{
				y = _height;
			}
			int ra = rand() % 100;
			if(score < 200 || ra < 50)
			{
				int n = rand() % 100;
				if(n < 35)
				{
					enemies->push_back(new Enemy(newVector2(x,y),textures->getEnemy1Texture(),32,3,1,1,newVector2(_player->getX(),_player->getY()),sqrt(pow(_player->getX()-x,2.0)+pow(_player->getY() - y,2.0))));
				}else if(n >= 35 && n < 48)
				{
					enemies->push_back(new Enemy(newVector2(x,y),textures->getEnemy2Texture(),32,4,3,6,newVector2(_player->getX(),_player->getY()),sqrt(pow(_player->getX()-x,2.0)+pow(_player->getY() - y,2.0))));
				}else if(n >= 48 && n < 54)
				{
					enemies->push_back(new Enemy(newVector2(x,y),textures->getEnemy3Texture(),32,4,8,7,newVector2(_player->getX(),_player->getY()),sqrt(pow(_player->getX()-x,2.0)+pow(_player->getY() - y,2.0))));
				}else if(n >= 54 && n< 63)
				{
					enemies->push_back(new Enemy(newVector2(x,y),textures->getEnemy4Texture(),32,5,12,8,newVector2(_player->getX(),_player->getY()),sqrt(pow(_player->getX()-x,2.0)+pow(_player->getY() - y,2.0))));
				}else if(n >= 63 && n < 71)
				{
					enemies->push_back(new Enemy(newVector2(x,y),textures->getEnemy5Texture(),32,6,13,9,newVector2(_player->getX(),_player->getY()),sqrt(pow(_player->getX()-x,2.0)+pow(_player->getY() - y,2.0))));
				}else if(n >= 71 && n < 82)
				{
					enemies->push_back(new Enemy(newVector2(x,y),textures->getEnemy6Texture(),32,7,15,10,newVector2(_player->getX(),_player->getY()),sqrt(pow(_player->getX()-x,2.0)+pow(_player->getY() - y,2.0))));
				}else if(n >= 82 && n < 90)
				{
					enemies->push_back(new Enemy(newVector2(x,y),textures->getEnemy7Texture(),32,7,16,15,newVector2(_player->getX(),_player->getY()),sqrt(pow(_player->getX()-x,2.0)+pow(_player->getY() - y,2.0))));
				}else if(n >= 90 && n < 95)
				{
					enemies->push_back(new Enemy(newVector2(x,y),textures->getEnemy8Texture(),32,7,17,20,newVector2(_player->getX(),_player->getY()),sqrt(pow(_player->getX()-x,2.0)+pow(_player->getY() - y,2.0))));
				}else
				{
					enemies->push_back(new Enemy(newVector2(x,y),textures->getEnemy1Texture(),128,2,100,25,newVector2(_player->getX(),_player->getY()),sqrt(pow(_player->getX()-x,2.0)+pow(_player->getY() - y,2.0))));
				}
			}else
			{
				int n = rand() % 100;
				if(n < 35)
				{
					enemies->push_back(new Enemy(newVector2(x,y),textures->getEnemy1Texture(),64,3,20,10,newVector2(_player->getX(),_player->getY()),sqrt(pow(_player->getX()-x,2.0)+pow(_player->getY() - y,2.0))));
				}else if(n >= 35 && n < 48)
				{
					enemies->push_back(new Enemy(newVector2(x,y),textures->getEnemy2Texture(),64,4,50,60,newVector2(_player->getX(),_player->getY()),sqrt(pow(_player->getX()-x,2.0)+pow(_player->getY() - y,2.0))));
				}else if(n >= 48 && n < 54)
				{
					enemies->push_back(new Enemy(newVector2(x,y),textures->getEnemy3Texture(),64,4,80,70,newVector2(_player->getX(),_player->getY()),sqrt(pow(_player->getX()-x,2.0)+pow(_player->getY() - y,2.0))));
				}else if(n >= 54 && n< 63)
				{
					enemies->push_back(new Enemy(newVector2(x,y),textures->getEnemy4Texture(),64,5,120,80,newVector2(_player->getX(),_player->getY()),sqrt(pow(_player->getX()-x,2.0)+pow(_player->getY() - y,2.0))));
				}else if(n >= 63 && n < 71)
				{
					enemies->push_back(new Enemy(newVector2(x,y),textures->getEnemy5Texture(),64,6,130,90,newVector2(_player->getX(),_player->getY()),sqrt(pow(_player->getX()-x,2.0)+pow(_player->getY() - y,2.0))));
				}else if(n >= 71 && n < 82)
				{
					enemies->push_back(new Enemy(newVector2(x,y),textures->getEnemy6Texture(),64,7,150,100,newVector2(_player->getX(),_player->getY()),sqrt(pow(_player->getX()-x,2.0)+pow(_player->getY() - y,2.0))));
				}else if(n >= 82 && n < 90)
				{
					enemies->push_back(new Enemy(newVector2(x,y),textures->getEnemy7Texture(),64,7,160,150,newVector2(_player->getX(),_player->getY()),sqrt(pow(_player->getX()-x,2.0)+pow(_player->getY() - y,2.0))));
				}else if(n >= 90 && n < 95)
				{
					enemies->push_back(new Enemy(newVector2(x,y),textures->getEnemy8Texture(),64,7,170,200,newVector2(_player->getX(),_player->getY()),sqrt(pow(_player->getX()-x,2.0)+pow(_player->getY() - y,2.0))));
				}else
				{
					enemies->push_back(new Enemy(newVector2(x,y),textures->getEnemy1Texture(),256,5,1000,250,newVector2(_player->getX(),_player->getY()),sqrt(pow(_player->getX()-x,2.0)+pow(_player->getY() - y,2.0))));
				}
			}
			enemyCounter = 0;
		}else
		{
			enemyCounter++;
		}

		if(_player->getX() < 0)
		{
			_player->setX(0);
		}
		if(_player->getX() + _player->getSize() > _width)
		{
			_player->setX(_width - _player->getSize());
		}
		if(_player->getY() < 0)
		{
			_player->setY(0);
		}
		if(_player->getY() + _player->getSize() > _height)
		{
			_player->setY(_height - _player->getSize());
		}

		for(std::vector<Armor*>::iterator i = armor->begin(); i != armor->end(); i++)
		{
			int ix = (*i)->getX();
			int iy = (*i)->getY();
			int isize = 32;
			int x = _player->getX();
			int y = _player->getY();
			int size = _player->getSize();

			if(x > ix && x < ix + isize && y > iy && y < iy + isize)
			{
				_player->setHealth(_player->getHealth() + (*i)->getHealth());
				(*i)->setDestroyed(true);
			}else if(x + size > ix && x + size < ix + isize && y > iy && y < iy + isize)
			{
				_player->setHealth(_player->getHealth() + (*i)->getHealth());
				(*i)->setDestroyed(true);
			}else if(x > ix && x < ix + isize && y + size > iy && y + size < iy + isize)
			{
				_player->setHealth(_player->getHealth() + (*i)->getHealth());
				(*i)->setDestroyed(true);
			}else if(x + size > ix && x + size < ix + isize && y + size > iy && y + size < iy + isize)
			{
				_player->setHealth(_player->getHealth() + (*i)->getHealth());
				(*i)->setDestroyed(true);
			}
		}

		for(std::vector<Armor*>::iterator i = armor->begin(); i != armor->end(); i++)
		{
			if((*i)->getDestroyed() == true)
			{
				armor->erase(i);
				break;
			}
		}
		float minDistance = 2000000;
		for(std::vector<Enemy*>::iterator i = enemies->begin(); i != enemies->end();i++)
		{
			Enemy* e = (*i);
			if(e->getDistance() < minDistance)
			{
				minDistance = e->getDistance();
			}
			if(e->getPosition().x < 0 || e->getPosition().x > _width || e->getPosition().y < 0 || e->getPosition().y > _height)
			{
				e->setDead(true);
			}
			(*i)->move(newVector2(_player->getX(),_player->getY()));
			for(std::vector<Bullet*>::iterator b = _player->getBullets()->begin(); b != _player->getBullets()->end();b++)
			{
				Bullet* c = (*b);
				int ix = e->getPosition().x;
				int iy = e->getPosition().y;
				int isize = e->getSize();
				int x = c->getPosition().x;
				int y = c->getPosition().y;
				int size = 32;

				if(x > ix && x < ix + isize && y > iy && y < iy + isize)
				{
					e->setHealth(e->getHealth() - _player->getSelectedWeapon()->getDamage());
					c->setDelete(true);
				}else if(x + size > ix && x + size < ix + isize && y > iy && y < iy + isize)
				{
					e->setHealth(e->getHealth() - _player->getSelectedWeapon()->getDamage());
					c->setDelete(true);
				}else if(x > ix && x < ix + isize && y + size > iy && y + size < iy + isize)
				{
					e->setHealth(e->getHealth() - _player->getSelectedWeapon()->getDamage());
					c->setDelete(true);
				}else if(x + size > ix && x + size < ix + isize && y + size > iy && y + size < iy + isize)
				{
					e->setHealth(e->getHealth() - _player->getSelectedWeapon()->getDamage());
					c->setDelete(true);
				}
			}
			if(e->getHealth() <= 0)
			{
				e->setDead(true);
				if(rand() % 100 < 5){
					ammo->push_back(new Ammo(e->getPosition(),rand() % 10 + 1,textures->getAmmoTexture()));
				}
				int r = rand() % 1000;
				if(r > 450 && r < 550)
				{
					_player->getSelectedWeapon()->setDamage(_player->getSelectedWeapon()->getDamage() + 1);
				}
			}

			int ix = e->getPosition().x;
			int iy = e->getPosition().y;
			int isize = e->getSize();
			int x = _player->getX();
			int y = _player->getY();
			int size = _player->getSize();

			if(x > ix && x < ix + isize && y > iy && y < iy + isize)
			{
				e->setDead(true);
				e->setHurtPlayer(true);
			}else if(x + size > ix && x + size < ix + isize && y > iy && y < iy + isize)
			{
				e->setDead(true);
				e->setHurtPlayer(true);
			}else if(x > ix && x < ix + isize && y + size > iy && y + size < iy + isize)
			{
				e->setDead(true);
				e->setHurtPlayer(true);
			}else if(x + size > ix && x + size < ix + isize && y + size > iy && y + size < iy + isize)
			{
				e->setDead(true);
				e->setHurtPlayer(true);
			}
			if((*i)->getHurtPlayer())
			{
				_player->setHealth(_player->getHealth() - (*i)->getDamage());
				if(_player->getHealth() <= 0 && !gameOver)
				{
					time = clock() - start;
					gameOver = true;
				}
			}
			if((*i)->Dead())
			{
				enemies->erase(i);
				break;
			}
		}
		if(minDistance != 2000000)
		{
			lengthSums += minDistance;
			lengthCounter++;
		}
		for(std::vector<Ammo*>::iterator i = ammo->begin(); i != ammo->end();i++)
		{
			Ammo* item = (*i);
			int ix = item->getX();
			int iy = item->getY();
			int isize = 32;
			int x = _player->getX();
			int y = _player->getY();
			int size = _player->getSize();

			if(x > ix && x < ix + isize && y > iy && y < iy + isize)
			{
				_player->getSelectedWeapon()->setAmmo(_player->getSelectedWeapon()->getAmmo() + item->getAmmo());
				ammo->erase(i);
				break;
			}else if(x + size > ix && x + size < ix + isize && y > iy && y < iy + isize)
			{
				_player->getSelectedWeapon()->setAmmo(_player->getSelectedWeapon()->getAmmo() + item->getAmmo());
				ammo->erase(i);
				break;
			}else if(x > ix && x < ix + isize && y + size > iy && y + size < iy + isize)
			{
				_player->getSelectedWeapon()->setAmmo(_player->getSelectedWeapon()->getAmmo() + item->getAmmo());
				ammo->erase(i);
				break;
			}else if(x + size > ix && x + size < ix + isize && y + size > iy && y + size < iy + isize)
			{
				_player->getSelectedWeapon()->setAmmo(_player->getSelectedWeapon()->getAmmo() + item->getAmmo());
				ammo->erase(i);
				break;
			}

		}
		if(!gameOver)
		{
			time = (clock() - start) - elapsedPauseMenuTime;
			score = time/1000;
		}else
		{
			if(!addedScore)
			{
				std::ifstream file("highScores.txt");
				if(file.is_open())
				{
					std::string line;
					std::cout << "Current Scores: <\n";
					while(std::getline(file,line))
					{
						highScores->push_back(line);
						std::cout << line << std::endl;
					}
					std::cout << "> End of Current Scores\n";
					file.close();
				}
				int counter = 0;
				int index = 0;
				for(std::vector<std::string>::iterator i = highScores->begin(); i != highScores->end();i++)
				{
					std::string s = (*i);
					std::string::size_type sz;
					int num = stoi(s,&sz);
					if(score >= num)
					{
						index = counter;
						break;
					}
					counter++;
					index = counter;
				}
				std::cout << "Score added at index = " << index << std::endl;
				std::ofstream theFile;
				theFile.open("highScores.txt");
				int c = 0;
				for(std::vector<std::string>::iterator i = highScores->begin(); i != highScores->end();i++)
				{
					if(c == index)
					{
						theFile << score << std::endl;
					}
					theFile << (*i) << std::endl;
					c++;
				}
				theFile.close();

				std::ofstream a;
				a.open("length.txt");
				a << lengthSums / lengthCounter;
				a.close();
				addedScore = true;
			}
		}

		if(lengthSums > 0 && lengthCounter > 0 && lengthSums != 2000000)
		{
			averageLength = lengthSums / lengthCounter;
		}
	}
	else if (state == OPTIONS)
	{
		if (_mouse->getX() > 0 && _mouse->getX() < 32 * 6)
		{
			if (_mouse->getY() > /*testBlock->getSize()*/ 32 * 2 && _mouse->getY() < /*testBlock->getSize()*/ 32 * 4 && _mouse->getMouseState(GLFW_MOUSE_BUTTON_1))
			{
				std::ofstream file;
				file.open("settings.txt");
				file << "1366\n";
				file << "768\n";
				file.close();
				state = RESTART;
			}
			else if (_mouse->getY() > /*testBlock->getSize()*/ 32 * 4 && _mouse->getY() < /*testBlock->getSize()*/ 32 * 6 && _mouse->getMouseState(GLFW_MOUSE_BUTTON_1))
			{
				std::ofstream file;
				file.open("settings.txt");
				file << "1920\n";
				file << "1080\n";
				file.close();
				state = RESTART;
			}
		}
	}
	else if (state == PAUSE_MENU)
	{
		if (_mouse->getX() > 0 && _mouse->getX() < /*testBlock->getSize()*/ 32 * 2 && _mouse->getY() > 0 && _mouse->getY() < /*testBlock->getSize()*/ 32 * 2 && _mouse->getMouseState(GLFW_MOUSE_BUTTON_1) == true)
		{
			state = OPTIONS;
		}
		if (_mouse->getX() > _width / 2 - (textureWidth / 2) && _mouse->getX() < _width / 2 + (textureWidth / 2) && _mouse->getY() > _height / 3 - (textureHeight / 2) && _mouse->getY() < _height / 3 + (textureHeight / 2))
		{
			hoverOverResumeButton_Pause_Menu = true;
			if (_mouse->getMouseState(GLFW_MOUSE_BUTTON_1) == true)
			{
				hoverOverPlayButton_Main_Menu = false;
				hoverOverExitButton_Main_Menu = false;
				hoverOverExitButton_Pause_Menu = false;
				hoverOverWaveStartButton_Game = false;
				hoverOverResumeButton_Pause_Menu = false;
				state = GAME;
				std::cout << "Resume Clicked\n";
				endpauseMenuTime = clock();
				elapsedPauseMenuTime = endpauseMenuTime - pauseMenuTime;
			}
		}
		else
		{
			hoverOverResumeButton_Pause_Menu = false;
		}
		if (_mouse->getX() > _width / 2 - (textureWidth / 2) && _mouse->getX() < _width / 2 + (textureWidth / 2) && _mouse->getY() > 2 * _height / 3 - (textureHeight / 2) && _mouse->getY() < 2 * _height / 3 + (textureHeight / 2))
		{
			hoverOverExitButton_Pause_Menu = true;
			if (_mouse->getMouseState(GLFW_MOUSE_BUTTON_1) == true)
			{
				hoverOverPlayButton_Main_Menu = false;
				hoverOverExitButton_Main_Menu = false;
				hoverOverExitButton_Pause_Menu = false;
				hoverOverWaveStartButton_Game = false;
				hoverOverResumeButton_Pause_Menu = false;
				state = MAIN_MENU;
				std::cout << "Exit Clicked\n";
			}
		}
		else
		{
			hoverOverExitButton_Pause_Menu = false;
		}
		//if (_keyboard->getKeyState(GLFW_KEY_ESCAPE))
		//{
		//	std::this_thread::sleep_for(std::chrono::milliseconds(500));
		//	std::cout << "Open Game\n";
		//	state = GAME;
		//}
	}else if(state == HIGHSCORES)
	{
		if (_keyboard->getKeyState(GLFW_KEY_ESCAPE))
		{
			state = MAIN_MENU;
		}
	}

	if (_keyboard->getKeyState(GLFW_KEY_1))
	{
		exit(0);
	}
}

void Game::render()
{
	if (state == MAIN_MENU)
	{
		GFX::drawRect(_width, _height, 0, 0, textures->getBackgroundTestTexture()->getTexture());
		GFX::drawRect(textureWidth, textureHeight, _width / 2 - (textureWidth / 2), _height / 3 - (textureHeight / 2), textures->getPlayFirstTexture()->getTexture());
		if (hoverOverPlayButton_Main_Menu)
		{
			GFX::drawRect(textureWidth, textureHeight, _width / 2 - (textureWidth / 2), _height / 3 - (textureHeight / 2), textures->getPlaySecondTexture()->getTexture());
		}
		GFX::drawRect(textureWidth, textureHeight, _width / 2 - (textureWidth / 2), 2 * _height / 3 - (textureHeight / 2), textures->getExitFirstTexture()->getTexture());
		if (hoverOverExitButton_Main_Menu)
		{
			GFX::drawRect(textureWidth, textureHeight, _width / 2 - (textureWidth / 2), 2 * _height / 3 - (textureHeight / 2), textures->getExitSecondTexture()->getTexture());
		}
		GFX::drawRect(textureWidth, textureHeight, _width / 2 - (textureWidth / 2), _height / 3 + textureHeight, textures->getHighScoreFirst()->getTexture());
		if (hoverOverHighScores_Main_Menu)
		{
			GFX::drawRect(textureWidth, textureHeight, _width / 2 - (textureWidth / 2), _height / 3 + textureHeight, textures->getHighScoreSecond()->getTexture());
		}
		GFX::drawRect(/*testBlock->getSize()*/ 32 * 2, /*testBlock->getSize()*/ 32 * 2, 0.0f, 0.0f, textures->getSettings()->getTexture());
	}
	else if (state == GAME)
	{
		for(std::vector<Block*>::iterator i = world->begin(); i != world->end(); i++)
		{
			(*i)->draw();
		}
		_player->draw();
		if(_player->getDirection() == 0)
		{
			GFX::drawLine(_player->getX() + (_player->getSize()/2),_player->getY() + (_player->getSize()/2),0,0,textures->getLaserTexture()->getTexture());
			GFX::drawLine(_player->getX() + (_player->getSize()/2),_player->getY() + (_player->getSize()/2),0,_height,textures->getLaserTexture()->getTexture());
		}else if(_player->getDirection() == 1)
		{
			GFX::drawLine(_player->getX() + (_player->getSize()/2),_player->getY() + (_player->getSize()/2),0,0,textures->getLaserTexture()->getTexture());
			GFX::drawLine(_player->getX() + (_player->getSize()/2),_player->getY() + (_player->getSize()/2),_width,0,textures->getLaserTexture()->getTexture());
		}else if(_player->getDirection() == 2)
		{
			GFX::drawLine(_player->getX() + (_player->getSize()/2),_player->getY() + (_player->getSize()/2),_width,_height,textures->getLaserTexture()->getTexture());
			GFX::drawLine(_player->getX() + (_player->getSize()/2),_player->getY() + (_player->getSize()/2),_width,0,textures->getLaserTexture()->getTexture());
		}else if(_player->getDirection() == 3)
		{
			GFX::drawLine(_player->getX() + (_player->getSize()/2),_player->getY() + (_player->getSize()/2),0,_height,textures->getLaserTexture()->getTexture());
			GFX::drawLine(_player->getX() + (_player->getSize()/2),_player->getY() + (_player->getSize()/2),_width,_height,textures->getLaserTexture()->getTexture());
		}
		_player->drawBullets();
		for(std::vector<Ammo*>::iterator i = ammo->begin(); i != ammo->end();i++)
		{
			(*i)->draw();
		}
		for(std::vector<Armor*>::iterator i = armor->begin(); i != armor->end(); i++)
		{
			(*i)->draw();
		}
		for(std::vector<Enemy*>::iterator i = enemies->begin(); i != enemies->end();i++)
		{
			(*i)->draw();
		}
		char h[32];
		sprintf(h, "%d",_player->getHealth());
		char a[32];
		sprintf(a,"%d",_player->getSelectedWeapon()->getAmmo());
		char d[32];
		sprintf(d,"%d",_player->getSelectedWeapon()->getDamage());
		char g[32];
		std::ostringstream oss;
		oss << "Score: " << score;
		std::string str = oss.str();

		char q[32];
		sprintf(q, "%d", (int)averageLength);

		char health[64] = "Health: ";
		char ab[64] = "Ammo: ";
		char da[64] = "Damage: ";
		char abb[64] = "Average Length: ";
		std::ostringstream oss1;
		oss1 << "GAME OVER Score: " << score;
		std::string str1 = oss1.str();

		strcat(health,h);
		strcat(ab,a);
		strcat(da,d);
		strcat(abb,q);

		GFX::drawString(32,_height-32,health,1.0f,1.0f,1.0f);
		GFX::drawString(256,_height-32,ab,1.0f,1.0f,1.0f);
		GFX::drawString(512,_height-32,da,1.0f,1.0f,1.0f);
		GFX::drawString(640,_height-32,str.c_str(),1.0f,1.0f,1.0f);
		GFX::drawString(900,_height-32,abb,1.0f,1.0f,1.0f);

		if(gameOver)
		{
			GFX::drawString(_width/2 - 128, _height/2 - 12,str1.c_str(),1.0f,1.0f,1.0f);
		}
		
	}
	else if (state == OPTIONS)
	{
		GFX::drawString(0, /*testBlock->getSize()*/ 32 * 4, "1366 X 768", 1.0f, 1.0f, 1.0f);
		GFX::drawString(0, /*testBlock->getSize()*/ 32 * 6, "1920 X 1080", 1.0f, 1.0f, 1.0f);
	}
	else if (state == PAUSE_MENU)
	{
		int textureWidth = 256;
		int textureHeight = 64;
		if (_width == 1920)
		{
			textureWidth = 512;
		}
		if (_height == 1080)
		{
			textureHeight = 128;
		}
		GFX::drawRect(textureWidth, textureHeight, _width / 2 - (textureWidth / 2), _height / 3 - (textureHeight / 2), textures->getResumeFirstTexture()->getTexture());
		if (hoverOverResumeButton_Pause_Menu)
		{
			GFX::drawRect(textureWidth, textureHeight, _width / 2 - (textureWidth / 2), _height / 3 - (textureHeight / 2), textures->getResumeSecondTexture()->getTexture());
		}
		GFX::drawRect(textureWidth, textureHeight, _width / 2 - (textureWidth / 2), 2 * _height / 3 - (textureHeight / 2), textures->getExitFirstTexture()->getTexture());
		if (hoverOverExitButton_Pause_Menu)
		{
			GFX::drawRect(textureWidth, textureHeight, _width / 2 - (textureWidth / 2), 2 * _height / 3 - (textureHeight / 2), textures->getExitSecondTexture()->getTexture());
		}
		GFX::drawRect(/*testBlock->getSize()*/ 32 * 2, /*testBlock->getSize()*/ 32 * 2, 0.0f, 0.0f, textures->getSettings()->getTexture());
	}else if(state == RESTART)
	{
		GFX::drawString(_width / 2 - 64, _height / 2, "You must restart to take effect! Press 1 to exit", 1.0f, 1.0f, 1.0f);
		if(_keyboard->getKeyState(GLFW_KEY_1))
		{
			exit(0);
		}
	}else if(state == HIGHSCORES)
	{
		std::ifstream file("highScores.txt");
		int counter = 0;
		if(file.is_open())
		{
			std::string line;
			while(std::getline(file,line))
			{
				highScores->push_back(line);
				GFX::drawString(_width/2 - 64,(counter + 1) * 32,line.c_str(),1.0f,1.0f,1.0f);
				counter++;
			}
			file.close();
		}
	}
	
}

