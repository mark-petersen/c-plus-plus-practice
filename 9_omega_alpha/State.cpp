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

    normalVelocity.resize(m.nEdges * m.nVertLevels);
    layerThickness.resize(m.nCells * m.nVertLevels);

    // initialize
    size_t d=m.nVertLevels;
    for (size_t e=0; e<m.nEdges; e++) {
      for (size_t k=0; k<d; k++) {
         normalVelocity[e*d+k] = 1.0;
      }
    }
    for (size_t i=0; i<m.nCells; i++) {
      for (size_t k=0; k<d; k++) {
         layerThickness[i*d+k] = 2.0;
      }
    }
}
