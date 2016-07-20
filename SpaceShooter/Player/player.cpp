#include "player.h"

HGE* player::hge = 0;
 
player::player(hgeVector position, hgeVector velocity) : Position(position), Velocity(velocity)
{
    hge = hgeCreate(HGE_VERSION); //Get interface to hge
	
	health = 100;
	fuel= 100;
    Texture = hge->Texture_Load("images/player.png");
	Sprite = new hgeSprite(Texture,0,0,70,95);  
	timer=0;
}

player::~player()
{
    hge->Texture_Free(Texture);
    delete Sprite;
 
    hge->Release();
}

bool player::Update(float delta)
{
    Velocity.x *= PLAYER_FRICTION;
    Velocity.y *= PLAYER_FRICTION;
    
    Position.x += Velocity.x;

	if(Position.x<50) Position.x=50;           //Clamping the values
	if(Position.x>700) Position.x=700;

	if(Position.y<50) Position.y=50;
	if(Position.y>500) Position.y=500;
	
	timer+=delta;
	if(timer>=2)       // deplets fuel after every two seconds
	{
     timer=0;
	 fuel-=5;
	}

    Position.y += Velocity.y;

	if(hge->Input_GetKeyState(HGEK_A) || hge->Input_GetKeyState(HGEK_LEFT)) Velocity.x -= PLAYER_ACCELERATION; //Input controls 
	if(hge->Input_GetKeyState(HGEK_D) || hge->Input_GetKeyState(HGEK_RIGHT)) Velocity.x += PLAYER_ACCELERATION;
	if(hge->Input_GetKeyState(HGEK_W) || hge->Input_GetKeyState(HGEK_UP)) Velocity.y -= PLAYER_ACCELERATION;
	if(hge->Input_GetKeyState(HGEK_S) || hge->Input_GetKeyState(HGEK_DOWN)) Velocity.y += PLAYER_ACCELERATION;

	if(hge->Input_KeyDown(HGEK_SPACE)) //------------------------Shoots Bullets
	{
				bullet* Bullet = new bullet(Position + hgeVector(15,10), hgeVector(15,-9), TextureManager::instance().tBullet, 10);
				Bullets.push_back(Bullet);
	}

    Sprite->GetBoundingBox(Position.x, Position.y, &BoundingBox);

	if(fuel>100) fuel=100;
	if(health>100) health=100;

    return false;
}

void player::Render()
{
    Sprite->Render(Position.x, Position.y);
}

void player::Reset()
{
	health=100;
	fuel=100;
}



