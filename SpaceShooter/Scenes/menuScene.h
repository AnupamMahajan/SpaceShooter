#ifndef MENUSCENE_H
#define MENUSCENE_H
#pragma once

#include "scene.h"

#include <hge.h>
#include <hgesprite.h>
#include <hgevector.h> 
#include<hgegui.h>
#include<hgefont.h>

#include "..\GUI\menuitem.h"

#include "..\Managers\GameManager.h"

#include "..\Managers\SceneManager.h"
#include "..\Scenes\mainScene.h"


class menuScene : public scene                     //---------- Contains the GUI elements , the main menu scene
{
   private : 
	   hgeGUI	*gui;
       hgeFont	*fnt;
       HEFFECT	snd;

	   HGE* hge;

   public :

	   menuScene(HGE* p_hge){  hge = p_hge;};

	   void Init();

	   void Destroy();

	   bool Update();

	   void Render(){ gui->Render();};

};
#endif