{

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
  int ncomb[nrings2] = {4,8};
  TH1D* h2precut [nnutypes][ninttypes][ndecaye2][nrings2][maxcomb];
  TH1D* h2precutrec [nnutypes][ninttypes][ndecaye2][nrings2][maxcomb];
  TH1D* h2postcutrec[nnutypes][ninttypes][ndecaye2][nrings2][maxcomb];

  const int nbins = 25;
  TString sbinedges[nbins+1] = {"0.0", "0.2", "0.4", "0.6", "0.8", "1.0", "1.2", "1.4", "1.6", "1.8", "2.0", "2.5", "3.0", "3.5", "4.0", "4.5", "5.0", "6.0", "7.0", "8.0", "9.0", "10.0", "15.0", "20.0", "40.0", "100"};

  TFile* tf = new TFile("outfilesk.root");
  const int nbins = nue_ccqe_precut->GetNbinsX();
  double yvals[nbins];
  double xvals[nbins];

  // precuts over all neutrinos

  TH2D* plotarea = new TH2D("plotarea","Precut Ratios",1000,0.,25.,1000,0.,1.);
  for (int ibin=0; ibin<nbins; ibin++) {
    int index = plotarea->GetXaxis()->FindBin(ibin);
    plotarea->GetXaxis()->SetBinLabel(index,sbinedges[ibin]);
  }
  plotarea->GetXaxis()->SetTitleOffset(1.4);
  plotarea->GetXaxis()->SetTitle("True E_{#nu} (GeV)");
  plotarea->GetYaxis()->SetTitle("Efficiency");
  //  plotarea->Draw();

//  // Efficiencies
//  TH1D* h2effs[nnutypes][ninttypes][ndecaye2][nrings2][maxcomb];
//  TH1D* h2effsrec[nnutypes][ninttypes][ndecaye2][nrings2][maxcomb];
//  TGraph* tg2effs[nnutypes][ninttypes][ndecaye2][nrings2][maxcomb];
//  TGraph* tg2effsrec[nnutypes][ninttypes][ndecaye2][nrings2][maxcomb];

  for (int nt=0; nt<nnutypes; nt++) {
    TString hprefix1 = nunames[nt];
    hprefix1 += "_";
    for (int it=0; it<ninttypes; it++) {
      TString hprefix = hprefix1;
      hprefix += intnames[it];
      TString hname = hprefix + "_truefv";
      gDirectory->GetObject(hname,htruefv[nt][it]);
      //      htruefv[nt][it] = new TH1D(hname,hname,nbins,binedges);
      std::cout << hname << ": " << htruefv[nt][it]->GetEntries() << std::endl;

      hname = hprefix + "_precut";
      gDirectory->GetObject(hname,hprecut[nt][it]);
      //      hprecut[nt][it] = new TH1D(hname,hname,nbins,binedges);
      std::cout << hname << ": " << hprecut[nt][it]->GetEntries() << std::endl;
      hname = hprefix + "_precutrec";
      gDirectory->GetObject(hname,hprecutrec[nt][it]);
      std::cout << hname << ": " << hprecutrec[nt][it]->GetEntries() << std::endl;
//      hprecutrec[nt][it] = new TH1D(hname,hname,nbins,binedges);
      hname = hprefix + "_postcutrec";
      gDirectory->GetObject(hname,hpostcutrec[nt][it]);
      std::cout << hname << ": " << hpostcutrec[nt][it]->GetEntries() << std::endl;
//      hpostcutrec[nt][it] = new TH1D(hname,hname,nbins,binedges);

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

	    // Precuts
	    hname = hprefix;
	    hname += "_mr_precut";
	    hname += hsuffix3;
	    gDirectory->GetObject(hname,h2precut[nt][it][ide][ir][icomb]);
	    std::cout << hname << ": " << h2precut[nt][it][ide][ir][icomb]->GetEntries() << std::endl;
//	    h2precut[nt][it][ide][ir][icomb] = new TH1D(hname,hname,nbins,binedges);
//	    h2effs[nt][it][ide][ir][icomb] = (TH1D*)h2precut[nt][it][ide][ir][icomb]->Clone();
//	    h2effs[nt][it][ide][ir][icomb]->Divide(htruefv[nt][it]);
//	    for (int ibin=0; ibin<nbins; ibin++) {
//	      yvals[ibin] = h2effs[nt][it][ide][ir][icomb]->GetBinContent(ibin+1);
//	      xvals[ibin] = ibin;
//	    }
//	    tg2effs[nt][it][ide][ir][icomb] = new TGraph(nbins,xvals,yvals);
//	    tg2effs[nt][it][ide][ir][icomb]->SetLineColor(1);
//	    tg2effs[nt][it][ide][ir][icomb]->SetLineWidth(4);
//	    tg2effs[nt][it][ide][ir][icomb]->SetMarkerColor(1);
//	    tg2effs[nt][it][ide][ir][icomb]->SetMarkerSize(1.5);
//	    tg2effs[nt][it][ide][ir][icomb]->SetMarkerStyle(21);
//	    //  h2effs[nt][it][ide][ir][icomb]->SetName("r00preall");
//	    //  tg2effs[nt][it][ide][ir][icomb]->SetTitle("Precut Ratios");
//	    tg2effs[nt][it][ide][ir][icomb]->GetXaxis()->SetTitleOffset(1.4);
//	    tg2effs[nt][it][ide][ir][icomb]->GetXaxis()->SetTitle("True E_{#nu} (GeV)");
//	    tg2effs[nt][it][ide][ir][icomb]->GetYaxis()->SetTitle("Efficiency");
//	    if ((ide == 2)&&(ir == 2)&&(icomb == 1)) {
//	      if (((nt == 1)&&(it))||((nt == 3)&&())) {
//		tg2effs[nt][it][ide][ir][icomb]->Draw("same LP");
//	      }
//	    }

	    // Precuts w/ Erec
	    hname = hprefix;
	    hname += "_mr_precutrec";
	    hname += hsuffix3;
	    gDirectory->GetObject(hname,h2precutrec[nt][it][ide][ir][icomb]);
	    //	    std::cout << hname << ": " << h2precutrec[nt][it][ide][ir][icomb]->GetEntries() << std::endl;
//	    h2precutrec[nt][it][ide][ir][icomb] = new TH1D(hname,hname,nbins,binedges);

	    // Postcuts???
	    hname = hprefix;
	    hname += "_mr_postcutrec";
	    hname += hsuffix3;
	    //	    gDirectory->GetObject(hname,h2postcutrec[nt][it][ide][ir][icomb]);
//	    h2postcutrec[nt][it][ide][ir][icomb] = new TH1D(hname,hname,nbins,binedges);
	  }
	}
      }
    }
  }

//  TH1D* r00preall = (TH1D*)nue_ccqe_precut->Clone();
//  r00preall->Divide(nue_ccqe_truefv);
//
//  for (int ibin=0; ibin<nbins; ibin++) {
//    yvals[ibin] = r00preall->GetBinContent(ibin+1);
//    xvals[ibin] = ibin;
//  }
//
//  TGraph* tg00preall = new TGraph(nbins,xvals,yvals);
//  tg00preall->SetLineColor(46);
//  tg00preall->SetLineWidth(4);
//  tg00preall->SetMarkerColor(46);
//  tg00preall->SetMarkerSize(1.5);
//  tg00preall->SetMarkerStyle(21);
////  r00preall->SetName("r00preall");
////  tg00preall->SetTitle("Precut Ratios");
//  tg00preall->GetXaxis()->SetTitleOffset(1.4);
//  tg00preall->GetXaxis()->SetTitle("True E_{#nu} (GeV)");
//  tg00preall->GetYaxis()->SetTitle("Efficiency");
//  tg00preall->Draw("same LP");
//
//  // nuebar ccqe
//
//  TH1D* r10preall = (TH1D*)nuebar_ccqe_precut->Clone();
//  r10preall->Divide(nuebar_ccqe_truefv);
//
//  for (int ibin=0; ibin<nbins; ibin++) {
//    yvals[ibin] = r10preall->GetBinContent(ibin+1);
//    xvals[ibin] = ibin;
//  }
//
//  TGraph* tg10preall = new TGraph(nbins,xvals,yvals);
//  for (int ibin=0; ibin<nbins; ibin++) {
//    int index = tg10preall->GetXaxis()->FindBin(ibin);
//    tg10preall->GetXaxis()->SetBinLabel(index,sbinedges[ibin]);
//  }
//  tg10preall->SetLineColor(6);
//  tg10preall->SetLineWidth(4);
//  tg10preall->SetMarkerColor(6);
//  tg10preall->SetMarkerSize(1.5);
//  tg10preall->SetMarkerStyle(21);
////  r10preall->SetName("r10preall");
//  tg10preall->SetTitle("Precut Ratios");
//  tg10preall->GetXaxis()->SetTitle("True E_{#nu} (GeV)");
//  tg10preall->GetYaxis()->SetTitle("Efficiency");
//  tg10preall->Draw("LP same");
//
//  // nue ccnqe
//
//  TH1D* r02preall = (TH1D*)nue_ccpip_precut->Clone();
//  r02preall->Add(nue_ccother_precut);
//  TH1D* tmp = (TH1D*)nue_ccpip_truefv->Clone();
//  tmp->Add(nue_ccother_truefv);
//  r02preall->Divide(tmp);
//
//  for (int ibin=0; ibin<nbins; ibin++) {
//    yvals[ibin] = r02preall->GetBinContent(ibin+1);
//    xvals[ibin] = ibin;
//  }
//
//  TGraph* tg02preall = new TGraph(nbins,xvals,yvals);
//  for (int ibin=0; ibin<nbins; ibin++) {
//    int index = tg02preall->GetXaxis()->FindBin(ibin);
//    tg02preall->GetXaxis()->SetBinLabel(index,sbinedges[ibin]);
//  }
//  tg02preall->SetLineColor(8);
//  tg02preall->SetLineWidth(4);
//  tg02preall->SetMarkerColor(8);
//  tg02preall->SetMarkerSize(1.5);
//  tg02preall->SetMarkerStyle(21);
////  r02preall->SetName("r02preall");
//  tg02preall->SetTitle("Precut Ratios");
//  tg02preall->GetXaxis()->SetTitle("True E_{#nu} (GeV)");
//  tg02preall->GetYaxis()->SetTitle("Efficiency");
//  tg02preall->Draw("LP same");
//
//  // nuebar ccnqe
//
//  TH1D* r12preall = (TH1D*)nuebar_ccpip_precut->Clone();
//  r12preall->Add(nuebar_ccother_precut);
//  TH1D* tmp = (TH1D*)nuebar_ccpip_truefv->Clone();
//  tmp->Add(nuebar_ccother_truefv);
//  r12preall->Divide(tmp);
//
//  for (int ibin=0; ibin<nbins; ibin++) {
//    yvals[ibin] = r12preall->GetBinContent(ibin+1);
//    xvals[ibin] = ibin;
//  }
//
//  TGraph* tg12preall = new TGraph(nbins,xvals,yvals);
//  for (int ibin=0; ibin<nbins; ibin++) {
//    int index = tg12preall->GetXaxis()->FindBin(ibin);
//    tg12preall->GetXaxis()->SetBinLabel(index,sbinedges[ibin]);
//  }
//  tg12preall->SetLineColor(3);
//  tg12preall->SetLineWidth(4);
//  tg12preall->SetMarkerColor(3);
//  tg12preall->SetMarkerSize(1.5);
//  tg12preall->SetMarkerStyle(21);
////  r12preall->SetName("r12preall");
//  tg12preall->SetTitle("Precut Ratios");
//  tg12preall->GetXaxis()->SetTitle("True E_{#nu} (GeV)");
//  tg12preall->GetYaxis()->SetTitle("Efficiency");
//  tg12preall->Draw("LP same");
//
//  // numu cc
//
//  TH1D* r22preall = (TH1D*)numu_ccqe_precut->Clone();
//  r22preall->Add(numu_ccpip_precut);
//  r22preall->Add(numu_ccother_precut);
//  r22preall->Add(numubar_ccqe_precut);
//  r22preall->Add(numubar_ccpip_precut);
//  r22preall->Add(numubar_ccother_precut);
//  TH1D* tmp = (TH1D*)numu_ccqe_truefv->Clone();
//  tmp->Add(numu_ccpip_truefv);
//  tmp->Add(numu_ccother_truefv);
//  tmp->Add(numubar_ccqe_truefv);
//  tmp->Add(numubar_ccpip_truefv);
//  tmp->Add(numubar_ccother_truefv);
//  r22preall->Divide(tmp);
//
//  for (int ibin=0; ibin<nbins; ibin++) {
//    yvals[ibin] = r22preall->GetBinContent(ibin+1);
//    xvals[ibin] = ibin;
//  }
//
//  TGraph* tg22preall = new TGraph(nbins,xvals,yvals);
//  for (int ibin=0; ibin<nbins; ibin++) {
//    int index = tg22preall->GetXaxis()->FindBin(ibin);
//    tg22preall->GetXaxis()->SetBinLabel(index,sbinedges[ibin]);
//  }
//  tg22preall->SetLineColor(7);
//  tg22preall->SetLineWidth(4);
//  tg22preall->SetMarkerColor(7);
//  tg22preall->SetMarkerSize(1.5);
//  tg22preall->SetMarkerStyle(21);
////  r22preall->SetName("r22preall");
//  tg22preall->SetTitle("Precut Ratios");
//  tg22preall->GetXaxis()->SetTitle("True E_{#nu} (GeV)");
//  tg22preall->GetYaxis()->SetTitle("Efficiency");
//  tg22preall->Draw("LP same");
//
//  // nc
//
//  TH1D* r44preall = (TH1D*)nue_nc_precut->Clone();
//  r44preall->Add(nuebar_nc_precut);
//  r44preall->Add(numu_nc_precut);
//  r44preall->Add(numubar_nc_precut);
//  TH1D* tmp = (TH1D*)nue_nc_truefv->Clone();
//  tmp->Add(nuebar_nc_truefv);
//  tmp->Add(numu_nc_truefv);
//  tmp->Add(numubar_nc_truefv);
//  r44preall->Divide(tmp);
//
//  for (int ibin=0; ibin<nbins; ibin++) {
//    yvals[ibin] = r44preall->GetBinContent(ibin+1);
//    xvals[ibin] = ibin;
//  }
//
//  TGraph* tg44preall = new TGraph(nbins,xvals,yvals);
//  for (int ibin=0; ibin<nbins; ibin++) {
//    int index = tg44preall->GetXaxis()->FindBin(ibin);
//    tg44preall->GetXaxis()->SetBinLabel(index,sbinedges[ibin]);
//  }
//  tg44preall->SetLineColor(42);
//  tg44preall->SetLineWidth(4);
//  tg44preall->SetMarkerColor(42);
//  tg44preall->SetMarkerSize(1.5);
//  tg44preall->SetMarkerStyle(21);
////  r44preall->SetName("r44preall");
//  tg44preall->SetTitle("Precut Ratios");
//  tg44preall->GetXaxis()->SetTitle("True E_{#nu} (GeV)");
//  tg44preall->GetYaxis()->SetTitle("Efficiency");
//  tg44preall->Draw("LP same");


// ************ Multi-ring ************

  const int nccqenutypes = 2;
  const int nccqedecaye = 2;
  TH1D* repiccqe[nccqenutypes][nccqedecaye][nrings2];
  TGraph* tgepiccqe[nccqenutypes][nccqedecaye][nrings2];
  int combepi[nrings2] = {1,3};
  int iccqecolor[nccqenutypes] = {46,6};

  for (int inu=0; inu < nccqenutypes; inu++) {
    for (int ide=0; ide<nccqedecaye; ide++) {
      for (int ir=0; ir<nrings2; ir++) {

	repiccqe[inu][ide][ir] = (TH1D*)h2precut[inu][0][ide][ir][combepi[ir]]->Clone();
	repiccqe[inu][ide][ir]->SetName("repiccqe");
	repiccqe[inu][ide][ir]->Divide(htruefv[inu][0]);

	for (int ibin=0; ibin<nbins; ibin++) {
	  yvals[ibin] = repiccqe[inu][ide][ir]->GetBinContent(ibin+1);
	  xvals[ibin] = ibin;
	}

	tgepiccqe[inu][ide][ir] = new TGraph(nbins,xvals,yvals);
	tgepiccqe[inu][ide][ir]->SetLineColor(iccqecolor[inu]);
	tgepiccqe[inu][ide][ir]->SetLineWidth(4);
	tgepiccqe[inu][ide][ir]->SetMarkerColor(iccqecolor[inu]);
	tgepiccqe[inu][ide][ir]->SetMarkerSize(1.5);
	tgepiccqe[inu][ide][ir]->SetMarkerStyle(21);
	//  repiccqe[inu][ide][ir]->SetName("r00preall");
	//  tgepiccqe[inu][ide][ir]->SetTitle("Precut Ratios");
	tgepiccqe[inu][ide][ir]->GetXaxis()->SetTitleOffset(1.4);
	tgepiccqe[inu][ide][ir]->GetXaxis()->SetTitle("True E_{#nu} (GeV)");
	tgepiccqe[inu][ide][ir]->GetYaxis()->SetTitle("Efficiency");
	//	tgepiccqe[inu][ide][ir]->Draw("same LP");

      }
    }
  }

  // CCpi+

  const int nccpipnutypes = 2;
  const int nccpipdecaye = 2;
  TH1D* repiccpip[nccpipnutypes][nccpipdecaye][nrings2];
  TGraph* tgepiccpip[nccpipnutypes][nccpipdecaye][nrings2];
  int iccpipcolor[nccpipnutypes] = {28,25};

  for (int inu=0; inu < nccpipnutypes; inu++) {
    for (int ide=0; ide<nccpipdecaye; ide++) {
      for (int ir=0; ir<nrings2; ir++) {

	repiccpip[inu][ide][ir] = (TH1D*)h2precut[inu][1][ide][ir][combepi[ir]]->Clone();
	repiccpip[inu][ide][ir]->SetName("repiccpip");
	repiccpip[inu][ide][ir]->Divide(htruefv[inu][1]);

	for (int ibin=0; ibin<nbins; ibin++) {
	  yvals[ibin] = repiccpip[inu][ide][ir]->GetBinContent(ibin+1);
	  xvals[ibin] = ibin;
	}

	tgepiccpip[inu][ide][ir] = new TGraph(nbins,xvals,yvals);
	tgepiccpip[inu][ide][ir]->SetLineColor(iccpipcolor[inu]);
	tgepiccpip[inu][ide][ir]->SetLineWidth(4);
	tgepiccpip[inu][ide][ir]->SetMarkerColor(iccpipcolor[inu]);
	tgepiccpip[inu][ide][ir]->SetMarkerSize(1.5);
	tgepiccpip[inu][ide][ir]->SetMarkerStyle(21);
	//  repiccpip[inu][ide][ir]->SetName("r00preall");
	//  tgepiccpip[inu][ide][ir]->SetTitle("Precut Ratios");
	tgepiccpip[inu][ide][ir]->GetXaxis()->SetTitleOffset(1.4);
	tgepiccpip[inu][ide][ir]->GetXaxis()->SetTitle("True E_{#nu} (GeV)");
	tgepiccpip[inu][ide][ir]->GetYaxis()->SetTitle("Efficiency");
	//	tgepiccpip[inu][ide][ir]->Draw("same LP");

      }
    }
  }

  // CCOther

  const int nccothernutypes = 2;
  const int nccotherdecaye = 2;
  TH1D* repiccother[nccothernutypes][nccotherdecaye][nrings2];
  TGraph* tgepiccother[nccothernutypes][nccotherdecaye][nrings2];
  int iccothercolor[nccothernutypes] = {8,3};

  for (int inu=0; inu < nccothernutypes; inu++) {
    for (int ide=0; ide<nccotherdecaye; ide++) {
      for (int ir=0; ir<nrings2; ir++) {

	repiccother[inu][ide][ir] = (TH1D*)h2precut[inu][2][ide][ir][combepi[ir]]->Clone();
	repiccother[inu][ide][ir]->SetName("repiccother");
	repiccother[inu][ide][ir]->Divide(htruefv[inu][2]);

	for (int ibin=0; ibin<nbins; ibin++) {
	  yvals[ibin] = repiccother[inu][ide][ir]->GetBinContent(ibin+1);
	  xvals[ibin] = ibin;
	}

	tgepiccother[inu][ide][ir] = new TGraph(nbins,xvals,yvals);
	tgepiccother[inu][ide][ir]->SetLineColor(iccothercolor[inu]);
	tgepiccother[inu][ide][ir]->SetLineWidth(4);
	tgepiccother[inu][ide][ir]->SetMarkerColor(iccothercolor[inu]);
	tgepiccother[inu][ide][ir]->SetMarkerSize(1.5);
	tgepiccother[inu][ide][ir]->SetMarkerStyle(21);
	//  repiccother[inu][ide][ir]->SetName("r00preall");
	//  tgepiccother[inu][ide][ir]->SetTitle("Precut Ratios");
	tgepiccother[inu][ide][ir]->GetXaxis()->SetTitleOffset(1.4);
	tgepiccother[inu][ide][ir]->GetXaxis()->SetTitle("True E_{#nu} (GeV)");
	tgepiccother[inu][ide][ir]->GetYaxis()->SetTitle("Efficiency");
	//	tgepiccother[inu][ide][ir]->Draw("same LP");

      }
    }
  }

  // CCnumu

  const int nccnumudecaye = 2;
  TH1D* repiccnumu[nccnumudecaye][nrings2];
  TGraph* tgepiccnumu[nccnumudecaye][nrings2];

  for (int ide=0; ide<nccnumudecaye; ide++) {
    for (int ir=0; ir<nrings2; ir++) {

      repiccnumu[ide][ir] = (TH1D*)h2precut[2][0][ide][ir][combepi[ir]]->Clone();
      repiccnumu[ide][ir]->Add(h2precut[2][1][ide][ir][combepi[ir]]);
      repiccnumu[ide][ir]->Add(h2precut[2][2][ide][ir][combepi[ir]]);
      repiccnumu[ide][ir]->Add(h2precut[3][0][ide][ir][combepi[ir]]);
      repiccnumu[ide][ir]->Add(h2precut[3][1][ide][ir][combepi[ir]]);
      repiccnumu[ide][ir]->Add(h2precut[3][2][ide][ir][combepi[ir]]);
      repiccnumu[ide][ir]->SetName("repiccnumu");
      TH1D* denom = (TH1D*)htruefv[2][0]->Clone();
      denom->Add(htruefv[2][1]);
      denom->Add(htruefv[2][2]);
      denom->Add(htruefv[3][0]);
      denom->Add(htruefv[3][1]);
      denom->Add(htruefv[3][2]);
      repiccnumu[ide][ir]->Divide(denom);

      for (int ibin=0; ibin<nbins; ibin++) {
	yvals[ibin] = repiccnumu[ide][ir]->GetBinContent(ibin+1);
	xvals[ibin] = ibin;
      }

      tgepiccnumu[ide][ir] = new TGraph(nbins,xvals,yvals);
      tgepiccnumu[ide][ir]->SetLineColor(7);
      tgepiccnumu[ide][ir]->SetLineWidth(4);
      tgepiccnumu[ide][ir]->SetMarkerColor(7);
      tgepiccnumu[ide][ir]->SetMarkerSize(1.5);
      tgepiccnumu[ide][ir]->SetMarkerStyle(21);
      //  repiccnumu[ide][ir]->SetName("r00preall");
      //  tgepiccnumu[ide][ir]->SetTitle("Precut Ratios");
      tgepiccnumu[ide][ir]->GetXaxis()->SetTitleOffset(1.4);
      tgepiccnumu[ide][ir]->GetXaxis()->SetTitle("True E_{#nu} (GeV)");
      tgepiccnumu[ide][ir]->GetYaxis()->SetTitle("Efficiency");
      //	tgepiccnumu[ide][ir]->Draw("same LP");

    }
  }

  // NC

  const int nncdecaye = 2;
  TH1D* repinc[nncdecaye][nrings2];
  TGraph* tgepinc[nncdecaye][nrings2];

  for (int ide=0; ide<nncdecaye; ide++) {
    for (int ir=0; ir<nrings2; ir++) {

      repinc[ide][ir] = (TH1D*)h2precut[0][3][ide][ir][combepi[ir]]->Clone();
      repinc[ide][ir]->Add(h2precut[1][3][ide][ir][combepi[ir]]);
      repinc[ide][ir]->Add(h2precut[2][3][ide][ir][combepi[ir]]);
      repinc[ide][ir]->Add(h2precut[3][3][ide][ir][combepi[ir]]);
      repinc[ide][ir]->SetName("repinc");
      TH1D* denom = (TH1D*)htruefv[0][3]->Clone();
      denom->Add(htruefv[1][3]);
      denom->Add(htruefv[2][3]);
      denom->Add(htruefv[3][3]);
      repinc[ide][ir]->Divide(denom);

      for (int ibin=0; ibin<nbins; ibin++) {
	yvals[ibin] = repinc[ide][ir]->GetBinContent(ibin+1);
	xvals[ibin] = ibin;
      }

      tgepinc[ide][ir] = new TGraph(nbins,xvals,yvals);
      tgepinc[ide][ir]->SetLineColor(42);
      tgepinc[ide][ir]->SetLineWidth(4);
      tgepinc[ide][ir]->SetMarkerColor(42);
      tgepinc[ide][ir]->SetMarkerSize(1.5);
      tgepinc[ide][ir]->SetMarkerStyle(21);
      //  repinc[ide][ir]->SetName("r00preall");
      //  tgepinc[ide][ir]->SetTitle("Precut Ratios");
      tgepinc[ide][ir]->GetXaxis()->SetTitleOffset(1.4);
      tgepinc[ide][ir]->GetXaxis()->SetTitle("True E_{#nu} (GeV)");
      tgepinc[ide][ir]->GetYaxis()->SetTitle("Efficiency");
      //	tgepinc[ide][ir]->Draw("same LP");

    }
  }

  // Draw!

  std::cout << "Begin Drawing" << std::endl;

  for (int ide=0; ide<nccnumudecaye; ide++) {
    TString canprefix = "eff_mr_decaye";
    canprefix += ide;
    for (int ir=0; ir<nrings2; ir++) {
      TString canname = canprefix;
      canname += "_nrings";
      canname += (ir+2);

      double maxeff = 0.;
      const int ncurves = 8;
      double maxvals[ncurves] = {
	repiccqe[0][ide][ir]->GetMaximum(),
	repiccqe[1][ide][ir]->GetMaximum(),
	repiccpip[0][ide][ir]->GetMaximum(),
	repiccpip[1][ide][ir]->GetMaximum(),
	repiccother[0][ide][ir]->GetMaximum(),
	repiccother[1][ide][ir]->GetMaximum(),
	repiccnumu[ide][ir]->GetMaximum(),
	repinc[ide][ir]->GetMaximum()};
      
      
      for (int ival=0; ival<ncurves; ival++) {
	if (maxvals[ival] > maxeff) {maxeff = maxvals[ival];}
      }
      if (maxeff < 0.01) {maxeff = 0.01;}

      TCanvas* tcan = new TCanvas(canname,canname);
      TH2D* plotarea2 = new TH2D("plotarea2","Precut Ratios",1000,0.,25.,1000,0.,maxeff*1.1);
      for (int ibin=0; ibin<nbins; ibin++) {
	int index = plotarea2->GetXaxis()->FindBin(ibin);
	plotarea2->GetXaxis()->SetBinLabel(index,sbinedges[ibin]);
      }
      plotarea2->GetXaxis()->SetTitleOffset(1.4);
      plotarea2->GetXaxis()->SetTitle("True E_{#nu} (GeV)");
      plotarea2->GetYaxis()->SetTitle("Efficiency");
      plotarea2->Draw();
      
      tgepiccqe[0][ide][ir]->Draw("same LP");
      tgepiccqe[1][ide][ir]->Draw("same LP");
      tgepiccpip[0][ide][ir]->Draw("same LP");
      tgepiccpip[1][ide][ir]->Draw("same LP");
      tgepiccother[0][ide][ir]->Draw("same LP");
      tgepiccother[1][ide][ir]->Draw("same LP");
      tgepiccnumu[ide][ir]->Draw("same LP");
      tgepinc[ide][ir]->Draw("same LP");
      canname += ".png";
      tcan->Print(canname);
      
      legend = new TLegend(0.1, 0.6, 0.25, 0.9);
      legend->SetHeader("The Legend Title");
      legend->AddEntry(tgepiccqe[0][ide][ir],"NCCQE nu 1","l");
      legend->AddEntry(tgepiccqe[1][ide][ir],"NCCQE nu 2","l");
      legend->AddEntry(tgepiccpip[0][ide][ir],"CC pi+ 1","l");
      legend->AddEntry(tgepiccpip[1][ide][ir],"CC pi+ 2","l");
      legend->AddEntry(tgepiccother[0][ide][ir],"NCC others 1","l");
      legend->AddEntry(tgepiccother[1][ide][ir],"NCC others 2","l");
      legend->AddEntry(tgepiccnumu[ide][ir],"CC nu mu","l");
      legend->AddEntry(tgepinc[ide][ir],"NC","l");
      legend->Draw();
    }
  }
}
