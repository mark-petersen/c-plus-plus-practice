/* 
   to make meshes:
   planar_hex --nx 16 --ny 16 --dc 64000 -o base_mesh_16x16.nc
   MpasMeshConverter.x base_mesh_16x16.nc mpas_mesh_16x16.nc
*/

#include <iostream>
#include <string>
#include <netcdf>
using namespace std;
using namespace netCDF;
using namespace netCDF::exceptions;

// Dimensions
//static const int nCells = 256;

// Return this code to the OS in case of failure.
static const int NC_ERR = 2;

void readVar(NcFile& dataFile, string varName, double var[]);

int main()
{
   // These arrays will store coordinates
   //double xCell[nCells], yCell[nCells];
   
   // These arrays will hold the data we will read in. We will only
   // need enough space to hold one timestep of data; one record.
   //double temperature[nVertLevels][nCells];
   
   try
   {
   // Open the file.
     NcFile dataFile("mpas_mesh_16x16.nc", NcFile::read);

   int nCells = dataFile.getDim("nCells").getSize();
   int nEdges = dataFile.getDim("nEdges").getSize();
   int nVertices = dataFile.getDim("nVertices").getSize();
   
   double latCell[nCells]; readVar(dataFile, "latCell", latCell);
   double lonCell[nCells]; readVar(dataFile, "lonCell", lonCell);
   double xCell[nCells]; readVar(dataFile, "xCell", xCell);
   double yCell[nCells]; readVar(dataFile, "yCell", yCell);
   double zCell[nCells]; readVar(dataFile, "zCell", zCell);
   double latEdge[nEdges]; readVar(dataFile, "latEdge", latEdge);
   double lonEdge[nEdges]; readVar(dataFile, "lonEdge", lonEdge);
   double xEdge[nEdges]; readVar(dataFile, "xEdge", xEdge);
   double yEdge[nEdges]; readVar(dataFile, "yEdge", yEdge);
   double zEdge[nEdges]; readVar(dataFile, "zEdge", zEdge);
   double latVertex[nVertices]; readVar(dataFile, "latVertex", latVertex);
   double lonVertex[nVertices]; readVar(dataFile, "lonVertex", lonVertex);
   double xVertex[nVertices]; readVar(dataFile, "xVertex", xVertex);
   double yVertex[nVertices]; readVar(dataFile, "yVertex", yVertex);
   double zVertex[nVertices]; readVar(dataFile, "zVertex", zVertex);
   double areaCell[nCells]; readVar(dataFile, "areaCell", areaCell);
   double angleEdge[nEdges]; readVar(dataFile, "angleEdge", angleEdge);
   double dcEdge[nEdges]; readVar(dataFile, "dcEdge", dcEdge);
   double dvEdge[nEdges]; readVar(dataFile, "dvEdge", dvEdge);
   double areaTriangle[nVertices]; readVar(dataFile, "areaTriangle", areaTriangle);
   double cellQuality[nCells]; readVar(dataFile, "cellQuality", cellQuality);
   double gridSpacing[nCells]; readVar(dataFile, "gridSpacing", gridSpacing);
   double triangleQuality[nVertices]; readVar(dataFile, "triangleQuality", triangleQuality);
   double triangleAngleQuality[nVertices]; readVar(dataFile, "triangleAngleQuality", triangleAngleQuality);
   double meshDensity[nCells]; readVar(dataFile, "meshDensity", meshDensity);
   // mrp need 2D array call for these
//   double weightsOnEdge[nEdges][maxEdges2]; readVar(dataFile, "weightsOnEdge", weightsOnEdge);
//   double kiteAreasOnVertex[nVertices][vertexDegree]; readVar(dataFile, "kiteAreasOnVertex", kiteAreasOnVertex);

   cout << "yCell" << endl;
   for (int iCell = 0; iCell < nCells; iCell++)
      cout << yCell[iCell]<< ", ";
   cout << endl;

/*
   // Check the coordinate variable data. 
       if (xCell[xCell] != START_LAT + 5. * xCell)
	 return NC_ERR;

   for (int yCell = 0; yCell < NLON; yCell++)
      if (yCell[yCell] != START_LON + 5. * yCell)
 	return NC_ERR;
  
   // Get the pressure and temperature variables and read data one time step at a time
   NcVar presVar, tempVar;
   presVar = dataFile.getVar("pressure");
   if(presVar.isNull()) return NC_ERR;
   tempVar = dataFile.getVar("temperature");
   if(tempVar.isNull()) return NC_ERR;

   vector<size_t> startp,countp;
   startp.push_back(0);
   startp.push_back(0);
   startp.push_back(0);
   startp.push_back(0);
   countp.push_back(1);
   countp.push_back(NLVL);
   countp.push_back(NLAT);
   countp.push_back(NLON);
   for (size_t rec = 0; rec < NREC; rec++)
   {
     // Read the data one record at a time.
     startp[0]=rec;
     presVar.getVar(startp,countp,pres_in);
     tempVar.getVar(startp,countp,temp_in);
     
     int i=0;  //used in the data generation loop
     for (int lvl = 0; lvl < NLVL; lvl++)
       for (int xCell = 0; xCell < NLAT; xCell++)
	 for (int yCell = 0; yCell < NLON; yCell++)
	   {
	     if(pres_in[lvl][xCell][yCell] != (double) (SAMPLE_PRESSURE + i)) return NC_ERR;
	     if(temp_in[lvl][xCell][yCell] != (double)(SAMPLE_TEMP + i++)) return NC_ERR;
	   }
     
   } // next record 
       
   // The file is automatically closed by the destructor. This frees
   // up any internal netCDF resources associated with the file, and
   // flushes any buffers.

   // cout << "*** SUCCESS reading example file pres_temp_4D.nc!" << endl;
   return 0;
   */

   }
   catch(NcException& e)
   {
      e.what();
      cout<<"FAILURE**************************"<<endl;
      return NC_ERR;
   }
  
}

void readVar(NcFile& dataFile, string varName, double var[]) {
   NcVar tempVar;
   tempVar = dataFile.getVar(varName);
   if(tempVar.isNull()) {
       cout << "Warning: " <<  varName << " was not found in file" << endl;
   } else {
       tempVar.getVar(var);
   }
}
