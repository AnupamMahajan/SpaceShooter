#ifndef GAMEOVERSCENE_H
#define GAMEOVERSCENE_H
#pragma once

#include<hge.h>
#include<hgefont.h>

#include"scene.h"
#include "menuScene.h"
#include"..\Managers\SceneManager.h"
#include"..\Managers\GameManager.h"

class gameOverScene : public scene    //-------end scene 
{
private :
      HGE* hge;
	  hgeFont *fnt;
public :

	gameOverScene(HGE* p_hge){hge=p_hge;};

	void Init();

	bool Update();

	void Destroy(){delete fnt;};

	void Render();

};

#endif