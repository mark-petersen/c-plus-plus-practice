#ifndef STATE_H
#define STATE_H

#include <vector>
#include <string>
#include "Config.h"
#include "Meta.h"
#include "Mesh.h"

class State {
  public:
  
    // State variables
    std::vector <double> normalVelocity;
    std::vector <double> layerThickness;

    // constructor
    State(Mesh &m);
    void init(Config &config, Mesh &m);
};
#endif
