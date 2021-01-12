/*
 * AgentNodes.h
 *
 *  Created on: Jul 29, 2020
 *      Author: hgngo
 */

#ifndef AGENTNODES_H_
#define AGENTNODES_H_

#include "FaultMsg_m.h"
#include<omnetpp.h>
#include<iostream>
#include<utility>
#include<vector>
#include<sstream>
#include<algorithm>

using namespace omnetpp;

class AgentNodes: public cSimpleModule, public cTopology, public SimTime
{
private:
    // current state of Agent Node
    State currentState;

    //Relay structure for Agent Node
    struct Relay
    {
        std::pair<int, int> relayPair;
        int bus;
    };

    // Transmission lines of power grid represented as Edges
    std::vector<std::pair<int,int>> Edges;


    //std::vector<Relay> relayProtection;
    //std::vector<std::string> relays;
    std::map<std::string, State> peerMap;
    std::vector<std::string> backUpRelays;
    int totalPeerNodes = 0;




protected:
    /* Initializes variables for simulation */
    virtual void initialize();

    /* Represents events in the simulation - what happens when a message arrives at the gate */
    virtual void handleMessage(cMessage *msg);

    /* Destructor for simulation - releases/destroys any variables */
    virtual void finish();

public:
    /* Constructor of each Agent Node instantiated with NORMAL state*/
    AgentNodes():currentState(NORMAL){};

    /* To change state of node */
    void setState(State x);

    /* To get agent node's current state */
    State getState();

    /* Function places Agent Node in a struct that would represent the Relay */
    Relay createRelay();

    /* Function takes electrical grid topology and places all the transmission lines into the form of edges for communication network to referece.*/
    void processElectricTopo();

    /*Function finds all the possible fault lines that are associated with given Relay*/
    std::vector<std::pair<int,int>> possibleFaultLines(Relay &initRelay);


    std::vector<std::string> convertToAgentStrings(std::vector<AgentNodes::Relay> protectionVect);

    std::vector<Relay> responsibleRelays(Relay &thisRelay, std::vector<std::pair<int,int>> &possibleFaultLines);

    /*Agent Node is set as a local fault therefore state would be IDLE */
    void setLocalFault(FaultMsg *receivedMsg);

    /*Agent Node is set as remote fault therefore state would be WAIT and query peers*/
    void setRemoteFault(FaultMsg *receivedMsg);

    /*Agent Node has been requested by a peer for its current State */
    void agentRequested(FaultMsg *receivedMsg);

    /*Agent Node ("Wait" node) is given response by peers, proceed with */
    void processResponseFromSlaveAgent(FaultMsg *receivedMsg);


};




#endif /* AGENTNODES_H_ */
