// 4. c++ vector, single length and computed index offset
// netcdf-c version

#include <iostream>
#include <string>
#include <netcdf>
#include <vector>

using namespace std;

/* Handle errors by printing an error message and exiting with a
 * non-zero status. */
#define ERRCODE 2
#define ERR(e) {printf("Error: %s\n", nc_strerror(e)); exit(ERRCODE);}
#define PRINT(message) {if (verbose) std::cout << message << std::endl;}
#define NEWLINE {if (verbose) std::cout << std::endl;}
bool verbose = true;

size_t readNCDim(int ncid, string dimName);
vector <int> readNCInt(int ncid, string varName, size_t dim);
vector <double> readNCDouble(int ncid, string varName, size_t dim);

class MpasMesh {
  public:

    // MPAS dimensions
    size_t nCells;
    size_t nVertLevels;
    size_t nEdges;
    size_t nVertices;
    size_t maxEdges;
    size_t maxEdges2;
    size_t vertexDegree;
  
    // MPAS mesh variables
    vector <double> latCell;
    vector <double> lonCell;
    vector <double> xCell;
    vector <double> yCell;
    vector <double> zCell;
    vector <double> latEdge;
    vector <double> lonEdge;
    vector <double> xEdge;
    vector <double> yEdge;
    vector <double> zEdge;
    vector <double> latVertex;
    vector <double> lonVertex;
    vector <double> xVertex;
    vector <double> yVertex;
    vector <double> zVertex;
    vector <double> areaCell;
    vector <double> angleEdge;
    vector <double> dcEdge;
    vector <double> dvEdge;
    vector <double> areaTriangle;
    vector <double> meshDensity;
    vector <int> indexToCellID;
    vector <int> indexToEdgeID;
    vector <int> indexToVertexID;
    vector <int> nEdgesOnCell;
    vector <int> nEdgesOnEdge;
    vector <int> cellsOnCell;
    vector <int> edgesOnCell;
    vector <int> verticesOnCell;
    vector <int> edgesOnEdge;
    vector <int> cellsOnEdge;
    vector <int> verticesOnEdge;
    vector <int> cellsOnVertex;
    vector <int> edgesOnVertex;
    // mesh quality variables. Not in init file.
    //vector <double> cellQuality;
    //vector <double> gridSpacing;
    //vector <double> triangleQuality;
    //vector <double> triangleAngleQuality;
    //vector <int> boundaryVertex;
    //vector <int> obtuseTriangle;
  
    // state variables
    vector <double> temperature;
    vector <double> salinity;
    vector <double> layerThickness;

    // constructor
    MpasMesh(string meshFileName) {

      int ncid, varid, retval;
      if (verbose) cout << "** Opening file: " << meshFileName << " **" << endl;
      if ((retval = nc_open((meshFileName).c_str(), NC_NOWRITE, &ncid))) ERR(retval);
      if (verbose) cout << endl;
    
      if (verbose) cout << "** Read in dimensions **" << endl;
      nCells = readNCDim(ncid, "nCells");
      nVertLevels = readNCDim(ncid, "nVertLevels");
      nEdges = readNCDim(ncid, "nEdges");
      nVertices = readNCDim(ncid, "nVertices");
      maxEdges = readNCDim(ncid, "maxEdges");
      maxEdges2 = readNCDim(ncid, "maxEdges2");
      vertexDegree = readNCDim(ncid, "vertexDegree");
      if (verbose) cout << endl;
    
      if (verbose) cout << "** Read in mesh variables **" << endl;
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
      if (verbose) cout << endl;
    
      if (verbose) cout << "** Read in state variables **" << endl;
      temperature = readNCDouble(ncid, "temperature", nCells*nVertLevels);
      salinity = readNCDouble(ncid, "salinity", nCells*nVertLevels);
      layerThickness = readNCDouble(ncid, "layerThickness", nCells*nVertLevels);
      if (verbose) cout << endl;
    
       }
};

int main()
{
  string dirName = "links_su/";
  //string fileName = "ocean.QU.240km.151209.nc";
  string fileName = "mpaso.EC30to60E2r3.230313.nc";
  //string fileName = "oRRS18to6v3.171116.nc";
  //
  MpasMesh m(dirName + fileName);
}

vector <int> readNCInt(int ncid, string varName, size_t dim) {
  int varid, retval;
  vector <int> var;
  var.resize(dim);
  if (verbose) cout << varName << ": ";
  if ((retval = nc_inq_varid(ncid, varName.c_str(), &varid))) ERR(retval);
  if ((retval = nc_get_var_int(ncid, varid, &var[0]))) ERR(retval);
  if (verbose) cout << var[0] << ", " << var[dim-1] << endl;
  return var;
}

vector <double> readNCDouble(int ncid, string varName, size_t dim) {
  int varid, retval;
  vector <double> var;
  var.resize(dim);
  if (verbose) cout << varName << ": ";
  if ((retval = nc_inq_varid(ncid, varName.c_str(), &varid))) ERR(retval);
  if ((retval = nc_get_var_double(ncid, varid, &var[0]))) ERR(retval);
  if (verbose) cout << var[0] << ", " << var[dim-1] << endl;
  return var;
}

size_t readNCDim(int ncid, string dimName) {
  int dimid, retval;
  size_t dim;
  if (verbose) cout << dimName << ": ";
  if ((retval = nc_inq_dimid(ncid, dimName.c_str(), &dimid) )) ERR(retval);
  if ((retval = nc_inq_dimlen(ncid, dimid, &dim) )) ERR(retval);
  if (verbose) cout << dim << endl;
  return dim;
}
