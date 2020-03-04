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
// TODO auto-generated type
//
network HelicsHypercubeNet
{
    submodules:
        omnetpp: omnetppFed {
            @display("p=86,205");
        }
        hypeCubeNetwork: HypercubeNet {
            @display("p=452,337");
        }
    connections:
        omnetpp.out --> hypeCubeNetwork.in;
        omnetpp.in <-- hypeCubeNetwork.out;
}
