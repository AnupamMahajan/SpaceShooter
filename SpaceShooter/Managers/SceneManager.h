#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H
#pragma once

#include<hge.h>
#include"..\Scenes\mainScene.h"
#include"..\Scenes\menuScene.h"
#include"..\Scenes\gameOverScene.h"
#include"..\Scenes\controlScene.h"
#include"..\Scenes\creditsScene.h"

class SceneManager                           //----------- Singleton manager class to facilitate scene switching
{
	public : 
	  static SceneManager& instance();

	  enum GameScenes
	  {
		  Menu,
		  MainGameplay,
		  GameOver,
		  Controls,
		  Credits
	  };

	  HGE* hge;
	  scene *currentScene;        // Pointer to the current loaded scene 

	  void changeScene(GameScenes nextScene);    //------ Function called when switching between scenes

	  private :

		SceneManager()	{hge =NULL;};

};
#endif
