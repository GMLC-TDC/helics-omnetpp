## HELICS Visual Studio guide for example3 - powersystem

### Step 1. Load Example into Visual Studio

_(We will be using isolatedFault as an example)_

Open up Visual Studio

a. When you open up Visual Studio, there will be a welcome/get started pop up. You will see panel like this:

***Insert IMAGE***

Choose "Create a new project"

***INSERT IMAGE***


b. Then choose "Empty Project"

***INSERT IMAGE***

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

***INSERT IMAGE***

### Step 2. Link HELICS in visual studios to run example

a. Since we are using the HELICS installer, only the release version is attached. We need to make sure we’re running on “Release” and “x64” settings. check that these are set in each tool bar of the projects:
