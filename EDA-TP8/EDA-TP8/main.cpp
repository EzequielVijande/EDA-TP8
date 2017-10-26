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

#define THRESHOLD_RATE 7.65

typedef struct
{
	string path;
	int threshold;
}userData_t;

//getPathFromCmd: funcion que concatena las palabras de un arreglo de char *, desde la segunda hasta la última palabra(inclusive),
//insertando entre medio de ellas un espacio. Recibe la cantidad de elementos del arreglo, el arreglo de palabras(o el char **).
//Devuelve las palabras concatenadas como string.
//Esta funcion contempla los casos que se recibe un path por línea de comando, pero ese path puede tener espacios entre medio.
string getPathFromCmd(int argc, char ** argv);

//interpretarThreshold: funcion que recibe un numero de 0,1 a 100 y lo traduce al threshold (umbral). devuelve el threshold traducido.
int interpretarThreshold(double threshold_cmd);

//string2dec: funcion que recibe un numero en formato const char *, y devuelve el numero en decimal.
//En caso de error de input devuelve -1.
double string2dec(const char * num_string);

//parserCmd: funcion que se asegura de recibir un path y un threshold.
bool parserCmd(int argc, char ** argv, userData_t & userData);

int main(int argc, char* argv[])
{
	vector <string> images_path;
	userData_t userData;
	if (!parserCmd(argc, argv, userData))
	{
	}
	else if (!SearchFiles(images_path, userData.path.c_str(), ".png"))
	{
		cout << "el path que ha pasado por parámetro es invalido, intente nuevamente" << endl;
		cout << "recuerde que primero debe pasar un path valido, donde haya imagenes .png" << endl;
		cout << "Luego, seguido de un espacio debe pasar el threshold, que es un numero entre 1 y 100" << endl;
	}
	else if (((int)images_path.size()) == 0)
	{
		cout << "no existe ninguna imagen .png en el directorio pasado por parametro" << endl;
		cout << "asegurese que la carpeta tenga imagenes, o de estar pasando bien el path" << endl;
		return -1;
	}
	else
	{
		if (!al_init())
		{
			cout << "Allegro Failed to initialize" << endl;
		}
		else
		{
			viewer v;
			vector<ImageDescriptor> Images;
			for (int i = 0; i < ((int)images_path.size()); i++)
			{
				ImageDescriptor img(images_path[i].c_str()); //init de todas las imagenes
				Images.push_back(img);
			}

			vector<ImageDescriptor> Botons;
			ImageDescriptor botLeft("C:\\Users\\malen\\source\\repos\\EDA-TP8\\EDA-TP8\\EDA-TP8\\botones/boton_left.png"); //init de los botones
			ImageDescriptor botRight("C:\\Users\\malen\\source\\repos\\EDA-TP8\\EDA-TP8\\EDA-TP8\\botones/boton_right.png");
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
			dam.refresh(); //se setean todas las posiciones de las imagenes de manera simetrica dentro del damero

			al_set_target_backbuffer(v.GetDisplay());
			al_flip_display();

			if (!(v.IsInitOK()))
			{
				cout << "Viewer Failed to initialize." << endl;
				return -1;
			}
			controller ctr(v, userData.threshold);
			while (!(ctr.GetExit()))
			{
				ctr.dispatch(v, dam);
			}
			Images.erase(Images.begin()); //eliminar todas las imagenes y botones.
		}
	}
	cout << "Press enter to quit..." << endl;
	getchar();
	return 0;
}


bool parserCmd(int argc, char ** argv, userData_t & userData)
{
	bool ret = true;
	if (argc > 2)
	{
		userData.path = getPathFromCmd(argc-1, argv); //arg - 1 porque el último elemento del argv no pertenece al path (el último es el treshold)
		double threshold_cmd = string2dec(argv[argc-1]); //el último parámetro es el treshold
		if ((threshold_cmd >= 1) && (threshold_cmd <= 100))
		{
			userData.threshold = interpretarThreshold(threshold_cmd);
		}
		else
		{
			cout << "error, el threshold (segundo parametro) debe ser un numero entre '1' y '100'" << endl;
			ret = false;
		}
	}
	else
	{
		cout << "error, recuerde ingresar un path al directorio de imagenes a comprimir y luego un threshold entre 1 y 100" << endl;
		ret = false;
	}

	return ret;
}
double string2dec(const char * num_string)
{
	double num_dec = 0.0;
	string num_string_aux = num_string;
	num_dec = (double)stof(num_string_aux, nullptr);
	
	return num_dec;
}

int interpretarThreshold(double threshold_cmd)
{
	int threshold = (int)ceil(threshold_cmd);
	return threshold;
}

string getPathFromCmd(int argc, char ** argv)
{
	string completePath;
	if (argc > 0)
	{
		completePath = argv[1];
	}
	for (int i = 2; i < argc; i++)
	{
		completePath += ' ';
		completePath += argv[i];
	}

	return completePath;
}