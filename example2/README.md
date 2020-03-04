# Hypercube model using Dynamic Module Creation

This example shows OMNeT++'s ability to encapsulate data transferred from a HELICS federate in order to create the Hypercube model at runtime.
The data that is transferred from the HELICS federate to the OMNeT++ federate is the new dimension for the Hypercube model.

To better understand the Hypercube model, please read the [README.txt](https://github.com/hgngo/Helics-Omnetpp/blob/master/example2/helics-hypercube/README.txt) provided by OMNeT++ which is found under the helics-hypercube directory.

The Hypercube sample code from OMNeT++ is used in this example.

## How This Works
1. Execute helics_broker -f2 on commandline - be sure to be in the correct directory.
2. Execute PublishHCN.exe
  - This is the HELICS federate.
3. Execute helics-hypercube.exe
  - This will hold the code for the OMNeT++ federate and all the modules involved in the Hypercube model.

## What is happening?
The two federates - HELICS and OMNeT++ - both connect to the broker. At the initialization of the simulation, the HELICS federate connects to the helics_broker and publishes the new dimensions to the helics_broker to hold until the OMNeT++ federate connects to it and subscribes to it.

After the initialization and the simulation begins, the hypecubeNetwork module will inquire a new dimension from the OMNeT++ federate. This would tell the OMNeT++ federate to obtain the new dimensions from the broker. Once obtained, that value is sent to the hypcubeNetwork where the value is used to build the dimensions of the Hypercube.

***Steps to see the module creation:***

  Before starting the simulation take a look at the topology from the OMNeT++ simulation interface.
  There is the overview where you can see only the two nodes: omnetpp and hypecubeNetwork.


  *We will now move along the simulation step by step by using the 'step' button which can be found in the upper left next to the 'run' button.*


  1. Click 'step' once and you will see that the "Inquire New Dimensions" message has changed into a "New Val" message which is sent from omnetpp to hypecubeNetwork.
  2. Right click on the hypecubeNetwork module then "Go Into 'hypecubeNetwork'"
  3. You will see that there is nothing there. This space will be where the module creation will occur.
  4. Click 'step' once.
  5. Now you will see the node "Hypercube" appear.
  6. Click 'step' once.
  7. You will see that inside the Hypercube is the structure of the hypercube created with 2^dim nodes.
  8. Now if you click start, you will see the simulation run.

After you stop and finish the simulation, the dynamic module Hypercube will be deallocated and deleted.

## Release

HELICS and helics-omnetpp are distributed under the terms of the [BSD-3](https://github.com/GMLC-TDC/helics-omnetpp/blob/master/LICENSE) clause license. All new contributions must be made under this license.

SPDX-License-Identifier: BSD-3-Clause
