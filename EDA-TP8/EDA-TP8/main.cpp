
#include <iostream>
#include <vector>
#include <allegro5\allegro.h>
#include "Controller.h"
#include "damero.h"
#include "ImageDescriptor.h"
#include "lodepng.h"
#include "Output.h"

#define THRESHOLD 50

int main(int argc, char* argv[])
{
	if(!al_init())
	{
		cout << "Allegro Failed to initialize" << endl;
		return -1;
	}
	viewer v;
	vector<ImageDescriptor> Images;
	ImageDescriptor img("../EDA-TP8/prueba.png"); //init de todas las imagenes (push_back al vector).
	Images.push_back(img);
	vector<ImageDescriptor> Botons;
	ImageDescriptor botLeft("../EDA-TP8/botLeft.png"); //init de los botones (push_back al vector).
	ImageDescriptor botRight("../EDA-TP8/botRight.png");
	Botons.push_back(botLeft);
	Botons.push_back(botRight);
	damero dam(1000, 600, Images, Botons);
	if (dam.imagesError())
	{
		cout << "Image initialization Failed" << endl;
		al_rest(1.0);
		return -1;
	}
	img.setPos(0.1 * 1000, 0.1 * 600); //en lugar de setear las imagenes una por una, hago refresh del damero y se me setean todas las posiciones
										//de manera simétrica.
	dam.refresh();
	dam.setImagesSize(IMAGE_SIZE_X, IMAGE_SIZE_Y); //se podria hacer que el tamaño lo decida damero, segun el tamaño del damero, el margen 
													//entre imagenes, y la cantidad de imagenes
	al_set_target_backbuffer(v.GetDisplay());
	al_flip_display();
	
	if (!(v.IsInitOK()))
	{
		cout << "Viewer Failed to initialize." << endl;
		return -1;
	}
	controller ctr(v,THRESHOLD);
	while (!(ctr.GetExit()))
	{
		ctr.dispatch(v,dam);
	}
	Images.erase(Images.begin()); //eliminar todas las imagenes y botones.
	return 0;
}