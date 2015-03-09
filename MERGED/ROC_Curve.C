void ROC_Curve(){
  TFile *f0=new TFile("CutTMVATrees_Barrel.root");
  TTree *s = f0->Get("t_S");
  TTree *b = f0->Get("t_B");
  c1=new TCanvas();
  int nROCBins=1000;
  s->Draw("Sieie>>signal(1000,0,0.02)");
  b->Draw("Sieie>>bkg(1000,0,0.02)");

  double CutV[1001];
  double CutVX[1001];
 
  double sigEff[1001];
  double bkgRej[1001];
  char ss[1024];
  for (unsigned int ibin= 1; ibin<1001 ; ibin++){
    float densig=signal->Integral();
    float denbkg=bkg->Integral();
    float sig=signal->Integral(0,ibin);
    float bk=bkg->Integral(0,ibin);
    float eff =(densig>0)?(sig/densig):0;
    float rej=(denbkg>0)?(1-(bk/denbkg)):0;
    sigEff[ibin-1]=eff;
    bkgRej[ibin-1]=rej;
    cout<<"CUT VALUE :"<<ibin*0.02/1000.0 <<"sigEff "<<eff<<" rejection "<<rej<<endl;
    CutV[ ibin - 1 ]  = ibin*0.02/1000.0; 
    CutVX[ibin - 1 ]  = rej;
   
  }
 
  
  TCanvas *c12 =new TCanvas("c12"," ROC PF Isolation ",10,430,900,700);	
  c12->SetGrid();
  TGraph *ROC_Curve1 = new TGraph(1000,bkgRej,sigEff);
  TGraph *ROC_Curve2 = new TGraph(1000,CutVX,CutV);
  TGraph *ROC_Curve3 = new TGraph(1000,sigEff,CutV);
  
  ROC_Curve1->SetMarkerStyle(24);
  ROC_Curve1->GetXaxis()->SetTitle("Bkg Rejection");
  ROC_Curve1->GetYaxis()->SetTitle("Sig Efficiency");
  ROC_Curve1->Draw("ACP");
  c12->Update();

  TCanvas *c13 =new TCanvas("c13"," ROC PF Isolation ",10,430,900,700);	
  c13->SetGrid();
  ROC_Curve2->SetTitle("Cut Value scan vs Bck Rejection");
  ROC_Curve2->SetMarkerStyle(24);
  ROC_Curve2->GetXaxis()->SetTitle("Bkg Rejection");
  ROC_Curve2->GetYaxis()->SetTitle("CutValue");
  ROC_Curve2->GetYaxis()->SetRangeUser(0.0096,0.01);
  ROC_Curve2->GetXaxis()->SetRangeUser(0.5,0.6);
  
 ROC_Curve2->Draw("ACP");
  c13->Update();


  
  TCanvas *c14 =new TCanvas("c14"," ROC PF Isolation ",10,430,900,700);	
  c14->SetGrid();
  ROC_Curve3->SetMarkerStyle(24);
  ROC_Curve3->SetTitle("Cut Value scan vs Signal Eff.");
  ROC_Curve3->GetXaxis()->SetTitle("signale eff");
  ROC_Curve3->GetYaxis()->SetTitle("CutValue");
  ROC_Curve3->GetYaxis()->SetRangeUser(0.0096,0.01);
  ROC_Curve3->GetXaxis()->SetRangeUser(0.9,1);
 
  //  ROC_Curve3->GetYaxis()->SetTitle("CutValue");
  //  ROC_Curve3->GetYaxis()->SetTitle("CutValue");

  ROC_Curve3->Draw("ACP");
  c14->Update();


  


  
}
