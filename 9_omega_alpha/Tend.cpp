// Using netcdf-c version of the netcdf libraries, and all 
// arrays are c++ vector containers, 1D with computed index offset

#include <iostream>
#include <string>
#include <netcdf>
#include <vector>
#include "Config.h"
#include "State.h"
#include "Meta.h"
#include "Mesh.h"
#include "Tend.h"

using namespace std;

// constructor
Tend::Tend(Config &config, Mesh &m) : State(config, m) {
    LOG(4,"-> Tend::Tend")

}
