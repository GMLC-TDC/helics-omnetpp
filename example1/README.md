## SimpleTicToc example

This simple example shows the use of HELICS within an OMNeT++ environment. 
OMNeT++ uses simple and compound modules to depict the different entities within the simulation. 

In the pubFed folder, there is a HELICS Federate which would be providing the information that will be passed to the OMNeT++ federate. 
In the simpletictoc folder, there is an HELICS Federate that is embedded in an OMNeT++ module. This federate would take in the information passed into it. It would pass it back and forth between that module and another module. At the end of the simulation. The federate will notify the other federate that the simulation is done. 

Both federates will have publication and subscription instances to allow reply and response. 
