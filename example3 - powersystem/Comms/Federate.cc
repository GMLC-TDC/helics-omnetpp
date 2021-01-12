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

void Federate::parseMsg(std::vector<std::string> &separateStrings, std::string msg){

    std::stringstream parse(msg);

    std::string portion;

    while (getline(parse, portion, ','))
    {
        separateStrings.push_back(portion);
    }

}


void Federate::checkMsgUpdate()
{
    currenttime = helicsFederateRequestTime (commFed, 2.0, &err);

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
        if (relayCodes.size() > 0){
            relayCodes.clear();
        }
        int numMessages = helicsEndpointPendingMessages(commsys);
        std::cout << "This is total num of messages: " << numMessages << std::endl;
        while (numMessages != 0)
        {
            receivedMsg = helicsEndpointGetMessageObject(commsys);
            std::string msgSource = helicsMessageGetSource(receivedMsg);
            std::cout << "Original source: " << msgSource << std::endl;

            std::string msg = helicsMessageGetString(receivedMsg);

            int mtype;
            int mcode;
            std::vector<std::string> strings;

            parseMsg (strings, msg);

            std::string mtypeString = strings[0].substr(6, strings[0].size() - 1);
            mtype = std::stoi(mtypeString);

            std::string mcodeString = strings[1].substr(6, strings[1].size()-1);
            mcode = std::stoi(mcodeString);

            std::cout << "This is mytpe: " << mtype << std::endl;
            std::cout << "This is mcode: " << mcode << std::endl;

            std::pair<int, int> codes;
            codes.first = mtype;
            codes.second = mcode;


            relayCodes[msgSource] = codes;
            std::cout << numMessages << std::endl;
            --numMessages;
        }
    }
    else
    {
        printf("No Message Received\n");
        helicsFederateFinalize(commFed, &err);
        helicsFederateFree(commFed);
        helicsCloseLibrary();
        endSimulation();
    }
}

void Federate::isolatedMsg(std::string relay)
{
    std::cout << "Relay: " << relay << std::endl;
    std::string isoMsg = "mtype:2,mcode:410";
    helicsMessageSetDestination(responseMsg, relay.c_str(), &err);
    helicsMessageSetData(responseMsg, isoMsg.c_str(), 128, &err);
    helicsEndpointSendMessageObject(commsys, responseMsg, &err);

    std::cout << "Message sent!" << std::endl;



}


void Federate::sendOutMessage(std::vector<std::string> names, std::vector<int> code, std::vector<int> type)
{
    cModule *parent = getParentModule();
    for(int i = 0; i < names.size(); i++)
    {
        std::cout << names[i] << ": " << code[i] << std::endl;
    }

    for(int i = 0; i < names.size(); i++)
    {
        FaultMsg *sendAgent = new FaultMsg;
        sendAgent->setSrcNodeName(cSimpleModule::getName());

        if (code[i] == LOCAL_FAULT_EVENT)
        {
            sendAgent->setMsgType(SETLOCAL);
        }
        else if (code[i] == REMOTE_FAULT_EVENT)
        {
            sendAgent->setMsgType(SETREMOTE);
        }
        cModule *agent = parent->getSubmodule(names[i].c_str());
        sendDirect(sendAgent, agent, "toAgent");
    }

}



void Federate::initialize()
{
    infoStruct = helicsCreateFederateInfo();
    helicsFederateInfoSetCoreTypeFromString (infoStruct, "zmq", &err);
    helicsFederateInfoSetCoreInitString (infoStruct, fedinitstring, &err);
    helicsFederateInfoSetTimeProperty( infoStruct, helics_property_time_period, 2.0, &err);

    commFed = helicsCreateMessageFederate("layoutTest.exe", infoStruct, &err);

    // initializes endpoint in federate
    commsys = helicsFederateRegisterGlobalEndpoint(commFed, "commEndpt", NULL, &err );


    // initializes msg objects in federate
    receivedMsg = helicsFederateCreateMessageObject(commFed, &err);
    responseMsg = helicsFederateCreateMessageObject(commFed, &err);

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


    std::map<std::string, std::pair<int, int>>::iterator it;
    std::vector<std::string> relayNames;
    std::vector<int> msgC;
    std::vector<int> msgT;

    for(it = relayCodes.begin(); it != relayCodes.end(); it++ )
    {
        relayNames.push_back(it->first);
        msgT.push_back(it->second.first);
        msgC.push_back(it->second.second);
    }

    if(relayNames.size() == 1 && msgC[0] == 403)
    {
        std::cout << "Fault isolated. Do nothing." << std::endl;
        isolatedMsg(relayNames[0]);

    }
    else
    {
        std::cout << "Fault is not isolated! DO YOUR MAGIC!!" << std::endl;
        sendOutMessage(relayNames, msgC, msgT);
    }


}

void Federate::handleMessage(cMessage *msg)
{
    std::cout << "Message from agent node received!" << std::endl;
    std::string agentNode = ((FaultMsg *)msg)->getSrcNodeName();
    std::string actionMsg = ((FaultMsg *)msg)->getMsg();
    pgActions[agentNode] = actionMsg;
    cancelAndDelete(((FaultMsg *)msg));
}

void Federate::finish()
{


    std::map<std::string, std::string>::iterator pgIterate;
    for(pgIterate = pgActions.begin(); pgIterate != pgActions.end(); pgIterate++ ){

        std::string relay = pgIterate->first;
        std::cout << "Relay: " << relay << std::endl;
        std::string isoMsg = pgIterate->second;
        helicsMessageSetDestination(responseMsg, relay.c_str(), &err);
        helicsMessageSetData(responseMsg, isoMsg.c_str(), 128, &err);
        helicsEndpointSendMessageObject(commsys, responseMsg, &err);
        std::cout << "Federate Message sent!" << std::endl;
    }


    checkMsgUpdate();

    std::map<std::string, std::pair<int, int>>::iterator it;
    std::vector<std::string> relayNames;
    std::vector<int> msgC;
    std::vector<int> msgT;

    for(it = relayCodes.begin(); it != relayCodes.end(); it++ )
    {
        relayNames.push_back(it->first);
        msgT.push_back(it->second.first);
        msgC.push_back(it->second.second);
    }

    for (int i = 0; i < relayNames.size(); i++)
    {
        if (msgC[i] == 405){
            std::cout << relayNames[i] << " has been tripped." << std::endl;
        }
        else if (msgC[i] == 406)
        {
            std::cout << relayNames[i] << " has been closed." << std::endl;
        }
        else if (msgC[i] == 407){
            std::cout << "Local fault cleared at" << relayNames[i] << std::endl;
        }
        else if (msgC[i] == 408){
            std::cout << "Remote fault cleared at" << relayNames[i] << std::endl;
        }
    }

    relayCodes.clear();
    helicsFederateFinalize(commFed, &err);
    helicsFederateFree(commFed);
    helicsCloseLibrary();
}

