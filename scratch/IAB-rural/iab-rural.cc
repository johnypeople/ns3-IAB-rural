 /* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
 /*
 *   Copyright (c) 2011 Centre Tecnologic de Telecomunicacions de Catalunya (CTTC)
 *   Copyright (c) 2015, NYU WIRELESS, Tandon School of Engineering, New York University
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License version 2 as
 *   published by the Free Software Foundation;
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *   Author: Marco Miozzo <marco.miozzo@cttc.es>
 *           Nicola Baldo  <nbaldo@cttc.es>
 *
 *   Modified by: Marco Mezzavilla < mezzavilla@nyu.edu>
 *        	 	  Sourjya Dutta <sdutta@nyu.edu>
 *        	 	  Russell Ford <russell.ford@nyu.edu>
 *        		  Menglei Zhang <menglei@nyu.edu>
 */

#include <ns3/buildings-module.h>
#include "ns3/mmwave-helper.h"
#include "ns3/lte-module.h"
#include "ns3/epc-helper.h"
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/internet-module.h"
#include "ns3/mobility-module.h"
#include "ns3/applications-module.h"
#include "ns3/point-to-point-helper.h"
#include "ns3/config-store.h"
#include "ns3/mmwave-point-to-point-epc-helper.h"
#include "ns3/flow-monitor-module.h"
//#include "ns3/gtk-config-store.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("MmWaveIabGrid");


void 
PrintGnuplottableBuildingListToFile (std::string filename)
{
  std::ofstream outFile;
  outFile.open (filename.c_str (), std::ios_base::out | std::ios_base::trunc);
  if (!outFile.is_open ())
    {
      NS_LOG_ERROR ("Can't open file " << filename);
      return;
    }
  uint32_t index = 0;
  for (BuildingList::Iterator it = BuildingList::Begin (); it != BuildingList::End (); ++it)
    {
      ++index;
      Box box = (*it)->GetBoundaries ();
      outFile << "set object " << index
              << " rect from " << box.xMin  << "," << box.yMin
              << " to "   << box.xMax  << "," << box.yMax
              //<< " height " << box.zMin << "," << box.zMax
              << " front fs empty "
              << std::endl;
    }
}

void 
PrintGnuplottableUeListToFile (std::string filename)
{
  std::ofstream outFile;
  outFile.open (filename.c_str (), std::ios_base::out | std::ios_base::trunc);
  if (!outFile.is_open ())
    {
      NS_LOG_ERROR ("Can't open file " << filename);
      return;
    }
  for (NodeList::Iterator it = NodeList::Begin (); it != NodeList::End (); ++it)
    {
      Ptr<Node> node = *it;
      int nDevs = node->GetNDevices ();
      for (int j = 0; j < nDevs; j++)
        {
          Ptr<LteUeNetDevice> uedev = node->GetDevice (j)->GetObject <LteUeNetDevice> ();
          Ptr<MmWaveUeNetDevice> mmuedev = node->GetDevice (j)->GetObject <MmWaveUeNetDevice> ();
          Ptr<McUeNetDevice> mcuedev = node->GetDevice (j)->GetObject <McUeNetDevice> ();
          if (uedev)
            {
              Vector pos = node->GetObject<MobilityModel> ()->GetPosition ();
              outFile << "set label \"" << uedev->GetImsi ()
                      << "\" at "<< pos.x << "," << pos.y << " left font \"Helvetica,8\" textcolor rgb \"black\" front point pt 1 ps 0.3 lc rgb \"black\" offset 0,0"
                      << std::endl;
            }
          else if (mmuedev)
           {
              Vector pos = node->GetObject<MobilityModel> ()->GetPosition ();
              outFile << "set label \"" << mmuedev->GetImsi ()
                      << "\" at "<< pos.x << "," << pos.y << " left font \"Helvetica,8\" textcolor rgb \"black\" front point pt 1 ps 0.3 lc rgb \"black\" offset 0,0"
                      << std::endl;
            }
          else if (mcuedev)
           {
              Vector pos = node->GetObject<MobilityModel> ()->GetPosition ();
              outFile << "set label \"" << mcuedev->GetImsi ()
                      << "\" at "<< pos.x << "," << pos.y << " left font \"Helvetica,8\" textcolor rgb \"black\" front point pt 1 ps 0.3 lc rgb \"black\" offset 0,0"
                      << std::endl;
            } 
        }
    }
}

void 
PrintGnuplottableEnbListToFile (std::string filename)
{
  std::ofstream outFile;
  outFile.open (filename.c_str (), std::ios_base::out | std::ios_base::trunc);
  if (!outFile.is_open ())
    {
      NS_LOG_ERROR ("Can't open file " << filename);
      return;
    }
  for (NodeList::Iterator it = NodeList::Begin (); it != NodeList::End (); ++it)
    {
      Ptr<Node> node = *it;
      int nDevs = node->GetNDevices ();
      for (int j = 0; j < nDevs; j++)
        {
          Ptr<LteEnbNetDevice> enbdev = node->GetDevice (j)->GetObject <LteEnbNetDevice> ();
          Ptr<MmWaveEnbNetDevice> mmdev = node->GetDevice (j)->GetObject <MmWaveEnbNetDevice> ();
          Ptr<MmWaveIabNetDevice> mmIabdev = node->GetDevice (j)->GetObject <MmWaveIabNetDevice> ();

          if (enbdev)
            {
              Vector pos = node->GetObject<MobilityModel> ()->GetPosition ();
              outFile << "set label \"" << enbdev->GetCellId ()
                      << "\" at "<< pos.x << "," << pos.y
                      << " left font \"Helvetica,8\" textcolor rgb \"blue\" front  point pt 4 ps 0.3 lc rgb \"blue\" offset 0,0"
                      << std::endl;
            }
          else if (mmdev)
            {
              Vector pos = node->GetObject<MobilityModel> ()->GetPosition ();
              outFile << "set label \"" << mmdev->GetCellId ()
                      << "\" at "<< pos.x << "," << pos.y
                      << " left font \"Helvetica,8\" textcolor rgb \"red\" front  point pt 4 ps 0.3 lc rgb \"red\" offset 0,0"
                      << std::endl;
            } 
         else if (mmIabdev)
            {
              Vector pos = node->GetObject<MobilityModel> ()->GetPosition ();
              outFile << "set label \"" << mmIabdev->GetCellId ()
                      << "\" at "<< pos.x << "," << pos.y
                      << " left font \"Helvetica,8\" textcolor rgb \"red\" front  point pt 4 ps 0.3 lc rgb \"red\" offset 0,0"
                      << std::endl;
            } 
        }
    }
}

int
main (int argc, char *argv[])
{
  // Logging minimo -- descomente conforme necessidade de debug
  // LogComponentEnableAll (LOG_PREFIX_TIME);
  // LogComponentEnableAll (LOG_PREFIX_FUNC);
  // LogComponentEnableAll (LOG_PREFIX_NODE);
  // LogComponentEnable("EpcIabApplication", LOG_LEVEL_LOGIC);
  // LogComponentEnable("LteEnbRrc", LOG_LEVEL_INFO);
  // LogComponentEnable("LteUeRrc", LOG_LEVEL_INFO);
  // LogComponentEnable("MmWaveHelper", LOG_LEVEL_LOGIC);
  // LogComponentEnable("MmWavePointToPointEpcHelper", LOG_LEVEL_LOGIC);
  // LogComponentEnable("UdpClient", LOG_LEVEL_INFO);
  // LogComponentEnable("UdpServer", LOG_LEVEL_INFO);
  // LogComponentEnable("MmWaveIabNetDevice", LOG_LEVEL_INFO);

  
  CommandLine cmd;
  unsigned run = 0;
  bool rlcAm = false;
  uint32_t numRelays = 1;
  uint32_t rlcBufSize = 10;
  uint32_t interPacketInterval = 200;
  uint32_t numUes = 20;
  cmd.AddValue("run", "run for RNG (for generating different deterministic sequences for different drops)", run);
  cmd.AddValue("am", "RLC AM if true", rlcAm);
  cmd.AddValue("numRelay", "Number of relays", numRelays);
  cmd.AddValue("numUes", "Number of UEs", numUes);
  cmd.AddValue("rlcBufSize", "RLC buffer size [MB]", rlcBufSize);
  cmd.AddValue("intPck", "interPacketInterval [us]", interPacketInterval);
  cmd.Parse(argc, argv);

  // LogComponentEnable("LteRlcAm", LOG_LEVEL_LOGIC);

  Config::SetDefault("ns3::MmWavePhyMacCommon::UlSchedDelay", UintegerValue(1));
  Config::SetDefault ("ns3::LteRlcAm::MaxTxBufferSize", UintegerValue (rlcBufSize * 1024 * 1024));
  Config::SetDefault ("ns3::LteRlcUm::MaxTxBufferSize", UintegerValue (rlcBufSize * 1024 * 1024));
  Config::SetDefault ("ns3::LteRlcAm::PollRetransmitTimer", TimeValue(MilliSeconds(1.0)));
  Config::SetDefault ("ns3::LteRlcAm::ReorderingTimer", TimeValue(MilliSeconds(2.0)));
  Config::SetDefault ("ns3::LteRlcAm::StatusProhibitTimer", TimeValue(MicroSeconds(500)));
  Config::SetDefault ("ns3::LteRlcAm::ReportBufferStatusTimer", TimeValue(MicroSeconds(500)));
  Config::SetDefault ("ns3::LteRlcUm::ReportBufferStatusTimer", TimeValue(MicroSeconds(500)));
  Config::SetDefault ("ns3::MmWaveHelper::RlcAmEnabled", BooleanValue(rlcAm));

  Config::SetDefault ("ns3::MmWaveFlexTtiMacScheduler::CqiTimerThreshold", UintegerValue(100));

  // ---- Cenario Rural (RMa, 3.5 GHz) ----
  Config::SetDefault ("ns3::MmWave3gppPropagationLossModel::Scenario", StringValue("RMa"));
  Config::SetDefault ("ns3::MmWavePhyMacCommon::CenterFreq", DoubleValue(3.5e9));
  // Forcar LOS para todos os links: justificado em cenario rural aberto onde
  // torres IAB sao posicionadas com visada direta. Evita NLoS com SINR~0
  // que causaria TxOpportunity=0 no backhaul encadeado.
  Config::SetDefault ("ns3::MmWave3gppPropagationLossModel::ChannelCondition", StringValue("l"));

	RngSeedManager::SetSeed (1);
	RngSeedManager::SetRun (run);

  Config::SetDefault ("ns3::MmWavePhyMacCommon::SymbolsPerSubframe", UintegerValue(240));
  Config::SetDefault ("ns3::MmWavePhyMacCommon::SubframePeriod", DoubleValue(1000));
  Config::SetDefault ("ns3::MmWavePhyMacCommon::SymbolPeriod", DoubleValue(1000/240));

  Ptr<MmWaveHelper> mmwaveHelper = CreateObject<MmWaveHelper> ();
  mmwaveHelper->SetAttribute ("PathlossModel", StringValue ("ns3::MmWave3gppPropagationLossModel"));
  Ptr<MmWavePointToPointEpcHelper>  epcHelper = CreateObject<MmWavePointToPointEpcHelper> ();
  mmwaveHelper->SetEpcHelper (epcHelper);
  mmwaveHelper->Initialize();

  ConfigStore inputConfig;
  inputConfig.ConfigureDefaults();

  // parse again so you can override default values from the command line
  cmd.Parse(argc, argv);

  Ptr<Node> pgw = epcHelper->GetPgwNode ();

   // Create a single RemoteHost
  NodeContainer remoteHostContainer;
  remoteHostContainer.Create (1);
  Ptr<Node> remoteHost = remoteHostContainer.Get (0);
  InternetStackHelper internet;
  internet.Install (remoteHostContainer);

  // Create the Internet
  PointToPointHelper p2ph;
  p2ph.SetDeviceAttribute ("DataRate", DataRateValue (DataRate ("100Gb/s")));
  p2ph.SetDeviceAttribute ("Mtu", UintegerValue (1500));
  p2ph.SetChannelAttribute ("Delay", TimeValue (Seconds (0.010)));
  NetDeviceContainer internetDevices = p2ph.Install (pgw, remoteHost);
  Ipv4AddressHelper ipv4h;
  ipv4h.SetBase ("1.0.0.0", "255.0.0.0");
  Ipv4InterfaceContainer internetIpIfaces = ipv4h.Assign (internetDevices);
  // interface 0 is localhost, 1 is the p2p device
  // Ipv4Address remoteHostAddr = internetIpIfaces.GetAddress (1);

  Ipv4StaticRoutingHelper ipv4RoutingHelper;
  Ptr<Ipv4StaticRouting> remoteHostStaticRouting = ipv4RoutingHelper.GetStaticRouting (remoteHost->GetObject<Ipv4> ());
  remoteHostStaticRouting->AddNetworkRouteTo (Ipv4Address ("7.0.0.0"), Ipv4Mask ("255.0.0.0"), 1);

  // ---- Topologia Rural ----
  // Area: 5 km x 5 km, sem edificios
  // Donor gNB: origem (0, 2500, 35 m)
  // IABs: encadeados linearmente ao longo do eixo X, separados por 1 km
  // UEs: distribuidos aleatoriamente em toda a area

  double areaX = 5000.0;  // m
  double areaY = 5000.0;  // m
  double gnbHeight = 35.0;  // m (hBS: 10-150 m para RMa)
  double iabHeight = 10.0;  // m — limite exato: hUT<=10 (backhaul) e hBS>=10 (acesso) em RMa
  double ueHeightMin = 1.5; // m (hUT: 1-10 m para RMa)
  double ueHeightMax = 2.0; // m

  // Donor gNB no canto esquerdo, IABs ao longo do corredor central
  double yCenter = areaY / 2.0;
  double iabSpacing = areaX / (numRelays + 1); // distancia uniforme entre nos

  Vector posWired = Vector(0.0, yCenter, gnbHeight);

  // Posicoes dos IABs: cadeia linear a partir do donor
  std::vector<Vector> iabPositions;
  for (uint32_t i = 0; i < numRelays; ++i)
  {
    double xIab = (i + 1) * iabSpacing;
    iabPositions.push_back(Vector(xIab, yCenter, iabHeight));
  }

  NS_LOG_UNCOND("Donor gNB: " << posWired);
  for (uint32_t i = 0; i < iabPositions.size(); ++i)
    NS_LOG_UNCOND("IAB[" << i << "]: " << iabPositions[i]);
  NS_LOG_UNCOND("Area: " << areaX << " x " << areaY << " m  ("
                << areaX/1000 << " x " << areaY/1000 << " km)");

  NodeContainer ueNodes;
  NodeContainer enbNodes;
  NodeContainer iabNodes;
 
  enbNodes.Create(1);
  iabNodes.Create(numRelays);
  ueNodes.Create(numUes);

  // Install Mobility Model
  Ptr<ListPositionAllocator> enbPositionAlloc = CreateObject<ListPositionAllocator> ();
  enbPositionAlloc->Add (posWired);
  MobilityHelper enbmobility;
  enbmobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  enbmobility.SetPositionAllocator(enbPositionAlloc);
  enbmobility.Install (enbNodes);

  if(numRelays > 0)
  {
    Ptr<ListPositionAllocator> iabPositionAlloc = CreateObject<ListPositionAllocator> ();
    for (uint32_t i = 0; i < numRelays; ++i)
      iabPositionAlloc->Add (iabPositions[i]);
    MobilityHelper iabmobility;
    iabmobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
    iabmobility.SetPositionAllocator (iabPositionAlloc);
    iabmobility.Install (iabNodes);
  }

  // UEs distribuidos aleatoriamente em toda a area rural
  MobilityHelper uemobility;
  Ptr<RandomRectanglePositionAllocator> uePosAlloc = CreateObject<RandomRectanglePositionAllocator>();
  uePosAlloc->SetAttribute("X", StringValue("ns3::UniformRandomVariable[Min=0|Max=" + std::to_string(areaX) + "]"));
  uePosAlloc->SetAttribute("Y", StringValue("ns3::UniformRandomVariable[Min=0|Max=" + std::to_string(areaY) + "]"));
  uemobility.SetPositionAllocator (uePosAlloc);
  uemobility.SetMobilityModel ("ns3::ConstantPositionMobilityModel");
  uemobility.Install (ueNodes);

  // Ajustar altura dos UEs (RandomRectanglePositionAllocator nao define Z)
  for (uint32_t u = 0; u < ueNodes.GetN (); ++u)
  {
    Ptr<MobilityModel> mob = ueNodes.Get(u)->GetObject<MobilityModel>();
    Vector pos = mob->GetPosition();
    pos.z = ueHeightMin + (ueHeightMax - ueHeightMin) * u / std::max(1u, ueNodes.GetN() - 1);
    mob->SetPosition(pos);
  }

  // Install mmWave Devices to the nodes
  NetDeviceContainer enbmmWaveDevs = mmwaveHelper->InstallEnbDevice (enbNodes);
  NetDeviceContainer iabmmWaveDevs;
  if(numRelays > 0)
  {
    iabmmWaveDevs = mmwaveHelper->InstallIabDevice (iabNodes);
  }
  NetDeviceContainer uemmWaveDevs = mmwaveHelper->InstallUeDevice (ueNodes);

  PrintGnuplottableBuildingListToFile("buildings.txt");// fileName.str ());
  PrintGnuplottableEnbListToFile("enbs.txt");
  PrintGnuplottableUeListToFile("ues.txt");

  // Install the IP stack on the UEs
  internet.Install (ueNodes);
  Ipv4InterfaceContainer ueIpIface;
  ueIpIface = epcHelper->AssignUeIpv4Address (NetDeviceContainer (uemmWaveDevs));
  // Assign IP address to UEs, and install applications
  for (uint32_t u = 0; u < ueNodes.GetN (); ++u)
    {
      Ptr<Node> ueNode = ueNodes.Get (u);
      // Set the default gateway for the UE
      Ptr<Ipv4StaticRouting> ueStaticRouting = ipv4RoutingHelper.GetStaticRouting (ueNode->GetObject<Ipv4> ());
      ueStaticRouting->SetDefaultRoute (epcHelper->GetUeDefaultGatewayAddress (), 1);
    }

  NetDeviceContainer possibleBaseStations(enbmmWaveDevs, iabmmWaveDevs);
  NS_LOG_INFO("number of IAB devs " << iabmmWaveDevs.GetN() << " num of possibleBaseStations "
    << possibleBaseStations.GetN());

  if(numRelays > 0)
  {
    mmwaveHelper->AttachIabToClosestWiredEnb (iabmmWaveDevs, enbmmWaveDevs);
  }
  mmwaveHelper->AttachToClosestEnbWithDelay (uemmWaveDevs, possibleBaseStations, Seconds(0.3));

  // Install and start applications on UEs and remote host
  uint16_t dlPort = 1234;
  // uint16_t ulPort = 2000;
  // uint16_t otherPort = 3000;
  ApplicationContainer clientApps;
  ApplicationContainer serverApps;

  for (uint32_t u = 0; u < ueNodes.GetN (); ++u)
  {
    // DL UDP
    UdpServerHelper dlPacketSinkHelper (dlPort);
    serverApps.Add (dlPacketSinkHelper.Install (ueNodes.Get(u)));

    UdpClientHelper dlClient (ueIpIface.GetAddress (u), dlPort);
    dlClient.SetAttribute ("Interval", TimeValue (MicroSeconds(interPacketInterval)));
    dlClient.SetAttribute ("PacketSize", UintegerValue(1400));
    dlClient.SetAttribute ("MaxPackets", UintegerValue(0xFFFFFFFF));
    clientApps.Add (dlClient.Install (remoteHost));

    dlPort++;
  }
  serverApps.Start (Seconds (0.49));
  clientApps.Stop (Seconds (1.2));
  clientApps.Start (Seconds (0.5));

  NS_LOG_UNCOND ("[1/4] Aplicacoes configuradas. Habilitando traces...");
  mmwaveHelper->EnableTraces ();

  NS_LOG_UNCOND ("[2/4] Traces habilitados. Escrevendo mapa de celulas...");
  // --- Mapeamento Cell ID -> Hop (para pos-processamento) ---
  {
    std::ofstream cellMap ("cell-hop-map.txt");
    cellMap << "NodeType\tNodeId\tCellId\tHop\tX\tY\tZ\n";
    for (uint32_t i = 0; i < enbmmWaveDevs.GetN (); i++)
      {
        Ptr<MmWaveEnbNetDevice> dev = DynamicCast<MmWaveEnbNetDevice> (enbmmWaveDevs.Get (i));
        if (dev)
          {
            Vector pos = enbNodes.Get (i)->GetObject<MobilityModel> ()->GetPosition ();
            cellMap << "gNB\t" << enbNodes.Get (i)->GetId () << "\t"
                    << dev->GetCellId () << "\t0\t"
                    << pos.x << "\t" << pos.y << "\t" << pos.z << "\n";
          }
      }
    for (uint32_t i = 0; i < iabmmWaveDevs.GetN (); i++)
      {
        Ptr<MmWaveIabNetDevice> dev = DynamicCast<MmWaveIabNetDevice> (iabmmWaveDevs.Get (i));
        if (dev)
          {
            Vector pos = iabNodes.Get (i)->GetObject<MobilityModel> ()->GetPosition ();
            cellMap << "IAB\t" << iabNodes.Get (i)->GetId () << "\t"
                    << dev->GetCellId () << "\t1\t"
                    << pos.x << "\t" << pos.y << "\t" << pos.z << "\n";
          }
      }
    cellMap.close ();
    NS_LOG_UNCOND ("Cell-hop map written to cell-hop-map.txt");
  }

  NS_LOG_UNCOND ("[3/4] Iniciando simulacao...");
  Simulator::Stop (Seconds (1.2));
  Simulator::Run ();

  NS_LOG_UNCOND ("[4/4] Simulacao concluida. Calculando metricas...");

  // --- Metricas de throughput e perda via UdpServer ---
  double simDuration  = 1.2 - 0.5; // janela util (s)
  double expectedPkts = simDuration / (interPacketInterval * 1e-6);
  double totalTput    = 0.0;

  std::ofstream flowFile ("flow-metrics.txt");
  if (!flowFile.is_open ())
    {
      NS_LOG_UNCOND ("[ERRO] Nao foi possivel criar flow-metrics.txt");
    }
  else
    {
      flowFile << "UeIndex\tUeIP\tTxPkts\tRxPkts\tThroughput_Mbps\tLoss_pct\n";

      for (uint32_t u = 0; u < ueNodes.GetN (); ++u)
        {
          Ptr<UdpServer> srv = serverApps.Get (u)->GetObject<UdpServer> ();
          if (!srv)
            {
              NS_LOG_UNCOND ("[WARN] UdpServer nao encontrado para UE " << u);
              continue;
            }
          uint32_t rxPkts = srv->GetReceived ();
          double tput     = rxPkts * 1400.0 * 8.0 / simDuration / 1e6;
          double loss     = (expectedPkts > rxPkts) ? (expectedPkts - rxPkts) * 100.0 / expectedPkts : 0.0;

          flowFile << u                        << "\t"
                   << ueIpIface.GetAddress (u) << "\t"
                   << (uint32_t) expectedPkts  << "\t"
                   << rxPkts                   << "\t"
                   << tput                     << "\t"
                   << loss                     << "\n";
          totalTput += tput;
        }

      flowFile << "\n# --- Resumo ---\n";
      flowFile << "# Total UEs:           " << ueNodes.GetN ()             << "\n";
      flowFile << "# Throughput total DL: " << totalTput                   << " Mbps\n";
      flowFile << "# Throughput medio/UE: " << totalTput / ueNodes.GetN () << " Mbps\n";
      flowFile.close ();

      NS_LOG_UNCOND ("=== Resumo da Simulacao ===");
      NS_LOG_UNCOND ("UEs                  : " << ueNodes.GetN ());
      NS_LOG_UNCOND ("Throughput total DL  : " << totalTput                   << " Mbps");
      NS_LOG_UNCOND ("Throughput medio/UE  : " << totalTput / ueNodes.GetN () << " Mbps");
      NS_LOG_UNCOND ("--- Arquivos gerados ---");
      NS_LOG_UNCOND ("flow-metrics.txt     : throughput e perda por UE");
      NS_LOG_UNCOND ("RxPacketTrace.txt    : SINR e TBLER por celula (PHY)");
      NS_LOG_UNCOND ("DlRlcStats.txt       : delay e bytes na RLC");
      NS_LOG_UNCOND ("DlPdcpStats.txt      : delay e bytes na PDCP");
      NS_LOG_UNCOND ("cell-hop-map.txt     : mapeamento CellId -> Hop");
    }

  /*GtkConfigStore config;
  config.ConfigureAttributes();*/

  Simulator::Destroy();
  return 0;
}

