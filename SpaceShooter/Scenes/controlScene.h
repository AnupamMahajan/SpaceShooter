#ifndef CONTROLS_H
#define CONTROLS_H
#pragma once
/*----------------
This scene lists the controls and the instructions to play the game
*/

#include<hgefont.h>
#include<hge.h>
#include"..\Managers\SceneManager.h"

class controlScene : public scene
{
private : 
	hgeFont *fnt;
	HGE* hge;
	hgeSprite *s_FuelAid;

public :

	controlScene(HGE*);

	void Init();
	bool Update();
	void Render();
	void Destroy();
};


#endif