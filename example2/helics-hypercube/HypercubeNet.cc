/*
 * HypercubeNet.cc
 *
 *  Created on: Feb 3, 2020
 *      Author: ngo17
 */


#include "ValueFederate.h"
#include <omnetpp.h>
#include "newVal_m.h"

using namespace omnetpp;

class HypercubeNet : public cSimpleModule, public SimTime
{
protected:
    cModuleType *moduleType;
    cModule *mod;
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;
};

Define_Module(HypercubeNet);


void HypercubeNet::initialize()
{
    cMessage *msg = new cMessage("Inquiring New Dimensions");
    send(msg, "out");

}

void HypercubeNet::handleMessage(cMessage *msg)
{
    moduleType = cModuleType::get("Hypercube");
    mod = moduleType->create("Hypercube", this);
    mod->par("dim") = ((NewVal *)msg)->getNewDim();
    mod->par("nodetype") = "HypercubeNode";
    mod->finalizeParameters();
    mod->buildInside();
    mod->scheduleStart(simTime());
    mod->callInitialize();
}

void HypercubeNet::finish()
{

    mod->callFinish();
    mod->deleteModule();

}



