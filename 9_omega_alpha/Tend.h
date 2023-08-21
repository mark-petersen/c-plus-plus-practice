#ifndef TEND_H
#define TEND_H

#include <vector>
#include <string>
#include "Config.h"
#include "Meta.h"
#include "Mesh.h"

// Tend is derived from the State class, so it
// inherits all its variables.
class Tend {
  public:
  
    // tend variables:
    std::vector <double> normalVelocity;
    std::vector <double> layerThickness;

    // constructor
    Tend(Config &config, Mesh &m);
};
#endif
