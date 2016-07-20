# include "mainScene.h"

mainScene::mainScene(HGE* p_hge)
{
	isPaused = false;

	fnt=NULL;

	Player=NULL;
	
	hge=p_hge;

	g_sBackground=NULL;

	healthBar = new hgeGUISlider(1,120,540,250,15,TextureManager::instance().tHealthBar,250,15,250,15,false);
	healthBar->SetMode(0,100,0);

	fuelBar = new hgeGUISlider(1,120,560,250,15,TextureManager::instance().tFuelBar,250,15,250,15,false);
	fuelBar->SetMode(0,100,0);
}

enemy* mainScene::createEnemies(enemyTypes e)
{
	  enemy* Enemy;
			switch(e)
			{
				case SimpleEnemy : Enemy = new simpleEnemy( hgeVector(hge->Random_Int(50,700),-50), TextureManager::instance().tSimpleEnemy);
					 break;

				 case SpiralEnemy :  Enemy = new spiralEnemy( hgeVector(hge->Random_Int(50,600),-50),TextureManager::instance().tSpiralEnemy);
					 break;

				 case FastEnemy : Enemy = new fastEnemy( hgeVector(hge->Random_Int(50,600),-120), TextureManager::instance().tFastEnemy);
					 break;
			}

		return Enemy;
}


void mainScene::CreateExplosion(hgeVector Position)
{
		explosion exp;
		exp.Animation = new hgeAnimation( TextureManager::instance().tExplosion,5,10,0,0,118,118);
		exp.Animation->SetHotSpot(59,59);
		exp.Animation->Play();
		exp.Position = Position;
		Explosions.push_back(exp);
}


void mainScene::EnemyGenerator()
{
	        float EnemyGenratorThreshhold;
			if(GameManager::instance().totalScore<200) EnemyGenratorThreshhold = 2.0f; // ----- This will increase the number of enemies as player scores more , making the progression challenging
			else if(GameManager::instance().totalScore<600) EnemyGenratorThreshhold=1.0f;
			else EnemyGenratorThreshhold=0.5f;

			if(enemyTimer>=EnemyGenratorThreshhold)
			{
				enemyTimer=0;
				if(Enemies.size() < 7)                                    
				{ 

					int probablity = hge->Random_Int(1,100);

					if(probablity <=60)
					{
						enemy* Enemy = createEnemies(SimpleEnemy);  
						Enemies.push_back(Enemy);
					}
					else if(probablity < 85)
					{
						enemy* Enemy = createEnemies(SpiralEnemy);
						Enemies.push_back(Enemy);
					}
					else
					{
						enemy* Enemy = createEnemies(FastEnemy);
						 Enemies.push_back(Enemy);
					}
				}
			}

}


void mainScene::GameOverConditionCheck()
{
	if(Player->GetHealth()<=0 || Player->GetFuel()<=0)            
				SceneManager::instance().changeScene(SceneManager::GameOver);
}

//------------------------------------------------Public functions
void mainScene::Init()
{
		fnt=new hgeFont("fonts/font1.fnt");
		PauseMenu = new pauseMenu();
		PauseMenu->Init();

		g_sBackground = new hgeSprite(TextureManager::instance().tBackground,0,0,1166,677);

		hgeVector startPos(SCREEN_WIDTH/2,SCREEN_HIEGHT-50);

		Player	= new player(startPos, hgeVector(0,0));
		GameManager::instance().Player=Player;

		enemyTimer=0;
		NotificationManager::instance().reset();
}

void mainScene::Destroy()
{
		
		for(auto i = Enemies.begin(); i != Enemies.end();)
		{
			delete (*i);
			i = Enemies.erase(i);
		}
 
		for(auto i = Bullets.begin(); i != Bullets.end();)
		{
			delete (*i);
			i = Bullets.erase(i);
		}

		for(auto i = FuelAids.begin(); i != FuelAids.end();)
		{
			delete (*i);
			i = FuelAids.erase(i);
		}

		for(auto i = Explosions.begin(); i != Explosions.end();)
		{
			delete (*i).Animation;
			i = Explosions.erase(i);
		}
       
		PauseMenu->Destroy();

		delete PauseMenu;
        delete g_sBackground;
		delete Player;
		delete fnt;
}


bool mainScene::Update()                 //-----------------------------Main game loop
{

	if (hge->Input_KeyDown(HGEK_ESCAPE))
		isPaused=!isPaused;
	
	if(!isPaused)
	{
			float delta = hge->Timer_GetDelta();
			int timeElapsed = hge->Timer_GetTime();

			NotificationManager::instance().Update(delta);
			enemyTimer+=delta;

			g_vBGPosition.y += BG_ScrollSpeed;

			if(g_vBGPosition.y> SCREEN_HIEGHT + 77) 
				g_vBGPosition.y=0;

			Player->Update(delta);
			Bullets=Player->Bullets;

			EnemyGenerator();                  //------------ Generates enemies

			if(timeElapsed % 8 == 0)           //------------- spawns a fuel aid after every 8 seconds
			{
				if(FuelAids.size()<1)
				{
				  int xPos = hge->Random_Int(20,700);
				  fuelAid* Aid = new fuelAid(xPos);
				  FuelAids.push_back(Aid);
				}
			}

			//------- bullets exiting 
			for(auto i = Bullets.begin(); i != Bullets.end();)
			{
				(*i)->Update();
		
				if((*i)->GetPosition().x > SCREEN_WIDTH || (*i)->GetPosition().x < 0 || (*i)->GetPosition().y < 0 || (*i)->GetPosition().y > SCREEN_HIEGHT) 
					i = Bullets.erase(i);
				else 
					i++;
			}

			//--------------enemies exiting
			for(auto i = Enemies.begin(); i != Enemies.end(); )
			{
				if((*i)->GetPosition().y > SCREEN_HIEGHT)
				{
					delete (*i);
					i = Enemies.erase(i);
				}
				else
				{
					(*i)->Update(delta);
					i++;
				}
			}

			//----------------- FueAids exiting
			for(auto i = FuelAids.begin(); i != FuelAids.end(); )
			{
				if((*i)->GetPosition().y > SCREEN_HIEGHT)
				{
					delete (*i);
					i = FuelAids.erase(i);
				}
				else
				{
					(*i)->Update();
					i++;
				}

				if(Player->GetFuel()<30)
					NotificationManager::instance().showMessage("Warning , Low Fuel !!"); //----- Displays a warning , when fuel is low
			}

			//Collision Bullet vs Enemy
				if(!Bullets.empty() && !Enemies.empty())
				{
					for(auto i = Bullets.begin(); i != Bullets.end(); )
					{
						
						bool bHit = false;
 
						for(auto x = Enemies.begin(); x != Enemies.end(); x++)
						{
							if((*x)->GetBoundingBox().Intersect(&(*i)->GetBoundingBox()))
							{
								(*x)->SetHealth((*x)->GetHealth() - (*i)->GetDamage());
						
								CreateExplosion((*i)->GetPosition());
								delete (*i);

								i    = Bullets.erase(i);
								bHit = true;
 
								break;
							}
						}
						if(!bHit) i++;
					}
				}

				Player->Bullets=Bullets;

				//----------------------- collision between enemy and player
				for(auto i = Enemies.begin(); i != Enemies.end();)
				{
					if((*i)->GetBoundingBox().Intersect(&Player->GetBoundingBox()))
					{
						CreateExplosion((*i)->GetPosition());
						Player->takeDamage((*i)->GetCollisionDamage());
						delete (*i);
						i = Enemies.erase(i);
					}
					else i++;
				}

				//-------------------------- collision between player and fuelAids
				for(auto i= FuelAids.begin();i!=FuelAids.end();)
				{
					if((*i)->GetBoundingBox().Intersect(&Player->GetBoundingBox()))
					{
						GameManager::instance().totalScore+=10;
						Player->addFuel(20);
						NotificationManager::instance().showMessage("Fuel ++ !!");
						delete (*i);
						i = FuelAids.erase(i);
 
					}
					else
							i++;
				}

				//-------checking for enemies health
				for(auto i = Enemies.begin(); i != Enemies.end();)
				{
					if((*i)->GetHealth() <= 0)
					{
						int enemyType = (*i)->enemyType;
						switch(enemyType)
						{

							case 1 : GameManager::instance().healthReward(5); //------------------Reward System
								GameManager::instance().totalScore+=20;
								break;

							case 2: GameManager::instance().healthReward(10);
								GameManager::instance().totalScore+=40;
								break;

							case 3 : GameManager::instance().healthReward(20);
								GameManager::instance().totalScore+=60;
								break;

						}


						delete (*i);
						i = Enemies.erase(i);
					}
					else i++;
				}

				//----------------explosion
				for(auto i = Explosions.begin(); i != Explosions.end(); )
				{
					if((*i).Animation->GetFrame() == 4)
					{
						delete (*i).Animation;
						i = Explosions.erase(i);
					}
					else
					{
						(*i).Animation->Update(delta);
						i++;
					}
				}
				healthBar->SetValue(Player->GetHealth());
				fuelBar->SetValue(Player->GetFuel());

				//--------------------------------
				GameOverConditionCheck();

    }

	else
	{
		    float delta = hge->Timer_GetDelta();
			isPaused=PauseMenu->Update(delta);
		    return false;
	}
		return false;
}

void mainScene::Render()
{  
	
	g_sBackground->Render(g_vBGPosition.x,g_vBGPosition.y);

	if(g_vBGPosition.y > 0)
		g_sBackground->Render(g_vBGPosition.x,g_vBGPosition.y-677);

	Player->Render();

	for(auto i = Bullets.begin(); i!= Bullets.end(); i++) //-----> Renders all the sprites from the list
	{
		(*i)->Render();
	}

	for(auto i = Enemies.begin(); i != Enemies.end(); i++)
	{
			(*i)->Render();
	}

	for(auto i = FuelAids.begin(); i != FuelAids.end(); i++)
	{
			(*i)->Render();
	}

	for(auto i = Explosions.begin(); i != Explosions.end(); i++)
	{
		(*i).Animation->Render((*i).Position.x, (*i).Position.y);
	}

	
	fnt->SetScale(0.8f);
	NotificationManager::instance().Render(); //------- to render messages
	
	fnt->printf(300,50,HGETEXT_LEFT,"Score : %d",GameManager::instance().totalScore); 
	fnt->printf(10, 540, HGETEXT_LEFT, "Health : %d",Player->GetHealth());
	fnt->printf(10, 560, HGETEXT_LEFT, "Fuel : %d",Player->GetFuel());

	healthBar->Render();
	fuelBar->Render();

	if(isPaused)
		PauseMenu->Render();

}