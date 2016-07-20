#include"menuScene.h"

void menuScene::Init()
{
			 fnt=new hgeFont("fonts/font1.fnt");
		    snd=hge->Effect_Load("sounds/menu.wav");
		    fnt=new hgeFont("fonts/font1.fnt");

		    // Create and initialize the GUI
		    gui=new hgeGUI();

			gui->AddCtrl(new hgeGUIMenuItem(1,fnt,snd,400,200,0.0f,"Play"));
			gui->AddCtrl(new hgeGUIMenuItem(2,fnt,snd,400,250,0.2f,"Controls"));
			gui->AddCtrl(new hgeGUIMenuItem(3,fnt,snd,400,300,0.3f,"Credits"));      
			gui->AddCtrl(new hgeGUIMenuItem(4,fnt,snd,400,350,0.4f,"Exit"));

			gui->SetNavMode(HGEGUI_UPDOWN | HGEGUI_CYCLED);

			gui->SetFocus(1);
			gui->Enter();
}

void menuScene::Destroy()
{
	       delete gui;
		   delete fnt;
	       hge->Effect_Free(snd);
}

bool menuScene::Update()
{
	        float delta = hge->Timer_GetDelta();
			int id;
			static int lastid=0;

			id=gui->Update(delta);
			if(id == -1)
			{
				switch(lastid)
				{
				case 1:  SceneManager::instance().changeScene(SceneManager::MainGameplay);   //--- starts the game
					     break;

				case 2:  SceneManager::instance().changeScene(SceneManager::Controls);
						  break;

				case 3:  SceneManager::instance().changeScene(SceneManager::Credits);
					     break;

				case 4 : return true;
						break;
				}
			}
			else if(id) { lastid=id; gui->Leave(); }
			return false;

}

