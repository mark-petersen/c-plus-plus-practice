// Using netcdf-c version of the netcdf libraries, and all 
// arrays are c++ vector containers, 1D with computed index offset

#include <iostream>
#include <string>
#include <netcdf>
#include "Config.h"
#include "Mesh.h"
#include "io.h"

using namespace std;

// constructor
Mesh::Mesh(Config &config) {
    LOG(4,"-> Mesh::Mesh")

    string meshFileName = config.dirName + config.fileName;

    int ncid, retval;
    if (config.verbose) cout << "** Opening file: " << meshFileName << " **" << endl;
    if ((retval = nc_open((meshFileName).c_str(), NC_NOWRITE, &ncid))) ERR(retval);
    if (config.verbose) cout << endl;

    if (config.verbose) cout << "** Read in dimensions **" << endl;
    nCells = readNCDim(ncid, "nCells");
    nVertLevels = readNCDim(ncid, "nVertLevels");
    nEdges = readNCDim(ncid, "nEdges");
    nVertices = readNCDim(ncid, "nVertices");
    maxEdges = readNCDim(ncid, "maxEdges");
    maxEdges2 = readNCDim(ncid, "maxEdges2");
    vertexDegree = readNCDim(ncid, "vertexDegree");
    if (config.verbose) cout << endl;

    if (config.verbose) cout << "** Read in mesh variables **" << endl;
    latCell = readNCDouble(ncid, "latCell", nCells);
    lonCell = readNCDouble(ncid, "lonCell", nCells);
    xCell = readNCDouble(ncid, "yCell", nCells);
    yCell = readNCDouble(ncid, "yCell", nCells);
    zCell = readNCDouble(ncid, "zCell", nCells);
    latEdge = readNCDouble(ncid, "latEdge", nEdges);
    lonEdge = readNCDouble(ncid, "lonEdge", nEdges);
    xEdge = readNCDouble(ncid, "xEdge", nEdges);
    yEdge = readNCDouble(ncid, "yEdge", nEdges);
    zEdge = readNCDouble(ncid, "zEdge", nEdges);
    latVertex = readNCDouble(ncid, "latVertex", nVertices);
    lonVertex = readNCDouble(ncid, "lonVertex", nVertices);
    xVertex = readNCDouble(ncid, "xVertex", nVertices);
    yVertex = readNCDouble(ncid, "yVertex", nVertices);
    zVertex = readNCDouble(ncid, "zVertex", nVertices);
    areaCell = readNCDouble(ncid, "areaCell", nCells);
    angleEdge = readNCDouble(ncid, "angleEdge", nEdges);
    dcEdge = readNCDouble(ncid, "dcEdge", nEdges);
    dvEdge = readNCDouble(ncid, "dvEdge", nEdges);
    areaTriangle = readNCDouble(ncid, "areaTriangle", nVertices);
    meshDensity = readNCDouble(ncid, "meshDensity", nCells);

    // Cell pointers. These need to be reduced by 1 for Fortran->C
    indexToCellID = readNCInt(ncid, "indexToCellID", nCells, true);
    indexToEdgeID = readNCInt(ncid, "indexToEdgeID", nEdges, true);
    indexToVertexID = readNCInt(ncid, "indexToVertexID", nVertices, true);
    cellsOnCell = readNCInt(ncid, "cellsOnCell", nCells*maxEdges, true);
    edgesOnCell = readNCInt(ncid, "edgesOnCell", nCells*maxEdges, true);
    verticesOnCell = readNCInt(ncid, "verticesOnCell", nCells*maxEdges, true);
    edgesOnEdge = readNCInt(ncid, "edgesOnEdge", nEdges*maxEdges2, true);
    cellsOnEdge = readNCInt(ncid, "cellsOnEdge", nEdges*2.0, true);
    verticesOnEdge = readNCInt(ncid, "verticesOnEdge", nEdges*2.0, true);
    cellsOnVertex = readNCInt(ncid, "cellsOnVertex", nVertices*vertexDegree, true);
    edgesOnVertex = readNCInt(ncid, "edgesOnVertex", nVertices*vertexDegree, true);

    // These do not need to be reduced by 1 for Fortran->C
    nEdgesOnCell = readNCInt(ncid, "nEdgesOnCell", nCells, false);
    nEdgesOnEdge = readNCInt(ncid, "nEdgesOnEdge", nEdges, false);

    // mesh quality variables. Not in init file.
    //cellQuality = readNCDouble(ncid, "cellQuality", nCells);
    //gridSpacing = readNCDouble(ncid, "gridSpacing", nCells);
    //triangleQuality = readNCDouble(ncid, "triangleQuality", nCells);
    //triangleAngleQuality = readNCDouble(ncid, "triangleAngleQuality", nCells);
    //boundaryVertex = readNCInt(ncid, "boundaryVertex", nVertices);
    //obtuseTriangle = readNCInt(ncid, "obtuseTriangle", nCells);
    if (config.verbose) cout << endl;

    if (config.verbose) cout << "** Closing file: " << meshFileName << " **" << endl;
    if ((retval = nc_close(ncid))) ERR(retval);
    if (config.verbose) cout << endl;

    edgeSignOnCell.resize(nCells*maxEdges);
    size_t E=maxEdges;
    size_t iCell, i, cell1, cell2, iEdge;
    for (iCell=0; iCell<nCells; iCell++) {
        for (i=0; i<nEdgesOnCell[iCell]; i++) {
            iEdge = edgesOnCell[iCell*E+i];
            cell1 = cellsOnEdge[iEdge*2];
            cell2 = cellsOnEdge[iEdge*2+1];
            // Vectors point from lower to higher cell number.
            // If my cell number is higher than my neighbor, then
            // vector points towards me and the edge sign is positive.
            if (iCell==std::max(cell1,cell2)) {
                edgeSignOnCell[iCell*E+i] = 1;
            } else {
                edgeSignOnCell[iCell*E+i] = -1;
            }
        }
    }

}
