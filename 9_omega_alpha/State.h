#ifndef STATE_H
#define STATE_H

#include <vector>
#include <string>
#include "Mesh.h"
using namespace std;

class State {
  public:
  
    // State variables
    vector <double> normalVelocity;
    vector <double> layerThickness;

    // constructor
    State(Mesh &m);
    void init(Mesh &m);
};
#endif
