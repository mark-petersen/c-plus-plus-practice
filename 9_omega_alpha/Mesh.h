#ifndef MESH_H
#define MESH_H

#include <vector>
#include <string>

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
    std::vector <double> latCell;
    std::vector <double> lonCell;
    std::vector <double> xCell;
    std::vector <double> yCell;
    std::vector <double> zCell;
    std::vector <double> latEdge;
    std::vector <double> lonEdge;
    std::vector <double> xEdge;
    std::vector <double> yEdge;
    std::vector <double> zEdge;
    std::vector <double> latVertex;
    std::vector <double> lonVertex;
    std::vector <double> xVertex;
    std::vector <double> yVertex;
    std::vector <double> zVertex;
    std::vector <double> areaCell;
    std::vector <double> angleEdge;
    std::vector <double> dcEdge;
    std::vector <double> dvEdge;
    std::vector <double> areaTriangle;
    std::vector <double> meshDensity;
    std::vector <int> indexToCellID;
    std::vector <int> indexToEdgeID;
    std::vector <int> indexToVertexID;
    std::vector <int> nEdgesOnCell;
    std::vector <int> nEdgesOnEdge;
    std::vector <int> cellsOnCell;
    std::vector <int> edgesOnCell;
    std::vector <int> verticesOnCell;
    std::vector <int> edgesOnEdge;
    std::vector <int> cellsOnEdge;
    std::vector <int> verticesOnEdge;
    std::vector <int> cellsOnVertex;
    std::vector <int> edgesOnVertex;
    // mesh quality variables. Not in init file.
    //std::vector <double> cellQuality;
    //std::vector <double> gridSpacing;
    //std::vector <double> triangleQuality;
    //std::vector <double> triangleAngleQuality;
    //std::vector <int> boundaryVertex;
    //std::vector <int> obtuseTriangle;

    // mesh variables that are computed on start-up
    std::vector <signed char> edgeSignOnCell;
  
    // constructor
    Mesh(Config &config);
};
#endif
