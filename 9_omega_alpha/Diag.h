#ifndef DIAG_H
#define DIAG_H

#include <vector>
#include <string>
#include "State.h"
#include "Diag.h"

class Diag {
  public:
  
    // Diagnostic variables
    std::vector <double> tangentialVelocity; // type="real" dimensions="nVertLevels nEdges Time" units="m s^-1" description="horizontal velocity, tangential to an edge"
    std::vector <double> layerThicknessEdgeMean; // type="real" dimensions="nVertLevels nEdges Time" units="m" description="layer thickness averaged from cell center to edges"
    std::vector <double> layerThicknessEdgeFlux; // type="real" dimensions="nVertLevels nEdges Time" units="m" description="layer thickness used for fluxes through edges. May be centered, upwinded, or a combination of the two."
    std::vector <double> layerThicknessVertex; // type="real" dimensions="nVertLevels nVertices Time" units="m" description="layer thickness averaged from cell center to vertices"

    std::vector <double> kineticEnergyCell; // type="real" dimensions="nVertLevels nCells Time" units="m^2 s^-2" description="kinetic energy of horizontal velocity on cells"
    std::vector <double> divergence; // type="real" dimensions="nVertLevels nCells Time" units="s^-1" description="divergence of horizontal velocity"
    std::vector <double> circulation; // type="real" dimensions="nVertLevels nVertices Time" units="m^2 s^-1" description="area-integrated vorticity"
    std::vector <double> relativeVorticity; // type="real" dimensions="nVertLevels nVertices Time" units="s^-1" description="curl of horizontal velocity, defined at vertices"
    std::vector <double> relativeVorticityCell; // type="real" dimensions="nVertLevels nCells Time" units="s^-1" description="curl of horizontal velocity, averaged from vertices to cell centers"
    std::vector <double> normalizedRelativeVorticityEdge; // type="real" dimensions="nVertLevels nEdges Time" units="s^-1" description="curl of horizontal velocity divided by layer thickness, averaged from vertices to edges"
    std::vector <double> normalizedPlanetaryVorticityEdge; // type="real" dimensions="nVertLevels nEdges Time" units="s^-1" description="earth's rotational rate (Coriolis parameter, f) divided by layer thickness, averaged from vertices to edges"
    std::vector <double> normalizedRelativeVorticityCell; // type="real" dimensions="nVertLevels nCells Time" units="s^-1" description="curl of horizontal velocity divided by layer thickness, averaged from vertices to cell centers"

    // for later:
    //string xtime; // type="text" dimensions="Time" description="model time, with format 'YYYY-MM-DD_HH:MM:SS'"
    //string simulationStartTime; // type="text" dimensions="" default_value="'no_date_available'" description="start time of first simulation, with format 'YYYY-MM-DD_HH:MM:SS'"
    //double daysSinceStartOfSim; // type="real" dimensions="Time" units="days" description="Time since simulationStartTime, for plotting"

    //std::vector <double> viscosity; // type="real" dimensions="nVertLevels nEdges Time" units="m^2 s^-1" description="horizontal viscosity"

    // constructor
    //Diag(state &s);
};
#endif
