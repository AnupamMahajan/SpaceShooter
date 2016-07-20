#ifndef FUELAID_H
#define FUELAID_H
#pragma once

#include <hge.h>
#include <hgevector.h>
#include <hgeanim.h>
#include<list>

#include "..\Managers\GameManager.h"
#include "..\Managers\TextureManager.h"

#define FUEL_AID_AMOUNT 20

class fuelAid                         //------------ by collecting fuel aids the player can retain the fuel
{
	private :
		 static HGE*     hge;
		 hgeVector       Position;
		 hgeVector       Velocity;
		 hgeSprite*      Sprite;
		 hgeRect         BoundingBox;

	public :

		fuelAid(int xPosition)
		{
			Position = hgeVector(xPosition,-30);
			Sprite  = new  hgeSprite(TextureManager::instance().tFuelAid,0,0,30,30);
			Velocity = hgeVector(3.0f,3.0f);
		}

		void Update()
		{
			Position.y+=Velocity.y;
			Sprite->GetBoundingBox(Position.x, Position.y, &BoundingBox);
		}

		void Render()
		{
			Sprite->Render(Position.x,Position.y);
		}

		hgeRect GetBoundingBox()
		{
			return BoundingBox;
		}

		hgeVector GetPosition()
		{
			return Position;
		}

};
#endif