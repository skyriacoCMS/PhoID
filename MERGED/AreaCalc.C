#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <string>
#include <sstream>

//#include <TProfile.h>


void CutID::ArCalc(double e_min, double e_max,int bin){
  //------------Describtion of MACRO FUNCTIONS----------------------------
  //
  // This macro works as a plotter, to plot the ISO, rHO vs the NVTX 
  // as to feed them in the Fitter.C that derives the slopes 
  // and consequently the effective areas for each isolation. 
  //
  // The plots are stored in a file named AreaCalc_X.root 
  // where X stands for the specific eta bin.
  //
  // The input to the file is the bin number and the eta min and eta max
  //
  //---------------------------------------------------------------------

  ostringstream fword;
  fword << bin;   
  string b_name = fword.str();
  string filen = "AreaCalc_"+b_name+".root";  
  char const *fName = filen.c_str();
  TFile *f1;
  f1 =  new TFile(fName,"recreate");


  //General Event Plots
  TH1 *PrimVD = new TH1F("PrimVD","Primary VertexDist",40,0,40);
    
  TH1 *Eta  = new TH1F("Eta","Ged Photon Pt Dist",20,-5,5);
  TH1 *Etas = new TH1F("Etas","Ged Photon Pt Dist",20,-5,5);
  TH1 *Etaf = new TH1F("Etaf","Ged Photon Pt Dist",20,-5,5);
 
  TH1 *Pt = new TH1F("Pt","Ged Photon Pt Dist",400,0,400);
  TH1 *Pts = new TH1F("Pts","Ged Photon signal Pt Dist",400,0,400);
  TH1 *Ptf = new TH1F("Ptf","Ged Photon fake Pt Dist",400,0,400);

  TH1 *SIEIE = new TH1F("SIEIE"," SIEIE",350,0,0.07);
  TH1 *SIEIEf = new TH1F("SIEIEf"," SIEIE",350,0,0.07);
  TH1 *SIEIEs = new TH1F("SIEIEs"," SIEIE",350,0,0.07);

  TH1 *TOW = new TH1F("TOW"," tower",250,0,0.1);
  TH1 *TOWf = new TH1F("TOWf"," tower",250,0,0.1);
  TH1 *TOWs = new TH1F("TOWs"," tower",250,0,0.1);

  // hprof = new TProfile("hprof","jkgskr",100,0,100,0,20);

  TH2D *IsoPvsRho   = new TH2D("IsoPvsRho"," IsoP versus Rho",450,0,45,450,0,450);
  TH2D *IsoCvsRho   = new TH2D("IsoCvsRho"," IsoC versus Rho",450,0,45,450,0,450);
  TH2D *IsoNvsRho   = new TH2D("IsoNvsRho"," IsoN versus Rho",450,0,45,450,0,450);





  TH2D *IsoPvsPV   = new TH2D("IsoPvsPV"," IsoP versus primary vertices",45,0,45,450,0,450);
  //IsoPvsPVp = new TProfile("IsoPvsPVp","IsoP versus primary vertices",200,0,20,0,20);
 
  TH2D *IsoCvsPV   = new TH2D("IsoCvsPV"," IsoC versus primary vertices",45,0,45,450,0,450);

  TH2D *IsoNvsPV   = new TH2D("IsoNvsPV"," IsoN versus primary vertices",45,0,45,450,0,450);
  
  TH2D *IsoPvsPVs   = new TH2D("IsoPvsPVs"," IsoP versus primary vertices",45,0,45,4500,0,450);
  TH2D *IsoCvsPVs   = new TH2D("IsoCvsPVs"," IsoC versus primary vertices",45,0,45,4500,0,450);
  TH2D *IsoNvsPVs   = new TH2D("IsoNvsPVs"," IsoN versus primary vertices",45,0,45,4500,0,450);

  TH2D *IsoPvsPVf   = new TH2D("IsoPvsPVf"," IsoP versus primary vertices",45,0,45,4500,0,450);
  TH2D *IsoCvsPVf   = new TH2D("IsoCvsPVf"," IsoC versus primary vertices",45,0,45,4500,0,450);
  TH2D *IsoNvsPVf   = new TH2D("IsoNvsPVf"," IsoN versus primary vertices",45,0,45,4500,0,450);

  TH2D *IsoPvsPt   = new TH2D("IsoPvsPt"," IsoP versus Pt",450,0,45,400,0,400);
  TH2D *IsoCvsPt   = new TH2D("IsoCvsPt"," IsoC versus Pt",450,0,45,400,0,400);
  TH2D *IsoNvsPt   = new TH2D("IsoNvsPt"," IsoN versus Pt",450,0,45,400,0,400);

  ///////////////////////////////////////////////////////////////////////////////
  //  ----------------  EVENT LOOP BEGINING --------------
  ///////////////////////////////////////////////////////////////////////////////
  if (fChain == 0) return;
  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++){
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      if(jentry % 1000000 == 0)cout<<"event:"<<jentry<<endl;
      
      int PrimV = NVtx;
      double eta = gedPhEta;
      double pt = gedPhPt;
      double phi = gedPhPhi;

	//First selection of Photons Based on eta / binning

      if((fabs(gedPhEta) < e_min || fabs(gedPhEta) > e_max )) continue;
      if(( pt < 15 || pt  > 200 ))continue;



	//-----after selection area -----

	double PhI = gedPhoIso;
	double ChgI = gedChgIso;
	double NeuI = gedNeuIso;	
	

	
	SIEIE->Fill(gedPhSieie);
	TOW->Fill(gedPhTower);
	Pt->Fill(gedPhPt);
	Eta->Fill(gedPhEta);

	IsoPvsPt->Fill(PhI,pt);
	IsoCvsPt->Fill(ChgI,pt);
	IsoNvsPt->Fill(NeuI,pt);


	IsoPvsPV->Fill(PrimV,PhI);
	IsoCvsPV->Fill(PrimV,ChgI);
	IsoNvsPV->Fill(PrimV,NeuI);



	//Signal Photons
	if(gedPhisPrompt == 1){
	  Pts->Fill(gedPhPt);
	  Etas->Fill(gedPhEta);
	  SIEIEs->Fill(gedPhSieie);
	  TOWs->Fill(gedPhTower);

	  
	  IsoPvsPVs->Fill(PrimV,PhI);
	  IsoCvsPVs->Fill(PrimV,ChgI);
	  IsoNvsPVs->Fill(PrimV,NeuI);

	  IsoPvsRho->Fill(Rho,PhI);
	  IsoCvsRho->Fill(Rho,ChgI);
	  IsoNvsRho->Fill(Rho,NeuI);

	  
	  //	  cout<<"Found Photon"<<endl;




	}


	//Background Photons
	if(gedPhisPrompt == 0){
	  TOWf->Fill(gedPhTower);
	  Ptf->Fill(gedPhPt);
	  Etaf->Fill(gedPhEta);
	  SIEIEf->Fill(gedPhSieie);


	  
	  IsoPvsPVf->Fill(PrimV,PhI);
	  IsoCvsPVf->Fill(PrimV,ChgI);
	  IsoNvsPVf->Fill(PrimV,NeuI);
	
	}

	
                 
  }//EOF loop on events //basically photons

   f1->cd();
   Eta->Write(); 
   Etas->Write();
   Etaf->Write();
   
   Pt->Write();
   Pts->Write();
   Ptf->Write();
   
   SIEIE->Write();
   SIEIEf->Write();
   SIEIEs->Write();
   
   TOW->Write();
   TOWf->Write();
   TOWs->Write();
   

   

   IsoPvsPV->Write();
   IsoCvsPV->Write();
   IsoNvsPV->Write();
   
   IsoPvsPVs->Write();
   IsoCvsPVs->Write();
   IsoNvsPVs->Write();
   
   IsoPvsPVf->Write();
   IsoCvsPVf->Write();
   IsoNvsPVf->Write();
   
   IsoPvsPt->Write();
   IsoCvsPt->Write();
   IsoNvsPt->Write();

   
   IsoPvsRho->Write();
   IsoCvsRho->Write();
   IsoNvsRho->Write();




   f1->Close();
}// loop function end

