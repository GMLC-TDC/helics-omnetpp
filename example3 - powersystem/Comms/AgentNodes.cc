/*
 * AgentNodes.cc
 *
 *  Created on: Jul 29, 2020
 *      Author: hgngo
 */

#include "AgentNodes.h"

Define_Module(AgentNodes);


// Returns state of current agent node
State AgentNodes::getState()
{
    return currentState;
}

// Sets the state of current agent node
void AgentNodes::setState(State x)
{
    currentState = x;
}

// Creates the topology of the IEEE 39-bus system
// This function forms the connections between agents nodes
void AgentNodes::processElectricTopo()
{
    cTopology electricTopo;
    electricTopo.extractByNedTypeName(cStringTokenizer("inet.node.inet.Router").asVector());
    for (int i = 0; i < electricTopo.getNumNodes(); i++) {
      cTopology::Node *node = electricTopo.getNode(i);
      std::string getSource = node->getModule()->getFullName();
      getSource = getSource.substr(1, getSource.length());
      int source = std::atoi(getSource.c_str());


      for (int j = 0; j < node->getNumOutLinks(); j++) {
        cTopology::Node *neighbour = node->getLinkOut(j)->getRemoteNode();
        std::string getDest = neighbour->getModule()->getFullName();
        getDest = getDest.substr(1, getDest.length());
        int dest = std::atoi(getDest.c_str());

        std::pair<int,int> addEdge;
        addEdge.first = source;
        addEdge.second = dest;
        Edges.push_back(addEdge);
      }
    }

}

// Returns a relay of the current agent node
AgentNodes::Relay AgentNodes::createRelay()
{
    Relay thisRelay;
    std::stringstream tokenize(cModule::getName());

    std::vector<std::string> buffTemp;
    std::string newString;
    std::string temp;
    while (getline(tokenize, temp, '_'))
    {
        buffTemp.push_back(temp);
    }

    thisRelay.relayPair.first = atoi(buffTemp[1].c_str());
    //std::cout << "Relay first: " << thisRelay.relayPair.first << std::endl;
    thisRelay.relayPair.second = atoi(buffTemp[2].c_str());
    //std::cout << "Relay second: " << thisRelay.relayPair.second << std::endl;
    thisRelay.bus = atoi(buffTemp[1].c_str());
    //std::cout << "Bus: " << thisRelay.bus << std::endl;

    return thisRelay;

}

// initRelay : relay of current agent node
// returns an array of all possible fault lines that's associated with initRelay
std::vector<std::pair<int,int>> AgentNodes::possibleFaultLines(Relay &initRelay)
{
    std::vector<std::pair<int,int>> faultLines;
    for(int i = 0; i < Edges.size(); i++)
    {
        if ((Edges[i].first == initRelay.relayPair.first && Edges[i].second == initRelay.relayPair.second) ||
                (Edges[i].first == initRelay.relayPair.second && Edges[i].second == initRelay.relayPair.first) )
        {
            continue;
        }


        if(initRelay.relayPair.second == Edges[i].first || initRelay.relayPair.second == Edges[i].second)
        {
            faultLines.push_back(std::make_pair(Edges[i].first, Edges[i].second));
        }
    }
    return faultLines;

}

// Function converts a vector of Relays to a vector string names for agent nodes
// This will allow the nodes to use the names of the agent nodes to send messages from source / to destination
std::vector<std::string> AgentNodes::convertToAgentStrings(std::vector<AgentNodes::Relay> protectionVect)
{
    std::vector<std::string> relayStringVect;
    for (int i = 0; i < protectionVect.size(); i++)
    {
        std::string agent;
        std::string agentSource = std::to_string(protectionVect[i].relayPair.first);
        std::string agentDest = std::to_string(protectionVect[i].relayPair.second);
        agent = "_" + agentSource + "_" + agentDest;

        std::vector<std::string>::iterator t = std::find(relayStringVect.begin(), relayStringVect.end(), agent);
        if (t == relayStringVect.end())
        {
            relayStringVect.push_back(agent);
        }
    }

    return relayStringVect;

}

// This function finds all the responsible relays for possible faulted lines
// thisRelay : current Relay that is being queried
// possibleFaultLines : the array of possibleFaultLines of thisRelay
// return an array of all responsible relays for thisRelay
std::vector<AgentNodes::Relay> AgentNodes::responsibleRelays(Relay &thisRelay, std::vector<std::pair<int,int>> &possibleFaultLines)
{
    std::vector<Relay> responsibleR;

    for (int i = 0; i < possibleFaultLines.size(); i++)
    {
        int source = possibleFaultLines[i].first; // u' in GECO paper
        int dest = possibleFaultLines[i].second; // v'  in GECO paper

        Relay addRelay;
        addRelay.relayPair.first = source;
        addRelay.relayPair.second = dest;
        addRelay.bus = source;
        //std::cout << "Primary 1: " << addRelay.relayPair.first << " " << addRelay.relayPair.second << " " << addRelay.bus << std::endl;
        responsibleR.push_back(addRelay);
        addRelay.bus = dest;
        //std::cout << "Primary 2: " << addRelay.relayPair.first << " " << addRelay.relayPair.second << " " << addRelay.bus << std::endl;
        responsibleR.push_back(addRelay);


        if (thisRelay.relayPair.second == source)
        {
            for(int j = 0; j < Edges.size(); j++)
            {
                if ((source == Edges[j].first && dest == Edges[j].second) ||
                        (dest == Edges[j].first && source == Edges[j].second))
                {
                    continue;
                }


                if (dest == Edges[j].first)
                {
                    Relay addRelay;
                    addRelay.relayPair.first = Edges[j].first;
                    addRelay.relayPair.second = Edges[j].second;
                    addRelay.bus = Edges[j].second;
                    responsibleR.push_back(addRelay);
                }
                if (dest == Edges[j].second)
                {
                    Relay addRelay;
                    addRelay.relayPair.first = Edges[j].first;
                    addRelay.relayPair.second = Edges[j].second;
                    addRelay.bus = Edges[j].first;
                    responsibleR.push_back(addRelay);
                }
            }

        }


        if (thisRelay.relayPair.second == dest)
        {
            for(int j = 0; j < Edges.size(); j++)
            {
                if ((source == Edges[j].first && dest == Edges[j].second) ||
                        (dest == Edges[j].first && source == Edges[j].second))
                {
                    continue;
                }

                if (source == Edges[j].first)
                {
                    Relay addRelay;
                    addRelay.relayPair.first = Edges[j].first;
                    addRelay.relayPair.second = Edges[j].second;
                    addRelay.bus = Edges[j].second;
                    responsibleR.push_back(addRelay);
                }
                if (source == Edges[j].second)
                {
                    Relay addRelay;
                    addRelay.relayPair.first = Edges[j].first;
                    addRelay.relayPair.second = Edges[j].second;
                    addRelay.bus = Edges[j].first;
                    responsibleR.push_back(addRelay);
                }

            }
        }

    }

    return responsibleR;

}

// If peer agent is set to be a local fault - immediately TRIP = set state to IDLE
void AgentNodes::setLocalFault(FaultMsg *receivedMsg)
{
    std::cout << "Local Fault detected at" << cSimpleModule::getName() << std::endl;

    cModule *parent = getParentModule();
    cModule *federate = parent->getSubmodule("fed");
    FaultMsg *msg = new FaultMsg;
    msg->setSrcNodeName(cSimpleModule::getName());
    msg->setMsg("mtype:2,mcode:410");
    sendDirect(msg, federate, "toFed");
    std::cout << "Message sent!" << std::endl;

    setState(IDLE);

}

// If peer agent is set to remote fault - query slave agent nodes by using following steps:
// 1. possibleFaultLines - find out all the possible faulted lines
// 2. responsibleRelays - from the possibleFaultLines, find out responsible relays - which are the two primary relays and all the back up relays for that line
// 3. Query responsible relays
// 4. Decision by relay is determined by responses from slave agents - 2 possible outcomes:
    // a. if second relay sees fault - TRIP = set peer agent to IDLE
    // b. if NONE of slave agent nodes do not see fault - BLOCK = set peer agent to OOS
void AgentNodes::setRemoteFault(FaultMsg *receivedMsg)
{
    std::cout << "Remote Fault detected at" << cSimpleModule::getName() << std::endl;

    setState(WAIT);

    Relay thisRelay = createRelay();
    std::vector<std::pair<int,int>> lines = possibleFaultLines(thisRelay);
    std::vector<Relay> responsibleRelayVect = responsibleRelays(thisRelay, lines);
    std::vector<std::string> relays = convertToAgentStrings(responsibleRelayVect);
    std::cout << "This is the relays responsible for " << cSimpleModule::getName() << ": " << std::endl;
    for (int i = 0; i < relays.size(); i++)
    {
        std::cout << relays[i] << std::endl;
    }

    totalPeerNodes = relays.size();

    for(int i = 0; i < relays.size(); i++)
    {
        peerMap[relays[i]] = UNINITIALIZED;
        FaultMsg *requestMsg = new FaultMsg;
        requestMsg->setMsgType(REQUEST);
        requestMsg->setSrcNodeName(cModule::getName());
        requestMsg->setNodeState(getState());
        cModule *parent = getParentModule();
        cModule *agentRelays = parent->getSubmodule(relays[i].c_str());
        sendDirect(requestMsg, agentRelays, "toAgent");
    }
}

// Function handles the slave agents that have been requested - slave agents include two primary protection relays and all the back up relays for specified relay
// Checks the slave agent node for its state
// Sends back state of slave agent node to original peer agent that had the remote fault
void AgentNodes::agentRequested(FaultMsg *receivedMsg)
{
    cModule *parent = getParentModule();
    FaultMsg *responseBack = new FaultMsg;
    responseBack->setSrcNodeName(cSimpleModule::getName());
    responseBack->setMsgType(RESPONSE);
    responseBack->setNodeState(getState());
    cModule *responseToNode = parent->getSubmodule(receivedMsg->getSrcNodeName());
    sendDirect(responseBack, responseToNode, "toAgent");
}

// Function processes the response from the slave agent nodes
void AgentNodes::processResponseFromSlaveAgent(FaultMsg *receivedMsg)
{
    std::string respondedPeerNode = receivedMsg->getSrcNodeName();

    cModule *parent = getParentModule();
    cModule *federate = parent->getSubmodule("fed");
    FaultMsg *msg = new FaultMsg;
    msg->setSrcNodeName(cSimpleModule::getName());
    if (receivedMsg->getNodeState() == IDLE || receivedMsg->getNodeState() == WAIT)
    {
        if (getState() != IDLE)
        {
            setState(IDLE);
            msg->setMsg("mtype:2,mcode:409");
            sendDirect(msg, federate, "toFed");
            std::cout << "Message sent!" << std::endl;
        }

    }
    else
    {
        if (peerMap[respondedPeerNode] == UNINITIALIZED)
        {
            peerMap[respondedPeerNode] = (State) receivedMsg->getNodeState();
            totalPeerNodes--;
        }

        if (totalPeerNodes <= 0) // this is the same as an agent node being blocked
        {
            std::cout << cSimpleModule::getName() << " needs to be serviced because no other faults sensed" << std::endl;
            setState(OOS);
            msg->setMsg("mtype:2,mcode:411");
            sendDirect(msg, federate, "toFed");
            std::cout << "Message sent!" << std::endl;
        }

    }

}

//Initializes the topology needed for connections between agent nodes
void AgentNodes::initialize()
{

    processElectricTopo();

}

// Message handling between agent nodes
void AgentNodes::handleMessage(cMessage *msg)
{

    if (((FaultMsg *)msg)->getMsgType() == SETLOCAL)
    {
        setLocalFault(((FaultMsg *)msg));

    }

    else if (((FaultMsg *)msg)->getMsgType() == SETREMOTE)
    {
        setRemoteFault(((FaultMsg *)msg));
    }

    else if (((FaultMsg *)msg)->getMsgType() == REQUEST)
    {

        agentRequested(((FaultMsg *)msg));

    }
    else if (((FaultMsg *)msg)->getMsgType() == RESPONSE)
    {

        processResponseFromSlaveAgent(((FaultMsg *)msg));

    }

    delete ((FaultMsg *)msg);
}

// At end of simulation check which to see which nodes have been altered
void AgentNodes::finish()
{

}
