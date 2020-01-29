#include <ValueFederate.h>
#include <stdio.h> 

int main()
{
	helics_federate_info infoStruct;
	const char* fedinitstring = "--federates=1"; // tells the broker to expect 1 federate
	helics_federate controlFed; // creates an instance of a federate
	helics_publication var; // creates an instance of a publication that would be used by the federate to pass along a message
	helics_input received; // creates an instance of a subscription that would be used by the federate
	helics_time currenttime = 0.0; //initializes the time for the federate to start 
	helics_bool isUpdated;
	helics_error err = helicsErrorInitialize(); // initializes an error variable to ensure that the simulation is working

	infoStruct = helicsCreateFederateInfo(); // creates a structure to hold information about the federate

	helicsFederateInfoSetCoreTypeFromString(infoStruct, "zmq", &err); //initializes the core and determines which core would be used
	helicsFederateInfoSetCoreInitString(infoStruct, fedinitstring, &err);

	helicsFederateInfoSetTimeProperty(infoStruct, helicsGetPropertyIndex("period"), 2.0, &err);

	controlFed = helicsCreateValueFederate("pubFed.exe", infoStruct, &err);
	
	helicsFederateInfoFree(infoStruct);
	if (err.error_code != helics_ok)
	{
		return(-2);
	}

	var = helicsFederateRegisterGlobalPublication(controlFed, "time", helics_data_type_string, "", &err);
	received = helicsFederateRegisterSubscription(controlFed, "sendback", NULL, &err); 

	helicsFederateEnterInitializingMode(controlFed, &err);
	
	if (err.error_code != helics_ok)
	{
		fprintf(stderr, "HELICS failed to enter initialization mode:%s\n", err.message);
	}
	else
	{
		printf("Initializing...\n");
	}

	helicsFederateEnterExecutingMode(controlFed, &err);
	
	if (err.error_code != helics_ok)
	{
		fprintf(stderr, "HELICS failed to enter execution mode:%s\n", err.message);
	}
	else
	{
		printf("Executing...\n");
	}

	helicsPublicationPublishString(var, "Hello!!", &err);

	currenttime = helicsFederateRequestTime(controlFed, 2.0, &err);
	if (err.error_code != helics_ok)
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