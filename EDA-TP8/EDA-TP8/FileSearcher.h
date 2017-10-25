#pragma once
#pragma once
#include <vector>
#include<iostream>
#include <fstream>
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost::filesystem;


bool SearchFiles(vector<const char*>& paths_vector, const char* path, const char* directory);
