#pragma once
#include "GameResources.h"
#include "Map.h"

class Character 
	: public GameResources
{
public:
	Character(void);
	~Character(void);
	virtual void draw() = 0;
	void movDown();
	void movUp();
	void movRight();
	void movLeft();
	float getX() const;
	float getY() const;
	void setX(float x);
	void setY(float y);
	void setIsActive(bool isActive);
	bool getIsActive() const;
	float getMovSpeed() const;
	void setMovSpeed(float movSpeed);
	void setAnimStep(int step);
	void setAnimDir(Direction dir);
	Direction getAnimDir() const;
	void animate();
	void setAnimDeathState(bool state);
	bool getAnimDeathState() const;
	bool detectCollision(Direction direction, Map* map);
	virtual void die() = 0;
protected:
	float x;
	float y;
	float movSpeed;
	bool isActive;
	int animStep;
	Direction animDir;
	bool anim_death;
	bool ghostCollision;
};

