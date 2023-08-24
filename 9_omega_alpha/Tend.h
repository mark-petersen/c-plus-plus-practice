#ifndef TEND_H
#define TEND_H

#include <vector>
#include <string>
#include "Meta.h"
#include "Mesh.h"
#include "State.h"

// Tend is derived from the State class, so it
// inherits all its variables.
class Tend : public State {
  public:

    // tend variables: nothing extra!

    // constructor
    Tend(Mesh &m);
};
#endif
