#ifndef DIAG_H
#define DIAG_H

#include <vector>
#include <string>
#include "State.h"
#include "Diag.h"
using namespace std;

class Diag {
  public:
  
    // Diagnostic variables
    vector <double> tangentialVelocity; // type="real" dimensions="nVertLevels nEdges Time" units="m s^-1" description="horizontal velocity, tangential to an edge"
    vector <double> layerThicknessEdgeMean; // type="real" dimensions="nVertLevels nEdges Time" units="m" description="layer thickness averaged from cell center to edges"
    vector <double> layerThicknessEdgeFlux; // type="real" dimensions="nVertLevels nEdges Time" units="m" description="layer thickness used for fluxes through edges. May be centered, upwinded, or a combination of the two."
    vector <double> layerThicknessVertex; // type="real" dimensions="nVertLevels nVertices Time" units="m" description="layer thickness averaged from cell center to vertices"

    vector <double> kineticEnergyCell; // type="real" dimensions="nVertLevels nCells Time" units="m^2 s^-2" description="kinetic energy of horizontal velocity on cells"
    vector <double> divergence; // type="real" dimensions="nVertLevels nCells Time" units="s^-1" description="divergence of horizontal velocity"
    vector <double> circulation; // type="real" dimensions="nVertLevels nVertices Time" units="m^2 s^-1" description="area-integrated vorticity"
    vector <double> relativeVorticity; // type="real" dimensions="nVertLevels nVertices Time" units="s^-1" description="curl of horizontal velocity, defined at vertices"
    vector <double> relativeVorticityCell; // type="real" dimensions="nVertLevels nCells Time" units="s^-1" description="curl of horizontal velocity, averaged from vertices to cell centers"
    vector <double> normalizedRelativeVorticityEdge; // type="real" dimensions="nVertLevels nEdges Time" units="s^-1" description="curl of horizontal velocity divided by layer thickness, averaged from vertices to edges"
    vector <double> normalizedPlanetaryVorticityEdge; // type="real" dimensions="nVertLevels nEdges Time" units="s^-1" description="earth's rotational rate (Coriolis parameter, f) divided by layer thickness, averaged from vertices to edges"
    vector <double> normalizedRelativeVorticityCell; // type="real" dimensions="nVertLevels nCells Time" units="s^-1" description="curl of horizontal velocity divided by layer thickness, averaged from vertices to cell centers"

    // for later:
    //string xtime; // type="text" dimensions="Time" description="model time, with format 'YYYY-MM-DD_HH:MM:SS'"
    //string simulationStartTime; // type="text" dimensions="" default_value="'no_date_available'" description="start time of first simulation, with format 'YYYY-MM-DD_HH:MM:SS'"
    //double daysSinceStartOfSim; // type="real" dimensions="Time" units="days" description="Time since simulationStartTime, for plotting"

    //vector <double> viscosity; // type="real" dimensions="nVertLevels nEdges Time" units="m^2 s^-1" description="horizontal viscosity"

    // constructor
    Diag(state s);
};
#endif
