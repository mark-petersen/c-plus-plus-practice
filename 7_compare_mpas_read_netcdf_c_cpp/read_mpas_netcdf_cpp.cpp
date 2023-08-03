/* 
   to make meshes:
   planar_hex --nx 16 --ny 16 --dc 64000 -o base_mesh_16x16.nc
   MpasMeshConverter.x base_mesh_16x16.nc mpas_mesh_16x16.nc
*/

#include <iostream>
#include <string>
#include <netcdf>
#include <array>

using namespace std;
using namespace netCDF;

// QU240
static constexpr auto fileName = "init_QU240.nc";
static constexpr size_t nVertLevels = 60 ;
static constexpr size_t nEdges = 22403 ;
static constexpr size_t nCells = 7153 ;
static constexpr size_t nVertices = 15211 ;
static constexpr size_t maxEdges = 6 ;
static constexpr size_t maxEdges2 = 12 ;

// Time reading with netcdf cpp library with the following methods:
// 1. C arrays with fixed size
// 2. C arrays with ** and new
// 3. c++ array object (dimensioned to a number)
// 4. c++ vector, single length and computed index offset
// 5. c++ vector of vectors for 2D.
// 6. YAKL arrays

int main()
{
  NcFile dataFile(fileName, NcFile::read);

  //int nCells = dataFile.getDim("nCells").getSize();
  double xCell[nCells];
  dataFile.getVar("xCell").getVar(xCell);
  cout << "xCell[0]: " << xCell[0] << endl;

// 1. C arrays with fixed size
  {
    cout << "1. C arrays with fixed size   ";
    double temperature[nCells][nVertLevels];
    dataFile.getVar("temperature").getVar(temperature);
    cout << "temperature[0][0] " << temperature[0][0] << endl;
  }

// 2. C arrays with ** and new
  {
    cout << "2. C arrays with ** and new (variable dim)  ";
    double** var;
    constexpr size_t dim1=nCells;
    constexpr size_t dim2=nVertLevels;
    auto varName = "temperature";

    var = new double*[dim1];
    for (int i=0; i<dim1; i++) var[i] = new double[dim2];
    NcVar tempVar;
    tempVar = dataFile.getVar(varName);
    if(tempVar.isNull()) {
      cout << "Warning: " <<  varName << " was not found in file" << endl;
    } else {
      double tempArray[dim1][dim2];
      tempVar.getVar(tempArray);
      //dataFile.getVar("temperature").getVar(tempArray);
      for (int i = 0; i < dim1; i++) {
        for (int j = 0; j < dim2; j++) {
          var[i][j] = tempArray[i][j];
        }
      }
    }
    cout << "temperature[0][0] " << var[0][0] << endl;
  }

// 3. c++ array object (dimensioned to a number)
  {
    cout << "3. c++ array object (fixed dim)    var";
    constexpr size_t dim1=nCells;
    constexpr size_t dim2=nVertLevels;
    array < array<double, dim2>, dim1 > var;
    auto varName = "temperature";

    NcVar tempVar;
    tempVar = dataFile.getVar(varName);
    if(tempVar.isNull()) {
      cout << "Warning: " <<  varName << " was not found in file" << endl;
    } else {
      double tempArray[dim1][dim2];
      tempVar.getVar(tempArray);
      for (int i = 0; i < dim1; i++) {
        for (int j = 0; j < dim2; j++) {
          var[i][j] = tempArray[i][j];
        }
      }
    }
    cout << "temperature[0][0] " << var[0][0] << endl;
  }

// 4. c++ vector, single length and computed index offset
// 5. c++ vector of vectors for 2D.
// 6. YAKL arrays

}
