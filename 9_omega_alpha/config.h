#ifndef CONFIG_H
#define CONFIG_H

// see https://www.learncpp.com/cpp-tutorial/sharing-global-constants-across-multiple-files-using-inline-variables/

#define ERRORMESSAGE(m) {printf("Error: %s\n", m); exit(0);}

namespace config {
  inline constexpr bool verbose { true }; // print verbose output during run
  inline constexpr char dirName[] = "links_su/";
  inline constexpr char fileName[] = "ocean.QU.240km.151209.nc";
  //inline constexpr char fileName[] = "mpaso.EC30to60E2r3.230313.nc";
  //inline constexpr char fileName[] = "oRRS18to6v3.171116.nc";

  inline constexpr char timestep_method[] = "forward_Euler";
}
#endif
