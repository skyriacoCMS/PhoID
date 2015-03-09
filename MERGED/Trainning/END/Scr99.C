#include <TFile.h>
#include <TH1F.h>
#include <fstream>
void Scr99(){


  TFile *f1 = new TFile("../../CutTMVATrees_EndCap.root");


  float ToE,Sie,IsoP,IsoC,IsoN,weighT,weightXS,Ppt; 

  ofstream myfile; 
  myfile.open("99per.txt");

  f1->cd();

  t_S->SetBranchAddress("ToE",&ToE);
  t_S->SetBranchAddress("Sieie",&Sie);
  t_S->SetBranchAddress("isoP",&IsoP);
  t_S->SetBranchAddress("isoC",&IsoC);
  t_S->SetBranchAddress("isoN",&IsoN);
  t_S->SetBranchAddress("weighT",&weighT);
  t_S->SetBranchAddress("Ppt",&Ppt);
  
  weightXS = 1;

  TH1F *HS = new TH1F("HS","sieie ",10000,0,0.15);
  TH1F *HH = new TH1F("HH","sieie ",10000,0,40);
  TH1F *HP = new TH1F("HP","sieie ",10000,0,500);
  TH1F *HC = new TH1F("HC","sieie ",10000,0,510);
  TH1F *HN = new TH1F("HN","sieie ",10000,0,500);


  double totS = 0; 
  cout<<t_S->GetEntries()<<endl;
  for(int i = 0; i < t_S->GetEntries(); i++){
    t_S->GetEntry(i);

    if(Ppt < 25 )continue;
    totS = totS + weighT*weightXS;
    HS->Fill(Sie,weighT*weightXS);
    HH->Fill(ToE,weighT*weightXS);
    HP->Fill(IsoP-0.0059*Ppt,weighT*weightXS);
    HC->Fill(IsoC,weighT*weightXS);
    HN->Fill(IsoN-0.0118*Ppt,weighT*weightXS);
  }

  cout<<" total : "<<totS<<endl;

  double xcsf=0; 
  double xchf=0; 
  double xcpf=0; 
  double xccf=0; 
  double xcnf=0; 
  
  
  int p1 = 0;
  int p2 = 0;
  int p3 = 0;
  int p4 = 0;
  int p5 = 0;
    


  for(int i =0; i < 30000; i++){
   double xcs = i*1.0/30000; 
   double xch = i*40.0/30000; 
   double xcp = i*500.0/30000; 
   double xcc = i*510.0/30000; 
   double xcn = i*500.0/30000; 

   int bin = HS->FindBin(xcs);
   if(1.0*HS->Integral(0,bin)/totS > 0.999 && p1 == 0){
     p1 = 1;
     xcsf = xcs; 
 
   }

  bin = HH->FindBin(xch);
  if(1.0*HS->Integral(0,bin)/totS > 0.999 && p2 == 0){
    p2 =1;
    xchf = xch; 
   
  }
   bin = HP->FindBin(xcp);
   if(1.0*HP->Integral(0,bin)/totS > 0.999 && p3 == 0){
     p3 = 1; 
     xcpf = xcp; 
    
   }
  bin = HC->FindBin(xcc);
  if(1.0*HC->Integral(0,bin)/totS > 0.998 && p4 == 0){
     p4 = 1;
     xccf = xcc; 
  }
  bin = HN->FindBin(xcn);
  if(1.0*HN->Integral(0,bin)/totS > 0.999 && p5 == 0){
    p5 = 1;
    xcnf = xcn; 
  }
  }

  myfile<<xcsf<<endl;
  myfile<<xchf<<endl;
  myfile<<xccf<<endl;
  myfile<<xcnf<<endl;
  myfile<<xcpf<<endl;

  myfile.close();

  cout<<"Sie  :"<<xcsf<<endl;
  cout<<"HoE  :"<<xchf<<endl;
  cout<<"IsoP :"<<xcpf<<endl;
  cout<<"IsoC :"<<xccf<<endl;
  cout<<"IsoN :"<<xcnf<<endl;



}
