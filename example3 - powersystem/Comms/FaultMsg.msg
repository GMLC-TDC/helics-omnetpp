//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

//
// TODO generated message class
//

enum State { 
    NORMAL = 0;
    IDLE = 1;
    WAIT = 2;
    OOS = 3;
    UNINITIALIZED = 4; 
}

enum MSGCODE{
    //PowerGrid commands for Comms
    LOCAL_FAULT_EVENT = 403;
    REMOTE_FAULT_EVENT = 404;
    //Comms commands for Power Grid 
    BREAKER_TRIP_COMMAND = 409;
    BREAKER_CLOSE_COMMAND = 410; 
    BREAKER_OOS_COMMAND = 411;
    //PowerGrid confirmation to Comms    
    BREAKER_TRIP_EVENT = 405;
    BREAKER_CLOSE_EVENT = 406; 
    LOCAL_FAULT_CLEARED = 407; 
    REMOTE_FAULT_CLEARED = 408; 
}

enum MSGTYPE { 
    //Msgtype between PowerGrid and Comms
    pingMessageType = 1;
    replyMessageType = 2; 
    
    //MsgType within Comms System
    SETLOCAL = 0; 
    SETREMOTE = 3; 
    REQUEST = 4;
    RESPONSE = 5;
}

packet FaultMsg {
     
    int destAddr; 
    int srcAddr;
    string srcNodeName = ""; 
    string msg = "";
   	int nodeState @enum(State); 
   	int msgType @enum(MSGTYPE); 
   	
}