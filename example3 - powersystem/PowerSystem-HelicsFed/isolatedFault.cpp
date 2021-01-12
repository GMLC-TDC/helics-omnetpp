// isolatedFault.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "MessageFederate.h" 
#include <iostream>
#include <vector> 
#include <fstream> 
#include <string>
#include <stdlib.h> 
#include<stdio.h>
#include<sstream>
#include<algorithm>
#include<string>

enum MSGTYPE
{
	//Msgtype between PowerGrid and Comms
	pingMessageType = 1,
	replyMessageType = 2
};

enum MSGCODE
{
	//PowerGrid commands for Comms
	LOCAL_FAULT_EVENT = 403,
	REMOTE_FAULT_EVENT = 404,
	//Comms commands for Power Grid 
	BREAKER_TRIP_COMMAND = 409,
	BREAKER_CLOSE_COMMAND = 410,
	BREAKER_OOS_COMMAND = 411,
	//PowerGrid confirmation to Comms    
	BREAKER_TRIP_EVENT = 405,
	BREAKER_CLOSE_EVENT = 406,
	LOCAL_FAULT_CLEARED = 407,
	REMOTE_FAULT_CLEARED = 408
};



void sendFault(std::string relayName, helics_endpoint endpoint, helics_message_object msgTo, MSGCODE confCode, helics_error thisErr)
{
	helicsMessageSetSource(msgTo, relayName.c_str(), &thisErr);
	helicsMessageSetDestination(msgTo, "commEndpt", &thisErr);
	std::string msg;
	switch (confCode)
	{
	case LOCAL_FAULT_EVENT:
		msg = "mtype:1,mcode:403";
		break;
	case REMOTE_FAULT_EVENT:
		msg = "mtype:1,mcode:404";
		break;
	}

	helicsMessageSetData(msgTo, msg.c_str(), 128, &thisErr);
	helicsEndpointSendMessageObject(endpoint, msgTo, &thisErr);

	std::cout << "Message sent!" << std::endl;
}

void confirmationMsg(std::string relayName, helics_endpoint endpoint, helics_message_object msgTo, MSGCODE confCode, helics_error thisErr)
{
	helicsMessageSetSource(msgTo, relayName.c_str(), &thisErr);
	helicsMessageSetDestination(msgTo, "commEndpt", &thisErr);
	std::string msg;
	switch (confCode)
	{
	case BREAKER_TRIP_EVENT:
		msg = "mtype:2,mcode:405";
		break;
	case BREAKER_CLOSE_EVENT:
		msg = "mtype:2,mcode:406";
		break;
	case LOCAL_FAULT_CLEARED:
		msg = "mtype:2,mcode:407";
		break;
	case REMOTE_FAULT_CLEARED:
		msg = "mtype:2,mcode:408";
		break;
	}

	helicsMessageSetData(msgTo, msg.c_str(), 128, &thisErr);
	helicsEndpointSendMessageObject(endpoint, msgTo, &thisErr);

	std::cout << "Message sent!" << std::endl;

}

void parseMsg(std::vector<std::string>& separateStrings, std::string msg) {

	std::stringstream parse(msg);

	std::string portion;

	while (getline(parse, portion, ','))
	{
		separateStrings.push_back(portion);
	}

}

void query(helics_time time, helics_federate fed, bool update, helics_error thisErr)
{
	time = helicsFederateRequestTime(fed, 4.0, &thisErr);
	helics_message_object bufferMsg;
	if (thisErr.error_code != helics_ok)
	{
		fprintf(stderr, "HELICS request time failed:%s\n", thisErr.message);
	}
	else
	{
		fprintf(stdout, "HELICS granted time: %f\n", time);
	}


	update = helicsFederateHasMessage(fed);

	printf("%d\n", update);
	int numMessages = helicsFederatePendingMessages(fed);
	std::cout << "Total number of messages: " << numMessages << std::endl;

	if (update)
	{
		while (numMessages != 0)
		{
			bufferMsg = helicsFederateGetMessageObject(fed);
			fprintf(stdout, "Message: %s\n", helicsMessageGetString(bufferMsg));
			std::string bufferString = helicsMessageGetString(bufferMsg);

			int mtype;
			int mcode;
			std::vector<std::string> strings;
			std::cout << "This is source: " << helicsMessageGetSource(bufferMsg) << std::endl;
			parseMsg(strings, bufferString);

			std::string mtypeString = strings[0].substr(6, strings[0].size() - 1);
			mtype = std::stoi(mtypeString);

			std::string mcodeString = strings[1].substr(6, strings[1].size() - 1);
			mcode = std::stoi(mcodeString);

			std::cout << "This is mytpe: " << mtype << std::endl;
			std::cout << "This is mcode: " << mcode << std::endl;

			std::string bufferDest = helicsMessageGetDestination(bufferMsg);

			helics_message_object confirmMsg = helicsFederateCreateMessageObject(fed, &thisErr);
			if (mtype == replyMessageType)
			{
				if (mcode == BREAKER_TRIP_COMMAND)
				{
					confirmationMsg(bufferDest, helicsFederateGetEndpoint(fed, bufferDest.c_str(), &thisErr), confirmMsg, BREAKER_TRIP_EVENT, thisErr);
					std::cout << "Sent break trip event" << std::endl;
				}
				else if (mcode == BREAKER_CLOSE_COMMAND)
				{
					confirmationMsg(bufferDest, helicsFederateGetEndpoint(fed, bufferDest.c_str(), &thisErr), confirmMsg, BREAKER_CLOSE_EVENT, thisErr);
					std::cout << "Sent break close event" << std::endl;
				}
				else if (mcode == BREAKER_OOS_COMMAND)
				{
					std::cout << "Sent breaker out of service event" << std::endl;
				}
				else
				{

				}
			}
			else
			{
				std::cout << "Invalid message type!" << std::endl;
			}

			numMessages--;
		}
	}

	else
	{
		printf("No Message\n");
	}


}



int main()
{
	std::vector<std::string> agentsList;
	helics_federate_info infoStruct;
	const char* fedinitstring = "--federates=1"; //tells the broker to expect 1 federate
	helics_federate subFed;
	helics_endpoint _14_4;
	helics_message_object sendMsg;
	helics_message_object rcvdMsg;
	helics_time currenttime = 0.0;

	bool msgUpdate;

	helics_error err = helicsErrorInitialize();

	infoStruct = helicsCreateFederateInfo();

	helicsFederateInfoSetCoreTypeFromString(infoStruct, "zmq", &err);
	helicsFederateInfoSetCoreInitString(infoStruct, fedinitstring, &err);

	helicsFederateInfoSetTimeProperty(infoStruct, helicsGetPropertyIndex("period"), 2.0, &err);

	subFed = helicsCreateMessageFederate("NonisolatedFault.exe", infoStruct, &err);

	helicsFederateInfoFree(infoStruct);

	if (err.error_code != helics_ok)
	{
		return (-2);
	}

	_14_4 = helicsFederateRegisterGlobalEndpoint(subFed, "_14_4", NULL, &err);

	rcvdMsg = helicsFederateCreateMessageObject(subFed, &err);

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

	/*Sending out fault messages*/
	sendFault("_14_4", _14_4, sendMsg, LOCAL_FAULT_EVENT, err);

	/*Request time & query for messages*/

	query(currenttime, subFed, &msgUpdate, err);

	helicsFederateFinalize(subFed, &err);
	helicsFederateFree(subFed);
	helicsCloseLibrary();

	return 0;


}

