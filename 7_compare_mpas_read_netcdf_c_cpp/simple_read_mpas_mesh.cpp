/* 
   to make meshes:
   planar_hex --nx 16 --ny 16 --dc 64000 -o base_mesh_16x16.nc
   MpasMeshConverter.x base_mesh_16x16.nc mpas_mesh_16x16.nc
*/

#include <iostream>
#include <netcdf>
using namespace std;
using namespace netCDF;

int main()
{
   NcFile dataFile("mpas_mesh_16x16.nc", NcFile::read);
   int nCells = dataFile.getDim("nCells").getSize();
   double xCell[nCells]; dataFile.getVar("xCell").getVar(xCell);
   cout << "xCell[0]: " << xCell[0] << endl;
}
