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

void ImageDescriptor::draw(int x, int y, int scale)
{
	//dibujar la imagen.
}

ImageDescriptor::~ImageDescriptor()
{
}
