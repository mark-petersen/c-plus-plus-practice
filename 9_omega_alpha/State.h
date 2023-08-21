#ifndef STATE_H
#define STATE_H

#include <vector>
#include <string>
#include "Config.h"
#include "Meta.h"
#include "Mesh.h"
#include "Tend.h"

class State {
  public:
  
    // State variables
    std::vector <double> normalVelocity;
    std::vector <double> layerThickness;


    // constructor
    State(Config &config, Mesh &m);
    void init(Config &config, Mesh &m);
    void computeTend(Config &config, Meta &meta, Mesh &m, Tend &tend);
};
#endif
