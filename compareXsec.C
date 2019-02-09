{

ifstream in;
in.open("input/fromGLOBES_xsec_nue_ccqe.txt");

ifstream in2;
in2.open("input/fromGLOBES_xsec_nue_ccnqe.txt");

TGraph* g1 = new TGraph();
TGraph* g2 = new TGraph();
TGraph* g3 = new TGraph("input/NEUTXsec_ccqe.txt");
TGraph* g4 = new TGraph("input/NEUTXsec_ccnqe.txt");
double aa =0;
double bb =0;
double cc =0;
double dd =0;
double ee =0;
double ff =0;
double gg =0;

double aa2 =0;
double bb2 =0;
double cc2 =0;
double dd2 =0;
double ee2 =0;
double ff2 =0;
double gg2 =0;

int i=0;
while (1){
if(in.eof()) break;
in >> aa >> bb >> cc >> dd >> ee >> ff >> gg;
cout<<aa<<" "<<bb<<" "<<cc<<" "<<dd<<" "<<ee<<" "<<ff<<" "<<gg<<endl;
aa = TMath::Power(10,aa);
if(aa>0.001 && aa< 6 && bb>0 && bb< 1000) g1->SetPoint(i, aa,bb);
i++;
}
i=0;
while (1){
if(in2.eof()) break;
in2 >> aa2 >> bb2 >> cc2 >> dd2 >> ee2 >> ff2 >> gg2;
aa2 = TMath::Power(10, aa2);
if(aa2>0.001 && aa2< 6 && bb2>0 && bb2< 1000) g2->SetPoint(i, aa2,bb2- g1->Eval(aa2) );
i++;
}


new TCanvas();
g1->SetLineColor(kBlack);
g2->SetLineColor(kRed);
g3->SetLineColor(kBlack);
g4->SetLineColor(kRed);
g3->SetLineStyle(2);
g4->SetLineStyle(2);
g1->SetLineWidth(3);
g2->SetLineWidth(4);
g3->SetLineWidth(3);
g4->SetLineWidth(4);

TH2F* eH = new TH2F("","cross section comparison", 100,0,5, 100, 0, 100);
eH->SetXTitle("E_{#nu} (GeV)");
eH->SetYTitle("#sigma/E_{#nu} ( 10^{-38} cm^{2} GeV^{-1} nucleon^{-1} )");
eH->Draw();

g1->Draw("same");
g2->Draw("same");
g3->Draw("same");
g4->Draw("same");

      TLegend* legend = new TLegend(0.1, 0.6, 0.25, 0.9);
      legend->AddEntry(g1,"nue qe GLOBES","l");
      legend->AddEntry(g2,"nue nqe GLOBES","l");
      legend->AddEntry(g3,"nue qe NEUT 5.3.6","l");
      legend->AddEntry(g4,"nue nqe NEUT 5.3.6","l");
      legend->Draw();

}
