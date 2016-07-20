#include "bullet.h"

HGE* bullet::hge = 0;

bullet::bullet(hgeVector position, hgeVector velocity,HTEXTURE &Texture, short damage) : Position(position), Velocity(velocity), Damage(damage)
{
    hge = hgeCreate(HGE_VERSION);
 
    Sprite  = new hgeSprite(Texture,0,0,12,12);
    //Sprite->SetHotSpot(3,1.5);
	Damage = BULLET_DAMAGE;
    Speed   = 0.15f;
}

bullet::~bullet()
{
    delete Sprite;
 
    hge->Release();
}

void bullet::Update()
{
    Velocity.x *= BULLET_FRICTION;
    Velocity.y *= BULLET_FRICTION;
 
    Position.y += Velocity.y;
 
    Sprite->GetBoundingBox(Position.x, Position.y, &BoundingBox);
}

void bullet::Render()
{
    Sprite->Render(Position.x, Position.y);
}

