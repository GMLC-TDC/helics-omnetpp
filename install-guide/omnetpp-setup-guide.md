In order to run an OMNeT++ simulation, we must create a new OMNeT++ project.

**NOTE: You may need to set PREFER_CLANG=no and PREFER_LLD=no in configure.user in OMNeT++**

  ***This example is based on importing example1/simpletictoc.***

1. Create a new OMNeT++ Project: File > New > OMNeT++ Project.

    <img alt="omnet++ setup" src=/config_guide/ide/demo-pictures/StartOmnetProj1.png width="550"> <br>

2. Name your OMNeT++ project.

    <img alt="omnet++ setup" src=/config_guide/ide/images/start_omnet_project2.png width="550"> <br>

3. Choose Empty project. Then Finish.

    <img alt="omnet++ setup" src=/config_guide/ide/images/start_omnet_project3.png width="550"> <br>

4. What the Project Explorer looks like after creating the project. 

    <img alt="omnet++ setup" src=/config_guide/ide/images/start_omnet_project4.png width="550"> <br>

**If you are not importing an example and already implemented simulation, you can stop at step 4. If you are, please continue to the next steps**

5. Right click on project name (i.e. simpletictoc) > Import ...

    <img alt="omnet++ setup" src=/config_guide/ide/images/start_omnet_project5.png width="550"> <br>

6. General > File System

    <img alt="omnet++ setup" src=/config_guide/ide/images/start_omnet_project6.png width="550"> <br>

7. Choose the directory that has all the necessary files to run your simulation.

    <img alt="omnet++ setup" src=/config_guide/ide/images/start_omnet_project7.png width="550"> <br>

8. We usually want the files with the suffixes: .ini, .ned, and .cc

    <img alt="omnet++ setup" src=/config_guide/ide/images/start_omnet_project8.png width="550"> <br>

9. What the Project Explorer should look like after importing files.

    <img alt="omnet++ setup" src=/config_guide/ide/images/start_omnet_project9.png width="550"> <br>

* If you have not yet configured OMNeT++ with HELICS, please go to [helics-from-installer](../config_guide/ide/helics-from-installer.md) if you installed HELICS through the installer or [helics-from-source](../config_guide/ide/helics-from-source.md) if you installed HELICS from source (git).
