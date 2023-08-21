
#include <iostream>
#include <vector>
#include <cmath> // for exp
#include "Config.h"
#include "Meta.h"
#include "Mesh.h"
#include "State.h"
#include "Tend.h"
#include "timestep.h"
#include "tendencies.h"

void forward_Euler_timestep(Config &config, Meta &meta, Mesh &m, std::vector<State> &s, std::vector<Tend> &tend) {
    LOG(4,"-> forward_Euler_timestep")
    // y(n+1) = y(n) + dt*RHS(n)

    size_t tCur=meta.timeArrayIndex[0];
    size_t tNew=meta.timeArrayIndex[1];
    compute_tendencies(config, meta, m, s[tCur], tend[0]);

    size_t K=m.nVertLevels;
    for (size_t e=0; e<m.nEdges; e++) {
      for (size_t k=0; k<K; k++) {
        s[tNew].normalVelocity[e*K+k] = s[tCur].normalVelocity[e*K+k] + config.dt * tend[0].normalVelocity[e*K+k];
      }
    }
    for (size_t i=0; i<m.nCells; i++) {
      for (size_t k=0; k<K; k++) {
        s[tNew].layerThickness[i*K+k] = s[tCur].layerThickness[i*K+k] + config.dt * tend[0].layerThickness[i*K+k];
      }
    }
    // switch array indices for next step:
    meta.timeArrayIndex[0] = tNew;
    meta.timeArrayIndex[1] = tCur;
}

void timestep(Config &config, Meta &meta, Mesh &m, std::vector<State> &s, std::vector<Tend> &tend) {
    LOG(4,"-> timestep")

    if (config.timestep_method=="forward_Euler") {
      forward_Euler_timestep(config, meta, m, s, tend);
    }

    // check against exact solution
    size_t tNew=meta.timeArrayIndex[1];
    double curTime = (meta.timeIndex)*config.dt;
    double sol = config.initial_condition_constant * std::exp(-config.Rayleigh_drag*curTime);
    LOG(3, meta.timeIndex << " " << sol << "  " << s[tNew].normalVelocity[0] << "  "<<s[tNew].layerThickness[0])

}

