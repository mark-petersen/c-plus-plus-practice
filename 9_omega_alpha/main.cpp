/*                                              __      __         
  ____  ____ ___  ___  ____ _____ _      ____ _/ /___  / /_  ____ _
 / __ \/ __ `__ \/ _ \/ __ `/ __ `/_____/ __ `/ / __ \/ __ \/ __ `/
/ /_/ / / / / / /  __/ /_/ / /_/ /_____/ /_/ / / /_/ / / / / /_/ / 
\____/_/ /_/ /_/\___/\__, /\__,_/      \__,_/_/ .___/_/ /_/\__,_/  
                    /____/                   /_/                  */

// Omega-alpha is a preliminary version of the Omega ocean model. The modeling
// capability is the same as Omega-0: the shallow water equations with
// identical vertical layers and inactive tracers. Omega-alpha runs on a single
// cpu with no domain decomposition, no GPU capability, and with native c++
// vectors rather than YAKL array objects. The purpose is to work out the
// design of the classes, functions, files, naming conventions, and code style
// in a very simple setting. The design of all Omega versions and the model
// equations may be found at:
// https://github.com/E3SM-Project/Omega/blob/develop/components/omega/doc/design/ShallowWaterOmega0.md
// Mark Petersen, LANL, August 2023

#include <iostream>
#include <string>
#include "Config.h"
#include "Meta.h"
#include "Mesh.h"
#include "State.h"
#include "Diag.h"
#include "Tend.h"
#include "timestep.h"

using namespace std;

int main() {
  LOG(2,"Omega-Alpha initialization")

  //*******************************************************
  //  Initialization
  //*******************************************************
  Config config;
  Meta meta(config);
  Mesh m(config);
  vector <State> s;
  {
    State temporaryState(m);
    for (size_t n=0; n<meta.stateLevelsInMemory; n++) {
      s.push_back(temporaryState);
    }
  }   // temporaryState is destroyed here.
  Diag d(m);
  vector <Tend> tend;
  {
    Tend temporaryTend(m);
    for (size_t n=0; n<meta.tendLevelsInMemory; n++) {
      tend.push_back(temporaryTend);
    }
  }   // temporaryTend is destroyed here.

  s[0].init(config, m);
  d.compute(config, m, s[0]);

  //*******************************************************
  //  time step loop
  //*******************************************************
  for (meta.timeIndex=0; meta.timeIndex<config.n_timesteps; meta.timeIndex++) {
    timestep(config, meta, m,s,d, tend);
  }

}

