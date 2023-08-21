#ifndef META_H
#define META_H

#include <iostream>
#include <string>
#include <vector>
#include "Config.h"

class Meta {
  public:
    size_t timeIndex {0}; // index for time stepping
    std::vector<size_t> timeArrayIndex; // index to large arrays in time
    double time {0.0}; // model time in seconds
    size_t stateLevelsInMemory { 2 }; 
    size_t tendLevelsInMemory { 1 }; 

    // constructor
    Meta(Config &config);
};

#endif
