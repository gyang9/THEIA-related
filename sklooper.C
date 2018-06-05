#define sklooper_cxx
#include "sklooper.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TH2D.h>
#include <iostream>


void sklooper::Loop()
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

   TFile* outfile = new TFile("outfilesk.root","RECREATE");
   TH2D* hzvsr = new TH2D("hzvsr","True Z vs R",40,0.,4000.,80,-4000.,4000.);
   TH2D* hfqzvsr = new TH2D("hfqzvsr","FiTQun Z vs R",40,0.,4000.,80,-4000.,4000.);

   const int nnutypes = 4;
   TString nunames[nnutypes] = {"nue","nuebar","numu","numubar"};
   const int ninttypes = 4;
   TString intnames[ninttypes] = {"ccqe","ccpip","ccother","nc"};

   TH1D* htruefv [nnutypes][ninttypes];

   TH1D* hprecut [nnutypes][ninttypes];
   TH1D* hprecutrec [nnutypes][ninttypes];
   TH1D* hpostcutrec[nnutypes][ninttypes];

   const int ndecaye2 = 3;
   const int nrings2 = 2;
   const int maxcomb = 8;
   TH1D* h2precut [nnutypes][ninttypes][ndecaye2][nrings2][maxcomb];
   TH1D* h2precutrec [nnutypes][ninttypes][ndecaye2][nrings2][maxcomb];
   TH1D* h2postcutrec[nnutypes][ninttypes][ndecaye2][nrings2][maxcomb];

   TH2D* htrueToreco [nnutypes][ninttypes];

   const int nbins = 25;
   double binedges[nbins+1] = {0.0, 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 15.0, 20.0, 40.0,100.0};

   for (int nt=0; nt<nnutypes; nt++) {
     TString hprefix1 = nunames[nt];
     hprefix1 += "_";
     for (int it=0; it<ninttypes; it++) {
       TString hprefix = hprefix1;
       hprefix += intnames[it];
       TString hname = hprefix + "_truefv";
       htruefv[nt][it] = new TH1D(hname,hname,nbins,binedges);

       hname = hprefix + "_precut";
       hprecut[nt][it] = new TH1D(hname,hname,nbins,binedges);
       hname = hprefix + "_precutrec";
       hprecutrec[nt][it] = new TH1D(hname,hname,nbins,binedges);
       hname = hprefix + "_postcutrec";
       hpostcutrec[nt][it] = new TH1D(hname,hname,nbins,binedges);
       hname = hprefix + "_trueToreco";
       htrueToreco[nt][it] = new TH1D(hname,hname,nbins,binedges,bins,binedges);

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
	     h2postcutrec[nt][it][ide][ir][icomb] = new TH1D(hname,hname,nbins,binedges);
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

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
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
      double fqwall = min(1690.-rpos,min(1810.-zpos,1810.+zpos));
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

      double erec = (me*me+mn*mn-mp*mp-2*mn*ee)/-2./(mn-ee+pe*costhbeam)/1000.;
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
      } else if ((abs(mode)<30)) { // CCother
	inttype = 2;
      } else if ((abs(mode)>30)) { // NC
	inttype = 3;
      }

      // neutrinos in FV
      if (wallv>200) {
	htruefv[nutype][inttype]->Fill(pnu[0]);
      }

      // pi0 efficiency
      if ((nhitac<16)
	  && (fqwall > 200.)
	  && (fq1rmom[0][1]>30.)
	  //&& (fqnse == 1)
	  && (fqnse < 2)
	 ) {
	if ((inttype == 3)&&(ntpi0 == 1)) {
	  htruefvpi0->Fill(ppi0);
	  if ((lpie > 175 - 0.875*fqpi0mass[0])
	      //&&(fq1rmom[0][1]<1000.)
	      ) {
	  //	  hpostcutrec[nutype][inttype]->Fill(erec);
	    hpostcutpi0->Fill(ppi0);
	  }
	}
      }


      // all included
      if ((nhitac<16)
          && (fqwall > 200.)
          && (evis>30)
          //&& (fqmrnring[0] == 1)
          //&& (lemu > fq1rmom[0][1]*0.2)
          //&& (fq1rmom[0][1]>100.)
                  && (fqnse < 2)
          ) {

        hprecut[nutype][inttype]->Fill(pnu[0]);
        hprecutrec[nutype][inttype]->Fill(erec);
        if ((inttype==0)&&(nutype==0)) heres->Fill((erec-pnu[0])/pnu[0]);

        if (fq1rmom[0][1]<500.) {
          if (lpie < 125 - 0.875*fqpi0mass[0]) {
            hpostcutrec[nutype][inttype]->Fill(erec);
          }
        } else if (fq1rmom[0][1]<1000.) {
          if (lpie < 150 - 0.6*fqpi0mass[0]) {
            hpostcutrec[nutype][inttype]->Fill(erec);
          }
        } else if (fq1rmom[0][1]>=1000.) {
          if (lpie < 100) {
            hpostcutrec[nutype][inttype]->Fill(erec);
          }
        }

      }



      // 1-ring e-like preselection
      if ((nhitac<16)
	  && (fqwall > 200.)
	  && (evis>30)
	  && (fqmrnring[0] == 1)
	  //&& (lemu > fq1rmom[0][1]*0.2)
	  //&& (fq1rmom[0][1]>100.)
	  	  && (fqnse < 2)
	  ) {

	hprecut[nutype][inttype]->Fill(pnu[0]);	
	hprecutrec[nutype][inttype]->Fill(erec);	
	if ((inttype==0)&&(nutype==0)) heres->Fill((erec-pnu[0])/pnu[0]);

	if (fq1rmom[0][1]<500.) {
	  if (lpie < 125 - 0.875*fqpi0mass[0]) {
	    hpostcutrec[nutype][inttype]->Fill(erec);
	  }
	} else if (fq1rmom[0][1]<1000.) {
	  if (lpie < 150 - 0.6*fqpi0mass[0]) {
	    hpostcutrec[nutype][inttype]->Fill(erec);
	  }
	} else if (fq1rmom[0][1]>=1000.) {
	  if (lpie < 100) {
	    hpostcutrec[nutype][inttype]->Fill(erec);
	  }
	}

      }


      // Multi-ring

      double xpos2 = fqmrpos[0][0][0];
      double ypos2 = fqmrpos[0][0][1];
      double zpos2 = fqmrpos[0][0][2];
      double rpos2 = sqrt(xpos2*xpos2+ypos2*ypos2);
      double fqwall2 = min(1690.-rpos2,min(1810.-zpos2,1810.+zpos2));

      double md = 1232;
      double mN = (mp + mn) / 2.;

      bool printstuff = false;
      if (printstuff) {std::cout << "mark 1" << std::endl;}
      // multiring nue-ccpip preselection
      if ((nhitac<16)
	  && (fqwall2 > 200.)
	  //	  && (fqmrnring[0] == 1)
	  //	  && (lemu > fq1rmom[0][1]*0.2)
	  && (fq1rmom[0][1]>30.)
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
	  erec = (md*md-mN*mN-me*me)/2/(mN-ee+pe*costhbeam)/1000.;

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
	  erec = (md*md-mN*mN-me*me)/2/(mN-ee+pe*costhbeam)/1000.;

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
