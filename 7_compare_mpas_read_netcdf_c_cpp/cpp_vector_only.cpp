// 4. c++ vector, single length and computed index offset
// netcdf-c version

#include <iostream>
#include <netcdf>
#include <string>
#include <vector>

using namespace std;

string dirName = "links_su/";
string fileName = "ocean.QU.240km.151209.nc";
// string fileName = "EC30to60E2r3_mocBasinsAndTransects20210623.nc";
// string fileName = "oRRS18to6v3.171116.nc.nc";

/* Handle errors by printing an error message and exiting with a
 * non-zero status. */
#define ERRCODE 2
#define ERR(e)                                                                 \
  {                                                                            \
    printf("Error: %s\n", nc_strerror(e));                                     \
    exit(ERRCODE);                                                             \
  }

int main() {
  /* Open the file */
  int ncid, varid, retval;
  if ((retval = nc_open((dirName + fileName).c_str(), NC_NOWRITE, &ncid)))
    ERR(retval);

  size_t nVertLevels;
  size_t nEdges;
  size_t nCells;
  size_t nVertices;
  size_t maxEdges;
  size_t maxEdges2;
  int dimid;

  if ((retval = nc_inq_dimid(ncid, "nCells", &dimid)))
    ERR(retval);
  if ((retval = nc_inq_dimlen(ncid, dimid, &nCells)))
    ERR(retval);

  if ((retval = nc_inq_dimid(ncid, "nVertLevels", &dimid)))
    ERR(retval);
  if ((retval = nc_inq_dimlen(ncid, dimid, &nVertLevels)))
    ERR(retval);

  /* Read the data. */
  double xCell[nCells];
  /* Get the varid of the data variable, based on its name. */
  if ((retval = nc_inq_varid(ncid, "xCell", &varid)))
    ERR(retval);
  if ((retval = nc_get_var_double(ncid, varid, &xCell[0])))
    ERR(retval);
  cout << "xCell[0]: " << xCell[0] << endl;

  cout << "4. c++ vector, single length and computed index offset";
  vector<double> var;
  int dim1 = nCells;
  int dim2 = nVertLevels;
  var.resize(dim1 * dim2);

  string varName = "temperature";
  /* Get the varid of the data variable, based on its name. */
  if ((retval = nc_inq_varid(ncid, varName.c_str(), &varid)))
    ERR(retval);
  if ((retval = nc_get_var_double(ncid, varid, &var[0])))
    ERR(retval);
  cout << " temperature[200*d2+20] " << var[200 * dim2 + 20] << endl;
}
