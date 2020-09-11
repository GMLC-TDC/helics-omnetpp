/*
 * Federate.cc
 *
 *  Created on: Jul 20, 2020
 *      Author: hgngo
 */

#include "Federate.h"

Define_Module(Federate);

void Federate::processElectricTopo()
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

std::string Federate::splitRearrange(std::string x)
{
    std::stringstream tokenize(x);

    std::vector<std::string> buffTemp;
    std::string newString;
    std::string temp;
    while (getline(tokenize, temp, '_'))
    {
        buffTemp.push_back(temp);
    }
    newString.append("_");
    newString.append(buffTemp[2]);
    newString.append("_");
    newString.append(buffTemp[1]);

    return newString;
}

Federate::Relay Federate::createRelay(std::string nameOfNode)
{
    Relay thisRelay;
    std::stringstream tokenize(nameOfNode);

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

std::vector<std::pair<int,int>> Federate::possibleFaultLines(Relay &initRelay)
{
    std::vector<std::pair<int,int>> faultLines;
    for(int i = 0; i < Edges.size(); i++)
    {
        if ((Edges[i].first == initRelay.relayPair.first && Edges[i].second == initRelay.relayPair.second) ||
                (Edges[i].first == initRelay.relayPair.second && Edges[i].second == initRelay.relayPair.first))
        {
            continue;
        }


        if(Edges[i].first == initRelay.relayPair.second || Edges[i].second == initRelay.relayPair.second)
        {
            faultLines.push_back(std::make_pair(Edges[i].first, Edges[i].second));
        }
    }
    return faultLines;

}

void Federate::responsibleRelays(Relay &thisRelay, std::vector<std::pair<int,int>> &possibleFaultLines)
{
    std::vector<Relay> relays;

    for (int i = 0; i < possibleFaultLines.size(); i++)
    {
        int source = possibleFaultLines[i].first;
        int dest = possibleFaultLines[i].second;
        //std::cout << "Relay: (" << thisRelay.relayPair.first << "," << thisRelay.relayPair.second << ")" << thisRelay.bus << ")" << std::endl;
        //std::cout << "Fault Line: (" << source << "," << dest << ")" << std::endl;

        Relay addRelay;
        addRelay.relayPair.first = source;
        addRelay.relayPair.second = dest;
        addRelay.bus = source;
        relays.push_back(addRelay);
        addRelay.bus = dest;
        relays.push_back(addRelay);

        for(int i = 0; i < Edges.size(); i++)
        {
            if ((Edges[i].first == source && Edges[i].second == dest) ||
                    (Edges[i].first == dest && Edges[i].second == source))
            {
                continue;
            }

            if (thisRelay.relayPair.second == source)
            {

                if (dest == Edges[i].first)
                {
                    Relay addRelay;
                    addRelay.relayPair.first = Edges[i].first;
                    addRelay.relayPair.second = Edges[i].second;
                    addRelay.bus = Edges[i].second;
                    relays.push_back(addRelay);
                }
                if (dest == Edges[i].second)
                {
                    Relay addRelay;
                    addRelay.relayPair.first = Edges[i].first;
                    addRelay.relayPair.second = Edges[i].second;
                    addRelay.bus = Edges[i].first;
                    relays.push_back(addRelay);
                }

            }

            if (thisRelay.relayPair.second == dest)
            {
                if (source == Edges[i].first)
                {
                    Relay addRelay;
                    addRelay.relayPair.first = Edges[i].first;
                    addRelay.relayPair.second = Edges[i].second;
                    addRelay.bus = Edges[i].second;
                    relays.push_back(addRelay);
                }
                if (source == Edges[i].second)
                {
                    Relay addRelay;
                    addRelay.relayPair.first = Edges[i].first;
                    addRelay.relayPair.second = Edges[i].second;
                    addRelay.bus = Edges[i].first;
                    relays.push_back(addRelay);
                }

            }
        }

    }

    convertToAgentStrings(relays);
}

void Federate::convertToAgentStrings(std::vector<Federate::Relay> &protectionVect)
{
    for (int i = 0; i < protectionVect.size(); i++)
    {
        std::string agent;
        std::string agentSource = std::to_string(protectionVect[i].relayPair.first);
        std::string agentDest = std::to_string(protectionVect[i].relayPair.second);
        agent = "_" + agentSource + "_" + agentDest;

        std::vector<std::string>::iterator t = std::find(relayVect.begin(), relayVect.end(), agent);
        if (t == relayVect.end())
        {
            relayVect.push_back(agent);
        }

    }

}

void Federate::checkMsgUpdate()
{

    double omnetTime = SIMTIME_DBL(simTime());

    currenttime = helicsFederateRequestTime (commFed, omnetTime, &err);

    if (err.error_code != helics_ok)
    {
           fprintf(stderr, "HELICS request time failed\n");
    }
    else
    {
        fprintf(stdout, "HELICS granted time: %f\n", currenttime);
    }
    msgUpdated = helicsEndpointHasMessage(commsys);
    std::cout << msgUpdated << std::endl;
    if (msgUpdated)
    {
        int numMessages = helicsEndpointPendingMessages(commsys);
        while (numMessages != 0)
        {
            receivedMsg = helicsEndpointGetMessageObject(commsys);
            std::string translate = helicsMessageGetString(receivedMsg);
            buffer.push_back(translate);

            numMessages--;
        }
    }
    else
    {
        printf("No Message Received");
    }
}

void Federate::findRemoteFault(std::string faultLine)
{
    std::stringstream tokenize(faultLine);

    std::vector<std::string> buffTemp;
    std::string newString;
    std::string temp;
    while (getline(tokenize, temp, '_'))
    {
        buffTemp.push_back(temp);
    }


    int source = std::atoi(buffTemp[1].c_str());
    int dest = std::atoi(buffTemp[2].c_str());
    for (int i = 0; i < Edges.size(); i ++)
    {
        if (Edges[i].second == source && Edges[i].first != dest)
        {
            std::string remoteAdd;
            remoteAdd.append("_");
            remoteAdd.append(std::to_string(Edges[i].first));
            remoteAdd.append("_");
            remoteAdd.append(std::to_string(Edges[i].second));
            remoteFault.push_back(remoteAdd);
        }

    }

    std::cout << "This is the remote faults: " << std::endl;
    for (int i = 0; i < remoteFault.size(); i++)
    {
        std::cout << remoteFault[i] << std::endl;
    }

}

/* Assume that message sent is the transmission line that failed to isolate */
void Federate::sendOutMessage()
{

    for (int i = 0; i < buffer.size(); i++)
    {
        // in the format of _failedbus_busAtEndOfLine
        std::string currentFaultLine = buffer[i];
        // reversed agentNode
        std::string localFault = splitRearrange(buffer[i]);

        std::cout << "Failed to isolate: " << currentFaultLine << std::endl;
        std::cout << "Local Fault: " << localFault << std::endl;
        FaultMsg *faultLocal = new FaultMsg;
        faultLocal->setSrcNodeName(cSimpleModule::getName());
        faultLocal->setMsgType(SETLOCAL);
        cModule *parent = getParentModule();
        cModule *local = parent->getSubmodule(localFault.c_str());
        sendDirect(faultLocal, local, "fromFed");

        findRemoteFault(currentFaultLine);

        for (int j = 0; j < remoteFault.size(); j++)
        {
            FaultMsg *faultRemote = new FaultMsg;
            faultRemote->setSrcNodeName(cSimpleModule::getName());
            faultRemote->setMsgType(SETREMOTE);
            cModule *remote = parent->getSubmodule(remoteFault[j].c_str());
            sendDirect(faultRemote, remote, "fromFed");
        }

    }
}

void Federate::initialize()
{
    infoStruct = helicsCreateFederateInfo();
    helicsFederateInfoSetCoreTypeFromString (infoStruct, "zmq", &err);
    helicsFederateInfoSetCoreInitString (infoStruct, fedinitstring, &err);
    helicsFederateInfoSetTimeProperty( infoStruct, helics_property_time_period, 1.0, &err);

    commFed = helicsCreateMessageFederate("Comms.exe", infoStruct, &err); // fed name might need to be changed depending on the executable name

    // initializes endpoint in federate
    commsys = helicsFederateRegisterEndpoint(commFed, "commEndpt", NULL, &err );

    // initializes msg objects in federate
    receivedMsg = helicsFederateCreateMessageObject(commFed, &err);
    //responseMsg = helicsFederateCreateMessageObject(commFed, &err);

    //initializes the federate
    helicsFederateEnterInitializingMode (commFed, &err);
    if (err.error_code != helics_ok)
    {
        fprintf(stderr, "HELICS failed to enter initialization mode:%s\n", err.message);
    }
    else
    {
        printf("Initializing...\n");
    }

    //executes federates
    helicsFederateEnterExecutingMode (commFed, &err);
    if (err.error_code != helics_ok)
    {
        fprintf(stderr, "HELICS failed to enter execution mode:%s\n", err.message);
    }
    else
    {
        printf("Executing...\n");
    }

    processElectricTopo();

    checkMsgUpdate();

    sendOutMessage();


}

void Federate::handleMessage(cMessage *msg)
{

}

void Federate::finish()
{
    helicsFederateFinalize(commFed, &err);
    helicsFederateFree(commFed);
    helicsCloseLibrary();
}

