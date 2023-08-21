/*                                              __      __         
  ____  ____ ___  ___  ____ _____ _      ____ _/ /___  / /_  ____ _
 / __ \/ __ `__ \/ _ \/ __ `/ __ `/_____/ __ `/ / __ \/ __ \/ __ `/
/ /_/ / / / / / /  __/ /_/ / /_/ /_____/ /_/ / / /_/ / / / / /_/ / 
\____/_/ /_/ /_/\___/\__, /\__,_/      \__,_/_/ .___/_/ /_/\__,_/  
                    /____/                   /_/                  */

#include <iostream>
#include <string>
#include "Config.h"
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

  //MetaInfo meta;
  Config config;
  Mesh m(config);
  vector <State> s;
  vector <Tend> t;
  //Diag d;
  {
    State temporaryState(config, m);
    for (size_t n=0; n<state_levels_in_memory; n++) {
      s.push_back(temporaryState);
    }
  // temporaryState is destroyed here.
  }
  {
    Tend temporaryTend(config, m);
    for (size_t n=0; n<tend_levels_in_memory; n++) {
      t.push_back(temporaryTend);
    }
  // temporaryTend is destroyed here.
  }
  s[0].init(config, m);

  // time step loop
  for (int n=0; n<n_timesteps; n++) {
      if (config.verbose) cout << "timestep n" << endl;
        timestep(config, m,s,t);
  }
  size_t K=m.nVertLevels;
  size_t i=m.nCells;
  size_t e=m.nEdges;
  cout << "s.normalVelocity[0]: " << s[0].normalVelocity[0] << endl;
  cout << "s.normalVelocity[1]: " << s[1].normalVelocity[e*K-1] << endl;
  cout << "s.layerThickness[0]: " << s[0].layerThickness[0] << endl;
  cout << "s.layerThickness[0]: " << s[1].layerThickness[i*K-1] << endl;
  cout << "t.normalVelocity[0]: " << t[0].normalVelocity[0] << endl;
  cout << "t.normalVelocity[1]: " << t[0].normalVelocity[e*K-1] << endl;
  cout << "t.layerThickness[0]: " << t[0].layerThickness[0] << endl;
  cout << "t.layerThickness[0]: " << t[0].layerThickness[i*K-1] << endl;

}

