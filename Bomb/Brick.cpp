#include "Brick.h"


Brick::Brick(void)
{
	this->brickType = VOID_BRICK;
}


Brick::~Brick(void)
{
	//?
}

void Brick::changeFreeState(void)
{
	if(this->isFree == true) this->isFree = false;
	else this->isFree = true;
}

void Brick::changeCollidingState()
{
	if(this->isColliding == true) this->isColliding = false;
	else this->isColliding = true;
}

void Brick::changeBrickType(int type)
{
	this->brickType = type;
}