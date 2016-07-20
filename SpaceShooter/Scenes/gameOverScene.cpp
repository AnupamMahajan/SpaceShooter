#include "gameOverScene.h"

void gameOverScene::Init()
{
	    fnt=new hgeFont("fonts/font1.fnt");
		fnt->SetScale(2);
}

bool gameOverScene::Update()
{
	
		if (hge->Input_GetKeyState(HGEK_ESCAPE)||(hge->Input_GetKeyState(HGEK_ENTER)))
		{
			GameManager::instance().reset();
			SceneManager::instance().changeScene(SceneManager::Menu);
		}
		
		return false;
}

void gameOverScene::Render()
{
	fnt->printf(200,200,HGETEXT_LEFT,"Game Over\n Your Score : %d",GameManager::instance().totalScore);
}