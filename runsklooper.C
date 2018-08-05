#include "sklooper.h"

int main( int argc, char**argv){

  //gROOT->ProcessLine(".L sklooper.C+");
  sklooper skl(Form("/home/gyang/Downloads/root/builddir/tutorials/tmva/outputTree_reinput_step%drun%d.root",atoi(argv[2]),atoi(argv[3])));
  skl.GetTMVACut(atof(argv[1]),atoi(argv[2]),atoi(argv[3]));
  skl.Loop(atof(argv[1]),atoi(argv[2]),atoi(argv[3]));

}
