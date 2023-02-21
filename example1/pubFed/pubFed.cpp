#include "helics/helics.h"
#include <stdio.h> 

int main()
{
	HelicsFederateInfo infoStruct;
	const char* fedinitstring = "--federates=1"; // tells the broker to expect 1 federate
	HelicsFederate controlFed; // creates an instance of a federate
	HelicsPublication var; // creates an instance of a publication that would be used by the federate to pass along a message
	HelicsInput received; // creates an instance of a subscription that would be used by the federate
	HelicsTime currenttime = 0.0; //initializes the time for the federate to start 
	HelicsBool isUpdated;
	HelicsError err = helicsErrorInitialize(); // initializes an error variable to ensure that the simulation is working

	infoStruct = helicsCreateFederateInfo(); // creates a structure to hold information about the federate

	helicsFederateInfoSetCoreTypeFromString(infoStruct, "zmq", &err); //initializes the core and determines which core would be used
	helicsFederateInfoSetCoreInitString(infoStruct, fedinitstring, &err);

	helicsFederateInfoSetTimeProperty(infoStruct, helicsGetPropertyIndex("period"), 2.0, &err);

	controlFed = helicsCreateValueFederate("pubFed", infoStruct, &err);
	
	helicsFederateInfoFree(infoStruct);
	if (err.error_code != HELICS_OK)
	{
		return(-2);
	}

	var = helicsFederateRegisterGlobalPublication(controlFed, "time", HELICS_DATA_TYPE_STRING, "", &err);
	received = helicsFederateRegisterSubscription(controlFed, "sendback", NULL, &err); 

	helicsFederateEnterInitializingMode(controlFed, &err);
	
	if (err.error_code != HELICS_OK)
	{
		fprintf(stderr, "HELICS failed to enter initialization mode:%s\n", err.message);
	}
	else
	{
		printf("Initializing...\n");
	}

	helicsFederateEnterExecutingMode(controlFed, &err);
	
	if (err.error_code != HELICS_OK)
	{
		fprintf(stderr, "HELICS failed to enter execution mode:%s\n", err.message);
	}
	else
	{
		printf("Executing...\n");
	}

	helicsPublicationPublishString(var, "Hello!!", &err);

	currenttime = helicsFederateRequestTime(controlFed, 2.0, &err);
	if (err.error_code != HELICS_OK)
	{
		fprintf(stderr, "HELICS request time failed:%s\n", err.message);
	}
	else
	{
		fprintf(stdout, "HELICS granted time: %f\n", currenttime);
	}

	currenttime = helicsFederateRequestTime(controlFed, 4.0, &err); 
	isUpdated = helicsInputIsUpdated(received); 
	if (isUpdated)
	{
		int actualLen; 
		char val[128] = ""; 
		helicsInputGetString(received, val, 128, &actualLen, &err); 
		fprintf(stderr, val, err.message); 
	}

	helicsFederateFinalize(controlFed, &err);
	helicsFederateFree(controlFed);
	helicsCloseLibrary();

	return 0;
}