#ifndef SCENE_H
#define SCENE_H
#pragma once

class scene                    //Abstract class for all the scenes in game
{
    public :

	virtual void Init()=0;         // This function will initialize the resources for the scene
	virtual void Destroy()=0;      // Deallocate the resources for the current scene
	virtual bool Update()=0;       // upadte function for the current scene
	virtual void Render()=0;       // render to targets for the current scene

};

#endif