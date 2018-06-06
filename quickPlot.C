{
   Double_t erecmr, fluxWeight[2], tmvaMR, fqwall, towall;
   Float_t  pnu[50];
   Int_t sigCategory, bkgCategory;
   Float_t evis;
   UInt_t nhitac;
   Int_t mode;


   TFile f("outputTree_reinput0.root");
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

   
   TH1D* h1[10];
   TH2D* h2[10];
   for(Int_t i=0;i<10;i++){ 
   h1[i] = new TH1D("","",100,0,10);
   h2[i] = new TH2D("","",100,0,10,100,0,10);
   }

   Long64_t nbytes = 0, nb = 0;
   NofEvent = 300000; //t->GetEntries();

   for (Long64_t jentry=0; jentry<NofEvent;jentry++) {
      t->GetEntry(jentry);  

      if (jentry % 100000 == 0) {std::cout << jentry << " events processed" << std::endl;}

      //cout<<"erecmr sigCategory towall evis nhitac fluxWeight[0] fluxWeight[1] : "<<erecmr<<" "<<sigCategory<<" "<<fqwall<<" "<<evis<<" "<<nhitac<<" "<<fluxWeight[0]<<" "<<fluxWeight[1]<<endl;

      if(fqwall>200 && evis > 30 && nhitac < 16){
	if(sigCategory>=0) h1[0]->Fill(erecmr, fluxWeight[1]);
	if(bkgCategory>=0) h1[1]->Fill(erecmr, fluxWeight[1]);

        if(tmvaMR > 0){

	if((abs(mode)==1)||(abs(mode)==2)) {h2[0]->Fill(pnu[0],erecmr);}
	if((abs(mode)==11)||(abs(mode)==13)||(abs(mode)==16)) {h2[1]->Fill(pnu[0],erecmr);}
	else if((abs(mode)<30)) {h2[2]->Fill(pnu[0],erecmr);}
	else if((abs(mode)>30)) {h2[3]->Fill(pnu[0],erecmr);}

        if(sigCategory>=0) h1[2]->Fill(erecmr, fluxWeight[1]);
        if(bkgCategory>=0) h1[3]->Fill(erecmr, fluxWeight[1]);
	}
      }

   }
	

   THStack *hs = new THStack("hs","");
   h1[1]->SetFillColor(2);
   hs->Add(h1[1]);
   h1[0]->SetFillColor(4);
   hs->Add(h1[0]);

   THStack *hs2 = new THStack("hs2","");
   h1[3]->SetFillColor(2);
   hs2->Add(h1[3]);
   h1[2]->SetFillColor(4);
   hs2->Add(h1[2]);

   new TCanvas();
   hs->Draw();
   
   new TCanvas();
   hs2->Draw();

   TCanvas* c1 = new TCanvas();
   c1->Divide(2,2);
   for(Int_t i=0;i<4;i++){
   c1->cd(i+1);
   h2[i]->Draw("colz");
   }
}
