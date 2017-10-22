#pragma once
#include <vector>
#include "ImageDescriptor.h"

#define MARGEN_RATE 0.15

class damero
{
public:
	damero(int width_, int height_, vector<ImageDescriptor> & images_);
	void refresh(void);
	void touchDamero(int x, int y);
	void setImagesSize(int sizeX_, int sizeY_);
	~damero();
private:
	vector<ImageDescriptor> images;
	int sizeX; //tamaño de cada image
	int sizeY;
	int margenX; //margenes
	int margenY;
	int width; //dimensiones del damero
	int height;
};

