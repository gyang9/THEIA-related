{

  gROOT->ProcessLine(".L sklooper.C+");
  sklooper skl;
  skl.GetTMVACut();
  skl.Loop();


}
