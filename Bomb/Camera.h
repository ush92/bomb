#pragma once
#include <allegro5/allegro.h>
#include "GameResources.h"
#include "GameTypes.h"
class Camera : GameResources
{
public:
	Camera(void);
	~Camera(void);
	void update(float x);
	float getMapScrollPx (void);
	void repair(); 
private:
	float cameraPosition;
	ALLEGRO_TRANSFORM instance;
	float mapScrollpx; 
};

