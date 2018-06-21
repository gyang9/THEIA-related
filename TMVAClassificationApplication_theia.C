/// \file
/// \ingroup tutorial_tmva
/// \notebook -nodraw
/// This macro provides a simple example on how to use the trained classifiers
/// within an analysis module
/// - Project   : TMVA - a Root-integrated toolkit for multivariate data analysis
/// - Package   : TMVA
/// - Exectuable: TMVAClassificationApplication
///
/// \macro_output
/// \macro_code
/// \author Andreas Hoecker

#include <cstdlib>
#include <vector>
#include <iostream>
#include <map>
#include <string>

#include "TCanvas.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TStopwatch.h"

#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"

using namespace TMVA;

void TMVAClassificationApplication_theia( TString myMethodList = "" )
{

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
   Use["DNN_CPU"] = 0;         // CUDA-accelerated DNN training.
   Use["DNN_GPU"] = 0;         // Multi-core accelerated DNN.
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
   Use["Plugin"]          = 0;
   Use["Category"]        = 0;
   Use["SVM_Gauss"]       = 0;
   Use["SVM_Poly"]        = 0;
   Use["SVM_Lin"]         = 0;

   std::cout << std::endl;
   std::cout << "==> Start TMVAClassificationApplication_theia" << std::endl;

   // Select methods (don't look at this code - not of interest)
   if (myMethodList != "") {
      for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) it->second = 0;

      std::vector<TString> mlist = gTools().SplitString( myMethodList, ',' );
      for (UInt_t i=0; i<mlist.size(); i++) {
         std::string regMethod(mlist[i]);

         if (Use.find(regMethod) == Use.end()) {
            std::cout << "Method \"" << regMethod
                      << "\" not known in TMVA under this name. Choose among the following:" << std::endl;
            for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) {
               std::cout << it->first << " ";
            }
            std::cout << std::endl;
            return;
         }
         Use[regMethod] = 1;
      }
   }

   // --------------------------------------------------------------------------------------------------

   // Create the Reader object

   TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" );

   // Create a set of variables and declare them to the reader
   // - the variable names MUST corresponds in name and type to those given in the weight file(s) used
/*
   Float_t var1, var2;
   Float_t var3, var4;
   reader->AddVariable( "myvar1 := var1+var2", &var1 );
   reader->AddVariable( "myvar2 := var1-var2", &var2 );
   reader->AddVariable( "var3",                &var3 );
   reader->AddVariable( "var4",                &var4 );

   // Spectator variables declared in the training have to be added to the reader, too
   Float_t spec1,spec2;
   reader->AddSpectator( "spec1 := var1*2",   &spec1 );
   reader->AddSpectator( "spec2 := var1*3",   &spec2 );
*/
/*
   reader->AddVariable( "fqpi0mom1[0]", "fqpi0mom1[0]", "units",  'F' );
   reader->AddVariable( "fqpi0mom2[0]", "fqpi0mom2[0]", "units", 'F' );
   reader->AddVariable( "fq1rnll[0][1]-fqpi0nll[0]", "fq1rnll[0][1]-fqpi0nll[0]", "units", 'F' );
   reader->AddVariable( "fqpi0mass[0]", "qpi0mass", "units", 'F' );
   reader->AddVariable( "fqpi0photangle[0]", "fqpi0photangle[0]", "units", 'F' );
   reader->AddVariable( "fqpi0momtot[0]", "fqpi0momtot[0]", "units", 'F' );
   reader->AddVariable( "fq1rmom[0][1]", "fq1rmom[0][1]", "units", 'F' );

   reader->AddVariable( "fqpi0dconv1[0]", "fqpi0dconv1", "units", 'F' );
   reader->AddVariable( "fqpi0dconv2[0]", "fqpi0dconv2", "units", 'F' );
   reader->AddVariable( "fqpi0t0[0]", "qpi0t0", "units",  'F' );
   reader->AddVariable( "fqpi0totmu[0]", "fqpi0totmu", "units", 'F' );
   reader->AddVariable( "fqpi0dirtot[0][0]", "fqpi0dirtot0", "units", 'F' );
   reader->AddVariable( "fqpi0dirtot[0][1]", "fqpi0dirtot1", "units", 'F' );
   reader->AddVariable( "fqpi0dirtot[0][2]", "fqpi0dirtot2", "units", 'F' );
*/
   //Float_t fqpi0mom1, fqpi0mom2, fq1rnll, fqpi0mass, fqpi0photangle, fqpi0nll, fqpi0momtot, fq1rmom, fqpi0dconv1, fqpi0dconv2, fqpi0t0, fqpi0totmu, fqpi0dirtot0, fqpi0dirtot1, fqpi0dirtot2, lepi, angleepi, momepi1, momepi2;

   Float_t fqpi0momm1;
   Float_t fqpi0momm2;
   Float_t  fq1rnll01_fqpi0nll0;
   Float_t  fqpi0mass0  ;
   Float_t  fqpi0photanglee ;

   Float_t erecmr;
   Float_t fq1rmom01 ;
   Float_t fq1rmom02 ;
   Float_t  fq1rmom03 ;
   Float_t  fqwall ;
   Float_t  fq1rnll01_fq1rnll02  ;
   Float_t  fq1rnll02_fq1rnll03  ;
   Float_t  fq1reloss03 ;
   Float_t  eTOpre ;
   Float_t  towall ;

   Float_t  momee0 ;
   Float_t  momee1 ;
   Float_t  momepi0 ;
   Float_t  momepi1 ;
   Float_t  mompp0 ;
   Float_t  mompp1;
   Float_t  mompie0 ;
   Float_t  mompie1 ;
   Float_t  angleepi;
   Float_t  anglepie ;
   Float_t  angleee ;
   Float_t  anglepp ;
   Float_t  fq1rE_fq2rEE ;
   Float_t  fq1rE_fq2rEP ;
   Float_t  fq1rE_fq2rPE ;
   Float_t  fq1rE_fq2rPP ;

    Float_t momeee0 ;
   Float_t  momeee1 ;
   Float_t  momeee2 ;
   Float_t  momppp0 ;
   Float_t  momppp1 ;
   Float_t  momppp2 ;
   Float_t  momeep0 ;
   Float_t  momeep1 ;
   Float_t  momeep2 ;
   Float_t  momepe0 ;
   Float_t  momepe1 ;
   Float_t  momepe2 ;
   Float_t  mompee0 ;
   Float_t  mompee1 ;
   Float_t  mompee2 ;
   Float_t  momppe0;
   Float_t  momppe1 ;
   Float_t  momppe2;
   Float_t  mompep0;
   Float_t  mompep1;
   Float_t  mompep2;
   Float_t  momepp0;
   Float_t  momepp1;
   Float_t  momepp2;
    Float_t angleeee0;
    Float_t angleeee1;
    Float_t angleeee2;
    Float_t angleppp0;
    Float_t angleppp1;
    Float_t angleppp2;
    Float_t angleeep0;
    Float_t angleeep1;
    Float_t angleeep2;
    Float_t angleepe0;
    Float_t angleepe1;
    Float_t angleepe2;
    Float_t anglepee0;
    Float_t anglepee1;
    Float_t anglepee2;
    Float_t angleppe0;
    Float_t angleppe1;
    Float_t angleppe2;
    Float_t anglepep0;
    Float_t anglepep1;
    Float_t anglepep2;
    Float_t angleepp0;
    Float_t angleepp1;
    Float_t angleepp2;
    Float_t fq3rEEE_fq2rEE;
    Float_t fq3rPPP_fq2rPP;
    Float_t fq3rEEP_fq2rEE ;
    Float_t fq3rEPE_fq2rEP ;
    Float_t fq3rPEE_fq2rPE ;
    Float_t fq3rEPP_fq2rEP ;
    Float_t fq3rPEP_fq2rPE ;
    Float_t fq3rPPE_fq2rPP;

   Float_t fqnse;

   ////////
   
   reader->AddVariable( "fqpi0mom1[0]", &fqpi0momm1);
   reader->AddVariable( "fqpi0mom2[0]", &fqpi0momm2);
   reader->AddVariable( "fq1rnll[0][1]-fqpi0nll[0]", &fq1rnll01_fqpi0nll0  );
   reader->AddVariable( "fqpi0mass[0]",&fqpi0mass0  );
   reader->AddVariable( "fqpi0photangle[0]",&fqpi0photanglee );

   reader->AddVariable( "erecmr",  &erecmr);
   reader->AddVariable( "fq1rmom[0][1]", &fq1rmom01 );
   reader->AddVariable( "fq1rmom[0][2]", &fq1rmom02 );
   reader->AddVariable( "fq1rmom[0][3]", &fq1rmom03 );
   reader->AddVariable( "fqwall", &fqwall );
   reader->AddVariable( "fq1rnll[0][1]-fq1rnll[0][2]",&fq1rnll01_fq1rnll02  );
   reader->AddVariable( "fq1rnll[0][2]-fq1rnll[0][3]",&fq1rnll01_fq1rnll02  );
   reader->AddVariable( "fq1reloss[0][3]", &fq1reloss03 );
   reader->AddVariable( "eTOpre", &eTOpre );
   reader->AddVariable( "towall", &towall );

   reader->AddVariable( "momee[0]", &momee0 );
   reader->AddVariable( "momee[1]", &momee1 );
   reader->AddVariable( "momepi[0]",&momepi0 );
   reader->AddVariable( "momepi[1]", &momepi1 );
   reader->AddVariable( "mompp[0]", &mompp0 );
   reader->AddVariable( "mompp[1]", &mompp1);
   reader->AddVariable( "mompie[0]", &mompie0 );
   reader->AddVariable( "mompie[1]", &mompie1 );
   reader->AddVariable( "angleepi", &angleepi );
   reader->AddVariable( "anglepie", &anglepie );
   reader->AddVariable( "angleee", &angleee );
   reader->AddVariable( "anglepp", &anglepp );
   reader->AddVariable( "fq1rE-fq2rEE", &fq1rE_fq2rEE );
   reader->AddVariable( "fq1rE-fq2rEP", &fq1rE_fq2rEP );
   reader->AddVariable( "fq1rE-fq2rPE", &fq1rE_fq2rPE );
   reader->AddVariable( "fq1rE-fq2rPP", &fq1rE_fq2rPP );

   reader->AddVariable( "momeee[0]", &momeee0 );
   reader->AddVariable( "momeee[1]", &momeee1 );
   reader->AddVariable( "momeee[2]", &momeee2 );
   reader->AddVariable( "momppp[0]", &momppp0 );
   reader->AddVariable( "momppp[1]", &momppp1 );
   reader->AddVariable( "momppp[2]", &momppp2 );
   reader->AddVariable( "momeep[0]", &momeep0 );
   reader->AddVariable( "momeep[1]", &momeep1 );
   reader->AddVariable( "momeep[2]", &momeep2 );
   reader->AddVariable( "momepe[0]", &momepe0 );
   reader->AddVariable( "momepe[1]", &momepe1 );
   reader->AddVariable( "momepe[2]", &momepe2 );
   reader->AddVariable( "mompee[0]", &mompee0 );
   reader->AddVariable( "mompee[1]", &mompee1 );
   reader->AddVariable( "mompee[2]", &mompee2 );
   reader->AddVariable( "momppe[0]", &momppe0);
   reader->AddVariable( "momppe[1]", &momppe1 );
   reader->AddVariable( "momppe[2]", &momppe2);
   reader->AddVariable( "mompep[0]", &mompep0);
   reader->AddVariable( "mompep[1]", &mompep1);
   reader->AddVariable( "mompep[2]", &mompep2);
   reader->AddVariable( "momepp[0]", &momepp0);
   reader->AddVariable( "momepp[1]", &momepp1);
   reader->AddVariable( "momepp[2]", &momepp2);

   reader->AddVariable( "angleeee[0]", &angleeee0);
   reader->AddVariable( "angleeee[1]", &angleeee1);
   reader->AddVariable( "angleeee[2]", &angleeee2);
   reader->AddVariable( "angleppp[0]", &angleppp0);
   reader->AddVariable( "angleppp[1]", &angleppp1);
   reader->AddVariable( "angleppp[2]", &angleppp2);
   reader->AddVariable( "angleeep[0]", &angleeep0);
   reader->AddVariable( "angleeep[1]", &angleeep1);
   reader->AddVariable( "angleeep[2]", &angleeep2);
   reader->AddVariable( "angleepe[0]", &angleepe0);
   reader->AddVariable( "angleepe[1]", &angleepe1);
   reader->AddVariable( "angleepe[2]", &angleepe2);
   reader->AddVariable( "anglepee[0]", &anglepee0);
   reader->AddVariable( "anglepee[1]", &anglepee1);
   reader->AddVariable( "anglepee[2]", &anglepee2);
   reader->AddVariable( "angleppe[0]", &angleppe0);
   reader->AddVariable( "angleppe[1]", &angleppe1);
   reader->AddVariable( "angleppe[2]", &angleppe2);
   reader->AddVariable( "anglepep[0]", &anglepep0);
   reader->AddVariable( "anglepep[1]", &anglepep1);
   reader->AddVariable( "anglepep[2]", &anglepep2);
   reader->AddVariable( "angleepp[0]", &angleepp0);
   reader->AddVariable( "angleepp[1]", &angleepp1);
   reader->AddVariable( "angleepp[2]", &angleepp2);

   reader->AddVariable( "fq3rEEE-fq2rEE",&fq3rEEE_fq2rEE );
   reader->AddVariable( "fq3rPPP-fq2rPP",&fq3rPPP_fq2rPP );
   reader->AddVariable( "fq3rEEP-fq2rEE",&fq3rEEP_fq2rEE );
   reader->AddVariable( "fq3rEPE-fq2rEP",&fq3rEPE_fq2rEP );
   reader->AddVariable( "fq3rPEE-fq2rPE",&fq3rPEE_fq2rPE );
   reader->AddVariable( "fq3rEPP-fq2rEP",&fq3rEPP_fq2rEP );
   reader->AddVariable( "fq3rPEP-fq2rPE",&fq3rPEP_fq2rPE );
   reader->AddVariable( "fq3rPPE-fq2rPP",&fq3rPPE_fq2rPP);

   reader->AddVariable( "fqnse", &fqnse );

/*
   reader->AddVariable( "fqpi0mom1[0]", &fqpi0mom1 );
   reader->AddVariable( "fqpi0mom2[0]", &fqpi0mom2 );
   reader->AddVariable( "fq1rnll[0][1]-fqpi0nll[0]", &fq1rnll );
   reader->AddVariable( "fqpi0mass[0]", &fqpi0mass );
   reader->AddVariable( "fqpi0photangle[0]", &fqpi0photangle );
   reader->AddVariable( "fqpi0momtot[0]", &fqpi0momtot);
   reader->AddVariable( "fq1rmom[0][1]", &fq1rmom );
   reader->AddVariable( "fqpi0dconv1[0]", &fqpi0dconv1 );
   reader->AddVariable( "fqpi0dconv2[0]", &fqpi0dconv2 );
   reader->AddVariable( "fqpi0t0[0]", &fqpi0t0 );
   reader->AddVariable( "fqpi0totmu[0]", &fqpi0totmu );
   reader->AddVariable( "fqpi0dirtot[0][0]", &fqpi0dirtot0 );
   reader->AddVariable( "fqpi0dirtot[0][1]", &fqpi0dirtot1 );
   reader->AddVariable( "fqpi0dirtot[0][2]", &fqpi0dirtot2 );

   reader->AddVariable( "var1", &fqpi0mom1 );
   reader->AddVariable( "var2", &fqpi0mom2 );
   reader->AddVariable( "var3", &fq1rnll );
   reader->AddVariable( "var4", &fqpi0mass );
   reader->AddVariable( "var5", &fqpi0photangle );
   reader->AddVariable( "var6", &fqpi0momtot);
   reader->AddVariable( "var7", &fq1rmom );
   reader->AddVariable( "vaf8", &fqpi0dconv1 );
   reader->AddVariable( "var9", &fqpi0dconv2 );
   reader->AddVariable( "var10", &fqpi0t0 );
   reader->AddVariable( "var11", &fqpi0totmu );
   reader->AddVariable( "var12", &fqpi0dirtot0 );
   reader->AddVariable( "var13", &fqpi0dirtot1 );
   reader->AddVariable( "var14", &fqpi0dirtot2 );
*/
/*
if( 1){ //atoi(gApplication->Argv(5))==3){
   reader->AddVariable( "var1:=fqpi0mom1[0]", &fqpi0mom1);
   reader->AddVariable( "var2:=fqpi0mom2[0]", &fqpi0mom2);
   reader->AddVariable( "var3:=lepi", &lepi );
   reader->AddVariable( "var4:=fqpi0mass[0]", &fqpi0mass );
   reader->AddVariable( "var5:=fqpi0photangle[0]", &fqpi0photangle);
   reader->AddVariable( "var6:=fqpi0momtot[0]", &fqpi0momtot );
   reader->AddVariable( "var7:=angleepi", &angleepi);
   reader->AddVariable( "var8:=momepi[0]", &momepi1);
   reader->AddVariable( "var9:=momepi[1]", &momepi2 );
   reader->AddVariable( "var10:=fqpi0nll[0]", &fqpi0nll);
}
else {
   reader->AddVariable( "var1:=fqpi0mom1[0]", &fqpi0mom1 );
   reader->AddVariable( "var2:=fqpi0mom2[0]", &fqpi0mom2 );
   reader->AddVariable( "var3:=fq1rnll[0][1]-fqpi0nll[0]", &fq1rnll );
   reader->AddVariable( "var4:=fqpi0mass[0]", &fqpi0mass );
   reader->AddVariable( "var5:=fqpi0photangle[0]", &fqpi0photangle );
   reader->AddVariable( "var6:=fqpi0momtot[0]", &fqpi0momtot);
   reader->AddVariable( "var7:=fq1rmom[0][1]", &fq1rmom );
}
*/
   //reader->AddVariable( "var8:=fqpi0dconv1[0]", &fqpi0dconv1 );
   //reader->AddVariable( "var9:=fqpi0dconv2[0]", &fqpi0dconv2 );
   //reader->AddVariable( "var10:=fqpi0t0[0]", &fqpi0t0 );
   //reader->AddVariable( "var11:=fqpi0totmu[0]", &fqpi0totmu );
   //reader->AddVariable( "var12:=fqpi0dirtot[0][0]", &fqpi0dirtot0 );
   //reader->AddVariable( "var13:=fqpi0dirtot[0][1]", &fqpi0dirtot1 );
   //reader->AddVariable( "var14:=fqpi0dirtot[0][2]", &fqpi0dirtot2 );
   cout<<"reading variables done.. "<<endl;

   Float_t Category_cat1, Category_cat2, Category_cat3;
   if (Use["Category"]){
      // Add artificial spectators for distinguishing categories
      //reader->AddSpectator( "Category_cat1 := var3<=0",             &Category_cat1 );
      //reader->AddSpectator( "Category_cat2 := (var3>0)&&(var4<0)",  &Category_cat2 );
      //reader->AddSpectator( "Category_cat3 := (var3>0)&&(var4>=0)", &Category_cat3 );
   }

   // Book the MVA methods

   TString dir    = "dataset/weights/";
   TString prefix = "TMVAClassification";

   // Book method(s)
   for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) {
      if (it->second) {
         TString methodName = TString(it->first) + TString(" method");
         TString weightfile = dir + prefix + TString("_") + TString(it->first) + TString(".weights.xml");
         reader->BookMVA( methodName,  "dataset/weights/TMVAClassification_BDT.weights.xml" );
      }
   }

   // Book output histograms
   UInt_t nbin = 100;
   TH1F *histLk(0);
   TH1F *histLkD(0);
   TH1F *histLkPCA(0);
   TH1F *histLkKDE(0);
   TH1F *histLkMIX(0);
   TH1F *histPD(0);
   TH1F *histPDD(0);
   TH1F *histPDPCA(0);
   TH1F *histPDEFoam(0);
   TH1F *histPDEFoamErr(0);
   TH1F *histPDEFoamSig(0);
   TH1F *histKNN(0);
   TH1F *histHm(0);
   TH1F *histFi(0);
   TH1F *histFiG(0);
   TH1F *histFiB(0);
   TH1F *histLD(0);
   TH1F *histNn(0);
   TH1F *histNnbfgs(0);
   TH1F *histNnbnn(0);
   TH1F *histNnC(0);
   TH1F *histNnT(0);
   TH1F *histBdt(0);
   TH1F *histBdtG(0);
   TH1F *histBdtB(0);
   TH1F *histBdtD(0);
   TH1F *histBdtF(0);
   TH1F *histRf(0);
   TH1F *histSVMG(0);
   TH1F *histSVMP(0);
   TH1F *histSVML(0);
   TH1F *histFDAMT(0);
   TH1F *histFDAGA(0);
   TH1F *histCat(0);
   TH1F *histPBdt(0);
   TH1F *histDnnGpu(0);
   TH1F *histDnnCpu(0);

   if (Use["Likelihood"])    histLk      = new TH1F( "MVA_Likelihood",    "MVA_Likelihood",    nbin, -1, 1 );
   if (Use["LikelihoodD"])   histLkD     = new TH1F( "MVA_LikelihoodD",   "MVA_LikelihoodD",   nbin, -1, 0.9999 );
   if (Use["LikelihoodPCA"]) histLkPCA   = new TH1F( "MVA_LikelihoodPCA", "MVA_LikelihoodPCA", nbin, -1, 1 );
   if (Use["LikelihoodKDE"]) histLkKDE   = new TH1F( "MVA_LikelihoodKDE", "MVA_LikelihoodKDE", nbin,  -0.00001, 0.99999 );
   if (Use["LikelihoodMIX"]) histLkMIX   = new TH1F( "MVA_LikelihoodMIX", "MVA_LikelihoodMIX", nbin,  0, 1 );
   if (Use["PDERS"])         histPD      = new TH1F( "MVA_PDERS",         "MVA_PDERS",         nbin,  0, 1 );
   if (Use["PDERSD"])        histPDD     = new TH1F( "MVA_PDERSD",        "MVA_PDERSD",        nbin,  0, 1 );
   if (Use["PDERSPCA"])      histPDPCA   = new TH1F( "MVA_PDERSPCA",      "MVA_PDERSPCA",      nbin,  0, 1 );
   if (Use["KNN"])           histKNN     = new TH1F( "MVA_KNN",           "MVA_KNN",           nbin,  0, 1 );
   if (Use["HMatrix"])       histHm      = new TH1F( "MVA_HMatrix",       "MVA_HMatrix",       nbin, -0.95, 1.55 );
   if (Use["Fisher"])        histFi      = new TH1F( "MVA_Fisher",        "MVA_Fisher",        nbin, -4, 4 );
   if (Use["FisherG"])       histFiG     = new TH1F( "MVA_FisherG",       "MVA_FisherG",       nbin, -1, 1 );
   if (Use["BoostedFisher"]) histFiB     = new TH1F( "MVA_BoostedFisher", "MVA_BoostedFisher", nbin, -2, 2 );
   if (Use["LD"])            histLD      = new TH1F( "MVA_LD",            "MVA_LD",            nbin, -2, 2 );
   if (Use["MLP"])           histNn      = new TH1F( "MVA_MLP",           "MVA_MLP",           nbin, -1.25, 1.5 );
   if (Use["MLPBFGS"])       histNnbfgs  = new TH1F( "MVA_MLPBFGS",       "MVA_MLPBFGS",       nbin, -1.25, 1.5 );
   if (Use["MLPBNN"])        histNnbnn   = new TH1F( "MVA_MLPBNN",        "MVA_MLPBNN",        nbin, -1.25, 1.5 );
   if (Use["CFMlpANN"])      histNnC     = new TH1F( "MVA_CFMlpANN",      "MVA_CFMlpANN",      nbin,  0, 1 );
   if (Use["TMlpANN"])       histNnT     = new TH1F( "MVA_TMlpANN",       "MVA_TMlpANN",       nbin, -1.3, 1.3 );
   if (Use["DNN_GPU"]) histDnnGpu = new TH1F("MVA_DNN_GPU", "MVA_DNN_GPU", nbin, -0.1, 1.1);
   if (Use["DNN_CPU"]) histDnnCpu = new TH1F("MVA_DNN_CPU", "MVA_DNN_CPU", nbin, -0.1, 1.1);
   if (Use["BDT"])           histBdt     = new TH1F( "MVA_BDT",           "MVA_BDT",           nbin, -0.8, 0.8 );
   if (Use["BDTG"])          histBdtG    = new TH1F( "MVA_BDTG",          "MVA_BDTG",          nbin, -1.0, 1.0 );
   if (Use["BDTB"])          histBdtB    = new TH1F( "MVA_BDTB",          "MVA_BDTB",          nbin, -1.0, 1.0 );
   if (Use["BDTD"])          histBdtD    = new TH1F( "MVA_BDTD",          "MVA_BDTD",          nbin, -0.8, 0.8 );
   if (Use["BDTF"])          histBdtF    = new TH1F( "MVA_BDTF",          "MVA_BDTF",          nbin, -1.0, 1.0 );
   if (Use["RuleFit"])       histRf      = new TH1F( "MVA_RuleFit",       "MVA_RuleFit",       nbin, -2.0, 2.0 );
   if (Use["SVM_Gauss"])     histSVMG    = new TH1F( "MVA_SVM_Gauss",     "MVA_SVM_Gauss",     nbin,  0.0, 1.0 );
   if (Use["SVM_Poly"])      histSVMP    = new TH1F( "MVA_SVM_Poly",      "MVA_SVM_Poly",      nbin,  0.0, 1.0 );
   if (Use["SVM_Lin"])       histSVML    = new TH1F( "MVA_SVM_Lin",       "MVA_SVM_Lin",       nbin,  0.0, 1.0 );
   if (Use["FDA_MT"])        histFDAMT   = new TH1F( "MVA_FDA_MT",        "MVA_FDA_MT",        nbin, -2.0, 3.0 );
   if (Use["FDA_GA"])        histFDAGA   = new TH1F( "MVA_FDA_GA",        "MVA_FDA_GA",        nbin, -2.0, 3.0 );
   if (Use["Category"])      histCat     = new TH1F( "MVA_Category",      "MVA_Category",      nbin, -2., 2. );
   if (Use["Plugin"])        histPBdt    = new TH1F( "MVA_PBDT",          "MVA_BDT",           nbin, -0.8, 0.8 );

   TH1F* eff1 = new TH1F("eff1","eff1",20,0, 5000);
   TH1F* eff2 = new TH1F("eff2","eff2",20,0, 5000);


   // PDEFoam also returns per-event error, fill in histogram, and also fill significance
   if (Use["PDEFoam"]) {
      histPDEFoam    = new TH1F( "MVA_PDEFoam",       "MVA_PDEFoam",              nbin,  0, 1 );
      histPDEFoamErr = new TH1F( "MVA_PDEFoamErr",    "MVA_PDEFoam error",        nbin,  0, 1 );
      histPDEFoamSig = new TH1F( "MVA_PDEFoamSig",    "MVA_PDEFoam significance", nbin,  0, 10 );
   }

   // Book example histogram for probability (the other methods are done similarly)
   TH1F *probHistFi(0), *rarityHistFi(0);
   if (Use["Fisher"]) {
      probHistFi   = new TH1F( "MVA_Fisher_Proba",  "MVA_Fisher_Proba",  nbin, 0, 1 );
      rarityHistFi = new TH1F( "MVA_Fisher_Rarity", "MVA_Fisher_Rarity", nbin, 0, 1 );
   }

   // Prepare input tree (this must be replaced by your data source)
   // in this example, there is a toy tree with signal and one with background events
   // we'll later on use only the "signal" events for the test in this example.
   //
   TFile *input(0);
   TString fname;
   if( /*atoi(gApplication->Argv(6))> 0*/ 1) fname = Form("/home/gyang/work/t2k/wc/outputTest.root" /*atoi(gApplication->Argv(6))*/);
   else fname = "/home/gyang/work/t2k/wc/outputTest.root";
   //TString fname = "/home/theiaang/work/t2k/wc/input/skmc/combined.root";
   //TString fname = "./tmva_class_example.root";
   if (!gSystem->AccessPathName( fname )) {
      input = TFile::Open( fname ); // check if file in local directory exists
   }
   else {
      TFile::SetCacheFileDir(".");
      //input = TFile::Open("http://root.cern.ch/files/tmva_class_example.root", "CACHEREAD"); // if not: download from ROOT server
   }
   if (!input) {
      std::cout << "ERROR: could not open data file" << std::endl;
      exit(1);
   }
   std::cout << "--- TMVAClassificationApp    : Using input file: " << input->GetName() << std::endl;

   // Event loop

   // Prepare the event tree
   // - Here the variable names have to corresponds to your tree
   // - You can use the same variables as above which is slightly faster,
   //   but of course you can use different ones and copy the values inside the event loop
   //
   std::cout << "--- Select signal sample" << std::endl;

   double fq2rPE;
   double fq2rEE;
   double fq2rEP;
   double fq2rPP;
   double fq1rE;
   double fq3rEEE;
   double fq3rPPP;
   double fq3rPPE;
   double fq3rPEP;
   double fq3rEPP;
   double fq3rEEP;
   double fq3rEPE;
   double fq3rPEE;
/*
   double angleepi;
   double anglepie;
   double anglepp;
   double angleee;
*/
   double angleeee[3];
   double angleppp[3];
   double angleepp[3];
   double anglepep[3];
   double angleppe[3];
   double angleeep[3];
   double angleepe[3];
   double anglepee[3];
   double momee[2];
   double momepi[2];
   double mompie[2];
   double mompp[2];
   double momeee[3];
   double momppp[3];
   double momeep[3];
   double momepe[3];
   double mompee[3];
   double momepp[3];
   double mompep[3];
   double momppe[3];

   double erec1r;
/*
   double eTOpre;
   double fqwall;
   double towall;
   double erec1r;
   double erecmr;
*/   
   Float_t         dirnu[50][3];
   Int_t           fqnse2;
   Int_t           fqntwnd;
   Int_t           fqtwnd_iclstr[10];   //[fqntwnd]
   Int_t           fqtwnd_npeak[10];   //[fqntwnd]
   Float_t         fqtwnd_prftt0[10];   //[fqntwnd]
   Float_t         fqtwnd_prftpos[10][3];   //[fqntwnd]
   Float_t         fqtwnd[10][2];   //[fqntwnd]
   Float_t         fqtwnd_peakt0[10][10];   //[fqntwnd]
   Float_t         fqtwnd_peakiness[10][10];   //[fqntwnd]
   //Int_t           fqnse;
   Int_t           fqitwnd[10];   //[fqnse]
   Int_t           fqipeak[10];   //[fqnse]
   Int_t           fqnhitpmt[10];   //[fqnse]
   Float_t         fqtotq[10];   //[fqnse]
   Float_t         fq0rtotmu[10];   //[fqnse]
   Float_t         fq0rnll[10];   //[fqnse]
   Int_t           fqn50[10];   //[fqnse]
   Float_t         fqq50[10];   //[fqnse]
   Int_t           fq1rpcflg[10][7];   //[fqnse]
   Float_t         fq1rmom[10][7];   //[fqnse]
   Float_t         fq1rt0[10][7];   //[fqnse]
   Float_t         fq1rtotmu[10][7];   //[fqnse]
   Float_t         fq1rnll[10][7];   //[fqnse]
   Float_t         fq1rpos[10][7][3];   //[fqnse]
   Float_t         fq1rdir[10][7][3];   //[fqnse]
   Float_t         fq1rdconv[10][7];   //[fqnse]
   Float_t         fq1reloss[10][7];   //[fqnse]
   Int_t           fqpi0pcflg[2];
   Float_t         fqpi0mom1[2];
   Float_t         fqpi0mom2[2];
   Float_t         fqpi0momtot[2];
   Float_t         fqpi0dconv1[2];
   Float_t         fqpi0dconv2[2];
   Float_t         fqpi0t0[2];
   Float_t         fqpi0totmu[2];
   Float_t         fqpi0nll[2];
   Float_t         fqpi0mass[2];
   Float_t         fqpi0photangle[2];
   Float_t         fqpi0pos[2][3];
   Float_t         fqpi0dir1[2][3];
   Float_t         fqpi0dir2[2][3];
   Float_t         fqpi0dirtot[2][3];
   Int_t           fqnmrfit;
   Int_t           fqmrifit [60];   //[fqnmrfit]
   Int_t           fqmrnring[60];   //[fqnmrfit]
   Int_t           fqmrpcflg[60];   //[fqnmrfit]
   Float_t         fqmrnll  [60];   //[fqnmrfit]
   Float_t         fqmrtotmu[60];   //[fqnmrfit]
   Int_t           fqmrpid  [60][6];   //[fqnmrfit]
   Float_t         fqmrmom  [60][6];   //[fqnmrfit]
   Float_t         fqmrdconv[60][6];   //[fqnmrfit]
   Float_t         fqmreloss[60][6];   //[fqnmrfit]
   Float_t         fqmrt0   [60][6];   //[fqnmrfit]
   Float_t         fqmrpos  [60][6][3];   //[fqnmrfit]
   Float_t         fqmrdir  [60][6][3];   //[fqnmrfit]

   Double_t  erecmr2;
   Double_t  eTOpre2;
   Double_t  fqwall2;
   Double_t  towall2;
   Double_t  angleee2;
   Double_t  anglepp2;
   Double_t  angleepi2;
   Double_t  anglepie2;   
   Double_t  evis;
   Double_t  nhitac; 

   TTree* theTree = (TTree*)input->Get("h1");
  
   theTree->Print(); 

   theTree->SetBranchAddress("fqntwnd", &fqntwnd);
   theTree->SetBranchAddress("fqtwnd_iclstr", fqtwnd_iclstr);
   theTree->SetBranchAddress("fqtwnd_npeak", fqtwnd_npeak);
   theTree->SetBranchAddress("fqtwnd_prftt0", fqtwnd_prftt0);
   theTree->SetBranchAddress("fqtwnd_prftpos", fqtwnd_prftpos);
   theTree->SetBranchAddress("fqtwnd", fqtwnd);
   theTree->SetBranchAddress("fqtwnd_peakt0", fqtwnd_peakt0);
   theTree->SetBranchAddress("fqtwnd_peakiness", fqtwnd_peakiness);
   theTree->SetBranchAddress("fqnse", &fqnse2);
   theTree->SetBranchAddress("fqitwnd", fqitwnd);
   theTree->SetBranchAddress("fqipeak", fqipeak);
   theTree->SetBranchAddress("fqnhitpmt", fqnhitpmt);
   theTree->SetBranchAddress("fqtotq", fqtotq);
   theTree->SetBranchAddress("fq0rtotmu", fq0rtotmu);
   theTree->SetBranchAddress("fq0rnll", fq0rnll);
   theTree->SetBranchAddress("fqn50", fqn50);
   theTree->SetBranchAddress("fqq50", fqq50);
   theTree->SetBranchAddress("fq1rpcflg", fq1rpcflg);
   theTree->SetBranchAddress("fq1rmom", fq1rmom);
   theTree->SetBranchAddress("fq1rt0", fq1rt0);
   theTree->SetBranchAddress("fq1rtotmu", fq1rtotmu);
   theTree->SetBranchAddress("fq1rnll", fq1rnll);
   theTree->SetBranchAddress("fq1rpos", fq1rpos);
   theTree->SetBranchAddress("fq1rdir", fq1rdir);
   theTree->SetBranchAddress("fq1rdconv", fq1rdconv);
   theTree->SetBranchAddress("fq1reloss", fq1reloss);
   theTree->SetBranchAddress("fqpi0pcflg", fqpi0pcflg);
   theTree->SetBranchAddress("fqpi0mom1", fqpi0mom1);
   theTree->SetBranchAddress("fqpi0mom2", fqpi0mom2);
   theTree->SetBranchAddress("fqpi0momtot", fqpi0momtot);
   theTree->SetBranchAddress("fqpi0dconv1", fqpi0dconv1);
   theTree->SetBranchAddress("fqpi0dconv2", fqpi0dconv2);
   theTree->SetBranchAddress("fqpi0t0", fqpi0t0);
   theTree->SetBranchAddress("fqpi0totmu", fqpi0totmu);
   theTree->SetBranchAddress("fqpi0nll", fqpi0nll);
   theTree->SetBranchAddress("fqpi0mass", fqpi0mass);
   theTree->SetBranchAddress("fqpi0photangle", fqpi0photangle);
   theTree->SetBranchAddress("fqpi0pos", fqpi0pos);
   theTree->SetBranchAddress("fqpi0dir1", fqpi0dir1);
   theTree->SetBranchAddress("fqpi0dir2", fqpi0dir2);
   theTree->SetBranchAddress("fqpi0dirtot", fqpi0dirtot);
   theTree->SetBranchAddress("fqnmrfit", &fqnmrfit);
   theTree->SetBranchAddress("fqmrifit", fqmrifit);
   theTree->SetBranchAddress("fqmrnring", fqmrnring);
   theTree->SetBranchAddress("fqmrpcflg", fqmrpcflg);
   theTree->SetBranchAddress("fqmrnll", fqmrnll);
   theTree->SetBranchAddress("fqmrtotmu", fqmrtotmu);
   theTree->SetBranchAddress("fqmrpid", fqmrpid);
   theTree->SetBranchAddress("fqmrmom", fqmrmom);
   theTree->SetBranchAddress("fqmrdconv", fqmrdconv);
   theTree->SetBranchAddress("fqmreloss", fqmreloss);
   theTree->SetBranchAddress("fqmrt0", fqmrt0);
   theTree->SetBranchAddress("fqmrpos", fqmrpos);
   theTree->SetBranchAddress("fqmrdir", fqmrdir);

   theTree->SetBranchAddress("fq1rE",&fq1rE);
   theTree->SetBranchAddress("fq2rPE",&fq2rPE);
   theTree->SetBranchAddress("fq2rEE",&fq2rEE);
   theTree->SetBranchAddress("fq2rPP",&fq2rPP);
   theTree->SetBranchAddress("fq2rEP",&fq2rEP);
   theTree->SetBranchAddress("fq3rEEP",&fq3rEEP);
   theTree->SetBranchAddress("fq3rEPE",&fq3rEPE);
   theTree->SetBranchAddress("fq3rPEE",&fq3rPEE);
   theTree->SetBranchAddress("fq3rPPP",&fq3rPPP);
   theTree->SetBranchAddress("fq3rEEE",&fq3rEEE);
   theTree->SetBranchAddress("fq3rEPP",&fq3rEPP);
   theTree->SetBranchAddress("fq3rPEP",&fq3rPEP);
   theTree->SetBranchAddress("fq3rPPE",&fq3rPPE);
   theTree->SetBranchAddress("erec1r",&erec1r);
   theTree->SetBranchAddress("erecmr",&erecmr2);
   theTree->SetBranchAddress("eTOpre",&eTOpre2);

   theTree->SetBranchAddress("fqwall",&fqwall2);
   theTree->SetBranchAddress("towall",&towall2);
   theTree->SetBranchAddress("angleepi",&angleepi2);
   theTree->SetBranchAddress("anglepie",&anglepie2);
   theTree->SetBranchAddress("angleee",&angleee2);
   theTree->SetBranchAddress("anglepp",&anglepp2);
   theTree->SetBranchAddress("angleeee",&angleeee);
   theTree->SetBranchAddress("angleppp",&angleppp);
   theTree->SetBranchAddress("angleepp",&angleepp);
   theTree->SetBranchAddress("anglepep",&anglepep);
   theTree->SetBranchAddress("angleppe",&angleppe);
   theTree->SetBranchAddress("angleeep",&angleeep);
   theTree->SetBranchAddress("angleepe",&angleepe);
   theTree->SetBranchAddress("anglepee",&anglepee);
   theTree->SetBranchAddress("momee",&momee);
   theTree->SetBranchAddress("momepi",&momepi);
   theTree->SetBranchAddress("mompie",&mompie);
   theTree->SetBranchAddress("mompp",&mompp);
   theTree->SetBranchAddress("momeee",&momeee);
   theTree->SetBranchAddress("momppp",&momppp);
   theTree->SetBranchAddress("momeep",&momeep);
   theTree->SetBranchAddress("momepe",&momepe);
   theTree->SetBranchAddress("mompee",&mompee);
   theTree->SetBranchAddress("momepp",&momepp);
   theTree->SetBranchAddress("mompep",&mompep);
   theTree->SetBranchAddress("momppe",&momppe);

   theTree->SetBranchAddress("evis",&evis);
   theTree->SetBranchAddress("nhitac",&nhitac);

   double tmvaR;
   //TBranch *tmvaAdd = theTree->Branch("tmva",&tmvaR,"tmva/D");

/*
   Float_t userVar1, userVar2;
   theTree->SetBranchAddress( "var1", &userVar1 );
   theTree->SetBranchAddress( "var2", &userVar2 );
   theTree->SetBranchAddress( "var3", &var3 );
   theTree->SetBranchAddress( "var4", &var4 );
*/
   // Efficiency calculator for cut method
   Int_t    nSelCutsGA = 0;
   Double_t effS       = 0.7;

   TFile* ff = TFile::Open(Form("outputTree_reinput%d.root", 0 /*atoi(gApplication->Argv(5))*/),"RECREATE");
   TTree* tt = theTree->CloneTree(0);
   //ff->Write();
   //delete ff;
   //delete tt;

   //TFile* fff = new TFile("outputTree.root","update");
   //TTree* ttt = (TTree*)fff->Get("h1");
   tt->Branch(Form("tmvaMR%d", 0 /*atoi(gApplication->Argv(5))*/),&tmvaR,"tmvaMR/D");

   std::vector<Float_t> vecVar(4); // vector for EvaluateMVA tests

   std::cout << "--- Processing: " << theTree->GetEntries() << " events" << std::endl;
   TStopwatch sw;
   sw.Start();
   for (Long64_t ievt=0; ievt< theTree->GetEntries();ievt++) {

      if (ievt%10000 == 0) std::cout << "--- ... Processing event: " << ievt << std::endl;

      theTree->GetEntry(ievt);

      /*
        for(Int_t fqLoop=0;fqLoop<fqnmrfit;fqLoop++){

	int ringN = fqmrifit[fqLoop]/1e8;
        int pid1 = fqmrifit[fqLoop] % 10;
        int pid2 = fqmrifit[fqLoop] / 10 % 10;
        int pid3 = fqmrifit[fqLoop] / 100% 10;

	if(TMath::Abs(fqmrifit[fqLoop]) < 1e9 && ringN == 2){
		if(pid1 == 1 && pid2 == 1) {fq2rEE = fqmrnll[fqLoop]; angleee = fqmrdir[fqLoop][0][0]*fqmrdir[fqLoop][1][0]+fqmrdir[fqLoop][0][1]*fqmrdir[fqLoop][1][1]+fqmrdir[fqLoop][0][2]*fqmrdir[fqLoop][1][2]; momee[0] = fqmrmom[fqLoop][0]; momee[1] = fqmrmom[fqLoop][1]; }
		if(pid1 == 3 && pid2 == 3) {fq2rPP = fqmrnll[fqLoop]; anglepp = fqmrdir[fqLoop][0][0]*fqmrdir[fqLoop][1][0]+fqmrdir[fqLoop][0][1]*fqmrdir[fqLoop][1][1]+fqmrdir[fqLoop][0][2]*fqmrdir[fqLoop][1][2]; mompp[0] = fqmrmom[fqLoop][0]; mompp[1] = fqmrmom[fqLoop][1]; }
		if(pid1 == 1 && pid2 == 3) {fq2rEP = fqmrnll[fqLoop]; angleepi = fqmrdir[fqLoop][0][0]*fqmrdir[fqLoop][1][0]+fqmrdir[fqLoop][0][1]*fqmrdir[fqLoop][1][1]+fqmrdir[fqLoop][0][2]*fqmrdir[fqLoop][1][2]; momepi[0] = fqmrmom[fqLoop][0]; momepi[1] = fqmrmom[fqLoop][1]; }
		if(pid1 == 3 && pid2 == 1) {fq2rPE = fqmrnll[fqLoop]; anglepie = fqmrdir[fqLoop][0][0]*fqmrdir[fqLoop][1][0]+fqmrdir[fqLoop][0][1]*fqmrdir[fqLoop][1][1]+fqmrdir[fqLoop][0][2]*fqmrdir[fqLoop][1][2]; mompie[0] = fqmrmom[fqLoop][0]; mompie[1] = fqmrmom[fqLoop][1];}
	}
// angle123[3]: [0],[1],[2]-> 12,13,23
	else if(TMath::Abs(fqmrifit[fqLoop]) < 1e9 && ringN == 3){
                if(pid1 == 1 && pid2 == 1 && pid3 == 1) {fq3rEEE = fqmrnll[fqLoop]; 
			angleeee[0] = fqmrdir[fqLoop][0][0]*fqmrdir[fqLoop][1][0]+fqmrdir[fqLoop][0][1]*fqmrdir[fqLoop][1][1]+fqmrdir[fqLoop][0][2]*fqmrdir[fqLoop][1][2]; 
			angleeee[1] = fqmrdir[fqLoop][0][0]*fqmrdir[fqLoop][2][0]+fqmrdir[fqLoop][0][1]*fqmrdir[fqLoop][2][1]+fqmrdir[fqLoop][0][2]*fqmrdir[fqLoop][2][2];
			angleeee[2] = fqmrdir[fqLoop][1][0]*fqmrdir[fqLoop][2][0]+fqmrdir[fqLoop][1][1]*fqmrdir[fqLoop][2][1]+fqmrdir[fqLoop][1][2]*fqmrdir[fqLoop][2][2];				
			momeee[0] = fqmrmom[fqLoop][0]; momeee[1] = fqmrmom[fqLoop][1]; momeee[2] = fqmrmom[fqLoop][2]; }
                if(pid1 == 3 && pid2 == 3 && pid3 == 3) {fq3rPPP = fqmrnll[fqLoop];
                        angleppp[0] = fqmrdir[fqLoop][0][0]*fqmrdir[fqLoop][1][0]+fqmrdir[fqLoop][0][1]*fqmrdir[fqLoop][1][1]+fqmrdir[fqLoop][0][2]*fqmrdir[fqLoop][1][2];
                        angleppp[1] = fqmrdir[fqLoop][0][0]*fqmrdir[fqLoop][2][0]+fqmrdir[fqLoop][0][1]*fqmrdir[fqLoop][2][1]+fqmrdir[fqLoop][0][2]*fqmrdir[fqLoop][2][2];
                        angleppp[2] = fqmrdir[fqLoop][1][0]*fqmrdir[fqLoop][2][0]+fqmrdir[fqLoop][1][1]*fqmrdir[fqLoop][2][1]+fqmrdir[fqLoop][1][2]*fqmrdir[fqLoop][2][2];
                        momppp[0] = fqmrmom[fqLoop][0]; momppp[1] = fqmrmom[fqLoop][1]; momppp[2] = fqmrmom[fqLoop][2]; }
                if(pid1 == 1 && pid2 == 3 && pid3 == 3) {fq3rEPP = fqmrnll[fqLoop];
                        angleepp[0] = fqmrdir[fqLoop][0][0]*fqmrdir[fqLoop][1][0]+fqmrdir[fqLoop][0][1]*fqmrdir[fqLoop][1][1]+fqmrdir[fqLoop][0][2]*fqmrdir[fqLoop][1][2];
                        angleepp[1] = fqmrdir[fqLoop][0][0]*fqmrdir[fqLoop][2][0]+fqmrdir[fqLoop][0][1]*fqmrdir[fqLoop][2][1]+fqmrdir[fqLoop][0][2]*fqmrdir[fqLoop][2][2];
                        angleepp[2] = fqmrdir[fqLoop][1][0]*fqmrdir[fqLoop][2][0]+fqmrdir[fqLoop][1][1]*fqmrdir[fqLoop][2][1]+fqmrdir[fqLoop][1][2]*fqmrdir[fqLoop][2][2];
                        momepp[0] = fqmrmom[fqLoop][0]; momepp[1] = fqmrmom[fqLoop][1]; momepp[2] = fqmrmom[fqLoop][2]; }
                if(pid1 == 3 && pid2 == 1 && pid3 == 3) {fq3rPEP = fqmrnll[fqLoop];
                        anglepep[0] = fqmrdir[fqLoop][0][0]*fqmrdir[fqLoop][1][0]+fqmrdir[fqLoop][0][1]*fqmrdir[fqLoop][1][1]+fqmrdir[fqLoop][0][2]*fqmrdir[fqLoop][1][2];
                        anglepep[1] = fqmrdir[fqLoop][0][0]*fqmrdir[fqLoop][2][0]+fqmrdir[fqLoop][0][1]*fqmrdir[fqLoop][2][1]+fqmrdir[fqLoop][0][2]*fqmrdir[fqLoop][2][2];
                        anglepep[2] = fqmrdir[fqLoop][1][0]*fqmrdir[fqLoop][2][0]+fqmrdir[fqLoop][1][1]*fqmrdir[fqLoop][2][1]+fqmrdir[fqLoop][1][2]*fqmrdir[fqLoop][2][2];
                        mompep[0] = fqmrmom[fqLoop][0]; mompep[1] = fqmrmom[fqLoop][1]; mompep[2] = fqmrmom[fqLoop][2]; }
                if(pid1 == 3 && pid2 == 3 && pid3 == 1) {fq3rPPE = fqmrnll[fqLoop];
                        angleppe[0] = fqmrdir[fqLoop][0][0]*fqmrdir[fqLoop][1][0]+fqmrdir[fqLoop][0][1]*fqmrdir[fqLoop][1][1]+fqmrdir[fqLoop][0][2]*fqmrdir[fqLoop][1][2];
                        angleppe[1] = fqmrdir[fqLoop][0][0]*fqmrdir[fqLoop][2][0]+fqmrdir[fqLoop][0][1]*fqmrdir[fqLoop][2][1]+fqmrdir[fqLoop][0][2]*fqmrdir[fqLoop][2][2];
                        angleppe[2] = fqmrdir[fqLoop][1][0]*fqmrdir[fqLoop][2][0]+fqmrdir[fqLoop][1][1]*fqmrdir[fqLoop][2][1]+fqmrdir[fqLoop][1][2]*fqmrdir[fqLoop][2][2];
                        momppe[0] = fqmrmom[fqLoop][0]; momppe[1] = fqmrmom[fqLoop][1]; momppe[2] = fqmrmom[fqLoop][2]; }
                if(pid1 == 1 && pid2 == 1 && pid3 == 3) {fq3rEEP = fqmrnll[fqLoop];
                        angleeep[0] = fqmrdir[fqLoop][0][0]*fqmrdir[fqLoop][1][0]+fqmrdir[fqLoop][0][1]*fqmrdir[fqLoop][1][1]+fqmrdir[fqLoop][0][2]*fqmrdir[fqLoop][1][2];
                        angleeep[1] = fqmrdir[fqLoop][0][0]*fqmrdir[fqLoop][2][0]+fqmrdir[fqLoop][0][1]*fqmrdir[fqLoop][2][1]+fqmrdir[fqLoop][0][2]*fqmrdir[fqLoop][2][2];
                        angleeep[2] = fqmrdir[fqLoop][1][0]*fqmrdir[fqLoop][2][0]+fqmrdir[fqLoop][1][1]*fqmrdir[fqLoop][2][1]+fqmrdir[fqLoop][1][2]*fqmrdir[fqLoop][2][2];
                        momeep[0] = fqmrmom[fqLoop][0]; momeep[1] = fqmrmom[fqLoop][1]; momeep[2] = fqmrmom[fqLoop][2]; }
                if(pid1 == 1 && pid2 == 3 && pid3 == 1) {fq3rEPE = fqmrnll[fqLoop];
                        angleepe[0] = fqmrdir[fqLoop][0][0]*fqmrdir[fqLoop][1][0]+fqmrdir[fqLoop][0][1]*fqmrdir[fqLoop][1][1]+fqmrdir[fqLoop][0][2]*fqmrdir[fqLoop][1][2];
                        angleepe[1] = fqmrdir[fqLoop][0][0]*fqmrdir[fqLoop][2][0]+fqmrdir[fqLoop][0][1]*fqmrdir[fqLoop][2][1]+fqmrdir[fqLoop][0][2]*fqmrdir[fqLoop][2][2];
                        angleepe[2] = fqmrdir[fqLoop][1][0]*fqmrdir[fqLoop][2][0]+fqmrdir[fqLoop][1][1]*fqmrdir[fqLoop][2][1]+fqmrdir[fqLoop][1][2]*fqmrdir[fqLoop][2][2];
                        momepe[0] = fqmrmom[fqLoop][0]; momepe[1] = fqmrmom[fqLoop][1]; momepe[2] = fqmrmom[fqLoop][2]; }
                if(pid1 == 3 && pid2 == 1 && pid3 == 1) {fq3rPEE = fqmrnll[fqLoop];
                        anglepee[0] = fqmrdir[fqLoop][0][0]*fqmrdir[fqLoop][1][0]+fqmrdir[fqLoop][0][1]*fqmrdir[fqLoop][1][1]+fqmrdir[fqLoop][0][2]*fqmrdir[fqLoop][1][2];
                        anglepee[1] = fqmrdir[fqLoop][0][0]*fqmrdir[fqLoop][2][0]+fqmrdir[fqLoop][0][1]*fqmrdir[fqLoop][2][1]+fqmrdir[fqLoop][0][2]*fqmrdir[fqLoop][2][2];
                        anglepee[2] = fqmrdir[fqLoop][1][0]*fqmrdir[fqLoop][2][0]+fqmrdir[fqLoop][1][1]*fqmrdir[fqLoop][2][1]+fqmrdir[fqLoop][1][2]*fqmrdir[fqLoop][2][2];
                        mompee[0] = fqmrmom[fqLoop][0]; mompee[1] = fqmrmom[fqLoop][1]; mompee[2] = fqmrmom[fqLoop][2]; }
	}
      }
	

        double xpos = fq1rpos[0][1][0];
        double ypos = fq1rpos[0][1][1];
        double zpos = fq1rpos[0][1][2];
        double rpos = TMath::Sqrt(xpos*xpos+ypos*ypos);
        fqwall = std::min(1690.-rpos,std::min(1810.-zpos,1810.+zpos));
        double tempDir[3], tempPos[3];
        for(Int_t loopTemp=0;loopTemp<3;loopTemp++){
		tempDir[loopTemp] = fq1rdir[0][1][loopTemp];
                tempPos[loopTemp] = fq1rpos[0][1][loopTemp];
	}
        towall = GetToWall(tempPos, tempDir);
	//std::cout<<"towall is "<<towall<<" "<<fq1rdir[0][1][2]<<" "<<fq1rpos[0][1][2]<<std::endl;
	//std::cout<<"fqwall and towall "<<fqwall<<" "<<towall<<std::endl;
        double lemu = fq1rnll[0][2]-fq1rnll[0][1];
        double lpie = fq1rnll[0][1]-fqpi0nll[0];
        double lpimu = fq1rnll[0][2]-fq1rnll[0][3];

        double pe = fq1rmom[0][1];
        double me = 0.5109989461;
        double ee = TMath::Sqrt(pe*pe+me*me);
        double mp = 938.2720813;
        double mn = 939.5654133;
	erec1r = 0;
        eTOpre = TMath::Sqrt( (fqtwnd_prftpos[0][0] - fq1rpos[0][1][0])* (fqtwnd_prftpos[0][0] - fq1rpos[0][1][0]) + (fqtwnd_prftpos[0][1] - fq1rpos[0][1][1])* (fqtwnd_prftpos[0][1] - fq1rpos[0][1][1]) + (fqtwnd_prftpos[0][2] - fq1rpos[0][1][2])* (fqtwnd_prftpos[0][2] - fq1rpos[0][1][2]));

        double costhbeam = fq1rdir[0][1][0]*dirnu[0][0]
                              + fq1rdir[0][1][1]*dirnu[0][1]
                              + fq1rdir[0][1][2]*dirnu[0][2];
        erec1r = (me*me+mn*mn-mp*mp-2*mn*ee)/-2./(mn-ee+pe*costhbeam)/1000.;
	//std::cout<<"directoins for fq and nu: "<<fq1rdir[0][1][0]<<" "<<fq1rdir[0][1][1]<<" "<<fq1rdir[0][1][2]<<" "<<dirnu[0][0]<<" "<<dirnu[0][1]<<" "<<dirnu[0][2]<<std::endl;
        //std::cout<<"costhbeam, me, mn, mp, ee and erec1r "<<costhbeam<<" "<<me<<" "<<mn<<" "<<mp<<" "<<ee<<" "<<erec1r<<std::endl;


        double md = 1232;
        double mN = (mp + mn) / 2.;

	erecmr = 0;

	// 2 rings
	if (fqmrnring[0] == 2) {
	  int pidcode = 0;
	  int ie = -1;
	  // 1st (most energetic) ring
	  if ((fqmrpid[0][0]==2)||(fqmrpid[0][0]==3)) {
	    pidcode = 2;
	  } else if (fqmrpid[0][0] == 1) {
	    ie = 0;
	  } else {
	    std::cout << "Oh no! fqmrnring[0] = " << fqmrnring[0] << " and fqmrpid[0][0] = " << fqmrpid[0][0] << std::endl;
	  }
	  // 2nd ring
	  if ((fqmrpid[0][1]==2)||(fqmrpid[0][1]==3)) {
	    pidcode++;
	  } else if (fqmrpid[0][1] == 1) {
	    if (ie < 0) {ie = 1;}
	  } else {
	    std::cout << "Oh no! fqmrnring[0] = " << fqmrnring[0] << " and fqmrpid[0][1] = " << fqmrpid[0][1] << std::endl;
	  }
	  if (ie < 0) {
	    //	    std::cout << "Ugh, ie = " << ie << ". Setting to 0" << std::endl;
	    ie = 0;
	  }

	  pe = fqmrmom[0][ie];
	  ee = TMath::Sqrt(pe*pe+me*me);
	  costhbeam = fqmrdir[0][ie][0]*dirnu[0][0]
			   + fqmrdir[0][ie][1]*dirnu[0][1]
			   + fqmrdir[0][ie][2]*dirnu[0][2];
	  erecmr = (md*md-mN*mN-me*me)/2/(mN-ee+pe*costhbeam)/1000.;


	  // 3 rings
	} else if (fqmrnring[0] == 3) {
	  int pidcode = 0;
	  int ie = -1;
	  // 1st (most energetic) ring
	  if ((fqmrpid[0][0]==2)||(fqmrpid[0][0]==3)) {
	    pidcode = 4;
	  } else if (fqmrpid[0][0] == 1) {
	    ie = 0;
	  } else {
	    std::cout << "Oh no! fqmrnring[0] = " << fqmrnring[0] << " and fqmrpid[0][0] = " << fqmrpid[0][0] << std::endl;
	  }
	  // 2nd ring
	  if ((fqmrpid[0][1]==2)||(fqmrpid[0][1]==3)) {
	    pidcode += 2;
	  } else if (fqmrpid[0][1] == 1) {
	    if (ie < 0) {ie = 1;}
	  } else {
	    std::cout << "Oh no! fqmrnring[0] = " << fqmrnring[0] << " and fqmrpid[0][1] = " << fqmrpid[0][1] << std::endl;
	  }
	  // 3rd ring
	  if ((fqmrpid[0][2]==2)||(fqmrpid[0][2]==3)) {
	    pidcode++;
	  } else if (fqmrpid[0][2] == 1) {
	    if (ie < 0) {ie = 2;}
	  } else {
	    std::cout << "Oh no! fqmrnring[0] = " << fqmrnring[0] << " and fqmrpid[0][2] = " << fqmrpid[0][2] << std::endl;
	  }
	  if (ie < 0) {
	    //	    std::cout << "Ugh, ie = " << ie << ". Setting to 0" << std::endl;
	    ie = 0;
	  }

	  pe = fqmrmom[0][ie];
	  ee = TMath::Sqrt(pe*pe+me*me);
	  costhbeam = fqmrdir[0][ie][0]*dirnu[0][0]
			   + fqmrdir[0][ie][1]*dirnu[0][1]
			   + fqmrdir[0][ie][2]*dirnu[0][2];
	  erecmr = (md*md-mN*mN-me*me)/2/(mN-ee+pe*costhbeam)/1000.;
	}

	else{
	  erecmr = erec1r;
	}
      */

        fqpi0momm1 = fqpi0mom1[0];
        fqpi0momm2 = fqpi0mom2[0];
        fq1rnll01_fqpi0nll0 = fq1rnll[0][1]-fqpi0nll[0];
        fqpi0mass0 = fqpi0mass[0];
        fqpi0photanglee = fqpi0photangle[0];

        fq1rmom01 = fq1rmom[0][1]; 
        fq1rmom02 = fq1rmom[0][2];
        fq1rmom03 = fq1rmom[0][3];
        fq1rnll01_fq1rnll02 = fq1rnll[0][1]-fq1rnll[0][2];
        fq1rnll02_fq1rnll03 = fq1rnll[0][2]-fq1rnll[0][3];
        fq1reloss03 = fq1reloss[0][3];

        momee0 = momee[0];
        momee1 = momee[1];
        momepi0 = momepi[0];
        momepi1 = momepi[1];
        mompp0 = mompp[0];
        mompp1 = mompp[1];
        mompie0 = mompie[0];
        mompie1 = mompie[1];
        fq1rE_fq2rEE = fq1rE-fq2rEE; 
        fq1rE_fq2rEP = fq1rE-fq2rEP;
        fq1rE_fq2rPE = fq1rE-fq2rPE;
        fq1rE_fq2rPP = fq1rE-fq2rPP;

        momeee0 = momeee[0];  
        momeee1 = momeee[1];
        momeee2 = momeee[2];
        momppp0 = momppp[0];
        momppp1 = momppp[1];
        momppp2 = momppp[2];
        momeep0 = momeep[0];
        momeep1 = momeep[1];
        momeep2 = momeep[2];
        momepe0 = momepe[0];
        momepe1 = momepe[1];
        momepe2 = momepe[2];
        mompee0 = mompee[0];
        mompee1 = mompee[1];
        mompee2 = mompee[2];
        momppe0 = momppe[0];
        momppe1 = momppe[1];
        momppe2 = momppe[2];
        mompep0 = mompep[0];
        mompep1 = mompep[1];
        mompep2 = mompep[2];
        momepp0 = momepp[0];
        momepp1 = momepp[1];
        momepp2 = momepp[2];

        angleeee0 = angleeee[0];
        angleeee1 = angleeee[1];
        angleeee2 = angleeee[2];
        angleppp0 = angleppp[0];
        angleppp1 = angleppp[1];
        angleppp2 = angleppp[2];
        angleeep0 = angleeep[0];
        angleeep1 = angleeep[1];
        angleeep2 = angleeep[2];
        angleepe0 = angleepe[0];
        angleepe1 = angleepe[1];
        angleepe2 = angleepe[2];
        anglepee0 = anglepee[0];
        anglepee1 = anglepee[1];
        anglepee2 = anglepee[2];
        angleppe0 = angleppe[0];
        angleppe1 = angleppe[1];
        angleppe2 = angleppe[2];
        anglepep0 = anglepep[0];
        anglepep1 = anglepep[1];
        anglepep2 = anglepep[2];
        angleepp0 = angleepp[0];
        angleepp1 = angleepp[1];
        angleepp2 = angleepp[2];

        fq3rEEE_fq2rEE = fq3rEEE-fq2rEE;
        fq3rPPP_fq2rPP = fq3rPPP-fq2rPP;
        fq3rEEP_fq2rEE = fq3rEEP-fq2rEE;
        fq3rEPE_fq2rEP = fq3rEPE-fq2rEP;
        fq3rPEE_fq2rPE = fq3rPEE-fq2rPE;
        fq3rEPP_fq2rEP = fq3rEPP-fq2rEP;
        fq3rPEP_fq2rPE = fq3rPEP-fq2rPE;
        fq3rPPE_fq2rPP = fq3rPPE-fq2rPP;

        fqnse = fqnse2;

        erecmr = erecmr2;
        eTOpre = eTOpre2;
        fqwall = fqwall2;
        towall = towall2;
        angleee = angleee2;
        anglepp = anglepp2;
        angleepi = angleepi2;
        anglepie = anglepie2;
	
      // Return the MVA outputs and fill into histograms

      if (Use["CutsGA"]) {
         // Cuts is a special case: give the desired signal efficienciy
         Bool_t passed = reader->EvaluateMVA( "CutsGA method", effS );
         if (passed) nSelCutsGA++;
      }

      if (Use["Likelihood"   ])   histLk     ->Fill( reader->EvaluateMVA( "Likelihood method"    ) );
      if (Use["LikelihoodD"  ])   histLkD    ->Fill( reader->EvaluateMVA( "LikelihoodD method"   ) );
      if (Use["LikelihoodPCA"])   histLkPCA  ->Fill( reader->EvaluateMVA( "LikelihoodPCA method" ) );
      if (Use["LikelihoodKDE"])   histLkKDE  ->Fill( reader->EvaluateMVA( "LikelihoodKDE method" ) );
      if (Use["LikelihoodMIX"])   histLkMIX  ->Fill( reader->EvaluateMVA( "LikelihoodMIX method" ) );
      if (Use["PDERS"        ])   histPD     ->Fill( reader->EvaluateMVA( "PDERS method"         ) );
      if (Use["PDERSD"       ])   histPDD    ->Fill( reader->EvaluateMVA( "PDERSD method"        ) );
      if (Use["PDERSPCA"     ])   histPDPCA  ->Fill( reader->EvaluateMVA( "PDERSPCA method"      ) );
      if (Use["KNN"          ])   histKNN    ->Fill( reader->EvaluateMVA( "KNN method"           ) );
      if (Use["HMatrix"      ])   histHm     ->Fill( reader->EvaluateMVA( "HMatrix method"       ) );
      if (Use["Fisher"       ])   histFi     ->Fill( reader->EvaluateMVA( "Fisher method"        ) );
      if (Use["FisherG"      ])   histFiG    ->Fill( reader->EvaluateMVA( "FisherG method"       ) );
      if (Use["BoostedFisher"])   histFiB    ->Fill( reader->EvaluateMVA( "BoostedFisher method" ) );
      if (Use["LD"           ])   histLD     ->Fill( reader->EvaluateMVA( "LD method"            ) );
      if (Use["MLP"          ])   histNn     ->Fill( reader->EvaluateMVA( "MLP method"           ) );
      if (Use["MLPBFGS"      ])   histNnbfgs ->Fill( reader->EvaluateMVA( "MLPBFGS method"       ) );
      if (Use["MLPBNN"       ])   histNnbnn  ->Fill( reader->EvaluateMVA( "MLPBNN method"        ) );
      if (Use["CFMlpANN"     ])   histNnC    ->Fill( reader->EvaluateMVA( "CFMlpANN method"      ) );
      if (Use["TMlpANN"      ])   histNnT    ->Fill( reader->EvaluateMVA( "TMlpANN method"       ) );
      if (Use["DNN_GPU"]) histDnnGpu->Fill(reader->EvaluateMVA("DNN_GPU method"));
      if (Use["DNN_CPU"]) histDnnCpu->Fill(reader->EvaluateMVA("DNN_CPU method"));
      if (Use["BDT"          ])   {
				  histBdt    ->Fill( reader->EvaluateMVA( "BDT method"           ) );
 				  //cout<<reader->EvaluateMVA( "BDT method"           )<<endl; 
				  eff1->Fill(erecmr);
				  //if(evis > 30 && fqwall > 200 && nhitac < 16 && fqnse < 3){
				  tmvaR = reader->EvaluateMVA( "BDT method");
				  //}
				  //else { tmvaR = -100; }
				  //tmvaAdd -> Fill(); 
				  tt->Fill();
				  if(reader->EvaluateMVA( "BDT method"           ) < 0 ) eff2-> Fill(erecmr);
				  }
      if (Use["BDTG"         ])   histBdtG   ->Fill( reader->EvaluateMVA( "BDTG method"          ) );
      if (Use["BDTB"         ])   histBdtB   ->Fill( reader->EvaluateMVA( "BDTB method"          ) );
      if (Use["BDTD"         ])   histBdtD   ->Fill( reader->EvaluateMVA( "BDTD method"          ) );
      if (Use["BDTF"         ])   histBdtF   ->Fill( reader->EvaluateMVA( "BDTF method"          ) );
      if (Use["RuleFit"      ])   histRf     ->Fill( reader->EvaluateMVA( "RuleFit method"       ) );
      if (Use["SVM_Gauss"    ])   histSVMG   ->Fill( reader->EvaluateMVA( "SVM_Gauss method"     ) );
      if (Use["SVM_Poly"     ])   histSVMP   ->Fill( reader->EvaluateMVA( "SVM_Poly method"      ) );
      if (Use["SVM_Lin"      ])   histSVML   ->Fill( reader->EvaluateMVA( "SVM_Lin method"       ) );
      if (Use["FDA_MT"       ])   histFDAMT  ->Fill( reader->EvaluateMVA( "FDA_MT method"        ) );
      if (Use["FDA_GA"       ])   histFDAGA  ->Fill( reader->EvaluateMVA( "FDA_GA method"        ) );
      if (Use["Category"     ])   histCat    ->Fill( reader->EvaluateMVA( "Category method"      ) );
      if (Use["Plugin"       ])   histPBdt   ->Fill( reader->EvaluateMVA( "P_BDT method"         ) );

      // Retrieve also per-event error
      if (Use["PDEFoam"]) {
         Double_t val = reader->EvaluateMVA( "PDEFoam method" );
         Double_t err = reader->GetMVAError();
         histPDEFoam   ->Fill( val );
         histPDEFoamErr->Fill( err );
         if (err>1.e-50) histPDEFoamSig->Fill( val/err );
      }

      // Retrieve probability instead of MVA output
      if (Use["Fisher"])   {
         probHistFi  ->Fill( reader->GetProba ( "Fisher method" ) );
         rarityHistFi->Fill( reader->GetRarity( "Fisher method" ) );
      }

   //tmvaAdd -> Fill();

   }

   // Get elapsed time
   sw.Stop();
   std::cout << "--- End of event loop: "; sw.Print();

   // Get efficiency for cuts classifier
   if (Use["CutsGA"]) std::cout << "--- Efficiency for CutsGA method: " << double(nSelCutsGA)/theTree->GetEntries()
                                << " (for a required signal efficiency of " << effS << ")" << std::endl;

   if (Use["CutsGA"]) {

      // test: retrieve cuts for particular signal efficiency
      // CINT ignores dynamic_casts so we have to use a cuts-secific Reader function to acces the pointer
      TMVA::MethodCuts* mcuts = reader->FindCutsMVA( "CutsGA method" ) ;

      if (mcuts) {
         std::vector<Double_t> cutsMin;
         std::vector<Double_t> cutsMax;
         mcuts->GetCuts( 0.7, cutsMin, cutsMax );
         std::cout << "--- -------------------------------------------------------------" << std::endl;
         std::cout << "--- Retrieve cut values for signal efficiency of 0.7 from Reader" << std::endl;
         for (UInt_t ivar=0; ivar<cutsMin.size(); ivar++) {
            std::cout << "... Cut: "
                      << cutsMin[ivar]
                      << " < \""
                      << mcuts->GetInputVar(ivar)
                      << "\" <= "
                      << cutsMax[ivar] << std::endl;
         }
         std::cout << "--- -------------------------------------------------------------" << std::endl;
      }
   }

   // Write histograms
   
   for(Int_t ii =0 ; ii< eff1->GetNbinsX();ii++){
     if (eff1->GetBinContent(ii+1)) eff1->SetBinContent(ii+1, eff2->GetBinContent(ii+1)/ eff1->GetBinContent(ii+1));
   }
   new TCanvas();
   eff1->GetXaxis()->SetTitle("Reconstructed electron energy (MeV)");
   eff1->GetYaxis()->SetTitle("Efficiency");
   eff1->Draw();
      


   TFile *target  = new TFile( "TMVApp.root","RECREATE" );
   if (Use["Likelihood"   ])   histLk     ->Write();
   if (Use["LikelihoodD"  ])   histLkD    ->Write();
   if (Use["LikelihoodPCA"])   histLkPCA  ->Write();
   if (Use["LikelihoodKDE"])   histLkKDE  ->Write();
   if (Use["LikelihoodMIX"])   histLkMIX  ->Write();
   if (Use["PDERS"        ])   histPD     ->Write();
   if (Use["PDERSD"       ])   histPDD    ->Write();
   if (Use["PDERSPCA"     ])   histPDPCA  ->Write();
   if (Use["KNN"          ])   histKNN    ->Write();
   if (Use["HMatrix"      ])   histHm     ->Write();
   if (Use["Fisher"       ])   histFi     ->Write();
   if (Use["FisherG"      ])   histFiG    ->Write();
   if (Use["BoostedFisher"])   histFiB    ->Write();
   if (Use["LD"           ])   histLD     ->Write();
   if (Use["MLP"          ])   histNn     ->Write();
   if (Use["MLPBFGS"      ])   histNnbfgs ->Write();
   if (Use["MLPBNN"       ])   histNnbnn  ->Write();
   if (Use["CFMlpANN"     ])   histNnC    ->Write();
   if (Use["TMlpANN"      ])   histNnT    ->Write();
   if (Use["DNN_GPU"]) histDnnGpu->Write();
   if (Use["DNN_CPU"]) histDnnCpu->Write();
   if (Use["BDT"          ])   histBdt    ->Write();
   if (Use["BDTG"         ])   histBdtG   ->Write();
   if (Use["BDTB"         ])   histBdtB   ->Write();
   if (Use["BDTD"         ])   histBdtD   ->Write();
   if (Use["BDTF"         ])   histBdtF   ->Write();
   if (Use["RuleFit"      ])   histRf     ->Write();
   if (Use["SVM_Gauss"    ])   histSVMG   ->Write();
   if (Use["SVM_Poly"     ])   histSVMP   ->Write();
   if (Use["SVM_Lin"      ])   histSVML   ->Write();
   if (Use["FDA_MT"       ])   histFDAMT  ->Write();
   if (Use["FDA_GA"       ])   histFDAGA  ->Write();
   if (Use["Category"     ])   histCat    ->Write();
   if (Use["Plugin"       ])   histPBdt   ->Write();

   // Write also error and significance histos
   if (Use["PDEFoam"]) { histPDEFoam->Write(); histPDEFoamErr->Write(); histPDEFoamSig->Write(); }

   // Write also probability hists
   if (Use["Fisher"]) { if (probHistFi != 0) probHistFi->Write(); if (rarityHistFi != 0) rarityHistFi->Write(); }
   target->Close();

   std::cout << "--- Created root file: \"TMVApp.root\" containing the MVA output histograms" << std::endl;

   delete reader;

   std::cout << "==> TMVAClassificationApplication_theia is done!" << std::endl << std::endl;

   tt->Write();
   ff->Write();
   //theTree->Print();
}

int main( int argc, char** argv )
{
   TString methodList;
   for (int i=1; i<argc; i++) {
      TString regMethod(argv[i]);
      if(regMethod=="-b" || regMethod=="--batch") continue;
      if (!methodList.IsNull()) methodList += TString(",");
      methodList += regMethod;
   }
   TMVAClassificationApplication_theia(methodList);
   return 0;
}
