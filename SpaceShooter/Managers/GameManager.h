#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include<hge.h>
#include"..\Player\player.h"
#include"NotificationManager.h"

//#include"SceneManager.h"
//#include"gameOverScene.h" 

class GameManager            //------------- Singleton class which stores major game data and a reference to the active player
{
  public : 
	  static GameManager& instance();

	  int totalKills;
	  int totalScore;
	  int difficultyFactor;     //----- it will decide the difficulty level of the game

	  void healthReward(int rewardAmount);

	  void reset();

	  player* Player;  //Game manager will keep a refernce to the main player , so it can be easily accessed in any class.

  private :
	 GameManager();  
};

#endif