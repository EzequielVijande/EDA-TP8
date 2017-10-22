#pragma once
#include <vector>
#include "ImageDescriptor.h"


class damero
{
public:
	damero(int width_, int height_, vector<ImageDescriptor> & images_);
	void refresh(void);
	void touchDamero(int x, int y);
	void selectAllImages(void);
	void unSelectAllImages(void);
	bool wasSomethingSelected(void);
	void setImagesSize(int sizeX_, int sizeY_);
	vector <ImageDescriptor> & getImages(void);
	int getSizeX(void);
	int getSizeY(void);
	int getMargenX(void);
	int getMargenY(void);
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

