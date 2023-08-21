// Using netcdf-c version of the netcdf libraries, and all 
// arrays are c++ vector containers, 1D with computed index offset

#include <iostream>
#include <string>
#include <netcdf>
#include <vector>
#include "Config.h"
#include "State.h"
#include "Tend.h"
#include "Mesh.h"
#include "io.h"

using namespace std;

// constructor, derived from the State class
Tend::Tend(Config &config, Mesh &m) : State(config, m) {
  if (config.verbose) cout << "** Tend Constructor **" << endl;

  // variable initialization derived from State constructor.

}

