# OMNET++ IDE Configuration - linking HELICS library and headers

*This guide is specific to the IDE configuration to link HELICS library and headers to OMNET++*

Ensure that you have already created an OMNET++ project before continuing onto this step

- If you have not done so and need help, go to [omnetpp-setup-guide](../../install-guide/omnetpp-setup-guide.md)

Please note that the example seen in the pictures are done with example1/simpletictoc code and that the HELICS version installed is obtained through the source (git).

Determine where your HELICS library and header files are. This can vary depending on the location you chose during your HELICS build.
Make note of the locations and the name of the library.

### Step 1: Adding HELICS library and HELICS header paths to makefile generation options (Makemake).

In order to get to the Makemake options, you will go to Project/Properties.

<img alt="demo5.PNG" src=/config_guide/ide/demo-pictures/demo5.PNG width="550">

Then you will choose OMNET++ on the left side bar and choose Makemake.

<img alt="demo6.PNG" src=/config_guide/ide/demo-pictures/demo6.PNG width="525">

Click on your project and on the right side, under Build and Makemake you will click Options.

<img alt="demo7.PNG" src=/config_guide/ide/demo-pictures/demo7.PNG width="525">

This will open up another window. Choose the Compile tab. This is where you will be adding the header directories.
There are two directories that hold the header files for the example HELICS build.
It is shown in the following pictures.

Make sure you double check that you get all the directories that hold the HELICS header files.

<img alt="demo8" src=/config_guide/ide/demo-pictures/demo8.PNG width="525"><br>

<img alt="demo9" src=/config_guide/ide/demo-pictures/demo9.PNG width="525"><br>

<img alt="demo9_1" src=/config_guide/ide/demo-pictures/demo9_1.PNG width="525"><br>

<img alt="demo9_2" src=/config_guide/ide/demo-pictures/demo9_2.PNG width="525"><br>


Next we will go to the Link Tab. This is where you will adding your library. You will only be entering the name of the library here. Omit the .lib suffix.

Please see pictures below to see what this looks like.

![](/config_guide/ide/demo-pictures/demo10.PNG)

![](/config_guide/ide/demo-pictures/demo11.PNG)

After that step, we are finished with adding the necessary paths and library to the makefile generation option. Click Apply to update the settings. Do not close just yet.

### Step 2: Adding HELICS library and HELICS library/header paths to Path and Symbols.

While still in Projects/Properties, on the side bar choose C/C++ General. Then choose Paths and Symbols.

In the first tab "Includes" we will be adding the same header directories we added to Makemake.

This can easily be done by choose
"Add... " -> "File system... " and then choosing the file or the directory.

Be sure to check "Add to all configurations" and "Add to all languages".

![](/config_guide/ide/demo-pictures/demo12.PNG)

![](/config_guide/ide/demo-pictures/demo12_1.PNG)

You should see the directories added to Assembly, GNU C and GNU C++.

![](/config_guide/ide/demo-pictures/demo12_2.PNG)

Now you will add the HELICS library and path to the two tabs: Libraries and Library Paths, respectively.
This time, unlike the Makemake option, you will be adding the full path to the library in the Libraries tab.

See the following pictures.

![](/config_guide/ide/demo-pictures/demo13.PNG)

![](/config_guide/ide/demo-pictures/demo14.PNG)

![](/config_guide/ide/demo-pictures/dem15.PNG)

Be sure to click "Apply" before closing everything.

### Step 3: Adding the HELICS and ZMQ dynamically-linked libraries to the project.

Go to "File" or right click on the project. Choose "Import" -> "General" -> "File System" and browse for the directories that the DLL are in.

![](/config_guide/ide/demo-pictures/demo15.PNG)

Select the file and import it into the project.

![](/config_guide/ide/demo-pictures/demo16.PNG)

![](/config_guide/ide/demo-pictures/demo17.PNG)

This will automatically add the libraries to the Binaries folder of the project.

![](/config_guide/ide/demo-pictures/demo18.PNG)
