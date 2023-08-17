#ifndef STATE_H
#define STATE_H

#include <vector>
#include <string>
using namespace std;

class State {
  public:
  
    // State variables
    vector <double> normalVelocity;
    vector <double> layerThickness;

    // constructor
    State();
};
#endif
