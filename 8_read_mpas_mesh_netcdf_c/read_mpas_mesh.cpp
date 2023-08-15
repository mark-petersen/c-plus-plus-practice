// 4. c++ vector, single length and computed index offset
// netcdf-c version

#include <iostream>
#include <string>
#include <netcdf>
#include <vector>

using namespace std;

string dirName = "links_su/";
string fileName = "ocean.QU.240km.151209.nc";
//string fileName = "EC30to60E2r3_mocBasinsAndTransects20210623.nc";
//string fileName = "oRRS18to6v3.171116.nc.nc";

/* Handle errors by printing an error message and exiting with a
 * non-zero status. */
#define ERRCODE 2
#define ERR(e) {printf("Error: %s\n", nc_strerror(e)); exit(ERRCODE);}
bool verbose = true;

size_t readNCDim(int ncid, string dimName);
vector <int> readNCVarInt(int ncid, string varName, size_t dim);
vector <double> readNCDouble(int ncid, string varName, size_t dim);

int main()
{
  /* Open the file */
  int ncid, varid, retval;
  if ((retval = nc_open((dirName + fileName).c_str(), NC_NOWRITE, &ncid)))
      ERR(retval);

  if (verbose) cout << "** Read in dimensions **" << endl;
  size_t nCells = readNCDim(ncid, "nCells");
  size_t nVertLevels = readNCDim(ncid, "nVertLevels");
  size_t nEdges = readNCDim(ncid, "nEdges");
  size_t nVertices = readNCDim(ncid, "nVertices");
  size_t maxEdges = readNCDim(ncid, "maxEdges");
  size_t maxEdges2 = readNCDim(ncid, "maxEdges2");
  int dimid;

  cout << "nCells " << nCells << endl;

  if (verbose) cout << "** Read in mesh variables **" << endl;
  vector <double> latCell = readNCDouble(ncid, "latCell", nCells);
  vector <double> lonCell = readNCDouble(ncid, "lonCell", nCells);
  vector <double> xCell = readNCDouble(ncid, "yCell", nCells);
  vector <double> yCell = readNCDouble(ncid, "yCell", nCells);
  vector <double> zCell = readNCDouble(ncid, "zCell", nCells);
  vector <double> latEdge = readNCDouble(ncid, "latEdge", nEdges);
  vector <double> lonEdge = readNCDouble(ncid, "lonEdge", nEdges);
  vector <double> xEdge = readNCDouble(ncid, "xEdge", nEdges);
  vector <double> yEdge = readNCDouble(ncid, "yEdge", nEdges);
  vector <double> zEdge = readNCDouble(ncid, "zEdge", nEdges);
  vector <double> latVertex = readNCDouble(ncid, "latVertex", nVertices);
  vector <double> lonVertex = readNCDouble(ncid, "lonVertex", nVertices);
  vector <double> xVertex = readNCDouble(ncid, "xVertex", nVertices);
  vector <double> yVertex = readNCDouble(ncid, "yVertex", nVertices);
  vector <double> zVertex = readNCDouble(ncid, "zVertex", nVertices);
  vector <double> areaCell = readNCDouble(ncid, "areaCell", nCells);
  vector <double> angleEdge = readNCDouble(ncid, "angleEdge", nEdges);
  vector <double> dcEdge = readNCDouble(ncid, "dcEdge", nEdges);
  vector <double> dvEdge = readNCDouble(ncid, "dvEdge", nEdges);
  vector <double> areaTriangle = readNCDouble(ncid, "areaTriangle", nVertices);
  //vector <double> cellQuality = readNCDouble(ncid, "cellQuality", nCells);
  //vector <double> gridSpacing = readNCDouble(ncid, "gridSpacing", nCells);
  //vector <double> triangleQuality = readNCDouble(ncid, "triangleQuality", nCells);
  //vector <double> triangleAngleQuality = readNCDouble(ncid, "triangleAngleQuality", nCells);
  vector <double> meshDensity = readNCDouble(ncid, "meshDensity", nCells);

  vector <int> indexToCellID = readNCInt(ncid, "indexToCellID", nCells);
  vector <int> indexToEdgeID = readNCInt(ncid, "indexToEdgeID", nEdge);
  vector <int> indexToVertexID = readNCInt(ncid, "indexToVertexID", nCells);
  vector <int> nEdgesOnCell = readNCInt(ncid, "nEdgesOnCell", nCells);
  vector <int> nEdgesOnEdge = readNCInt(ncid, "nEdgesOnEdge", Edge);
  vector <int> boundaryVertex = readNCInt(ncid, "boundaryVertex", nCells);
  vector <int> obtuseTriangle = readNCInt(ncid, "obtuseTriangle", nCells);

//    std::vector<std::vector<int>>
    //std::vector<std::vector<int>> cellsOnCellVector(nCells,std::vector<int>(maxEdges));
    // ha! Use the first version above. Then use vector.assign to create the size of the vector in the subroutine.
  vector <int> cellsOnCell = readNCInt(ncid, "cellsOnCell", nCells);
  vector <int> edgesOnCell = readNCInt(ncid, "edgesOnCell", nCells);
  vector <int> verticesOnCell = readNCInt(ncid, "verticesOnCell", nCells);
  vector <int> edgesOnEdge = readNCInt(ncid, "edgesOnEdge", nCells);
  vector <int> cellsOnEdge = readNCInt(ncid, "cellsOnEdge", nCells);
  vector <int> verticesOnEdge = readNCInt(ncid, "verticesOnEdge", nCells);
  vector <int> cellsOnVertex = readNCInt(ncid, "cellsOnVertex", nCells);
  vector <int> edgesOnVertex = readNCInt(ncid, "edgesOnVertex", nCells);


  if (verbose) cout << "** Read in state variables **" << endl;
  vector <double> temperature = readNCDouble(ncid, "temperature", nCells*nVertLevels);
}

vector <int> readNCInt(int ncid, string varName, size_t dim) {
  int varid, retval;
  vector <int> var;
  var.resize(dim);
  /* Get the varid of the data variable, based on its name. */
  if ((retval = nc_inq_varid(ncid, varName.c_str(), &varid))) ERR(retval);
  if ((retval = nc_get_var_int(ncid, varid, &var[0]))) ERR(retval);
  if (verbose) cout << varName << "[0]: " << var[0] << endl;
  return var;
}

vector <double> readNCDouble(int ncid, string varName, size_t dim) {
  int varid, retval;
  vector <double> var;
  var.resize(dim);
  /* Get the varid of the data variable, based on its name. */
  if ((retval = nc_inq_varid(ncid, varName.c_str(), &varid))) ERR(retval);
  if ((retval = nc_get_var_double(ncid, varid, &var[0]))) ERR(retval);
  if (verbose) cout << varName << "[0]: " << var[0] << endl;
  return var;
}

size_t readNCDim(int ncid, string dimName) {
  int dimid, retval;
  size_t dim;
  if ((retval = nc_inq_dimid(ncid, dimName.c_str(), &dimid) )) ERR(retval);
  if ((retval = nc_inq_dimlen(ncid, dimid, &dim) )) ERR(retval);
  if (verbose) cout << dimName << ": " << dim << endl;
  return dim;
}
