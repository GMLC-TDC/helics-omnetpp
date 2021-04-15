# Power System Example

What you will find in folders:

1. Comms : The communication model (as in following research: *A Federated Simulation Toolkit for Electric Power Grid and Communication network Co-simulation*, referencing *GECO: Global Event-Drive Co-Simulation  Framework for Interconnected Power System and Communication Network*) represented in OMNET++
2. PowerSystem-HelicsFed: The power system model represented by Helics Federate (simplified - federate sends over remote/local faults for Comms to process and run simulation in OMNET++; no powersystem simulation is really running.)

## Notes Before Running Co-Simulation
1. Comms will be ran in the OMNET++ IDE.
2. PowerSystem-HelicsFed will be ran in the Visual Studio IDE. Each .cpp file is its own federate. Only choose one to run against Comms. Make sure that the files have been built into executables before running.
*For clearer steps on how to use HELICS within the Visual Studio IDE, please see this page: [HELICS-VISUALSTUDIO](https://docs.helics.org/en/latest/introduction/hello-world-VS.html)*

## How This Works
1. Execute helics_broker -f2 on commandline - be sure to be in the correct directory.
2. Execute one of the PowerSystem-HelicsFed - this should either be the isolatedFault.exe or NonisolatedFault.exe
  - This is the HELICS Power System federate.
3. Execute comms.exe
 - This will hold the code for the OMNET++ federate and all the modules involved in the IEEE 39-Bus model.


## Release

HELICS and helics-omnetpp are distributed under the terms of the [BSD-3](https://github.com/GMLC-TDC/helics-omnetpp/blob/master/LICENSE) clause license. All new contributions must be made under this license.

SPDX-License-Identifier: BSD-3-Clause
