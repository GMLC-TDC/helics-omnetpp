# SimpleTicToc example

This example shows a simple exchange of a string between value federates in an OMNeT++ environment. 

OMNeT++ uses simple and compound modules to depict the different entities within the simulation. A compound module consists of multiple simple modules. A network is considered as a compound module.  
We will only be working with simple modules in this example. 

There are five components to consider: the Helics Federate (pubFed), the OMNeT++ Federate (simpletictoc), the two simple modules (Txc1 and Helics), and the network Tictoc1. 

In the pubFed directory, the pubFed.cpp will contain the HELICS Federate, pubFed. It provides the information that will be passed to the OMNeT++ federate, simpletictoc. The chosen value that will be published to simpletictoc is "Hello!!". 

The simpletictoc directory has three files: omnetpp.ini, tictoc1.ned, and txc1.cc. 

In OMNeT++, all simulations need a network in order to run. The modeling of this topology is found in .ned files. All simulations under OMNeT++ must also have a .ned file.  

We will be working with the network Tictoc1. 

Since a network is a compound module, this means that network TicToc1 is comprised of simple or compound modules. In this case, it will only be simple modules. The two simple modules in the TicToc1 network are tic (instance of class Txc1) and inputFed(instance of class Helics). 
Helics will be used to instantiate the OMNeT++ federate and to create the connection with the HELICS broker while Txc1 will simply be used as a module that will be bouncing the string back and forth between itself and inputFed module until a certain amount of counts have been reached. 

The omnetpp.ini is a configuration file. It is also another file that is required in the OMNeT++ simulation. You can choose to modify or not. 

## How this works

1. Execute helics_broker -f2 on commandline - be sure to be in the correct directory 
2. Execute pubFed.exe 
	- This should create a connection between the broker and pubFed. The pubFed will publish a string which will be held by the broker until the simpletictoc is connected. 
3. Execute simpletictoc.exe 
	- This should create a connection between the broker and simpletictoc. Because simpletictoc is subscribing to pubFed, when the connection is present, the broker will deliver the string pubFed had sent to simpletictoc.

## What is happening? 

The helics_broker waits for two federates to connect to it. The pubFed will first connect to it, send the string, "Hello!!", and grant the time of 2.0 if it successful. 
In the meantime, the broker will hold onto the string until simpletictoc is connected to it. 
Once simpletictoc is connected to the helics_broker, OMNeT++'s graphical runtime environment will pop up and you will see the set up of the network TicToc1. 
In the environment you will see that next to the InputFed, there is the message "Hello!" which means that the publication had succeeded. It is granted the time of 2.0. 
Pressing START in the environment will begin the OMNeT++ simulation. 
Once the message has bounced back and forth between the two modules for a number of counts, the simulation will invoke finish() and send a message back to pubFed saying, "Simulation is done!" The time, 4.0, will be granted after this exchange.


*Both federates will have publication and subscription instances to allow reply and response. Each federate will be run as their own executable.* 
