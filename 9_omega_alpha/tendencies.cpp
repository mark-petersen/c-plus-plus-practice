#include <iostream>
#include "Config.h"
#include "Meta.h"
#include "Mesh.h"
#include "State.h"
#include "Tend.h"
#include "tendencies.h"

void uTend_Rayleigh(Config &config, Meta &meta, Mesh &m, State &s, Tend &tend) {
    LOG(4,"-> uTend_Rayleigh")
    if (!config.uTend_Rayleigh_enable) return;

    size_t K=m.nVertLevels;
    for (size_t e=0; e<m.nEdges; e++) {
      for (size_t k=0; k<K; k++) {
        tend.normalVelocity[e*K+k] = - config.uTend_Rayleigh_drag * s.normalVelocity[e*K+k];
      }
    }
}

void hTend_decay(Config &config, Meta &meta, Mesh &m, State &s, Tend &tend) {
    LOG(4,"-> hTend_decay")
    if (!config.hTend_decay_enable) return;

    size_t K=m.nVertLevels;
    for (size_t i=0; i<m.nCells; i++) {
      for (size_t k=0; k<K; k++) {
        tend.layerThickness[i*K+k] = - config.hTend_decay_coef * s.layerThickness[i*K+k];
      }
    }
}

void compute_velocity_tendencies(Config &config, Meta &meta, Mesh &m, State &s, Tend &tend) {
    LOG(4,"-> compute_velocity_tendencies")

    uTend_Rayleigh(config, meta, m, s, tend);
}

void compute_thickness_tendencies(Config &config, Meta &meta, Mesh &m, State &s, Tend &tend) {
    LOG(4,"-> compute_thickness_tendencies")

    hTend_decay(config, meta, m, s, tend);
}

