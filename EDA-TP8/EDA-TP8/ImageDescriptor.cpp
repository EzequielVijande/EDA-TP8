#include "ImageDescriptor.h"

#include <iostream>

ImageDescriptor::ImageDescriptor(const char * path_) : path(path_)
{
	error = false;
	//path = path_;
	Image = load_image_at_size(path_, IMAGE_SIZE_X, IMAGE_SIZE_Y);
	if (Image == nullptr)
	{
		error = true;
	}
	cout << path << endl;
	ALLEGRO_BITMAP * originalImage = al_load_bitmap(path_);
	if (originalImage == nullptr)
	{
		error = true;
	}
	else
	{
		width = al_get_bitmap_width(originalImage);
		height = al_get_bitmap_height(originalImage);
		al_destroy_bitmap(originalImage);
	}


}
ImageDescriptor::ImageDescriptor()
{
	error = true;
	Image = nullptr;
	width = 0;
	height = 0;
	Image = nullptr;



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

unsigned int ImageDescriptor::getWidth()
{
	return width;
}

unsigned int ImageDescriptor::getHeight()
{
	return height;
}


ImageDescriptor::~ImageDescriptor()
{
	/*
	if (!error)
	{
		al_destroy_bitmap(Image); //tira error pero no se porque.
		Image = nullptr;
	}
	*/
}

bool ImageDescriptor::GetError()const
{
	return error;
}

ALLEGRO_BITMAP* ImageDescriptor::GetBitmap()const
{
	return Image;
}