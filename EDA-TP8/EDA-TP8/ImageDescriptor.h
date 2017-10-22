#pragma once
#include <string>
//header de allegro!!!
using namespace std;

class ImageDescriptor
{
public:
	ImageDescriptor(char * path_); //falta completar.
	bool wasSelected(void);
	void toggleSelected(void);
	void setPos(int posX_, int posY_);
	int getPosX(void);
	int getPosY(void);
	void draw(int sizeX, int sizeY); //falta completar.
	~ImageDescriptor();
private:
	bool selected;
	string path;
	int posX;
	int posY;
	ALLEGRO_BITMAP imageNotelected;
	ALLEGRO_BITMAP imageSelected; // esto es opcional, tambien se puede agregar un recuadro encima en lugar de imprimir una imagen totalmente nueva. 
};

