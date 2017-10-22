#pragma once

typedef struct Color
{
	unsigned char max;
	unsigned char min;
}color_t;

class Sector
{
public:
	Sector(unsigned int length_);

	unsigned int getLength();
	bool setLength(unsigned int length_);

	unsigned int getRedMax();
	unsigned int getRedMin();
	unsigned int getRedAverage();
	bool setRedMax(unsigned int red_);
	bool setRedMin(unsigned int red_);

	unsigned int getGreenMax();
	unsigned int getGreenMin();
	unsigned int getGreenAverage();
	bool setGreenMax(unsigned int green_);
	bool setGreenMin(unsigned int green_);

	unsigned int getBlueMax();
	unsigned int getBlueMin();
	unsigned int getBlueAverage();
	bool setBlueMax(unsigned int blue_);
	bool setBlueMin(unsigned int blue_);

private:
	unsigned int length;
	unsigned int trash;
	color_t red;
	color_t green;
	color_t blue;
};