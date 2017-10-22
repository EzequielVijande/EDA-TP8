#include "damero.h"

#define MARGEN_RATE 0.1

damero::damero(int width_, int height_, vector<ImageDescriptor> & images_)
{
	width = width_;
	height = height_;
	images = images_;
	margenX = width * MARGEN_RATE;
	margenY = height * MARGEN_RATE;
}

void damero::setImagesSize(int sizeX_, int sizeY_)
{
	sizeX = sizeX_;
	sizeY = sizeY_;
}
void damero::touchDamero(int x, int y)
{
	bool imageTouched = false;
	int posX = 0;
	int posY = 0;

	for (int i = 0; (i < images.size()) && (!imageTouched); i++)
	{
		posX = images[i].getPosX();
		posY = images[i].getPosY();
		if (((x >= posX) && (x <= (posX + sizeX))) && ((y >= posY) && (y <= (posY + sizeY)))) //si se toco una imagen
		{
			imageTouched = true;
			images[i].toggleSelected();
		}
	}
}

void damero::refresh(void)
{
	int posX = margenX; //posicion de la imagen inicial
	int posY = margenY;
	for (int i = 0; i < (images.size()); i++)
	{
		images[i].setPos(posX, posY); //seteo posicion
		//images[i].draw(sizeX, sizeY); //dibujo
		posX += (sizeX + margenX);  //calculo posición de la proxima imagen
		posY += (sizeY + margenY);
		if (posX > (width - margenX - sizeX)) //reseteo posX cuando llega al tope de anchura del damero. tope de anchura: (width - margenX - sizeX)
		{
			posX = margenX;
		}
	}
}

void damero::selectAllImages(void)
{
	for (int i = 0; i < images.size(); i++)
	{
		if (!(images[i].wasSelected()))
		{
			images[i].toggleSelected();
		}
	}
}

void damero::unSelectAllImages(void)
{
	for (int i = 0; i < images.size(); i++)
	{
		if ((images[i].wasSelected()))
		{
			images[i].toggleSelected();
		}
	}
}

vector <ImageDescriptor> & damero::getImages(void)
{
	return images;
}

bool damero::wasSomethingSelected(void)
{
	bool wasSomethingSelected = false;
	for (int i = 0; (i < images.size()) && !wasSomethingSelected; i++)
	{
		if (images[i].wasSelected())
		{
			wasSomethingSelected = true;
		}
	}
	return wasSomethingSelected;
}

int damero::getSizeX(void)
{
	return sizeX;
}

int damero::getSizeY(void)
{
	return sizeY;
}

int damero::getMargenX(void)
{
	return margenX;
}

int damero::getMargenY(void)
{
	return margenY;
}



damero::~damero()
{
}
