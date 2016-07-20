#ifndef MAINSCENE_H
#define MAINSCENE_H
#pragma once


#include "scene.h"                          //--------------- Main class to implement the game screen

#include <hge.h>
#include <hgesprite.h>
#include <hgevector.h> 
#include<hgegui.h>
#include<hgefont.h>
#include<hgeguictrls.h>

#include <iostream>
#include <list>

#include "..\Player\bullet.h"
#include "..\Player\player.h"
#include "..\Enemies\enemy.h"
#include "..\Player\fuelAid.h"
#include "..\Scenes\pauseMenu.h"

#include "..\Managers\GameManager.h"
#include "..\Managers\NotificationManager.h"
#include "..\Managers\TextureManager.h"
#include "..\Managers\SceneManager.h"

#define BG_ScrollSpeed 2.0f
#define SCREEN_WIDTH 800
#define SCREEN_HIEGHT 600

class mainScene : public scene                   
{
private :

	std::list<bullet*> Bullets;    //---- list of active bullets in the scene
	std::list<enemy*> Enemies;     //---- list of active enemies in the scene
	std::list<fuelAid*> FuelAids;

	bool isPaused;
	pauseMenu *PauseMenu;         //--- Pause Menu

	hgeFont	*fnt;
	hgeGUISlider *healthBar;
	hgeGUISlider *fuelBar;

	struct explosion
	{
		hgeAnimation*   Animation;
		hgeVector       Position;
	};

	void CreateExplosion(hgeVector Position);

	std::list<explosion> Explosions;

	player*	Player;
	HGE* hge;

	hgeSprite*  g_sBackground;
	hgeVector   g_vBGPosition;


	enum enemyTypes
	{
		SimpleEnemy,
		SpiralEnemy,
		FastEnemy
	};

	enemy* createEnemies(enemyTypes e);

	float enemyTimer;

	void EnemyGenerator();
	void GameOverConditionCheck();
	

public :

	mainScene(HGE* hge);

	void Init();
	void Destroy();
	bool Update();
	void Render();

};
#endif