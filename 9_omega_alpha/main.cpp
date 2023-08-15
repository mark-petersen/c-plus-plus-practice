// 4. c++ vector, single length and computed index offset
// netcdf-c version

bool verbose = true;

#include <iostream>
#include <string>
#include <vector>
#include "config.h"

#include "MpasMesh.h"

using namespace std;

int main() {
  string dirName = config::dirName; // convert char to string
  string fileName = config::fileName; // convert char to string

  MpasMesh m(dirName + fileName);

}

