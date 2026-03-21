#include "ns3/wave-module.h"
#include "ns3/wifi-module.h"
#include "ns3/mobility-module.h"
#include "ns3/core-module.h"
#include "ns3/netanim-module.h"
#include "cust-app.h"
#include "wave-setup.h"
#include "ns2-node-utility.h"
#include "ns3/flow-monitor-module.h"

using namespace ns3;

int main (int argc, char *argv[]) //int argc, char *argv[] kun isaa duratti
{
  CommandLine cmd;
  cmd.Parse (argc, argv);

   
  // uint32_t SenderPackets=0;
   //uint32_t SenderPackets=0;
   //uint32_t SenderPackets=0;

  //A tool I created so that we only start the applications within nodes when they actually enter the simulation.
  Ns2NodeUtility ns2_utility ("scratch/MyThesis/HighwayMob.tcl");
  uint32_t nnodes = ns2_utility.GetNNodes();
  double sim_time = ns2_utility.GetSimulationTime();

//Create a node container for vehicles
  NodeContainer nodes;
//create a node coantainer for RSUs
  NodeContainer rsu_container;
  nodes.Create (nnodes);
  rsu_container.Create(1);
   
 // FlowMonitorHelper flowmon;
  //flowmon = flowmon.InstallAll ();

  //For vehicles,you can use SUMO-generated trace.Using the bulit-in ns-2 mobility helper
 Ns2MobilityHelper sumo_trace ("scratch/MyThesis/HighwayMob.tcl");
sumo_trace.Install(nodes.Begin(),nodes.End()); //install ns-2 mobility in all nodes
//For RSU, use contantPositionMobiltyModel
MobilityHelper mob;
mob.SetMobilityModel("ns3::ConstantPositionMobilityModel");
mob.Install(rsu_container);

//Now that you installed contantPositionMobiltyModel,we can set RSU node positions as you please
//For node RSU 0, We can set the position to 100,200,3

rsu_container.Get(0)->GetObject<MobilityModel>()->SetPosition(Vector(100,200,3)); 

//we can also using the loop For example if the RSU are in straight Highway and spaced by 300 meters
//WaveSetup wave;
//wave.ConfigureDevices(rsu_container);
double distance=300.0;
for (uint32_t i=0;i<rsu_container.GetN();i++){

rsu_container.Get(0)->GetObject <MobilityModel>()->SetPosition( Vector(100 + distance,200,3));


}

  //To write shorter code, I put the code to setup WaveNetDevice in a separate file.
  WaveSetup wave;
  wave.ConfigureDevices(nodes);

  //Let's install my CustomApplication to all nodes and start them at the appropriate time using my utilitiy.
  for (uint32_t i=0 ; i<nnodes; i++)
    {
      Ptr<Node> n = nodes.Get(i);
      Ptr<CustomApplication> app = CreateObject <CustomApplication>();

      app->SetStartTime(Seconds (ns2_utility.GetEntryTimeForNode(i))); //this is the first time the node appears in the ns-2 trace
      app->SetStopTime (Seconds (ns2_utility.GetExitTimeForNode(i)));
      n->AddApplication(app);
    }


  Simulator::Stop(Seconds (sim_time)); //because this is the last timestamp in your ns-2 trace
 
//AnimationInterface anim("/home/dagy/ns-allinone-3.29/netanim-3.107/vehiclesmotion.xml");
          //EPC server


/**AnimationInterface anim("animation.xml");

       anim.SetMobilityPollInterval (Seconds (1));
       anim.setContantPosition(ptr<Node> n, double x,double y);
       anim.EnablePacketMetadata (true);
       ptr<Node> n=nodecontainer.get(1);
       AnimationInterface anim("anim.xml");
       anim.setConstantPosition(n,100,200);*/
Simulator::Run ();
std::cout << "End of Program" << std::endl;
/**int j=0;
float AvgThroughput=0;
Time Delay;

ptr<Ipv4FlowClassifier> classifier=DynamicCast<Ipv4FlowClassifier> (flowmon.GetClassifier());
  std::map<FlowId,FlowMonitor::FlowStats> stats=monitor->GetFlowStats();

for(std::map<FlowId,FlowMonitor::FlowStats>::const_iterator iter=stats.begin(); iter !=stats.end(); ++iter){

  Ipv4FlowClassifier::FiveTuple t= classifier->FindFlow(iter->first);
NS_LOG_UNCOND("---Flow ID" <<iter->first);
NS_LOG_UNCOND("scr addr="<<t.sourceAddress<<"dst addr"<<t.destinationAddress);
NS_LOG_UNCOND("sender packets="<<iter->second.txpacket);
NS_LOG_UNCOND("receiver packets="<<iter->second.rxpacket);
NS_LOG_UNCOND("lost packets="<<iter->second.txpacket-iter->second.rxpacket<<"%");
NS_LOG_UNCOND("packets delivery ratio="<<iter->second.rxpacket*100/iter->second.rxpacket<<"%");
NS_LOG_UNCOND("Delay="<<iter->second.delaySum);
NS_LOG_UNCOND("Troughput="<<iter->second.rxBytes*8.0/(iter->second.timeLostRxPacket.GetSeconds()-iter->second.timeFirstTxPacket.GetSecond())/1024<<"Kbps");
Sentpackets=SentPackets + (iter->second.txPackets);
ReceiverPackets=ReceiverPackets + (iter->second.rxPackets);
LostPackets=LostPackets + (iter->second.txPackets-iter->second.rxPackets);
AvgThroughput = AvgThroughput + (iter->second.rxBytes*8.0/(iter->second.timeLostRxPacket.GetSeconds()-iter->second.timeFirstTxPacket.GetSecond())/1024<<"Kbps");
Delay=Delay +(iter->second.delaySum);
J=j+1;
}
AvgThroughput = AvgThroughput/j;
NS_LOG_UNCOND("***********TOTAL RESULT OF THE SIMULATION******"<<std::endl;
NS_LOG_UNCOND("Total Sent Packets="<<SentPackets);
NS_LOG_UNCOND("Total Receiver Packets="<<ReceiverPackets);
NS_LOG_UNCOND("Total Lost Packets="<<LostPackets);
NS_LOG_UNCOND("Packets loss ratio="<<((LostPackets*100)/SentPackets)<<"%");
NS_LOG_UNCOND("Packets  delivery ratio="<<((ReceivedPackets*100)/SentPackets)<<"%");
NS_LOG_UNCOND("Average Throughput="<<AvgThroughput<<"Kbps");
NS_LOG_UNCOND("End to End Delay="<<Delay;
Monitor->serializeToXmlFile("Manet-routing.xml",true.true);

*/
  std::cout << "End of Program" << std::endl;

}
