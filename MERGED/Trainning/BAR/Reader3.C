#include <cstdlib>
#include <vector>
#include <iostream>
#include <map>
#include <string>
#include "TH2.h"
#include "TRandom.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TStopwatch.h"
#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TMVA/Tools.h"
#include "TMVA/Factory.h"
#include "TFile.h"
#include "TTree.h"
#include "TH2D.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TStopwatch.h"
#include "TMVA/Tools.h"
#include "TMVA/Reader.h"

using namespace TMVA;

void Reader3(){
  
  TMVA::Tools::Instance();  

  ofstream myfileT; 
  
  myfileT.open("TightR.txt");
  
  /*
  ofstream myfileM; 
  myfileM.open("MediumR.txt");
  */
 
  /*
  ofstream myfileL; 
  myfileL.open("LooseR.txt");
  */



  //Declaring the reader  
  TString methodName = "Cuts_Tight_r";
  TString weightfile = "./weights/TMVAClassification_Cut_Tight_r.weights.xml";

  
  

  
  TMVA::Reader *reader = new TMVA::Reader( "!Color" );
   
  float Sieie,ToE,isoC,isoN,isoP,pt;
  reader->AddVariable("Sieie",&Sieie);
  reader->AddVariable("ToE",&ToE);
  reader->AddVariable( "isoC",&isoC );
  reader->AddVariable( "isoN-0.0025*Ppt",&isoN );
  reader->AddVariable( "isoP-0.0010*Ppt",&isoP );

  

  reader->AddSpectator("Ppt",&pt);
  reader->BookMVA(methodName,weightfile); 


  TMVA::MethodCuts* mcuts = dynamic_cast<TMVA::MethodCuts*>(reader->FindCutsMVA(methodName) );
  std::vector<Double_t> cutsMin;
  std::vector<Double_t> cutsMax;
  /*
  double SEF =  0.90;   
  if(mcuts)mcuts->GetCuts(SEF, cutsMin, cutsMax ); 
  myfileL<<" "<<cutsMax[0]<<" "<<cutsMax[1]<<" "<<cutsMax[2]<<" "<<cutsMax[3]<<" "<<cutsMax[4]<<" "<<endl;  
  */

  /*  
  double SEF =  0.80;   
  if(mcuts)mcuts->GetCuts(SEF, cutsMin, cutsMax ); 
  myfileM<<" "<<cutsMax[0]<<" "<<cutsMax[1]<<" "<<cutsMax[2]<<" "<<cutsMax[3]<<" "<<cutsMax[4]<<" "<<endl;  
  */


  
  double SEF =  0.75;   
  if(mcuts)mcuts->GetCuts(SEF, cutsMin, cutsMax ); 
  myfileT<<" "<<cutsMax[0]<<" "<<cutsMax[1]<<" "<<cutsMax[2]<<" "<<cutsMax[3]<<" "<<cutsMax[4]<<" "<<endl;  
  
  

  delete reader;
  //  myfileL.close(); 
  //myfileM.close(); 
  myfileT.close(); 
  cout<<"DONE READING CUTS"<<endl;
  
}

