#include "ImageDescriptor.h"



ImageDescriptor::ImageDescriptor(char * path_)
{
	path = path_; //paso de (char *) a (string)

}
bool ImageDescriptor::wasSelected(void)
{
	return selected;
}

void ImageDescriptor::toggleSelected(void)
{
	selected = !selected;
}

void ImageDescriptor::setPos(int posX_, int posY_) 
{
	posX = posX_;
	posY = posY_;
}

int ImageDescriptor::getPosX(void)
{
	return posX;
}

int ImageDescriptor::getPosY(void)
{
	return posY;
}

void ImageDescriptor::draw(int sizeX, int sizeY)
{
	//dibujar la imagen.
}

ImageDescriptor::~ImageDescriptor()
{
}