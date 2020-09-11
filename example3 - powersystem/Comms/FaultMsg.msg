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
    WAIT =2;
    OOS = 3;
    UNINITIALIZED = 4; 
}

enum MSGTYPE { 
    
    SETLOCAL = 0; 
    SETREMOTE = 1; 
    BACKUPRELAY = 2;
    REQUEST = 3;
    RESPONSE = 4;
}

packet FaultMsg {
     
    int destAddr; 
    int srcAddr;
    string srcNodeName = ""; 
    string msg = "";
   	int nodeState @enum(State); 
   	int msgType @enum(MSGTYPE); 
   	
}