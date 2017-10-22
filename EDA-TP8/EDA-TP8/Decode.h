#pragma once

#include "lodepng.h"
#include <fstream>

#include <iostream>
#include <cstdlib>

using namespace std;

enum actualState { WAITING_RED, WAITING_GREEN, WAITING_BLUE, WAITING_H, WAITING_N };

bool decode(const char * archivo);