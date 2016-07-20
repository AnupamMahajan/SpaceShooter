#include "SceneManager.h"

SceneManager& SceneManager::instance()
{
	static SceneManager manager;
	return manager;
}

void SceneManager::changeScene(GameScenes nextScene)
{

	      currentScene->Destroy();         //------- Deallocates the objects for previous scene 

		  switch(nextScene)                // ------ creates a new scene
		  {
			  case Menu    :	  currentScene = new menuScene(hge);
						          break;

			  case MainGameplay:  currentScene = new mainScene(hge);
								  break;

			  case GameOver :     currentScene = new gameOverScene(hge);
								  break;
		      
			  case Controls :     currentScene = new controlScene(hge);
								  break;

			  case Credits  :     currentScene = new creditScene(hge);
								  break;
		  }

    currentScene->Init();           //----- Allocates the new objects for the new scene
}

