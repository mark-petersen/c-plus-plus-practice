
#include <iostream>
#include <string>
#include <vector>
#include "Config.h"
#include "Mesh.h"
#include "State.h"
#include "Tend.h"
#include "timestep.h"
using namespace std;

void forward_Euler_timestep(Config &config, Mesh &m, vector<State> &s, vector<Tend> &tend) {
    if (config.verbose) cout << "In forward_Euler_timestep" << endl;
    // y(n+1) = y(n) + dt*RHS(n)
    //tend[0].compute_tend(config, m, s);

    size_t K=m.nVertLevels;
    for (size_t e=0; e<m.nEdges; e++) {
      for (size_t k=0; k<K; k++) {
        //s[s.newTime].normalVelocity[e*K+k] = s[s.curTime].normalVelocity[e*K+k] + dt * tend[0].normalVelocity[e*K+k];
        // normalVelocity[e*K+k] = 1.0;
      }
    }
    for (size_t i=0; i<m.nCells; i++) {
      for (size_t k=0; k<K; k++) {
         s[0].layerThickness[i*K+k] = 2.0;
      }
    }
}

void timestep(Config &config, Mesh &m, vector<State> &s, vector<Tend> &tend) {
    if (config.verbose) cout << "In timestep" << endl;

    if (config.timestep_method=="forward_Euler") {
      forward_Euler_timestep(config, m, s, tend);
    }

}

