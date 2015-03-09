void Scr99(){


  TFile *f1 = new TFile("../../CutTMVATrees_Barrel.root");


  float ToE,Sie,IsoP,IsoC,IsoN,weighT,weightXS,Ppt; 

  ofstream myfile; 
  myfile.open("99per.txt");

  t_S->SetBranchAddress("Ppt",&Ppt);
  t_S->SetBranchAddress("ToE",&ToE);
  t_S->SetBranchAddress("Sieie",&Sie);
  t_S->SetBranchAddress("isoP",&IsoP);
  t_S->SetBranchAddress("isoC",&IsoC);
  t_S->SetBranchAddress("isoN",&IsoN);
  t_S->SetBranchAddress("weighT",&weighT);

  weightXS = 1;

  TH1F *HS = new TH1F("HS","sieie ",1500,0,0.15);
  TH1F *HH = new TH1F("HH","sieie ",10000,0,40);
  TH1F *HP = new TH1F("HP","sieie ",3000,0,500);
  TH1F *HC = new TH1F("HC","sieie ",3000,0,500);
  TH1F *HN = new TH1F("HN","sieie ",3000,0,500);



  double totS = 0; 
  for(int i = 0; i < t_S->GetEntries(); i++){
    t_S->GetEntry(i);
    totS = totS + weighT*weightXS;
    
    HS->Fill(Sie,weighT*weightXS);
    HH->Fill(ToE,weighT*weightXS);
    HP->Fill(IsoP - 0.0059*Ppt,weighT*weightXS);
    HC->Fill(IsoC,weighT*weightXS);
    HN->Fill(IsoN - 0.0118*Ppt,weighT*weightXS);
  }

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
    


  for(int i =0; i < 10000; i++){
   double xcs = i*0.15/10000; 
   double xch = i*40.0/10000; 
   double xcp = i*500.0/10000; 
   double xcc = i*500.0/10000; 
   double xcn = i*500.0/10000; 

   int bin = HS->FindBin(xcs);
   if(1.0*HS->Integral(0,bin)/totS > 0.999 && p1 == 0){
     p1 = 1;
     xcsf = xcs; 
 
   }

  bin = HH->FindBin(xch);
  if(1.0*HS->Integral(0,bin)/totS > 0.999 && p2 == 0){
    xchf = xch; 
    p2 =1;
  }
   bin = HP->FindBin(xcp);
   if(1.0*HP->Integral(0,bin)/totS > 0.999 && p3 == 0){
     xcpf = xcp; 
     p3 = 1; 
   }
  bin = HC->FindBin(xcc);
  if(1.0*HC->Integral(0,bin)/totS > 0.999 && p4 == 0){
    xccf = xcc; 
    p4 = 1; 
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
