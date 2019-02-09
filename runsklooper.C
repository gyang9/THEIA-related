#include "sklooper.h"

int main( int argc, char**argv){

  // tmva_BGfraction FHC stepN runN fluxCut enerStep tmvaStep
  //gROOT->ProcessLine(".L sklooper.C+");
  sklooper skl(Form("/home/guang/Downloads/root-6.14.02/builddir/tutorials/tmva/outputTree_reinput_%s_step%drun%d.root",argv[2], atoi(argv[3]), atoi(argv[4])));
  skl.GetTMVACut(atof(argv[1]),argv[2], atoi(argv[3]), atoi(argv[4]), atof(argv[6]),atof(argv[7]) );
  skl.Loop(atof(argv[1]), argv[2], atoi(argv[3]),atoi(argv[4]), atof(argv[5]));

}
