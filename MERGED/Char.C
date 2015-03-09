void Char(){


  TFile *f1 = new TFile("phys14.root");
  

  gROOT->ProcessLine(" .L tdrstyle.C");
  setTDRStyle();
  gStyle->SetOptStat(0);
 

  TCanvas *c1 = new TCanvas("c1","Char",700,700);
  c1->cd();
  
  
  t1->Draw("gedPhPt>>hpf","gedPhisPrompt == 0 && gedPhPt > 15 && gedPhPt < 200","");
  hpf->SetLineColor(kBlue);

  hpf->Draw();
  hpf->GetXaxis()->SetTitle("Pt GeVc^{-1}");


  t1->Draw("gedPhPt>>hpt","gedPhisPrompt == 1 && gedPhPt > 15 && gedPhPt < 200","same");
  hpt->SetLineColor(kRed);

  
  hpt->Draw("same");


  c1->SaveAs("Pt.png");

  c1->Close();
  
  TCanvas *c2 = new TCanvas("c2","Char",700,700);
  c2->cd();
  
  
  t1->Draw("gedPhEta>>hef","gedPhisPrompt == 1 && gedPhPt > 15 && gedPhPt < 200","");
  hef->SetLineColor(kRed);
  hef->Draw();

  hef->GetXaxis()->SetTitle("#eta");

  t1->Draw("gedPhEta>>het","gedPhisPrompt == 0 && gedPhPt > 15 && gedPhPt < 200","same");
  het->SetLineColor(kBlue);

  het->Draw("same");


  c2->SaveAs("Eta.png");


  c2->Close();



  TCanvas *c3 = new TCanvas("c3","Char",700,700);
  c3->cd();
  
  
  t1->Draw("gedPhPhi>>hhf","gedPhisPrompt == 1 && gedPhPt > 15 && gedPhPt < 200","");
  hhf->SetLineColor(kRed);
  hhf->Draw();
  hhf->GetXaxis()->SetTitle("#phi");

  t1->Draw("gedPhPhi>>hht","gedPhisPrompt == 0 && gedPhPt > 15 && gedPhPt < 200","same");
  hht->SetLineColor(kBlue);

  hht->Draw("same");


  c3->SaveAs("Phi.png");



}
