# OMNET++ Command-line configuration - linking HELICS library and headers

*This guide is specific to the command line configuration that links HELICS library and headers to OMNET++*

Determine where your HELICS libraries (.lib and .dll) and header files are. This can vary depending on the location you chose during your HELICS build.
Make note of the locations and the name of the libraries.

Go to the root directory of chosen project.
For example, if you are running simpletictoc, go to the folder that holds the * .ned, * .msg, * .cc, and * .h.

## Step 1: Add the dynamically-linked libraries: helics & zmq.

These libraries have the suffix ".dll".

The HELICS dll should look something like this "helicsSharedLib.dll".

The ZMQ dll should look something like this
"libzmq-v142-mt-gd-4_3_2.dll"

These could vary depending on your HELICS version and build.

You will be copying these two libraries directly into the project like this:

![](/config_guide/cmdline/demo-pictures/demo1.jpg)

![](/config_guide/cmdline/demo-pictures/demo2.jpg)

## Step 2: Makefile generation

OMNET++ provides a tool that helps manage the build of C/C++ programs: opp_makemake. This tool handles the automatic generation of Makefiles for source files that are found in the current directory and optionally, subdirectories.

In order to link the HELICS library/include paths and HELICS library, you need to use the following options with the **opp_makemake** command:

-I\<include path>

-L\<library path>

-l\<library name>

In this example you will see that absolute paths have been used.

![](/config_guide/cmdline/demo-pictures/demo3.jpg)

After running this command, there should be a generated Makefile. This should successfully link HELICS to OMNET++.

The next two steps will take you through running the rest of your project.

## Step 3: Make

Running "make" will generate an executable for your project. This would output
your name-chosen executeable or the default which is the name of the folder with the suffix .exe.  

## Step 4: Execution

In order to execute your executable, simply type in "./" followed by the name of your executeable.

** For subdirectory build / compilation please refer to OMNET++ manual [here](https://doc.omnetpp.org/omnetpp/manual/#sec:build-sim-progs:opp-makemake).
