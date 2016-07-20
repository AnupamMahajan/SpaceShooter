#ifndef NOTIFICATIONMANAGER_H
#define NOTIFICATIONMANAGER_H
#pragma once

#include<string>
#include<hgefont.h>
#include<hge.h>

class NotificationManager             //---------- this Manager can be accessed from anywhere to display a message on the screen
{
   private :
	   hgeFont* fnt;
	   float timer;
	   bool isRendering;

	   NotificationManager()
	   {
		   fnt=new hgeFont("fonts/font1.fnt");
		   fnt->SetScale(0.8f);
		   timer=0;
		   isRendering=false;
	   }


	public : 
	  static NotificationManager& instance()
	  {
		  static NotificationManager manager;
		  return manager;
	  }

	  std::string message;

	  void reset()
	  {
		  message="";
	  }

	  void showMessage( std::string p_message)
	  { 
		  timer=0;
		  isRendering=true;
		  message= p_message;
	  }

	  void Update(float delta)
	  {
	        timer+=delta;
			if(timer>=2)
			{
				timer=0;
				isRendering=false;
			}	
	  }

	  void Render()
	  {
		  if(isRendering)
			  fnt->printf(50,300,HGETEXT_LEFT,message.c_str());
	  }
};

#endif