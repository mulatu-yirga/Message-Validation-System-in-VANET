#include "wave-setup.h"
#include "ns3/epc-enb-application.h"
#include "ns3/socket.h"
#include "ns3/virtual-net-device.h"
#include "ns3/object.h"
#include "ns3/log.h"
#include "ns3/mac48-address.h"
#include "ns3/uinteger.h"
#include "ns3/epc-gtpu-header.h"
#include "ns3/eps-bearer-tag.h"
#include "ns3/core-module.h"
#include "ns3/config-store-module.h"
#include "ns3/node.h"
#include "ns3/packet.h"
#include <sstream>
#include <cassert>
#include "ns3/log.h"
#include "ns3/stats-module.h"
#include "ns3/simulator.h"
#include "ns3/node-container.h"
#include "ns3/net-device-container.h"
#include "ns3/network-module.h"
#include "ns3/mobility-module.h"
#include "ns3/mobility-helper.h"
#include "ns3/config-store-module.h"
#include "ns3/lte-module.h"
#include "ns3/lte-helper.h"
#include "ns3/epc-helper.h"
#include <ns3/buildings-helper.h>
#include "ns3/config-store.h"
#include "ns3/wave-module.h"
#include "ns3/wifi-module.h"
#include "ns3/ns2-mobility-helper.h"
#include "ns3/applications-module.h"
#include "ns3/internet-module.h"
#include "ns3/ipv4-static-routing-helper.h"
#include "ns3/ipv4-list-routing-helper.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/olsr-helper.h"
#include "ns3/ocb-wifi-mac.h"
#include "ns3/wifi-80211p-helper.h"
#include "ns3/wave-mac-helper.h"
#include "ns3/aodv-module.h"
#include "ns3/point-to-point-helper.h"
#include "ns3/make-event.h"
//#include "ns3/netanim-module.h"
#include "ns3/flow-monitor-module.h"
#include "ns3/spectrum-module.h"
#include "ns3/internet-trace-helper.h"
#include "sys/timeb.h"


namespace ns3
{

WaveSetup::WaveSetup(){}
WaveSetup::~WaveSetup () {}

NetDeviceContainer WaveSetup::ConfigureDevices (NodeContainer& nodes)
{

  /*
    Setting up WAVE devices. With PHY & MAC using default settings. 
  */
  YansWifiChannelHelper waveChannel = YansWifiChannelHelper::Default ();
  YansWavePhyHelper wavePhy =  YansWavePhyHelper::Default ();
  wavePhy.SetChannel (waveChannel.Create ());
  wavePhy.SetPcapDataLinkType (WifiPhyHelper::DLT_IEEE802_11_RADIO);
  wavePhy.Set ("TxPowerStart", DoubleValue (5) );
  wavePhy.Set ("TxPowerEnd", DoubleValue (33) );
  wavePhy.Set ("TxPowerLevels", UintegerValue (8));
  //Setup up MAC
  QosWaveMacHelper waveMac = QosWaveMacHelper::Default ();
  WaveHelper waveHelper = WaveHelper::Default ();

  waveHelper.SetRemoteStationManager ("ns3::ConstantRateWifiManager",
  		"DataMode", StringValue ("OfdmRate6MbpsBW10MHz"	),
  		"ControlMode",StringValue ("OfdmRate6MbpsBW10MHz"),
  		"NonUnicastMode", StringValue ("OfdmRate6MbpsBW10MHz"));

  NetDeviceContainer devices = waveHelper.Install (wavePhy, waveMac, nodes);

//Ssid ssid = Ssid ("wifi-default");
     wavePhy.SetPcapDataLinkType (YansWifiPhyHelper::DLT_IEEE802_11);
     NqosWaveMacHelper wifi80211pMac = NqosWaveMacHelper::Default ();
     WifiMacQueue queue;


 ////////CTEATE DEVICES AND INSTALL THEM IN THE RSU ////////
            NodeContainer rsu;
            rsu.Create(1);
MobilityHelper mobility;
Ptr<ListPositionAllocator> positionAlloc2 =   CreateObject<ListPositionAllocator> ();
      positionAlloc2->Add (Vector (0, 150, 0));

 //mobility1.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
 mobility.SetPositionAllocator (positionAlloc2);
 mobility.Install (rsu);
          	   NetDeviceContainer rsu1Devs;
          	   Wifi80211pHelper wifi80211p1 = Wifi80211pHelper::Default ();
          	   wifi80211p1.SetStandard(WIFI_PHY_STANDARD_80211_10MHZ);
          	   wifi80211p1.SetRemoteStationManager("ns3::ConstantRateWifiManager", "DataMode",StringValue ("OfdmRate6MbpsBW10MHz"), "ControlMode", StringValue ("OfdmRate6MbpsBW10MHz"));

 rsu1Devs = wifi80211p1.Install (wavePhy, wifi80211pMac, rsu);
 wavePhy.EnablePcap ("the left RSU", rsu1Devs); // Tracing of the left RSU 1


          	   // Assign some attributes for vehicles on physical layer (wavePhy)
          	       //wavePhy.Set ("EnergyDetectionThreshold", DoubleValue (-96.0) );  // the PHY layer to detect the signal (the energy of a received signal should higher than this threshold)
          	      // wavePhy.Set ("CcaMode1Threshold", DoubleValue (-99.0) );        //  the PHY layer allow to declare CCA BUSY state (the energy of a received signal should higher than this threshold)
          	      // wavePhy.Set("TxGain", DoubleValue(0));
          	      // wavePhy.Set("RxGain", DoubleValue(0));
          	      // wavePhy.Set("TxPowerStart", DoubleValue(10.5));  		 //     minimum transmission range   {250-300 meter transmission range (value = 16)}
          	      // wavePhy.Set("TxPowerEnd", DoubleValue(25));     		    //      maximum transmission range   {250-300 meter transmission range (value = 16)}
          	      // wavePhy.Set("TxPowerLevels", UintegerValue(25));     	//      Number of transmission power levels available between TxPowerStart and TxPowerEnd included
          	      // wavePhy.Set ("RxNoiseFigure", DoubleValue (1) );          //     the difference noise (db) b/n actual and ideal receivers of nois output  (SNR)
          	       //wavePhy.Set("ChannelWidth", UintegerValue(10));
          	      // wavePhy.Set("Antennas", UintegerValue(1));             // the number of antennas on each smart vehicles
          	       //wavePhy.Set("TxAntennas", DoubleValue(1));             // the number of supported Tx antenna
          	       //wavePhy.Set("RxAntennas", DoubleValue(1));             // the number of supported Rx antenna

          	      


         // set olsr protocol on rsu 1
          	       /** OlsrHelper olsr_rsu1;
          	        Ipv4StaticRoutingHelper staticRouting_rsu1;
          	        Ipv4ListRoutingHelper list_rsu1;
          	        list_rsu1.Add (staticRouting_rsu1, 0);
          	        list_rsu1.Add (olsr_rsu1, 0);
          	        InternetStackHelper internet_olsr_rsu1;
          	        internet_olsr_rsu1.SetRoutingHelper (list_rsu1); 
                          
// has effect on the next Install ()
          	        internet_olsr_rsu1.Install (rsu);
                        */


        //  Create Internet and IP connections for rsu 1
                //InternetStackHelper rsustack;
                //rsustack.Install(rsu);
                // Ipv4AddressHelper address3;
                 //address3.SetBase ("10.1.3.0", "255.255.255.0");
                 //Ipv4InterfaceContainer Rsu1interface =
                // address3.Assign (rsu1Devs);


        // beacon broadcasting by rsu 1
                     /*TypeId tid_rsu1 = TypeId::LookupByName ("ns3::UdpSocketFactory");

                           // the rsu 1 become as a sink node
                             Ptr<Socket> beacon_Sink_rsu1 = Socket::CreateSocket (rsu1.Get (0), tid_rsu1);
                             InetSocketAddress beacon_local_rsu1 = InetSocketAddress (Ipv4Address::GetAny(),80);
                             beacon_Sink_rsu1->Bind (beacon_local_rsu1);
                             beacon_Sink_rsu1->SetRecvCallback (MakeCallback (&ReceiveBeacon));

                           // the rsu 1 become as a source node
                             Ptr<Socket> beacon_source_rsu1 = Socket::CreateSocket (rsu1.Get (0), tid_rsu1);
                             InetSocketAddress beaconBroadcast_rsu1 = InetSocketAddress (Ipv4Address ("255.255.255.255"), 80);
                             beacon_source_rsu1->SetAllowBroadcast (true);
                             beacon_source_rsu1->Connect (beaconBroadcast_rsu1);

                            Simulator::ScheduleWithContext (0, Seconds (60.0), &GenerateBeacon,beacon_source_rsu1, packetSize,numPackets, interPacketInterval_1);*/

                 
  //if you want PCAP trace, uncomment this!
  //wavePhy.EnablePcap ("custom-application", devices); //This generates *.pcap files

  return devices;
}

}
