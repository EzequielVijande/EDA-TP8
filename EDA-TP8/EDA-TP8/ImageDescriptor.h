#pragma once
#include <string>
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>
#include"Imagenes.h"
#define IMAGE_SIZE_X 256
#define IMAGE_SIZE_Y 130
#define SPACE 10

using namespace std;

class ImageDescriptor
{
public:
	ImageDescriptor(const char * path_); //falta completar.
	bool wasSelected(void);
	void toggleSelected(void);
	void setPos(int posX_, int posY_);
	int getPosX(void);
	int getPosY(void);
	unsigned int getWidth();
	unsigned int getHeight();
	const char * getPath(void);
	bool GetError()const;
	ALLEGRO_BITMAP* GetBitmap()const;
	//void draw(int sizeX, int sizeY); //falta completar.
	~ImageDescriptor();
private:
	bool selected;
	const char * path;
	int posX;
	int posY;
	ALLEGRO_BITMAP* Image;
	bool error;
	unsigned int  width;
	unsigned int height;
};

