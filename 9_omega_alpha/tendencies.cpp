#include <iostream>
#include "Config.h"
#include "Meta.h"
#include "Mesh.h"
#include "State.h"
#include "Diag.h"
#include "Tend.h"
#include "tendencies.h"

void uTend_ssh_gradient(Config &config, Meta &meta, Mesh &m, State &s, Tend &tend) {
  LOG(4,"-> uTend_ssh_gradient")
  if (!config.uTend_ssh_gradient_enable) return;

  size_t K=m.nVertLevels;
  for (size_t e=0; e<m.nEdges; e++) {
    for (size_t k=0; k<K; k++) {
    //tend.normalVelocity[e*K+k] += config.uTend_ssh_gradient * s.normalVelocity[e*K+k];
    }
  }
}

void uTend_advection(Config &config, Meta &meta, Mesh &m, State &s, Tend &tend) {
  LOG(4,"-> uTend_advection")
  if (!config.uTend_advection_enable) return;

  size_t K=m.nVertLevels;
  for (size_t e=0; e<m.nEdges; e++) {
    for (size_t k=0; k<K; k++) {
    //tend.normalVelocity[e*K+k] += config.uTend_advection * s.normalVelocity[e*K+k];
    }
  }
}

void uTend_del2(Config &config, Meta &meta, Mesh &m, State &s, Tend &tend) {
  LOG(4,"-> uTend_del2")
  if (!config.uTend_del2_enable) return;

  size_t K=m.nVertLevels;
  for (size_t e=0; e<m.nEdges; e++) {
    for (size_t k=0; k<K; k++) {
    //tend.normalVelocity[e*K+k] += config.uTend_del2 * s.normalVelocity[e*K+k];
    }
  }
}

void uTend_del4(Config &config, Meta &meta, Mesh &m, State &s, Tend &tend) {
  LOG(4,"-> uTend_del4")
  if (!config.uTend_del4_enable) return;

  size_t K=m.nVertLevels;
  for (size_t e=0; e<m.nEdges; e++) {
    for (size_t k=0; k<K; k++) {
    //tend.normalVelocity[e*K+k] += config.uTend_del4 * s.normalVelocity[e*K+k];
    }
  }
}

void uTend_bottom_drag(Config &config, Meta &meta, Mesh &m, State &s, Tend &tend) {
  LOG(4,"-> uTend_bottom_drag")
  if (!config.uTend_bottom_drag_enable) return;

  size_t K=m.nVertLevels;
  for (size_t e=0; e<m.nEdges; e++) {
    for (size_t k=0; k<K; k++) {
    //tend.normalVelocity[e*K+k] += config.uTend_bottom_drag * s.normalVelocity[e*K+k];
    }
  }
}

void uTend_wind_forcing(Config &config, Meta &meta, Mesh &m, State &s, Tend &tend) {
  LOG(4,"-> uTend_wind_forcing")
  if (!config.uTend_wind_forcing_enable) return;

  size_t K=m.nVertLevels;
  for (size_t e=0; e<m.nEdges; e++) {
    for (size_t k=0; k<K; k++) {
    //tend.normalVelocity[e*K+k] += config.uTend_wind_forcing * s.normalVelocity[e*K+k];
    }
  }
}

void uTend_Rayleigh(Config &config, Meta &meta, Mesh &m, State &s, Tend &tend) {
  LOG(4,"-> uTend_Rayleigh")
  if (!config.uTend_Rayleigh_enable) return;

  size_t K=m.nVertLevels;
  for (size_t e=0; e<m.nEdges; e++) {
    for (size_t k=0; k<K; k++) {
    tend.normalVelocity[e*K+k] -= config.uTend_Rayleigh_drag * s.normalVelocity[e*K+k];
    }
  }
}

void hTend_advection(Config &config, Meta &meta, Mesh &m, State &s, Tend &tend) {
  LOG(4,"-> hTend_advection")
  if (!config.hTend_advection_enable) return;

  size_t K=m.nVertLevels;
  for (size_t i=0; i<m.nCells; i++) {
    for (size_t k=0; k<K; k++) {
    //tend.layerThickness[i*K+k] -= config.hTend_advection_coef * s.layerThickness[i*K+k];
    }
  }
}

void hTend_decay(Config &config, Meta &meta, Mesh &m, State &s, Tend &tend) {
  LOG(4,"-> hTend_decay")
  if (!config.hTend_decay_enable) return;

  size_t K=m.nVertLevels;
  for (size_t i=0; i<m.nCells; i++) {
    for (size_t k=0; k<K; k++) {
    tend.layerThickness[i*K+k] -= config.hTend_decay_coef * s.layerThickness[i*K+k];
    }
  }
}

void hTend_del2(Config &config, Meta &meta, Mesh &m, State &s, Tend &tend) {
  LOG(4,"-> hTend_del2")
  if (!config.hTend_del2_enable) return;

  size_t K=m.nVertLevels;
  size_t E=m.maxEdges;
  size_t iCell, i, k, cell1, cell2, iEdge;
  double invAreaCell, r_tmp, tracer_turb_flux, flux;
  for (iCell=0; iCell<m.nCells; iCell++) {
    invAreaCell = 1.0 / m.areaCell[iCell];
    for (i=0; i<m.nEdgesOnCell[iCell]; i++) {
      iEdge = m.edgesOnCell.at(iCell*E+i);
      cell1 = m.cellsOnEdge.at(iEdge*2);
      cell2 = m.cellsOnEdge.at(iEdge*2+1);
      r_tmp = config.hTend_del2_coef * m.dvEdge[iEdge] / m.dcEdge[iEdge];
      for (k=0; k<K; k++) {
//        ! \kappa_2 \nabla \phi on edge
        tracer_turb_flux = s.layerThickness.at(cell2*K+k) - s.layerThickness.at(cell1*K+k);
//        ! div(h \kappa_2 \nabla \phi) at cell center, but no h coefficient here
        flux =  tracer_turb_flux * r_tmp;
        tend.layerThickness[iCell*K+k] -= m.edgeSignOnCell[iCell*E+i] * flux * invAreaCell;
      }
    }
  }
//    do iCell = 1, nCells
//    invAreaCell = 1.0_RKIND / areaCell(iCell)
//    do i = 1, nEdgesOnCell(iCell)
//      iEdge = edgesOnCell(i, iCell)
//      cell1 = cellsOnEdge(1,iEdge)
//      cell2 = cellsOnEdge(2,iEdge)
//
//      r_tmp = meshScalingDel2(iEdge) * eddyDiff2 * dvEdge(iEdge) / dcEdge(iEdge)
//
//      do k = minLevelEdgeBot(iEdge), maxLevelEdgeTop(iEdge)
//      do iTracer = 1, num_tracers
//        ! \kappa_2 \nabla \phi on edge
//        tracer_turb_flux = tracers(iTracer, k, cell2) - tracers(iTracer, k, cell1)
//
//        ! div(h \kappa_2 \nabla \phi) at cell center
//        flux = layerThickEdgeMean(k, iEdge) * tracer_turb_flux * r_tmp
//
//        tend(iTracer, k, iCell) = tend(iTracer, k, iCell) - edgeSignOnCell(i, iCell) * flux * invAreaCell
//      end do
//      end do
//
//    end do
//    end do
}

void compute_velocity_tendencies(Config &config, Meta &meta, Mesh &m, State &s, Diag &diag, Tend &tend) {
  LOG(4,"-> compute_velocity_tendencies")

  fill(tend.normalVelocity.begin(), tend.normalVelocity.end(), 0.0);
  uTend_Rayleigh(config, meta, m, s, tend);
}

void compute_thickness_tendencies(Config &config, Meta &meta, Mesh &m, State &s, Diag &diag, Tend &tend) {
  LOG(4,"-> compute_thickness_tendencies")

  fill(tend.layerThickness.begin(), tend.layerThickness.end(), 0.0);
  hTend_decay(config, meta, m, s, tend);
  hTend_del2(config, meta, m, s, tend);
}

