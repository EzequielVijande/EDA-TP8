#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "lodepng.h"
#include "boost\filesystem.hpp"
#include "boost/archive/text_oarchive.hpp"

#define EXTENSION ".met"
namespace fs = boost::filesystem;

bool compressImage(const char * imagePath, unsigned width, unsigned height, unsigned int threshold);

void quadTree(fs::ofstream & text, std::vector<unsigned char>& image, unsigned int threshold, unsigned int width);

//busca valor maximo y minimo en un vector, salteandose de a n elementos, empezando del elemento offset
void setMinMax(std::vector<unsigned char>& image,unsigned int& min,unsigned int& max, unsigned int skipNro,unsigned int offset); 

bool fillCuadrant(std::vector<unsigned char>& original, unsigned int originalWidth, std::vector<unsigned char>& nCuadrant, unsigned int n);