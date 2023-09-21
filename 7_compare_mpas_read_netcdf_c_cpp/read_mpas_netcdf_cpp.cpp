/*
   to make meshes:
   planar_hex --nx 16 --ny 16 --dc 64000 -o base_mesh_16x16.nc
   MpasMeshConverter.x base_mesh_16x16.nc mpas_mesh_16x16.nc
*/

#include <array>
#include <iostream>
#include <netcdf>
#include <string>
#include <vector>

using namespace std;
using namespace netCDF;

string dirName = "links_su/";
string fileName = "ocean.QU.240km.151209.nc";
// string fileName = "EC30to60E2r3_mocBasinsAndTransects20210623.nc";
// string fileName = "oRRS18to6v3.171116.nc.nc";
static constexpr size_t nVertLevels = 60;
static constexpr size_t nEdges = 22403;
static constexpr size_t nCells = 7153;
static constexpr size_t nVertices = 15211;
static constexpr size_t maxEdges = 6;
static constexpr size_t maxEdges2 = 12;

// Time reading with netcdf cpp library with the following methods:
// 1. C arrays with fixed size
// 2. C arrays with ** and new
// 3. c++ array object (dimensioned to a number)
// 4. c++ vector, single length and computed index offset
// 5. c++ vector of vectors for 2D.
// 6. YAKL arrays

int main() {
  NcFile dataFile(dirName + fileName, NcFile::read);

  // int nCells = dataFile.getDim("nCells").getSize();
  double xCell[nCells];
  dataFile.getVar("xCell").getVar(xCell);
  cout << "xCell[0]: " << xCell[0] << endl;

  {
    cout << "1. C arrays with fixed size   ";
    double temperature[nCells][nVertLevels];
    dataFile.getVar("temperature").getVar(temperature);
    cout << "temperature[200][20] " << temperature[200][20] << endl;
  }
  {
    cout << "2. C arrays with ** and new (variable dim)  ";
    double **var;
    constexpr size_t dim1 = nCells;
    constexpr size_t dim2 = nVertLevels;
    auto varName = "temperature";

    var = new double *[dim1];
    for (int i = 0; i < dim1; i++)
      var[i] = new double[dim2];
    NcVar tempVar;
    tempVar = dataFile.getVar(varName);
    if (tempVar.isNull()) {
      cout << "Warning: " << varName << " was not found in file" << endl;
    } else {
      double tempArray[dim1][dim2];
      tempVar.getVar(tempArray);
      // dataFile.getVar("temperature").getVar(tempArray);
      for (int i = 0; i < dim1; i++) {
        for (int j = 0; j < dim2; j++) {
          var[i][j] = tempArray[i][j];
        }
      }
    }
    cout << "temperature[200][20] " << var[200][20] << endl;
  }
  {
    cout << "3. c++ array object (fixed dim) ";
    constexpr size_t dim1 = nCells;
    constexpr size_t dim2 = nVertLevels;
    array<array<double, dim2>, dim1> var;
    auto varName = "temperature";

    NcVar tempVar;
    tempVar = dataFile.getVar(varName);
    if (tempVar.isNull()) {
      cout << "Warning: " << varName << " was not found in file" << endl;
    } else {
      double tempArray[dim1][dim2];
      tempVar.getVar(tempArray);
      for (int i = 0; i < dim1; i++) {
        for (int j = 0; j < dim2; j++) {
          var[i][j] = tempArray[i][j];
        }
      }
    }
    cout << "temperature[200][20] " << var[200][20] << endl;
  }
  {
    cout << "4. c++ vector, single length and computed index offset ";
    // I was not able to figure out how to read a resized vector directly
    // int dim1 = dataFile.getDim("nCells").getSize();
    // int dim2 = dataFile.getDim("nVertLevels").getSize();
    // cout << "dim12 " << dim1 << " " << dim2 << endl;
    constexpr size_t dim1 = nCells;
    constexpr size_t dim2 = nVertLevels;
    vector<double> var;
    var.resize(dim1 * dim2);
    auto varName = "temperature";

    NcVar tempVar;
    tempVar = dataFile.getVar(varName);
    if (tempVar.isNull()) {
      cout << "Warning: " << varName << " was not found in file" << endl;
    } else {
      double tempArray[dim1][dim2];
      tempVar.getVar(tempArray);
      // I was not able to figure out how to read a resized vector directly
      // I tried variations of this with dim1, dim2 read in:
      // tempVar.getVar(&var[0])
      // tempVar.getVar(var[0])
      // tempVar.getVar(var.begin())
      // tempVar.getVar(&var.begin())
      // tempVar.getVar(var.front())
      // tempVar.getVar(&var.front())
      // tempVar.getVar(&var[0],dim1*dim2,&var[0])
      for (int i = 0; i < dim1; i++) {
        for (int j = 0; j < dim2; j++) {
          var[i * dim2 + j] = tempArray[i][j];
        }
      }
    }
    cout << "temperature[200*d2+20] " << var[200 * dim2 + 20] << endl;
  }
  {
    cout << "5. c++ vector of vectors for 2D ";
    constexpr size_t dim1 = nCells;
    constexpr size_t dim2 = nVertLevels;
    vector<vector<double>> var;
    auto varName = "temperature";

    NcVar tempVar;
    tempVar = dataFile.getVar(varName);
    if (tempVar.isNull()) {
      cout << "Warning: " << varName << " was not found in file" << endl;
    } else {
      double tempArray[dim1][dim2];
      tempVar.getVar(tempArray);
      var.resize(dim1);
      for (int i = 0; i < dim1; i++) {
        var[i].resize(dim2);
        for (int j = 0; j < dim2; j++) {
          var[i][j] = tempArray[i][j];
        }
      }
    }
    cout << "temperature[200][20] " << var[200][20] << endl;
  }
}
