#pragma once
#include <iostream>
#include <vector>
#include "FileSearcher.h"
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
	vector <string> images_path;
	SearchFiles(images_path, "", ".png");
	viewer v;
	vector<ImageDescriptor> Images;
	for (int i = 0; i < ((int)images_path.size()); i++)
	{
		ImageDescriptor img(images_path[i].c_str()); //init de todas las imagenes
		Images.push_back(img);
	}

	vector<ImageDescriptor> Botons;
	ImageDescriptor botLeft("../EDA-TP8/botLeft.png"); //init de los botones
	ImageDescriptor botRight("../EDA-TP8/botRight.png");
	Botons.push_back(botLeft); //primero el boton izquierdo, luego el derecho
	Botons.push_back(botRight);

	damero dam(1000, 600, Images, Botons);
	if (dam.imagesError())
	{
		cout << "Image initialization Failed" << endl;
		al_rest(1.0);
		return -1;
	}

	dam.setImagesSize(IMAGE_SIZE_X, IMAGE_SIZE_Y); //se podria hacer que el tamaño lo decida damero, segun el tamaño del damero, el margen 
												   //entre imagenes, y la cantidad de imagenes
	dam.refresh(); //se setean todas las posiciones de las imagenes de manera simetrica
	
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