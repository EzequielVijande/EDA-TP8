#include "damero.h"

#define MARGEN_RATE 0.1
#define FIRST_IMG_OF_THIS_DAMERO(dameroActual) (IMAGES_PER_DAMERO * dameroActual)
#define LAST_IMG_OF_THIS_DAMERO(dameroActual) (IMAGES_PER_DAMERO * (dameroActual + 1))


damero::damero(int width_, int height_, vector<ImageDescriptor> & images_, vector<ImageDescriptor> & botons_)
{
	width = width_;
	height = height_;
	images = images_;
	margenX = width * MARGEN_RATE;
	margenY = height * MARGEN_RATE;
	botons = botons_;
	images = images_;
	botons[BOTON_LEFT].setPos(BOTON_SIZE_X * MARGEN_RATE, height - BOTON_SIZE_Y);
	botons[BOTON_LEFT].setPos(width-(BOTON_SIZE_X * MARGEN_RATE), height - BOTON_SIZE_Y);

	dameroMaximo = images.size() / IMAGES_PER_DAMERO;
	if (!(images.size() % IMAGES_PER_DAMERO)) //si la division es exacta
	{
		dameroMaximo--; //resto, porque los dameros arrancan desde 0.
	}					//ejemplo: si tengo 9 imagenes y mi damero acepta 9 imagenes como maximo, quiero que mi dameroMaximo sea '0' en lugar de '1'
}

void damero::setImagesSize(int sizeX_, int sizeY_)
{
	sizeX = sizeX_;
	sizeY = sizeY_;
}
void damero::setBotonsSize(int sizeX_, int sizeY_)
{
botonSizeX = sizeX_;
botonSizeY = sizeY_;
}
void damero::touchDamero(int x, int y)
{
	bool imageTouched = false;
	int posX = 0;
	int posY = 0;

	for (int i = FIRST_IMG_OF_THIS_DAMERO(dameroActual); (i < LAST_IMG_OF_THIS_DAMERO(dameroActual)) && (!imageTouched) && (i < images.size()); i++)
	{
		posX = images[i].getPosX();
		posY = images[i].getPosY();
		if (((x >= posX) && (x <= (posX + sizeX))) && ((y >= posY) && (y <= (posY + sizeY)))) //si se toco una imagen
		{
			imageTouched = true;
			images[i].toggleSelected();
		}
	}

	if (!imageTouched)
	{
		bool botonTouched = false;
		int inicio = 0;  //en principio, deseo tener en cuenta todo el vector de botones.
		int finish = botons.size();
		if (dameroActual == 0) //primer damero
		{
			inicio = 1; //salteo el primer boton.
		}
		else if (dameroActual == dameroMaximo) //ultimo damero
		{
			finish--; //descarto el último boton.
		}
		for (int i = 0; (i < finish) && (!botonTouched); i++)
		{
			posX = botons[i].getPosX();
			posY = botons[i].getPosY();
			if (((x >= posX) && (x <= (posX + sizeX))) && ((y >= posY) && (y <= (posY + sizeY)))) //si se toco una imagen
			{
				botonTouched = true;
				changeDamero(i);
			}
		}
	}
}

void damero::refresh(void)
{
	int posX = margenX; //posicion de la imagen inicial
	int posY = margenY;
	for (int i = FIRST_IMG_OF_THIS_DAMERO(dameroActual); (i < LAST_IMG_OF_THIS_DAMERO(dameroActual)) && (i < images.size()); i++)
	{
		images[i].setPos(posX, posY); //seteo posicion
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
	for (int i = FIRST_IMG_OF_THIS_DAMERO(dameroActual); (i < LAST_IMG_OF_THIS_DAMERO(dameroActual)) && (i < images.size()); i++)
	{
		if (!(images[i].wasSelected()))
		{
			images[i].toggleSelected();
		}
	}
}

void damero::unSelectAllImages(void)
{
	for (int i = FIRST_IMG_OF_THIS_DAMERO(dameroActual); (i < LAST_IMG_OF_THIS_DAMERO(dameroActual)) && (i < images.size()); i++)
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

vector <ImageDescriptor> & damero:: getBotons(void)
{
	return botons;
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

int damero::getDameroActual(void)
{
	return dameroActual;
}

int damero::getDameroMaximo(void)
{
	return dameroMaximo;
}

bool damero::imagesError(void)
{
	bool errorFounded = false;
	for (int i = 0; (i < images.size()) && (!errorFounded); i++)
	{
		if (images[i].GetError())
		{
			errorFounded = true;
		}
	}

	return errorFounded; //true si hubo error en alguna imagen.- false si esta todo bien.
}

void damero::changeDamero(int botonPressed_)
{
	switch (botonPressed_)
	{
		case BOTON_LEFT:
			dameroActual--;
			break;
		case BOTON_RIGHT:
			dameroActual++;
			break;
	}
}



damero::~damero()
{
}
