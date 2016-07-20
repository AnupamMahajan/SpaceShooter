#include "creditsScene.h"

creditScene::creditScene(HGE* p_hge)
{
	hge=p_hge;
}


void creditScene::Init()
{
   fnt = new hgeFont("fonts/font1.fnt");
}


bool creditScene::Update()
{
	if (hge->Input_KeyDown(HGEK_ESCAPE))
		SceneManager::instance().changeScene(SceneManager::Menu);
	
	return false;
}

void creditScene::Render()
{
	fnt->printf(50,50,HGETEXT_LEFT,"Developer : ");
	fnt->printf(50,80,HGETEXT_LEFT,"Anupam Mahajan ");
	fnt->printf(50,110,HGETEXT_LEFT,"www.anupammahajan.weebly.com");
	fnt->printf(50,140,HGETEXT_LEFT,"anupammahajan92@gmail.com");
	fnt->printf(50,200,HGETEXT_LEFT,"Design : ");
	fnt->printf(50,230,HGETEXT_LEFT,"Ubisoft Pune");
    fnt->printf(50,300,HGETEXT_LEFT,"Art Assets : ");
	fnt->printf(50,330,HGETEXT_LEFT,"Opengameart.org");
}

void creditScene::Destroy()
{
   delete fnt;
}
