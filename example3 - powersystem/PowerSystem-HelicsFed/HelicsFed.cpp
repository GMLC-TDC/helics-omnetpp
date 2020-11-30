// TestSub.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "MessageFederate.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <stdlib.h>
#include<stdio.h>

void readAgentNodes(std::vector<std::string>& listAgent, std::string name)
{
	std::ifstream textfile;
	textfile.open(name);
	if (textfile.is_open())
	{
		std::string agent;
		while (getline(textfile, agent))
		{
			listAgent.push_back(agent);
		}
		textfile.close();
	}

}

std::string chooseRandomAgent(std::vector<std::string>& listAgent)
{
	int index = rand()%68 ;

	return listAgent[index];

}


int main()
{
	std::vector<std::string> agentsList;
	helics_federate_info infoStruct;
	const char* fedinitstring = "--federates=1"; //tells the broker to expect 1 federate
	helics_federate subFed;
	helics_endpoint subEndpt;
	helics_message_object sendMsg;
	//helics_message_object rcvdMsg;
	helics_time currenttime = 0.0;

	////bool msgUpdate;

	int numRuns = 1;

	readAgentNodes(agentsList, "agentnodes.txt");

	helics_error err = helicsErrorInitialize();

	infoStruct = helicsCreateFederateInfo();

	helicsFederateInfoSetCoreTypeFromString(infoStruct, "zmq", &err);
	helicsFederateInfoSetCoreInitString(infoStruct, fedinitstring, &err);

	helicsFederateInfoSetTimeProperty(infoStruct, helicsGetPropertyIndex("period"), 1.0, &err);

	subFed = helicsCreateMessageFederate("HelicsFed.exe", infoStruct, &err); // name might need to be changed depending on name of executable

	helicsFederateInfoFree(infoStruct);

	if (err.error_code != helics_ok)
	{
		return (-2);
	}

	subEndpt = helicsFederateRegisterEndpoint(subFed, "Re:Griddyn", NULL, &err);
	//rcvdMsg = helicsFederateCreateMessageObject(subFed, &err);

	sendMsg = helicsFederateCreateMessageObject(subFed, &err);



	//Initialize all variables
	helicsFederateEnterInitializingMode(subFed, &err);

	if (err.error_code != helics_ok)
	{
		fprintf(stderr, "HELICS failed to enter initialization mode:%s\n", err.message);
	}
	else
	{
		printf("Initializing...\n");
	}
	// Enter simulation execution
	helicsFederateEnterExecutingMode(subFed, &err);

	if (err.error_code != helics_ok)
	{
		fprintf(stderr, "HELICS failed to enter execution mode:%s\n", err.message);
	}
	else
	{
		printf("Executing...\n");
	}


	/*int j = 2;
	while (j != 0)
	{
		helicsMessageSetDestination(sendMsg, "layoutTest.exe/commEndpt", &err);
		std::string msg = chooseRandomAgent(agentsList);
		std::cout << msg.c_str() << std::endl;
		helicsMessageSetData(sendMsg, msg.c_str(), 128, &err);
		helicsEndpointSendMessageObject(subEndpt, sendMsg, &err);

		j--;

	}*/

	helicsMessageSetDestination(sendMsg, "layoutTest.exe/commEndpt", &err);
	std::string msg = "_4_14";
	helicsMessageSetData(sendMsg, msg.c_str(), 128, &err);
	helicsEndpointSendMessageObject(subEndpt, sendMsg, &err);





/*	currenttime = helicsFederateRequestTime(subFed, 1.0, &err);

	if (err.error_code != helics_ok)
	{
		fprintf(stderr, "HELICS request time failed:%s\n", err.message);
	}
	else
	{
		fprintf(stdout, "HELICS granted time: %f\n", currenttime);
	}

	msgUpdate = helicsEndpointHasMessage(subEndpt);

	printf("%d\n", msgUpdate);


	if (msgUpdate)
	{
		rcvdMsg = helicsEndpointGetMessageObject(subEndpt);
		fprintf(stdout, "Message: %s\n", helicsMessageGetString(rcvdMsg));

		helicsMessageSetData(responseMsg, "received", 128, &err);
		helicsMessageSetDestination(responseMsg, "PGsim.exe/Griddyn", &err);
		helicsEndpointSendMessageObject(subEndpt, responseMsg, &err);
	}

	else
	{
		printf("No Message\n");
	}
*/

	helicsFederateFinalize(subFed, &err);
	helicsFederateFree(subFed);
	helicsCloseLibrary();

	return 0;


}
