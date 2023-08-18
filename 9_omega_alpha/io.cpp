// Using netcdf-c version of the netcdf libraries, and all 
// arrays are c++ vector containers, 1D with computed index offset

#include <iostream>
#include <string>
#include <netcdf>
#include <vector>
#include "config.h"
#include "io.h"

using namespace std;

vector <int> readNCInt(int ncid, string varName, size_t dim) {
  int varid, retval;
  vector <int> var;
  var.resize(dim);
  if (config::verbose) cout << varName << ": ";
  if ((retval = nc_inq_varid(ncid, varName.c_str(), &varid))) ERR(retval);
  if ((retval = nc_get_var_int(ncid, varid, &var[0]))) ERR(retval);
  if (config::verbose) cout << var[0] << ", " << var[dim-1] << endl;
  return var;
}

vector <double> readNCDouble(int ncid, string varName, size_t dim) {
  int varid, retval;
  vector <double> var;
  var.resize(dim);
  if (config::verbose) cout << varName << ": ";
  if ((retval = nc_inq_varid(ncid, varName.c_str(), &varid))) ERR(retval);
  if ((retval = nc_get_var_double(ncid, varid, &var[0]))) ERR(retval);
  if (config::verbose) cout << var[0] << ", " << var[dim-1] << endl;
  return var;
}

void fillNCDouble(int ncid, string varName, vector <double> &var) {
  int varid, retval;
  if (config::verbose) cout << varName << ": ";
  if ((retval = nc_inq_varid(ncid, varName.c_str(), &varid))) ERR(retval);
  if ((retval = nc_get_var_double(ncid, varid, &var[0]))) ERR(retval);
  if (config::verbose) cout << var[0] << ", " << var[1] << endl;
}

size_t readNCDim(int ncid, string dimName) {
  int dimid, retval;
  size_t dim;
  if (config::verbose) cout << dimName << ": ";
  if ((retval = nc_inq_dimid(ncid, dimName.c_str(), &dimid) )) ERR(retval);
  if ((retval = nc_inq_dimlen(ncid, dimid, &dim) )) ERR(retval);
  if (config::verbose) cout << dim << endl;
  return dim;
}
