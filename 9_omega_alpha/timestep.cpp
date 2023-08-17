
#include <iostream>
#include <string>
#include <vector>
#include "config.h"
#include "Mesh.h"
#include "timestep.h"
using namespace std;

void timestep(MpasMesh m) {
    if (config::verbose) cout << "In timestep" << endl;
    if (string(config::timestep_method)=="forward_Euler") {
      forward_Euler_timestep(m);
    }
}

void forward_Euler_timestep(MpasMesh m) {
    if (config::verbose) cout << "In forward_Euler_timestep" << endl;
    // y(n+1) = y(n) + dt*RHS(n)
    tend = compute_tend(stateCur);
    state[newTime] = state[curTime] + dt * tend;
}
