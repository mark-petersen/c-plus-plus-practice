// Using netcdf-c version of the netcdf libraries, and all 
// arrays are c++ vector containers, 1D with computed index offset

#include <iostream>
#include <string>
#include <netcdf>
#include <vector>
#include "Config.h"
#include "State.h"
#include "Mesh.h"
#include "io.h"

using namespace std;

// constructor
State::State(Config &config, Mesh &m) {
  if (config.verbose) cout << "** State Constructor **" << endl;

    normalVelocity.resize(m.nEdges * m.nVertLevels, -1.0e32);
    layerThickness.resize(m.nCells * m.nVertLevels, -1.0e32);
}

void State::init(Config &config, Mesh &m) {

  size_t K=m.nVertLevels;
  if (config.initial_condition=="constant") {
    fill(normalVelocity.begin(), normalVelocity.end(), config.initial_condition_constant);
    fill(layerThickness.begin(), layerThickness.end(), config.initial_condition_constant);

  } else if (config.initial_condition=="init_file") {

    std::string meshFileName = config.dirName + config.fileName;
    int ncid, retval;
    if (config.verbose) cout << "** Opening file: " << meshFileName << " **" << endl;
    if ((retval = nc_open((meshFileName).c_str(), NC_NOWRITE, &ncid))) ERR(retval);
    if (config.verbose) cout << endl;

    if (config.verbose) cout << "** Read in state variables **" << endl;
    fillNCDouble(ncid, "normalVelocity", normalVelocity);
    fillNCDouble(ncid, "layerThickness", layerThickness);
    if (config.verbose) cout << endl;

    if (config.verbose) cout << "** Closing file: " << meshFileName << " **" << endl;
    if ((retval = nc_close(ncid))) ERR(retval);
    if (config.verbose) cout << endl;

  } else if (config.initial_condition=="sinx") {
    for (size_t e=0; e<m.nEdges; e++) {
      for (size_t k=0; k<K; k++) {
         normalVelocity[e*K+k] = 1.0;
      }
    }
    for (size_t i=0; i<m.nCells; i++) {
      for (size_t k=0; k<K; k++) {
         layerThickness[i*K+k] = 2.0;
      }
    }
  } else {
    ERRORMESSAGE("State::init: Incorrect initial_case")
  }

}
