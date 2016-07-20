#include<hge.h>
#include<hgefont.h>
#include<hgegui.h>
#include"..\GUI\menuitem.h"
#include"..\Managers\GameManager.h"
#include"..\Managers\SceneManager.h"

#ifndef PAUSEMENU_H
#define PAUSEMENU_H
#pragma once

class pauseMenu
{
	hgeFont *fnt;
	hgeGUI *pauseGUI;

public : 

	void Init();
	bool Update(float);
	void Render();
	void Destroy();
};

#endif