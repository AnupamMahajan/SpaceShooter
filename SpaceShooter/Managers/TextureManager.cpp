#include<hge.h>
#include "TextureManager.h"

 TextureManager& TextureManager::instance()
{
	static TextureManager manager;
	return manager;
}

 TextureManager::TextureManager()
 {
	 hge=NULL;
 }

 void TextureManager::LoadTextures(HGE *p_hge)
 {
	hge=p_hge;

	tEnemyBullet = hge->Texture_Load("images/enemyBullet.png");
	tFuelAid = hge->Texture_Load("images/fuelAid.png");

	tBackground = hge->Texture_Load("images/back1.jpg");	
	tBullet = hge->Texture_Load("images/bullet.png");

	tExplosion    = hge->Texture_Load("images/Explosion.png");
	tHealthBar    = hge->Texture_Load("images/healthBar.png");
	tFuelBar    = hge->Texture_Load("images/fuelBar.png");

	tSimpleEnemy = hge->Texture_Load("images/SimpleEnemy.png");
	tSpiralEnemy = hge->Texture_Load("images/SpiralEnemy.png");
	tFastEnemy = hge->Texture_Load("images/FastEnemy.png");

 }

 void TextureManager::UnloadTextures(HGE *p_hge)
 {
	  hge=p_hge;
	  hge->Texture_Free(tEnemyBullet);
	  hge->Texture_Free(tFuelAid);
	  hge->Texture_Free(tBackground);
	  hge->Texture_Free(tBullet);
	  hge->Texture_Free(tExplosion);
	  hge->Texture_Free(tHealthBar);
	  hge->Texture_Free(tFuelBar);
	  hge->Texture_Free(tSimpleEnemy);
	  hge->Texture_Free(tSpiralEnemy);
	  hge->Texture_Free(tFastEnemy);
 }