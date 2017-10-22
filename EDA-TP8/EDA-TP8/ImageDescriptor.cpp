#include "ImageDescriptor.h"



ImageDescriptor::ImageDescriptor(const char * path_)
{
	error = false;
	path = path_; //paso de (char *) a (string)
	Image = load_image_at_size(path_, IMAGE_SIZE_X, IMAGE_SIZE_Y);
	if (Image == nullptr)
	{
		error = true;
	}

}

const char * ImageDescriptor::getPath(void)
{
	return path;
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

//void ImageDescriptor::draw(int sizeX, int sizeY)
//{
//	//dibujar la imagen.
//}

ImageDescriptor::~ImageDescriptor()
{
	if (!error)
	{
		al_destroy_bitmap(Image); //tira error pero no se porque.
		Image = nullptr;
	}
}

bool ImageDescriptor::GetError()const
{
	return error;
}

ALLEGRO_BITMAP* ImageDescriptor::GetBitmap()const
{
	return Image;
}