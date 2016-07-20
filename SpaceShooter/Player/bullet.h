#ifndef BULLET_H
#define BULLET_H
#pragma once
 
#include <hge.h>
#include <hgesprite.h>
#include <hgerect.h>
#include <hgevector.h>
 
#define BULLET_FRICTION 0.99f          //class for the bullets of the player
#define BULLET_DAMAGE 10
 
class bullet
{
private:
    static HGE*     hge;
    hgeVector       Position;
    hgeVector       Velocity;
    hgeSprite*      Sprite;
    hgeRect         BoundingBox;
    float           Speed;
    short           Damage;

	public:
    bullet(hgeVector Position, hgeVector Velocity, HTEXTURE &Texture, short Damage);
    ~bullet();
 
    void Update();
    void Render();
 
    void        SetDamage(short damage) { Damage = damage; };
    short       GetDamage() { return Damage; };
    hgeRect     GetBoundingBox() { return BoundingBox; };
    hgeVector   GetPosition() { return Position; };
};
 
#endif