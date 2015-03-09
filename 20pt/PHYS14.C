#define PHYS14_cxx
#include "PHYS14.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <iomanip>
#include <cstdlib>
#include <iostream>
#include <TMath.h>
#include <vector>
#include <TVector3.h>

void PHYS14::Loop()
{
  TFile *f1 = new TFile("T.root","recreate");
  TTree *t1 = new TTree("t1","EventsTree");
  float gedPhEta,gedPhPt,gedPhPhi,gedPhoIso,gedChgIso,gedNeuIso,gedPhTower,gedPhSieie,gedPhisPrompt,Rho;
  float gedGenPt,gedPhweightXS; 
  int gedPhPixSeed,NVtx; 

  TH1D *MatchPhos = new TH1D("MatchPhos","# of matched photons in event",5,0,5);
 
  TH2D *RvsPV = new TH2D("RvsPV","Rho versus primary vertices",70,0,70,700,0,70);
  TH2D *PIallevs = new TH2D("PIallevs","Iso vs Pt for true photons",100,0,100,1000,0,100);
  TH2D *PIevs1pho = new TH2D("PIevs1pho","Iso vs Pt for true photons evs 1 photon",100,0,100,1000,0,100);
  TH2D *PIevs1st = new TH2D("PIevs1st","Iso vs Pt for true photons 1st photon matched",100,0,100,1000,0,100);
  TH2D *PIevsMax = new TH2D("PIevsMAX","Iso vs Pt for true photons Max pt photon matched",100,0,100,1000,0,100);

  t1->Branch("Rho",&Rho,"Rho/F");
  t1->Branch("NVtx",&NVtx,"NVtx/I");
  t1->Branch("gedPhEta",&gedPhEta,"gedPhEta/F");
  t1->Branch("gedPhPhi",&gedPhPhi,"gedPhPhi/F");
  t1->Branch("gedPhPt",&gedPhPt,"gedPhPt/F");
  t1->Branch("gedPhSieie",&gedPhSieie,"gedPhSieie/F");
  t1->Branch("gedPhTower",&gedPhTower,"gedPhTower/F");
  t1->Branch("gedPhisPrompt",&gedPhisPrompt,"gedPhisPrompt/F");
  t1->Branch("gedPhoIso",&gedPhoIso,"gedPhoIso/F");
  t1->Branch("gedChgIso",&gedChgIso,"gedChgIso/F");
  t1->Branch("gedNeuIso",&gedNeuIso,"gedNeuIso/F");
  t1->Branch("gedGenPt",&gedGenPt,"gedGenPt/F");
  t1->Branch("gedPhPixSeed",&gedPhPixSeed,"gedPhPixSeed/F");
  t1->Branch("gedPhweightXS",&gedPhweightXS,"gedPhweightXS/F");

  int sigg = 0;
  int bckk = 0;

   if (fChain == 0) return;
   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;
   
   // calculating the 20-40 pt sample weight
   double weightt1 = 145400*0.001776/(nentries);                    
   cout<<"weight of  this sample "<<weightt1<<endl;  

   cout<<"total entries:"<<nentries<<endl;
   int m1 = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
  
      RvsPV->Fill(nVtx,rho);


      for(uint imc = 0; imc < (*mcPID).size(); imc++){
	
	if((*mcPID)[imc] == 22 && ((*mcMomPID)[imc] == 22 ))cout<< "mom is photon"<<endl;

	if((*mcPID)[imc] == 22 && ((*mcMomPID)[imc] == 22 ) && ((*mcGMomPID)[imc] == 22 )) cout<<"Mom is a photon"<<endl;
		
      }
      //first loop to determine that the event has ONLY one matched photon
      int mPHOS = 0;
      int hptm = 0; 
      int mto1st = 0;
      double maxpt = 0;
      for(uint ipho = 0; ipho < (*phoEt).size(); ipho++){
	double pEta = (*phoEta)[ipho]; 
	double pPhi = (*phoPhi)[ipho]; 

	int pass = 0;
	int Fpho = 0;
	for(uint imc = 0; imc < (*mcPID).size(); imc++){
	  	  
	  if((*mcStatus)[imc] != 1)continue; 
	  if((*mcPID)[imc] != 22)continue;	  
	  if((fabs((*mcMomPID)[imc]) !=21) && (fabs((*mcMomPID)[imc]) !=1)&&(fabs((*mcMomPID)[imc]) !=2)&&(fabs((*mcMomPID)[imc]) !=3)&&(fabs((*mcMomPID)[imc]) !=4)&&(fabs((*mcMomPID)[imc]) !=5)&&(fabs((*mcMomPID)[imc]) !=6))continue;



	  
	  double meta = (*mcEta)[imc];
	  double mphi = (*mcPhi)[imc];	  
	  
	  Fpho++;

	  TVector3 mcphoton;
	  TVector3 recoPHOTOn;
	  
	  mcphoton.SetPtEtaPhi(1.0,meta,mphi);
	  recoPHOTOn.SetPtEtaPhi(1.0,pEta,pPhi);			       
	  double DR = mcphoton.DrEtaPhi(recoPHOTOn);
	  if(DR < 0.1 ){
	    pass = 1;
	    if(Fpho == 1)mto1st = ipho;
	    if((*phoEt)[ipho] > maxpt ){
	      maxpt = (*phoEt)[ipho];
	      hptm = ipho;
	    }
	  }
	}//EOF MC Particles loop	

	if(pass) mPHOS++; 
	if(pass)PIallevs->Fill((*phoEt)[ipho],(*phoPFPhoIso)[ipho]);
	
      }//EOF Photon Loop
      
      
      
      MatchPhos->Fill(mPHOS);

      if(mPHOS == 1){
	PIevs1pho->Fill((*phoEt)[mto1st],(*phoPFPhoIso)[mto1st]);
      }

      if(mPHOS != 0 ){
	PIevs1st->Fill((*phoEt)[mto1st],(*phoPFPhoIso)[mto1st]);
	PIevsMax->Fill((*phoEt)[hptm],(*phoPFPhoIso)[hptm]);
      }




      //if the event has 0 or more than 1 matched photons skip the event;
      if(mPHOS != 1) continue;
      m1++;

      for(uint ipho = 0; ipho < (*phoEt).size(); ipho++){
	double pEta = (*phoEta)[ipho]; 
	double pPhi = (*phoPhi)[ipho]; 


	// setting the photon variables
	Rho = rho;                                                              
        NVtx = nVtx;                                                            
        gedPhPt = (*phoEt)[ipho];                                               
        gedPhEta = pEta;                                                        
        gedPhPhi = pPhi;                                                        
        gedPhSieie = (*phoSigmaIEtaIEta)[ipho];                                 
        gedPhTower   = (*phoHoverE)[ipho];                                      
        gedPhoIso = (*phoPFPhoIso)[ipho];                                       
        gedChgIso = (*phoPFChIso)[ipho];                                        
        gedNeuIso = (*phoPFNeuIso)[ipho];                                       
        gedPhPixSeed  = (*phohasPixelSeed)[ipho];                               
        gedPhweightXS = 1;       

	

	int pass = 0;
	double genPt = -1;
	for(uint imc = 0; imc < (*mcPID).size(); imc++){
	  
	  if((*mcStatus)[imc] != 1)continue; 
	  if((*mcPID)[imc] != 22)continue;
	  
	  if((fabs((*mcMomPID)[imc]) !=21) && (fabs((*mcMomPID)[imc]) !=1)&&(fabs((*mcMomPID)[imc]) !=2)&&(fabs((*mcMomPID)[imc]) !=3)&&(fabs((*mcMomPID)[imc]) !=4)&&(fabs((*mcMomPID)[imc]) !=5)&&(fabs((*mcMomPID)[imc]) !=6))continue;
	  
	

	  double meta = (*mcEta)[imc];
	  double mphi = (*mcPhi)[imc];	  

	  TVector3 mcphoton;
	  TVector3 recoPHOTOn;
	  
	  mcphoton.SetPtEtaPhi(1.0,meta,mphi);
	  recoPHOTOn.SetPtEtaPhi(1.0,pEta,pPhi);			       
	  double DR = mcphoton.DrEtaPhi(recoPHOTOn);

	  if(DR < 0.1 ){
	    genPt = (*mcPt)[imc];
	    pass = 1;
	  }
	}//EOF MC Particles loop 
	gedPhisPrompt = pass;
	gedGenPt = genPt; 
	if(gedPhisPrompt) sigg ++;
	if(gedPhisPrompt == 0) bckk ++;

	t1->Fill();	

      }//EOF Photon Loop



   }//EOF EVENT LOOP 
   cout<<"SIGNAL   "<<sigg <<endl;
   cout<<"background   "<<bckk <<endl;

   cout<<"Total Events :"<< nentries <<endl;
   cout<<"Events with only 1 matched :"<< m1 <<endl;


   RvsPV->Write();      

   
   MatchPhos->Write();      
   PIallevs->Write();
   PIevs1pho->Write();
   PIevs1st->Write();
   PIevsMax->Write();

   t1->Write();
}



