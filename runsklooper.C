#include "sklooper.h"

int main( int argc, char**argv){

  //gROOT->ProcessLine(".L sklooper.C+");
  sklooper skl;
  skl.GetTMVACut(atof(argv[1]));
  skl.Loop(atof(argv[1]));

}
