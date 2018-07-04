#ifndef _TEXTURES_H
#define _TEXTURES_H
#include <iostream>
#include "Texture.h"
class Textures
{
public:
	Textures();
	~Textures();
	Texture* getAirTexture();
	Texture* getDirt2Texture();
	Texture* getDirtTexture();
	Texture* getLaserTexture();
	Texture* getBackgroundTestTexture();
	Texture* getExitFirstTexture();
	Texture* getExitSecondTexture();
	Texture* getPauseFirstTexture();
	Texture* getPauseSecondTexture();
	Texture* getPlayFirstTexture();
	Texture* getPlaySecondTexture();
	Texture* getPlayTexture();
	Texture* getPlay1Texture();
	Texture* getResumeFirstTexture();
	Texture* getResumeSecondTexture();
	Texture* getEnemy1Texture();
	Texture* getEnemy2Texture();
	Texture* getEnemy3Texture();
	Texture* getEnemy4Texture();
	Texture* getEnemy5Texture();
	Texture* getEnemy6Texture();
	Texture* getEnemy7Texture();
	Texture* getEnemy8Texture();
	Texture* getSettings();
	Texture* getPlayerFrontTexture();
	Texture* getPlayerBackTexture();
	Texture* getPlayerLeftTexture();
	Texture* getPlayerRightTexture();
	Texture* getBulletTexture();
	Texture* getAmmoTexture();
	Texture* getHighScoreFirst();
	Texture* getHighScoreSecond();
	Texture* getCursorTexture();
	Texture* getArmorTexture();
private:
	Texture* air;
	Texture* dirt2;
	Texture* dirt;
	Texture* laser;
	Texture* exitFirst;
	Texture* exitSecond;
	Texture* pauseFirst;
	Texture* pauseSecond;
	Texture* playFirst;
	Texture* playSecond;
	Texture* play;
	Texture* play1;
	Texture* resumeFirst;
	Texture* resumeSecond;
	Texture* enemy1;
	Texture* enemy2;
	Texture* enemy3;
	Texture* enemy4;
	Texture* enemy5;
	Texture* enemy6;
	Texture* enemy7;
	Texture* enemy8;
	Texture* backgroundTestTexture;
	Texture* settings;
	Texture* back;
	Texture* front;
	Texture* left;
	Texture* right;
	Texture* bullet;
	Texture* ammo;
	Texture* highScores_first;
	Texture* highScores_second;
	Texture* cursor;
	Texture* armor;
};

#endif