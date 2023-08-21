#ifndef IO_H
#define IO_H

#include <netcdf>
#include <string>
#include <vector>

/* Handle errors by printing an error message and exiting with a
 * non-zero status. */
#define ERRCODE 2
#define ERR(e) {printf("Error: %s\n", nc_strerror(e)); exit(ERRCODE);}
#define PRINT(message) {if (verbose) std::cout << message << std::endl;}
#define NEWLINE {if (verbose) std::cout << std::endl;}

size_t readNCDim(int ncid, std::string dimName);
std::vector <int> readNCInt(int ncid, std::string varName, size_t dim);
std::vector <double> readNCDouble(int ncid, std::string varName, size_t dim);
void fillNCDouble(int ncid, std::string varName, std::vector <double> &var);

#endif
