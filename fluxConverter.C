{

TString atmFlux1 = "input/hondaFlux_0.9-1.0.txt";
TString atmFlux2 = "input/hondaFlux_0.8-0.9.txt";
TString atmFlux3 = "input/hondaFlux_0.7-0.8.txt";
TString atmFlux4 = "input/hondaFlux_0.6-0.7.txt";
TString atmFlux5 = "input/hondaFlux_0.5-0.6.txt";
TString atmFlux6 = "input/hondaFlux_0.4-0.5.txt";
TString atmFlux7 = "input/hondaFlux_0.3-0.4.txt";
TString atmFlux8 = "input/hondaFlux_0.2-0.3.txt";
TString atmFlux9 = "input/hondaFlux_0.1-0.2.txt";
TString atmFlux10 = "input/hondaFlux_0.0-0.1.txt";
TString atmFlux11 = "input/hondaFlux_m0.1-0.0.txt";
TString atmFlux12 = "input/hondaFlux_m0.2-m0.1.txt";
TString atmFlux13 = "input/hondaFlux_m0.3-m0.2.txt";
TString atmFlux14 = "input/hondaFlux_m0.4-m0.3.txt";
TString atmFlux15 = "input/hondaFlux_m0.5-m0.4.txt";
TString atmFlux16 = "input/hondaFlux_m0.6-m0.5.txt";
TString atmFlux17 = "input/hondaFlux_m0.7-m0.6.txt";
TString atmFlux18 = "input/hondaFlux_m0.8-m0.7.txt";
TString atmFlux19 = "input/hondaFlux_m0.9-m0.8.txt";
TString atmFlux20 = "input/hondaFlux_m1.0-m0.9.txt";

TGraph * gAtm1_numu  = new TGraph(atmFlux1, "%lg %*lg %*lg %*lg %lg", "");
TGraph * gAtm2_numu  = new TGraph(atmFlux1, "%lg %*lg %*lg %*lg %lg", "");
TGraph * gAtm3_numu  = new TGraph(atmFlux2, "%lg %*lg %*lg %*lg %lg", "");
TGraph * gAtm4_numu  = new TGraph(atmFlux2, "%lg %*lg %*lg %*lg %lg", "");
TGraph * gAtm5_numu  = new TGraph(atmFlux3, "%lg %*lg %*lg %*lg %lg", "");
TGraph * gAtm6_numu  = new TGraph(atmFlux3, "%lg %*lg %*lg %*lg %lg", "");
TGraph * gAtm7_numu  = new TGraph(atmFlux4, "%lg %*lg %*lg %*lg %lg", "");
TGraph * gAtm8_numu  = new TGraph(atmFlux4, "%lg %*lg %*lg %*lg %lg", "");
TGraph * gAtm9_numu  = new TGraph(atmFlux5, "%lg %*lg %*lg %*lg %lg", "");
TGraph * gAtm10_numu  = new TGraph(atmFlux5, "%lg %*lg %*lg %*lg %lg", "");
TGraph * gAtm11_numu  = new TGraph(atmFlux6, "%lg %*lg %*lg %*lg %lg", "");
TGraph * gAtm12_numu  = new TGraph(atmFlux6, "%lg %*lg %*lg %*lg %lg", "");
TGraph * gAtm13_numu  = new TGraph(atmFlux7, "%lg %*lg %*lg %*lg %lg", "");
TGraph * gAtm14_numu  = new TGraph(atmFlux7, "%lg %*lg %*lg %*lg %lg", "");
TGraph * gAtm15_numu  = new TGraph(atmFlux8, "%lg %*lg %*lg %*lg %lg", "");
TGraph * gAtm16_numu  = new TGraph(atmFlux8, "%lg %*lg %*lg %*lg %lg", "");
TGraph * gAtm17_numu  = new TGraph(atmFlux9, "%lg %*lg %*lg %*lg %lg", "");
TGraph * gAtm18_numu  = new TGraph(atmFlux9, "%lg %*lg %*lg %*lg %lg", "");
TGraph * gAtm19_numu  = new TGraph(atmFlux10, "%lg %*lg %*lg %*lg %lg", "");
TGraph * gAtm20_numu  = new TGraph(atmFlux10, "%lg %*lg %*lg %*lg %lg", "");
TGraph * gAtm21_numu  = new TGraph(atmFlux11, "%lg %*lg %*lg %*lg %lg", "");
TGraph * gAtm22_numu  = new TGraph(atmFlux11, "%lg %*lg %*lg %*lg %lg", "");
TGraph * gAtm23_numu  = new TGraph(atmFlux12, "%lg %*lg %*lg %*lg %lg", "");
TGraph * gAtm24_numu  = new TGraph(atmFlux12, "%lg %*lg %*lg %*lg %lg", "");
TGraph * gAtm25_numu  = new TGraph(atmFlux13, "%lg %*lg %*lg %*lg %lg", "");
TGraph * gAtm26_numu  = new TGraph(atmFlux13, "%lg %*lg %*lg %*lg %lg", "");
TGraph * gAtm27_numu  = new TGraph(atmFlux14, "%lg %*lg %*lg %*lg %lg", "");
TGraph * gAtm28_numu  = new TGraph(atmFlux14, "%lg %*lg %*lg %*lg %lg", "");
TGraph * gAtm29_numu  = new TGraph(atmFlux15, "%lg %*lg %*lg %*lg %lg", "");
TGraph * gAtm30_numu  = new TGraph(atmFlux15, "%lg %*lg %*lg %*lg %lg", "");
TGraph * gAtm31_numu  = new TGraph(atmFlux16, "%lg %*lg %*lg %*lg %lg", "");
TGraph * gAtm32_numu  = new TGraph(atmFlux16, "%lg %*lg %*lg %*lg %lg", "");
TGraph * gAtm33_numu  = new TGraph(atmFlux17, "%lg %*lg %*lg %*lg %lg", "");
TGraph * gAtm34_numu  = new TGraph(atmFlux17, "%lg %*lg %*lg %*lg %lg", "");
TGraph * gAtm35_numu  = new TGraph(atmFlux18, "%lg %*lg %*lg %*lg %lg", "");
TGraph * gAtm36_numu  = new TGraph(atmFlux18, "%lg %*lg %*lg %*lg %lg", "");
TGraph * gAtm37_numu  = new TGraph(atmFlux19, "%lg %*lg %*lg %*lg %lg", "");
TGraph * gAtm38_numu  = new TGraph(atmFlux19, "%lg %*lg %*lg %*lg %lg", "");
TGraph * gAtm39_numu  = new TGraph(atmFlux20, "%lg %*lg %*lg %*lg %lg", "");
TGraph * gAtm40_numu  = new TGraph(atmFlux20, "%lg %*lg %*lg %*lg %lg", "");

double aa,bb,cc;
ifstream in;
in.open("input/battistFlux.txt");


ofstream out;
out.open("honda11Flux_converted_nuebar.txt",std::ios::app);

while (1){
if(in.eof()) break;
in >> aa >> bb >> cc ;
cout<<aa<<" "<<bb<<" "<<cc<<endl;
if(aa>0.8){
if(bb>0.9 && bb< 1.0) out<< aa <<" &   " << bb <<" &   " <<gAtm1_numu->Eval(aa)<<endl;
if(bb>0.8 && bb< 0.9) out<< aa <<" &   "<< bb <<" &   "<< gAtm3_numu->Eval(aa)<<endl;
if(bb>0.7 && bb< 0.8) out<< aa <<" &   "<< bb <<" &   "<< gAtm5_numu->Eval(aa)<<endl;
if(bb>0.6 && bb< 0.7) out<< aa <<" &   "<< bb <<" &   "<< gAtm7_numu->Eval(aa)<<endl;
if(bb>0.5 && bb< 0.6) out<< aa <<" &   "<< bb <<" &   "<< gAtm9_numu->Eval(aa)<<endl;
if(bb>0.4 && bb< 0.5) out<< aa <<" &   "<< bb <<" &   "<< gAtm11_numu->Eval(aa)<<endl;
if(bb>0.3 && bb< 0.4) out<< aa <<" &   "<< bb <<" &   "<< gAtm13_numu->Eval(aa)<<endl;
if(bb>0.2 && bb< 0.3) out<< aa <<" &   "<< bb <<" &   "<< gAtm15_numu->Eval(aa)<<endl;
if(bb>0.1 && bb< 0.2) out<< aa <<" &   "<< bb <<" &   "<< gAtm17_numu->Eval(aa)<<endl;

if(bb>0.0 && bb< 0.1) out<< aa <<" &   "<< bb <<" &   "<< gAtm19_numu->Eval(aa)<<endl;
if(bb>-0.1 && bb< 0.0) out<< aa <<" &   "<< bb <<" &   "<< gAtm21_numu->Eval(aa)<<endl;
if(bb>-0.2 && bb< -0.1) out<< aa <<" &   "<< bb <<" &   "<< gAtm23_numu->Eval(aa)<<endl;
if(bb>-0.3 && bb< -0.2) out<< aa <<" &   "<< bb <<" &   "<< gAtm25_numu->Eval(aa)<<endl;
if(bb>-0.4 && bb< -0.3) out<< aa <<" &   "<< bb <<" &   "<< gAtm27_numu->Eval(aa)<<endl;
if(bb>-0.5 && bb< -0.4) out<< aa <<" &   "<< bb <<" &   "<< gAtm29_numu->Eval(aa)<<endl;
if(bb>-0.6 && bb< -0.5) out<< aa <<" &   "<< bb <<" &   "<< gAtm31_numu->Eval(aa)<<endl;
if(bb>-0.7 && bb< -0.6) out<< aa <<" &   "<< bb <<" &   "<< gAtm33_numu->Eval(aa)<<endl;
if(bb>-0.8 && bb< -0.7) out<< aa <<" &   "<< bb <<" &   "<< gAtm35_numu->Eval(aa)<<endl;
if(bb>-0.9 && bb< -0.8) out<< aa <<" &   "<< bb <<" &   "<< gAtm37_numu->Eval(aa)<<endl;
if(bb>-1.0 && bb< -0.9) out<< aa <<" &   "<< bb <<" &   "<< gAtm39_numu->Eval(aa)<<endl;
}
}


cout<<"done "<<endl;



}
