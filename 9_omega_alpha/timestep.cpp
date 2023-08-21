
#include <iostream>
#include <vector>
#include <cmath> // for exp
#include "Config.h"
#include "Mesh.h"
#include "State.h"
#include "Tend.h"
#include "timestep.h"

void forward_Euler_timestep(Config &config, Meta &meta, Mesh &m, std::vector<State> &s, std::vector<Tend> &tend) {
    LOG(4,"-> forward_Euler_timestep")
    // y(n+1) = y(n) + dt*RHS(n)

    size_t K=m.nVertLevels;
    size_t tCur=meta.timeArrayIndex[0];
    size_t tNew=meta.timeArrayIndex[1];
    //tend[0].compute_tend(config, m, s);
    for (size_t e=0; e<m.nEdges; e++) {
      for (size_t k=0; k<K; k++) {
        tend[0].normalVelocity[e*K+k] = - config.Rayleigh_drag * s[tCur].normalVelocity[e*K+k];
      }
    }

    for (size_t e=0; e<m.nEdges; e++) {
      for (size_t k=0; k<K; k++) {
        s[tNew].normalVelocity[e*K+k] = s[tCur].normalVelocity[e*K+k] + config.dt * tend[0].normalVelocity[e*K+k];
      }
    }
    for (size_t i=0; i<m.nCells; i++) {
      for (size_t k=0; k<K; k++) {
         s[0].layerThickness[i*K+k] = 2.0;
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
    size_t n = meta.timeIndex;
    size_t tNew=meta.timeArrayIndex[1];
    double curTime = (n+1)*config.dt;
    double sol = config.initial_condition_constant * std::exp(-config.Rayleigh_drag*curTime);
    LOG(3, meta.timeIndex << " " << sol << "  " << s[tNew].normalVelocity[0])

}

