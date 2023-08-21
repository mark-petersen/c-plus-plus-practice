#ifndef TIMESTEP_H
#define TIMESTEP_H

#include "vector"
#include "Config.h"
#include "Mesh.h"
#include "State.h"
#include "Tend.h"

void timestep(Config &config, Mesh &m, std::vector<State> &s, std::vector<Tend> &tend);

#endif
