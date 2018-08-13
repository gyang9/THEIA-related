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

   TString atmFlux("input/hondaFluxTruncated_new.txt");
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
   
   atmSpline[0]->SetLineColor(1);
   atmSpline[0]->SetLineWidth(2);
   atmSpline[0]->Draw("");
   
   atmSpline[1]->SetLineColor(2);
   atmSpline[1]->SetLineWidth(2);
   atmSpline[1]->Draw("SAME");
   
   atmSpline[2]->SetLineColor(3);
   atmSpline[2]->SetLineWidth(2);
   atmSpline[2]->Draw("SAME");
   
   atmSpline[3]->SetLineColor(4);
   atmSpline[3]->SetLineWidth(2);
   atmSpline[3]->Draw("SAME");
   
   TLegend * atmLegend = new TLegend(0.5, 0.5, 0.9, 0.9);
   atmLegend->SetBorderSize(0);
   atmLegend->SetFillStyle(0);
   atmLegend->AddEntry(duneSpline[0], "#nu_{e}", "l");
   atmLegend->AddEntry(duneSpline[1], "anti-#nu_{e}", "l");
   atmLegend->AddEntry(duneSpline[2], "#nu_{#mu}", "l");
   atmLegend->AddEntry(duneSpline[3], "anti-#nu_{#mu}", "l");
   atmLegend->Draw();
   
   c1->SetLogy();

   TCanvas * c2 = new TCanvas();
   TH1D * axesDuneOsc = new TH1D("axesDuneOsc", "DUNE oscillated flux splines;E_{#nu} [GeV];#Phi", 100, 0, 10);
   axesDuneOsc->Draw("");
   axesDuneOsc->SetMaximum(0.2);
   axesDuneOsc->SetMinimum(0.);
   
   duneSpline[2]->SetLineColor(3);
   duneSpline[2]->SetLineWidth(2);
   duneSpline[2]->Draw("");
   
   duneSpline[1]->SetLineColor(2);
   duneSpline[1]->SetLineWidth(2);
   duneSpline[1]->Draw("SAME");
   
   duneSpline[0]->SetLineColor(1);
   duneSpline[0]->SetLineWidth(2);
   duneSpline[0]->Draw("SAME");
   
   duneSpline[3]->SetLineColor(4);
   duneSpline[3]->SetLineWidth(2);
   duneSpline[3]->Draw("SAME");
   
   TLegend * duneLegend = new TLegend(0.5, 0.5, 0.9, 0.9);
   duneLegend->SetBorderSize(0);
   duneLegend->SetFillStyle(0);
   duneLegend->AddEntry(duneSpline[0], "#nu_{e}", "l");
   duneLegend->AddEntry(duneSpline[1], "anti-#nu_{e}", "l");
   duneLegend->AddEntry(duneSpline[2], "#nu_{#mu}", "l");
   duneLegend->AddEntry(duneSpline[3], "anti-#nu_{#mu}", "l");
   duneLegend->Draw();
  
   c2->SetLogy();  
 
   c1->SaveAs("atmFluxSplines.png");
   c2->SaveAs("duneSpline.png");
   c1->SaveAs("atmFluxSplines.C");
   c2->SaveAs("duneSpline.C");

}
