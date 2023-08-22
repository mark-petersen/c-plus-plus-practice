#ifndef CONFIG_H
#define CONFIG_H

/* VERBOSITY LEVELS
0. No printing
1. warnings only
2. High level code locations - init, timestep, finalize only (like mpas log).
3. Mid level information - summary diagnostics on simulation in text output per time step.
4. Print upon entry to most subroutines
5. Max printing - individual variable reading
*/

#define VERBOSITY 3
#define LOG(verbose_level, message) {if (VERBOSITY>=verbose_level) std::cout<< message << std::endl;}
#define ERRORMESSAGE(m) {printf("Error: %s\n", m); exit(0);}

#include <string>

class Config {
  public:

  //*******************************************************
  //  Initialization
  //*******************************************************
  bool verbose { true }; // print verbose output during run
  std::string dirName { "links_su/" };
  std::string fileName { "ocean.QU.240km.151209.nc" };
  //std::string fileName { "mpaso.EC30to60E2r3.230313.nc" };
  //std::string fileName { "oRRS18to6v3.171116.nc" };
  
  //std::string initial_condition = "init_file";
  //std::string initial_condition = "constant";
  double initial_condition_constant = 55.0;
  std::string initial_condition = "sinx";

  //*******************************************************
  //  time stepping
  //*******************************************************
  std::string timestep_method { "forward_Euler" };
  double dt = 0.01; // time step [s]
  size_t n_timesteps = 100;

  //*******************************************************
  //  velocity tendency terms
  //*******************************************************
  bool uTend_Rayleigh_enable = true;
  double uTend_Rayleigh_drag {0.1}; // coefficient in -Ra*u term [1/s]

  //*******************************************************
  //  thickness tendency terms
  //*******************************************************
  bool hTend_decay_enable = true; // -c*h ( for testing only)
  double hTend_decay_coef {0.1}; // coefficient Ra [1/s]

  bool hTend_del2_enable = true; // kappa del2(h)
  double hTend_del2_coef {0.1}; // coefficient in -Ra*u term [1/s]
};
#endif
