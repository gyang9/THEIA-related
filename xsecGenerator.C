{
   Double_t erecmr, fluxWeight[2], tmvaMR, fqwall, towall;
   Float_t  pnu[50];
   Int_t sigCategory, bkgCategory;
   Float_t evis;
   UInt_t nhitac;
   Int_t mode;
   Int_t fqnse;
   Int_t ipnu[50];

   Double_t erecmr2, fluxWeight2[2], tmvaMR2, fqwall2, towall2;
   Float_t  pnu2[50];
   Int_t sigCategory2, bkgCategory2;
   Float_t evis2;
   UInt_t nhitac2;
   Int_t mode2;
   Int_t fqnse2;
   Int_t ipnu2[50];
   Float_t wallv,wallv2;

   int nBin=0; 
   double binEdge[200]={};
   double binValue[200]={};
   ifstream in;
   in.open("input/fromGLOBES_nc.txt");
   while(!in.eof()){
     in >> binEdge[nBin] >> binValue[nBin];
     std::cout<<nBin<<" "<<binEdge[nBin]<<" "<<binValue[nBin]<<std::endl;
     nBin++;
   }

   TFile f("outputTest_temp.root");
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
   t->SetBranchAddress("wallv", &wallv);

   TH1D* h1[10];
   TH1D* h2[10];
   TH1D* h3[10];
   TH2D* h2D[10];
   double c_ss[100][100]={};
   double c_bb[100][100]={};
    
   for(Int_t i=0;i<10;i++){ 
   h1[i] = new TH1D("","",100,0,10);
   h2[i] = new TH1D("","",nBin-2,binEdge);
   h3[i] = new TH1D("","",nBin-2,binEdge);
   h2D[i]= new TH2D("","",100,0,10,100,-1,1);
   }

   TString atmFlux = "input/hondaFlux_AllDirectionAveraged.txt";

   TGraph * gAtmNumu     = new TGraph(atmFlux, "%lg %lg" , "");
   TGraph * gAtmNumubar  = new TGraph(atmFlux, "%lg %*lg %lg", "");
   TGraph * gAtmNue    = new TGraph(atmFlux, "%lg %*lg %*lg %lg", "");
   TGraph * gAtmNuebar = new TGraph(atmFlux, "%lg %*lg %*lg %*lg %lg", "");

   double scalingFactor = 500 * 365. * 24. * 60. * 60. * 0.01 * 0.01 * 4. * 3.14 * (25. * 1000.*1000./(1.7* 1E-27));

   Long64_t NofEvent = t->GetEntries();
   for (Long64_t jentry=0; jentry<NofEvent/1.;jentry++) {
      t->GetEntry(jentry);

      if (jentry % 100000 == 0) {std::cout << jentry << " events processed" << std::endl;}

      if(wallv > 200 && gAtmNumu->Eval(pnu[0])*scalingFactor != 0){
	//cout<< scalingFactor<<" "<<1./(gAtmNumu->Eval(pnu[0])*scalingFactor)<<endl;
        if(ipnu[0] == 14 && mode ==1 ) h1[0]->Fill(pnu[0],  1./(gAtmNumu->Eval(pnu[0])*scalingFactor) );
        else if(ipnu[0] == 14 && mode ==2) h1[1]->Fill(pnu[0], 1./(gAtmNumu->Eval(pnu[0])*scalingFactor));
        else if(ipnu[0] == 12 && mode == 1) h1[2]->Fill(pnu[0], 1./(gAtmNue->Eval(pnu[0])*scalingFactor));
        else if(ipnu[0] == 14 && mode <30) h1[3]->Fill(pnu[0], 1./(gAtmNumu->Eval(pnu[0])*scalingFactor));

      }
   }

   for(Int_t i = 0; i < h1[0]->GetNbinsX(); i++){
       h1[0]->SetBinContent(i+1,h1[0]->GetBinContent(i+1)/h1[0]->GetBinWidth(i+1)/h1[0]->GetBinCenter(i+1));
       h1[1]->SetBinContent(i+1,h1[1]->GetBinContent(i+1)/h1[1]->GetBinWidth(i+1)/h1[1]->GetBinCenter(i+1));
       h1[2]->SetBinContent(i+1,h1[2]->GetBinContent(i+1)/h1[2]->GetBinWidth(i+1)/h1[2]->GetBinCenter(i+1));
       h1[3]->SetBinContent(i+1,h1[3]->GetBinContent(i+1)/h1[3]->GetBinWidth(i+1)/h1[3]->GetBinCenter(i+1));
   }
	
   TCanvas* c0 = new TCanvas();
   h1[0]->SetLineColor(kBlack);
   h1[1]->SetLineColor(kRed);
   h1[2]->SetLineColor(kGreen);
   h1[3]->SetLineColor(kBlue);
   h1[0]->SetLineWidth(3);
   h1[1]->SetLineWidth(3);
   h1[2]->SetLineWidth(3);
   h1[3]->SetLineWidth(3);
   h1[0]->SetXTitle("neutrino energy");
   h1[0]->Draw();
   h1[1]->Draw("same");
   h1[2]->Draw("same");
   h1[3]->Draw("same");

      TLegend* legend = new TLegend(0.1, 0.6, 0.25, 0.9);
      legend->AddEntry(h1[0],"numu ccqe","l");
      legend->AddEntry(h1[1],"numu 2p2h","l");
      legend->AddEntry(h1[2],"nue ccqe","l");
      legend->AddEntry(h1[3],"numu cc other","l");
      legend->Draw();


}
