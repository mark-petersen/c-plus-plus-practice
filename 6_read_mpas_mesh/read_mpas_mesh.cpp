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

static const bool verbose = true;

// Dimensions
//static const int nCells = 256;

// Return this code to the OS in case of failure.
static const int NC_ERR = 2;

template <typename varType>
void printArray(string varName, varType var[], int varSize);

template <typename varType>
void read1DArray(NcFile& dataFile, string varName, varType var[]);

void read2DArrayInt(NcFile& dataFile, string varName, int**& var, int dim1, int dim2);
void read2DArrayDouble(NcFile& dataFile, string varName, double**& var, int dim1, int dim2);

class MpasMesh {
  public:
    int nCells;
    int nEdges;
    int nVertices;
    int maxEdges;
    int maxEdges2;
    int vertexDegree;

    double* latCell;
    double* lonCell;
    double* xCell;
    double* yCell;
    double* zCell;
    double* latEdge;
    double* lonEdge;
    double* xEdge;
    double* yEdge;
    double* zEdge;
    double* latVertex;
    double* lonVertex;
    double* xVertex;
    double* yVertex;
    double* zVertex;
    double* areaCell;
    double* angleEdge;
    double* dcEdge;
    double* dvEdge;
    double* areaTriangle;
    double* cellQuality;
    double* gridSpacing;
    double* triangleQuality;
    double* triangleAngleQuality;
    double* meshDensity;

    int* indexToCellID;
    int* indexToEdgeID;
    int* indexToVertexID;
    int* nEdgesOnCell;
    int* nEdgesOnEdge;
    int* boundaryVertex;
    int* obtuseTriangle;

    // using this format for 2D arrays because I couldn't get template to work. This produces no error message if variable is missing.
    int** cellsOnCell;
    int** edgesOnCell;
    int** verticesOnCell;
    int** edgesOnEdge;
    int** cellsOnEdge;
    int** verticesOnEdge;
    int** cellsOnVertex;
    int** edgesOnVertex;
    double** weightsOnEdge;
    double** kiteAreasOnVertex;

    // constructor
    MpasMesh(string meshFileName) {
      NcFile dataFile(meshFileName, NcFile::read);

      nCells = dataFile.getDim("nCells").getSize();
      nEdges = dataFile.getDim("nEdges").getSize();
      nVertices = dataFile.getDim("nVertices").getSize();
      maxEdges = dataFile.getDim("maxEdges").getSize();
      maxEdges2 = dataFile.getDim("maxEdges2").getSize();
      vertexDegree = dataFile.getDim("vertexDegree").getSize();

   latCell = new double[nCells]; read1DArray(dataFile, "latCell", latCell);
   lonCell = new double[nCells]; read1DArray(dataFile, "lonCell", lonCell);
   xCell = new double[nCells]; read1DArray(dataFile, "xCell", xCell);
   yCell = new double[nCells]; read1DArray(dataFile, "yCell", yCell);
   zCell = new double[nCells]; read1DArray(dataFile, "zCell", zCell);
   latEdge = new double[nEdges]; read1DArray(dataFile, "latEdge", latEdge);
   lonEdge = new double[nEdges]; read1DArray(dataFile, "lonEdge", lonEdge);
   xEdge = new double[nEdges]; read1DArray(dataFile, "xEdge", xEdge);
   yEdge = new double[nEdges]; read1DArray(dataFile, "yEdge", yEdge);
   zEdge = new double[nEdges]; read1DArray(dataFile, "zEdge", zEdge);
   latVertex = new double[nVertices]; read1DArray(dataFile, "latVertex", latVertex);
   lonVertex = new double[nVertices]; read1DArray(dataFile, "lonVertex", lonVertex);
   xVertex = new double[nVertices]; read1DArray(dataFile, "xVertex", xVertex);
   yVertex = new double[nVertices]; read1DArray(dataFile, "yVertex", yVertex);
   zVertex = new double[nVertices]; read1DArray(dataFile, "zVertex", zVertex);
   areaCell = new double[nCells]; read1DArray(dataFile, "areaCell", areaCell);
   angleEdge = new double[nEdges]; read1DArray(dataFile, "angleEdge", angleEdge);
   dcEdge = new double[nEdges]; read1DArray(dataFile, "dcEdge", dcEdge);
   dvEdge = new double[nEdges]; read1DArray(dataFile, "dvEdge", dvEdge);
   areaTriangle = new double[nVertices]; read1DArray(dataFile, "areaTriangle", areaTriangle);
   cellQuality = new double[nCells]; read1DArray(dataFile, "cellQuality", cellQuality);
   gridSpacing = new double[nCells]; read1DArray(dataFile, "gridSpacing", gridSpacing);
   triangleQuality = new double[nVertices]; read1DArray(dataFile, "triangleQuality", triangleQuality);
   triangleAngleQuality = new double[nVertices]; read1DArray(dataFile, "triangleAngleQuality", triangleAngleQuality);
   meshDensity = new double[nCells]; read1DArray(dataFile, "meshDensity", meshDensity);
   read2DArrayDouble(dataFile, "weightsOnEdge", weightsOnEdge, nEdges, maxEdges2);
   read2DArrayDouble(dataFile, "kiteAreasOnVertex", kiteAreasOnVertex, nEdges, maxEdges2);
   //read2DArrayInt(dataFile, "", , , );

   indexToCellID = new int[nCells]; read1DArray(dataFile, "indexToCellID", indexToCellID);
   indexToEdgeID = new int[nEdges]; read1DArray(dataFile, "indexToEdgeID", indexToEdgeID);
   indexToVertexID = new int[nVertices]; read1DArray(dataFile, "indexToVertexID", indexToVertexID);
   nEdgesOnCell = new int[nCells]; read1DArray(dataFile, "nEdgesOnCell", nEdgesOnCell);
   nEdgesOnEdge = new int[nEdges]; read1DArray(dataFile, "nEdgesOnEdge", nEdgesOnEdge);
   boundaryVertex = new int[nVertices]; read1DArray(dataFile, "boundaryVertex", boundaryVertex);
   obtuseTriangle = new int[nVertices]; read1DArray(dataFile, "obtuseTriangle", obtuseTriangle);

   read2DArrayInt(dataFile, "cellsOnCell", cellsOnCell, nCells, maxEdges);
   read2DArrayInt(dataFile, "edgesOnCell", edgesOnCell, nCells, maxEdges);
   read2DArrayInt(dataFile, "verticesOnCell", verticesOnCell, nCells, maxEdges);
   read2DArrayInt(dataFile, "edgesOnEdge", edgesOnEdge, nEdges, maxEdges2);
   read2DArrayInt(dataFile, "cellsOnEdge", cellsOnEdge, nEdges, 2);
   read2DArrayInt(dataFile, "verticesOnEdge", verticesOnEdge, nEdges, 2);
   read2DArrayInt(dataFile, "cellsOnVertex", cellsOnVertex, nVertices, vertexDegree);
   read2DArrayInt(dataFile, "edgesOnVertex", edgesOnVertex, nVertices, vertexDegree);

   }
};

int main()
{
   
   try
   {
   // Open the file.
  MpasMesh m("mpas_mesh_16x16.nc");
  cout << "xCell[0]: " << m.xCell[0] << endl;
  cout << "cellsOnEdge[0]: " << m.cellsOnEdge[0][0] << endl;
 for (int i = 0; i < 3; i++) {
    cout << m.weightsOnEdge[i][0] << "  " << m.weightsOnEdge[i][1] << endl;
 }
  // NcFile dataFile("mdpas_mesh_16x16.nc", NcFile::read);

   
   //printArray("yCell",yCell,nCells);
   //printArray("areaCell",areaCell,nCells);
  
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
void read1DArray(NcFile& dataFile, string varName, varType var[]) {
   NcVar tempVar;
   tempVar = dataFile.getVar(varName);
   if(tempVar.isNull()) {
       cout << "Warning: " <<  varName << " was not found in file" << endl;
   } else {
       tempVar.getVar(var);
   }
}

void read2DArrayDouble(NcFile& dataFile, string varName, double**& var, int dim1, int dim2) {
  if (verbose) cout << "read2DArrayDouble: var=" << varName << endl;
  var = new double*[dim1];
  for (int i=0; i<dim1; i++) var[i] = new double[dim2];
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
}

void read2DArrayInt(NcFile& dataFile, string varName, int**& var, int dim1, int dim2) {
  if (verbose) cout << "read2DArrayInt: var=" << varName << endl;
  var = new int*[dim1];
  for (int i=0; i<dim1; i++) var[i] = new int[dim2];
  NcVar tempVar;
  tempVar = dataFile.getVar(varName);
  if(tempVar.isNull()) {
    cout << "Warning: " <<  varName << " was not found in file" << endl;
  } else {
    int tempArray[dim1][dim2];
    tempVar.getVar(tempArray);
    for (int i = 0; i < dim1; i++) {
      for (int j = 0; j < dim2; j++) {
        var[i][j] = tempArray[i][j];
      }
    }
  }
}

// does not work. Try later
//template <typename varType, int row, int column>
//void read1DArray(NcFile& dataFile, string varName, varType (var)[row][column]) {
//   NcVar tempVar;
//   tempVar = dataFile.getVar(varName);
//   if(tempVar.isNull()) {
//       cout << "Warning: " <<  varName << " was not found in file" << endl;
//   } else {
//       tempVar.getVar(var);
//   }
//}
