#include "enemyBullet.h"

HGE* enemyBullet::hge = 0;

enemyBullet::enemyBullet(hgeVector position,HTEXTURE &texture,short damage,int p_slope)
{
	hge = hgeCreate(HGE_VERSION);
	Position = position + hgeVector(30,30);
	Velocity = hgeVector(8.0f,8.0f);
	Sprite  = new hgeSprite(texture,0,0,13,13);
    //Sprite->SetHotSpot(3,1.5);
	Damage = damage;  
	slope=p_slope;
}

enemyBullet::~enemyBullet()
{
    delete Sprite;
    hge->Release();
}

void enemyBullet::Update()
{
	switch(slope)
	{
	   case 0 : Position.y+=Velocity.y * 2;
					 break;

	   case 1 : Position.y+=Velocity.y;
				Position.x+=Velocity.x;
				break;

	   case -1 :Position.y+=Velocity.y;
				Position.x-=Velocity.x;
				break;
	}

	 Sprite->GetBoundingBox(Position.x, Position.y, &BoundingBox);
}

void enemyBullet::Render()
{
    Sprite->Render(Position.x, Position.y);
}