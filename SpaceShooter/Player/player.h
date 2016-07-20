#ifndef PLAYER_H
#define PLAYER_H
#pragma once

#include <hge.h>
#include <hgevector.h>
#include <hgeanim.h>
#include <list>
#include "bullet.h"
#include "..\Managers\TextureManager.h"

#define PLAYER_FRICTION 0.97f
#define PLAYER_ACCELERATION 0.2f
#define	FUEL_DEPLETION_RATE 0.04f	

class player
{
private:
	static HGE*		hge;
	hgeVector		Position;
	hgeVector		Velocity;
	HTEXTURE		Texture;
	hgeSprite*		Sprite;
	hgeRect			BoundingBox;

	int             health;
	int             fuel;
	float			timer;

public:
	player(hgeVector Position, hgeVector Velocity);
	~player();

	std::list<bullet*> Bullets;

	bool Update(float delta);
	void Render();

	void		ReverseVelocity() { Velocity = hgeVector(-Velocity.x,-Velocity.y); };

	void		SetVelocity(hgeVector velocity) { Velocity = velocity; };
	void		SetPosition(hgeVector position) { Position = position; };
	hgeRect		GetBoundingBox() { return BoundingBox; };
	hgeVector	GetPosition() { return Position; };
	int         GetHealth() {return health;};
	int         GetFuel(){return fuel;};

	void        addHealth(int amount){health+=amount;};

	void        takeDamage(int damageAmount) {health-=damageAmount;};

	void        addFuel(int fuelAmount) {fuel += fuelAmount;};

	void        Reset();
};

#endif