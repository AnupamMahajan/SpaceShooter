/*--------------------------------------------------------------
Name : Spaceshooter.exe
Description : A top down space shooter game , goal of the game is to kill maximum enemies,
              while collecting fuel in order to reatin the depleting fuel level

Owner Details : Anupam Mahajan 
                anupam.mahajan@dsksupinfogame.com
				+91 8806005205
				www.anupammahajan.weebly.com

---------------------------------------------------------------*/

#include <hge.h>
#include <hgesprite.h>
#include <hgevector.h> 
#include<hgegui.h>
#include<hgefont.h>

#include <iostream>
#include <list>

#include "Player/bullet.h"
#include "Player/player.h"
#include "Enemies/enemy.h"
#include "GUI/menuitem.h"

#include "Managers/GameManager.h"
#include "Managers/TextureManager.h"

#include "Managers/SceneManager.h"
#include "Scenes/menuScene.h"
#include "Scenes/gameOverScene.h"

bool isPaused;

HGE* hge;

bool FrameFunc()
{  

	       return SceneManager::instance().currentScene->Update(); //-------------- update function of the current scen

}
 
bool RenderFunc()
{
    hge->Gfx_BeginScene();
    hge->Gfx_Clear(0);

	SceneManager::instance().currentScene->Render();
	
    hge->Gfx_EndScene();
    return false;
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    hge = hgeCreate(HGE_VERSION);
    hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
    hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
    hge->System_SetState(HGE_WINDOWED, true);
    hge->System_SetState(HGE_USESOUND, false);
    hge->System_SetState(HGE_FPS, HGEFPS_VSYNC);
    hge->System_SetState(HGE_TITLE, "Spaceshooter");
	hge->System_SetState(HGE_SCREENWIDTH, 800);
	hge->System_SetState(HGE_SCREENHEIGHT, 600);
	hge->System_SetState(HGE_SCREENBPP, 32);
 
    if(hge->System_Initiate())
    { 
		isPaused=false;
		SceneManager::instance().hge=hge;
		SceneManager::instance().currentScene = new menuScene(hge);
		SceneManager::instance().currentScene->Init();

		TextureManager::instance().LoadTextures(hge);
		hge->System_Start();
		
		SceneManager::instance().currentScene->Destroy();   //----- Exiting the game
		delete SceneManager::instance().currentScene;
	    TextureManager::instance().UnloadTextures(hge);

    }

    else
    {
      MessageBox(NULL, hge->System_GetErrorMessage(), "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
    }
 
    hge->System_Shutdown();
    hge->Release();
 
    return 0;
}


