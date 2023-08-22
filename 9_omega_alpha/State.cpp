// Using netcdf-c version of the netcdf libraries, and all 
// arrays are c++ vector containers, 1D with computed index offset

#include <iostream>
#include <cmath> // for sin, M_PI
#include <string>
#include <netcdf>
#include <vector>
#include "Config.h"
#include "Meta.h"
#include "Mesh.h"
#include "State.h"
#include "io.h"

using namespace std;

// constructor
State::State(Config &config, Mesh &m) {
    LOG(4,"-> State::State")

    normalVelocity.resize(m.nEdges * m.nVertLevels, -1.0e32);
    layerThickness.resize(m.nCells * m.nVertLevels, -1.0e32);
}

void State::init(Config &config, Mesh &m) {
    LOG(4,"-> State::Init")

    size_t K=m.nVertLevels;
    double pi2Lx = 2.0*M_PI/config.Lx;
    size_t iCell, iEdge, k;
    if (config.initial_condition=="constant") {
        fill(normalVelocity.begin(), normalVelocity.end(), config.initial_condition_amplitude);
        fill(layerThickness.begin(), layerThickness.end(), config.initial_condition_amplitude);

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
        for (iEdge=0; iEdge<m.nEdges; iEdge++) {
            for (k=0; k<K; k++) {
                 normalVelocity[iEdge*K+k] = config.initial_condition_amplitude * std::sin(pi2Lx*m.xEdge[iEdge]);
            }
        }
        for (iCell=0; iCell<m.nCells; iCell++) {
            for (k=0; k<K; k++) {
                 layerThickness[iCell*K+k] = config.initial_condition_amplitude * std::sin(pi2Lx*(m.xCell[iCell]-m.xCell[0]));
            }
        }
//  //std::cout << "IC x: "<< Lx << " ";
//  for (size_t i=0; i<16; i++) {
//    printf(" %.0f", m.xCell[i]);
//  }
//  std::cout << std::endl;
//  std::cout << "IC h: ";
//  for (size_t i=0; i<16; i++) {
//    printf(" %.3f", layerThickness[i]);
//  }
//  std::cout << std::endl;
    } else {
        ERRORMESSAGE("State::init: Incorrect initial_case")
    }

}

