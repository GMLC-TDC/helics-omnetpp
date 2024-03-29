//
// Generated file, do not edit! Created by nedtool 5.7 from FaultMsg.msg.
//

#ifndef __FAULTMSG_M_H
#define __FAULTMSG_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// nedtool version check
#define MSGC_VERSION 0x0507
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of nedtool: 'make clean' should help.
#endif



/**
 * Enum generated from <tt>FaultMsg.msg:20</tt> by nedtool.
 * <pre>
 * enum State
 * {
 *     NORMAL = 0;
 *     IDLE = 1;
 *     WAIT = 2;
 *     OOS = 3;
 *     UNINITIALIZED = 4;
 * }
 * </pre>
 */
enum State {
    NORMAL = 0,
    IDLE = 1,
    WAIT = 2,
    OOS = 3,
    UNINITIALIZED = 4
};

/**
 * Enum generated from <tt>FaultMsg.msg:28</tt> by nedtool.
 * <pre>
 * enum MSGCODE
 * {
 *     //PowerGrid commands for Comms
 *     LOCAL_FAULT_EVENT = 403;
 *     REMOTE_FAULT_EVENT = 404;
 *     //Comms commands for Power Grid 
 *     BREAKER_TRIP_COMMAND = 409;
 *     BREAKER_CLOSE_COMMAND = 410;
 *     BREAKER_OOS_COMMAND = 411;
 *     //PowerGrid confirmation to Comms    
 *     BREAKER_TRIP_EVENT = 405;
 *     BREAKER_CLOSE_EVENT = 406;
 *     LOCAL_FAULT_CLEARED = 407;
 *     REMOTE_FAULT_CLEARED = 408;
 * }
 * </pre>
 */
enum MSGCODE {
    LOCAL_FAULT_EVENT = 403,
    REMOTE_FAULT_EVENT = 404,
    BREAKER_TRIP_COMMAND = 409,
    BREAKER_CLOSE_COMMAND = 410,
    BREAKER_OOS_COMMAND = 411,
    BREAKER_TRIP_EVENT = 405,
    BREAKER_CLOSE_EVENT = 406,
    LOCAL_FAULT_CLEARED = 407,
    REMOTE_FAULT_CLEARED = 408
};

/**
 * Enum generated from <tt>FaultMsg.msg:43</tt> by nedtool.
 * <pre>
 * enum MSGTYPE
 * {
 *     //Msgtype between PowerGrid and Comms
 *     pingMessageType = 1;
 *     replyMessageType = 2;
 * 
 *     //MsgType within Comms System
 *     SETLOCAL = 0;
 *     SETREMOTE = 3;
 *     REQUEST = 4;
 *     RESPONSE = 5;
 * }
 * </pre>
 */
enum MSGTYPE {
    pingMessageType = 1,
    replyMessageType = 2,
    SETLOCAL = 0,
    SETREMOTE = 3,
    REQUEST = 4,
    RESPONSE = 5
};

/**
 * Class generated from <tt>FaultMsg.msg:55</tt> by nedtool.
 * <pre>
 * packet FaultMsg
 * {
 *     int destAddr;
 *     int srcAddr;
 *     string srcNodeName = "";
 *     string msg = "";
 *     int nodeState \@enum(State);
 *     int msgType \@enum(MSGTYPE);
 * 
 * }
 * </pre>
 */
class FaultMsg : public ::omnetpp::cPacket
{
  protected:
    int destAddr;
    int srcAddr;
    ::omnetpp::opp_string srcNodeName;
    ::omnetpp::opp_string msg;
    int nodeState;
    int msgType;

  private:
    void copy(const FaultMsg& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const FaultMsg&);

  public:
    FaultMsg(const char *name=nullptr, short kind=0);
    FaultMsg(const FaultMsg& other);
    virtual ~FaultMsg();
    FaultMsg& operator=(const FaultMsg& other);
    virtual FaultMsg *dup() const override {return new FaultMsg(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    // field getter/setter methods
    virtual int getDestAddr() const;
    virtual void setDestAddr(int destAddr);
    virtual int getSrcAddr() const;
    virtual void setSrcAddr(int srcAddr);
    virtual const char * getSrcNodeName() const;
    virtual void setSrcNodeName(const char * srcNodeName);
    virtual const char * getMsg() const;
    virtual void setMsg(const char * msg);
    virtual int getNodeState() const;
    virtual void setNodeState(int nodeState);
    virtual int getMsgType() const;
    virtual void setMsgType(int msgType);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const FaultMsg& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, FaultMsg& obj) {obj.parsimUnpack(b);}


#endif // ifndef __FAULTMSG_M_H

