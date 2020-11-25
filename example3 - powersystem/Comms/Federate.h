/*
 * Federate.h
 *
 *  Created on: Sep 1, 2020
 *      Author: hgngo
 */

#ifndef FEDERATE_H_
#define FEDERATE_H_

#include "MessageFederate.h"
#include "FaultMsg_m.h"
#include <omnetpp.h>
#include<vector>
#include<sstream>
#include<algorithm>

using namespace omnetpp;

class Federate: public cSimpleModule, public cTopology
{
private:
    helics_federate_info infoStruct; // info struct for federate
    const char* fedinitstring = "--federates=1"; // tells the broker to expect 1 federate
    helics_federate commFed; // creates an instance of a federate
    helics_time currenttime = 0.0; /* the current time of the simulation*/
    helics_error err = helicsErrorInitialize();
    helics_bool msgUpdated; // returns true if updated, returns false if not

    helics_endpoint commsys; // name of federate endpoint
    helics_message_object receivedMsg; // message object for federate endpoint

    std::vector<std::string> buffer; // buffer for messages sent from PowerGrid Fed

    struct Relay
    {
        std::pair<int, int> relayPair;
        int bus;
    };

    /* Transmission lines represented as Edges */
    std::vector<std::pair<int,int>> Edges;


    /* Every Relay connected to Agent Node */
    std::vector<std::string> relayVect;

    /* Remote Faults of given fault Line */
    std::vector<std::string> remoteFault;

    /* Local Fault of given fault Line */



protected:
    /* Initializes variables for simulation */
    virtual void initialize();

    /* Represents events in the simulation - what happens when a message arrives at the gate */
    virtual void handleMessage(cMessage *msg);

    /* Destructor for simulation - releases/destroys any variables */
    virtual void finish();

public:

    /* Function takes electrical grid topology and places all the transmission lines into the form of edges for communication network to referece.*/
    void processElectricTopo();

    /* Function rearranges the two ends of the fault lines */
    std::string splitRearrange(std::string x);

    /* Function takes in name of Agent Node and places it in a struct that would represent the Relay */
    Relay createRelay(std::string nameOfNode);

    /*Function finds all the possible fault lines that are associated with given Relay*/
    std::vector<std::pair<int,int>> possibleFaultLines(Relay &initRelay);

    /* Function finds all responsible relays for fault line */
    void responsibleRelays(Relay &thisRelay, std::vector<std::pair<int,int>> &possibleFaultLines);

    /* Function translates Relay Struct into string and adds to Relay Vector */
     void convertToAgentStrings(std::vector<Relay> &protectionVect);

    /* Function queries broker for any new messages */
    void checkMsgUpdate();

    void findRemoteFault(std::string faultLine);

    /* Function sends out alert/state message to Agent Nodes*/
    void sendOutMessage();


};




#endif /* FEDERATE_H_ */