#ifndef STATE_H
#define STATE_H

#include <vector>
#include <string>
#include "Mesh.h"

class State {
  public:
  
    // State variables
    std::vector <double> normalVelocity;
    std::vector <double> layerThickness;


    // constructor
    State(Config &config, Mesh &m);
    void init(Config &config, Mesh &m);
};
#endif
