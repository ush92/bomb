#pragma once
#include "field.h"
class Brick : public Field
{
public:
	Brick(void);
	~Brick(void);
private:	
	virtual void changeFreeState();
	virtual void changeCollidingState();

	void changeBrickType(int type);


	enum BrickTypes{ VOID_BRICK, HARD_BRICK, SOFT_BRICK };

	int brickType;
};
