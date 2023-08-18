// Using netcdf-c version of the netcdf libraries, and all 
// arrays are c++ vector containers, 1D with computed index offset

#include <iostream>
#include <string>
#include <netcdf>
#include <vector>
#include "config.h"
#include "State.h"
#include "Mesh.h"
#include "io.h"

using namespace std;

// constructor
State::State(Mesh &m) {
  if (config::verbose) cout << "** State Constructor **" << endl;

    normalVelocity.resize(m.nEdges * m.nVertLevels, -1.0e32);
    layerThickness.resize(m.nCells * m.nVertLevels, -1.0e32);
}

void State::init(Mesh &m) {
  string initial_case = "init_file";
  //string initial_case = "ones";

  size_t K=m.nVertLevels;
  if (initial_case=="ones") {
    fill(normalVelocity.begin(), normalVelocity.end(), 1.0);
    fill(layerThickness.begin(), layerThickness.end(), 1.0);

  } else if (initial_case=="init_file") {

    string dirName = config::dirName; // convert char to string
    string fileName = config::fileName; // convert char to string
    string meshFileName = dirName + fileName;
    int ncid, retval;
    if (config::verbose) cout << "** Opening file: " << meshFileName << " **" << endl;
    if ((retval = nc_open((meshFileName).c_str(), NC_NOWRITE, &ncid))) ERR(retval);
    if (config::verbose) cout << endl;

    if (config::verbose) cout << "** Read in state variables **" << endl;
    fillNCDouble(ncid, "normalVelocity", normalVelocity);
    fillNCDouble(ncid, "layerThickness", layerThickness);
    if (config::verbose) cout << endl;

    if (config::verbose) cout << "** Closing file: " << meshFileName << " **" << endl;
    if ((retval = nc_close(ncid))) ERR(retval);
    if (config::verbose) cout << endl;

  } else if (initial_case=="sinx") {
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
