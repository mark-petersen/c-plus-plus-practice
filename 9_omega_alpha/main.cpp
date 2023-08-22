/*                                                                                            __            __                 
    ____    ____ ___    ___    ____ _____ _            ____ _/ /___    / /_    ____ _
 / __ \/ __ `__ \/ _ \/ __ `/ __ `/_____/ __ `/ / __ \/ __ \/ __ `/
/ /_/ / / / / / /    __/ /_/ / /_/ /_____/ /_/ / / /_/ / / / / /_/ / 
\____/_/ /_/ /_/\___/\__, /\__,_/            \__,_/_/ .___/_/ /_/\__,_/    
                                        /____/                                     /_/                                    */

#include <iostream>
#include <string>
#include "Config.h"
#include "Meta.h"
#include "Mesh.h"
#include "State.h"
#include "Tend.h"
#include "timestep.h"

using namespace std;

int main() {
    LOG(2,"Omega-Alpha initialization")

    //*******************************************************
    //    Initialization
    //*******************************************************
    Config config;
    Meta meta(config);
    Mesh m(config);
    vector <State> s;
    vector <Tend> t;
    //Diag d;
    {
        State temporaryState(config, m);
        for (size_t n=0; n<meta.stateLevelsInMemory; n++) {
            s.push_back(temporaryState);
        }
    }   // temporaryState is destroyed here.
    {
        Tend temporaryTend(config, m);
        for (size_t n=0; n<meta.tendLevelsInMemory; n++) {
            t.push_back(temporaryTend);
        }
    }   // temporaryTend is destroyed here.
    s[0].init(config, m);

    //*******************************************************
    //    time step loop
    //*******************************************************
    for (meta.timeIndex=0; meta.timeIndex<config.n_timesteps; meta.timeIndex++) {
        timestep(config, meta, m,s,t);
    }

}

