Helics-Omnetpp contains examples of the interaction between HELICS and OMNeT++. 

## Prerequisite
1. Install HELICS. 
2. Install OMNeT++

## Installation of HELICS 

HELICS download for preferred OS (Ubuntu, Windows, MacOS, docker) can be found [here](https://helics.readthedocs.io/en/latest/installation/index.html#).

*HELICS also provides options of installing through an installer (must donwload pre-compiled libraries from release page and add to path) or package manager.*

## Installation of OMNeT++

OMNeT++ download for preferred OS (Linux, Windows, MacOS, docker) can be found [here](https://omnetpp.org/download/).
This will download a zipped file which needs to be extracted under a directory that does not contain any spaces in the name. 

Depending on which OS you are using, you will be need to follow the instructions directed in the [Install Guide](https://doc.omnetpp.org/omnetpp/InstallGuide.pdf) on the OMNeT++ website. 

###### *\*OMNeT++ can be ran using their MSYS2 commandline tool or their IDE. Both have been embedded with their simulation kernel which is based on C++.\**

## Tips on running examples: 

- Helics library and include paths need to be added to Path and Symbols in OMNeT++ IDE and also under Properties/OMNeT++/Makemake/Build option. 
- Make sure that helics_broker is accepting the appropriate number of federates. 

## Release

HELICS and helics-omnetpp are distributed under the terms of the [BSD-3](https://github.com/GMLC-TDC/helics-omnetpp/blob/master/LICENSE) clause license. All new contributions must be made under this license.

SPDX-License-Identifier: BSD-3-Clause