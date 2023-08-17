#ifndef MESH_H
#define MESH_H

#include <vector>
#include <string>
using namespace std;

class Mesh {
  public:

    // MPAS dimensions
    size_t nCells;
    size_t nVertLevels;
    size_t nEdges;
    size_t nVertices;
    size_t maxEdges;
    size_t maxEdges2;
    size_t vertexDegree;
  
    // MPAS mesh variables
    vector <double> latCell;
    vector <double> lonCell;
    vector <double> xCell;
    vector <double> yCell;
    vector <double> zCell;
    vector <double> latEdge;
    vector <double> lonEdge;
    vector <double> xEdge;
    vector <double> yEdge;
    vector <double> zEdge;
    vector <double> latVertex;
    vector <double> lonVertex;
    vector <double> xVertex;
    vector <double> yVertex;
    vector <double> zVertex;
    vector <double> areaCell;
    vector <double> angleEdge;
    vector <double> dcEdge;
    vector <double> dvEdge;
    vector <double> areaTriangle;
    vector <double> meshDensity;
    vector <int> indexToCellID;
    vector <int> indexToEdgeID;
    vector <int> indexToVertexID;
    vector <int> nEdgesOnCell;
    vector <int> nEdgesOnEdge;
    vector <int> cellsOnCell;
    vector <int> edgesOnCell;
    vector <int> verticesOnCell;
    vector <int> edgesOnEdge;
    vector <int> cellsOnEdge;
    vector <int> verticesOnEdge;
    vector <int> cellsOnVertex;
    vector <int> edgesOnVertex;
    // mesh quality variables. Not in init file.
    //vector <double> cellQuality;
    //vector <double> gridSpacing;
    //vector <double> triangleQuality;
    //vector <double> triangleAngleQuality;
    //vector <int> boundaryVertex;
    //vector <int> obtuseTriangle;
  
    // state variables
    vector <double> temperature;
    vector <double> salinity;
    vector <double> layerThickness;

    // constructor
    Mesh();
};
#endif
