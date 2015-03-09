#include <cstdlib>
#include <iostream> 
#include <map>
#include <string>
#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TMVA/GeneticAlgorithm.h"
#include "TMVA/GeneticFitter.h"
#include "TMVA/IFitterTarget.h"
#include "TMVA/Tools.h"
#include "TMVA/Factory.h"
#include <sstream>
#include <string.h>

void Calculator_ef(){

  ifstream tight; 
  ifstream medium; 
  ifstream loose; 
  ofstream outp; 

  tight.open("TightR.txt");
  medium.open("MediumR.txt");
  loose.open("LooseR.txt");
  outp.open("efBk.txt");

  double efL,efM,efT,bkL,bkM,bkT; 
  double IsoPcutL,IsoPcutM,IsoPcutT,IsoCcutL,IsoCcutM,IsoCcutT,IsoNcutL,IsoNcutM,IsoNcutT,SieiecutL,SieiecutM,SieiecutT,HoEcutL,HoEcutM,HoEcutT;

  if(tight.is_open()){
    while(!tight.eof()){
      
      tight>>SieiecutT>>HoEcutT>>IsoCcutT>>IsoNcutT>>IsoPcutT;
      break;
    }
  }
    
  if(medium.is_open()){
    while(!medium.eof()){
      
      medium>>SieiecutM>>HoEcutM>>IsoCcutM>>IsoNcutM>>IsoPcutM;
      break;

    }
  }


    
  if(loose.is_open()){
    while(!loose.eof()){
      
      loose>>SieiecutL>>HoEcutL>>IsoCcutL>>IsoNcutL>>IsoPcutL;
      break;

    }
  }

  /*
  //OLD ENDCAP CUTS 

  double OisCL = 2.3;
  double OisCM = 1.2; 
  double OisCT = 0.5; 
  
  double OisPL = 1000; 
  double OisPM =1.0; 
  double OisPT = 1.0; 

  double OisNL = 2.9; 
  double OisNM = 1.5; 
  double OisNT = 1.5; 


  double OtL = 0.05; 
  double OtM = 0.05; 
  double OtT = 0.05; 

  double OsL = 0.012; 
  double OsM = 0.011; 
  double OsT = 0.011; 
  */

  //Input file:
  TString fname = "../../../CutTMVATrees_Barrel.root";
  input = TFile::Open( fname );
  
  // --- Register the regression tree
  float Sie_ie,iso_P,iso_C,iso_N,to_e,weightXS,weighT;
  float Ppt; 
  int Pix;

  //Signal Tree
  t_S->SetBranchAddress("Sieie",&Sie_ie);
  t_S->SetBranchAddress("isoP",&iso_P);
  t_S->SetBranchAddress("isoC",&iso_C);
  t_S->SetBranchAddress("isoN",&iso_N);
  t_S->SetBranchAddress("ToE",&to_e);
  t_S->SetBranchAddress("weighT",&weighT);
  t_S->SetBranchAddress("Pix",&Pix);
  t_S->SetBranchAddress("Ppt",&Ppt);

  //Background Tree
  t_B->SetBranchAddress("Sieie",&Sie_ie);
  t_B->SetBranchAddress("isoP",&iso_P);
  t_B->SetBranchAddress("isoC",&iso_C);
  t_B->SetBranchAddress("isoN",&iso_N);
  t_B->SetBranchAddress("ToE",&to_e);  
 
  t_B->SetBranchAddress("weighT",&weighT);
  t_B->SetBranchAddress("Pix",&Pix);
  t_B->SetBranchAddress("Ppt",&Ppt);




  double LoosSEf = 0; 
  double TightSEf = 0; 
  double MediumSEf = 0; 

  
  double LoosBckR = 0; 
  double TightBckR = 0; 
  double MediumBckR = 0; 

  double slopeP = 0.0010; 
  double slopeN = 0.0025; 
  
  double totS = 0; 
  for(int i  = 0 ; i < t_S->GetEntries(); i++){
    t_S->GetEntry(i);
    if(Pix == 1)continue;
    if(Ppt < 30 ) continue;

    totS = totS+ weighT; 


    //Calculating the Efficiencies for the Loose Set of Cuts 
    if((iso_P < IsoPcutL + slopeP*Ppt)&&(iso_N < IsoNcutL  + slopeN*Ppt)&&(iso_C < IsoCcutL)&&(to_e<HoEcutL)&&(Sie_ie < SieiecutL )&&(Pix==0)){
      LoosSEf = LoosSEf + weighT;
    }
    
    if((iso_P < IsoPcutM +slopeP*Ppt)&&(iso_N < IsoNcutM +Ppt*slopeN)&&(iso_C < IsoCcutM)&&(to_e<HoEcutM)&&(Sie_ie < SieiecutM )&&(Pix == 0)){
       MediumSEf = MediumSEf + weighT;
    }
    
       if((iso_P < IsoPcutT +slopeP*Ppt)&&(iso_N < IsoNcutT + slopeN*Ppt)&&(iso_C < IsoCcutT)&&(to_e<HoEcutT)&&(Sie_ie < SieiecutT ) &&(Pix==0)){
        TightSEf = TightSEf + weighT;
    }
    
  }

  double totB = 0; 
  for(int i  = 0 ; i < t_B->GetEntries(); i++){
    t_B->GetEntry(i);
    if(Pix == 1)continue;
    if(Ppt < 30 ) continue;

    totB = totB+ weighT; 
   

    
    if((iso_P < IsoPcutL +Ppt*slopeP )&&(iso_N < IsoNcutL + slopeN*Ppt)&&(iso_C < IsoCcutL)&&(to_e<HoEcutL)&&(Sie_ie < SieiecutL )&&(Pix==0)){
      LoosBckR = LoosBckR + weighT;
    }
    
       if((iso_P < IsoPcutM +slopeP*Ppt)&&(iso_N < IsoNcutM +slopeN*Ppt)&&(iso_C < IsoCcutM)&&(to_e<HoEcutM)&&(Sie_ie < SieiecutM )&&(Pix==0)){
	 MediumBckR = MediumBckR + weighT;
    }
    
       if((iso_P < IsoPcutT +  Ppt*slopeP)&&(iso_N < IsoNcutT + slopeN*Ppt)&&(iso_C < IsoCcutT)&&(to_e<HoEcutT)&&(Sie_ie < SieiecutT )&&(Pix == 0)){
        TightBckR = TightBckR + weighT;
    }


  }// Eoff Back ground tree for Sig Back 


  


  outp<<LoosSEf/totS<<" "<<1 - LoosBckR/totB<<" "<<MediumSEf/totS<<" "<<1 - MediumBckR/totB<<" "<<TightSEf/totS<<" "<<1 - TightBckR/totB;



}
