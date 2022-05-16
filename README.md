Helics-Omnetpp contains examples of the interaction between HELICS and OMNeT++.

## Prerequisite
1. Install HELICS.
2. Install OMNeT++

## Installation of HELICS

HELICS download for preferred OS (Ubuntu, Windows, MacOS, docker) can be found [here](https://docs.helics.org/en/latest/user-guide/installation/index.html).

*HELICS also provides options of installing through an installer (must donwload pre-compiled libraries from release page and add to path) or package manager.*

## Installation of OMNeT++

OMNeT++ download for preferred OS (Linux, Windows, MacOS, docker) can be found [here](https://omnetpp.org/download/).
This will download a zipped file which needs to be extracted under a directory that does not contain any spaces in the name.

Depending on which OS you are using, you will be need to follow the instructions directed in the [Install Guide](https://doc.omnetpp.org/omnetpp/InstallGuide.pdf) on the OMNeT++ website.

**NOTE: You may need to set PREFER_CLANG=no and PREFER_LLD=no in configure.user**

###### **OMNeT++ can be ran using their MSYS2 commandline tool or their IDE. Both have been embedded with their simulation kernel which is based on C++.**

## Tips on running examples:

- OMNET++ examples cannot be ran simply  by importing the entire example into the workspace. You must create an OMNET++ project first and then import the necessary files.
  - In OMNET++ workspace, Go to File > New > OMNeT++ Project
  - Once Project is created, right click on project name > Import.
    - General > Filesystem > Choose directory that holds files that need to be imported i.e. .cc, .ned, .ini files.

- HELICS library and include paths need to be added to Path and Symbols in OMNeT++ IDE and also under Properties/OMNeT++/Makemake/Build option.
(For a step by step direction, please go to [config_guide](/config_guide) directory)

- Make sure that helics_broker is accepting the appropriate number of federates.

## Directory Navigation

- Config_guide
  - cmdline : Instructions on how to run OMNeT++ with HELICS on the commandline
  - ide : Instructions on how to run OMNeT++ with HELICS in the IDE
    - helics-from-installer : use this guide if you installed HELICS through the installer
    - helics-from-source : use this guide if you installed HELICS from source (git)
- Install-guide : Additional instructions for HELICS and OMNeT++
  - helics-installer-guide : Instructions to install HELICS using the installer / Break down of the HELICS directories needed for OMNeT++
  - omnetpp-setup-guide : Instructions on how to start a new OMNeT++ project (This step is needed before running any OMNeT++ project, whether you're importing a project or starting from scratch).

## Release

HELICS and helics-omnetpp are distributed under the terms of the [BSD-3](https://github.com/GMLC-TDC/helics-omnetpp/blob/master/LICENSE) clause license. All new contributions must be made under this license.

SPDX-License-Identifier: BSD-3-Clause
