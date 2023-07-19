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

int main()
{
   // These arrays will store coordinates
   //float xCell[nCells], yCell[nCells];
   
   // These arrays will hold the data we will read in. We will only
   // need enough space to hold one timestep of data; one record.
   //float temperature[nVertLevels][nCells];
   
   try
   {
   // Open the file.
     NcFile dataFile("mpas_mesh_16x16.nc", NcFile::read);

   int nCells = dataFile.getDim("nCells").getSize();
   int nEdges = dataFile.getDim("nEdges").getSize();
   int nVertices = dataFile.getDim("nVertices").getSize();
   
   float xCell[nCells]; dataFile.getVar("xCell").getVar(xCell);

   float yCell[nCells];
   string varName = "yCellxxx";
   tempVar = dataFile.getVar(varName);
   if(tempVar.isNull()) {
       cout << varName << " not found in file" << endl;
       return NC_ERR;
   } else {
       tempVar.getVar(yCell);
   }

   tempVar = dataFile.getVar(varName);
   if(tempVar.isNull()) { return NC_ERR; } else { tempVar.getVar(yCell); }

   cout << "xCell" << endl;
   for (int iCell = 0; iCell < nCells; iCell++)
      cout << xCell[iCell]<< ", ";
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
	     if(pres_in[lvl][xCell][yCell] != (float) (SAMPLE_PRESSURE + i)) return NC_ERR;
	     if(temp_in[lvl][xCell][yCell] != (float)(SAMPLE_TEMP + i++)) return NC_ERR;
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

void readVar(string varName, float *var) {
   NcVar tempVar;
   tempVar = dataFile.getVar(varName);
   if(tempVar.isNull()) {
       cout << "Warning: " <<  varName << " not found in file" << endl;
   } else {
       tempVar.getVar(var);
   }
}
