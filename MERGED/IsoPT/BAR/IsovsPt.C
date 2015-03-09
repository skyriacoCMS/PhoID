#include <cstdlib>
#include <TFile.h>
#include <TGraph.h>
#include <TH1F.h>


void IsovsPt(){
  TFile *f1 = new TFile("../../CutTMVATrees_Barrel.root");
  float genPt,ppt,peta,Sie_ie,iso_P,iso_C,iso_N,to_e,weighT;
  int nvtx;
  gStyle->SetOptStat(0);

  //Signal Tree
  t_S->SetBranchAddress("Sieie",&Sie_ie);
  t_S->SetBranchAddress("isoP",&iso_P);
  t_S->SetBranchAddress("isoC",&iso_C);
  t_S->SetBranchAddress("isoN",&iso_N);
  t_S->SetBranchAddress("ToE",&to_e);
  t_S->SetBranchAddress("weighT",&weighT);

  t_S->SetBranchAddress("Nvtx",&nvtx);
  t_S->SetBranchAddress("Peta",&peta);
  t_S->SetBranchAddress("Ppt",&ppt);
  t_S->SetBranchAddress("genPt",&genPt);

  //Background Tree
  t_B->SetBranchAddress("Sieie",&Sie_ie);
  t_B->SetBranchAddress("isoP",&iso_P);
  t_B->SetBranchAddress("isoC",&iso_C);
  t_B->SetBranchAddress("isoN",&iso_N);
  t_B->SetBranchAddress("ToE",&to_e);
  t_B->SetBranchAddress("weighT",&weighT);

  t_B->SetBranchAddress("Nvtx",&nvtx);
  t_B->SetBranchAddress("Peta",&peta);
  t_B->SetBranchAddress("Ppt",&ppt);



  TH2F *isoCptS = new TH2F("isoCptS","Iso Charge vs Pt",100,0,200,3000,0,30);
  TH2F *isoNptS = new TH2F("isoNptS","Iso Neutral vs Pt",100,0,200,3000,0,30);
  TH2F *isoPptS = new TH2F("isoPptS","Iso Photon vs Pt",100,0,200,3000,0,30);




  for(int i  = 0; i < t_S->GetEntries();i++){
    t_S->GetEntry(i);
    
    if(ppt < 25) continue;

    isoCptS->Fill(ppt,iso_C);
    isoNptS->Fill(ppt,iso_N);
    isoPptS->Fill(ppt,iso_P);
  }







  // Now that we have the Iso vs pt histograms lets see the efficiency in pt bins

  double BinCch [100][3000] = {0};
  double BinCph [100][3000] = {0};
  double BinCh  [100][3000] = {0};
 
  double ptX[100] ={0};

  

  cout<<"here"<<endl;

  for(int j  = 0 ; j < 100 ; j++){
  
    double ptx = 200.0*j/100 + 1.0; 
    ptX[j] = ptx; 

    for(int i  = 0; i < 3000 ; i++){
      double isocx = 30.0*i/3000 + 0.005; 
      double isopx = 30.0*i/3000 + 0.005; 
      double isonx = 30.0*i/3000 + 0.005; 
      
      int bin =  isoCptS->FindBin(ptx,isocx);    
      BinCch[j][i] = isoCptS->GetBinContent(bin);

      bin =  isoPptS->FindBin(ptx,isopx);    
      BinCph[j][i] = isoPptS->GetBinContent(bin);

      bin =  isoNptS->FindBin(ptx,isonx);    
      BinCh[j][i] = isoNptS->GetBinContent(bin);

    
    
    }

  } 




  double ch_95[100] = {0};
  double ch_90[100] = {0}; 
  double ch_80[100] = {0}; 
  double ch_70[100] = {0}; 
  
  

  double ph_95[100] = {0};
  double ph_90[100] = {0}; 
  double ph_80[100] = {0}; 
  double ph_70[100] = {0}; 
  
  double ne_95[100] = {0};
  double ne_90[100] = {0}; 
  double ne_80[100] = {0}; 
  double ne_70[100] = {0}; 
  
  double ch_95e[100] = {0};
  double ch_90e[100] = {0}; 
  double ch_80e[100] = {0}; 
  double ch_70e[100] = {0}; 
  
  double ph_95e[100] = {0}; 
  double ph_90e[100] = {0}; 
  double ph_80e[100] = {0}; 
  double ph_70e[100] = {0}; 
  
  double ne_95e[100] = {0};
  double ne_90e[100] = {0}; 
  double ne_80e[100] = {0}; 
  double ne_70e[100] = {0}; 



  
  for(int j = 0 ; j  < 100; j ++){
    
    double totC = 0;
    double totN = 0;
    double totP = 0;
    
    for(int i = 0; i < 3000; i++) totC = totC + BinCch[j][i];
    for(int i = 0; i < 3000; i++) totN = totN + BinCh[j][i]; 
    for(int i = 0; i < 3000; i++) totP = totP + BinCph[j][i]; 

   

    double entrC = 0;
    double entrP = 0;
    double entrN = 0;
    
    int passc95 = 0; 
    int passc9 = 0;
    int passc8 = 0;
    int passc7 = 0;

    int passp95 = 0; 
    int passp9 = 0;
    int passp8 = 0;
    int passp7 = 0;

    int passn95 = 0; 
    int passn9 = 0;
    int passn8 = 0;
    int passn7 = 0; 

    for(int i  = 0; i < 3000 ; i++){
      
      entrC = entrC + BinCch[j][i];
      entrP = entrP + BinCph[j][i];
      entrN = entrN + BinCh[j][i];

      //------- photon
      if(passp95 == 0 && entrP*1.0/totP  > 0.95){
	
	double num = sqrt(entrP);
	double den = sqrt(totP);

	ph_95e[j] = 0.95*sqrt(pow(num/totP,2) + pow(den/entrP,2) );



	ph_95[j] = i*0.01;
	passp95= 1; 
      }

      


      if(passp9 == 0 && entrP*1.0/totP  > 0.90){
	
	double num = sqrt(entrP);
	double den = sqrt(totP);

	ph_90e[j] = 0.9*sqrt(pow(num/totP,2) + pow(den/entrP,2) );



	ph_90[j] = i*0.01;
	passp9 = 1; 
      }
      if(passp8 == 0 && entrP*1.0/totP  > 0.80){

	
	double num = sqrt(entrP);
	double den = sqrt(totP);

	ph_80e[j] = 0.8*sqrt(pow(num/totP,2) + pow(den/entrP,2) );

	
	ph_80[j] = i*0.01;
	passp8 = 1; 
      }
      if(passp7 == 0 && entrP*1.0/totP  > 0.70){

	
	double num = sqrt(entrP);
	double den = sqrt(totP);

	ph_70e[j] = 0.7*sqrt(pow(num/totP,2) + pow(den/entrP,2) );



	ph_70[j] = i*0.01;
	passp7 = 1; 
      }


      //--------- charge
      if(passc95 == 0 && entrC*1.0/totC  > 0.95){
	
	double num = sqrt(entrC);
	double den = sqrt(totC);

	ch_95e[j] = 0.95*sqrt(pow(num/totC,2) + pow(den/entrC,2) );



	ch_95[j] = i*0.01;
	passc95= 1; 
      }
      

      if(passc9 == 0 && entrC*1.0/totC  > 0.90){

	double num = sqrt(entrC);
	double den = sqrt(totC);

	ch_90e[j] = 0.9*sqrt(pow(num/totC,2) + pow(den/entrC,2) );

	ch_90[j] = i*0.01;
	passc9 = 1; 
      }
      if(passc8 == 0 && entrC*1.0/totC  > 0.80){

	double num = sqrt(entrC);
	double den = sqrt(totC);

	ch_80e[j] = 0.8*sqrt(pow(num/totC,2) + pow(den/entrC,2) );

	ch_80[j] = i*0.01;
	passc8 = 1; 
      }
      if(passc7 == 0 && entrC*1.0/totC  > 0.70){
	
	double num = sqrt(entrC);
	double den = sqrt(totC);

	ch_70e[j] = 0.7*sqrt(pow(num/totC,2) + pow(den/entrC,2) );

	ch_70[j] = i*0.01;
	passc7 = 1; 
      }

      
      //--------- neutral
      if(passn95 == 0 && entrN*1.0/totN  > 0.95){
	
	double num = sqrt(entrN);
	double den = sqrt(totN);

	ne_95e[j] = 0.95*sqrt(pow(num/totN,2) + pow(den/entrN,2) );



	ne_95[j] = i*0.01;
	passn95= 1; 
      }
    






      if(passn9 == 0 && entrN*1.0/totN  > 0.90){

	
	double num = sqrt(entrN);
	double den = sqrt(totN);

	ne_90e[j] = 0.9*sqrt(pow(num/totN,2) + pow(den/entrN,2) );



	ne_90[j] = i*0.01;
	passn9 = 1; 
      }
      if(passn8 == 0 && entrN*1.0/totN  > 0.80){

	
	double num = sqrt(entrN);
	double den = sqrt(totN);

	ne_80e[j] = 0.8*sqrt(pow(num/totN,2) + pow(den/entrN,2) );


	ne_80[j] = i*0.01; 
	passn8 = 1; 
      }
      if(passn7 == 0 && entrN*1.0/totN  > 0.70){

	
	double num = sqrt(entrN);
	double den = sqrt(totN);

	ne_70e[j] = 0.7*sqrt(pow(num/totN,2) + pow(den/entrN,2) );


	ne_70[j] = i*0.01;
	passn7 = 1; 
      }


    }
    
  }
  


  TF1 *fn1 = new TF1("fn1","[0]*x+[1]",25,200);
  TF2 *fn2 = new TF1("fn2","[0]*x+[1]",25,200);
  TF3 *fn3 = new TF1("fn3","[0]*x+[1]",25,200);

  TF1 *fp1 = new TF1("fp1","[0]*x+[1]",25,200);
  TF2 *fp2 = new TF1("fp2","[0]*x+[1]",25,200);
  TF3 *fp3 = new TF1("fp3","[0]*x+[1]",25,200);

  TF1 *fc1 = new TF1("fc1","[0]*x+[1]",25,200);
  TF2 *fc2 = new TF1("fc2","[0]*x+[1]",25,200);
  TF3 *fc3 = new TF1("fc3","[0]*x+[1]",25,200);
  


  double ptXe[100] = {2};
  TGraph *p95 = new TGraphErrors(100,ptX,ph_95,ptXe,ph_95e);
  TGraph *p9 = new TGraphErrors(100,ptX,ph_90,ptXe,ph_90e);
  TGraph *p8 = new TGraphErrors(100,ptX,ph_80,ptXe,ph_80e);
  TGraph *p7 = new TGraphErrors(100,ptX,ph_70,ptXe,ph_70e);

  
  p95->Fit("fp1","R");
  p9->Fit("fp2","R");
  p8->Fit("fp3","R");





  p95->SetMarkerColor(kMagenta);
  p9->SetMarkerColor(kRed);
  p8->SetMarkerColor(kOrange);
  p7->SetMarkerColor(kYellow);
 

  p95->SetMarkerSize(kMagenta);
  p9->SetMarkerSize(1);
  p8->SetMarkerSize(1);
  p7->SetMarkerSize(1);

  
  p95->SetLineColor(kMagenta);
  p9->SetLineColor(kRed);
  p8->SetLineColor(kOrange);
  p7->SetLineColor(kYellow);






  TGraph *n95 = new TGraphErrors(100,ptX,ne_95,ptXe,ne_95e);
  TGraph *n9 = new TGraphErrors(100,ptX,ne_90,ptXe,ne_90e);
  TGraph *n8 = new TGraphErrors(100,ptX,ne_80,ptXe,ne_80e);
  TGraph *n7 = new TGraphErrors(100,ptX,ne_70,ptXe,ne_70e);

  n95->Fit("fn1","R");
  n9->Fit("fn2","R");
  n8->Fit("fn3","R");


  n95->SetMarkerColor(kMagenta);
  n9->SetMarkerColor(kRed);
  n8->SetMarkerColor(kOrange);
  n7->SetMarkerColor(kYellow);

  n95->SetMarkerSize(kMagenta);
  n9->SetMarkerSize(1);
  n8->SetMarkerSize(1);
  n7->SetMarkerSize(1);

  n95->SetLineColor(kMagenta);
  n9->SetLineColor(kRed);
  n8->SetLineColor(kOrange);
  n7->SetLineColor(kYellow);




  TGraph *c95 = new TGraphErrors(100,ptX,ch_95,ptXe,ch_95e);
  TGraph *c9 = new TGraphErrors(100,ptX,ch_90,ptXe,ch_90e);
  TGraph *c8 = new TGraphErrors(100,ptX,ch_80,ptXe,ch_80e);
  TGraph *c7 = new TGraphErrors(100,ptX,ch_70,ptXe,ch_70e);

  
  c95->Fit("fc1","R");
  c9->Fit("fc2","R");
  c8->Fit("fc3","R");





  c95->SetMarkerColor(kMagenta); 
  c9->SetMarkerColor(kRed);
  c8->SetMarkerColor(kOrange);
  c7->SetMarkerColor(kYellow);


  c95->SetLineColor(kMagenta); 
  c9->SetLineColor(kRed);
  c8->SetLineColor(kOrange);
  c7->SetLineColor(kYellow);



  c95->SetMarkerSize(1);
  c9->SetMarkerSize(1);
  c8->SetMarkerSize(1);
  c7->SetMarkerSize(1);




  TMultiGraph *PhoIso = new TMultiGraph();
  TMultiGraph *ChgIso = new TMultiGraph();
  TMultiGraph *NeuIso = new TMultiGraph();


  PhoIso->Add(p95,"p");
  PhoIso->Add(p9,"p");
  PhoIso->Add(p7,"p");
  PhoIso->Add(p8,"p");


  ChgIso->Add(c95,"p");
  ChgIso->Add(c9,"p");
  ChgIso->Add(c7,"p");
  ChgIso->Add(c8,"p");

  NeuIso->Add(n95,"p");
  NeuIso->Add(n9,"p");
  NeuIso->Add(n7,"p");
  NeuIso->Add(n8,"p");

  



  TCanvas *c1 = new TCanvas("c1","Iso P vs Pt",1000,500);
  c1->Divide(2,1); 

  c1->cd(1);
  PhoIso->Draw("AP");
  PhoIso->GetXaxis()->SetTitle("Pt GeVc^{-1}");
  PhoIso->GetYaxis()->SetTitle("Isolation PF:gamma");
  

  
  c1->cd(2)->SetLogz();
  
  isoPptS->Draw("colz");  
  isoPptS->GetXaxis()->SetTitle("Pt GeVc^{-1}");
  isoPptS->GetYaxis()->SetTitle("Isolation PF:gamma");

  c1->SaveAs("P.png");


  TCanvas *c2 = new TCanvas("c2","Iso C vs Pt",1000,500);
  c2->Divide(2,1);
  c2->cd(1);
  ChgIso->Draw("AP");
  ChgIso->GetXaxis()->SetTitle("Pt GeVc^{-1}");
  ChgIso->GetYaxis()->SetTitle("Isolation PF:ch hadrons");
  

  c2->cd(2)->SetLogz();
  
  isoCptS->Draw("colz");  
  isoCptS->GetXaxis()->SetTitle("Pt GeVc^{-1}");
  isoCptS->GetYaxis()->SetTitle("Isolation PF:ch hadrons");


  c2->SaveAs("C.png");
  
  TCanvas *c3 = new TCanvas("c3","Iso N vs Pt",1000,500);
  c3->Divide(2,1);
  c3->cd(1);
  NeuIso->Draw("AP");
  NeuIso->GetXaxis()->SetTitle("Pt GeVc^{-1}");
  NeuIso->GetYaxis()->SetTitle("Isolation PF:h0");
  

  c3->cd(2)->SetLogz();
  
  isoNptS->Draw("colz");  
  isoNptS->GetXaxis()->SetTitle("Pt GeVc^{-1}");
  isoNptS->GetYaxis()->SetTitle("Isolation PF:h0");


  c3->SaveAs("N.png");

  c1->Update();






  c2->Update();
  c3->Update();


  cout<<"--    The slopes ---"<<endl;


  TF1 *fpp1  = p95->GetFunction("fp1");
  TF1 *fpp2  = p9->GetFunction("fp2");
  TF1 *fpp3  = p8->GetFunction("fp3");

  TF1 *fcc1  = c95->GetFunction("fc1");
  TF1 *fcc2  = c9->GetFunction("fc2");
  TF1 *fcc3  = c8->GetFunction("fc3");

  TF1 *fnn1  = n95->GetFunction("fn1");
  TF1 *fnn2  = n9->GetFunction("fn2");
  TF1 *fnn3  = n8->GetFunction("fn3");

  
  double ap1 = fpp1->GetParameter(0); 
  double ap2 = fpp2->GetParameter(0); 
  double ap3 = fpp3->GetParameter(0);

  double ac1 = fcc1->GetParameter(0); 
  double ac2 = fcc2->GetParameter(0); 
  double ac3 = fcc3->GetParameter(0);

  double an1 = fnn1->GetParameter(0); 
  double an2 = fnn2->GetParameter(0); 
  double an3 = fnn3->GetParameter(0);



  cout<<"--------------------------------------------------------------"<<endl;
  cout<<"Photons "<<endl;
  cout<<ap1<<"  "<<ap2<<" "<<ap3<<" ave "<< (ap1 + ap2 + ap3)/3.0<<endl;
  cout<<endl;

  cout<<"--------------------------------------------------------------"<<endl;

  cout<<"Neutral "<<endl;
  
  cout<<an1<<"  "<<an2<<" "<<an3<<" ave "<<(an1 + an2 + an3)/3.0<<endl;
 cout<<endl;


  cout<<"--------------------------------------------------------------"<<endl;

  cout<<"Charged "<<endl;
  
  cout<<ac1<<"  "<<ac2<<" "<<ac3<<" ave  "<<(ac1 + ac2 + ac3)/3.0<<endl;
 cout<<endl;
  cout<<"--------------------------------------------------------------"<<endl;









}
