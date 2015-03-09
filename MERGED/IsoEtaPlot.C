
//#define CUTID_cxx
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TGraph.h>



void CutID::IsoEta(){

  TFile *f1 =  new TFile("IsoVSEta.root","recreate");
  TH1D *Nvrt = new TH1D("Nvrt","Vertices ",50,0,50);

  TH2D *IsoEtaP_l = new TH2D("IsoEtaP_l","IsoPvs Eta ",100,0,5,300,0,30);
  TH2D *IsoEtaP_h = new TH2D("IsoEtaP_h","IsoPvs Eta",100,0,5,300,0,30);

  TH2D *IsoEtaC_l = new TH2D("IsoEtaC_l","IsoCvs Eta ",100,0,5,300,0,30);
  TH2D *IsoEtaC_h = new TH2D("IsoEtaC_h","IsoCvs Eta",100,0,5,300,0,30);

  TH2D *IsoEtaN_l = new TH2D("IsoEtaN_l","IsoNvs Eta ",100,0,5,300,0,30);
  TH2D *IsoEtaN_h = new TH2D("IsoEtaN_h","IsoNvs Eta",100,0,5,300,0,30);



 
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

    //Cut on the Pt of the Photon




    if(gedPhPt < 30 && gedPhPt > 200 )continue;
    if(gedPhisPrompt == 0)continue;


    Nvrt->Fill(NVtx);


    //Making sure it is signal photon 


    //filling low bins
    if(NVtx >= 13 && NVtx < 15){
      
      IsoEtaP_l->Fill(gedPhEta,gedPhoIso);
      IsoEtaC_l->Fill(gedPhEta,gedChgIso);
      IsoEtaN_l->Fill(gedPhEta,gedNeuIso);

    }
    

    //Filling second bin 
    if(NVtx >= 19 && NVtx < 21){

      
      IsoEtaP_h->Fill(gedPhEta,gedPhoIso);
      IsoEtaC_h->Fill(gedPhEta,gedChgIso);
      IsoEtaN_h->Fill(gedPhEta,gedNeuIso);

      
    }








  }//EOF loop
 
  
  IsoEtaP_l->Write();
  IsoEtaP_h->Write();

  IsoEtaC_l->Write();
  IsoEtaC_h->Write();

  IsoEtaN_l->Write();
  IsoEtaN_h->Write();

    


  Nvrt->Write();


}



