// PublishHCN.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <ValueFederate.h>
#include <stdio.h>
#include <iostream>

int main()
{
    helics_federate_info fedinfo; 
    const char* fedinitstring = "--federates=1";
    helics_federate fed; 
    helics_publication nodes; 
    helics_time currenttime = 0.0;
    helics_error err = helicsErrorInitialize();

    fedinfo = helicsCreateFederateInfo();

    helicsFederateInfoSetCoreTypeFromString(fedinfo, "zmq", &err);
    helicsFederateInfoSetCoreInitString(fedinfo, fedinitstring, &err); 
    helicsFederateInfoSetTimeProperty(fedinfo, helicsGetPropertyIndex("period"), 1.0, &err);

    fed = helicsCreateValueFederate("PublishHCN.exe", fedinfo, &err);
	if (err.error_code != helics_ok)
	{
		return(-2);
	}

	nodes = helicsFederateRegisterGlobalPublication(fed, "newDim", helics_data_type_double, "", &err);


	helicsFederateEnterInitializingMode(fed, &err);

	if (err.error_code != helics_ok)

	{
		fprintf(stderr, "HELICS failed to enter initialization mode:%s\n", err.message);
	}
	else
	{
		printf("Initializing...\n");
	}

	helicsFederateEnterExecutingMode(fed, &err);

	if (err.error_code != helics_ok)
	{
		fprintf(stderr, "HELICS failed to enter execution mode:%s\n", err.message);
	}
	else
	{
		printf("Executing...\n");
	}

	helicsPublicationPublishDouble(nodes, 4.0, &err);

	currenttime = helicsFederateRequestTime(fed, 2.0, &err);
	if (err.error_code != helics_ok)
	{
		fprintf(stderr, "HELICS request time failed:%s\n", err.message);
	}
	else
	{
		fprintf(stdout, "HELICS granted time: %f\n", currenttime);

	}


	helicsFederateFinalize(fed, &err);
	helicsFederateFree(fed);
	helicsCloseLibrary();

	return 0;

}
