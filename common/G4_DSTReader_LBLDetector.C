#ifndef MACRO_G4DSTREADERLBLDETECTOR_C
#define MACRO_G4DSTREADERLBLDETECTOR_C

#include <GlobalVariables.C>

#include <G4_AllSilicon.C>
#include <G4_CEmc_EIC.C>
#include <G4_EEMC.C>
#include <G4_FEMC_EIC.C>
#include <G4_FHCAL.C>
#include <G4_HcalIn_ref.C>
#include <G4_HcalOut_ref.C>
#include <G4_Magnet.C>

#include <g4eval/PHG4DSTReader.h>

#include <fun4all/Fun4AllServer.h>

R__LOAD_LIBRARY(libg4eval.so)

//////////////////////////////////////////////////////////////////
/*!
  \file G4_DSTReader.C
  \brief Convert DST to human command readable TTree for quick poke around the outputs
  \author  Jin Huang
  \version $Revision:  $
  \date    $Date: $
*/
//////////////////////////////////////////////////////////////////
namespace Enable
{
  bool DSTREADER = false;
  int DSTREADER_VERBOSITY = 0;
}  // namespace Enable

namespace G4DSTREADER
{
  bool save_g4_raw = true;
  double tower_zero_supp = 1.e-6;
}  // namespace G4DSTREADER

void G4DSTreader_LBLDetectorInit() {}
void G4DSTreader_LBLDetector(const string &outputFile = "G4sPHENIXCells.root")
{
  //! debug output on screen?
  int verbosity = max(Enable::VERBOSITY, Enable::DSTREADER_VERBOSITY);

  // save a comprehensive  evaluation file
  PHG4DSTReader *ana = new PHG4DSTReader(outputFile);
  ana->set_save_particle(true);
  ana->set_load_all_particle(false);
  ana->set_load_active_particle(true);
  ana->set_save_vertex(true);

  ana->Verbosity(verbosity);

  if (G4DSTREADER::save_g4_raw)
  {
    if (Enable::ALLSILICON)
    {
      char nodename[100];
      for (int i = 10; i < 16; i++)
      {
        sprintf(nodename, "LBLVTX_CENTRAL_%d", i);
        ana->AddNode(nodename);
      }
      for (int i = 20; i < 25; i++)
      {
        sprintf(nodename, "LBLVTX_FORWARD_%d", i);
        ana->AddNode(nodename);
      }
      for (int i = 30; i < 35; i++)
      {
        sprintf(nodename, "LBLVTX_BACKWARD_%d", i);
        ana->AddNode(nodename);
      }
      if (Enable::ABSORBER || Enable::ALLSILICON_ABSORBER)
      {
        ana->AddNode("ABSORBER_LBLVTX");
      }
    }

    if (Enable::CEMC)
    {
      ana->AddNode("CEMC");
      if (Enable::ABSORBER || Enable::CEMC_ABSORBER)
      {
        ana->AddNode("ABSORBER_CEMC");
        ana->AddNode("CEMC_ELECTRONICS");
        ana->AddNode("CEMC_SPT");
      }
    }

    if (Enable::HCALIN)
    {
      ana->AddNode("HCALIN");
      if (Enable::ABSORBER || Enable::HCALIN_ABSORBER)
        ana->AddNode("ABSORBER_HCALIN");
    }

    if (Enable::MAGNET)
    {
      if (Enable::ABSORBER || Enable::MAGNET_ABSORBER)
        ana->AddNode("MAGNET");
    }

    if (Enable::HCALOUT)
    {
      ana->AddNode("HCALOUT");
      if (Enable::ABSORBER || Enable::HCALOUT_ABSORBER)
        ana->AddNode("ABSORBER_HCALOUT");
    }

    if (Enable::FHCAL)
    {
      ana->AddNode("FHCAL");
      if (Enable::ABSORBER || Enable::FHCAL_ABSORBER)
        ana->AddNode("ABSORBER_FHCAL");
    }

    if (Enable::FEMC)
    {
      ana->AddNode("FEMC");
      if (Enable::ABSORBER || Enable::FEMC_ABSORBER)
        ana->AddNode("ABSORBER_FEMC");
    }

    if (Enable::EEMC)
    {
      ana->AddNode("EEMC");
    }

    if (Enable::BLACKHOLE)
    {
      ana->AddNode("BH_1");
      ana->AddNode("BH_FORWARD_PLUS");
      ana->AddNode("BH_FORWARD_NEG");
    }
  }
  ana->set_tower_zero_sup(G4DSTREADER::tower_zero_supp);
  if (Enable::CEMC_TOWER)
  {
    ana->AddTower("SIM_CEMC");
    ana->AddTower("RAW_CEMC");
    ana->AddTower("CALIB_CEMC");
  }
  if (Enable::HCALIN_TOWER)
  {
    ana->AddTower("SIM_HCALIN");
    ana->AddTower("RAW_HCALIN");
    ana->AddTower("CALIB_HCALIN");
  }
  if (Enable::HCALOUT_TOWER)
  {
    ana->AddTower("SIM_HCALOUT");
    ana->AddTower("RAW_HCALOUT");
    ana->AddTower("CALIB_HCALOUT");
  }
  if (Enable::FHCAL_TOWER)
  {
    ana->AddTower("SIM_FHCAL");
    ana->AddTower("RAW_FHCAL");
    ana->AddTower("CALIB_FHCAL");
  }
  if (Enable::FEMC_TOWER)
  {
    ana->AddTower("SIM_FEMC");
    ana->AddTower("RAW_FEMC");
    ana->AddTower("CALIB_FEMC");
  }
  if (Enable::FEMC_TOWER)
  {
    ana->AddTower("SIM_EEMC");
    ana->AddTower("RAW_EEMC");
    ana->AddTower("CALIB_EEMC");
  }

  // Jets disabled for now
  //  if (do_jet_reco)
  //    {
  //
  //      ana->AddJet("AntiKt06JetsInPerfect");
  //      ana->AddJet("G4TowerJets_6");
  //    }
  //  if (embed_input_file && do_jet_reco)
  //    {
  //      ana->AddJet("G4TowerJets_combined_6");
  //    }

  Fun4AllServer *se = Fun4AllServer::instance();
  se->registerSubsystem(ana);
}
#endif
