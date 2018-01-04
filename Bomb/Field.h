#pragma once
#include "GameTypes.h"

using namespace gameTypes;

class Field
{
public:
	Field(void);
	~Field(void);
	void setIsFree(bool isFree);
	bool getIsFree() const;

	void setFieldType(FieldType fieldType);
	FieldType getFieldType() const;

	void setItemType(ItemType itemType);
	ItemType getItemType() const;

private: 
	bool isFree;
	FieldType fieldType;
	ItemType itemType;
};

