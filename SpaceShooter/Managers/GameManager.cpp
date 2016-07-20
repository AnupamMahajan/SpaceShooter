#include "GameManager.h"
#include <string>

 GameManager& GameManager::instance()
{
	static GameManager manager;
	return manager;
}

 GameManager::GameManager()
 {
	 difficultyFactor=1;
 }

 void GameManager::healthReward(int rewardAmount)
 {
	 Player->addHealth(rewardAmount);
	 NotificationManager::instance().showMessage(" Health Points!!++");
 }

 void GameManager::reset()   //since its static its duration will be throught the game , hence needs to reset
 {
	 Player=NULL;
	 totalScore=0;
 }