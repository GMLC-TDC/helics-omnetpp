/*
 * txc1.cc
 *
 *  Created on: Nov 25, 2019
 *      Author: hgngo
 */

#include <string.h>
#include <omnetpp.h>
#include <ValueFederate.h>

using namespace omnetpp;

/**
 * Derive the Txc1 class from cSimpleModule. In the Tictoc1 network,
 * both the `tic' and `toc' modules are Txc1 objects, created by OMNeT++
 * at the beginning of the simulation.
 */

class Txc1 : public cSimpleModule
{
protected:
    // The following redefined virtual function holds the algorithm.
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;
};

class Helics : public cSimpleModule, public SimTime // OMNET++ modules called helics - not to be confused
{
protected:
    helics_federate_info infoStruct;
    const char* fedinitstring = "--federates=1"; // tells the broker to expect 1 federate
    helics_federate controlFed; // creates an instance of a federate
    helics_input received; // creates an instance of a input that would take in the value provided by publication federate
    helics_publication reply; // creates an instance of a publication to reply to pub fed
    helics_time currenttime = 0.0; /* the current time of the simulation*/
    helics_error err = helicsErrorInitialize();
    helics_bool isUpdated;

  // The following redefined virtual function holds the algorithm.
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;
};

// The module class needs to be registered with OMNeT++
Define_Module(Txc1);
Define_Module(Helics);

void Helics::initialize()
{
    infoStruct = helicsCreateFederateInfo();
    helicsFederateInfoSetCoreTypeFromString (infoStruct, "zmq", &err);
    helicsFederateInfoSetCoreInitString (infoStruct, fedinitstring, &err);

    helicsFederateInfoSetTimeProperty( infoStruct, helics_property_time_period, 2.0, &err);

    controlFed = helicsCreateValueFederate("simpletictoc.exe", infoStruct, &err);

    helicsFederateInfoFree(infoStruct);
    // creates an instance of an input "time" for the federate received from pubFed.exe
    received = helicsFederateRegisterSubscription (controlFed, "time", NULL, &err);
    // creates an instance of a publication "sendback" for the federate which would be sent to pubFed.exe
    reply = helicsFederateRegisterGlobalPublication (controlFed, "sendback", helics_data_type_string, "", &err);
    //initializes the federate
    helicsFederateEnterInitializingMode (controlFed, &err);
    if (err.error_code != helics_ok)
    {
        fprintf(stderr, "HELICS failed to enter initialization mode:%s\n", err.message);
    }
    else
    {
        printf("Initializing...\n");
    }

    //executes federates
    helicsFederateEnterExecutingMode (controlFed, &err);
    if (err.error_code != helics_ok)
    {
        fprintf(stderr, "HELICS failed to enter execution mode:%s\n", err.message);
    }
    else
    {
        printf("Executing...\n");
    }

    // sets a time variable for OMNET++
    double omnetTime = SIMTIME_DBL(simTime());
    currenttime = helicsFederateRequestTime (controlFed, omnetTime, &err);

    if (err.error_code != helics_ok)
    {
           fprintf(stderr, "HELICS request time failed\n");
    }
    else
    {
        fprintf(stdout, "HELICS granted time: %f\n", currenttime);
    }

    isUpdated = helicsInputIsUpdated(received);
    if (isUpdated) // if there is a new value for the subscription
    {
        int actualLen;
        char value[128] = "";
        helicsInputGetString(received, value, 128, &actualLen, &err); // add value to string
        cMessage *msg = new cMessage(value);
        send(msg, "out"); // send string in the module
       }
    else
    {
        printf("No new value!\n");
    }

}

void Txc1::initialize()
{
    // Initialize is called at the beginning of the simulation.
    // To bootstrap the tic-toc-tic-toc process, one of the modules needs
    // to send the first message. Let this be `tic'.
}


void Helics::handleMessage(cMessage *msg)
{
    if (simTime() == 1.0){
        endSimulation();
    }
    else
    {
        send(msg, "out");
    }
}


void Txc1::handleMessage(cMessage *msg)
{
    if (simTime() == 1.0){
        endSimulation();
    }
    else
    {
        send(msg, "out");
    }
}

void Txc1::finish()
{

}
void Helics::finish()
{
    double omnetTime = SIMTIME_DBL(simTime());
    helicsPublicationPublishString(reply, "Simulation is done", &err);
    currenttime = helicsFederateRequestTime(controlFed, omnetTime, &err);
    if (err.error_code != helics_ok)
    {
        fprintf(stderr, "HELICS request time failed:%s\n", err.message);
    }
    else
    {
        fprintf(stdout, "HELICS granted time: %f\n", currenttime);
    }
    helicsFederateFinalize(controlFed, &err);
    helicsFederateFree(controlFed);
    helicsCloseLibrary();
}




