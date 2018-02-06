#include "EpEm.h"
#include "EpEp.h"
#include "EmEm.h"
#include "data.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iostream>
#include "HFilter.h"
#include <fstream>

using namespace std;
using namespace PATData;

int main()
{
//******************************************* B E A M   P A R A M E T E R S *****************************/
    /*
    //proj = new TLorentzVector(0,0,1700,1705.71972227); // PION BEAM 1.7 GeV/c momentum
   //targ = new TLorentzVector(0,0,0,938.27231); // PROTON
   beam = new TLorentzVector(0,0,0,0);
   proj = new TLorentzVector(0,0,700,713.7785); // PION BEAM 0.7 GeV/c momentum 
   targ = new TLorentzVector(0,0,0,938.27231); // PROTON
   *beam = *proj + *targ;
   */

   //PION BEAM SCANNER
//   double pion_momentum = 612.0;

//   double pion_momentum = 656.0;
   double pion_momentum = 690.0; 
//   double pion_momentum = 748.0;
//   double pion_momentum = 800.0;

   // ORIGIN: https://hades-wiki.gsi.de/foswiki/bin/view/PionBeam/WebHome

   double pion_energy = sqrt( pion_momentum*pion_momentum + 139.56995*139.56995 );

   proj = new TLorentzVector(0,0, pion_momentum, pion_energy); // PION BEAM momentum as above

   targ = new TLorentzVector(0,0,0,938.27231); // PROTON
/*******************************************************************************************************/
   beam = new TLorentzVector(0,0,0,0);
   *beam = *proj + *targ;



   //*******************************************************************************************************/


   //filter = new HFilter;

// *********************** FILES WITH CUTS ****************************
   insideEmS0 = -1;
   insideEmS1 = -1;
   insideEpS0 = -1;
   insideEpS1 = -1;

   insideEm1S0 = -1;
   insideEm1S1 = -1;
   insideEm2S0 = -1;
   insideEm2S1 = -1;

   insideEp1S0 = -1;
   insideEp1S1 = -1;
   insideEp2S0 = -1;
   insideEp2S1 = -1;

   e1 = new TLorentzVector(0,0,0,0);
   e2 = new TLorentzVector(0,0,0,0);
   gammae1e2 = new TLorentzVector(0,0,0,0);
   e1e2 = new TLorentzVector(0,0,0,0);
   e1_delta = new TLorentzVector(0,0,0,0);
   e2_delta = new TLorentzVector(0,0,0,0);
   e1e2_miss = new TLorentzVector(0,0,0,0);

/************************************** O U T P U T   F I L E ******************************************/
   outFileData = new TFile("pNb_epem_all.root","recreate");
   ofstream myfile;
   myfile.open ("raport.txt",ios::trunc);
   //outFileData = new TFile("ntuple_epem_656_C_gen1.root","recreate");
   //outFileData = new TFile("ntuple_epem_690_C_gen1.root","recreate");
   //outFileData = new TFile("ntuple_epem_690_PE_gen1_helicity.root","recreate");
   //outFileData = new TFile("ntuple_epem_690_C_gen1_helicity.root","recreate");
   //outFileData = new TFile("ntuple_epem_748_C_gen1.root","recreate");
   //outFileData = new TFile("ntuple_epem_800_C_gen1.root","recreate");
/*******************************************************************************************************/

/************************** control ntuple ***************************/
   tlo = new HNtuple("epem","epem");
   tlo->setFile( outFileData );
/*********************************************************************/

   sig_all = new TH1F("sig_all","sig_all",300,0,1);
   sig_all->Sumw2();
   sig_all_bt = new TH1F("sig_all_bt","sig_all_bt",300,0,1);
   sig_all_bt->Sumw2();
   sig_all_back1 = new TH1F("sig_all_back1","sig_all_back1",300,0,1);
   sig_all_back1->Sumw2();
   sig_all_back2 = new TH1F("sig_all_back2","sig_all_back2",300,0,1);
   sig_all_back2->Sumw2();
   sig_all_bt_back1 = new TH1F("sig_all_bt_back1","sig_all_bt_back1",300,0,1);
   sig_all_bt_back1->Sumw2();
   sig_all_bt_back2 = new TH1F("sig_all_bt_back2","sig_all_bt_back2",300,0,1);
   sig_all_bt_back2->Sumw2();
   sig_rf_and_bt=new TH1F("sig_rf_and_bt","sig_rf_and_bt",300,0,1);
   sig_rf_and_bt_OK=new TH1F("sig_rf_and_bt_OK","sig_rf_and_bt_OK",300,0,1);
   sig_rf_and_bt_OK->Sumw2();
   sig_rf_and_bt_back1=new TH1F("sig_rf_and_bt_back1","sig_rf_and_bt_back1",300,0,1);
   sig_rf_and_bt_back1->Sumw2();
   sig_rf_and_bt_back2=new TH1F("sig_rf_and_bt_back2","sig_rf_and_bt_back2",300,0,1);
   sig_rf_and_bt_back2->Sumw2();
   
   sig_OK = 0;
   sig_bt_OK = 0;
   
   miss_all = new TH1F("miss_all","miss_all",80,0.6,1.4);
   miss_all->Sumw2();
   miss_all_back1 = new TH1F("miss_all_back1","miss_all_back1",80,0.6,1.4);
   miss_all_back1->Sumw2();
   miss_all_back2 = new TH1F("miss_all_back2","miss_all_back2",80,0.6,1.4);
   miss_all_back2->Sumw2();
   miss_OK = 0;

   Float_t xbins[] = {0.000,0.005,0.010,0.015,0.020,0.025,0.030,0.035,0.040,0.045,0.050,0.055,0.070,0.085,0.100,0.120,0.140,0.180,0.230,0.280,0.330,0.400,0.500,0.600,0.800,1.000};
   Int_t nbins = sizeof(xbins)/sizeof(Float_t);

   sig_all_var = new TH1F("sig_all_var","sig_all_var",nbins-1,xbins);
   sig_all_var->Sumw2();
   sig_all_var_bt = new TH1F("sig_all_var_bt","sig_all_var_bt",nbins-1,xbins);
   sig_all_var_bt->Sumw2();
   sig_all_var_back1 = new TH1F("sig_all_var_back1","sig_all_var_back1",nbins-1,xbins);
   sig_all_var_back1->Sumw2();
   sig_all_var_back2 = new TH1F("sig_all_var_back2","sig_all_var_back2",nbins-1,xbins);
   sig_all_var_back2->Sumw2();
   sig_all_var_bt_back1 = new TH1F("sig_all_var_bt_back1","sig_all_var_bt_back1",nbins-1,xbins);
   sig_all_var_bt_back1->Sumw2();
   sig_all_var_bt_back2 = new TH1F("sig_all_var_bt_back2","sig_all_var_bt_back2",nbins-1,xbins);
   sig_all_var_bt_back2->Sumw2();
   sig_var_bt_OK = 0;
   sig_var_OK = 0;

   sig_all_var2 = new TH1F("sig_all_var_no","sig_all_var_no_norm",nbins-1,xbins);
   sig_all_var2->Sumw2();
   sig_all_var2_back1 = new TH1F("sig_all_var_back1_no","sig_all_var_back1_no_norm",nbins-1,xbins);
   sig_all_var2_back1->Sumw2();
   sig_all_var2_back2 = new TH1F("sig_all_var_back2_no","sig_all_var_back2_no_norm",nbins-1,xbins);
   sig_all_var2_back2->Sumw2();
   sig_var2_OK = 0;

   
   Float_t xbinsang[] =  {-1.0, -0.9, -0.8, -0.7, -0.6, -0.4, -0.2, 0, 0.2, 0.4, 0.6, 0.7, 0.8, 0.9, 1.0};
   Int_t nbinsang = sizeof(xbinsang)/sizeof(Float_t);

   cos_ep = new TH1F("cos_ep","cos_ep",10,-1,1); cos_ep->Sumw2();
   cos_em = new TH1F("cos_em","cos_em",10,-1,1); cos_em->Sumw2();
   cos_sum = new TH1F("cos_sum","cos_sum",10,-1,1); cos_sum->Sumw2();
   cos_ep_back1 = new TH1F("cos_ep_back1","cos_ep_back1",10,-1,1); cos_ep_back1->Sumw2();
   cos_em_back1 = new TH1F("cos_em_back1","cos_em_back1",10,-1,1); cos_em_back1->Sumw2();
   cos_sum_back1 = new TH1F("cos_sum_back1","cos_sum_back1",10,-1,1); cos_sum_back1->Sumw2();
   cos_ep_back2 = new TH1F("cos_ep_back2","cos_ep_back2",10,-1,1); cos_ep_back2->Sumw2();
   cos_em_back2 = new TH1F("cos_em_back2","cos_em_back2",10,-1,1); cos_em_back2->Sumw2();
   cos_sum_back2 = new TH1F("cos_sum_back2","cos_sum_back2",10,-1,1); cos_sum_back2->Sumw2();

   cos_ep_cm = new TH1F("cos_ep_cm","cos_ep_cm",10,-1,1); cos_ep_cm->Sumw2();
   cos_back1_cm = new TH1F("cos_back1_cm","cos_back1_cm",10,-1,1); cos_back1_cm->Sumw2();
   cos_back2_cm = new TH1F("cos_back2_cm","cos_back2_cm",10,-1,1); cos_back2_cm->Sumw2();
   cos_ep_cm_OK = new TH1F("cos_ep_cm_OK","cos_ep_cm_OK",10,-1,1); cos_ep_cm_OK->Sumw2();


   rapidity_all = new TH1F("rapidity_all","rapidity_all",50,0,2); rapidity_all->Sumw2();
   rapidity_back1 = new TH1F("rapidity_back1","rapidity_back1",50,0,2); rapidity_back1->Sumw2();
   rapidity_back2 = new TH1F("rapidity_back2","rapidity_back2",50,0,2); rapidity_back2->Sumw2();
   rapidity_OK = 0;

   rapidity_140_all = new TH1F("rapidity_140_all","rapidity_140_all",50,0,2); rapidity_140_all->Sumw2();
   rapidity_140_back1 = new TH1F("rapidity_140_back1","rapidity_140_back1",50,0,2); rapidity_140_back1->Sumw2();
   rapidity_140_back2 = new TH1F("rapidity_140_back2","rapidity_140_back2",50,0,2); rapidity_140_back2->Sumw2();
   rapidity_140_OK = 0;

   pt_all = new TH1F("pt_all","pt_all",50,0,1); pt_all->Sumw2();
   pt_back1 = new TH1F("pt_back1","pt_back1",50,0,1); pt_back1->Sumw2();
   pt_back2 = new TH1F("pt_back2","pt_back2",50,0,1); pt_back2->Sumw2();
   pt_OK = 0;

   pt_140_all = new TH1F("pt_140_all","pt_140_all",50,0,1); pt_140_all->Sumw2();
   pt_140_back1 = new TH1F("pt_140_back1","pt_140_back1",50,0,1); pt_140_back1->Sumw2();
   pt_140_back2 = new TH1F("pt_140_back2","pt_140_back2",50,0,1); pt_140_back2->Sumw2();
   pt_140_OK = 0;

   ep_beta_mom = new TH2F("ep_beta_mom","ep_beta_mom",50,0.6,1.3,100,0,1000); ep_beta_mom->Sumw2();
   em_beta_mom = new TH2F("em_beta_mom","em_beta_mom",50,0.6,1.3,100,0,1000); em_beta_mom->Sumw2();
   ep_beta_mom_bt = new TH2F("ep_beta_mom_bt","ep_beta_mom_bt",50,0.6,1.3,100,0,1000); ep_beta_mom_bt->Sumw2();
   em_beta_mom_bt = new TH2F("em_beta_mom_bt","em_beta_mom_bt",50,0.6,1.3,100,0,1000); em_beta_mom_bt->Sumw2();

   em_mom= new TH1F("em_mom","em_mom",250,0,1000);
   ep_mom= new TH1F("ep_mom","ep_mom",250,0,1000);
   em_mom_bt= new TH1F("em_mom_bt","em_mom_bt",250,0,1000);
   ep_mom_bt= new TH1F("ep_mom_bt","ep_mom_bt",250,0,1000);

   pureBT_signal=new TH1F("pureBT_signal","pureBT_signal",300,0,1);
   pureBT_signal_OK=new TH1F("pureBT_signal_OK","pureBT_signal_OK",300,0,1);
   pureBT_signal_back1=new TH1F("pureBT_signal_back1","pureBT_signal_back1",300,0,1);
   pureBT_signal_back2=new TH1F("pureBT_signal_back2","pureBT_signal_back2",300,0,1);

   pureBT_signal_var=new TH1F("pureBT_signal_var","pureBT_signal_var",nbins-1,xbins);
   pureBT_signal_OK_var=new TH1F("pureBT_signal_OK_var","pureBT_signal_OK_var",nbins-1,xbins);
   pureBT_signal_back1_var=new TH1F("pureBT_signal_back1_var","pureBT_signal_back1_var",nbins-1,xbins);
   pureBT_signal_back2_var=new TH1F("pureBT_signal_back2_var","pureBT_signal_back2_var",nbins-1,xbins);
   
   sig_sum=new TH1F("sig_sum","sig_sum",300,0,1);
   sig_sum_var=new TH1F("sig_sum_var","sig_sum_var",nbins-1,xbins);
   
   pureBT_beta_mom=new TH2F("pureBT_beta_mom","pureBT_beta_mom",50,0.7,1.3,100,0,1000);

   bt_rf_stat=new TH1I("bt_rf_stat","Statistic how many events heppend",14,-0.5,13.5);
   bt_rf_stat_pi=new TH1I("bt_rf_stat_pi","Statistic how many events heppend for mass>140MeV",14,-0.5,13.5);
   bt_rf_stat_back1=new TH1I("bt_rf_stat_back1","Statistic how many events heppend",14,-0.5,13.5);
   bt_rf_stat_pi_back1=new TH1I("bt_rf_stat_pi_back1","Statistic how many events heppend for mass>140MeV",14,-0.5,13.5);
   bt_rf_stat_back2=new TH1I("bt_rf_stat_back2","Statistic how many events heppend",14,-0.5,13.5);
   bt_rf_stat_pi_back2=new TH1I("bt_rf_stat_pi_back2","Statistic how many events heppend for mass>140MeV",14,-0.5,13.5);
   bt_rf_stat_OK=new TH1I("bt_rf_stat_OK","Statistic how many events heppend",14,-0.5,13.5);
   bt_rf_stat_pi_OK=new TH1I("bt_rf_stat_pi_OK","Statistic how many events heppend for mass>140MeV",14,-0.5,13.5);

   rf_freedom=new TH3F("rf_freedom","rf_freedom:d_theta:d_phi*sin(theta):mom",50,-2,2,50,-2,2,20,0,800);
   rf_f_dtheta=new TH2F("rf_f_dtheta","fr_f_dtheta",50,-4,4,20,0,800);
   rf_f_dphi=new TH2F("rf_f_dphi","fr_f_dphi",50,-4,4,20,0,800);
   /**************************** M A I N   P A R T ****************************************/

   EpEm t;
   t.Loop();
   EpEp t_back1;
   EmEm t_back2;
   cout << "START EPEM!" << endl;
   cout << "START EPEP!" << endl;
   t_back1.Loop();
   cout << "START EMEM!" << endl;
   t_back2.Loop();
   cout << "FINALIZING!" << endl;


/***************************** F I N A L     C A L C U L A T I O N S ********************/

   sig_OK = (TH1F*)signal("sig_OK", sig_all, sig_all_back1, sig_all_back2);
   sig_bt_OK = (TH1F*)signal("sig_bt_OK", sig_all_bt, sig_all_bt_back1, sig_all_bt_back2);
   pureBT_signal_OK=(TH1F*)signal("pureBT_signal_OK",pureBT_signal,pureBT_signal_back1,pureBT_signal_back2);
   sig_rf_and_bt_OK=(TH1F*)signal("sig_rf_and_bt_OK",sig_rf_and_bt,sig_rf_and_bt_back1,sig_rf_and_bt_back2);
   pureBT_signal_OK_var=(TH1F*)signal("pureBT_signal_OK_var",pureBT_signal_var,pureBT_signal_back1_var,pureBT_signal_back2_var);
   bt_rf_stat_OK=(TH1I*)signal("bt_rf_stat_OK",bt_rf_stat,bt_rf_stat_back1,bt_rf_stat_back2);
   bt_rf_stat_pi_OK=(TH1I*)signal("bt_rf_stat_pi_OK",bt_rf_stat_pi,bt_rf_stat_pi_back1,bt_rf_stat_pi_back2);
   //normalize( sig_all );
   //normalize( sig_all_back1 );
   //normalize( sig_all_back2 );
   //normalize( sig_OK );
   miss_OK = (TH1F*)signal("miss_OK", miss_all, miss_all_back1, miss_all_back2);
   //normalize( miss_all );
   //normalize( miss_all_back1 );
   //normalize( miss_all_back2 );
   //normalize( miss_OK );
         
   sig_var_OK = (TH1F*)signal("sig_var_OK", sig_all_var, sig_all_var_back1, sig_all_var_back2);
   sig_var_bt_OK = (TH1F*)signal("sig_var_bt_OK", sig_all_var_bt, sig_all_var_bt_back1, sig_all_var_bt_back2);
   sig_var2_OK = (TH1F*)signal("sig_var2_OK", sig_all_var2, sig_all_var2_back1, sig_all_var2_back2);
   normalize( sig_all_var );
   normalize( sig_all_var_bt );
   
   normalize( sig_all_var_back1 );
   normalize( sig_all_var_back2 );
   normalize( sig_var_OK );

   normalize( sig_all_var_bt_back1 );
   normalize( sig_all_var_bt_back2 );
   normalize( sig_var_bt_OK );

   normalize( pureBT_signal_var );
   normalize( pureBT_signal_back1_var );
   normalize( pureBT_signal_back2_var );
   normalize( pureBT_signal_OK_var );
   
   sig_sum->Add(sig_OK, pureBT_signal_OK,1,1);
   sig_sum_var->Add(sig_var_OK, pureBT_signal_OK_var,1,1);
   
   SIGNAL = (TH1F*)sig_var2_OK->Clone("SIGNAL");
   SIGNAL->SetNameTitle("SIGNAL","SIGNAL");
   CB = (TH1F*)sig_all_var2_back1->Clone("CB");
   CB->Add(sig_all_var2_back2);
   CB->SetNameTitle("CB","CB");

        SIGNIFICANCE = (TH1F*)CB->Clone("SIGNIFICANCE");
        SIGNIFICANCE->Divide( SIGNAL );
        SIGNIFICANCE->Scale(2.);
        for (Int_t j=1; j<SIGNIFICANCE->GetNbinsX()+1; ++j)
        {
           SIGNIFICANCE->SetBinContent( j, SIGNIFICANCE->GetBinContent(j) + 1. );
        }
        TH1F *temp = (TH1F*)SIGNAL->Clone("temp");
        temp->Divide( SIGNIFICANCE );
        SIGNIFICANCE = temp;
        SIGNIFICANCE->SetNameTitle("SIGNIFICANCE", "SIGNIFICANCE");

   normalize( SIGNIFICANCE );
   normalize( SIGNAL );
   normalize( CB );

   cos_ep_OK = (TH1F*)signal("cos_ep_OK", cos_ep, cos_ep_back1, cos_ep_back2);
//   normalize( cos_ep );
//   normalize( cos_ep_back1 );
//   normalize( cos_ep_back2 );
//   normalize( cos_ep_OK );

   cos_em_OK = (TH1F*)signal("cos_em_OK", cos_em, cos_em_back1, cos_em_back2);
//   normalize( cos_em );
//   normalize( cos_em_back1 );
//   normalize( cos_em_back2 );
//   normalize( cos_em_OK );

   cos_sum_OK = (TH1F*)signal("cos_sum_OK", cos_sum, cos_sum_back1, cos_sum_back2);
//   normalize( cos_sum );
//   normalize( cos_sum_back1 );
//   normalize( cos_sum_back2 );
//   normalize( cos_sum_OK );

   cos_ep_cm_OK = (TH1F*)signal("cos_ep_cm_OK", cos_ep_cm, cos_back1_cm, cos_back2_cm);
//   normalize( cos_ep_cm_OK );
//   normalize( cos_back1_cm );
//   normalize( cos_back2_cm );
//   normalize( cos_ep_cm );
   
   rapidity_OK = (TH1F*)signal("rapidity_OK", rapidity_all, rapidity_back1, rapidity_back2);
//   normalize( rapidity_all );
//   normalize( rapidity_back1 );
//   normalize( rapidity_back2 );
//   normalize( rapidity_OK );

   rapidity_140_OK = (TH1F*)signal("rapidity_140_OK", rapidity_140_all, rapidity_140_back1, rapidity_140_back2);
//   normalize( rapidity_140_all );
//  normalize( rapidity_140_back1 );
//   normalize( rapidity_140_back2 );
//   normalize( rapidity_140_OK );

   pt_OK = (TH1F*)signal("pt_OK", pt_all, pt_back1, pt_back2);
//   normalize( pt_all );
//   normalize( pt_back1 );
//   normalize( pt_back2 );
//   normalize( pt_OK );

   pt_140_OK = (TH1F*)signal("pt_140_OK", pt_140_all, pt_140_back1, pt_140_back2);
//   normalize( pt_140_all );
//   normalize( pt_140_back1 );
//   normalize( pt_140_back2 );
//   normalize( pt_140_OK );

/****************************************************************************************/

   outFileData->cd();

   // tlo->Write();


   ep_beta_mom->Write();
   em_beta_mom->Write();
   ep_beta_mom_bt->Write();
   em_beta_mom_bt->Write();

   sig_all->Write();
   sig_all_bt->Write();
   sig_all_back1->Write();
   sig_all_back2->Write();
   sig_OK->Write();
   sig_all_bt_back1->Write();
   sig_all_bt_back2->Write();
   sig_bt_OK->Write();
   sig_rf_and_bt->Write();
   sig_rf_and_bt_OK->Write();

   miss_all->Write();
   miss_all_back1->Write();
   miss_all_back2->Write();
   miss_OK->Write();

   sig_all_var->Write();
   sig_all_var_bt->Write();
   sig_all_var_back1->Write();
   sig_all_var_back2->Write();
   sig_var_OK->Write();
   sig_all_var_bt_back1->Write();
   sig_all_var_bt_back2->Write();
   sig_var_bt_OK->Write();
   
   SIGNAL->Write();
   CB->Write();
   SIGNIFICANCE->Write();

   sig_all_var2->Write();
   sig_all_var2_back1->Write();
   sig_all_var2_back2->Write();
   sig_var2_OK->Write();

   cos_ep->Write();
   cos_ep_back1->Write();
   cos_ep_back2->Write();
   cos_ep_OK->Write();
   cos_em->Write();
   cos_em_back1->Write();
   cos_em_back2->Write();
   cos_em_OK->Write();
   cos_sum->Write();
   cos_sum_back1->Write();
   cos_sum_back2->Write();
   cos_sum_OK->Write();
 
   cos_ep_cm_OK->Write();
   cos_ep_cm->Write();
   cos_back1_cm->Write();
   cos_back2_cm->Write();

   rapidity_all->Write();
   rapidity_back1->Write();
   rapidity_back2->Write();
   rapidity_OK->Write();
   
   rapidity_140_all->Write();
   rapidity_140_back1->Write();
   rapidity_140_back2->Write();
   rapidity_140_OK->Write();
   
   pt_all->Write();
   pt_back1->Write();
   pt_back2->Write();
   pt_OK->Write();
   
   pt_140_all->Write();
   pt_140_back1->Write();
   pt_140_back2->Write();
   pt_140_OK->Write();

   ep_mom->Write();
   em_mom->Write();
   ep_mom_bt->Write();
   em_mom_bt->Write();

   pureBT_beta_mom->Write();
   pureBT_signal->Write();
   pureBT_signal_OK->Write();
   pureBT_signal_back1->Write();
   pureBT_signal_back2->Write();

   //pureBT_beta_mom->Write();
   pureBT_signal_var->Write();
   pureBT_signal_OK_var->Write();
   pureBT_signal_back1_var->Write();
   pureBT_signal_back2_var->Write();

   sig_sum->Write();
   sig_sum_var->Write();

   bt_rf_stat->Write();
   bt_rf_stat_pi->Write();
   bt_rf_stat_back1->Write();
   bt_rf_stat_back2->Write();
   bt_rf_stat_pi_back2->Write();
   bt_rf_stat_pi_back1->Write();
   bt_rf_stat_pi_OK->Write();
   bt_rf_stat_OK->Write();

   rf_freedom->Write();
   rf_f_dphi->Write();
   rf_f_dtheta->Write();
   
   TCanvas* cSpectra=new TCanvas("cSpectra","cSpectra");
   cSpectra->Divide(2);
   cSpectra->cd(1);
   gPad->SetLogy();
   sig_all_var->Draw();
   sig_all_var_bt->SetLineColor(kRed);
   sig_all_var_bt->Draw("same");
   cSpectra->cd(2);
   gPad->SetLogy();
   sig_var_OK->SetLineColor(kBlue);
   sig_var_OK->Draw();
   sig_var_bt_OK->SetLineColor(kRed);
   sig_var_bt_OK->Draw("SAME");

   TCanvas* cMomenta=new TCanvas("cMomenta","cMomenta");
   cMomenta->Divide(2);
   cMomenta->cd(1);
   ep_mom_bt->SetLineColor(kRed);
   ep_mom_bt->Draw();
   ep_mom->Draw("same");
   cMomenta->cd(2);
   em_mom_bt->SetLineColor(kRed);
   em_mom_bt->Draw();
   em_mom->Draw("same");
   
   TCanvas* cBetaMom=new TCanvas("cBetaMom","cBetaMom");
   cBetaMom->Divide(2,2);
   cBetaMom->cd(1);
   ep_beta_mom->Draw("colz");
   cBetaMom->cd(2);
   em_beta_mom->Draw("colz");
   cBetaMom->cd(3);
   ep_beta_mom_bt->Draw("colz");
   cBetaMom->cd(4);
   em_beta_mom_bt->Draw("colz");

   TCanvas* cPureBT=new TCanvas("cPureBT","cPureBT");
   cPureBT->Divide(2);
   cPureBT->cd(1);
   gPad->SetLogy();
   sig_var_OK->Draw();
   pureBT_signal_OK_var->SetLineColor(kRed);
   pureBT_signal_OK_var->Draw("same");
   cPureBT->cd(2);
   pureBT_beta_mom->Draw("colz");

   TCanvas* cSiggAll=new TCanvas("cSiggAll","cSiggAll");
   cSiggAll->SetLogy();
   sig_var_OK->Draw();
   pureBT_signal_OK_var->Draw("same");
   sig_sum_var->SetLineColor(kGreen);
   sig_sum_var->Draw("same");

   TCanvas* cBackground=new TCanvas("cBackground","cBackground");
   cBackground->Divide(2);
   cBackground->cd(1);
   gPad->SetLogy();
   sig_all_var->Draw();
   sig_var_OK->SetLineColor(kBlue+1);
   sig_var_OK->Draw("same");
   cBackground->cd(2);
   sig_all_var_bt->Draw();
   sig_var_bt_OK->SetLineColor(kRed+1);
   sig_var_bt_OK->Draw("same");
   gPad->SetLogy();
 
   
   
   cBetaMom->Write();
   cSpectra->Write();
   cMomenta->Write();
   cPureBT->Write();
   cSiggAll->Write();
   cBackground->Write();
   
   //Save histopgrams parameters into text file
   
   myfile <<"Di-lepton parameters\n";
   myfile<< "Number of all di-leptons reconstructed in Pi0 mass region\n";
   myfile<<"  RF: "<<sig_OK->Integral(0,43)<<" BT: "<<sig_bt_OK->Integral(0,43)<<"\n";
   myfile<< "Number of di-leptons reconstructed E>mPi0\n";
   myfile<<"  RF: "<<sig_OK->Integral(44,300)<<" BT: "<<sig_bt_OK->Integral(44,300)<<"\n";
   myfile<<" Number of di-lepton recnstructed by BT and RF together in Pi0 mass region: \n";
   myfile<<"  = "<<sig_rf_and_bt_OK->Integral(0,43)<<endl;
   myfile<<" Number of di-lepton recnstructed by BT and RF together E>mPi0: \n";
   myfile<<"  = "<<sig_rf_and_bt_OK->Integral(44,300)<<endl;
   myfile<< "Number of di-leptons reconstructed by BT and missed by RF in Pi0 mass region:\n";
   myfile<<"  = "<<pureBT_signal_OK->Integral(0,43)<<"\n";
   myfile<< "Number of di-leptons reconstructed by BT and missed by RF E>mPi0:\n";
   myfile<<"  = "<<pureBT_signal_OK->Integral(44,300)<<"\n";
   myfile.close();

   outFileData->Close();
}

