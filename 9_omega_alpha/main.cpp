/*                                              __      __         
  ____  ____ ___  ___  ____ _____ _      ____ _/ /___  / /_  ____ _
 / __ \/ __ `__ \/ _ \/ __ `/ __ `/_____/ __ `/ / __ \/ __ \/ __ `/
/ /_/ / / / / / /  __/ /_/ / /_/ /_____/ /_/ / / /_/ / / / / /_/ / 
\____/_/ /_/ /_/\___/\__, /\__,_/      \__,_/_/ .___/_/ /_/\__,_/  
                    /____/                   /_/                  */

#include <iostream>
#include <string>
#include "config.h"
#include "Mesh.h"
#include "State.h"
#include "Tend.h"
#include "timestep.h"

using namespace std;

int main() {
  // configs to move later
  size_t n_timesteps = 3;
  size_t state_levels_in_memory = 2; 
  size_t tend_levels_in_memory = 1; 

  Mesh m;
  vector <State> s;
  vector <Tend> tend;
  {
    State temporaryState(m);
    for (size_t n=0; n<state_levels_in_memory; n++) {
      s.push_back(temporaryState);
    }
  }
  {
    Tend temporaryTend(m);
    for (size_t n=0; n<tend_levels_in_memory; n++) {
      tend.push_back(temporaryTend);
    }
  }
  // temporaryTend is destroyed here.
  s[0].init(m);

  // time step loop
  for (int n=0; n<n_timesteps; n++) {
      if (config::verbose) cout << "timestep n" << endl;
        timestep(m, s);
  }
  size_t K=m.nVertLevels;
  size_t i=m.nCells;
  size_t e=m.nEdges;
  cout << "s.normalVelocity[0]: " << s[0].normalVelocity[0] << endl;
  cout << "s.normalVelocity[1]: " << s[1].normalVelocity[e*K-1] << endl;
  cout << "s.layerThickness[0]: " << s[0].layerThickness[0] << endl;
  cout << "s.layerThickness[0]: " << s[1].layerThickness[i*K-1] << endl;
  cout << "tend.normalVelocity[0]: " << tend[0].normalVelocity[0] << endl;
  cout << "tend.normalVelocity[1]: " << tend[0].normalVelocity[e*K-1] << endl;
  cout << "tend.layerThickness[0]: " << tend[0].layerThickness[0] << endl;
  cout << "tend.layerThickness[0]: " << tend[0].layerThickness[i*K-1] << endl;

}

