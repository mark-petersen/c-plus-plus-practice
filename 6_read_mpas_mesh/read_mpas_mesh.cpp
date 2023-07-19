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

template <typename varType>
void printArray(string varName, varType var[], int varSize);

template <typename varType>
void readArray(NcFile& dataFile, string varName, varType var[]);

// does not work. Try again later
// template <typename varType, size_t row, size_t column>
// void readArray(NcFile& dataFile, string varName, varType (var)[row][column]);

int main()
{
   
   try
   {
   // Open the file.
   NcFile dataFile("mdpas_mesh_16x16.nc", NcFile::read);

   int nCells = dataFile.getDim("nCells").getSize();
   int nEdges = dataFile.getDim("nEdges").getSize();
   int nVertices = dataFile.getDim("nVertices").getSize();
   int maxEdges = dataFile.getDim("maxEdges").getSize();
   int maxEdges2 = dataFile.getDim("maxEdges2").getSize();
   int vertexDegree = dataFile.getDim("vertexDegree").getSize();
   
   double latCell[nCells]; readArray(dataFile, "latCell", latCell);
   double lonCell[nCells]; readArray(dataFile, "lonCell", lonCell);
   double xCell[nCells]; readArray(dataFile, "xCell", xCell);
   double yCell[nCells]; readArray(dataFile, "yCell", yCell);
   double zCell[nCells]; readArray(dataFile, "zCell", zCell);
   double latEdge[nEdges]; readArray(dataFile, "latEdge", latEdge);
   double lonEdge[nEdges]; readArray(dataFile, "lonEdge", lonEdge);
   double xEdge[nEdges]; readArray(dataFile, "xEdge", xEdge);
   double yEdge[nEdges]; readArray(dataFile, "yEdge", yEdge);
   double zEdge[nEdges]; readArray(dataFile, "zEdge", zEdge);
   double latVertex[nVertices]; readArray(dataFile, "latVertex", latVertex);
   double lonVertex[nVertices]; readArray(dataFile, "lonVertex", lonVertex);
   double xVertex[nVertices]; readArray(dataFile, "xVertex", xVertex);
   double yVertex[nVertices]; readArray(dataFile, "yVertex", yVertex);
   double zVertex[nVertices]; readArray(dataFile, "zVertex", zVertex);
   double areaCell[nCells]; readArray(dataFile, "areaCell", areaCell);
   double angleEdge[nEdges]; readArray(dataFile, "angleEdge", angleEdge);
   double dcEdge[nEdges]; readArray(dataFile, "dcEdge", dcEdge);
   double dvEdge[nEdges]; readArray(dataFile, "dvEdge", dvEdge);
   double areaTriangle[nVertices]; readArray(dataFile, "areaTriangle", areaTriangle);
   double cellQuality[nCells]; readArray(dataFile, "cellQuality", cellQuality);
   double gridSpacing[nCells]; readArray(dataFile, "gridSpacing", gridSpacing);
   double triangleQuality[nVertices]; readArray(dataFile, "triangleQuality", triangleQuality);
   double triangleAngleQuality[nVertices]; readArray(dataFile, "triangleAngleQuality", triangleAngleQuality);
   double meshDensity[nCells]; readArray(dataFile, "meshDensity", meshDensity);

   int indexToCellID[nCells]; readArray(dataFile, "indexToCellID", indexToCellID);
   int indexToEdgeID[nEdges]; readArray(dataFile, "indexToEdgeID", indexToEdgeID);
   int indexToVertexID[nVertices]; readArray(dataFile, "indexToVertexID", indexToVertexID);
   int nEdgesOnCell[nCells]; readArray(dataFile, "nEdgesOnCell", nEdgesOnCell);
   int nEdgesOnEdge[nEdges]; readArray(dataFile, "nEdgesOnEdge", nEdgesOnEdge);
   int boundaryVertex[nVertices]; readArray(dataFile, "boundaryVertex", boundaryVertex);
   int obtuseTriangle[nVertices]; readArray(dataFile, "obtuseTriangle", obtuseTriangle);

   // using this format for 2D arrays because I couldn't get template to work. This produces no error message if variable is missing.
   double weightsOnEdge[nEdges][maxEdges2]; dataFile.getVar("weightsOnEdge").getVar(weightsOnEdge);
   double kiteAreasOnVertex[nEdges][maxEdges2]; dataFile.getVar("kiteAreasOnVertex").getVar(kiteAreasOnVertex);
   int cellsOnCell[nCells][maxEdges]; dataFile.getVar("cellsOnCell").getVar(cellsOnCell);
   int edgesOnCell[nCells][maxEdges]; dataFile.getVar("edgesOnCell").getVar(edgesOnCell);
   int verticesOnCell[nCells][maxEdges]; dataFile.getVar("verticesOnCell").getVar(verticesOnCell);
   int edgesOnEdge[nEdges][maxEdges2]; dataFile.getVar("edgesOnEdge").getVar(edgesOnEdge);
   int cellsOnEdge[nEdges][2]; dataFile.getVar("cellsOnEdge").getVar(cellsOnEdge);
   int verticesOnEdge[nEdges][2]; dataFile.getVar("verticesOnEdge").getVar(verticesOnEdge);
   int cellsOnVertex[nVertices][vertexDegree]; dataFile.getVar("cellsOnVertex").getVar(cellsOnVertex);
   int edgesOnVertex[nVertices][vertexDegree]; dataFile.getVar("edgesOnVertex").getVar(edgesOnVertex);

   printArray("yCell",yCell,nCells);
   printArray("areaCell",areaCell,nCells);
  
  /*
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

template <typename varType>
void printArray(string varName, varType var[], int varSize) {
   cout << varName << endl;
   for (int j = 0; j < varSize; j++)
      cout << var[j]<< ", ";
   cout << endl;
}

template <typename varType>
void readArray(NcFile& dataFile, string varName, varType var[]) {
   NcVar tempVar;
   tempVar = dataFile.getVar(varName);
   if(tempVar.isNull()) {
       cout << "Warning: " <<  varName << " was not found in file" << endl;
   } else {
       tempVar.getVar(var);
   }
}

// does not work. Try later
//template <typename varType, int row, int column>
//void readArray(NcFile& dataFile, string varName, varType (var)[row][column]) {
//   NcVar tempVar;
//   tempVar = dataFile.getVar(varName);
//   if(tempVar.isNull()) {
//       cout << "Warning: " <<  varName << " was not found in file" << endl;
//   } else {
//       tempVar.getVar(var);
//   }
//}
