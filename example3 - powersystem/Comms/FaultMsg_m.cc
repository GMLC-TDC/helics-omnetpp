//
// Generated file, do not edit! Created by nedtool 5.6 from FaultMsg.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include "FaultMsg_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i=0; i<n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp


// forward
template<typename T, typename A>
std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec);

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// operator<< for std::vector<T>
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

EXECUTE_ON_STARTUP(
    omnetpp::cEnum *e = omnetpp::cEnum::find("State");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("State"));
    e->insert(NORMAL, "NORMAL");
    e->insert(IDLE, "IDLE");
    e->insert(WAIT, "WAIT");
    e->insert(OOS, "OOS");
    e->insert(UNINITIALIZED, "UNINITIALIZED");
)

EXECUTE_ON_STARTUP(
    omnetpp::cEnum *e = omnetpp::cEnum::find("MSGTYPE");
    if (!e) omnetpp::enums.getInstance()->add(e = new omnetpp::cEnum("MSGTYPE"));
    e->insert(SETLOCAL, "SETLOCAL");
    e->insert(SETREMOTE, "SETREMOTE");
    e->insert(BACKUPRELAY, "BACKUPRELAY");
    e->insert(REQUEST, "REQUEST");
    e->insert(RESPONSE, "RESPONSE");
)

Register_Class(FaultMsg)

FaultMsg::FaultMsg(const char *name, short kind) : ::omnetpp::cPacket(name,kind)
{
    this->destAddr = 0;
    this->srcAddr = 0;
    this->srcNodeName = "";
    this->msg = "";
    this->nodeState = 0;
    this->msgType = 0;
}

FaultMsg::FaultMsg(const FaultMsg& other) : ::omnetpp::cPacket(other)
{
    copy(other);
}

FaultMsg::~FaultMsg()
{
}

FaultMsg& FaultMsg::operator=(const FaultMsg& other)
{
    if (this==&other) return *this;
    ::omnetpp::cPacket::operator=(other);
    copy(other);
    return *this;
}

void FaultMsg::copy(const FaultMsg& other)
{
    this->destAddr = other.destAddr;
    this->srcAddr = other.srcAddr;
    this->srcNodeName = other.srcNodeName;
    this->msg = other.msg;
    this->nodeState = other.nodeState;
    this->msgType = other.msgType;
}

void FaultMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cPacket::parsimPack(b);
    doParsimPacking(b,this->destAddr);
    doParsimPacking(b,this->srcAddr);
    doParsimPacking(b,this->srcNodeName);
    doParsimPacking(b,this->msg);
    doParsimPacking(b,this->nodeState);
    doParsimPacking(b,this->msgType);
}

void FaultMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cPacket::parsimUnpack(b);
    doParsimUnpacking(b,this->destAddr);
    doParsimUnpacking(b,this->srcAddr);
    doParsimUnpacking(b,this->srcNodeName);
    doParsimUnpacking(b,this->msg);
    doParsimUnpacking(b,this->nodeState);
    doParsimUnpacking(b,this->msgType);
}

int FaultMsg::getDestAddr() const
{
    return this->destAddr;
}

void FaultMsg::setDestAddr(int destAddr)
{
    this->destAddr = destAddr;
}

int FaultMsg::getSrcAddr() const
{
    return this->srcAddr;
}

void FaultMsg::setSrcAddr(int srcAddr)
{
    this->srcAddr = srcAddr;
}

const char * FaultMsg::getSrcNodeName() const
{
    return this->srcNodeName.c_str();
}

void FaultMsg::setSrcNodeName(const char * srcNodeName)
{
    this->srcNodeName = srcNodeName;
}

const char * FaultMsg::getMsg() const
{
    return this->msg.c_str();
}

void FaultMsg::setMsg(const char * msg)
{
    this->msg = msg;
}

int FaultMsg::getNodeState() const
{
    return this->nodeState;
}

void FaultMsg::setNodeState(int nodeState)
{
    this->nodeState = nodeState;
}

int FaultMsg::getMsgType() const
{
    return this->msgType;
}

void FaultMsg::setMsgType(int msgType)
{
    this->msgType = msgType;
}

class FaultMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertynames;
  public:
    FaultMsgDescriptor();
    virtual ~FaultMsgDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyname) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyname) const override;
    virtual int getFieldArraySize(void *object, int field) const override;

    virtual const char *getFieldDynamicTypeString(void *object, int field, int i) const override;
    virtual std::string getFieldValueAsString(void *object, int field, int i) const override;
    virtual bool setFieldValueAsString(void *object, int field, int i, const char *value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual void *getFieldStructValuePointer(void *object, int field, int i) const override;
};

Register_ClassDescriptor(FaultMsgDescriptor)

FaultMsgDescriptor::FaultMsgDescriptor() : omnetpp::cClassDescriptor("FaultMsg", "omnetpp::cPacket")
{
    propertynames = nullptr;
}

FaultMsgDescriptor::~FaultMsgDescriptor()
{
    delete[] propertynames;
}

bool FaultMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<FaultMsg *>(obj)!=nullptr;
}

const char **FaultMsgDescriptor::getPropertyNames() const
{
    if (!propertynames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
        const char **basenames = basedesc ? basedesc->getPropertyNames() : nullptr;
        propertynames = mergeLists(basenames, names);
    }
    return propertynames;
}

const char *FaultMsgDescriptor::getProperty(const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : nullptr;
}

int FaultMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 6+basedesc->getFieldCount() : 6;
}

unsigned int FaultMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeFlags(field);
        field -= basedesc->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<6) ? fieldTypeFlags[field] : 0;
}

const char *FaultMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldName(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldNames[] = {
        "destAddr",
        "srcAddr",
        "srcNodeName",
        "msg",
        "nodeState",
        "msgType",
    };
    return (field>=0 && field<6) ? fieldNames[field] : nullptr;
}

int FaultMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount() : 0;
    if (fieldName[0]=='d' && strcmp(fieldName, "destAddr")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "srcAddr")==0) return base+1;
    if (fieldName[0]=='s' && strcmp(fieldName, "srcNodeName")==0) return base+2;
    if (fieldName[0]=='m' && strcmp(fieldName, "msg")==0) return base+3;
    if (fieldName[0]=='n' && strcmp(fieldName, "nodeState")==0) return base+4;
    if (fieldName[0]=='m' && strcmp(fieldName, "msgType")==0) return base+5;
    return basedesc ? basedesc->findField(fieldName) : -1;
}

const char *FaultMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldTypeString(field);
        field -= basedesc->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "string",
        "string",
        "int",
        "int",
    };
    return (field>=0 && field<6) ? fieldTypeStrings[field] : nullptr;
}

const char **FaultMsgDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldPropertyNames(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 4: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        case 5: {
            static const char *names[] = { "enum",  nullptr };
            return names;
        }
        default: return nullptr;
    }
}

const char *FaultMsgDescriptor::getFieldProperty(int field, const char *propertyname) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldProperty(field, propertyname);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        case 4:
            if (!strcmp(propertyname,"enum")) return "State";
            return nullptr;
        case 5:
            if (!strcmp(propertyname,"enum")) return "MSGTYPE";
            return nullptr;
        default: return nullptr;
    }
}

int FaultMsgDescriptor::getFieldArraySize(void *object, int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldArraySize(object, field);
        field -= basedesc->getFieldCount();
    }
    FaultMsg *pp = (FaultMsg *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

const char *FaultMsgDescriptor::getFieldDynamicTypeString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldDynamicTypeString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    FaultMsg *pp = (FaultMsg *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string FaultMsgDescriptor::getFieldValueAsString(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldValueAsString(object,field,i);
        field -= basedesc->getFieldCount();
    }
    FaultMsg *pp = (FaultMsg *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getDestAddr());
        case 1: return long2string(pp->getSrcAddr());
        case 2: return oppstring2string(pp->getSrcNodeName());
        case 3: return oppstring2string(pp->getMsg());
        case 4: return enum2string(pp->getNodeState(), "State");
        case 5: return enum2string(pp->getMsgType(), "MSGTYPE");
        default: return "";
    }
}

bool FaultMsgDescriptor::setFieldValueAsString(void *object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->setFieldValueAsString(object,field,i,value);
        field -= basedesc->getFieldCount();
    }
    FaultMsg *pp = (FaultMsg *)object; (void)pp;
    switch (field) {
        case 0: pp->setDestAddr(string2long(value)); return true;
        case 1: pp->setSrcAddr(string2long(value)); return true;
        case 2: pp->setSrcNodeName((value)); return true;
        case 3: pp->setMsg((value)); return true;
        case 4: pp->setNodeState((State)string2enum(value, "State")); return true;
        case 5: pp->setMsgType((MSGTYPE)string2enum(value, "MSGTYPE")); return true;
        default: return false;
    }
}

const char *FaultMsgDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructName(field);
        field -= basedesc->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

void *FaultMsgDescriptor::getFieldStructValuePointer(void *object, int field, int i) const
{
    omnetpp::cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount())
            return basedesc->getFieldStructValuePointer(object, field, i);
        field -= basedesc->getFieldCount();
    }
    FaultMsg *pp = (FaultMsg *)object; (void)pp;
    switch (field) {
        default: return nullptr;
    }
}


