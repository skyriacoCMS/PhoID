#include <FitterAL.C>
#include <stdlib>
#include <TSystem.h>
#include <TableWriterAL.C>

void run_ALEFF(){
  //-----------------Macro Describtion----------------------------------------------------------
  //
  // This macro wraps the whole procedure in a single shell. 
  // Initialy it caluclates the effective areas -macros (AreaCalc.C + Fitter.C) 
  // and then feed them in a Tree Maker, that makes a Tree with the variables of interest 
  // separated to background/signal and weight based on the pt, for possible MVA techinques 
  // and to derive the cuts. 
  // This file to run, needs the full construction of the CUTID class and also the extra macros
  // for each of the specified process. 
  //
  //--------------------------------------------------------------------------------------------

  gSystem->CompileMacro("CutID.C");
  
  CutID t; 
  
  // here you declare the number of eta  bins 
  double Fin[7][3]= {0};
  double isoP,isoN,isoC;

  cout<<"------------------------------------------------------------"<<endl;
  cout<<"Creating the bins and retrieving the effective area for each"<<endl;
  cout<<"-----------------------------------------------------------"<<endl;
  t.ArCalc(0,1,1);
  FitterAL(0,1,1,isoP,isoC,isoN);
 
  Fin[0][0] = isoC;
  Fin[0][1] = isoN;
  Fin[0][2] = isoP;
 
  double emin =1; 
  double emax =1.479;
  
  t.ArCalc(emin,emax,2);  
  FitterAL(emin,emax,2,isoP,isoC,isoN);
  
  Fin[1][0] = isoC;
  Fin[1][1] = isoN;
  Fin[1][2] = isoP;
  

 
  emin = 1.479;
  emax = 2.0;

  t.ArCalc(emin,emax,3);
  FitterAL(emin,emax,3,isoP,isoC,isoN);
  Fin[2][0] = isoC;
  Fin[2][1] = isoN;
  Fin[2][2] = isoP;
  

  emin = 2.0;
  emax = 2.2;
  t.ArCalc(emin,emax,4);
  FitterAL(emin,emax,4,isoP,isoC,isoN);
  Fin[3][0] = isoC;
  Fin[3][1] = isoN;
  Fin[3][2] = isoP;
  


  emin = 2.2;
  emax = 2.3;
  t.ArCalc(emin,emax,5);
  FitterAL(emin,emax,5,isoP,isoC,isoN);
  Fin[4][0] = isoC;
  Fin[4][1] = isoN;
  Fin[4][2] = isoP;
  


  emin = 2.3;
  emax = 2.4;
  t.ArCalc(emin,emax,6);
  FitterAL(emin,emax,6,isoP,isoC,isoN);
  Fin[5][0] = isoC;
  Fin[5][1] = isoN;
  Fin[5][2] = isoP;

  emin = 2.4;
  emax = 5;
  t.ArCalc(emin,emax,7);
  FitterAL(emin,emax,7,isoP,isoC,isoN);
  
  Fin[6][0] = isoC;
  Fin[6][1] = isoN;
  Fin[6][2] = isoP;



  for(int j  = 0; j < 4; j++)cout<<endl;
  cout<<"Derived the Effective areas --- "<<endl;
  for(int j  = 0; j < 4; j++)cout<<endl;

  TableWriterAL(Fin);
  cout<<"WRITTING THE EFFECTIVE AREAS"<<endl;
  for(int j  = 0; j < 4; j++)cout<<endl;

  cout<<"----------------------------------------------------"<<endl;
  cout<<"Creating the Trees for the Cut Optimization"<<endl;
  for(int j  = 0; j < 4; j++)cout<<endl;

  
  cout<<"----------------------------------------------------"<<endl;
  /*
  cout<<"----------------------Barrel--------------"<<endl;
  t.CutBasedID(1,Fin);
  cout<<"----------------------End Cap--------------"<<endl;
  t.CutBasedID(2,Fin);
  */
  



}
