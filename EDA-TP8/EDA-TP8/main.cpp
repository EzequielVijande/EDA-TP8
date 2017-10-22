#include <iostream>
#include <vector>
#include <allegro5\allegro.h>
#include "Controller.h"
#include "damero.h"
#include "ImageDescriptor.h"
#include "lodepng.h"
#include "Output.h"

int main(int argc, char* argv[])
{
	if(!al_init())
	{
		cout << "Allegro Failed to initialize" << endl;
		return -1;
	}
	viewer v;
	ImageDescriptor img("../EDA-TP8/prueba.png");
	if (img.GetError())
	{
		cout << "Image initialization Failed" << endl;
		al_rest(1.0);
		return -1;
	}
	img.setPos(0.1 * 1000, 0.1 * 600);
	vector<ImageDescriptor> Images;
	Images.push_back(img);
	damero dam(1000, 600, Images);
	dam.setImagesSize(IMAGE_SIZE_X, IMAGE_SIZE_Y);
	al_set_target_backbuffer(v.GetDisplay());
	al_flip_display();
	
	if (!(v.IsInitOK()))
	{
		cout << "Viewer Failed to initialize." << endl;
		return -1;
	}
	controller ctr(v);
	while (!(ctr.GetExit()))
	{
		ctr.dispatch(v,dam);
	}
	Images.erase(Images.begin());
	return 0;
}