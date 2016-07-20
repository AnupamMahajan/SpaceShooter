#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H
#pragma once
 

#include<hge.h>
#include <hgevector.h>
#include <hgesprite.h>
#include <hgerect.h>

class enemyBullet
{
	private:
		static HGE*     hge;
		hgeVector       Position;
		hgeVector       Velocity;
		hgeSprite*      Sprite;
		hgeRect         BoundingBox;
		int             slope;
		short           Damage;

	public:
    enemyBullet(hgeVector Position,HTEXTURE &Texture,short Damage,int slope);
    ~enemyBullet();

	void Update();
    void Render();

	hgeRect     GetBoundingBox() { return BoundingBox; };
};

#endif