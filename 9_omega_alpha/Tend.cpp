// Using netcdf-c version of the netcdf libraries, and all 
// arrays are c++ vector containers, 1D with computed index offset

#include <iostream>
#include <string>
#include <netcdf>
#include <vector>
#include "Config.h"
#include "Tend.h"
#include "Meta.h"
#include "Mesh.h"
#include "io.h"

using namespace std;

// constructor
Tend::Tend(Config &config, Mesh &m) {
    LOG(4,"-> Tend::Tend")

    normalVelocity.resize(m.nEdges * m.nVertLevels, -1.0e32);
    layerThickness.resize(m.nCells * m.nVertLevels, -1.0e32);
}
