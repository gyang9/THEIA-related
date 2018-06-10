#include <TFile.h>
#include <TTree.h>
#include <TString.h>
#include <TSpline.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TStyle.h>

#include "THEIALoop.hh"

int main(int argc, char* argv[])
{

   gStyle->SetOptStat(0);
  
   TFile* f = new TFile("input/combined_extra.root");
   TTree* tree = (TTree*)f->Get("h1");

   std::cout<<"preparing.."<<std::endl;
   THEIA* sLoop = new THEIA(tree);

   TString atmFlux("input/hondaFluxTruncated.txt");
   TSpline5** atmSpline = sLoop->LoadAtmFlux(atmFlux);

   TString duneFlux("input/g4lbne_FHC_FD.root");
   TSpline5** duneSpline = sLoop->LoadDuneFlux(duneFlux);   

   for (int i = 0; i < 4; i++) atmSpline[i]->SetNpx(1000);
   for (int i = 0; i < 8; i++) duneSpline[i]->SetNpx(1000);
   
   TCanvas * c1 = new TCanvas();
   TH1D * axesAtm = new TH1D("axesAtm", "Atmospheric flux splines;E_{#nu} [GeV];#Phi", 100, 0, 10);
   axesAtm->Draw("");
   axesAtm->SetMaximum(30000);
   axesAtm->SetMinimum(10);
   
   atmSpline[0]->SetLineColor(kRed);
   atmSpline[0]->Draw("");
   
   atmSpline[1]->SetLineColor(kRed+2);
   atmSpline[1]->Draw("SAME");
   
   atmSpline[2]->SetLineColor(kBlue);
   atmSpline[2]->Draw("SAME");
   
   atmSpline[3]->SetLineColor(kBlue+2);
   atmSpline[3]->Draw("SAME");
   
   TLegend * atmLegend = new TLegend(0.5, 0.5, 0.9, 0.9);
   atmLegend->SetBorderSize(0);
   atmLegend->SetFillStyle(0);
   atmLegend->AddEntry(atmSpline[0], "#nu_{e}", "l");
   atmLegend->AddEntry(atmSpline[1], "anti-#nu_{e}", "l");
   atmLegend->AddEntry(atmSpline[2], "#nu_{#mu}", "l");
   atmLegend->AddEntry(atmSpline[3], "anti-#nu_{#mu}", "l");
   atmLegend->Draw();
   
   c1->SetLogy();

   TCanvas * c2 = new TCanvas();
   TH1D * axesDuneOsc = new TH1D("axesDuneOsc", "DUNE oscillated flux splines;E_{#nu} [GeV];#Phi", 100, 0, 10);
   axesDuneOsc->Draw("");
   axesDuneOsc->SetMaximum(0.2);
   axesDuneOsc->SetMinimum(0.);
   
   duneSpline[6]->SetLineColor(kRed);
   duneSpline[6]->Draw("");
   
   duneSpline[5]->SetLineColor(kRed+2);
   duneSpline[5]->Draw("SAME");
   
   duneSpline[4]->SetLineColor(kBlue);
   duneSpline[4]->Draw("SAME");
   
   duneSpline[7]->SetLineColor(kBlue+2);
   duneSpline[7]->Draw("SAME");
   
   TLegend * duneLegend = new TLegend(0.5, 0.5, 0.9, 0.9);
   duneLegend->SetBorderSize(0);
   duneLegend->SetFillStyle(0);
   duneLegend->AddEntry(duneSpline[4], "#nu_{e}", "l");
   duneLegend->AddEntry(duneSpline[5], "anti-#nu_{e}", "l");
   duneLegend->AddEntry(duneSpline[6], "#nu_{#mu}", "l");
   duneLegend->AddEntry(duneSpline[7], "anti-#nu_{#mu}", "l");
   duneLegend->Draw();
  
   c2->SetLogy();  
 
   c1->SaveAs("atmFluxSplines.png");
   c2->SaveAs("duneSpline.png");
   c1->SaveAs("atmFluxSplines.C");
   c2->SaveAs("duneSpline.C");

}
