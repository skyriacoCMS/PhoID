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

//#include "TMVARegGui.C"
#include "TMVA/Tools.h"
#include "TMVA/Factory.h"

using namespace TMVA;


void Reg(){
  
  TMVA::Tools::Instance();
  std::cout << "==> Start TMVARegression" << std::endl;
    
  ifstream myfile; 
  myfile.open("99per.txt");


  ostringstream xcS,xcH,xcP,xcC,xcN;  
  double xS,xH,xC,xN,xP;

  if(myfile.is_open()){
    while(!myfile.eof()){
      myfile>>xS>>xH>>xC>>xN>>xP;
    }
  }

  xcS<<xS;
  xcH<<xH;
  xcC<<xC;
  xcN<<xN;
  xcP<<xP;

  //Output file 
  TString outfileName( "Loose_w_scaled.root" );
  TFile* outputFile = TFile::Open( outfileName, "RECREATE" );
  
  //Declaring the factory
  TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification", outputFile, 
					      "!V:!Silent:Color:DrawProgressBar" );
  //Declaring Input Variables 
  factory->AddVariable( "Sieie",'F');
  factory->AddVariable( "ToE", 'F' );
  factory->AddVariable( "isoC",'F' );
  factory->AddVariable( "isoN-0.0025*Ppt",'F' );
  factory->AddVariable( "isoP-0.0010*Ppt",'F' );
  factory->AddSpectator( "Ppt",'F' );
  
  TString fname = "../../CutTMVATrees_Barrel.root";
  input = TFile::Open( fname );
  
  // --- Register the regression tree
  TTree *signal = (TTree*)input->Get("t_S");
  TTree *background = (TTree*)input->Get("t_B");
  
  //Just Some more settings
   Double_t signalWeight      = 1.0; 
   Double_t backgroundWeight  = 1.0; 

   // You can add an arbitrary number of regression trees
   factory->AddSignalTree( signal, signalWeight );
   factory->AddBackgroundTree( background , backgroundWeight );
 
   TCut mycuts ="Ppt>15 && Pix == 0";
   TCut mycutb ="Ppt>15 && Pix == 0";
   factory->PrepareTrainingAndTestTree(mycuts,mycutb,"");

   //"nTrain_Signal=9000:nTrain_Background=9000:nTest_Signal=10000:nTest_Background=10000");

   factory->SetBackgroundWeightExpression("weighT");
   factory->SetSignalWeightExpression("weighT");

   TString methodName = "Cut_Loose_r";
   TString methodOptions ="!H:!V:FitMethod=GA:EffMethod=EffSEl"; 
   methodOptions +=":VarProp[0]=FMin:VarProp[1]=FMin:VarProp[2]=FMin:VarProp[3]=FMin:VarProp[4]=FMin";
  
   methodOptions +=":CutRangeMax[0]="+xcS.str(); 
   methodOptions +=":CutRangeMax[1]="+xcH.str();
   methodOptions +=":CutRangeMax[2]="+xcC.str();
   methodOptions +=":CutRangeMax[3]="+xcN.str();
   methodOptions +=":CutRangeMax[4]="+xcP.str();

   //************
   factory->BookMethod(TMVA::Types::kCuts,methodName,methodOptions);
   factory->TrainAllMethods();
   factory->TestAllMethods();
   factory->EvaluateAllMethods();    
   
   // --------------------------------------------------------------
   // Save the output
   outputFile->Close();



   std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
   std::cout << "==> TMVARegression is done!" << std::endl;      
   delete factory;

}
