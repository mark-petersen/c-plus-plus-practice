#ifndef TENDENCIES_H
#define TENDENCIES_H
#include "Config.h"
#include "Meta.h"
#include "Mesh.h"
#include "State.h"
#include "Tend.h"

void compute_velocity_tendencies(Config &config, Meta &meta, Mesh &m, State &s, Tend &tend);
void compute_thickness_tendencies(Config &config, Meta &meta, Mesh &m, State &s, Tend &tend);

#endif
