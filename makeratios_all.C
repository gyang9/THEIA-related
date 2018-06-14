{

  const int nnutypes = 4;
  TString nunames[nnutypes] = {"nue","nuebar","numu","numubar"};
  const int ninttypes = 4;
  TString intnames[ninttypes] = {"ccqe","ccpip","ccother","nc"};

  TH1D* htruefv [nnutypes][ninttypes];

  TH1D* hprecut [nnutypes][ninttypes];
  TH1D* hprecutrec [nnutypes][ninttypes];
  TH1D* hpostcutrec[nnutypes][ninttypes];
  TH1D* hpostcutrecDB[nnutypes][ninttypes];

  TH1D* h1rprecut [nnutypes][ninttypes];
  TH1D* h1rprecutrec [nnutypes][ninttypes];
  TH1D* h1rpostcutrec[nnutypes][ninttypes];

  const int ndecaye2 = 3;
  const int nrings2 = 2;
  const int maxcomb = 8;
  int ncomb[nrings2] = {4,8};
  TH1D* h2precut [nnutypes][ninttypes][ndecaye2][nrings2][maxcomb];
  TH1D* h2precutrec [nnutypes][ninttypes][ndecaye2][nrings2][maxcomb];
  TH1D* h2postcutrec[nnutypes][ninttypes][ndecaye2][nrings2][maxcomb];
  TH2D* h2trueTOreco[nnutypes][ninttypes];
  TH2D* h2trueTOrecoPRE[nnutypes][ninttypes];

  const int nbins = 25;
  TString sbinedges[nbins+1] = {"0.0", "0.2", "0.4", "0.6", "0.8", "1.0", "1.2", "1.4", "1.6", "1.8", "2.0", "2.5", "3.0", "3.5", "4.0", "4.5", "5.0", "6.0", "7.0", "8.0", "9.0", "10.0", "15.0", "20.0", "40.0", "60"};

  const int nbinsPost = 9;
  TString sbinedgesPost[nbinsPost+1] = {"0.175", "0.6", "1.175", "1.75", "2.5", "3.5", "4.5", "7.5", "10.0", "60.0"};

  TFile* tf = new TFile(Form("outfilesk_%s.root", gApplication->Argv(4)  ));
  const int nbins = nue_ccqe_precut->GetNbinsX();
  double yvals[nbins];
  double xvals[nbins];

  const int nbinsPost = nue_ccqe_postcutrec->GetNbinsX();
  double yvalsPost[nbinsPost];
  double xvalsPost[nbinsPost];


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

      hname = hprefix + "_trueToreco";
      gDirectory->GetObject(hname,h2trueTOreco[nt][it]);
      std::cout << hname << ": " << h2trueTOreco[nt][it]->GetEntries() << std::endl;
      hname = hprefix + "_trueTorecoPRE";
      gDirectory->GetObject(hname,h2trueTOrecoPRE[nt][it]);
      std::cout << hname << ": " << h2trueTOrecoPRE[nt][it]->GetEntries() << std::endl;

      hname = hprefix + "_postcutrecDB";
      gDirectory->GetObject(hname,hpostcutrecDB[nt][it]);
      std::cout << hname << ": " << hpostcutrecDB[nt][it]->GetEntries() << std::endl;

      hname = hprefix + "_1rprecut";
      gDirectory->GetObject(hname,h1rprecut[nt][it]);
      //      hprecut[nt][it] = new TH1D(hname,hname,nbins,binedges);
      std::cout << hname << ": " << h1rprecut[nt][it]->GetEntries() << std::endl;
      hname = hprefix + "_1rprecutrec";
      gDirectory->GetObject(hname,h1rprecutrec[nt][it]);
      std::cout << hname << ": " << h1rprecutrec[nt][it]->GetEntries() << std::endl;
//      hprecutrec[nt][it] = new TH1D(hname,hname,nbins,binedges);
      hname = hprefix + "_1rpostcutrec";
      gDirectory->GetObject(hname,h1rpostcutrec[nt][it]);
      std::cout << hname << ": " << h1rpostcutrec[nt][it]->GetEntries() << std::endl;

    }
  }

// ************ pi0 ************

// ************ Single-ring ************


// ************ all ************

  const int nccqenutypes = 2;
  const int nccqedecaye = 2;
  TH1D* repiccqe[nccqenutypes];
  TH1D* repiccqePostDB[nccqenutypes];
  TGraph* tgepiccqe[nccqenutypes];
  TH1D* repiccqePost[nccqenutypes];
  TH1D* repiccSignal;
  TGraph* tgepiccqePost[nccqenutypes];
  int combepi[nrings2] = {1,3};
  int iccqecolor[nccqenutypes] = {46,6};

  std::cout<<"CCQE; "<<endl;
  for (int inu=0; inu < nccqenutypes; inu++) {

	repiccqe[inu] = (TH1D*)hprecut[inu][0]->Clone();
	repiccqe[inu]->SetName("repiccqe");
	repiccqe[inu]->Divide(htruefv[inu][0]);

	for (int ibin=0; ibin<nbins; ibin++) {
	  yvals[ibin] = repiccqe[inu]->GetBinContent(ibin+1);
	  xvals[ibin] = ibin;
	}

	tgepiccqe[inu] = new TGraph(nbins,xvals,yvals);
	tgepiccqe[inu]->SetLineColor(iccqecolor[inu]);
	tgepiccqe[inu]->SetLineWidth(4);
	tgepiccqe[inu]->SetMarkerColor(iccqecolor[inu]);
	tgepiccqe[inu]->SetMarkerSize(1.5);
	tgepiccqe[inu]->SetMarkerStyle(21);
	tgepiccqe[inu]->GetXaxis()->SetTitleOffset(1.4);
	tgepiccqe[inu]->GetXaxis()->SetTitle("True E_{#nu} (GeV)");
	tgepiccqe[inu]->GetYaxis()->SetTitle("Efficiency");
  }
  std::cout<<"... "<<std::endl;
  for (int inu=0; inu < nccqenutypes; inu++) {

        repiccqePostDB[inu] = (TH1D*)hpostcutrecDB[inu][0]->Clone();
        repiccqePostDB[inu]->SetName("repiccqePostDB");

        repiccqePost[inu] = (TH1D*)hpostcutrec[inu][0]->Clone();
        repiccqePost[inu]->SetName("repiccqePost");
        repiccqePost[inu]->Divide(hprecutrec[inu][0]);

        for (int ibin=0; ibin<nbinsPost; ibin++) {
          yvalsPost[ibin] = repiccqePost[inu]->GetBinContent(ibin+1);
          xvalsPost[ibin] = ibin;
        }

        tgepiccqePost[inu] = new TGraph(nbinsPost,xvalsPost,yvalsPost);
        tgepiccqePost[inu]->SetLineColor(iccqecolor[inu]);
        tgepiccqePost[inu]->SetLineWidth(4);
        tgepiccqePost[inu]->SetMarkerColor(iccqecolor[inu]);
        tgepiccqePost[inu]->SetMarkerSize(1.5);
        tgepiccqePost[inu]->SetMarkerStyle(21);
        tgepiccqePost[inu]->GetXaxis()->SetTitleOffset(1.4);
        tgepiccqePost[inu]->GetXaxis()->SetTitle("Reco E_{#nu} (GeV)");
        tgepiccqePost[inu]->GetYaxis()->SetTitle("Efficiency");
  }


  // CCpi+
  std::cout<<"CCpi+; "<<endl;
  const int nccpipnutypes = 2;
  const int nccpipdecaye = 2;
  TH1D* repiccpip[nccpipnutypes];
  TGraph* tgepiccpip[nccpipnutypes];
  TH1D* repiccpipPost[nccpipnutypes];
  TH1D* repiccpipPostDB[nccpipnutypes];
  TGraph* tgepiccpipPost[nccpipnutypes];
  int iccpipcolor[nccpipnutypes] = {28,25};

  for (int inu=0; inu < nccpipnutypes; inu++) {

	repiccpip[inu] = (TH1D*)hprecut[inu][1]->Clone();
	repiccpip[inu]->SetName("repiccpip");
	repiccpip[inu]->Divide(htruefv[inu][1]);

	for (int ibin=0; ibin<nbins; ibin++) {
	  yvals[ibin] = repiccpip[inu]->GetBinContent(ibin+1);
	  xvals[ibin] = ibin;
	}

	tgepiccpip[inu] = new TGraph(nbins,xvals,yvals);
	tgepiccpip[inu]->SetLineColor(iccpipcolor[inu]);
	tgepiccpip[inu]->SetLineWidth(4);
	tgepiccpip[inu]->SetMarkerColor(iccpipcolor[inu]);
	tgepiccpip[inu]->SetMarkerSize(1.5);
	tgepiccpip[inu]->SetMarkerStyle(21);
	tgepiccpip[inu]->GetXaxis()->SetTitleOffset(1.4);
	tgepiccpip[inu]->GetXaxis()->SetTitle("True E_{#nu} (GeV)");
	tgepiccpip[inu]->GetYaxis()->SetTitle("Efficiency");
  }

  for (int inu=0; inu < nccpipnutypes; inu++) {

        repiccpipPostDB[inu] = (TH1D*)hpostcutrecDB[inu][1]->Clone();
        repiccpipPostDB[inu]->SetName("repiccpipPostDB");

        repiccpipPost[inu] = (TH1D*)hpostcutrec[inu][1]->Clone();
        repiccpipPost[inu]->SetName("repiccpipPost");
        repiccpipPost[inu]->Divide(hprecutrec[inu][1]);

        for (int ibin=0; ibin<nbinsPost; ibin++) {
          yvalsPost[ibin] = repiccpipPost[inu]->GetBinContent(ibin+1);
          xvalsPost[ibin] = ibin;
        }

        tgepiccpipPost[inu] = new TGraph(nbinsPost,xvalsPost,yvalsPost);
        tgepiccpipPost[inu]->SetLineColor(iccpipcolor[inu]);
        tgepiccpipPost[inu]->SetLineWidth(4);
        tgepiccpipPost[inu]->SetMarkerColor(iccpipcolor[inu]);
        tgepiccpipPost[inu]->SetMarkerSize(1.5);
        tgepiccpipPost[inu]->SetMarkerStyle(21);
        tgepiccpipPost[inu]->GetXaxis()->SetTitleOffset(1.4);
        tgepiccpipPost[inu]->GetXaxis()->SetTitle("Reco E_{#nu} (GeV)");
        tgepiccpipPost[inu]->GetYaxis()->SetTitle("Efficiency");
  }

  // CCOther
  std::cout<<"CCother; "<<endl;
  const int nccothernutypes = 2;
  const int nccotherdecaye = 2;
  TH1D* repiccother[nccothernutypes];
  TGraph* tgepiccother[nccothernutypes];
  TH1D* repiccotherPost[nccothernutypes];
  TH1D* repiccotherPostDB[nccothernutypes];
  TGraph* tgepiccotherPost[nccothernutypes];
  int iccothercolor[nccothernutypes] = {8,3};

  for (int inu=0; inu < nccothernutypes; inu++) {

	repiccother[inu] = (TH1D*)hprecut[inu][2]->Clone();
	repiccother[inu]->SetName("repiccother");
	repiccother[inu]->Divide(htruefv[inu][2]);

	for (int ibin=0; ibin<nbins; ibin++) {
	  yvals[ibin] = repiccother[inu]->GetBinContent(ibin+1);
	  xvals[ibin] = ibin;
	}

	tgepiccother[inu] = new TGraph(nbins,xvals,yvals);
	tgepiccother[inu]->SetLineColor(iccothercolor[inu]);
	tgepiccother[inu]->SetLineWidth(4);
	tgepiccother[inu]->SetMarkerColor(iccothercolor[inu]);
	tgepiccother[inu]->SetMarkerSize(1.5);
	tgepiccother[inu]->SetMarkerStyle(21);
	tgepiccother[inu]->GetXaxis()->SetTitleOffset(1.4);
	tgepiccother[inu]->GetXaxis()->SetTitle("True E_{#nu} (GeV)");
	tgepiccother[inu]->GetYaxis()->SetTitle("Efficiency");
  }

  for (int inu=0; inu < nccothernutypes; inu++) {

        repiccotherPostDB[inu] = (TH1D*)hpostcutrecDB[inu][2]->Clone();
        repiccotherPostDB[inu]->SetName("repiccotherPostDB");

        repiccotherPost[inu] = (TH1D*)hpostcutrec[inu][2]->Clone();
        repiccotherPost[inu]->SetName("repiccotherPost");
        repiccotherPost[inu]->Divide(hprecutrec[inu][2]);

        for (int ibin=0; ibin<nbinsPost; ibin++) {
          yvalsPost[ibin] = repiccotherPost[inu]->GetBinContent(ibin+1);
          xvalsPost[ibin] = ibin;
        }

        tgepiccotherPost[inu] = new TGraph(nbinsPost,xvalsPost,yvalsPost);
        tgepiccotherPost[inu]->SetLineColor(iccothercolor[inu]);
        tgepiccotherPost[inu]->SetLineWidth(4);
        tgepiccotherPost[inu]->SetMarkerColor(iccothercolor[inu]);
        tgepiccotherPost[inu]->SetMarkerSize(1.5);
        tgepiccotherPost[inu]->SetMarkerStyle(21);
        tgepiccotherPost[inu]->GetXaxis()->SetTitleOffset(1.4);
        tgepiccotherPost[inu]->GetXaxis()->SetTitle("Reco E_{#nu} (GeV)");
        tgepiccotherPost[inu]->GetYaxis()->SetTitle("Efficiency");
  }

  // CCnumu
  std::cout<<"CCnumu; "<<endl;
  const int nccnumudecaye = 2;
  TH1D* repiccnumu;
  TGraph* tgepiccnumu;
  TH1D* repiccnumuPost;
  TH1D* repiccnumuPostDB;
  TGraph* tgepiccnumuPost;

  {
      repiccnumu = (TH1D*)hprecut[2][0]->Clone();
      repiccnumu->Add(hprecut[2][1]);
      repiccnumu->Add(hprecut[2][2]);
      repiccnumu->Add(hprecut[3][0]);
      repiccnumu->Add(hprecut[3][1]);
      repiccnumu->Add(hprecut[3][2]);
      repiccnumu->SetName("repiccnumu");
      TH1D* denom = (TH1D*)htruefv[2][0]->Clone();
      denom->Add(htruefv[2][1]);
      denom->Add(htruefv[2][2]);
      denom->Add(htruefv[3][0]);
      denom->Add(htruefv[3][1]);
      denom->Add(htruefv[3][2]);
      repiccnumu->Divide(denom);

      for (int ibin=0; ibin<nbins; ibin++) {
	yvals[ibin] = repiccnumu->GetBinContent(ibin+1);
	xvals[ibin] = ibin;
      }

      tgepiccnumu = new TGraph(nbins,xvals,yvals);
      tgepiccnumu->SetLineColor(7);
      tgepiccnumu->SetLineWidth(4);
      tgepiccnumu->SetMarkerColor(7);
      tgepiccnumu->SetMarkerSize(1.5);
      tgepiccnumu->SetMarkerStyle(21);
      tgepiccnumu->GetXaxis()->SetTitleOffset(1.4);
      tgepiccnumu->GetXaxis()->SetTitle("True E_{#nu} (GeV)");
      tgepiccnumu->GetYaxis()->SetTitle("Efficiency");
  }

  {

      repiccnumuPostDB = (TH1D*)hpostcutrecDB[2][0]->Clone();
      repiccnumuPostDB->Add(hpostcutrecDB[2][1]);
      repiccnumuPostDB->Add(hpostcutrecDB[2][2]);
      repiccnumuPostDB->Add(hpostcutrecDB[3][0]);
      repiccnumuPostDB->Add(hpostcutrecDB[3][1]);
      repiccnumuPostDB->Add(hpostcutrecDB[3][2]);
      repiccnumuPostDB->SetName("repiccnumuPostDB");

      repiccnumuPost = (TH1D*)hpostcutrec[2][0]->Clone();
      repiccnumuPost->Add(hpostcutrec[2][1]);
      repiccnumuPost->Add(hpostcutrec[2][2]);
      repiccnumuPost->Add(hpostcutrec[3][0]);
      repiccnumuPost->Add(hpostcutrec[3][1]);
      repiccnumuPost->Add(hpostcutrec[3][2]);
      repiccnumuPost->SetName("repiccnumuPost");
      TH1D* denomPost = (TH1D*)hprecutrec[2][0]->Clone();
      denomPost->Add(hprecutrec[2][1]);
      denomPost->Add(hprecutrec[2][2]);
      denomPost->Add(hprecutrec[3][0]);
      denomPost->Add(hprecutrec[3][1]);
      denomPost->Add(hprecutrec[3][2]);
      repiccnumuPost->Divide(denomPost);

      for (int ibin=0; ibin<nbinsPost; ibin++) {
        yvalsPost[ibin] = repiccnumuPost->GetBinContent(ibin+1);
        xvalsPost[ibin] = ibin;
      }

      tgepiccnumuPost = new TGraph(nbinsPost,xvalsPost,yvalsPost);
      tgepiccnumuPost->SetLineColor(7);
      tgepiccnumuPost->SetLineWidth(4);
      tgepiccnumuPost->SetMarkerColor(7);
      tgepiccnumuPost->SetMarkerSize(1.5);
      tgepiccnumuPost->SetMarkerStyle(21);
      tgepiccnumuPost->GetXaxis()->SetTitleOffset(1.4);
      tgepiccnumuPost->GetXaxis()->SetTitle("Reco E_{#nu} (GeV)");
      tgepiccnumuPost->GetYaxis()->SetTitle("Efficiency");
  }

  // NC
  std::cout<<"NC; "<<std::endl;
  const int nncdecaye = 2;
  TH1D* repinc;
  TGraph* tgepinc;
  TH1D* repincPost;
  TH1D* repincPostDB;
  TGraph* tgepincPost;

  {
      repinc = (TH1D*)hprecut[0][3]->Clone();
      repinc->Add(hprecut[1][3]);
      repinc->Add(hprecut[2][3]);
      repinc->Add(hprecut[3][3]);
      repinc->SetName("repincPost");
      TH1D* denom = (TH1D*)htruefv[0][3]->Clone();
      denom->Add(htruefv[1][3]);
      denom->Add(htruefv[2][3]);
      denom->Add(htruefv[3][3]);
      repinc->Divide(denom);

      for (int ibin=0; ibin<nbins; ibin++) {
        yvals[ibin] = repinc->GetBinContent(ibin+1);
        xvals[ibin] = ibin;
      }

      tgepinc = new TGraph(nbins,xvals,yvals);
      tgepinc->SetLineColor(42);
      tgepinc->SetLineWidth(4);
      tgepinc->SetMarkerColor(42);
      tgepinc->SetMarkerSize(1.5);
      tgepinc->SetMarkerStyle(21);
      tgepinc->GetXaxis()->SetTitleOffset(1.4);
      tgepinc->GetXaxis()->SetTitle("True E_{#nu} (GeV)");
      tgepinc->GetYaxis()->SetTitle("Efficiency");

  }
  {
      repincPostDB = (TH1D*)hpostcutrecDB[0][3]->Clone();
      repincPostDB->Add(hpostcutrecDB[1][3]);
      repincPostDB->Add(hpostcutrecDB[2][3]);
      repincPostDB->Add(hpostcutrecDB[3][3]);
      repincPostDB->SetName("repincPostDB");

      repincPost = (TH1D*)hpostcutrec[0][3]->Clone();
      repincPost->Add(hpostcutrec[1][3]);
      repincPost->Add(hpostcutrec[2][3]);
      repincPost->Add(hpostcutrec[3][3]);
      repincPost->SetName("repincPost");
      TH1D* denomPost = (TH1D*)hprecutrec[0][3]->Clone();
      denomPost->Add(hprecutrec[1][3]);
      denomPost->Add(hprecutrec[2][3]);
      denomPost->Add(hprecutrec[3][3]);
      repincPost->Divide(denomPost);

      for (int ibin=0; ibin<nbinsPost; ibin++) {
	yvalsPost[ibin] = repincPost->GetBinContent(ibin+1);
	xvalsPost[ibin] = ibin;
      }

      tgepincPost = new TGraph(nbinsPost,xvalsPost,yvalsPost);
      tgepincPost->SetLineColor(42);
      tgepincPost->SetLineWidth(4);
      tgepincPost->SetMarkerColor(42);
      tgepincPost->SetMarkerSize(1.5);
      tgepincPost->SetMarkerStyle(21);
      tgepincPost->GetXaxis()->SetTitleOffset(1.4);
      tgepincPost->GetXaxis()->SetTitle("Reco E_{#nu} (GeV)");
      tgepincPost->GetYaxis()->SetTitle("Efficiency");

  }

  // Draw!

  std::cout << "Begin Drawing" << std::endl;

  for (int ide=0; ide<1; ide++) {
    TString canprefix = "eff_mr_decaye";
    canprefix += ide;
    for (int ir=0; ir<1; ir++) {
      TString canname = canprefix;
      canname += "_nrings";
      canname += (ir+2);

      double maxeff = 0.;
      const int ncurves = 8;
      double maxvals[ncurves] = {
	repiccqe[0]->GetMaximum(),
	repiccqe[1]->GetMaximum(),
	repiccpip[0]->GetMaximum(),
	repiccpip[1]->GetMaximum(),
	repiccother[0]->GetMaximum(),
	repiccother[1]->GetMaximum(),
	repiccnumu->GetMaximum(),
	repinc->GetMaximum()};
      
      
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
      
      tgepiccqe[0]->Draw("same LP");
      tgepiccqe[1]->Draw("same LP");
      tgepiccpip[0]->Draw("same LP");
      tgepiccpip[1]->Draw("same LP");
      tgepiccother[0]->Draw("same LP");
      tgepiccother[1]->Draw("same LP");
      tgepiccnumu->Draw("same LP");
      tgepinc->Draw("same LP");
      canname += ".png";
      tcan->Print(canname);
      
      legend = new TLegend(0.1, 0.6, 0.25, 0.9);
      legend->SetHeader("curves");
      legend->AddEntry(tgepiccqe[0],"CCQE nu 1","l");
      legend->AddEntry(tgepiccqe[1],"CCQE nu 2","l");
      legend->AddEntry(tgepiccpip[0],"CC pi+ 1","l");
      legend->AddEntry(tgepiccpip[1],"CC pi+ 2","l");
      legend->AddEntry(tgepiccother[0],"CC others 1","l");
      legend->AddEntry(tgepiccother[1],"CC others 2","l");
      legend->AddEntry(tgepiccnumu,"CC nu mu","l");
      legend->AddEntry(tgepinc,"NC","l");
      legend->Draw();
    }
  }

  for (int ide=0; ide<1; ide++) {
    TString canprefixPost = "eff_pose";
    canprefixPost += ide;
    for (int ir=0; ir<1; ir++) {
      TString cannamePost = canprefix;
      cannamePost += "_post_nrings";
      cannamePost += (ir+2);

      double maxeffPost = 0.;
      const int ncurvesPost = 8;
      double maxvalsPost[ncurvesPost] = {
        repiccqePost[0]->GetMaximum(),
        repiccqePost[1]->GetMaximum(),
        repiccpipPost[0]->GetMaximum(),
        repiccpipPost[1]->GetMaximum(),
        repiccotherPost[0]->GetMaximum(),
        repiccotherPost[1]->GetMaximum(),
        repiccnumuPost->GetMaximum(),
        repincPost->GetMaximum()};


      for (int ival=0; ival<ncurvesPost; ival++) {
        if (maxvalsPost[ival] > maxeffPost) {maxeffPost = maxvalsPost[ival];}
      }
      if (maxeffPost < 0.01) {maxeffPost = 0.01;}

      TCanvas* tcanPost = new TCanvas(cannamePost,cannamePost);
      TH2D* plotarea2Post = new TH2D("plotarea2Post","Postcut Ratios",1000,0.,8.,1000,0.,maxeffPost*1.1);
      for (int ibin=0; ibin<nbinsPost; ibin++) {
        int index = plotarea2Post->GetXaxis()->FindBin(ibin);
        plotarea2Post->GetXaxis()->SetBinLabel(index,sbinedgesPost[ibin]);
      }
      plotarea2Post->GetXaxis()->SetTitleOffset(1.4);
      plotarea2Post->GetXaxis()->SetTitle("Reco E_{#nu} (GeV)");
      plotarea2Post->GetYaxis()->SetTitle("Efficiency");
      plotarea2Post->Draw();

      tgepiccqePost[0]->Draw("same LP");
      tgepiccqePost[1]->Draw("same LP");
      tgepiccpipPost[0]->Draw("same LP");
      tgepiccpipPost[1]->Draw("same LP");
      tgepiccotherPost[0]->Draw("same LP");
      tgepiccotherPost[1]->Draw("same LP");
      tgepiccnumuPost->Draw("same LP");
      tgepincPost->Draw("same LP");
      cannamePost += ".png";
      tcanPost->Print(cannamePost);

      legend = new TLegend(0.1, 0.6, 0.25, 0.9);
      legend->SetHeader("curves");
      legend->AddEntry(tgepiccqePost[0],"CCQE nu 1","l");
      legend->AddEntry(tgepiccqePost[1],"CCQE nu 2","l");
      legend->AddEntry(tgepiccpipPost[0],"CC pi+ 1","l");
      legend->AddEntry(tgepiccpipPost[1],"CC pi+ 2","l");
      legend->AddEntry(tgepiccotherPost[0],"CC others 1","l");
      legend->AddEntry(tgepiccotherPost[1],"CC others 2","l");
      legend->AddEntry(tgepiccnumuPost,"CC nu mu","l");
      legend->AddEntry(tgepincPost,"NC","l");
      legend->Draw();
    }
  }

  TCanvas* c3 = new TCanvas();
  c3->Divide(nnutypes,ninttypes);    
  for (int nt=0; nt<nnutypes; nt++) {
    for (int it=0; it<ninttypes; it++) {
      c3->cd(ninttypes*nt + it +1);
      h2trueTOrecoPRE[nt][it]->SetTitle(Form("int type %d, nu type %d", it, nt));
      h2trueTOrecoPRE[nt][it]->Draw("colz");
    }
  }

   THStack *hs = new THStack("hs","");

   repiccnumuPostDB->SetFillColor(1);
   repincPostDB->SetFillColor(2);

   repiccSignal = (TH1D*)repiccqePostDB[0]->Clone();
   repiccSignal->Add(repiccpipPostDB[0]);
   repiccSignal->Add(repiccotherPostDB[0]);
   //repiccSignal->Add(repiccqePost[1]);
   //repiccSignal->Add(repiccpipPost[1]);
   //repiccSignal->Add(repiccotherPost[1]);
   repiccSignal->SetFillColor(4);

   hs->Add(repiccnumuPostDB);
   hs->Add(repincPostDB);   
   hs->Add(repiccSignal);

   new TCanvas();
   hs->Draw();

   legend = new TLegend(0.1, 0.6, 0.25, 0.9);
   legend->SetHeader("Stacked plot");
   legend->AddEntry(repiccnumuPostDB,"numu","f");
   legend->AddEntry(repincPostDB,"nc","f");
   legend->AddEntry(repiccSignal,"nue CC (all)","f");
   legend->Draw();


}
