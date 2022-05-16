/*
 * HSub.cc
 *
 *  Created on: Jan 26, 2020
 *      Author: hgngo
 */
#include "ValueFederate.h"
#include <omnetpp.h>
#include "newVal_m.h"

using namespace omnetpp;


class omnetppFed: public cSimpleModule
{
protected:
    HelicsFederateInfo infoStruct;
    const char* fedinitstring = "--federates=1"; // tells the broker to expect 1 federate
    HelicsFederate controlFed; // creates an instance of a federate
    HelicsInput received; // creates an instance of a input that would take in the value provided by publication federate
    HelicsTime currenttime = 0.0; /* the current time of the simulation*/
    HelicsError err = helicsErrorInitialize();
    HelicsBool isUpdated;


    // The following redefined virtual function holds the algorithm.
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;
};

Define_Module(omnetppFed);

void omnetppFed::initialize()
{
        infoStruct = helicsCreateFederateInfo();
        helicsFederateInfoSetCoreTypeFromString (infoStruct, "zmq", &err);
        helicsFederateInfoSetCoreInitString (infoStruct, fedinitstring, &err);

        helicsFederateInfoSetTimeProperty( infoStruct, HELICS_PROPERTY_TIME_PERIOD, 2.0, &err);

        controlFed = helicsCreateValueFederate("helics-hypercube.exe", infoStruct, &err);

        // creates an instance of an input "time" for the federate received from pubFed.exe
        received = helicsFederateRegisterSubscription (controlFed, "newDim", NULL, &err);


        // creates an instance of a publication "sendback" for the federate which would be sent to pubFed.exe
        //reply = helicsFederateRegisterGlobalPublication (controlFed, "sendback", helics_data_type_string, "", &err);


        //initializes the federate
        helicsFederateEnterInitializingMode (controlFed, &err);
        if (err.error_code != HELICS_OK)
        {
            fprintf(stderr, "HELICS failed to enter initialization mode:%s\n", err.message);
        }
        else
        {
            printf("Initializing...\n");
        }

        //executes federates
        helicsFederateEnterExecutingMode (controlFed, &err);
        if (err.error_code != HELICS_OK)
        {
            fprintf(stderr, "HELICS failed to enter execution mode:%s\n", err.message);
        }
        else
        {
            printf("Executing...\n");
        }

}

void omnetppFed::handleMessage(cMessage *msg)
{
    // sets a time variable for OMNET++
    double omnetTime = SIMTIME_DBL(simTime());
    currenttime = helicsFederateRequestTime (controlFed, omnetTime, &err);

    if (err.error_code != HELICS_OK)
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
        NewVal *helicsNewDim = new NewVal;
        helicsNewDim->setNewDim(helicsInputGetDouble(received, &err));
        send(helicsNewDim, "out"); // send string in the module

    }
    else
    {
        printf("No new value!\n");
    }

}

void omnetppFed::finish()
{
    helicsFederateFinalize(controlFed, &err);
    helicsFederateFree(controlFed);
    helicsCloseLibrary();


}
