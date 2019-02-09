{

ifstream in;
in.open("input/fromGLOBES_flux.txt");

ifstream in2;
in2.open("input/fromGLOBES_fluxt.txt");


TFile* f1 = new TFile("input/g4lbne_FHC_FD.root");

TH1D* nue       = (TH1D*)f1->Get("nue_flux");
TH1D* nuebar    = (TH1D*)f1->Get("nuebar_flux");
TH1D* numu      = (TH1D*)f1->Get("numu_flux");
TH1D* numubar   = (TH1D*)f1->Get("numubar_flux");
TH1D* nueOsc    = (TH1D*)f1->Get("nue_fluxosc");
TH1D* nuebarOsc = (TH1D*)f1->Get("nuebar_fluxosc");
TH1D* numuOsc   = (TH1D*)f1->Get("numu_fluxosc");
TH1D* numubarOsc= (TH1D*)f1->Get("numubar_fluxosc");

   TH1D * hists[] = {nue, nuebar, numu, numubar, nueOsc, nuebarOsc, numuOsc, numubarOsc};

   for (int iHist = 0; iHist < 8; iHist++) {
     for (int iBin = 1; iBin <= hists[iHist]->GetNbinsX(); iBin++)
       hists[iHist]->SetBinContent(iBin, hists[iHist]->GetBinContent(iBin)/hists[iHist]->GetBinWidth(iBin));
   }

new TCanvas();
nue->Draw();
numu->Draw("same");

TGraph* g1 = new TGraph();
TGraph* g2 = new TGraph();
TGraph* g3 = new TGraph();
TGraph* g4 = new TGraph();
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
//cout<<aa<<" "<<bb<<" "<<cc<<" "<<dd<<" "<<ee<<" "<<ff<<" "<<gg<<endl;
if(aa>0.001 && aa< 10 && bb>0 && bb< 1000) g1->SetPoint(i, aa,bb);
if(aa>0.001 && aa< 10 && bb>0 && bb< 1000) g2->SetPoint(i, aa,cc);
if(aa>0.001 && aa< 10 && bb>0 && bb< 1000) g3->SetPoint(i, aa,ee);
if(aa>0.001 && aa< 10 && bb>0 && bb< 1000) g4->SetPoint(i, aa,ff);
i++;
}


new TCanvas();
g1->SetLineColor(kBlack);
g2->SetLineColor(kRed);
g1->SetLineWidth(2);
g2->SetLineWidth(2);

TH2F* eH = new TH2F("","flux comparison", 100,0,10,100, 10E-15, 10E-10);
eH->SetXTitle("E_{#nu} (GeV)");
eH->SetYTitle("flux (neutrinos/GeV/m2/POT)");
eH->Draw();

hists[0]->SetLineColor(kBlack);
hists[2]->SetLineColor(kRed);
hists[0]->SetLineStyle(2);
hists[2]->SetLineStyle(2);

hists[0]->Draw("hist");
hists[2]->Draw("same");
g1->Draw("same");
g2->Draw("same");

      TLegend* legend = new TLegend(0.1, 0.6, 0.25, 0.9);
      legend->AddEntry(g1,"nue flux GLOBES","l");
      legend->AddEntry(g2,"numu flux GLOBES","l");
      legend->AddEntry(nue,"nue flux GY","l");
      legend->AddEntry(numu,"numu flux GY","l");
      legend->Draw();

}
