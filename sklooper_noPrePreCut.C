#define sklooper_cxx
#include "sklooper.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH2D.h>
#include <iostream>
#include <TGraph.h>
#include <TH1.h>

void sklooper::GetTMVACut(double factor, int stepN, int runN)
{

   Double_t erecmr, fluxWeight[2], tmvaMR, fqwall, towall;
   Float_t  pnu[100];
   Int_t sigCategory, bkgCategory;
   Float_t evis;
   UInt_t nhitac;
   Int_t mode;
   Int_t fqnse;
   Int_t ipnu[100];
   Int_t fqmrnring[100];

   std::cout<<"factor input here is "<<factor<<" "<<stepN<<" "<<runN<<std::endl;
   TFile f(Form("/home/gyang/Downloads/root/builddir/tutorials/tmva/outputTree_reinput_step%drun%d.root",stepN,runN));
   TTree*t = (TTree*)f.Get("h1");

   t->SetBranchAddress("erecmr", &erecmr);
   t->SetBranchAddress("fluxWeight", &fluxWeight);
   t->SetBranchAddress("tmvaMR0", &tmvaMR);
   t->SetBranchAddress("fqwall", &fqwall);
   t->SetBranchAddress("towall", &towall);
   t->SetBranchAddress("evis", &evis);
   t->SetBranchAddress("nhitac", &nhitac);
   t->SetBranchAddress("sigCategory", &sigCategory);
   t->SetBranchAddress("bkgCategory", &bkgCategory);
   t->SetBranchAddress("pnu", &pnu);
   t->SetBranchAddress("mode", &mode);
   t->SetBranchAddress("fqnse",&fqnse);
   t->SetBranchAddress("ipnu", &ipnu);
   t->SetBranchAddress("fqmrnring", &fqmrnring);

   Long64_t nbytes = 0, nb = 0;
   Int_t NofEvent = 100000; //t->GetEntries();

   for(Int_t i=0;i<100;i++){
	for(Int_t j=0;j<100;j++){
        c_ss[i][j]=0;
        c_bb[i][j]=0;
	}
   curr_sOb[i]=-100;
   curr_sEff[i]=100;
   locTMVA[i]=0;
   c_sss[i] = 0;
   c_bbb[i] = 0;
   }

   for (Long64_t jentry=0; jentry<NofEvent;jentry++) {
      t->GetEntry(jentry);

      if (jentry % 100000 == 0) {std::cout << jentry << " events processed" << std::endl;}

      //std::cout<<"event : "<<jentry<<" erecmr sigCategory towall evis nhitac fluxWeight[0] fluxWeight[1] tmvaMR fqnse : "<<erecmr<<" "<<sigCategory<<" "<<fqwall<<" "<<evis<<" "<<nhitac<<" "<<fluxWeight[0]<<" "<<fluxWeight[1]<<" "<<tmvaMR<<" "<<fqnse<<std::endl;

      if(fqwall>200 
	&& evis > 30 
	&& nhitac < 16 
	&& fqnse <= 2 
//	&& (fqmrnring[0] == 1)
	){
	for(Int_t iii=0;iii<100;iii++){
	  if(erecmr>iii*0.1 && erecmr<(iii+1)*0.1 ) {if(sigCategory>=0)c_sss[iii]++; if(bkgCategory>=0)c_bbb[iii]++;}
          for(Int_t ii=0;ii<80;ii++){
                if(erecmr>iii*0.1 && erecmr<(iii+1)*0.1 && tmvaMR > -0.4 + 0.01*ii) {if(sigCategory>=0)c_ss[iii][ii]++; if(bkgCategory>=0)c_bb[iii][ii]++;}
	  }
        }
      }
   }

   std::cout<<"trying to see the results of tmva cuts with variable "<<factor<<" ... "<<std::endl;
   for(Int_t ii=0;ii<100;ii++){
        for(Int_t jj=0;jj<80;jj++){
                if(c_ss[ii][jj]/sqrt(c_ss[ii][jj]+c_bb[ii][jj]+c_bb[ii][jj]*c_bb[ii][jj]*factor)>curr_sOb[ii] ) {curr_sOb[ii] = c_ss[ii][jj]/sqrt(c_ss[ii][jj]+c_bb[ii][jj]+c_bb[ii][jj]*c_bb[ii][jj]*factor); locTMVA[ii] = jj; std::cout<<ii<<" "<<c_ss[ii][jj]/sqrt(c_ss[ii][jj]+c_bb[ii][jj]+c_bb[ii][jj]*c_bb[ii][jj]*factor)<<std::endl; }
                //if(c_ss[ii][jj]/sqrt(c_ss[ii][jj]+c_bb[ii][jj]+c_bb[ii][jj]*c_bb[ii][jj]*atof(gApplication->Argv(4)))>curr_sOb[ii] ) {curr_sOb[ii] = c_ss[ii][jj]/sqrt(c_ss[ii][jj]+c_bb[ii][jj]+c_bb[ii][jj]*c_bb[ii][jj]*atof(gApplication->Argv(4))); locTMVA[ii] = jj; std::cout<<ii<<" "<<c_ss[ii][jj]/sqrt(c_ss[ii][jj]+c_bb[ii][jj]+c_bb[ii][jj]*c_bb[ii][jj]*atof(gApplication->Argv(4)))<<std::endl; }
		//std::cout<<c_ss[ii][jj]/c_sss[ii]<<std::endl;
		//if(TMath::Abs(c_ss[ii][jj]/c_sss[ii] - atof(gApplication->Argv(4)) ) <curr_sEff[ii] ) {curr_sEff[ii] = TMath::Abs(c_ss[ii][jj]/c_sss[ii] - atof(gApplication->Argv(4))); locTMVA[ii] = jj; std::cout<<ii<<" "<<TMath::Abs(c_ss[ii][jj]/c_sss[ii] - atof(gApplication->Argv(4)))<<std::endl; }
        }
   }

   std::cout<<std::endl;
   std::cout<<"locations of TMVAs for every 0.1 GeV are:  ";
   for(Int_t ii=0;ii<100;ii++){std::cout<< " "<< locTMVA[ii]*0.01 - 0.4 <<"  ";}
   std::cout<<std::endl;

}

void sklooper::Loop(double factor, int stepN, int runN)
{

  std::cout << "I am here!!!!" << std::endl;

  //   In a ROOT session, you can do:
//      Root > .L sklooper.C
//      Root > sklooper t
//      Root > t.GetEntry(12); // Fill t data members with entry number 12
//      Root > t.Show();       // Show values of entry 12
//      Root > t.Show(16);     // Read and show values of entry 16
//      Root > t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;

   TFile* outfile = new TFile(Form("outfilesk_%f_file_step%drun%d.root", factor,stepN,runN),"RECREATE");
   TH2D* hzvsr = new TH2D("hzvsr","True Z vs R",40,0.,4000.,80,-4000.,4000.);
   TH2D* hfqzvsr = new TH2D("hfqzvsr","FiTQun Z vs R",40,0.,4000.,80,-4000.,4000.);

   const int nnutypes = 4;
   TString nunames[nnutypes] = {"nue","nuebar","numu","numubar"};
   const int ninttypes = 4;
   TString intnames[ninttypes] = {"ccqe","ccpip","ccother","nc"};

   TH1D* htruefv [nnutypes][ninttypes];
   TH1D* htruefvOsc [nnutypes][ninttypes];

   TH1D* hprecut [nnutypes][ninttypes];
   TH1D* hprecutrec [nnutypes][ninttypes];
   TH1D* hpostcutrec[nnutypes][ninttypes];
   TH1D* hpostcutrecDB[nnutypes][ninttypes];
   TH1D* hprecutrecDB[nnutypes][ninttypes];
   TH1D* hpostcutrecNoFlux[nnutypes][ninttypes];
   TH1D* hpostcutrecDBNoFlux[nnutypes][ninttypes];
   TH1D* hprecutrecNoFlux[nnutypes][ninttypes];
   TH1D* hprecutrecDBNoFlux[nnutypes][ninttypes];

   TH1D* h1rprecut [nnutypes][ninttypes];
   TH1D* h1rprecutrec [nnutypes][ninttypes];
   TH1D* h1rpostcutrec[nnutypes][ninttypes];
   TH1D* h1rprecutDB [nnutypes][ninttypes];
   TH1D* h1rprecutrecDB [nnutypes][ninttypes];
   TH1D* h1rpostcutrecDB[nnutypes][ninttypes];

   TH2D* hpi0precut[nnutypes][ninttypes];
   TH2D* hpi0postcut[nnutypes][ninttypes];
   TH2D* h1rpi0precut[nnutypes][ninttypes];

   const int ndecaye2 = 3;
   const int nrings2 = 2;
   const int maxcomb = 8;
   TH1D* h2precut [nnutypes][ninttypes][ndecaye2][nrings2][maxcomb];
   TH1D* h2precutrec [nnutypes][ninttypes][ndecaye2][nrings2][maxcomb];
   TH1D* h2postcutrec[nnutypes][ninttypes][ndecaye2][nrings2][maxcomb];

   TH2D* htrueToreco [nnutypes][ninttypes];
   TH2D* htrueTorecoPRE [nnutypes][ninttypes];
   TH2D* htrueTorecoNoFlux [nnutypes][ninttypes];

   const int nbins = 26;
   double binedges[nbins+1] = {0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 15.0, 20.0, 40.0,60.0, 100.0};

   std::cout<<"binned one out of two.. "<<std::endl;
   const int nbinsPost = 10;
   //double binedgesPost[nbinsPost+1] = {0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0};
   double binedgesPost[nbinsPost+1] = {0.175,0.6,1.175,1.75,2.5,3.5,4.5,7.5,10.0,60.0, 100.0};

   for (int nt=0; nt<nnutypes; nt++) {
     TString hprefix1 = nunames[nt];
     hprefix1 += "_";
     for (int it=0; it<ninttypes; it++) {
       TString hprefix = hprefix1;
       hprefix += intnames[it];
       TString hname = hprefix + "_truefv";
       htruefv[nt][it] = new TH1D(hname,hname,nbins,binedges);

       hname = hprefix + "_truefvOsc";
       htruefvOsc[nt][it] = new TH1D(hname,hname,nbins,binedges);

       hname = hprefix + "_precut";
       hprecut[nt][it] = new TH1D(hname,hname,nbins,binedges);
       hname = hprefix + "_precutrec";
       hprecutrec[nt][it] = new TH1D(hname,hname,nbinsPost,binedgesPost);
       hname = hprefix + "_postcutrec";
       hpostcutrec[nt][it] = new TH1D(hname,hname,nbinsPost,binedgesPost);
       hname = hprefix + "_precutrecDB";
       hprecutrecDB[nt][it] = new TH1D(hname,hname,62,0.25,8);
       hname = hprefix + "_postcutrecDB";
       hpostcutrecDB[nt][it] = new TH1D(hname,hname,62,0.25,8);
       hname = hprefix + "_1rprecut";
       h1rprecut[nt][it] = new TH1D(hname,hname,nbins,binedges);
       hname = hprefix + "_1rprecutrec";
       h1rprecutrec[nt][it] = new TH1D(hname,hname,nbinsPost,binedgesPost);
       hname = hprefix + "_1rpostcutrec";
       h1rpostcutrec[nt][it] = new TH1D(hname,hname,nbinsPost,binedgesPost);
       hname = hprefix + "_1rprecutrecDB";
       h1rprecutrecDB[nt][it] = new TH1D(hname,hname,62,0.25,8);
       hname = hprefix + "_1rpostcutrecDB";
       h1rpostcutrecDB[nt][it] = new TH1D(hname,hname,62,0.25,8);
       hname = hprefix + "_trueToreco";
       htrueToreco[nt][it] = new TH2D(hname,hname,100,0,10,100,0,10);
       hname = hprefix + "_trueTorecoPRE";
       htrueTorecoPRE[nt][it] = new TH2D(hname,hname,100,0,10,100,0,10);

       hname = hprefix + "_precutrecNoFlux";
       hprecutrecNoFlux[nt][it] = new TH1D(hname,hname,nbins,binedges);
       hname = hprefix + "_precutrecDBNoFlux";
       hprecutrecDBNoFlux[nt][it] = new TH1D(hname,hname,62,0.25,8);
       hname = hprefix + "_postcutrecNoFlux";
       hpostcutrecNoFlux[nt][it] = new TH1D(hname,hname,nbinsPost,binedgesPost);
       hname = hprefix + "_postcutrecDBNoFlux";
       hpostcutrecDBNoFlux[nt][it] = new TH1D(hname,hname,62,0.25,8);
       hname = hprefix + "_trueTorecoNoFlux";
       htrueTorecoNoFlux[nt][it] = new TH2D(hname,hname,100,0,10,100,0,10);

       hname = hprefix + "_hpi0precut";
       hpi0precut[nt][it] = new TH2D(hname,hname,30,0,300,40,0,400);
       hname = hprefix + "_hpi0postcut";
       hpi0postcut[nt][it] = new TH2D(hname,hname,30,0,300,40,0,400);
       hname = hprefix + "_h1rpi0precut";
       h1rpi0precut[nt][it] = new TH2D(hname,hname,30,0,300,40,0,400);

       int ncomb[nrings2] = {4,8};
       for (int ide=0; ide<ndecaye2; ide++) {
	 TString hsuffix1 = "_de";
	 hsuffix1 += ide;
	 for (int ir=0; ir<nrings2; ir++) {
	   TString hsuffix2 = hsuffix1;
	   hsuffix2 += "_nrings";
	   hsuffix2 += (ir+2);
	   for (int icomb=0; icomb<ncomb[ir]; icomb++) {
	     TString hsuffix3 = hsuffix2;
	     hsuffix3 += "_pid";
	     hsuffix3 += icomb;
	     hname = hprefix + "_mr_precut" + hsuffix3;
	     h2precut[nt][it][ide][ir][icomb] = new TH1D(hname,hname,nbins,binedges);
	     hname = hprefix + "_mr_precutrec" + hsuffix3;
	     h2precutrec[nt][it][ide][ir][icomb] = new TH1D(hname,hname,nbins,binedges);
	     hname = hprefix + "_mr_postcutrec" + hsuffix3;
	     h2postcutrec[nt][it][ide][ir][icomb] = new TH1D(hname,hname,nbinsPost,binedgesPost);
	   }
	 }
       }
     }
   }

   TH1D* heres = new TH1D("heres","nue CCQE Energy Pull",1000,-1.,1.);
   TH1D* h2eres = new TH1D("heres_2r","nue CCQE Energy Pull (2R)",1000,-1.,1.);
   TH1D* h3eres = new TH1D("heres_3r","nue CCQE Energy Pull (3R)",1000,-1.,1.);
   TH1D* htruefvpi0 = new TH1D("htruefvpi0","NC pi0 momentum precut",10,0.,1000.);
   TH1D* hpostcutpi0 = new TH1D("hpostcutpi0","NC pi0 momentum postcut",10,0.,1000.);

   TH1D* hTMVA = new TH1D("TMVA_values","TMVA_values",100,0,10);
   for(Int_t ii=0;ii<hTMVA->GetNbinsX();ii++) {hTMVA -> SetBinContent(ii+1, locTMVA[ii+1]*0.01-0.4 );}

   TFile fff("simpleRatio.root");
   //TGraph* ratioNC       = (TGraph*)fff.Get("nc");
   //TGraph* ratioNUECCQE  = (TGraph*)fff.Get("nueccqe");
   //TGraph* ratioNUMU     = (TGraph*)fff.Get("numu");
   //TGraph* ratioNUECCNQE = (TGraph*)fff.Get("nueccnqe");

   TH1D* hratioNC       = (TH1D*)fff.Get("nc");
   TH1D* hratioNUECCQE  = (TH1D*)fff.Get("nueccqe");
   TH1D* hratioNUMU     = (TH1D*)fff.Get("numu");
   TH1D* hratioNUECCNQE = (TH1D*)fff.Get("nueccnqe");

   TGraph* ratioNC = new TGraph(hratioNC);
   TGraph* ratioNUECCQE = new TGraph(hratioNUECCQE);
   TGraph* ratioNUMU = new TGraph(hratioNUMU);
   TGraph* ratioNUECCNQE = new TGraph(hratioNUECCNQE);

   //std::cout<<hratioNC->GetBinContent(2)<<" "<<ratioNC->Eval(1)<<" "<<ratioNUMU->Eval(1)<<std::endl;

   Long64_t nentries = fChain->GetEntriesFast()/10.;

   Long64_t nbytes = 0, nb = 0;
   Int_t ccount[nnutypes][ninttypes]={};
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;

      if (jentry % 100000 == 0) {std::cout << jentry << " events processed" << std::endl;}

      double ppi0 = -1.;
      int ntpi0 = 0;
      for (int ipart=0; ipart<npar; ipart++) {
	if ((ipv[ipart] == 7)&&(light_flag[ipart]==1)) {
	  ntpi0++;
	  ppi0 = pmomv[ipart];
	}
      }
      for (int ipart=0; ipart<npar2; ipart++) {
	if (ipv2[ipart] == 7) {
	  ntpi0++;
	  ppi0 = pmomv2[ipart];
	}
      }

      double xpos = fq1rpos[0][1][0];
      double ypos = fq1rpos[0][1][1];
      double zpos = fq1rpos[0][1][2];
      double rpos = sqrt(xpos*xpos+ypos*ypos);
      double fqwall = TMath::Min(1690.-rpos,TMath::Min(1810.-zpos,1810.+zpos));
      //      std::cout << "wall, fqwall, rpos, zpos, ypos, xpos = " << wall << ", " << fqwall << ", " << rpos << ", " << zpos << ", " << ypos << ", " << xpos << std::endl;

      hfqzvsr->Fill(rpos,zpos);
      hzvsr->Fill(sqrt(posv[0]*posv[0]+posv[1]*posv[1]),posv[2]);

      double lemu = fq1rnll[0][2]-fq1rnll[0][1];
      double lpie = fq1rnll[0][1]-fqpi0nll[0];
      double lpimu = fq1rnll[0][2]-fq1rnll[0][3];

      double pe = fq1rmom[0][1];
      double me = 0.5109989461;
      double ee = sqrt(pe*pe+me*me);
      double mp = 938.2720813;
      double mn = 939.5654133;

      double costhbeam = fq1rdir[0][1][0]*dirnu[0][0]
			      + fq1rdir[0][1][1]*dirnu[0][1]
			      + fq1rdir[0][1][2]*dirnu[0][2];

      double erec = erecmr; //(me*me+mn*mn-mp*mp-2*mn*ee)/-2./(mn-ee+pe*costhbeam)/1000.;
      //      double erec = (me*me-2*mn*ee)/-2./(mn-ee+pe*costhbeam);
      //double erec = (mn*ee-me*me/2.)/(mn-ee+pe*costhbeam);

      // neutrino ntype
      int nutype = -1;
      if (ipnu[0] == 12) { // nue
	nutype = 0;
      } else if (ipnu[0] == -12) { // nuebar
	nutype = 1;
      } else if (ipnu[0] == 14) { // numu
	nutype = 2;
      } else if (ipnu[0] == -14) { // numubar
	nutype = 3;
      }

      // interaction type
      int inttype = -1;
      if ((abs(mode)==1)||(abs(mode)==2)) { // CCQE
	inttype = 0;
      } else if ((abs(mode)==11)||(abs(mode)==13)||(abs(mode)==16)) { // CCpi+
	inttype = 1;
      } else if (abs(mode)<30) { // CCother
	inttype = 2;
      } else if ((abs(mode)>30)) { // NC
	inttype = 3;
      }

      // neutrinos in FV
      if (wallv>200) {
	htruefv[nutype][inttype]->Fill(pnu[0],fluxWeight[1]);
        htruefvOsc[nutype][inttype]->Fill(pnu[0],fluxWeight[1]);
      }

      // pi0 efficiency
      if ((nhitac<16)
	  && (fqwall > 200.)
	  && (evis>30)
	  //&& (fq1rmom[0][1]>30.)
	  //&& (fqnse == 1)
	  && (fqnse < 2)
	 ) {
	if ((inttype == 3)&&(ntpi0 == 1)) {
	  htruefvpi0->Fill(ppi0);
	  //if ((lpie > 175 - 0.875*fqpi0mass[0])
	  if( (tmvaMR > 0)
	      //&&(fq1rmom[0][1]<1000.)
	      ) {
	  //	  hpostcutrec[nutype][inttype]->Fill(erec);
	    hpostcutpi0->Fill(ppi0);
	  }
	}
      }

      bool passed = false;
      bool passed1r = false;
      switch(stepN){
	case 1: 
		if(nhitac<16 && wall > 200 && evis > 100 && nring == 1 && ip[0] == 2 && nmue == 0) {passed = true; passed1r = true;}
		break;
	case 2: 
		if(nhitac<16 && fqwall > 200 && fq1rmom[0][1] > 30 && fqmrnring[0] == 1 && fq1rnll[0][2]-fq1rnll[0][1] > fq1rmom[0][1]*0.2 && fqnse < 2) {passed = true; passed1r = true;}
		break;
	case 3:
		switch(runN){
		  case 1:
			if(nhitac<16 && fqwall > 200 && fq1rmom[0][1] > 30 && fqmrnring[0] == 1 && fq1rnll[0][2]-fq1rnll[0][1] > fq1rmom[0][1]*0.2 && fqnse == 1) {passed = true; passed1r = true;}
			break;
		  case 2:
			if(nhitac<16 && fqwall > 200 && fq1rmom[0][1] > 30 && fqmrnring[0] == 1 && fq1rnll[0][2]-fq1rnll[0][1] > fq1rmom[0][1]*0.2 && fqnse == 2) {passed = true; passed1r = true;}
			break;
		}
		break;
        case 4:
                switch(runN){
                  case 1:
                        if(nhitac<16 && fqwall > 200 && fq1rmom[0][1] > 30 && fqmrnring[0] == 1 && fqnse == 1) {passed = true; passed1r = true;}
			break;
                  case 2:
                        if(nhitac<16 && fqwall > 200 && fq1rmom[0][1] > 30 && fqmrnring[0] == 1 && fqnse == 2) {passed = true; passed1r = true;}
			break;
		}
		break;
        case 5:
                switch(runN){
                  case 1:
                        if(nhitac<16 && fqwall > 200 && fq1rmom[0][1] > 30 && fqmrnring[0] == 2 && fqnse == 1) {passed = true; passed1r = true;}
			break;
                  case 2:
                        if(nhitac<16 && fqwall > 200 && fq1rmom[0][1] > 30 && fqmrnring[0] == 2 && fqnse == 2) {passed = true; passed1r = true;}
			break;
                  case 3:
                        if(nhitac<16 && fqwall > 200 && fq1rmom[0][1] > 30 && fqmrnring[0] == 3 && fqnse == 1) {passed = true; passed1r = true;}
			break;
                  case 4:
                        if(nhitac<16 && fqwall > 200 && fq1rmom[0][1] > 30 && fqmrnring[0] == 3 && fqnse == 2) {passed = true; passed1r = true;}
			break;
		}
		break;
      }


      // all included
      if (passed) {

        //erecmr = pnu[0];
        //std::cout<<pnu[0]<<" "<<erecmr<<std::endl;
	/*
        if(nutype == 0 && inttype != 3) htrueTorecoPRE[nutype][inttype]->Fill(pnu[0],erecmr, fluxWeight[1]);
	else htrueTorecoPRE[nutype][inttype]->Fill(pnu[0],erecmr, fluxWeight[1]);

        if(nutype == 0 && inttype != 3) hprecut[nutype][inttype]->Fill(pnu[0], fluxWeight[1]);
	else hprecut[nutype][inttype]->Fill(pnu[0], fluxWeight[1]);

	hprecutrecDB[nutype][inttype]->Fill(erecmr, fluxWeight[1]);

        if(nutype == 0 && inttype != 3) hprecutrec[nutype][inttype]->Fill(erecmr, fluxWeight[1]);
	else hprecutrec[nutype][inttype]->Fill(erecmr, fluxWeight[1]);
	*/

        double factorAdd = 1;
	if(abs(mode)> 30 ) factorAdd = ratioNC->Eval(erecmr);
        if((abs(mode)==1)||(abs(mode)==2)  && ipnu[0]==12) factorAdd = ratioNUECCQE->Eval(erecmr);
        if(abs(mode)<30 && abs(ipnu[0])==14) factorAdd = ratioNUMU->Eval(erecmr);
        if(abs(mode)!=1  && abs(mode)!=2 && abs(ipnu[0])==12) factorAdd = ratioNUECCNQE->Eval(erecmr);
        //std::cout<<pnu[0]<<"  "<<factorAdd<<std::endl;
	if(factorAdd<0.00000000001 || factorAdd>10) factorAdd = 1;

	htrueTorecoPRE[nutype][inttype]->Fill(pnu[0],erecmr, fluxWeight[1]*(1./factorAdd));
	hprecut[nutype][inttype]->Fill(pnu[0], fluxWeight[1]*(1./factorAdd));
	hprecutrecDB[nutype][inttype]->Fill(erecmr, fluxWeight[1]*(1./factorAdd));
	hprecutrec[nutype][inttype]->Fill(erecmr, fluxWeight[1]*(1./factorAdd));

        if ((inttype==0)&&(nutype==0)) heres->Fill((erecmr-pnu[0])/pnu[0]);

        hprecutrecNoFlux[nutype][inttype]->Fill(erecmr);
        hprecutrecDBNoFlux[nutype][inttype]->Fill(erecmr);

        hpi0precut[nutype][inttype]->Fill(fqpi0mass[0],lpie,fluxWeight[1]*(1./factorAdd));

	//std::cout<<"tmva variable for nutype& inttype "<<nutype<<" "<<inttype<<" "<<tmvaMR<<std::endl;
	for(Int_t innLoop=0;innLoop<100;innLoop++){
	//std::cout<<"testing locTMVA no."<<innLoop<<" "<<locTMVA[innLoop]*0.01-0.4<<std::endl;
	if( 
        erecmr>0.1*innLoop && erecmr<0.1*(innLoop+1) && 
	tmvaMR>locTMVA[innLoop]*0.01-0.4 
	) 
	  {
	  if(nutype == 0 && inttype != 3) htrueToreco[nutype][inttype]->Fill(pnu[0],erecmr, fluxWeight[1]*(1./factorAdd));
	  else htrueToreco[nutype][inttype]->Fill(pnu[0],erecmr, fluxWeight[1]*(1./factorAdd));
	  if(nutype == 0 && inttype != 3) hpostcutrec[nutype][inttype]->Fill(erecmr, fluxWeight[1]*(1./factorAdd));
	  else hpostcutrec[nutype][inttype]->Fill(erecmr, fluxWeight[1]*(1./factorAdd));
          if(nutype == 0 && inttype != 3) hpostcutrecDB[nutype][inttype]->Fill(erecmr, fluxWeight[1]*(1./factorAdd));
	  else hpostcutrecDB[nutype][inttype]->Fill(erecmr, fluxWeight[1]*(1./factorAdd));
	  ccount[nutype][inttype]++;

       	  hpi0postcut[nutype][inttype]->Fill(fqpi0mass[0],lpie,fluxWeight[1]*(1./factorAdd));

          htrueTorecoNoFlux[nutype][inttype]->Fill(pnu[0],erecmr);
          hpostcutrecNoFlux[nutype][inttype]->Fill(erecmr);
          hpostcutrecDBNoFlux[nutype][inttype]->Fill(erecmr);
	  }
	}

        //if (fq1rmom[0][1]<500.) {
        //  if (lpie < 125 - 0.875*fqpi0mass[0]) {
        //    hpostcutrec[nutype][inttype]->Fill(erec);
        //  }
        //} else if (fq1rmom[0][1]<1000.) {
        //  if (lpie < 150 - 0.6*fqpi0mass[0]) {
        //    hpostcutrec[nutype][inttype]->Fill(erec);
        //  }
        //} else if (fq1rmom[0][1]>=1000.) {
        //  if (lpie < 100) {
        //    hpostcutrec[nutype][inttype]->Fill(erec);
        //  }
        //}

      }


      // 1-ring e-like preselection
      if (passed1r) {

	h1rprecut[nutype][inttype]->Fill(pnu[0], fluxWeight[1]);	
	h1rprecutrec[nutype][inttype]->Fill(erecmr, fluxWeight[1]);	
        h1rprecutrecDB[nutype][inttype]->Fill(erecmr, fluxWeight[1]);

	//if ((inttype==0)&&(nutype==0)) heres->Fill((erec-pnu[0])/pnu[0]);

        //if(tmvaMR>0) {
        //  h1rpostcutrec[nutype][inttype]->Fill(erec);
        //}

	//std::cout<<"testing lpie fqpi0mass[0] and fq1rmom[0][1] "<<lpie<<" "<< fqpi0mass[0] <<" "<< fq1rmom[0][1]<<std::endl;
	h1rpi0precut[nutype][inttype]->Fill(fqpi0mass[0],lpie,fluxWeight[1]);	

	if (fq1rmom[0][1]<500.) {
	  if (lpie < 125 - 0.875*fqpi0mass[0]) {
	    h1rpostcutrec[nutype][inttype]->Fill(erecmr,fluxWeight[1]);
            h1rpostcutrecDB[nutype][inttype]->Fill(erecmr,fluxWeight[1]);
	  }
	} else if (fq1rmom[0][1]<1000.) {
	  if (lpie < 150 - 0.6*fqpi0mass[0]) {
	    h1rpostcutrec[nutype][inttype]->Fill(erecmr,fluxWeight[1]);
            h1rpostcutrecDB[nutype][inttype]->Fill(erecmr,fluxWeight[1]);
	  }
	} else if (fq1rmom[0][1]>=1000.) {
	  if (lpie < 100) {
	    h1rpostcutrec[nutype][inttype]->Fill(erecmr,fluxWeight[1]);
            h1rpostcutrecDB[nutype][inttype]->Fill(erecmr,fluxWeight[1]);
	  }
	}

      }

      // Multi-ring

      double xpos2 = fqmrpos[0][0][0];
      double ypos2 = fqmrpos[0][0][1];
      double zpos2 = fqmrpos[0][0][2];
      double rpos2 = sqrt(xpos2*xpos2+ypos2*ypos2);
      double fqwall2 = TMath::Min(1690.-rpos2,TMath::Min(1810.-zpos2,1810.+zpos2));

      double md = 1232;
      double mN = (mp + mn) / 2.;

      bool printstuff = false;
      if (printstuff) {std::cout << "mark 1" << std::endl;}
      // multiring nue-ccpip preselection
      if ((nhitac<16)
	  && (fqwall2 > 200.)
	  && (evis > 30)
	  //	  && (fqmrnring[0] == 1)
	  //	  && (lemu > fq1rmom[0][1]*0.2)
	  //&& (fq1rmom[0][1]>30.)
	  && (fqnse < 2)
	  ) {
	// 2 rings
	if (fqmrnring[0] == 2) {
	  if (printstuff) {std::cout << "mark 2" << std::endl;}
	  int pidcode = 0;
	  int ie = -1;
	  // 1st (most energetic) ring
	  if (printstuff) {std::cout << "mark 2.1" << std::endl;}
	  if ((fqmrpid[0][0]==2)||(fqmrpid[0][0]==3)) {
	    pidcode = 2;
	  } else if (fqmrpid[0][0] == 1) {
	    ie = 0;
	  } else {
	    std::cout << "Oh no! fqmrnring[0] = " << fqmrnring[0] << " and fqmrpid[0][0] = " << fqmrpid[0][0] << std::endl;
	  }
	  // 2nd ring
	  if (printstuff) {std::cout << "mark 2.2" << std::endl;}
	  if ((fqmrpid[0][1]==2)||(fqmrpid[0][1]==3)) {
	    pidcode++;
	  } else if (fqmrpid[0][1] == 1) {
	    if (ie < 0) {ie = 1;}
	  } else {
	    std::cout << "Oh no! fqmrnring[0] = " << fqmrnring[0] << " and fqmrpid[0][1] = " << fqmrpid[0][1] << std::endl;
	  }
	  if (printstuff) {std::cout << "mark 2.3" << std::endl;}
	  if (ie < 0) {
	    //	    std::cout << "Ugh, ie = " << ie << ". Setting to 0" << std::endl;
	    ie = 0;
	  }

	  if (printstuff) {std::cout << "mark 2.4" << std::endl;}
	  pe = fqmrmom[0][ie];
	  ee = sqrt(pe*pe+me*me);
	  costhbeam = fqmrdir[0][ie][0]*dirnu[0][0]
			   + fqmrdir[0][ie][1]*dirnu[0][1]
			   + fqmrdir[0][ie][2]*dirnu[0][2];
	  erec = erecmr; //(md*md-mN*mN-me*me)/2/(mN-ee+pe*costhbeam)/1000.;

	  if ((inttype==1)&&(nutype==0)) h2eres->Fill((erec-pnu[0])/pnu[0]);

	  if (printstuff) {std::cout << "mark 2.5" << std::endl;}
 	  h2precut[nutype][inttype][fqnse-1][0][pidcode]->Fill(pnu[0]);
	  h2precutrec[nutype][inttype][fqnse-1][0][pidcode]->Fill(erec);

	  // 3 rings
	} else if (fqmrnring[0] == 3) {
	  if (printstuff) {std::cout << "mark 3" << std::endl;}
	  int pidcode = 0;
	  int ie = -1;
	  // 1st (most energetic) ring
	  if (printstuff) {std::cout << "mark 3.1" << std::endl;}
	  if ((fqmrpid[0][0]==2)||(fqmrpid[0][0]==3)) {
	    pidcode = 4;
	  } else if (fqmrpid[0][0] == 1) {
	    ie = 0;
	  } else {
	    std::cout << "Oh no! fqmrnring[0] = " << fqmrnring[0] << " and fqmrpid[0][0] = " << fqmrpid[0][0] << std::endl;
	  }
	  // 2nd ring
	  if (printstuff) {std::cout << "mark 3.2" << std::endl;}
	  if ((fqmrpid[0][1]==2)||(fqmrpid[0][1]==3)) {
	    pidcode += 2;
	  } else if (fqmrpid[0][1] == 1) {
	    if (ie < 0) {ie = 1;}
	  } else {
	    std::cout << "Oh no! fqmrnring[0] = " << fqmrnring[0] << " and fqmrpid[0][1] = " << fqmrpid[0][1] << std::endl;
	  }
	  // 3rd ring
	  if (printstuff) {std::cout << "mark 3.3" << std::endl;}
	  if ((fqmrpid[0][2]==2)||(fqmrpid[0][2]==3)) {
	    pidcode++;
	  } else if (fqmrpid[0][2] == 1) {
	    if (ie < 0) {ie = 2;}
	  } else {
	    std::cout << "Oh no! fqmrnring[0] = " << fqmrnring[0] << " and fqmrpid[0][2] = " << fqmrpid[0][2] << std::endl;
	  }
	  if (printstuff) {std::cout << "mark 3.4" << std::endl;}
	  if (ie < 0) {
	    //	    std::cout << "Ugh, ie = " << ie << ". Setting to 0" << std::endl;
	    ie = 0;
	  }

	  if (printstuff) {std::cout << "mark 3.5" << std::endl;}
	  pe = fqmrmom[0][ie];
	  ee = sqrt(pe*pe+me*me);
	  costhbeam = fqmrdir[0][ie][0]*dirnu[0][0]
			   + fqmrdir[0][ie][1]*dirnu[0][1]
			   + fqmrdir[0][ie][2]*dirnu[0][2];
	  erec = erecmr; //(md*md-mN*mN-me*me)/2/(mN-ee+pe*costhbeam)/1000.;

	  if ((inttype==1)&&(nutype==0)) h3eres->Fill((erec-pnu[0])/pnu[0]);

	  if (printstuff) {std::cout << "mark 3.6 " << nutype << ", " << inttype << ", " << fqnse << ", 0, " << pidcode << std::endl;}
	  h2precut[nutype][inttype][fqnse-1][1][pidcode]->Fill(pnu[0]);
	  if (printstuff) {std::cout << "mark 3.7" << std::endl;}
	  h2precutrec[nutype][inttype][fqnse-1][1][pidcode]->Fill(erec);
	  if (printstuff) {std::cout << "mark 3.8" << std::endl;}

	}

      }
      if (printstuff) {std::cout << "mark 4" << std::endl;}

   }

   outfile->Write();
   outfile->Close();

}
