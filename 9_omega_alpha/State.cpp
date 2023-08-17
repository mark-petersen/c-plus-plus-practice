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
State::State(string stateFileName) {

  int ncid, retval;
  if (config::verbose) cout << "** Opening file: " << stateFileName << " **" << endl;
  if ((retval = nc_open((stateFileName).c_str(), NC_NOWRITE, &ncid))) ERR(retval);
  if (config::verbose) cout << endl;

  if (config::verbose) cout << "** Read in state variables **" << endl;
  temperature = readNCDouble(ncid, "temperature", nCells*nVertLevels);
  salinity = readNCDouble(ncid, "salinity", nCells*nVertLevels);
  layerThickness = readNCDouble(ncid, "layerThickness", nCells*nVertLevels);
  if (config::verbose) cout << endl;

  if (config::verbose) cout << "** Closing file: " << stateFileName << " **" << endl;
  if ((retval = nc_close(ncid))) ERR(retval);
  if (config::verbose) cout << endl;
}
