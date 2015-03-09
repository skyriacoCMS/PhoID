#include <Fitter.C>
#include <stdlib>
#include <TSystem.h>
#include <TableWriter.C>

void run_TreeMakerONLY(){
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


  Fin[0][0] = 0.0130;
  Fin[0][1] = 0.0056;
  Fin[0][2] = 0.0896;
 

  Fin[1][0] = 0.0096;
  Fin[1][1] = 0.0107;
  Fin[1][2] = 0.0762;

  Fin[2][0] = 0.0107;
  Fin[2][1] = 0.0019;
  Fin[2][2] = 0.0383;

  Fin[3][0] = 0.0077;
  Fin[3][1] = 0.0011;
  Fin[3][2] = 0.0534;

  Fin[4][0] = 0.0088;
  Fin[4][1] = 0.0076;
  Fin[4][2] = 0.0846;

  Fin[5][0] = 0.0065;
  Fin[5][1] = 0.0178;
  Fin[5][2] = 0.1032;

  Fin[6][0] = 0.0030;
  Fin[6][1] = 0.1675;
  Fin[6][2] = 0.1598;

  t.CutBasedID(1,Fin);
  t.CutBasedID(2,Fin);
  
  



}
