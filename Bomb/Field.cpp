#include "Field.h"
#include <iostream>
using namespace std;
using namespace gameTypes;

Field::Field()
{

}

Field::~Field()
{
}

void Field::setIsFree(bool isFree)
{
	this->isFree = isFree;
}

bool Field::getIsFree() const
{
	return isFree;
}

void Field::setFieldType(FieldType fieldType)
{
	this->fieldType = fieldType;
}

FieldType Field::getFieldType() const
{
	return fieldType;
}

void Field::setItemType(ItemType itemType)
{
	this->itemType = itemType;
}

ItemType Field::getItemType() const
{
	return itemType;
}
