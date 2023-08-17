#ifndef TIMESTEP_H
#define TIMESTEP_H

#include "Mesh.h"
#include "State.h"

void timestep(Mesh &m, State &s);
void forward_Euler_timestep(Mesh &m, State &s);

#endif
