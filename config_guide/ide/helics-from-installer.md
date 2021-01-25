# OMNET++ IDE Configuration

*This guide is specific to the IDE configuration to link HELICS library and headers to OMNET++*

Ensure that you have already created an OMNET++ project before continuing onto this step.

- If you have not done so and need help, go to [omnetpp-setup-guide](/install-guide/omnetpp-setup-guide)

Please note that the example seen in the pictures are done with example1/simpletictoc code and that the HELICS version installed is obtained through the installer method.

- For steps on navigating HELICS installer and understanding the directories please go to [helics-installer-guide](/install-guide/helics-installer-guide)

### Step 1: Adding HELICS library and HELICS header paths to makefile generation options (Makemake).

1. In order to get to the Makemake options, you will go to Project/Properties > OMNeT++ > Makemake.

  <img alt="config-file1" src=/config_guide/ide/demo-pictures/helics-installer-config/pathsandsymbol10.PNG width="550"> <br>

2. Once you're in Makemake, you will see on the right hand panel: Build > Makemake > Options...
This will open up to a window. Navigate to Compile:

  <img alt="config-file2" src=/config_guide/ide/demo-pictures/helics-installer-config/pathsandsymbol11.PNG width="550"> <br>

3. Here you will add the include directories that hold the HELICS header files (if you are unclear of which directories these are please check [helics-installer-guide](/install-guide/helics-installer-guide)):

    <img alt="config-file3" src=/config_guide/ide/demo-pictures/helics-installer-config/pathsandsymbol12.PNG width="550"> <br>

4. Once that is done, do not exit and navigate to Link tab. Here you will add the name of the HELICS library without the suffix:

  <img alt="config-file4" src=/config_guide/ide/demo-pictures/helics-installer-config/pathsandsymbol13.PNG width="550"> <br>

5. Once done, click OK. Do not exit Properties.

### Step 2: Adding HELICS library and HELICS library/header paths to Path and Symbols.

1. On left navigation bar of Properties, navigate C/C++ General > Paths and Symbols:

    <img alt="config-file5" src=/config_guide/ide/demo-pictures/helics-installer-config/pathsandsymbol1.PNG width="550"> <br>

2. In the Includes tab, we will also be adding HELICS include/header directories here.
Make sure to check 'Add to all configurations' and 'Add to all languages'
  - This will save you the trouble of having to add the directories again in GNU C and GNU C++

    Add > File system .. > Select directories:

    <img alt="config-file6" src=/config_guide/ide/demo-pictures/helics-installer-config/pathsandsymbol2.PNG width="550">

    <img alt="config-file7" src=/config_guide/ide/demo-pictures/helics-installer-config/pathsandsymbol5.PNG width="550">

    <img alt="config-file8" src=/config_guide/ide/demo-pictures/helics-installer-config/pathsandsymbol6.PNG width="550">

3. Once the Include directories have been added, navigate to Libraries Tab. Here you will add the full path to the HELICS library:

    <img alt="config-file9" src=/config_guide/ide/demo-pictures/helics-installer-config/pathsandsymbol7.PNG width="550"> <br>

    <img alt="config-file10" src=/config_guide/ide/demo-pictures/helics-installer-config/pathsandsymbol8.PNG width="550"> <br>

    <img alt="config-file11" src=/config_guide/ide/demo-pictures/helics-installer-config/pathsandsymbol15.PNG width="550"> <br>

4. Navigate to the Library Paths Tab, and add the library directory:

    <img alt="config-file12" src=/config_guide/ide/demo-pictures/helics-installer-config/pathsandsymbol16.PNG width="550"> <br>

    <img alt="config-file13" src=/config_guide/ide/demo-pictures/helics-installer-config/pathsandsymbol9.PNG width="550"> <br>

    <img alt="config-file14" src=/config_guide/ide/demo-pictures/helics-installer-config/pathsandsymbol17.PNG width="550"> <br>

5. Once all previous steps are done, click Apply and Close.

## Step 3: Adding the HELICS dynamically-linked library to the project.

1. Right click on project name > Import ...

    <img alt="config-file15" src=/config_guide/ide/demo-pictures/StartOmnetProj5.PNG width="550"> <br>

2. General > File System

    <img alt="config-file16" src=/config_guide/ide/demo-pictures/StartOmnetProj6.PNG width="550"> <br>

3. Choose the directory that holds the HELICS dynamically-linked library then choose the library to import:

    <img alt="config-file17" src=/config_guide/ide/demo-pictures/helics-installer-config/pathsandsymbol14.PNG width="550"> <br>

4. How the Project Explorer should look after the dynamically-linked library is added:

    <img alt="config-file18" src=/config_guide/ide/demo-pictures/helics-installer-config/pathsandsymbol18.PNG width="550"> <br>
