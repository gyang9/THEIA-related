
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

#include "TMVA/Factory.h"
#include "TMVA/DataLoader.h"
#include "TMVA/Tools.h"
#include "TMVA/TMVAGui.h"

int TMVAClassification_theia( TString myMethodList = "" )
{
   // The explicit loading of the shared libTMVA is done in TMVAlogon.C, defined in .rootrc
   // if you use your private .rootrc, or run from a different directory, please copy the
   // corresponding lines from .rootrc

   // Methods to be processed can be given as an argument; use format:
   //
   //     mylinux~> root -l TMVAClassification.C\(\"myMethod1,myMethod2,myMethod3\"\)

   //---------------------------------------------------------------
   // This loads the library
   TMVA::Tools::Instance();

   // Default MVA methods to be trained + tested
   std::map<std::string,int> Use;

   // Cut optimisation
   Use["Cuts"]            = 1;
   Use["CutsD"]           = 1;
   Use["CutsPCA"]         = 0;
   Use["CutsGA"]          = 0;
   Use["CutsSA"]          = 0;
   //
   // 1-dimensional likelihood ("naive Bayes estimator")
   Use["Likelihood"]      = 1;
   Use["LikelihoodD"]     = 0; // the "D" extension indicates decorrelated input variables (see option strings)
   Use["LikelihoodPCA"]   = 1; // the "PCA" extension indicates PCA-transformed input variables (see option strings)
   Use["LikelihoodKDE"]   = 0;
   Use["LikelihoodMIX"]   = 0;
   //
   // Mutidimensional likelihood and Nearest-Neighbour methods
   Use["PDERS"]           = 1;
   Use["PDERSD"]          = 0;
   Use["PDERSPCA"]        = 0;
   Use["PDEFoam"]         = 1;
   Use["PDEFoamBoost"]    = 0; // uses generalised MVA method boosting
   Use["KNN"]             = 1; // k-nearest neighbour method
   //
   // Linear Discriminant Analysis
   Use["LD"]              = 1; // Linear Discriminant identical to Fisher
   Use["Fisher"]          = 0;
   Use["FisherG"]         = 0;
   Use["BoostedFisher"]   = 0; // uses generalised MVA method boosting
   Use["HMatrix"]         = 0;
   //
   // Function Discriminant analysis
   Use["FDA_GA"]          = 1; // minimisation of user-defined function using Genetics Algorithm
   Use["FDA_SA"]          = 0;
   Use["FDA_MC"]          = 0;
   Use["FDA_MT"]          = 0;
   Use["FDA_GAMT"]        = 0;
   Use["FDA_MCMT"]        = 0;
   //
   // Neural Networks (all are feed-forward Multilayer Perceptrons)
   Use["MLP"]             = 0; // Recommended ANN
   Use["MLPBFGS"]         = 0; // Recommended ANN with optional training method
   Use["MLPBNN"]          = 1; // Recommended ANN with BFGS training method and bayesian regulator
   Use["CFMlpANN"]        = 0; // Depreciated ANN from ALEPH
   Use["TMlpANN"]         = 0; // ROOT's own ANN
   Use["DNN_GPU"]         = 0; // CUDA-accelerated DNN training.
   Use["DNN_CPU"]         = 0; // Multi-core accelerated DNN.
   //
   // Support Vector Machine
   Use["SVM"]             = 1;
   //
   // Boosted Decision Trees
   Use["BDT"]             = 1; // uses Adaptive Boost
   Use["BDTG"]            = 0; // uses Gradient Boost
   Use["BDTB"]            = 0; // uses Bagging
   Use["BDTD"]            = 0; // decorrelation + Adaptive Boost
   Use["BDTF"]            = 0; // allow usage of fisher discriminant for node splitting
   //
   // Friedman's RuleFit method, ie, an optimised series of cuts ("rules")
   Use["RuleFit"]         = 1;
   // ---------------------------------------------------------------

   std::cout << std::endl;
   std::cout << "==> Start TMVAClassification" << std::endl;

   // Select methods (don't look at this code - not of interest)
   if (myMethodList != "") {
      for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) it->second = 0;

      std::vector<TString> mlist = TMVA::gTools().SplitString( myMethodList, ',' );
      for (UInt_t i=0; i<mlist.size(); i++) {
         std::string regMethod(mlist[i]);

         if (Use.find(regMethod) == Use.end()) {
            std::cout << "Method \"" << regMethod << "\" not known in TMVA under this name. Choose among the following:" << std::endl;
            for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) std::cout << it->first << " ";
            std::cout << std::endl;
            return 1;
         }
         Use[regMethod] = 1;
      }
   }

   // --------------------------------------------------------------------------------------------------

   // Here the preparation phase begins

   cout<<atoi(gApplication->Argv(4))<<" "<<atoi(gApplication->Argv(5))<<endl;
   // Read training and test data
   // (it is also possible to use ASCII format as input -> see TMVA Users Guide)
   TFile *input(0);
   TFile *input2(0);
   TFile *inputTest(0);
   TFile *inputTest2(0);
   //TString fname = "./tmva_class_example.root";
   //TString fname = Form("/home/gyang/work/t2k/wc/combined_fluxWeightAdded_%dring%ddecay_hE.root",atoi(gApplication->Argv(5)),atoi(gApplication->Argv(6)));
   //TString fname2 = Form("/home/gyang/work/t2k/wc/combined_fluxWeightAdded_%dring%ddecay_bkg_hE.root",atoi(gApplication->Argv(5)),atoi(gApplication->Argv(6)));
   //TString fnameTest = "/home/gyang/work/t2k/wc/combined_sbu_processed_sig.root";
   //TString fnameTest2 = "/home/gyang/work/t2k/wc/combined_sbu_processed_bkg.root";

   TString fname  = "/home/gyang/work/t2k/wc/outputTest.root";
   TString fname2 = "/home/gyang/work/t2k/wc/outputTest.root";

   if (!gSystem->AccessPathName( fname )) {
      input = TFile::Open( fname ); // check if file in local directory exists
      //inputTest = TFile::Open( fnameTest );
   }
   else {
      TFile::SetCacheFileDir(".");
      //input = TFile::Open("http://root.cern.ch/files/tmva_class_example.root", "CACHEREAD");
   }
   if (!input) {
      std::cout << "ERROR: could not open data file" << std::endl;
      exit(1);
   }
   std::cout << "--- TMVAClassification       : Using input file: " << input->GetName() << std::endl;

   if (!gSystem->AccessPathName( fname2 )) {
      input2 = TFile::Open( fname2 ); // check if file in local directory exists
      //inputTest2 = TFile::Open( fnameTest2 );
   }
   else {
      TFile::SetCacheFileDir(".");
      //input2 = TFile::Open("http://root.cern.ch/files/tmva_class_example.root", "CACHEREAD");
   }
   if (!input2) {
      std::cout << "ERROR: could not open data file" << std::endl;
      exit(1);
   }
   std::cout << "--- TMVAClassification       : Using input file 2: " << input2->GetName() << std::endl;

   // Register the training and test trees

   TTree *signalTree     = (TTree*)input->Get("h1");
   TTree *background     = (TTree*)input->Get("h1");

   //TTree *signalTreeTest     = (TTree*)inputTest->Get("h1");
   //TTree *backgroundTest     = (TTree*)inputTest2->Get("h1");

   // Create a ROOT output file where TMVA will store ntuples, histograms, etc.
   TString outfileName( "TMVA_gy.root" );
   TFile* outputFile = TFile::Open( outfileName, "RECREATE" );

   // Create the factory object. Later you can choose the methods
   // whose performance you'd like to investigate. The factory is
   // the only TMVA object you have to interact with
   //
   // The first argument is the base of the name of all the
   // weightfiles in the directory weight/
   //
   // The second argument is the output file for the training results
   // All TMVA output can be suppressed by removing the "!" (not) in
   // front of the "Silent" argument in the option string
   //TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification", outputFile,
   //                                            "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );
   TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification", outputFile,
                                               "!V:!Silent:Color:DrawProgressBar:Transformations=D:AnalysisType=Classification" );

   TMVA::DataLoader *dataloader=new TMVA::DataLoader("dataset");
   // If you wish to modify default settings
   // (please check "src/Config.h" to see all available global options)
   //
   //    (TMVA::gConfig().GetVariablePlotting()).fTimesRMS = 8.0;
   //    (TMVA::gConfig().GetIONames()).fWeightFileDir = "myWeightDirectory";

   // Define the input variables that shall be used for the MVA training
   // note that you may also use variable expressions, such as: "3*var1/var2*abs(var3)"
   // [all types of expressions that can also be parsed by TTree::Draw( "expression" )]

   dataloader->AddVariable( "var1:=fqpi0mom1[0]", "fqpi0mom1[0]", "units",  'F' );
   dataloader->AddVariable( "var2:=fqpi0mom2[0]", "fqpi0mom2[0]", "units", 'F' );
   dataloader->AddVariable( "var3:=fq1rnll[0][1]-fqpi0nll[0]", "fq1rnll[0][1]-fqpi0nll[0]", "units", 'F' );
   dataloader->AddVariable( "var4:=fqpi0mass[0]", "qpi0mass", "units", 'F' );
   dataloader->AddVariable( "var5:=fqpi0photangle[0]", "fqpi0photangle[0]", "units", 'F' );

   dataloader->AddVariable( "var6:=erecmr", "erecmr", "units", 'F' );
   dataloader->AddVariable( "var7:=fq1rmom[0][1]", "fq1rmom[0][1]", "units", 'F' );
   dataloader->AddVariable( "var8:=fq1rmom[0][2]", "fq1rmom[0][2]", "units", 'F' );
   dataloader->AddVariable( "var9:=fq1rmom[0][3]", "fq1rmom[0][3]", "units", 'F' );
   dataloader->AddVariable( "var10:=fqwall", "fqwall", "units", 'F' );
   dataloader->AddVariable( "var11:=fq1rnll[0][1]-fq1rnll[0][2]", "fq1rnll[0][1]-fq1rnll[0][2]", "units", 'F' );
   dataloader->AddVariable( "var12:=fq1rnll[0][2]-fq1rnll[0][3]", "fq1rnll[0][2]-fq1rnll[0][3]", "units", 'F' );
   dataloader->AddVariable( "var13:=fq1reloss[0][3]", "fq1reloss[0][3]", "units", 'F' );
   dataloader->AddVariable( "var14:=eTOpre", "eTOpre", "units", 'F' );
   dataloader->AddVariable( "var15:=towall", "towall", "units", 'F' );

   dataloader->AddVariable( "var16:=momee[0]", "momee[0]", "units", 'F' );
   dataloader->AddVariable( "var17:=momee[1]", "momee[1]", "units", 'F' );
   dataloader->AddVariable( "var18:=momepi[0]", "momepi[0]", "units", 'F' );
   dataloader->AddVariable( "var19:=momepi[1]", "momepi[1]", "units", 'F' );
   dataloader->AddVariable( "var20:=mompp[0]", "mompp[0]", "units", 'F' );
   dataloader->AddVariable( "var21:=mompp[1]", "mompp[1]", "units", 'F' );
   dataloader->AddVariable( "var22:=mompie[0]", "mompie[0]", "units", 'F' );
   dataloader->AddVariable( "var23:=mompie[1]", "mompie[1]", "units", 'F' );
   dataloader->AddVariable( "var24:=angleepi", "angleepi", "units", 'F' );
   dataloader->AddVariable( "var25:=anglepie", "anglepie", "units", 'F' );
   dataloader->AddVariable( "var26:=angleee", "angleee", "units", 'F' );
   dataloader->AddVariable( "var27:=anglepp", "anglepp", "units", 'F' );
   dataloader->AddVariable( "var28:=fq1rE-fq2rEE", "fq1rE-fq2rEE", "units", 'F' );
   dataloader->AddVariable( "var29:=fq1rE-fq2rEP", "fq1rE-fq2rEP", "units", 'F' );
   dataloader->AddVariable( "var30:=fq1rE-fq2rPE", "fq1rE-fq2rPE", "units", 'F' );
   dataloader->AddVariable( "var31:=fq1rE-fq2rPP", "fq1rE-fq2rPP", "units", 'F' );

   dataloader->AddVariable( "var32:=momeee[0]", "momeee[0]", "units", 'F' );
   dataloader->AddVariable( "var33:=momeee[1]", "momeee[1]", "units", 'F' );
   dataloader->AddVariable( "var34:=momeee[2]", "momeee[2]", "units", 'F' );
   dataloader->AddVariable( "var35:=momppp[0]", "momppp[0]", "units", 'F' );
   dataloader->AddVariable( "var36:=momppp[1]", "momppp[1]", "units", 'F' );
   dataloader->AddVariable( "var37:=momppp[2]", "momppp[2]", "units", 'F' );
   dataloader->AddVariable( "var38:=momeep[0]", "momeep[0]", "units", 'F' );
   dataloader->AddVariable( "var39:=momeep[1]", "momeep[1]", "units", 'F' );
   dataloader->AddVariable( "var40:=momeep[2]", "momeep[2]", "units", 'F' );
   dataloader->AddVariable( "var41:=momepe[0]", "momepe[0]", "units", 'F' );
   dataloader->AddVariable( "var42:=momepe[1]", "momepe[1]", "units", 'F' );
   dataloader->AddVariable( "var43:=momepe[2]", "momepe[2]", "units", 'F' );
   dataloader->AddVariable( "var44:=mompee[0]", "mompee[0]", "units", 'F' );
   dataloader->AddVariable( "var45:=mompee[1]", "mompee[1]", "units", 'F' );
   dataloader->AddVariable( "var46:=mompee[2]", "mompee[2]", "units", 'F' );
   dataloader->AddVariable( "var47:=momppe[0]", "momppe[0]", "units", 'F' );
   dataloader->AddVariable( "var48:=momppe[1]", "momppe[1]", "units", 'F' );
   dataloader->AddVariable( "var49:=momppe[2]", "momppe[2]", "units", 'F' );
   dataloader->AddVariable( "var50:=mompep[0]", "mompep[0]", "units", 'F' );
   dataloader->AddVariable( "var51:=mompep[1]", "mompep[1]", "units", 'F' );
   dataloader->AddVariable( "var52:=mompep[2]", "mompep[2]", "units", 'F' );
   dataloader->AddVariable( "var53:=momepp[0]", "momepp[0]", "units", 'F' );
   dataloader->AddVariable( "var54:=momepp[1]", "momepp[1]", "units", 'F' );
   dataloader->AddVariable( "var55:=momepp[2]", "momepp[2]", "units", 'F' );

   dataloader->AddVariable( "var56:=angleeee[0]", "angleeee[0]", "units", 'F' );
   dataloader->AddVariable( "var57:=angleeee[1]", "angleeee[1]", "units", 'F' );
   dataloader->AddVariable( "var58:=angleeee[2]", "angleeee[2]", "units", 'F' );
   dataloader->AddVariable( "var59:=angleppp[0]", "angleppp[0]", "units", 'F' );
   dataloader->AddVariable( "var60:=angleppp[1]", "angleppp[1]", "units", 'F' );
   dataloader->AddVariable( "var61:=angleppp[2]", "angleppp[2]", "units", 'F' );
   dataloader->AddVariable( "var62:=angleeep[0]", "angleeep[0]", "units", 'F' );
   dataloader->AddVariable( "var63:=angleeep[1]", "angleeep[1]", "units", 'F' );
   dataloader->AddVariable( "var64:=angleeep[2]", "angleeep[2]", "units", 'F' );
   dataloader->AddVariable( "var65:=angleepe[0]", "angleepe[0]", "units", 'F' );
   dataloader->AddVariable( "var66:=angleepe[1]", "angleepe[1]", "units", 'F' );
   dataloader->AddVariable( "var67:=angleepe[2]", "angleepe[2]", "units", 'F' );
   dataloader->AddVariable( "var68:=anglepee[0]", "anglepee[0]", "units", 'F' );
   dataloader->AddVariable( "var69:=anglepee[1]", "anglepee[1]", "units", 'F' );
   dataloader->AddVariable( "var70:=anglepee[2]", "anglepee[2]", "units", 'F' );
   dataloader->AddVariable( "var71:=angleppe[0]", "angleppe[0]", "units", 'F' );
   dataloader->AddVariable( "var72:=angleppe[1]", "angleppe[1]", "units", 'F' );
   dataloader->AddVariable( "var73:=angleppe[2]", "angleppe[2]", "units", 'F' );
   dataloader->AddVariable( "var74:=anglepep[0]", "anglepep[0]", "units", 'F' );
   dataloader->AddVariable( "var75:=anglepep[1]", "anglepep[1]", "units", 'F' );
   dataloader->AddVariable( "var76:=anglepep[2]", "anglepep[2]", "units", 'F' );
   dataloader->AddVariable( "var77:=angleepp[0]", "angleepp[0]", "units", 'F' );
   dataloader->AddVariable( "var78:=angleepp[1]", "angleepp[1]", "units", 'F' );
   dataloader->AddVariable( "var79:=angleepp[2]", "angleepp[2]", "units", 'F' );

   dataloader->AddVariable( "var80:=fq3rEEE-fq2rEE", "fq3rEEE-fq2rEE", "units", 'F' );
   dataloader->AddVariable( "var81:=fq3rPPP-fq2rPP", "fq3rPPP-fq2rPP", "units", 'F' );
   dataloader->AddVariable( "var82:=fq3rEEP-fq2rEE", "fq3rEEP-fq2rEE", "units", 'F' );
   dataloader->AddVariable( "var83:=fq3rEPE-fq2rEP", "fq3rEPE-fq2rEP", "units", 'F' );
   dataloader->AddVariable( "var84:=fq3rPEE-fq2rPE", "fq3rPEE-fq2rPE", "units", 'F' );
   dataloader->AddVariable( "var85:=fq3rEPP-fq2rEP", "fq3rEPP-fq2rEP", "units", 'F' );
   dataloader->AddVariable( "var86:=fq3rPEP-fq2rPE", "fq3rPEP-fq2rPE", "units", 'F' );
   dataloader->AddVariable( "var87:=fq3rPPE-fq2rPP", "fq3rPPE-fq2rPP", "units", 'F' );

   //dataloader->AddVariable( "var88:=fqnse", "fqnse", "units", 'I' );

/*
if(atoi(gApplication->Argv(4))==1){
   dataloader->AddVariable( "var1:=fqpi0mom1[0]", "fqpi0mom1[0]", "units",  'F' );
   dataloader->AddVariable( "var2:=fqpi0mom2[0]", "fqpi0mom2[0]", "units", 'F' );
   dataloader->AddVariable( "var3:=fq1rnll[0][1]-fqpi0nll[0]", "fq1rnll[0][1]-fqpi0nll[0]", "units", 'F' );
   dataloader->AddVariable( "var4:=fqpi0mass[0]", "qpi0mass", "units", 'F' );
   dataloader->AddVariable( "var5:=fqpi0photangle[0]", "fqpi0photangle[0]", "units", 'F' );
   dataloader->AddVariable( "var6:=fqpi0momtot[0]", "fqpi0momtot[0]", "units", 'F' );
   dataloader->AddVariable( "var7:=fq1rmom[0][1]", "fq1rmom[0][1]", "units", 'F' );
  
   dataloader->AddVariable( "var8:=fq1rE-fq2rEE", "fq1rE-fq2rEE", "units", 'F' );
   dataloader->AddVariable( "var9:=fq1rE-fq2rEP", "fq1rE-fq2rEP", "units", 'F' );
   dataloader->AddVariable( "var10:=fq1rE-fq2rPE", "fq1rE-fq2rPE", "units", 'F' );
   dataloader->AddVariable( "var11:=fq1rE-fq2rPP", "fq1rE-fq2rPP", "units", 'F' );
   dataloader->AddVariable( "var12:=erec1r", "erec1r", "units", 'F' );

   dataloader->AddVariable( "var13:=wall", "wall", "units", 'F' );
   dataloader->AddVariable( "var14:=evis", "evis", "units", 'F' );
}
else if(atoi(gApplication->Argv(4))==2){
   dataloader->AddVariable( "var1:=fqpi0mom1[0]", "fqpi0mom1[0]", "units",  'F' );
   dataloader->AddVariable( "var2:=fqpi0mom2[0]", "fqpi0mom2[0]", "units", 'F' );
   dataloader->AddVariable( "var3:=fq2rEP-fqpi0nll[0]", "fq2rEP-fqpi0nll[0]", "units", 'F' );
   dataloader->AddVariable( "var4:=fqpi0mass[0]", "qpi0mass", "units", 'F' );
   dataloader->AddVariable( "var5:=fqpi0photangle[0]", "fqpi0photangle[0]", "units", 'F' );
   dataloader->AddVariable( "var6:=fqpi0momtot[0]", "fqpi0momtot[0]", "units", 'F' );
   dataloader->AddVariable( "var7:=angleepi", "angleepi", "units", 'F' );
   dataloader->AddVariable( "var8:=momepi[0]", "momepi[0]", "units", 'F' );
   dataloader->AddVariable( "var9:=momepi[1]", "momepi[1]", "units", 'F' );
   dataloader->AddVariable( "var10:=fqpi0nll[0]", "fqpi0nll[0]", "units", 'F' );
*/
/*
   dataloader->AddVariable( "var11:=fq2rEE-fq3rEEE", "fq2rEE-fq3rEEE", "units", 'F' );
   dataloader->AddVariable( "var12:=fq2rEE-fq3rEPE", "fq2rEE-fq3rEPE", "units", 'F' );
   dataloader->AddVariable( "var13:=fq2rEE-fq3rPEE", "fq2rEE-fq3rPEE", "units", 'F' );
   dataloader->AddVariable( "var14:=fq2rEE-fq3rEEP", "fq2rEE-fq3rEEP", "units", 'F' );
   dataloader->AddVariable( "var15:=fq2rEE-fq3rEPP", "fq2rEE-fq3rEPP", "units", 'F' );
   dataloader->AddVariable( "var16:=fq2rEE-fq3rPPE", "fq2rEE-fq3rPPE", "units", 'F' );
   dataloader->AddVariable( "var17:=fq2rEE-fq3rPEP", "fq2rEE-fq3rPEP", "units", 'F' );
   dataloader->AddVariable( "var18:=fq2rEE-fq3rPPP", "fq2rEE-fq3rPPP", "units", 'F' );

   dataloader->AddVariable( "var19:=fq2rPP-fq3rEEE", "fq2rPP-fq3rEEE", "units", 'F' );
   dataloader->AddVariable( "var20:=fq2rPP-fq3rEPE", "fq2rPP-fq3rEPE", "units", 'F' );
   dataloader->AddVariable( "var21:=fq2rPP-fq3rPEE", "fq2rPP-fq3rPEE", "units", 'F' );
   dataloader->AddVariable( "var22:=fq2rPP-fq3rEEP", "fq2rPP-fq3rEEP", "units", 'F' );
   dataloader->AddVariable( "var23:=fq2rPP-fq3rEPP", "fq2rPP-fq3rEPP", "units", 'F' );
   dataloader->AddVariable( "var24:=fq2rPP-fq3rPPE", "fq2rPP-fq3rPPE", "units", 'F' );
   dataloader->AddVariable( "var25:=fq2rPP-fq3rPEP", "fq2rPP-fq3rPEP", "units", 'F' );
   dataloader->AddVariable( "var26:=fq2rPP-fq3rPPP", "fq2rPP-fq3rPPP", "units", 'F' );

   dataloader->AddVariable( "var27:=fq2rEP-fq3rEEE", "fq2rEP-fq3rEEE", "units", 'F' );
   dataloader->AddVariable( "var28:=fq2rEP-fq3rEPE", "fq2rEP-fq3rEPE", "units", 'F' );
   dataloader->AddVariable( "var29:=fq2rEP-fq3rPEE", "fq2rEP-fq3rPEE", "units", 'F' );
   dataloader->AddVariable( "var30:=fq2rEP-fq3rEEP", "fq2rEP-fq3rEEP", "units", 'F' );
   dataloader->AddVariable( "var31:=fq2rEP-fq3rEPP", "fq2rEP-fq3rEPP", "units", 'F' );
   dataloader->AddVariable( "var32:=fq2rEP-fq3rPPE", "fq2rEP-fq3rPPE", "units", 'F' );
   dataloader->AddVariable( "var33:=fq2rEP-fq3rPEP", "fq2rEP-fq3rPEP", "units", 'F' );
   dataloader->AddVariable( "var34:=fq2rEP-fq3rPPP", "fq2rEP-fq3rPPP", "units", 'F' );

   dataloader->AddVariable( "var35:=fq2rPE-fq3rEEE", "fq2rPE-fq3rEEE", "units", 'F' );
   dataloader->AddVariable( "var36:=fq2rPE-fq3rEPE", "fq2rPE-fq3rEPE", "units", 'F' );
   dataloader->AddVariable( "var37:=fq2rPE-fq3rPEE", "fq2rPE-fq3rPEE", "units", 'F' );
   dataloader->AddVariable( "var38:=fq2rPE-fq3rEEP", "fq2rPE-fq3rEEP", "units", 'F' );
   dataloader->AddVariable( "var39:=fq2rPE-fq3rEPP", "fq2rPE-fq3rEPP", "units", 'F' );
   dataloader->AddVariable( "var40:=fq2rPE-fq3rPPE", "fq2rPE-fq3rPPE", "units", 'F' );
   dataloader->AddVariable( "var41:=fq2rPE-fq3rPEP", "fq2rPE-fq3rPEP", "units", 'F' );
   dataloader->AddVariable( "var42:=fq2rPE-fq3rPPP", "fq2rPE-fq3rPPP", "units", 'F' );
}
*/
   //dataloader->AddVariable( "var8:=fqpi0dconv1[0]", "fqpi0dconv1", "units", 'F' );
   //dataloader->AddVariable( "var9:=fqpi0dconv2[0]", "fqpi0dconv2", "units", 'F' );
   //dataloader->AddVariable( "var10:=fqpi0t0[0]", "qpi0t0", "units",  'F' );
   //dataloader->AddVariable( "var11:=fqpi0totmu[0]", "fqpi0totmu", "units", 'F' );
   //dataloader->AddVariable( "var12:=fqpi0dirtot[0][0]", "fqpi0dirtot0", "units", 'F' );
   //dataloader->AddVariable( "var13:=fqpi0dirtot[0][1]", "fqpi0dirtot1", "units", 'F' );
   //dataloader->AddVariable( "var14:=fqpi0dirtot[0][2]", "fqpi0dirtot2", "units", 'F' );
/*
   dataloader->AddVariable( "fqpi0mom1[1]", "fqpi0mom12", "units",  'F' );
   dataloader->AddVariable( "fqpi0mom2[1]", "fqpi0mom22", "units", 'F' );
   dataloader->AddVariable( "fqpi0dconv1[1]", "fqpi0dconv12", "units", 'F' );
   dataloader->AddVariable( "fqpi0dconv2[1]", "fqpi0dconv22", "units", 'F' );
   dataloader->AddVariable( "fqpi0t0[1]", "qpi0t02", "units",  'F' );
   dataloader->AddVariable( "fqpi0totmu[1]", "fqpi0totmu2", "units", 'F' );
   dataloader->AddVariable( "fqpi0nll[1]", "fqpi0nll2", "units", 'F' );
   dataloader->AddVariable( "fqpi0mass[1]", "qpi0mass2", "units", 'F' );
   dataloader->AddVariable( "fqpi0photangle[1]", "fqpi0photangle2", "units", 'F' );
   dataloader->AddVariable( "fqpi0dirtot[1][0]", "fqpi0dirtot02", "units", 'F' );
   dataloader->AddVariable( "fqpi0dirtot[1][1]", "fqpi0dirtot12", "units", 'F' );
   dataloader->AddVariable( "fqpi0dirtot[1][2]", "fqpi0dirtot22", "units", 'F' );
*/
   // You can add so-called "Spectator variables", which are not used in the MVA training,
   // but will appear in the final "TestTree" produced by TMVA. This TestTree will contain the
   // input variables, the response values of all trained MVAs, and the spectator variables

   //dataloader->AddSpectator( "fqpi0dirtot[0][0]",  "pi0 dir. Spectator 1", "units", 'F' );
   //dataloader->AddSpectator( "fqpi0dirtot[0][1]",  "pi0 dir. Spectator 2", "units", 'F' );
   //dataloader->AddSpectator( "fqpi0dirtot[0][2]",  "pi0 dir. Spectator 3", "units", 'F' );

   // global event weights per tree (see below for setting event-wise weights)
   Double_t signalWeight     = 1.0;
   Double_t backgroundWeight = 1.0;

   // You can add an arbitrary number of signal or background trees
   dataloader->AddSignalTree    ( signalTree,     signalWeight  );
   dataloader->AddBackgroundTree( background, backgroundWeight  );

   //dataloader->AddSignalTree    ( signalTreeTest,     signalWeight, "Test" );
   //dataloader->AddBackgroundTree( backgroundTest, backgroundWeight, "Test" );

   // To give different trees for training and testing, do as follows:
   //
   //     dataloader->AddSignalTree( signalTrainingTree, signalTrainWeight, "Training" );
   //     dataloader->AddSignalTree( signalTestTree,     signalTestWeight,  "Test" );

   // Use the following code instead of the above two or four lines to add signal and background
   // training and test events "by hand"
   // NOTE that in this case one should not give expressions (such as "var1+var2") in the input
   //      variable definition, but simply compute the expression before adding the event
   // ```cpp
   // // --- begin ----------------------------------------------------------
   // std::vector<Double_t> vars( 4 ); // vector has size of number of input variables
   // Float_t  treevars[4], weight;
   //
   // // Signal
   // for (UInt_t ivar=0; ivar<4; ivar++) signalTree->SetBranchAddress( Form( "var%i", ivar+1 ), &(treevars[ivar]) );
   // for (UInt_t i=0; i<signalTree->GetEntries(); i++) {
   //    signalTree->GetEntry(i);
   //    for (UInt_t ivar=0; ivar<4; ivar++) vars[ivar] = treevars[ivar];
   //    // add training and test events; here: first half is training, second is testing
   //    // note that the weight can also be event-wise
   //    if (i < signalTree->GetEntries()/2.0) dataloader->AddSignalTrainingEvent( vars, signalWeight );
   //    else                              dataloader->AddSignalTestEvent    ( vars, signalWeight );
   // }
   //
   // // Background (has event weights)
   // background->SetBranchAddress( "weight", &weight );
   // for (UInt_t ivar=0; ivar<4; ivar++) background->SetBranchAddress( Form( "var%i", ivar+1 ), &(treevars[ivar]) );
   // for (UInt_t i=0; i<background->GetEntries(); i++) {
   //    background->GetEntry(i);
   //    for (UInt_t ivar=0; ivar<4; ivar++) vars[ivar] = treevars[ivar];
   //    // add training and test events; here: first half is training, second is testing
   //    // note that the weight can also be event-wise
   //    if (i < background->GetEntries()/2) dataloader->AddBackgroundTrainingEvent( vars, backgroundWeight*weight );
   //    else                                dataloader->AddBackgroundTestEvent    ( vars, backgroundWeight*weight );
   // }
   // // --- end ------------------------------------------------------------
   // ```
   // End of tree registration

   // Set individual event weights (the variables must exist in the original TTree)
   // -  for signal    : `dataloader->SetSignalWeightExpression    ("weight1*weight2");`
   // -  for background: `dataloader->SetBackgroundWeightExpression("weight1*weight2");`
   dataloader->SetSignalWeightExpression( "fluxWeight[1]" );
   dataloader->SetBackgroundWeightExpression( "fluxWeight[1]" );

   // Apply additional cuts on the signal and background samples (can be different)
   //TCut mycuts = "sigCategory >= 0 && sigCategory <= 2  && (evis > 30 && fqwall > 200 && nhitac < 16 && fqnse < 3) && !((fqmrnring[0]==1 && fqnse == 1) || (fqmrnring[0]==1 && fqnse == 2) || (fqmrnring[0]==2 && fqnse == 2)) "; // for example: TCut mycuts = "abs(var1)<0.5 && abs(var2-0.5)<1";
   //TCut mycutb = "bkgCategory >= 0 && bkgCategory <= 2  && (evis > 30 && fqwall > 200 && nhitac < 16 && fqnse < 3) && !((fqmrnring[0]==1 && fqnse == 1) || (fqmrnring[0]==1 && fqnse == 2) || (fqmrnring[0]==2 && fqnse == 2)) "; // for example: TCut mycutb = "abs(var1)<0.5";

   // fq1rnll[0][2]-fq1rnll[0][1] > fq1rmom[0][1]*0.2
   TCut myCommonCut = "fq1rmom[0][1] > 30 && fqwall > 200 && nhitac < 16 && fqmrnring[0] == 3 && fqnse == 2";
   TCut mycuts = "sigCategory >= 0 && sigCategory <= 2  " && myCommonCut;
   TCut mycutb = "bkgCategory >= 0 && bkgCategory <= 2  " && myCommonCut;

   // Tell the dataloader how to use the training and testing events
   //
   // If no numbers of events are given, half of the events in the tree are used
   // for training, and the other half for testing:
   //
   //    dataloader->PrepareTrainingAndTestTree( mycut, "SplitMode=random:!V" );
   //
   // To also specify the number of testing events, use:
   //
   //    dataloader->PrepareTrainingAndTestTree( mycut,
   //         "NSigTrain=3000:NBkgTrain=3000:NSigTest=3000:NBkgTest=3000:SplitMode=Random:!V" );
   dataloader->PrepareTrainingAndTestTree( mycuts, mycutb,"nTest_Signal=1000:nTest_Background=1000:SplitMode=Random:NormMode=NumEvents:!V" );
                                        //"nTrain_Signal=1000:nTrain_Background=1000:SplitMode=Random:NormMode=NumEvents:!V" );


   cout<<"Booking MVA methods.. "<<endl;
   // ### Book MVA methods
   //
   // Please lookup the various method configuration options in the corresponding cxx files, eg:
   // src/MethoCuts.cxx, etc, or here: http://tmva.sourceforge.net/optionRef.html
   // it is possible to preset ranges in the option string in which the cut optimisation should be done:
   // "...:CutRangeMin[2]=-1:CutRangeMax[2]=1"...", where [2] is the third input variable

   // Cut optimisation
   if (Use["Cuts"])
      factory->BookMethod( dataloader, TMVA::Types::kCuts, "Cuts",
                           "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart" );

   if (Use["CutsD"])
      factory->BookMethod( dataloader, TMVA::Types::kCuts, "CutsD",
                           "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart:VarTransform=Decorrelate" );

   if (Use["CutsPCA"])
      factory->BookMethod( dataloader, TMVA::Types::kCuts, "CutsPCA",
                           "!H:!V:FitMethod=MC:EffSel:SampleSize=200000:VarProp=FSmart:VarTransform=PCA" );

   if (Use["CutsGA"])
      factory->BookMethod( dataloader, TMVA::Types::kCuts, "CutsGA",
                           "H:!V:FitMethod=GA:CutRangeMin[0]=-10:CutRangeMax[0]=10:VarProp[1]=FMax:EffSel:Steps=30:Cycles=3:PopSize=400:SC_steps=10:SC_rate=5:SC_factor=0.95" );

   if (Use["CutsSA"])
      factory->BookMethod( dataloader, TMVA::Types::kCuts, "CutsSA",
                           "!H:!V:FitMethod=SA:EffSel:MaxCalls=150000:KernelTemp=IncAdaptive:InitialTemp=1e+6:MinTemp=1e-6:Eps=1e-10:UseDefaultScale" );

   // Likelihood ("naive Bayes estimator")
   if (Use["Likelihood"])
      factory->BookMethod( dataloader, TMVA::Types::kLikelihood, "Likelihood",
                           "H:!V:TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmoothBkg[1]=10:NSmooth=1:NAvEvtPerBin=50" );

   // Decorrelated likelihood
   if (Use["LikelihoodD"])
      factory->BookMethod( dataloader, TMVA::Types::kLikelihood, "LikelihoodD",
                           "!H:!V:TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmooth=5:NAvEvtPerBin=50:VarTransform=Decorrelate" );

   // PCA-transformed likelihood
   if (Use["LikelihoodPCA"])
      factory->BookMethod( dataloader, TMVA::Types::kLikelihood, "LikelihoodPCA",
                           "!H:!V:!TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmooth=5:NAvEvtPerBin=50:VarTransform=PCA" );

   // Use a kernel density estimator to approximate the PDFs
   if (Use["LikelihoodKDE"])
      factory->BookMethod( dataloader, TMVA::Types::kLikelihood, "LikelihoodKDE",
                           "!H:!V:!TransformOutput:PDFInterpol=KDE:KDEtype=Gauss:KDEiter=Adaptive:KDEFineFactor=0.3:KDEborder=None:NAvEvtPerBin=50" );

   // Use a variable-dependent mix of splines and kernel density estimator
   if (Use["LikelihoodMIX"])
      factory->BookMethod( dataloader, TMVA::Types::kLikelihood, "LikelihoodMIX",
                           "!H:!V:!TransformOutput:PDFInterpolSig[0]=KDE:PDFInterpolBkg[0]=KDE:PDFInterpolSig[1]=KDE:PDFInterpolBkg[1]=KDE:PDFInterpolSig[2]=Spline2:PDFInterpolBkg[2]=Spline2:PDFInterpolSig[3]=Spline2:PDFInterpolBkg[3]=Spline2:KDEtype=Gauss:KDEiter=Nonadaptive:KDEborder=None:NAvEvtPerBin=50" );

   // Test the multi-dimensional probability density estimator
   // here are the options strings for the MinMax and RMS methods, respectively:
   //
   //      "!H:!V:VolumeRangeMode=MinMax:DeltaFrac=0.2:KernelEstimator=Gauss:GaussSigma=0.3" );
   //      "!H:!V:VolumeRangeMode=RMS:DeltaFrac=3:KernelEstimator=Gauss:GaussSigma=0.3" );
   if (Use["PDERS"])
      factory->BookMethod( dataloader, TMVA::Types::kPDERS, "PDERS",
                           "!H:!V:NormTree=T:VolumeRangeMode=Adaptive:KernelEstimator=Gauss:GaussSigma=0.3:NEventsMin=400:NEventsMax=600" );

   if (Use["PDERSD"])
      factory->BookMethod( dataloader, TMVA::Types::kPDERS, "PDERSD",
                           "!H:!V:VolumeRangeMode=Adaptive:KernelEstimator=Gauss:GaussSigma=0.3:NEventsMin=400:NEventsMax=600:VarTransform=Decorrelate" );

   if (Use["PDERSPCA"])
      factory->BookMethod( dataloader, TMVA::Types::kPDERS, "PDERSPCA",
                           "!H:!V:VolumeRangeMode=Adaptive:KernelEstimator=Gauss:GaussSigma=0.3:NEventsMin=400:NEventsMax=600:VarTransform=PCA" );

   // Multi-dimensional likelihood estimator using self-adapting phase-space binning
   if (Use["PDEFoam"])
      factory->BookMethod( dataloader, TMVA::Types::kPDEFoam, "PDEFoam",
                           "!H:!V:SigBgSeparate=F:TailCut=0.001:VolFrac=0.0666:nActiveCells=500:nSampl=2000:nBin=5:Nmin=100:Kernel=None:Compress=T" );

   if (Use["PDEFoamBoost"])
      factory->BookMethod( dataloader, TMVA::Types::kPDEFoam, "PDEFoamBoost",
                           "!H:!V:Boost_Num=30:Boost_Transform=linear:SigBgSeparate=F:MaxDepth=4:UseYesNoCell=T:DTLogic=MisClassificationError:FillFoamWithOrigWeights=F:TailCut=0:nActiveCells=500:nBin=20:Nmin=400:Kernel=None:Compress=T" );

   // K-Nearest Neighbour classifier (KNN)
   if (Use["KNN"])
      factory->BookMethod( dataloader, TMVA::Types::kKNN, "KNN",
                           "H:nkNN=20:ScaleFrac=0.8:SigmaFact=1.0:Kernel=Gaus:UseKernel=F:UseWeight=T:!Trim" );

   // H-Matrix (chi2-squared) method
   if (Use["HMatrix"])
      factory->BookMethod( dataloader, TMVA::Types::kHMatrix, "HMatrix", "!H:!V:VarTransform=None" );

   // Linear discriminant (same as Fisher discriminant)
   if (Use["LD"])
      factory->BookMethod( dataloader, TMVA::Types::kLD, "LD", "H:!V:VarTransform=None:CreateMVAPdfs:PDFInterpolMVAPdf=Spline2:NbinsMVAPdf=50:NsmoothMVAPdf=10" );

   // Fisher discriminant (same as LD)
   if (Use["Fisher"])
      factory->BookMethod( dataloader, TMVA::Types::kFisher, "Fisher", "H:!V:Fisher:VarTransform=None:CreateMVAPdfs:PDFInterpolMVAPdf=Spline2:NbinsMVAPdf=50:NsmoothMVAPdf=10" );

   // Fisher with Gauss-transformed input variables
   if (Use["FisherG"])
      factory->BookMethod( dataloader, TMVA::Types::kFisher, "FisherG", "H:!V:VarTransform=Gauss" );

   // Composite classifier: ensemble (tree) of boosted Fisher classifiers
   if (Use["BoostedFisher"])
      factory->BookMethod( dataloader, TMVA::Types::kFisher, "BoostedFisher",
                           "H:!V:Boost_Num=20:Boost_Transform=log:Boost_Type=AdaBoost:Boost_AdaBoostBeta=0.2:!Boost_DetailedMonitoring" );

   // Function discrimination analysis (FDA) -- test of various fitters - the recommended one is Minuit (or GA or SA)
   if (Use["FDA_MC"])
      factory->BookMethod( dataloader, TMVA::Types::kFDA, "FDA_MC",
                           "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=MC:SampleSize=100000:Sigma=0.1" );

   if (Use["FDA_GA"]) // can also use Simulated Annealing (SA) algorithm (see Cuts_SA options])
      factory->BookMethod( dataloader, TMVA::Types::kFDA, "FDA_GA",
                           "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=GA:PopSize=100:Cycles=2:Steps=5:Trim=True:SaveBestGen=1" );

   if (Use["FDA_SA"]) // can also use Simulated Annealing (SA) algorithm (see Cuts_SA options])
      factory->BookMethod( dataloader, TMVA::Types::kFDA, "FDA_SA",
                           "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=SA:MaxCalls=15000:KernelTemp=IncAdaptive:InitialTemp=1e+6:MinTemp=1e-6:Eps=1e-10:UseDefaultScale" );

   if (Use["FDA_MT"])
      factory->BookMethod( dataloader, TMVA::Types::kFDA, "FDA_MT",
                           "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=MINUIT:ErrorLevel=1:PrintLevel=-1:FitStrategy=2:UseImprove:UseMinos:SetBatch" );

   if (Use["FDA_GAMT"])
      factory->BookMethod( dataloader, TMVA::Types::kFDA, "FDA_GAMT",
                           "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=GA:Converger=MINUIT:ErrorLevel=1:PrintLevel=-1:FitStrategy=0:!UseImprove:!UseMinos:SetBatch:Cycles=1:PopSize=5:Steps=5:Trim" );

   if (Use["FDA_MCMT"])
      factory->BookMethod( dataloader, TMVA::Types::kFDA, "FDA_MCMT",
                           "H:!V:Formula=(0)+(1)*x0+(2)*x1+(3)*x2+(4)*x3:ParRanges=(-1,1);(-10,10);(-10,10);(-10,10);(-10,10):FitMethod=MC:Converger=MINUIT:ErrorLevel=1:PrintLevel=-1:FitStrategy=0:!UseImprove:!UseMinos:SetBatch:SampleSize=20" );

   // TMVA ANN: MLP (recommended ANN) -- all ANNs in TMVA are Multilayer Perceptrons
   if (Use["MLP"])
      factory->BookMethod( dataloader, TMVA::Types::kMLP, "MLP", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=600:HiddenLayers=N+5:TestRate=5:!UseRegulator" );

   if (Use["MLPBFGS"])
      factory->BookMethod( dataloader, TMVA::Types::kMLP, "MLPBFGS", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=600:HiddenLayers=N+5:TestRate=5:TrainingMethod=BFGS:!UseRegulator" );

   if (Use["MLPBNN"])
      factory->BookMethod( dataloader, TMVA::Types::kMLP, "MLPBNN", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=60:HiddenLayers=N+5:TestRate=5:TrainingMethod=BFGS:UseRegulator" ); // BFGS training with bayesian regulators


   // Multi-architecture DNN implementation.
   if (Use["DNN_CPU"] or Use["DNN_GPU"]) {
      // General layout.
      TString layoutString ("Layout=TANH|128,TANH|128,TANH|128,LINEAR");

      // Training strategies.
      TString training0("LearningRate=1e-1,Momentum=0.9,Repetitions=1,"
                        "ConvergenceSteps=20,BatchSize=256,TestRepetitions=10,"
                        "WeightDecay=1e-4,Regularization=L2,"
                        "DropConfig=0.0+0.5+0.5+0.5, Multithreading=True");
      TString training1("LearningRate=1e-2,Momentum=0.9,Repetitions=1,"
                        "ConvergenceSteps=20,BatchSize=256,TestRepetitions=10,"
                        "WeightDecay=1e-4,Regularization=L2,"
                        "DropConfig=0.0+0.0+0.0+0.0, Multithreading=True");
      TString training2("LearningRate=1e-3,Momentum=0.0,Repetitions=1,"
                        "ConvergenceSteps=20,BatchSize=256,TestRepetitions=10,"
                        "WeightDecay=1e-4,Regularization=L2,"
                        "DropConfig=0.0+0.0+0.0+0.0, Multithreading=True");
      TString trainingStrategyString ("TrainingStrategy=");
      trainingStrategyString += training0 + "|" + training1 + "|" + training2;

      // General Options.
      TString dnnOptions ("!H:V:ErrorStrategy=CROSSENTROPY:VarTransform=N:"
                          "WeightInitialization=XAVIERUNIFORM");
      dnnOptions.Append (":"); dnnOptions.Append (layoutString);
      dnnOptions.Append (":"); dnnOptions.Append (trainingStrategyString);

      // Cuda implementation.
      if (Use["DNN_GPU"]) {
         TString gpuOptions = dnnOptions + ":Architecture=GPU";
         factory->BookMethod(dataloader, TMVA::Types::kDNN, "DNN_GPU", gpuOptions);
      }
      // Multi-core CPU implementation.
      if (Use["DNN_CPU"]) {
         TString cpuOptions = dnnOptions + ":Architecture=CPU";
         factory->BookMethod(dataloader, TMVA::Types::kDNN, "DNN_CPU", cpuOptions);
      }
   }

   // CF(Clermont-Ferrand)ANN
   if (Use["CFMlpANN"])
      factory->BookMethod( dataloader, TMVA::Types::kCFMlpANN, "CFMlpANN", "!H:!V:NCycles=200:HiddenLayers=N+1,N"  ); // n_cycles:#nodes:#nodes:...

   // Tmlp(Root)ANN
   if (Use["TMlpANN"])
      factory->BookMethod( dataloader, TMVA::Types::kTMlpANN, "TMlpANN", "!H:!V:NCycles=200:HiddenLayers=N+1,N:LearningMethod=BFGS:ValidationFraction=0.3"  ); // n_cycles:#nodes:#nodes:...

   // Support Vector Machine
   if (Use["SVM"])
      factory->BookMethod( dataloader, TMVA::Types::kSVM, "SVM", "Gamma=0.25:Tol=0.001:VarTransform=Norm" );

   // Boosted Decision Trees
   if (Use["BDTG"]) // Gradient Boost
      factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDTG",
                           "!H:!V:NTrees=1000:MinNodeSize=2.5%:BoostType=Grad:Shrinkage=0.10:UseBaggedBoost:BaggedSampleFraction=0.5:nCuts=20:MaxDepth=2" );

   if (Use["BDT"])  // Adaptive Boost
      factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDT",
                           "!H:!V:NTrees=850:MinNodeSize=2.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=20" );

   if (Use["BDTB"]) // Bagging
      factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDTB",
                           "!H:!V:NTrees=400:BoostType=Bagging:SeparationType=GiniIndex:nCuts=20" );

   if (Use["BDTD"]) // Decorrelation + Adaptive Boost
      factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDTD",
                           "!H:!V:NTrees=400:MinNodeSize=5%:MaxDepth=3:BoostType=AdaBoost:SeparationType=GiniIndex:nCuts=20:VarTransform=Decorrelate" );

   if (Use["BDTF"])  // Allow Using Fisher discriminant in node splitting for (strong) linearly correlated variables
      factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDTF",
                           "!H:!V:NTrees=50:MinNodeSize=2.5%:UseFisherCuts:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:SeparationType=GiniIndex:nCuts=20" );

   // RuleFit -- TMVA implementation of Friedman's method
   if (Use["RuleFit"])
      factory->BookMethod( dataloader, TMVA::Types::kRuleFit, "RuleFit",
                           "H:!V:RuleFitModule=RFTMVA:Model=ModRuleLinear:MinImp=0.001:RuleMinDist=0.001:NTrees=20:fEventsMin=0.01:fEventsMax=0.5:GDTau=-1.0:GDTauPrec=0.01:GDStep=0.01:GDNSteps=10000:GDErrScale=1.02" );

   // For an example of the category classifier usage, see: TMVAClassificationCategory
   //
   // --------------------------------------------------------------------------------------------------
   //  Now you can optimize the setting (configuration) of the MVAs using the set of training events
   // STILL EXPERIMENTAL and only implemented for BDT's !
   //
   //     factory->OptimizeAllMethods("SigEffAt001","Scan");
   //     factory->OptimizeAllMethods("ROCIntegral","FitGA");
   //
   // --------------------------------------------------------------------------------------------------

   cout<<"MVA method has been booked.. "<<endl;
   // Now you can tell the factory to train, test, and evaluate the MVAs
   //
   // Train MVAs using the set of training events
   factory->TrainAllMethods();

   // Evaluate all MVAs using the set of test events
   factory->TestAllMethods();

   // Evaluate and compare performance of all configured MVAs
   factory->EvaluateAllMethods();

   // --------------------------------------------------------------

   // Save the output
   outputFile->Close();

   std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
   std::cout << "==> TMVAClassification is done!" << std::endl;

   delete factory;
   delete dataloader;
   // Launch the GUI for the root macros
   if (!gROOT->IsBatch()) TMVA::TMVAGui( outfileName );

   return 0;
}

int main( int argc, char** argv )
{
   // Select methods (don't look at this code - not of interest)
   TString methodList;
   for (int i=1; i<argc; i++) {
      TString regMethod(argv[i]);
      if(regMethod=="-b" || regMethod=="--batch") continue;
      if (!methodList.IsNull()) methodList += TString(",");
      methodList += regMethod;
   }
   return TMVAClassification_theia(methodList);
}
