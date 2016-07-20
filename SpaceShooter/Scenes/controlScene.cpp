#include"controlScene.h"


controlScene::controlScene(HGE* p_hge)
{
	hge=p_hge;
}

void controlScene::Init()
{
	fnt = new hgeFont("fonts/font1.fnt");
	s_FuelAid = new hgeSprite(TextureManager::instance().tFuelAid,0,0,30,30);
}

bool controlScene::Update()
{
	if (hge->Input_KeyDown(HGEK_ESCAPE))
		SceneManager::instance().changeScene(SceneManager::Menu);
	
	return false;
}

void controlScene::Destroy()
{
	delete fnt;
	delete s_FuelAid;
}

void controlScene::Render()
{
	fnt->printf(50,50,HGETEXT_LEFT,"Controls - ");
	fnt->printf(50,100,HGETEXT_LEFT,"W, A, S, D : Movements \nSpaceBar : Fire\nESC : Pause");
	fnt->printf(50,250,HGETEXT_LEFT,"Instructions - ");
	fnt->printf(50,300,HGETEXT_LEFT,"Kill Maximum enemies and gain Health Ponts");
	fnt->printf(50,330,HGETEXT_LEFT,"Keep Collecting the Fuel to retain the Fuel Level");
	s_FuelAid->Render(600,330);
}