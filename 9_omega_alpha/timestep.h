#ifndef TIMESTEP_H
#define TIMESTEP_H

#include "vector"
#include "Config.h"
#include "Meta.h"
#include "Mesh.h"
#include "State.h"
#include "Diag.h"
#include "Tend.h"

void timestep(Config &config, Meta &meta, Mesh &m, std::vector<State> &s, Diag &diag, std::vector<Tend> &tend);

#endif
