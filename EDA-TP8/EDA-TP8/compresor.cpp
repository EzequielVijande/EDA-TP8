#include "compresor.h"

// Devuelve true en caso de que no haya error, devuelve false si es que lo hay
bool compressImage(const char * imagePath, unsigned width, unsigned height, unsigned int threshold)
{
	std::vector<unsigned char> image; //the raw pixels

	if(width != height)
	{
		std::cout << "Actualemente el compresor solo admite imagenes cuadradas" << std::endl;
		return false;
	}
	unsigned error = lodepng::decode(image, width, height, imagePath);
	if (error)
	{
		std::cout << "Decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
		return false;
	}

	std::string imageName(imagePath);
	imageName.resize(imageName.size() - 4); //remuevo el ".png" del nombre
	std::string extension = EXTENSION;
	fs::ifstream newFile(imageName+extension); //creo el archivo
	newFile.close();
	fs::ofstream file(imageName + extension); //abro el archivo para escritura

	char * ptr = (char*) &width;
	for (int i = 0; i < 4; i++) //escribo el largo de la imagenen  4 bytes
	{
		file << *(ptr + i);
	}
	quadTree(file, image, threshold, width);

	return true;
}

void quadTree(fs::ofstream & text, std::vector<unsigned char>& image, unsigned int threshold ,unsigned int width)
{
	unsigned int rMax,rMin, gMax, gMin, bMax, bMin;
	setMinMax(image,rMin,rMax,3,0);
	setMinMax(image,gMin,gMax,3,1);
	setMinMax(image,bMin,bMax,3,2);
	unsigned int score = (rMax - rMin + gMax - gMin + bMax - bMin);
	if (score > threshold) //si no se llega al umbral, se divide nuevamente en cuatro
	{
		std::vector<unsigned char> firstCuadrant((width)*(width),0); // el size del nuevo cuadrante es los lados al cuadrado por 4 bytes cada pixel dividido 4
		std::vector<unsigned char> secondCuadrant((width)*(width), 0);
		std::vector<unsigned char> thirdCuadrant((width)*(width), 0);
		std::vector<unsigned char> fouthCuadrant((width)*(width), 0);
		fillCuadrant(image,width,firstCuadrant,1);
		fillCuadrant(image,width,secondCuadrant,2);
		fillCuadrant(image,width,thirdCuadrant,3);
		fillCuadrant(image,width,fouthCuadrant,4);
		text << 'H';
		// declare en el archivo que se divide ahora en cuatro hijos
		// llamo a la recursion para cada cuadrante
		text << 'N';
		quadTree(text, firstCuadrant, threshold, width/2);
		text << 'N';
		quadTree(text, secondCuadrant, threshold, width / 2);
		text << 'N';
		quadTree(text, thirdCuadrant, threshold, width / 2);
		text << 'N';
		quadTree(text, fouthCuadrant, threshold, width / 2);
	}
	else //se llega al limite, se reemplaza por el promedio
	{
		text << (char)((rMax + rMin)/2);
		text << (char)((gMax + gMin)/2);
		text << (char)((bMax + bMin)/2);
	}
}

void setMinMax(std::vector<unsigned char>& image,unsigned int & min, unsigned int & max, unsigned int skipNro,unsigned int offset)
{
	min = 255;
	max = 0;
	for (int i = offset; (i < (image.size()/(skipNro+1))); i += (skipNro+1))
	{
		if (image[i] > max)
		{
			max = image[i];
		}
		if (image[i] < min)
		{
			min = image[i];
		}
	}
}

bool fillCuadrant(std::vector<unsigned char>& original,unsigned int originalWidth,std::vector<unsigned char>& nCuadrant,unsigned int n)
{
	int iInicial = 0;
	int jInicial = 0;
	int iMax = 0;
	int jMax = 0;
	switch (n)
	{
	case 1:
		iMax = (originalWidth * 2);
		jMax = (originalWidth/2);
		break;
	case 2:
		iInicial = (originalWidth * 2);
		iMax = (originalWidth*4);
		jMax = (originalWidth/2);
		break;
	case 3:
		jInicial = (originalWidth/2);
		iMax = (originalWidth * 2);
		jMax = (originalWidth);
		break;
	case 4:
		iInicial = (originalWidth * 2);
		jInicial = (originalWidth/2);
		iMax = (originalWidth * 4);
		jMax = (originalWidth);
		break;
	default:
		return false;
		break;
	}
	for (int i = iInicial, k =0; i < iMax; i++,k++)
	{
		for (int j = jInicial, l = 0; j < jMax; j++,l++)
		{
			nCuadrant[k + l*(originalWidth)] = original[i + j*(originalWidth)];
		}
	}
	return true;
}