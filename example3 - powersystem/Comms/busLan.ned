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




import inet.common.misc.ThruputMeteringChannel;
import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.node.inet.Router;
import inet.node.inet.StandardHost;
import ned.DatarateChannel;

simple Federate
{
    gates:
        inout gate[];
        input toFed @directIn; 
}


network WAN
{
    @display("bgb=3866.3528,2100.241");
    types:
        channel C extends ThruputMeteringChannel
        {
            delay = 5ns;
            datarate = 100Mbps;
        }

    submodules:
        configurator: Ipv4NetworkConfigurator {

            @display("p=55,30");
        }
        // router declaration: 
        r1: Router {
            @display("p=356.7395,515.0112");
        }
        r2: Router {
            @display("p=773.773,268.81076");
        }
        r3: Router {
            @display("p=984.802,515.0112");
        }
        r4: Router {
            @display("p=1590.2543,1082.7798");
        }
        r5: Router {
            @display("p=1155.635,1082.7798");
        }
        r6: Router {
            @display("p=1057.6572,1540.0093");
        }
        r7: Router {
            @display("p=643.136,1540.0093");
        }
        r8: Router {
            @display("p=643.136,1133.0248");
        }
        r9: Router {
            @display("p=258.76175,1540.0093");
        }
        r10: Router {
            @display("p=1846.5037,1678.183");
        }
        r11: Router {
            @display("p=1527.448,1655.5728");
        }
        r13: Router {
            @display("p=2150.486,1560.1072");
        }
        r14: Router {
            @display("p=1992.2142,1082.7798");
        }
        r15: Router {
            @display("p=2459.4927,1336.517");
        }
        r16: Router {
            @display("p=2906.673,1414.3967");
        }
        r17: Router {
            @display("p=2090.192,653.185");
        }
        r18: Router {
            @display("p=1467.1539,630.57477");
        }
        r19: Router {
            @display("p=2831.3057,1766.1117");
        }
        r21: Router {
            @display("p=3223.2168,1733.4525");
        }
        r22: Router {
            @display("p=3368.9272,1384.2498");
        }
        r23: Router {
            @display("p=3368.9272,977.26526");
        }
        r24: Router {
            @display("p=3125.239,1035.047");
        }
        r25: Router {
            @display("p=1394.2987,183.39424");
        }
        r26: Router {
            @display("p=2710.7178,366.78848");
        }
        r27: Router {
            @display("p=2459.4927,542.646");
        }
        r28: Router {
            @display("p=3027.2612,228.61475");
        }
        r29: Router {
            @display("p=3368.9272,414.52124");
        }
        r39: Router {

            @display("p=356.7395,899.3855");
        }

        //csma nodes: 
        lan1: StandardHost {
            @display("p=195.95549,404.47223");
        }
        lan2: StandardHost {
            @display("p=457.2295,125.612495");
        }
        lan3: StandardHost {
            @display("p=698.4055,630.57477");
        }
        lan4: StandardHost {
            @display("p=1527.448,1346.566");
        }
        lan5: StandardHost {
            @display("p=1017.46124,811.4567");
        }
        lan6: StandardHost {
            @display("p=1057.6572,1904.2855");
        }
        lan7: StandardHost {
            @display("p=643.136,1904.2855");
        }
        lan8: StandardHost {
            @display("p=829.0425,1248.5883");
        }
        lan9: StandardHost {
            @display("p=258.76175,1929.408");
        }
        lan10: StandardHost {
            @display("p=1911.8223,1967.0917");
        }
        lan11: StandardHost {
            @display("p=1492.2765,1929.408");
        }
        lan13: StandardHost {
            @display("p=2248.4636,1929.408");
        }
        lan14: StandardHost {
            @display("p=2009.7999,899.3855");
        }
        lan15: StandardHost {
            @display("p=2459.4927,1590.2543");
        }
        lan16: StandardHost {
            @display("p=2808.6956,1035.047");
        }
        lan17: StandardHost {
            @display("p=1605.3278,401.96");
        }
        lan18: StandardHost {
            @display("p=1248.5883,404.47223");
        }
        lan19: StandardHost {
            @display("p=2808.6956,2002.2632");
        }
        lan21: StandardHost {
            @display("p=3547.2969,1929.408");
        }
        lan22: StandardHost {
            @display("p=3645.2747,1434.4948");
        }
        lan23: StandardHost {
            @display("p=3645.2747,977.26526");
        }
        lan24: StandardHost {
            @display("p=3090.0674,741.1137");
        }
        lan25: StandardHost {
            @display("p=1678.183,95.4655");
        }
        lan26: StandardHost {
            @display("p=2660.4727,206.0045");
        }
        lan27: StandardHost {
            @display("p=2263.537,454.71725");
        }
        lan28: StandardHost {
            @display("p=3321.1943,125.612495");
        }
        lan29: StandardHost {
            @display("p=3645.2747,414.52124");
        }
        lan39: StandardHost {
            @display("p=195.95549,929.5325");
        }

        // Agent Nodes
        _1_2: AgentNodes {
            @display("p=75.3675,228.61475");
        }
        _1_39: AgentNodes {
            @display("p=75.3675,630.57477");
        }

        _2_1: AgentNodes {
            @display("p=314.03125,95.4655");
        }
        _2_3: AgentNodes {
            @display("p=512.49896,268.81076");
        }
        _2_25: AgentNodes {

            @display("p=695.89325,95.4655");
        }

        _3_2: AgentNodes {
            @display("p=509.98676,741.1137");
        }
        _3_4: AgentNodes {
            @display("p=715.9912,786.3342");
        }
        _3_18: AgentNodes {
            @display("p=715.9912,454.71725");
        }

        _4_3: AgentNodes {
            @display("p=1371.6885,1220.9535");
        }
        _4_5: AgentNodes {
            @display("p=1391.7865,1472.1785");
        }
        _4_14: AgentNodes {


            @display("p=1663.1095,1298.8333");
        }


        _5_4: AgentNodes {
            @display("p=1173.2207,884.312");
        }
        _5_6: AgentNodes {
            @display("p=1055.145,1220.9535");
        }
        _5_8: AgentNodes {


            @display("p=869.23846,849.1405");
        }


        _6_5: AgentNodes {
            @display("p=959.6795,1678.183");
        }
        _6_7: AgentNodes {
            @display("p=869.23846,1904.2855");
        }
        _6_11: AgentNodes {

            @display("p=1228.4902,1929.408");
        }

        _7_6: AgentNodes {
            @display("p=771.26074,1733.4525");
        }
        _7_8: AgentNodes {


            @display("p=530.0847,1733.4525");
        }
        _8_5: AgentNodes {
            @display("p=746.13824,977.26526");
        }
        _8_7: AgentNodes {

            @display("p=771.26074,1434.4948");
        }
        _8_9: AgentNodes {


            @display("p=545.15826,1336.517");
        }


        _9_8: AgentNodes {
            @display("p=381.862,1678.183");
        }
        _9_39: AgentNodes {

            @display("p=125.612495,1766.1117");
        }
        _10_11: AgentNodes {
            @display("p=1733.4525,1843.9915");
        }
        _10_13: AgentNodes {

            @display("p=1967.0917,1791.2343");
        }
        _11_6: AgentNodes {
            @display("p=1371.6885,1776.1608");
        }
        _11_10: AgentNodes {

            @display("p=1602.8154,1791.2343");
        }
        _13_10: AgentNodes {
            @display("p=2125.3635,1806.3077");
        }
        _13_14: AgentNodes {


            @display("p=2286.1475,1776.1608");
        }

        _14_4: AgentNodes {
            @display("p=1771.1362,929.5325");
        }
        _14_13: AgentNodes {
            @display("p=2125.3635,849.1405");
        }
        _14_15: AgentNodes {


            @display("p=2163.047,1035.047");
        }
        _15_14: AgentNodes {
            @display("p=2318.8066,1472.1785");
        }
        _15_16: AgentNodes {


            @display("p=2607.7156,1472.1785");
        }
        _16_15: AgentNodes {
            @display("p=2607.7156,849.1405");
        }
        _16_17: AgentNodes {
            @display("p=2755.9382,811.4567");
        }
        _16_19: AgentNodes {
            @display("p=2657.9604,967.21625");
        }
        _16_21: AgentNodes {
            @display("p=2951.8938,1035.047");
        }
        _16_24: AgentNodes {


            @display("p=2881.5508,849.1405");
        }

        _17_16: AgentNodes {
            @display("p=1675.6708,515.0112");
        }
        _17_18: AgentNodes {
            @display("p=1524.9357,268.81076");
        }
        _17_27: AgentNodes {

            @display("p=1733.4525,316.5435");
        }
        _18_3: AgentNodes {
            @display("p=1090.3165,366.78848");
        }
        _18_17: AgentNodes {


            @display("p=1391.7865,414.52124");
        }
        _19_16: AgentNodes {

            @display("p=2951.8938,1904.2855");
        }
        _21_16: AgentNodes {
            @display("p=3366.415,1967.0917");
        }
        _21_22: AgentNodes {

            @display("p=3605.0786,1766.1117");
        }
        _22_21: AgentNodes {
            @display("p=3522.1746,1560.1072");
        }
        _22_23: AgentNodes {

            @display("p=3667.885,1263.6617");
        }


        _23_22: AgentNodes {
            @display("p=3572.4194,1143.0737");
        }
        _23_24: AgentNodes {

            @display("p=3642.7625,811.4567");
        }


        _24_16: AgentNodes {
            @display("p=2951.1616,629.73376");
        }
        _24_23: AgentNodes {


            @display("p=3220.7043,653.185");
        }
        _25_2: AgentNodes {
            @display("p=1489.7643,57.78175");
        }
        _25_26: AgentNodes {
            @display("p=1843.9915,80.392");
        }

        _26_25: AgentNodes {
            @display("p=2542.397,57.78175");
        }
        _26_27: AgentNodes {
            @display("p=2401.711,155.75949");
        }
        _26_28: AgentNodes {
            @display("p=2733.328,80.392");
        }
        _26_29: AgentNodes {
            @display("p=2806.183,206.0045");
        }
        _27_17: AgentNodes {
            @display("p=2065.0696,464.76624");
        }
        _27_26: AgentNodes {
            @display("p=2369.0518,401.96");
        }
        _28_26: AgentNodes {
            @display("p=3087.5552,80.392");
        }
        _28_29: AgentNodes {

            @display("p=3471.9294,183.39424");
        }


        _29_26: AgentNodes {
            @display("p=3507.1008,602.94");
        }
        _29_28: AgentNodes {

            @display("p=3666.768,183.19528");
        }
        _39_1: AgentNodes {
            @display("p=193.44325,761.21173");
        }
        _39_9: AgentNodes {

            @display("p=150.735,1170.7085");
        }
        fed: Federate {

            @display("p=1274.8806,79.26719");
        }
    connections allowunconnected:
        // ROUTER CONNECTIONS: 
        r1.pppg++ <--> C <--> r39.pppg++;
        r1.pppg++ <--> C <--> r2.pppg++;

        r2.pppg++ <--> C <--> r3.pppg++;
        r2.pppg++ <--> C <--> r25.pppg++;

        r3.pppg++ <--> C <--> r4.pppg++;
        r3.pppg++ <--> C <--> r18.pppg++;

        r4.pppg++ <--> C <--> r5.pppg++;
        r4.pppg++ <--> C <--> r14.pppg++;

        r5.pppg++ <--> C <--> r6.pppg++;
        r5.pppg++ <--> C <--> r8.pppg++;

        r6.pppg++ <--> C <--> r7.pppg++;
        r6.pppg++ <--> C <--> r11.pppg++;

        r7.pppg++ <--> C <--> r8.pppg++;

        r8.pppg++ <--> C <--> r9.pppg++;

        r9.pppg++ <--> C <--> r39.pppg++;

        r10.pppg++ <--> C <--> r11.pppg++;
        r10.pppg++ <--> C <--> r13.pppg++;

        r13.pppg++ <--> C <--> r14.pppg++;

        r14.pppg++ <--> C <--> r15.pppg++;

        r15.pppg++ <--> C <--> r16.pppg++;

        r16.pppg++ <--> C <--> r17.pppg++;
        r16.pppg++ <--> C <--> r19.pppg++;
        r16.pppg++ <--> C <--> r21.pppg++;
        r16.pppg++ <--> C <--> r24.pppg++;

        r17.pppg++ <--> C <--> r18.pppg++;
        r17.pppg++ <--> C <--> r27.pppg++;

        r21.pppg++ <--> C <--> r22.pppg++;

        r22.pppg++ <--> C <--> r23.pppg++;

        r23.pppg++ <--> C <--> r24.pppg++;

        r25.pppg++ <--> C <--> r26.pppg++;

        r26.pppg++ <--> C <--> r27.pppg++;
        r26.pppg++ <--> C <--> r28.pppg++;
        r26.pppg++ <--> C <--> r29.pppg++;

        r28.pppg++ <--> C <--> r29.pppg++;

        // LANHUB TO ROUTER CONNECTIONS: 
        r1.ethg++ <--> C <--> lan1.ethg++;
        r2.ethg++ <--> C <--> lan2.ethg++;
        r3.ethg++ <--> C <--> lan3.ethg++;
        r4.ethg++ <--> C <--> lan4.ethg++;
        r5.ethg++ <--> C <--> lan5.ethg++;
        r6.ethg++ <--> C <--> lan6.ethg++;
        r7.ethg++ <--> C <--> lan7.ethg++;
        r8.ethg++ <--> C <--> lan8.ethg++;
        r9.ethg++ <--> C <--> lan9.ethg++;
        r10.ethg++ <--> C <--> lan10.ethg++;
        r11.ethg++ <--> C <--> lan11.ethg++;
        r13.ethg++ <--> C <--> lan13.ethg++;
        r14.ethg++ <--> C <--> lan14.ethg++;
        r15.ethg++ <--> C <--> lan15.ethg++;
        r16.ethg++ <--> C <--> lan16.ethg++;
        r17.ethg++ <--> C <--> lan17.ethg++;
        r18.ethg++ <--> C <--> lan18.ethg++;
        r19.ethg++ <--> C <--> lan19.ethg++;
        r21.ethg++ <--> C <--> lan21.ethg++;
        r22.ethg++ <--> C <--> lan22.ethg++;
        r23.ethg++ <--> C <--> lan23.ethg++;
        r24.ethg++ <--> C <--> lan24.ethg++;
        r25.ethg++ <--> C <--> lan25.ethg++;
        r26.ethg++ <--> C <--> lan26.ethg++;
        r27.ethg++ <--> C <--> lan27.ethg++;
        r28.ethg++ <--> C <--> lan28.ethg++;
        r29.ethg++ <--> C <--> lan29.ethg++;
        r39.ethg++ <--> C <--> lan39.ethg++;

		// AGENT NODES

        lan1.ethg++ <--> C <--> _1_39.gate++;
        lan1.ethg++ <--> C <--> _1_2.gate++;

        lan2.ethg++ <--> C <--> _2_1.gate++;
        lan2.ethg++ <--> C <--> _2_3.gate++;
        lan2.ethg++ <--> C <--> _2_25.gate++;

        lan3.ethg++ <--> C <--> _3_2.gate++;
        lan3.ethg++ <--> C <--> _3_4.gate++;
        lan3.ethg++ <--> C <--> _3_18.gate++;

        lan4.ethg++ <--> C <--> _4_3.gate++;
        lan4.ethg++ <--> C <--> _4_5.gate++;
        lan4.ethg++ <--> C <--> _4_14.gate++;

        lan5.ethg++ <--> C <--> _5_4.gate++;
        lan5.ethg++ <--> C <--> _5_6.gate++;
        lan5.ethg++ <--> C <--> _5_8.gate++;

        lan6.ethg++ <--> C <--> _6_5.gate++;
        lan6.ethg++ <--> C <--> _6_7.gate++;
        lan6.ethg++ <--> C <--> _6_11.gate++;

        lan7.ethg++ <--> C <--> _7_6.gate++;
        lan7.ethg++ <--> C <--> _7_8.gate++;

        lan8.ethg++ <--> C <--> _8_7.gate++;
        lan8.ethg++ <--> C <--> _8_9.gate++;

        lan9.ethg++ <--> C <--> _9_8.gate++;
        lan9.ethg++ <--> C <--> _9_39.gate++;

        lan10.ethg++ <--> C <--> _10_11.gate++;
        lan10.ethg++ <--> C <--> _10_13.gate++;

        lan11.ethg++ <--> C <--> _11_10.gate++;
        lan11.ethg++ <--> C <--> _11_6.gate++;

        lan13.ethg++ <--> C <--> _13_10.gate++;
        lan13.ethg++ <--> C <--> _13_14.gate++;

        lan14.ethg++ <--> C <--> _14_13.gate++;
        lan14.ethg++ <--> C <--> _14_15.gate++;
        lan14.ethg++ <--> C <--> _14_4.gate++;

        lan15.ethg++ <--> C <--> _15_14.gate++;
        lan15.ethg++ <--> C <--> _15_16.gate++;

        lan16.ethg++ <--> C <--> _16_15.gate++;
        lan16.ethg++ <--> C <--> _16_17.gate++;
        lan16.ethg++ <--> C <--> _16_19.gate++;
        lan16.ethg++ <--> C <--> _16_21.gate++;
        lan16.ethg++ <--> C <--> _16_24.gate++;

        lan17.ethg++ <--> C <--> _17_16.gate++;
        lan17.ethg++ <--> C <--> _17_18.gate++;
        lan17.ethg++ <--> C <--> _17_27.gate++;

        lan18.ethg++ <--> C <--> _18_17.gate++;
        lan18.ethg++ <--> C <--> _18_3.gate++;

        lan19.ethg++ <--> C <--> _19_16.gate++;

        lan21.ethg++ <--> C <--> _21_16.gate++;
        lan21.ethg++ <--> C <--> _21_22.gate++;

        lan22.ethg++ <--> C <--> _22_21.gate++;
        lan22.ethg++ <--> C <--> _22_23.gate++;

        lan23.ethg++ <--> C <--> _23_22.gate++;
        lan23.ethg++ <--> C <--> _23_24.gate++;

        lan24.ethg++ <--> C <--> _24_23.gate++;
        lan24.ethg++ <--> C <--> _24_16.gate++;

        lan25.ethg++ <--> C <--> _25_2.gate++;
        lan25.ethg++ <--> C <--> _25_26.gate++;

        lan26.ethg++ <--> C <--> _26_25.gate++;
        lan26.ethg++ <--> C <--> _26_27.gate++;
        lan26.ethg++ <--> C <--> _26_28.gate++;
        lan26.ethg++ <--> C <--> _26_29.gate++;

        lan27.ethg++ <--> C <--> _27_17.gate++;
        lan27.ethg++ <--> C <--> _27_26.gate++;

        lan28.ethg++ <--> C <--> _28_26.gate++;
        lan28.ethg++ <--> C <--> _28_29.gate++;

        lan29.ethg++ <--> C <--> _29_26.gate++;
        lan29.ethg++ <--> C <--> _29_28.gate++;

        lan39.ethg++ <--> C <--> _39_1.gate++;
        lan39.ethg++ <--> C <--> _39_9.gate++;


}
