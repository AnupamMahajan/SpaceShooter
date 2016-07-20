#include"pauseMenu.h"

void pauseMenu::Init()
{
	    fnt = new hgeFont("fonts/font1.fnt");

		pauseGUI=new hgeGUI();
		pauseGUI->AddCtrl(new hgeGUIMenuItem(1,fnt,NULL,400,200,0.0f,"Resume"));
		pauseGUI->AddCtrl(new hgeGUIMenuItem(2,fnt,NULL,400,250,0.2f,"Restart"));
		pauseGUI->AddCtrl(new hgeGUIMenuItem(3,fnt,NULL,400,300,0.2f,"Main Menu"));
		pauseGUI->SetNavMode(HGEGUI_UPDOWN | HGEGUI_CYCLED);
		pauseGUI->SetFocus(1);
}

void pauseMenu::Destroy()
{
	delete fnt;
	delete pauseGUI;
}

void pauseMenu::Render()
{
	pauseGUI->Render();
}

bool pauseMenu::Update(float delta)
{
		    int id;
			static int lastid=0;
			
			id=pauseGUI->Update(delta);
			if(id == -1)
			{
				switch(lastid)
				{
				case 1:  pauseGUI->Reset();
						 pauseGUI->Enter();
						 return false;
					     break;

				case 2:  GameManager::instance().reset();
					     SceneManager::instance().changeScene(SceneManager::MainGameplay);
					     break;

				case 3:  SceneManager::instance().changeScene(SceneManager::Menu);
						 GameManager::instance().reset();
						
				   		break; 
				}

			}
			else if(id) { lastid=id; pauseGUI->Leave(); }
			return true;

}