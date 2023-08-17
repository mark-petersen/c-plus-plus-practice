// Using netcdf-c version of the netcdf libraries, and all 
// arrays are c++ vector containers, 1D with computed index offset

#include <iostream>
#include <string>
#include <netcdf>
#include <vector>
#include "config.h"
#include "Mesh.h"
#include "io.h"

using namespace std;

// constructor
Mesh::Mesh() {

  string dirName = config::dirName; // convert char to string
  string fileName = config::fileName; // convert char to string
  string meshFileName = dirName + fileName;

  int ncid, varid, retval;
  if (config::verbose) cout << "** Opening file: " << meshFileName << " **" << endl;
  if ((retval = nc_open((meshFileName).c_str(), NC_NOWRITE, &ncid))) ERR(retval);
  if (config::verbose) cout << endl;

  if (config::verbose) cout << "** Read in dimensions **" << endl;
  nCells = readNCDim(ncid, "nCells");
  nVertLevels = readNCDim(ncid, "nVertLevels");
  nEdges = readNCDim(ncid, "nEdges");
  nVertices = readNCDim(ncid, "nVertices");
  maxEdges = readNCDim(ncid, "maxEdges");
  maxEdges2 = readNCDim(ncid, "maxEdges2");
  vertexDegree = readNCDim(ncid, "vertexDegree");
  if (config::verbose) cout << endl;

  if (config::verbose) cout << "** Read in mesh variables **" << endl;
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
  indexToCellID = readNCInt(ncid, "indexToCellID", nCells);
  indexToEdgeID = readNCInt(ncid, "indexToEdgeID", nEdges);
  indexToVertexID = readNCInt(ncid, "indexToVertexID", nVertices);
  nEdgesOnCell = readNCInt(ncid, "nEdgesOnCell", nCells);
  nEdgesOnEdge = readNCInt(ncid, "nEdgesOnEdge", nEdges);
  cellsOnCell = readNCInt(ncid, "cellsOnCell", nCells*maxEdges);
  edgesOnCell = readNCInt(ncid, "edgesOnCell", nCells*maxEdges);
  verticesOnCell = readNCInt(ncid, "verticesOnCell", nCells*maxEdges);
  edgesOnEdge = readNCInt(ncid, "edgesOnEdge", nEdges*maxEdges2);
  cellsOnEdge = readNCInt(ncid, "cellsOnEdge", nEdges*2.0);
  verticesOnEdge = readNCInt(ncid, "verticesOnEdge", nEdges*2.0);
  cellsOnVertex = readNCInt(ncid, "cellsOnVertex", nVertices*vertexDegree);
  edgesOnVertex = readNCInt(ncid, "edgesOnVertex", nVertices*vertexDegree);
  // mesh quality variables. Not in init file.
  //cellQuality = readNCDouble(ncid, "cellQuality", nCells);
  //gridSpacing = readNCDouble(ncid, "gridSpacing", nCells);
  //triangleQuality = readNCDouble(ncid, "triangleQuality", nCells);
  //triangleAngleQuality = readNCDouble(ncid, "triangleAngleQuality", nCells);
  //boundaryVertex = readNCInt(ncid, "boundaryVertex", nVertices);
  //obtuseTriangle = readNCInt(ncid, "obtuseTriangle", nCells);
  if (config::verbose) cout << endl;

  if (config::verbose) cout << "** Read in state variables **" << endl;
  temperature = readNCDouble(ncid, "temperature", nCells*nVertLevels);
  salinity = readNCDouble(ncid, "salinity", nCells*nVertLevels);
  layerThickness = readNCDouble(ncid, "layerThickness", nCells*nVertLevels);
  if (config::verbose) cout << endl;

  if (config::verbose) cout << "** Closing file: " << meshFileName << " **" << endl;
  if ((retval = nc_close(ncid))) ERR(retval);
  if (config::verbose) cout << endl;
}
