#include <TFile.h>
#include <cstdlib>
#include <TH1F.h>

void ROCcomp(){

  gROOT->ProcessLine(".L tdrstyle.C");
  setTDRStyle();
  gStyle->SetOptStat(0);


  TFile *fLoose = new TFile("Loose.root");
  TFile *fTight  = new TFile("Tight.root");
  TFile *fMedium  = new TFile("Medium.root");

  TCanvas *c1 = new TCanvas("c1","ROC Curves Comparison",600,600);
  c1->cd()->SetGrid();

  fTight->cd("Method_Cuts/Cut_Tight_r");
  MVA_Cut_Tight_r_trainingRejBvsS->Draw();
  MVA_Cut_Tight_r_trainingRejBvsS->SetLineColor(kMagenta);
  MVA_Cut_Tight_r_trainingRejBvsS->GetXaxis()->SetTitle("Signal Efficiency"); 
  MVA_Cut_Tight_r_trainingRejBvsS->GetYaxis()->SetTitle("Background Rejection");
  
  fMedium->cd("Method_Cuts/Cut_Medium_r");
  MVA_Cut_Medium_r_trainingRejBvsS->Draw("same");
  MVA_Cut_Medium_r_trainingRejBvsS->SetLineColor(kBlue);


  
  fLoose->cd("Method_Cuts/Cut_Loose_r");
  MVA_Cut_Loose_r_trainingRejBvsS->Draw("same");
  MVA_Cut_Loose_r_trainingRejBvsS->SetLineColor(kBlack);
  
  
  c1->SaveAs("ROCs_train.png");



}
