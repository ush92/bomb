#pragma once
#include "GameResources.h"

class Bomb 
	: GameResources
{
public:
	Bomb(void);
	~Bomb(void);
	bool getIsActive() const;
	void setIsActive(bool active);
	void setX(float x);
	void setY(float y);
	float getX() const;
	float getY() const;
	
	void draw(); 
	void animate();

	bool selfExplode(); 

	void putSound(bool detonator) const; 
	void boomSound()const;
	void errSound() const;
private:
	bool isActive;
	int animStep;
	float x;
	float y;
	float lifeTime;
};

