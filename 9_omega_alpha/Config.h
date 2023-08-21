#ifndef CONFIG_H
#define CONFIG_H

#define VERBOSITY 4
#define LOG(verbose_level, message) {if (VERBOSITY>=verbose_level) std::cout<< message << std::endl;}
#define ERRORMESSAGE(m) {printf("Error: %s\n", m); exit(0);}

#include <string>

class Config {
  public:

    bool verbose { true }; // print verbose output during run
    std::string dirName { "links_su/" };
    std::string fileName { "ocean.QU.240km.151209.nc" };
    //std::string fileName { "mpaso.EC30to60E2r3.230313.nc" };
    //std::string fileName { "oRRS18to6v3.171116.nc" };
  
    std::string timestep_method { "forward_Euler" };
};
#endif
