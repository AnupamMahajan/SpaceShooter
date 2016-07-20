#ifndef CREDITS_H
#define CREDITS_H
#pragma once

#include<hgefont.h>
#include<hge.h>
#include"..\Managers\SceneManager.h"

class creditScene : public scene
{
private : 
	hgeFont *fnt;
	HGE* hge;

public :

	creditScene(HGE* );

	void Init();
	bool Update();
	void Render();
	void Destroy();
};

#endif