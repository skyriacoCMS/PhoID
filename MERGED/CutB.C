
//#define CUTID_cxx
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void CutID::CutBasedID(int reg,double EFFAr[7][3]){

  TFile *f1;
  if(reg == 1) f1 =  new TFile("HPT_Barrel.root","recreate");
  if(reg == 2) f1 =  new TFile("HPT_EndCap.root","recreate");

  TTree *t_S = new TTree("t_S","CUT NEEDS THIS  ");
  TTree *t_B = new TTree("t_B","CUT NEEDS THIS ");
  
  TTree *t_R = new TTree("t_R","CUT NEEDS THIS ");


  TH1F *SieieSw = new TH1F("SieieSw","Sigma ie ie signal pt weighted",1000,0,1);
  TH1F *SieieBw = new TH1F("SieieBw","Sigma ie ie background pt weighted",1000,0,1);

  TH1F *TowSw = new TH1F("TowSw","H o E ie ie signal pt weighted",600,0,6);
  TH1F *TowBw = new TH1F("TowBw","H o E ie ie background pt weighted",600,0,6);

  TH1F *iSOPsw = new TH1F("iSOPsw","Iso gamma  signal pt weighted",300,0,30);
  TH1F *iSOPbw = new TH1F("iSOPbw","Iso gamma  background pt weighted",300,0,30);

  TH1F *iSOCsw = new TH1F("iSOCsw","Iso charge  signal pt weighted",300,0,30);
  TH1F *iSOCbw = new TH1F("iSOCbw","Iso charge  background pt weighted",300,0,30);

  TH1F *iSONsw = new TH1F("iSONsw","Iso neutral  signal pt weighted",300,0,30);
  TH1F *iSONbw = new TH1F("iSONbw","Iso neutral  background pt weighted",300,0,30);
  
  TH1F *pTs = new TH1F("pTs","Signal Pt ",185,15,200);
  TH1F *pTb = new TH1F("pTb","Bckground Pt",185,15,200);

  TH1F *etaS = new TH1F("etaS","Signal Eta   ",20,-5,5);
  TH1F *etaB = new TH1F("etaB","Bckground Eta",20,-5,5);  
  TH1F *etaSw = new TH1F("etaSw","Signal Eta weighted  ",200,-5,5);
  TH1F *etaBw = new TH1F("etaBw","Bckground Eta weighted",200,-5,5);

  TH1F *pTsw = new TH1F("pTsw","Signal Ptpt weighted ",185,15,200);
  TH1F *pTbw = new TH1F("pTbw","Bckground Pt pt weighted",185,15,200);

  TH2D *etaPts = new TH2D("etaPts","Eta vs pt",200,-5,5,185,15,200);
  TH2D *etaPtb = new TH2D("etaPtb","Eta vs pt",200,-5,5,185,15,200);
  
  TH2D *etaPtsw = new TH2D("etaPtsw","Eta vs pt weighted",200,-5,5,185,15,200);
  TH2D *etaPtbw = new TH2D("etaPtbw","Eta vs pt weighted",200,-5,5,185,15,200);
  
  // in case we expand in the frixione etc cones 
  //  double isoN,isoC,isoP,Fc1N,Fc2N,Fc3N,Fc1C,Fc2C,Fc3C,Fc1P,Fc2P,Fc3P,Mc1N,Mc2N,Mc3N,Mc1C,Mc2C,Mc3C,Mc1P,Mc2P,Mc3P,Sieie,ToE,Peta,Pphi,Ppt;

  float genPt,isoN,isoC,isoP,isoNu,isoCu,isoPu,Peta,Ppt,Pphi,ToE,Sieie,Sieie2012,weighT;

  int Pix,Nvtx;

  
  t_S->Branch("Peta",&Peta,"Peta/F");
  t_S->Branch("Pphi",&Pphi,"Pphi/F");
  t_S->Branch("Ppt",&Ppt,"Ppt/F");
  t_S->Branch("isoN",&isoN,"isoN/F");   
  t_S->Branch("isoP",&isoP,"isoP/F");
  t_S->Branch("isoC",&isoC,"isoC/F");

  
  //  t_S->Branch("isoNu",&isoNu,"isoNu/F");
  // t_S->Branch("isoPu",&isoPu,"isoPu/F");
  // t_S->Branch("isoCu",&isoCu,"isoCu/F");


  t_S->Branch("Nvtx",&Nvtx,"Nvtx/I");

  t_S->Branch("genPt",&genPt,"genPt/F");
  
  t_S->Branch("Sieie",&Sieie,"Sieie/F");

  t_S->Branch("ToE",&ToE,"ToE/F");

  t_S->Branch("Pix",&Pix,"Pix/I");
  t_S->Branch("weighT",&weighT,"weightT/F");


  /* 
  t_S->Branch("Fc1N",&Fc1N,"Fc1N/D");
  t_S->Branch("Fc2N",&Fc1N,"Fc2N/D");
  t_S->Branch("Fc3N",&Fc1N,"Fc3N/D");

  t_S->Branch("Fc1P",&Fc1P,"Fc1P/D");
  t_S->Branch("Fc2P",&Fc1P,"Fc2P/D");
  t_S->Branch("Fc3P",&Fc1P,"Fc3P/D");

  t_S->Branch("Fc1C",&Fc1C,"Fc1C/D");
  t_S->Branch("Fc2C",&Fc1C,"Fc2C/D");
  t_S->Branch("Fc3C",&Fc1C,"Fc3C/D");


  
  t_S->Branch("Mc1N",&Mc1N,"Mc1N/D");
  t_S->Branch("Mc2N",&Mc1N,"Mc2N/D");
  t_S->Branch("Mc3N",&Mc1N,"Mc3N/D");

  t_S->Branch("Mc1P",&Mc1P,"Mc1P/D");
  t_S->Branch("Mc2P",&Mc1P,"Mc2P/D");
  t_S->Branch("Mc3P",&Mc1P,"Mc3P/D");

  t_S->Branch("Mc1C",&Mc1C,"Mc1C/D");
  t_S->Branch("Mc2C",&Mc1C,"Mc2C/D");
  t_S->Branch("Mc3C",&Mc1C,"Mc3C/D");
  */


  //---------Background Tree---------------

  t_B->Branch("Peta",&Peta,"Peta/F");
  t_B->Branch("Pphi",&Pphi,"Pphi/F");
  t_B->Branch("Ppt",&Ppt,"Ppt/F");

  t_B->Branch("isoN",&isoN,"isoN/F");
  t_B->Branch("isoP",&isoP,"isoP/F");
  t_B->Branch("isoC",&isoC,"isoC/F");

  // t_B->Branch("isoNu",&isoNu,"isoNu/F");
  // t_B->Branch("isoPu",&isoPu,"isoPu/F");
  // t_B->Branch("isoCu",&isoCu,"isoCu/F");

  

  t_B->Branch("Sieie",&Sieie,"Sieie/F");

  t_B->Branch("ToE",&ToE,"ToE/F");

  
  t_B->Branch("Pix",&Pix,"Pix/I");
  t_B->Branch("weighT",&weighT,"weightT/F");

  t_B->Branch("Nvtx",&Nvtx,"Nvtx/I");


  /* 
  t_B->Branch("Fc1N",&Fc1N,"Fc1N/D");
  t_B->Branch("Fc2N",&Fc1N,"Fc2N/D");
  t_B->Branch("Fc3N",&Fc1N,"Fc3N/D");

  t_B->Branch("Fc1P",&Fc1P,"Fc1P/D");
  t_B->Branch("Fc2P",&Fc1P,"Fc2P/D");
  t_B->Branch("Fc3P",&Fc1P,"Fc3P/D");

  t_B->Branch("Fc1C",&Fc1C,"Fc1C/D");
  t_B->Branch("Fc2C",&Fc1C,"Fc2C/D");
  t_B->Branch("Fc3C",&Fc1C,"Fc3C/D");

  t_B->Branch("Mc1N",&Mc1N,"Mc1N/D");
  t_B->Branch("Mc2N",&Mc1N,"Mc2N/D");
  t_B->Branch("Mc3N",&Mc1N,"Mc3N/D");

  t_B->Branch("Mc1P",&Mc1P,"Mc1P/D");
  t_B->Branch("Mc2P",&Mc1P,"Mc2P/D");
  t_B->Branch("Mc3P",&Mc1P,"Mc3P/D");

  t_B->Branch("Mc1C",&Mc1C,"Mc1C/D");
  t_B->Branch("Mc2C",&Mc1C,"Mc2C/D");
  t_B->Branch("Mc3C",&Mc1C,"Mc3C/D");
  */


 
  ///////////////////////////////////////////////////////////////////////////////

  //  ----------------  EVENT LOOP BEGINING --------------

  ///////////////////////////////////////////////////////////////////////////////

  // this first loop on the events is for deriving the weights of the trainning
  // so we are only interested on the pt distribution of back/ signal events
  

  if (fChain == 0) return;
  Long64_t nentries = fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++){
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;

    int PrimV = NVtx;
    
    //Geetign the weights regarding the Pt for each event

      //Pt Cut
      
    //    if(gedPhPt< 15 || gedPhPt > 200)continue;
    if(gedPhPt< 15) continue; // || gedPhPt > 200)continue;
      
      //Eta barrel endcap def
      if(reg == 1 && fabs(gedPhEta) > 1.4442 ) continue;
      if(reg == 2 && ( fabs(gedPhEta) < 1.566 || fabs(gedPhEta) > 2.5  )) continue;
      
      if(gedPhisPrompt){
	pTs->Fill(gedPhPt,gedPhweightXS);
	etaS->Fill(gedPhEta,gedPhweightXS);
	etaPts->Fill(gedPhEta,gedPhPt,gedPhweightXS);

      }
      if(gedPhisPrompt == 0){
	pTb->Fill(gedPhPt,gedPhweightXS);
	etaB->Fill(gedPhEta,gedPhweightXS);
	etaPtb->Fill(gedPhEta,gedPhPt,gedPhweightXS);
      }
  }

  
  TAxis *xS = pTs->GetXaxis();
  TAxis *xB = pTb->GetXaxis();

  TAxis *xES = etaS->GetXaxis();
  TAxis *xEB = etaB->GetXaxis();

  cout<<"end of first loop on events"<<endl;

  for (Long64_t jentry=0; jentry<nentries;jentry++){
    Long64_t ientry = LoadTree(jentry);
    if (ientry < 0) break;
    nb = fChain->GetEntry(jentry);   nbytes += nb;
       
    double eta = gedPhEta;
    if(gedPhPt < 15) continue; // || gedPhPt > 200   ) continue;
    
    //---------------------------------------------------------------------
    //      CALC OF THE RHO SUB - ISOLATION 
    //---------------------------------------------------------------------
    double EAph = 0; 
    double EAneu = 0;
    double EAch = 0;	
    
    //Setting up the effective areas
    int biin;
    if(fabs(eta) < 1.0 )biin = 0;
    if(fabs(eta) > 1.0 && fabs(eta) < 1.479)biin = 1;
    if(fabs(eta) > 1.479 && fabs(eta) < 2.0)biin = 2;
    if(fabs(eta) > 2.0 && fabs(eta) < 2.2)biin = 3;
    if(fabs(eta) > 2.2 && fabs(eta) < 2.3)biin = 4;
    if(fabs(eta) > 2.3 && fabs(eta) < 2.4)biin = 5;
    if(fabs(eta) > 2.4 ) biin = 6;
    
    
    
    EAph  = EFFAr[biin][2];
    EAneu = EFFAr[biin][1];
    EAch  = EFFAr[biin][0];
    ///
    
    float PhI = gedPhoIso;
    float ChgI = gedChgIso;
    float NeuI = gedNeuIso;	
    
    
    PhI = max( PhI - Rho*EAph,0.0);
    ChgI = max( ChgI - Rho*EAch,0.0);
    NeuI = max( NeuI - Rho*EAneu,0.0);
    
    
    //EOF THE ISOLATION CALCULATION
    
    if(reg == 1 && fabs(gedPhEta) > 1.4442 ) continue;
    if(reg == 2 && ( fabs(gedPhEta) < 1.566 || fabs(gedPhEta) > 2.5  )) continue;
    
    if(gedPhisPrompt){
      Peta=gedPhEta;
      Pphi=gedPhPhi;
      Ppt=gedPhPt;
      Pix = gedPhPixSeed;
      isoP = PhI;
      isoC = ChgI;
      isoN = NeuI;

      isoPu = gedPhoIso;
      isoCu = gedChgIso;
      isoNu = gedNeuIso;



      Sieie =gedPhSieie ;

      ToE = gedPhTower;
      genPt = gedGenPt; 
      Nvtx = NVtx; 

      int binx = etaPts->FindBin(gedPhEta,gedPhPt);
      weighT = 1./etaPts->GetBinContent(binx);
     
      /*
      int binx = xS->FindBin(gedPhPt);
      weighT = 1./(pTs->GetBinContent(binx));
      binx = xES->FindBin(gedPhEta);
      weighT = weighT*(1./(etaS->GetBinContent(binx)));
      */

      SieieSw->Fill(Sieie,weighT);
      TowSw->Fill(ToE,weighT);
      iSOPsw->Fill(isoP,weighT);
      iSONsw->Fill(isoN,weighT);
      iSOCsw->Fill(isoC,weighT);
      pTsw->Fill(Ppt,weighT);
      etaSw->Fill(Peta,weighT);
      etaPtsw->Fill(Peta,Ppt,weighT);
      t_S->Fill();     
    }
    
    
    if(gedPhisPrompt == 0){
      
      Peta = gedPhEta;
      Pphi = gedPhPhi;
      Ppt  = gedPhPt;
      Pix  = gedPhPixSeed;
      
      isoP = PhI;
      isoC = ChgI;
      isoN = NeuI;

      
      isoPu = gedPhoIso;
      isoCu = gedChgIso;
      isoNu = gedNeuIso;


      
      Sieie = gedPhSieie ;

      ToE   = gedPhTower;

      Nvtx = NVtx; 




      /*int binx = xB->FindBin(gedPhPt);
      weighT = 1./(pTb->GetBinContent(binx));
      binx = xEB->FindBin(gedPhEta);*/
      
      int binx = etaPtb->FindBin(gedPhEta,gedPhPt);
      weighT = 1./(etaPtb->GetBinContent(binx));
      t_B->Fill();
	
      // weighT = weighT*(1./(etaB->GetBinContent(binx)));
      
      SieieBw->Fill(Sieie,weighT);
      TowBw->Fill(ToE,weighT);
      iSOPbw->Fill(isoP,weighT);
      iSONbw->Fill(isoN,weighT);
      iSOCbw->Fill(isoC,weighT);
      pTbw->Fill(Ppt,weighT);
      etaBw->Fill(Peta,weighT);
      etaPtbw->Fill(Peta,Ppt,weighT);
					       
    }
	


  }//eof the event loop


  t_S->Write();
  t_B->Write();
  t_R->Write();


  SieieSw->Write();
  TowSw->Write();
  iSOPsw->Write();
  iSONsw->Write();
  iSOCsw->Write();  

  SieieBw->Write();
  TowBw->Write();
  iSOPbw->Write();
  iSONbw->Write();
  iSOCbw->Write();
  
  pTsw->Write();
  pTbw->Write();

  etaSw->Write();
  etaBw->Write();

  etaPts->Write();
  etaPtb->Write();

  etaPtsw->Write();
  etaPtbw->Write();


  f1->Close();
}// loop function end







