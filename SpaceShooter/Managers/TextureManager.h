#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include<hge.h>
#include<hgesprite.h>

class TextureManager                    //----- Singleton class so that each individual texture is loaded only once
{
  public : 
	  static TextureManager& instance();
	
	  HTEXTURE tEnemyBullet;
	  HTEXTURE tFuelAid;
	  HTEXTURE  tBackground;
	  HTEXTURE tBullet;

	  HTEXTURE tExplosion ;
	  HTEXTURE tHealthBar;
	  HTEXTURE tFuelBar;

	  HTEXTURE tSimpleEnemy ;
	  HTEXTURE tSpiralEnemy ;
	  HTEXTURE tFastEnemy ;

	  void LoadTextures(HGE *);
	  void UnloadTextures(HGE *);

  private :
	 TextureManager();  
	 HGE *hge;
};

#endif