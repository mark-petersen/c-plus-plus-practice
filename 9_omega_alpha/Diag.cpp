#include <vector>
#include "Config.h"
#include "Mesh.h"
#include "State.h"
#include "Diag.h"

// constructor
Diag::Diag(Mesh &m) {
    LOG(4,"-> Diag::Diag")

    tangentialVelocity.resize(m.nEdges * m.nVertLevels, -1.0e32); // type="real" dimensions="nVertLevels nEdges Time" units="m s^-1" description="horizontal velocity, tangential to an edge"
    layerThicknessEdgeMean.resize(m.nEdges * m.nVertLevels, -1.0e32); // type="real" dimensions="nVertLevels nEdges Time" units="m" description="layer thickness averaged from cell center to edges"
    layerThicknessEdgeFlux.resize(m.nEdges * m.nVertLevels, -1.0e32); // type="real" dimensions="nVertLevels nEdges Time" units="m" description="layer thickness used for fluxes through edges. May be centered, upwinded, or a combination of the two."
    layerThicknessVertex.resize(m.nVertices * m.nVertLevels, -1.0e32); // type="real" dimensions="nVertLevels nVertices Time" units="m" description="layer thickness averaged from cell center to vertices"
    kineticEnergyCell.resize(m.nCells * m.nVertLevels, -1.0e32); // type="real" dimensions="nVertLevels nCells Time" units="m^2 s^-2" description="kinetic energy of horizontal velocity on cells"
    divergence.resize(m.nCells * m.nVertLevels, -1.0e32); // type="real" dimensions="nVertLevels nCells Time" units="s^-1" description="divergence of horizontal velocity"
    circulation.resize(m.nVertices * m.nVertLevels, -1.0e32); // type="real" dimensions="nVertLevels nVertices Time" units="m^2 s^-1" description="area-integrated vorticity"
    relativeVorticity.resize(m.nVertices * m.nVertLevels, -1.0e32); // type="real" dimensions="nVertLevels nVertices Time" units="s^-1" description="curl of horizontal velocity, defined at vertices"
    relativeVorticityCell.resize(m.nCells * m.nVertLevels, -1.0e32); // type="real" dimensions="nVertLevels nCells Time" units="s^-1" description="curl of horizontal velocity, averaged from vertices to cell centers"
    normalizedRelativeVorticityEdge.resize(m.nEdges * m.nVertLevels, -1.0e32); // type="real" dimensions="nVertLevels nEdges Time" units="s^-1" description="curl of horizontal velocity divided by layer thickness, averaged from vertices to edges"
    normalizedPlanetaryVorticityEdge.resize(m.nEdges * m.nVertLevels, -1.0e32); // type="real" dimensions="nVertLevels nEdges Time" units="s^-1" description="earth's rotational rate (Coriolis parameter, f) divided by layer thickness, averaged from vertices to edges"
    normalizedRelativeVorticityCell.resize(m.nCells * m.nVertLevels, -1.0e32); // type="real" dimensions="nVertLevels nCells Time" units="s^-1" description="curl of horizontal velocity divided by layer thickness, averaged from vertices to cell centers"

}

void Diag::compute(Config &config, Mesh &m, State &s) {
    LOG(4,"-> Diag::compute")

    //tangentialVelocity
    //layerThicknessEdgeMean
    //layerThicknessEdgeFlux
    //layerThicknessVertex
    //kineticEnergyCell
    //divergence
    //circulation
    //relativeVorticity
    //relativeVorticityCell
    //normalizedRelativeVorticityEdge
    //normalizedPlanetaryVorticityEdge
    //normalizedRelativeVorticityCell

}
