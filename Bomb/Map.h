#pragma once
#include "Field.h"
#include "GameResources.h"
#include "GameTypes.h"
#include <time.h> 
#include <stdlib.h>
#include <iostream> 

class Map : public GameResources
{
public:
	Map(int X, int Y);
	~Map(void);
	void showMap(void) const;
	void draw(ALLEGRO_COLOR roundMapColor);
	void generateNewMap(ItemType roundItem, int dens);
	Field* getField(int x, int y);
	void setDoorState(bool state);
	bool getDoorState() const;
	void makeFree();
	
	void openDoor();
	
	bool getisBurning() const;
	float updateAfterExplosion(int bombx, int bomby, int explosionRange);
	
private:
	void setItemPosition(ItemType itemType);
	void burningBrickAnimation(int x, int y);
	void explosionAnimation(int x, int y);
	void destroyBrick(int dirx, int diry);
	void damageDoor();
	int animStep;
	int animStep2;
	bool isBurning;

	int map_X, map_Y;
	int dens;
	bool doorState;
	Field **roundMap;
};

