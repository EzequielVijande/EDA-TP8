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
	void draw(int x, int y, int scale); //falta completar.
	~ImageDescriptor();
private:
	bool selected;
	string path;
	ALLEGRO_BITMAP imageNotelected;
	ALLEGRO_BITMAP imageSelected; // esto es opcional, tambien se puede agregar un recuadro encima en lugar de imprimir una imagen totalmente nueva. 
};

