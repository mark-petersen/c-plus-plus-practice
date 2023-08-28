#include <vector>
#include "Config.h"
#include "Mesh.h"
#include "State.h"
#include "Diag.h"

// constructor
Diag::Diag(Mesh &m) {
    LOG(4,"-> Diag::Diag")

    tangentialVelocity.resize(m.nEdges * m.nVertLevels, -1.0e32); // type="real" dimensions="nVertLevels nEdges Time" units="m s^-1" description="horizontal velocity, tangential to an edge"
    kineticEnergyCell.resize(m.nCells * m.nVertLevels, -1.0e32); // type="real" dimensions="nVertLevels nCells Time" units="m^2 s^-2" description="kinetic energy of horizontal velocity on cells"
    divergence.resize(m.nCells * m.nVertLevels, -1.0e32); // type="real" dimensions="nVertLevels nCells Time" units="s^-1" description="divergence of horizontal velocity"
    relativeVorticity.resize(m.nVertices * m.nVertLevels, -1.0e32); // type="real" dimensions="nVertLevels nVertices Time" units="s^-1" description="curl of horizontal velocity, defined at vertices"

// unused for now:
//    relativeVorticityCell.resize(m.nCells * m.nVertLevels, -1.0e32); // type="real" dimensions="nVertLevels nCells Time" units="s^-1" description="curl of horizontal velocity, averaged from vertices to cell centers"
//    normalizedRelativeVorticityEdge.resize(m.nEdges * m.nVertLevels, -1.0e32); // type="real" dimensions="nVertLevels nEdges Time" units="s^-1" description="curl of horizontal velocity divided by layer thickness, averaged from vertices to edges"
//    normalizedPlanetaryVorticityEdge.resize(m.nEdges * m.nVertLevels, -1.0e32); // type="real" dimensions="nVertLevels nEdges Time" units="s^-1" description="earth's rotational rate (Coriolis parameter, f) divided by layer thickness, averaged from vertices to edges"
//    normalizedRelativeVorticityCell.resize(m.nCells * m.nVertLevels, -1.0e32); // type="real" dimensions="nVertLevels nCells Time" units="s^-1" description="curl of horizontal velocity divided by layer thickness, averaged from vertices to cell centers"
//    layerThicknessEdgeMean.resize(m.nEdges * m.nVertLevels, -1.0e32); // type="real" dimensions="nVertLevels nEdges Time" units="m" description="layer thickness averaged from cell center to edges"
//    layerThicknessEdgeFlux.resize(m.nEdges * m.nVertLevels, -1.0e32); // type="real" dimensions="nVertLevels nEdges Time" units="m" description="layer thickness used for fluxes through edges. May be centered, upwinded, or a combination of the two."
//    layerThicknessVertex.resize(m.nVertices * m.nVertLevels, -1.0e32); // type="real" dimensions="nVertLevels nVertices Time" units="m" description="layer thickness averaged from cell center to vertices"
//    circulation.resize(m.nVertices * m.nVertLevels, -1.0e32); // type="real" dimensions="nVertLevels nVertices Time" units="m^2 s^-1" description="area-integrated vorticity"
}

void Diag::compute(Config &config, Mesh &m, State &s) {
    LOG(4,"-> Diag::compute")

// Loop over vertices
//relativeVorticity
      do iVertex = 1, nVerticesAll
         invAreaTri1 = 1.0_RKIND / areaTriangle(iVertex)
         do i = 1, vertexDegree
            iEdge = edgesOnVertex(i, iVertex)
            do k = minLevelVertexTop(iVertex), maxLevelVertexBot(iVertex)
              r_tmp = dcEdge(iEdge) * normalVelocity(k, iEdge)
              relativeVorticity(k, iVertex) = relativeVorticity(k, iVertex) + edgeSignOnVertex(i, iVertex) * r_tmp * invAreaTri1
            end do
         end do
      end do

    //divergence, kineticEnergyCell
      do iCell = 1, nCells
         divergence(:,iCell) = 0.0_RKIND
         kineticEnergyCell(:,iCell) = 0.0_RKIND
         div_hu(:) = 0.0_RKIND
         invAreaCell1 = invAreaCell(iCell)
         kmin = minLevelCell(iCell)
         kmax = maxLevelCell(iCell)
         do i = 1, nEdgesOnCell(iCell)
            iEdge = edgesOnCell(i, iCell)
            edgeSignOnCell_temp = edgeSignOnCell(i, iCell)
            dcEdge_temp = dcEdge(iEdge)
            dvEdge_temp = dvEdge(iEdge)
            do k = kmin,kmax
               r_tmp = dvEdge_temp*normalVelocity(k,iEdge)*invAreaCell1

               divergence(k,iCell) = divergence(k,iCell) &
                                   - edgeSignOnCell_temp*r_tmp
               div_hu(k) = div_hu(k) &
                         - layerThicknessEdgeFlux(k,iEdge)* &
                           edgeSignOnCell_temp*r_tmp
               kineticEnergyCell(k,iCell) = kineticEnergyCell(k,iCell) &
                                          + 0.25*r_tmp*dcEdge_temp* &
                                            normalVelocity(k,iEdge)
            end do
         end do
    //tangentialVelocity
      do iEdge = 1, nEdges
         tangentialVelocity(:,iEdge) = 0.0_RKIND
         kmin = minLevelEdgeBot(iEdge)
         kmax = maxLevelEdgeTop(iEdge)
         do i = 1, nEdgesOnEdge(iEdge)
            eoe = edgesOnEdge(i,iEdge)
            weightsOnEdge_temp = weightsOnEdge(i, iEdge)
            do k = kmin,kmax
               tangentialVelocity(k,iEdge) = &
               tangentialVelocity(k,iEdge) + weightsOnEdge_temp* &
                                             normalVelocity(k, eoe)
            end do
         end do
      end do
    //kineticEnergyCell, from KE vertex mix
      do iVertex = 1, nVerticesAll
         kineticEnergyVertex(:, iVertex) = 0.0_RKIND
         do i = 1, vertexDegree
            iEdge = edgesOnVertex(i, iVertex)
            rTmp  = dcEdge(iEdge)*dvEdge(iEdge)*0.25_RKIND/ &
                    areaTriangle(iVertex)
            do k = 1, nVertLevels
               kineticEnergyVertex(k,iVertex) = &
               kineticEnergyVertex(k,iVertex) + rTmp* &
                            normalVelocity(k,iEdge)**2
            end do
         end do
      end do
      do iCell = 1, nCells
         kineticEnergyVertexOnCells(:, iCell) = 0.0_RKIND
         invAreaCell1 = invAreaCell(iCell)
         do i = 1, nEdgesOnCell(iCell)
            j = kiteIndexOnCell(i, iCell)
            iVertex = verticesOnCell(i, iCell)
            do k = 1, nVertLevels
               kineticEnergyVertexOnCells(k,iCell) = &
               kineticEnergyVertexOnCells(k,iCell) + &
                        kiteAreasOnVertex(j,iVertex)* &
                        kineticEnergyVertex(k,iVertex)*invAreaCell1
            end do
         end do
      end do
      do iCell = 1, nCells
      do k = 1, nVertLevels
         kineticEnergyCell(k,iCell) = 5.0_RKIND/8.0_RKIND* &
                                      kineticEnergyCell(k,iCell) & 
                                    + 3.0_RKIND/8.0_RKIND* &
                                      kineticEnergyVertexOnCells(k,iCell)
      end do
      end do
    //normalizedRelativeVorticityEdge (do I need these? - no)
    //normalizedPlanetaryVorticityEdge
    //normalizedRelativeVorticityCell
      do iVertex = 1, nVertices
         invAreaTri1 = 1.0_RKIND / areaTriangle(iVertex)
         do k = 1, maxLevelVertexBot(iVertex)
            layerThicknessVertex = 0.0_RKIND
            do i = 1, vertexDegree
               iCell = cellsOnVertex(i,iVertex)
               layerThicknessVertex = layerThicknessVertex &
                                    + layerThickness(k,iCell) &
                                    * kiteAreasOnVertex(i,iVertex)
            end do
            layerThicknessVertex = layerThicknessVertex*invAreaTri1
            if (layerThicknessVertex == 0) cycle

            normalizedRelativeVorticityVertex(k,iVertex) = &
                            relativeVorticity(k,iVertex) / &
                            layerThicknessVertex
            normalizedPlanetaryVorticityVertex(k,iVertex) = &
                            fVertex(iVertex)/layerThicknessVertex
         end do
      end do
      do iEdge = 1, nEdges
         normalizedRelativeVorticityEdge (:,iEdge) = 0.0_RKIND
         normalizedPlanetaryVorticityEdge(:,iEdge) = 0.0_RKIND
         vertex1 = verticesOnEdge(1, iEdge)
         vertex2 = verticesOnEdge(2, iEdge)
         do k = minLevelEdgeTop(iEdge), maxLevelEdgeBot(iEdge)
            normalizedRelativeVorticityEdge(k,iEdge) = 0.5_RKIND* &
                   (normalizedRelativeVorticityVertex(k,vertex1) &
                  + normalizedRelativeVorticityVertex(k,vertex2))
            normalizedPlanetaryVorticityEdge(k,iEdge) = 0.5_RKIND* &
                   (normalizedPlanetaryVorticityVertex(k,vertex1) &
                  + normalizedPlanetaryVorticityVertex(k,vertex2))
        end do
      end do
      do iCell = 1, nCells
         normalizedRelativeVorticityCell(:,iCell) = 0.0_RKIND
         invAreaCell1 = invAreaCell(iCell)

         do i = 1, nEdgesOnCell(iCell)
            j = kiteIndexOnCell(i, iCell)
            iVertex = verticesOnCell(i, iCell)
            do k = minLevelCell(iCell), maxLevelCell(iCell)
               normalizedRelativeVorticityCell(k,iCell) = &
               normalizedRelativeVorticityCell(k,iCell) + &
                                  kiteAreasOnVertex(j,iVertex)* &
                  normalizedRelativeVorticityVertex(k,iVertex)* &
                  invAreaCell1
            end do
         end do
      end do
         do iEdge = 1,nEdges
            do k = minLevelEdgeTop(iEdge), maxLevelEdgeBot(iEdge)
               normalizedRelativeVorticityEdge(k,iEdge) = &
               normalizedRelativeVorticityEdge(k,iEdge) - &
                    apvm_scale_factor*dt* &
                    (normalVelocity(k,iEdge)* &
                     vorticityGradientNormalComponent(k,iEdge)      &
                   + tangentialVelocity(k,iEdge)* &
                     vorticityGradientTangentialComponent(k,iEdge) )
            end do
         enddo
//relativeVorticityCell - Probably a visualization variable only
      do iCell = 1, nCellsOwned
         relativeVorticityCell(:,iCell) = 0.0_RKIND
         invAreaCell1 = invAreaCell(iCell)
         kmin = minLevelCell(iCell)
         kmax = maxLevelCell(iCell)

         do i = 1, nEdgesOnCell(iCell)
            j = kiteIndexOnCell(i, iCell)
            iVertex = verticesOnCell(i, iCell)
            do k = kmin,kmax
               relativeVorticityCell(k,iCell) = &
               relativeVorticityCell(k,iCell) + &
                        kiteAreasOnVertex(j,iVertex)* &
                        relativeVorticity(k,iVertex)*invAreaCell1
            end do
         end do
      end do

}
