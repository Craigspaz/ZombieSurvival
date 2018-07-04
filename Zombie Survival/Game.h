#ifndef _GAME_H
#define _GAME_H
#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <ctime>
#include <sstream>
#include <string>
#include <GLFW\glfw3.h>
#include <stdio.h>
#include <cstdlib>
#include "Block.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "GFX.h"
#include "Textures.h"
#include "Player.h"
#include "Vector2.h"
#include "Item.h"
#include "Weapon.h"
#include "Enemy.h"
#include "Ammo.h"
#include "Armor.h"
class Game
{
public:
	Game(int width,int height);

	void update();
	void render();
	~Game();

private:
	int _width;
	int _height;
	Keyboard* _keyboard;
	Mouse* _mouse;
	Textures* textures;
	Player* _player;

	int textureWidth;
	int textureHeight;
	enum State {MAIN_MENU, GAME,OPTIONS, PAUSE_MENU,RESTART,HIGHSCORES};
	State state;

	bool hoverOverPlayButton_Main_Menu;
	bool hoverOverHighScores_Main_Menu;
	bool hoverOverExitButton_Main_Menu;
	bool hoverOverExitButton_Pause_Menu;
	bool hoverOverWaveStartButton_Game;
	bool hoverOverResumeButton_Pause_Menu;

	std::vector<Block*>* world;
	std::vector<Enemy*>* enemies;

	int enemyCounter;
	int maxEnemyCounter;
	std::vector<Ammo*>* ammo;
	std::vector<Armor*>* armor;
	int itemCounter;
	unsigned long start;
	unsigned long time;
	bool gameOver;
	unsigned long score;
	std::vector<std::string>* highScores;
	bool addedScore;
	unsigned long pauseMenuTime;
	unsigned long endpauseMenuTime;
	unsigned long elapsedPauseMenuTime;
	int armorCounter;
	float averageLength;
	int lengthCounter;
	float lengthSums;
};

#endif