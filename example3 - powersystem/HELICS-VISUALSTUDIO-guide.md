## HELICS Visual Studio guide for example3 - powersystem

### Step 1. Load Example into Visual Studio

_(We will be using isolatedFault as an example)_

Open up Visual Studio

a. When you open up Visual Studio, there will be a welcome/get started pop up. You will see panel like this:

  <img src=VisualStudioGuide-images/visualStudio1.png width="550">

Choose "Create a new project"

b. Then choose "Empty Project"

  <img src=VisualStudioGuide-images/visualStudio2.png width="550">

c. Enter name the project with the file name without it’s suffix (for example: isolatedFault)

d. Choose “Create”.


i. In Solution Explorer,
```
Right click the project name (isolatedFault) > Add > Existing item ...
```

ii. Go to the location of the HELICS-omnetpp example 
```
<your path>\helics-omnetpp\example3 - powersystem\PowerSystem-HelicsFed\isolatedFault.cpp
```
Click Add. You should see the isolatedFault.cpp file appear in the Solutions Explorer under the Source Files in Visual Studio.

  <img src=VisualStudioGuide-images/visualStudio3.png width="550">

### Step 2. Link HELICS in visual studios to run example

a. Since we are using the HELICS installer, only the release version is attached. We need to make sure we’re running on “Release” and “x64” settings. Check that these are set in each tool bar of the projects

b. Go to Project > Properties > C/C++ > All Options > Additional Include Directories > Down Arrow > Edit

  <img src=VisualStudioGuide-images/visualStudio4.png width="550">

This is where you will add the Include Directory of your HELICS installation

  <img src=VisualStudioGuide-images/visualStudio5.png width="550">

Click Ok > Apply. ** Do not exit out of Properties yet **

c. Go to Linker > All Options > scroll all the way up

i. Additional Dependencies > Down Arrow > Edit

This is where you will add the HELICS static library name: helics.lib

  <img src=VisualStudioGuide-images/visualStudio6.png width="550">

Click Ok > Apply. ** Do not exit out of Properties yet. Stay in Linker**

ii. Additional Library Directories > Down Arrow > Edit

This is where you will add the directories that hold the HELICS static and dynamic libraries, helics.lib and helics.dll, i.e. from example:

  <img src=VisualStudioGuide-images/visualStudio7.png width="550">

Click Ok > Apply > Ok (This will exit you out of Properties)

d. Go to ToolBar > Build > Build Solution

e. Once the solution is built, go to the Solution Explorer. You will go to the ToolBar and click on the folder/window icon next to the Home Icon. Once clicked, you will either see

Folder View

    if you see this, you can just simply click Folder View and it’ll switch you over to the Folder View

or

    Two Options: .sln and project name with path

          if you see this, you will click the project name with the path


Once you switch to Folder View or the option with the name + path, you will go to the Folder x64 > Release. You should be able to find the .exe file  on of the project you’re looking at right now.

Here you will add the dynamic library. This is crucial part and cannot be missed or else we will have an error when we try to run the simulation.

i. Right Click on Release > Click Open Folder in File Explorer

ii. In another File Explorer, open up to your HELICS bin folder. You will find the helics.dll file. This will then be COPIED to the Release Folder that was just opened.

Click on the helics.dll in bin folder > Ctrl + c > Go over to Release folder > Ctrl + v

iii. Go back to Solutions View in order to run the solution (executable).

To do this, go back to Solution Explorer toolbar and click on folder/window icon next tot the Home Icon. Click the down arrow and choose option with .sln extension.

### Step 3. Run the example

To run the example we must have the broker running and the solution built into an executable and ran.

The broker should be located in your HELICS bin folder.

a. Open a command prompt on windows, and go to the project folder & run:

```
helics_broker -f2
```

This will tell the broker to expect the federate (ex. isolatedFault).

b. Run isolatedFault

```
Click Green Play button 'Local Windows Debugger'
```

** Microsoft visual Studio Debug console should pop up **
