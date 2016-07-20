#include "enemy.h"

HGE* enemy::hge = 0;
 
enemy::enemy()
{
    hge = hgeCreate(HGE_VERSION);
	timer = 0;
}

//------------------------------------------Initializing all the enemies 

simpleEnemy::simpleEnemy(hgeVector position, HTEXTURE Texture) : enemy()
{
	Position = position;
	Health = 10 * GameManager::instance().difficultyFactor; //Health of the player , depends on the difficulty settings

	Velocity = hgeVector(3.0f,hge->Random_Int(1,5));
    Sprite  = new  hgeSprite(Texture,0,0,80,80);

	CollisionDamage = 20;
	BulletDamage = 10 * GameManager::instance().difficultyFactor; // damage caused by this enemies bullets
	enemyType=1;

}

spiralEnemy::spiralEnemy(hgeVector position, HTEXTURE Texture) : enemy()
{
	
	Position = position;
	Health = 20 * GameManager::instance().difficultyFactor; // dies in two hits by default
	Velocity = hgeVector(3.0f,1.0f);
    Sprite  = new  hgeSprite(Texture,0,0,80,100);

	CollisionDamage = 30;
	BulletDamage = 20 * GameManager::instance().difficultyFactor;
	enemyType=2;
}


fastEnemy::fastEnemy(hgeVector position, HTEXTURE Texture) : enemy()
{
	Position = position;
	Health = 30 * GameManager::instance().difficultyFactor ; //dies in three hits by default
	Velocity = hgeVector(0,0);
    Sprite  = new  hgeSprite(Texture,0,0,120,120);

	CollisionDamage = 50;
	BulletDamage = 20 * GameManager::instance().difficultyFactor;
	enemyType=3;
}

//--------------------------------- Updating the bullet list , each enemy will mantain the list for its own bullets

void enemy::UpdateBullets(float delta)
{
	hgeRect playerBoundingBox = GameManager::instance().Player->GetBoundingBox();

	for(auto i = Bullets.begin(); i != Bullets.end();)
	{
		
		if((*i)->GetBoundingBox().Intersect(&playerBoundingBox))
		{
				GameManager::instance().Player->takeDamage(BULLET_DAMAGE);
				delete (*i);
				i = Bullets.erase(i);
		}

		else
		{
			(*i)->Update();
			i++;
		}

	}

	timer+=delta;

	if(timer>=SHOOTING_FREQUENCY)         // shoots bullets 
	{
		timer=0;
		ShootBullets();
	}

}

//---------------------------------------------------------------- Update functions containing three diffrent behaviours 
bool enemy::Update(float delta)
{
    Sprite->GetBoundingBox(Position.x, Position.y, &BoundingBox);

    return false;
}

bool simpleEnemy::Update(float delta)
{
	 Position.y += Velocity.y;
	 Sprite->GetBoundingBox(Position.x, Position.y, &BoundingBox);
	 UpdateBullets(delta);
	 return false;
}

bool spiralEnemy::Update(float delta)
{
	 Position.y += Velocity.y;
	 Position.x +=Velocity.x;

	 if(Position.x > 600 || Position.x< 20)
		 Velocity.x*=-1;

	 Sprite->GetBoundingBox(Position.x, Position.y, &BoundingBox);
	 UpdateBullets(delta);

	 return false;
}

bool fastEnemy::Update(float delta)
{
	Position.y += Velocity.y;
	Velocity.y+=0.1f;
	Sprite->GetBoundingBox(Position.x, Position.y, &BoundingBox);
	UpdateBullets(delta);
	return false;
}


// -------------------------------------------Base Functions for destructor and rendering 
void enemy::Render()
{
    Sprite->Render(Position.x, Position.y);

	for(auto i = Bullets.begin(); i != Bullets.end(); i++)
	{
			(*i)->Render();
	}

}

//------------------------------------------ Shooting Bullets
void enemy::ShootBullets()
{
	enemyBullet* Bullet = new enemyBullet(Position,TextureManager::instance().tEnemyBullet,BULLET_DAMAGE,0);
    Bullets.push_back(Bullet);
}

void fastEnemy::ShootBullets()    //Overrides the base defination
{
	    //Shoots three bullets in three directions
	    
	    hgeVector bulletPos = Position + hgeVector(20,50); //adjusting offset according to sprite

		enemyBullet* Bullet1 = new enemyBullet(bulletPos,TextureManager::instance().tEnemyBullet,BULLET_DAMAGE,-1);
		Bullets.push_back(Bullet1);

		enemyBullet* Bullet2 = new enemyBullet(bulletPos,TextureManager::instance().tEnemyBullet,BULLET_DAMAGE,0);
		Bullets.push_back(Bullet2);

		enemyBullet* Bullet3 = new enemyBullet(bulletPos,TextureManager::instance().tEnemyBullet,BULLET_DAMAGE,1);
		Bullets.push_back(Bullet3);

}


enemy::~enemy()
{
    delete Sprite;
    hge->Release();

	for(auto i = Bullets.begin(); i != Bullets.end(); /**/)
		{
			delete (*i);
			i = Bullets.erase(i);
		}
}




