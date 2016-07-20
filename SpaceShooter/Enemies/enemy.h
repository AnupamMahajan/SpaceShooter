#ifndef ENEMY_H
#define ENEMY_H
#pragma once
/*----------------------------------
  Class for the enemies , It contains the base class as well as 
  the derived classes for all three types of enemies
-------------------------------------*/

#include <hge.h>
#include <hgevector.h>
#include <hgeanim.h>
#include<list>

#include "..\Managers\TextureManager.h"
#include "..\Managers\GameManager.h"
#include "enemyBullet.h"
 
#define ENEMY_FRICTION 0.95f
#define BULLET_DAMAGE 10
#define SHOOTING_FREQUENCY 1
 
class enemy                                 //-------- base class for the different enemies
{
  protected:
    static HGE*     hge;
    hgeVector       Position;
    hgeVector       Velocity;
    hgeSprite*      Sprite;
    hgeRect         BoundingBox;
	short           Health;
	int             BulletDamage;
	int				CollisionDamage;

	std::list<enemyBullet*> Bullets;    //--------List of bullets shot by the enemy

	float timer;
 
public:
    enemy();
    ~enemy();
	
	int enemyType;

    virtual bool Update(float delta);     //---- derived classes will store the individual enemy behaviour in update
	virtual void ShootBullets();


    void Render();
	void UpdateBullets(float delta);
 
    short       GetHealth() { return Health; };
    void        SetHealth(short health) { Health = health; };
 
    hgeRect     GetBoundingBox() { return BoundingBox; };
    hgeVector   GetPosition() { return Position; };
	int GetBulletDamage(){ return BulletDamage;};
	int GetCollisionDamage(){ return CollisionDamage;};

};

class simpleEnemy : public enemy                    //---- this enemy moves in straight path
{
	public : 
	simpleEnemy(hgeVector Position, HTEXTURE Texture);
	bool Update(float delta);
};

class spiralEnemy : public enemy                 //---------- This enemy has a zigzag path and heavy bullets
{
    public :
	spiralEnemy(hgeVector Position,HTEXTURE Texture);
	bool Update(float delta);
};
 

class fastEnemy : public enemy                 //-----------This enemy has acceleration also fires multiple bullets in different directions
{
    public :
	fastEnemy(hgeVector Position,HTEXTURE Texture);
	bool Update(float delta);
	void ShootBullets();
};

#endif