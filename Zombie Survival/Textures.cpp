#include "Textures.h"


Textures::Textures()
{
	air = new Texture("res/air.png");
	dirt = new Texture("res/dirt.png");
	dirt2 = new Texture("res/Dirt (2).png");
	laser = new Texture("res/Laser.png");
	exitFirst = new Texture("res/Buttons/Exit_First.png");
	exitSecond = new Texture("res/Buttons/Exit_Second.png");
	pauseFirst = new Texture("res/Buttons/Pause.png");
	pauseSecond = new Texture("res/Buttons/Pause1.png");
	play = new Texture("res/Buttons/Play.png");
	playFirst = new Texture("res/Buttons/Play_First.png");
	playSecond = new Texture("res/Buttons/Play_Second.png");
	play1 = new Texture("res/Buttons/Play1.png");
	resumeFirst = new Texture("res/Buttons/Resume_First.png");
	resumeSecond = new Texture("res/Buttons/Resume_Second.png");
	enemy1 = new Texture("res/Enemy/Enemy1.png");
	enemy2 = new Texture("res/Enemy/Enemy2.png");
	enemy3 = new Texture("res/Enemy/Enemy3.png");
	enemy4 = new Texture("res/Enemy/Enemy4.png");
	enemy5 = new Texture("res/Enemy/Enemy5.png");
	enemy6 = new Texture("res/Enemy/Enemy6.png");
	enemy7 = new Texture("res/Enemy/Enemy7.png");
	enemy8 = new Texture("res/Enemy/Enemy8.png");
	backgroundTestTexture = new Texture("res/background.png");
	settings = new Texture("res/settings.png");
	back = new Texture("res/back.png");
	front = new Texture("res/front.png");
	left = new Texture("res/left.png");
	right = new Texture("res/right.png");
	bullet = new Texture("res/bullet.png");
	ammo = new Texture("res/ammo.png");
	highScores_first = new Texture("res/Buttons/HighScores_First.png");
	highScores_second = new Texture("res/Buttons/HighScores_Second.png");
	cursor = new Texture("res/cursor.png");
	armor = new Texture("res/armor.png");
}


Textures::~Textures()
{
	delete air;
	delete dirt2;
	delete dirt;
	delete laser;
	delete exitFirst;
	delete exitSecond;
	delete pauseFirst;
	delete pauseSecond;
	delete playFirst;
	delete playSecond;
	delete play;
	delete play1;
	delete resumeFirst;
	delete resumeSecond;
	delete enemy1;
	delete enemy2;
	delete enemy3;
	delete enemy4;
	delete enemy5;
	delete enemy6;
	delete enemy7;
	delete enemy8;
	delete backgroundTestTexture;
	delete settings;
	delete back;
	delete front;
	delete left;
	delete right;
	delete bullet;
	delete ammo;
	delete highScores_first;
	delete highScores_second;
	delete cursor;
	delete armor;
}

Texture* Textures::getBackgroundTestTexture()
{
	return backgroundTestTexture;
}

Texture* Textures::getAirTexture()
{
	return air;
}
Texture* Textures::getDirt2Texture()
{
	return dirt2;
}
Texture* Textures::getDirtTexture()
{
	return dirt;
}
Texture* Textures::getLaserTexture()
{
	return laser;
}
Texture* Textures::getExitFirstTexture()
{
	return exitFirst;
}
Texture* Textures::getExitSecondTexture()
{
	return exitSecond;
}
Texture* Textures::getPauseFirstTexture()
{
	return pauseFirst;
}
Texture* Textures::getPauseSecondTexture()
{
	return pauseSecond;
}
Texture* Textures::getPlayFirstTexture()
{
	return playFirst;
}
Texture* Textures::getPlaySecondTexture()
{
	return playSecond;
}
Texture* Textures::getPlayTexture()
{
	return play;
}
Texture* Textures::getPlay1Texture()
{
	return play1;
}
Texture* Textures::getResumeFirstTexture()
{
	return resumeFirst;
}
Texture* Textures::getResumeSecondTexture()
{
	return resumeSecond;
}
Texture* Textures::getEnemy1Texture()
{
	return enemy1;
}
Texture* Textures::getEnemy2Texture()
{
	return enemy2;
}
Texture* Textures::getEnemy3Texture()
{
	return enemy3;
}
Texture* Textures::getEnemy4Texture()
{
	return enemy4;
}
Texture* Textures::getEnemy5Texture()
{
	return enemy4;
}
Texture* Textures::getEnemy6Texture()
{
	return enemy6;
}
Texture* Textures::getEnemy7Texture()
{
	return enemy7;
}
Texture* Textures::getEnemy8Texture()
{
	return enemy8;
}
Texture* Textures::getSettings()
{
	return settings;
}
Texture* Textures::getPlayerFrontTexture()
{
	return front;
}
Texture* Textures::getPlayerBackTexture()
{
	return back;
}
Texture* Textures::getPlayerLeftTexture()
{
	return left;
}
Texture* Textures::getPlayerRightTexture()
{
	return right;
}
Texture* Textures::getBulletTexture()
{
	return bullet;
}
Texture* Textures::getAmmoTexture()
{
	return ammo;
}
Texture* Textures::getHighScoreFirst()
{
	return highScores_first;
}
Texture* Textures::getHighScoreSecond()
{
	return highScores_second;
}

Texture* Textures::getCursorTexture()
{
	return cursor;
}

Texture* Textures::getArmorTexture()
{
	return armor;
}