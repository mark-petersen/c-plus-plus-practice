/* 
   to make meshes:
   planar_hex --nx 16 --ny 16 --dc 64000 -o base_mesh_16x16.nc
   MpasMeshConverter.x base_mesh_16x16.nc mpas_mesh_16x16.nc
*/

#include <iostream>
#include <string>
#include <netcdf>
#include <array>
#include <vector>

using namespace std;
using namespace netCDF;

string dirName = "links_su/";
string fileName = "ocean.QU.240km.151209.nc";
//string fileName = "EC30to60E2r3_mocBasinsAndTransects20210623.nc";
//string fileName = "oRRS18to6v3.171116.nc.nc";
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

/* Handle errors by printing an error message and exiting with a
 * non-zero status. */
#define ERRCODE 2
#define ERR(e) {printf("Error: %s\n", nc_strerror(e)); exit(ERRCODE);}

int main()
{
  /* Open the file */
  // netcdf-c version:
  int ncid, varid, retval;
  if ((retval = nc_open((dirName + fileName).c_str(), NC_NOWRITE, &ncid)))
      ERR(retval);
  // netcdf c++ version:
  NcFile dataFile(dirName + fileName, NcFile::read);

  //int nCells = dataFile.getDim("nCells").getSize();
  double xCell[nCells];

  /* Read the data. */
  // netcdf-c version:
  /* Get the varid of the data variable, based on its name. */
   if ((retval = nc_inq_varid(ncid, "xCell", &varid))) ERR(retval);
   if ((retval = nc_get_var_double(ncid, varid, &xCell[0]))) ERR(retval);
  // netcdf c++ version:
  //dataFile.getVar("xCell").getVar(xCell);

  cout << "xCell[0]: " << xCell[0] << endl;

  constexpr size_t dim1=nCells;
  constexpr size_t dim2=nVertLevels;
  string varName = "temperature";
  {
    cout << "1. C arrays with fixed size   ";
    double temperature[nCells][nVertLevels];
    // netcdf-c version:
    if ((retval = nc_inq_varid(ncid, "temperature", &varid))) ERR(retval);
    if ((retval = nc_get_var_double(ncid, varid, &temperature[0][0]))) ERR(retval);
    // netcdf c++ version:
    //  dataFile.getVar("temperature").getVar(temperature);
    cout << "temperature[200][20] " << temperature[200][20] << endl;
  }
  {
    cout << "2. C arrays with ** and new (variable dim)  ";
    double** var;
    var = new double*[dim1];
    for (int i=0; i<dim1; i++) var[i] = new double[dim2];

    double tempArray[dim1][dim2];
    if ((retval = nc_inq_varid(ncid, varName.c_str(), &varid))) ERR(retval);
    if ((retval = nc_get_var_double(ncid, varid, &tempArray[0][0]))) ERR(retval);
    for (int i = 0; i < dim1; i++) {
      for (int j = 0; j < dim2; j++) {
        var[i][j] = tempArray[i][j];
      }
    }
    cout << "temperature[200][20] " << var[200][20] << endl;
  }
  {
    cout << "3. c++ array object (fixed dim)    var";
    array < array<double, dim2>, dim1 > var;

    double tempArray[dim1][dim2];
    if ((retval = nc_inq_varid(ncid, varName.c_str(), &varid))) ERR(retval);
    if ((retval = nc_get_var_double(ncid, varid, &tempArray[0][0]))) ERR(retval);
    for (int i = 0; i < dim1; i++) {
      for (int j = 0; j < dim2; j++) {
        var[i][j] = tempArray[i][j];
      }
    }
    cout << "temperature[200][20] " << var[200][20] << endl;
  }
  {
    cout << "4. c++ vector, single length and computed index offset";
    vector <double> var;
    var.resize(dim1*dim2);

    if ((retval = nc_inq_varid(ncid, varName.c_str(), &varid))) ERR(retval);
    if ((retval = nc_get_var_double(ncid, varid, &var[0]))) ERR(retval);
    cout << "temperature[200*d2+20] " << var[200*dim2+20] << endl;
  }
  {
    cout << "5. c++ vector of vectors for 2D";
    vector <double> var;
    var.resize(dim1*dim2);

    double tempArray[dim1][dim2];
    if ((retval = nc_inq_varid(ncid, varName.c_str(), &varid))) ERR(retval);
    if ((retval = nc_get_var_double(ncid, varid, &tempArray[0][0]))) ERR(retval);
    for (int i = 0; i < dim1; i++) {
      for (int j = 0; j < dim2; j++) {
        var[i*dim2 + j] = tempArray[i][j];
      }
    }
    cout << "temperature[200*d2+20] " << var[200*dim2+20] << endl;
  }

}
