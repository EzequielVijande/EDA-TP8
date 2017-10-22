#include "Sector.h"

Sector::Sector(unsigned int length_) { length = length_; };

unsigned int Sector::getLength() { return length; }
bool Sector::setLength(unsigned int length_)
{ 
	length = length_;
	return true;
}

unsigned int Sector::getRedMax() { return red.max; }
unsigned int Sector::getRedMin() { return red.min; }
unsigned int Sector::getRedAverage() { return ((unsigned int)(red.max + red.min) / 2); }
bool Sector::setRedMax(unsigned int red_)
{
	red.max = red_;
	return true;
}

bool Sector::setRedMin(unsigned int red_)
{
	red.min = red_;
	return true;
}

unsigned int Sector::getGreenMax() { return green.max; }
unsigned int Sector::getGreenMin() { return green.min; }
unsigned int Sector::getGreenAverage() { return ((unsigned int)(green.max + green.min) / 2); }
bool Sector::setGreenMax(unsigned int green_)
{
	green.max = green_;
	return true;
}

bool Sector::setGreenMin(unsigned int green_)
{
	green.min = green_;
	return true;
}

unsigned int Sector::getBlueMax() { return blue.max; }
unsigned int Sector::getBlueMin() { return blue.min; }
unsigned int Sector::getBlueAverage() { return ((unsigned int)(blue.max + blue.min) / 2); }
bool Sector::setBlueMax(unsigned int blue_)
{
	blue.max = blue_;
	return true;
}
bool Sector::setBlueMin(unsigned int blue_)
{
	blue.min = blue_;
	return true;
}