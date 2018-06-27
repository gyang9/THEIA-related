{
   Double_t erecmr, fluxWeight[2], tmvaMR, fqwall, towall;
   Float_t  pnu[50];
   Int_t sigCategory, bkgCategory;
   Float_t evis;
   UInt_t nhitac;
   Int_t mode;
   Int_t fqnse;
   Int_t ipnu[50];

   TFile f("outputTest.root");
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

   TH1D* h1[10];
   TH2D* h2[10];
   TH2D* h2D[10];
   double c_ss[100][100]={};
   double c_bb[100][100]={};
    
   for(Int_t i=0;i<10;i++){ 
   h1[i] = new TH1D("","",100,0,10);
   h2[i] = new TH2D("","",100,0,10,100,0,10);
   h2D[i]= new TH2D("","",100,0,10,100,-1,1);
   }

   Long64_t nbytes = 0, nb = 0;
   NofEvent = t->GetEntries();

   for (Long64_t jentry=0; jentry<NofEvent;jentry++) {
      t->GetEntry(jentry);  

      if (jentry % 100000 == 0) {std::cout << jentry << " events processed" << std::endl;}

        if(sigCategory>0 && pnu[0]>0 && pnu[0]<10) h1[0]->Fill(pnu[0], fluxWeight[1]);
        if(sigCategory>0 && erecmr>0 && erecmr<10) h1[1]->Fill(erecmr, fluxWeight[1]);

   }
	
   new TCanvas();
   h1[0]->GetXaxis()->SetTitle("erec [GeV]");
   h1[0]->GetYaxis()->SetTitle("Events");
   h1[0]->Draw("");

   new TCanvas();
   h1[1]->GetXaxis()->SetTitle("erec [GeV]");
   h1[1]->GetYaxis()->SetTitle("Events");
   h1[1]->Draw("");

}
