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

      //cout<<"erecmr sigCategory towall evis nhitac fluxWeight[0] fluxWeight[1] : "<<erecmr<<" "<<sigCategory<<" "<<fqwall<<" "<<evis<<" "<<nhitac<<" "<<fluxWeight[0]<<" "<<fluxWeight[1]<<endl;

      if(fqwall>200 && evis > 30 && nhitac < 16 && fqnse <= 2 ){
	if(sigCategory>=0) h1[0]->Fill(erecmr, fluxWeight[1]);
	if(bkgCategory>=0) h1[1]->Fill(erecmr, fluxWeight[1]);

	if(sigCategory>=0) h2D[0]->Fill(erecmr,tmvaMR,fluxWeight[1]);
        if(bkgCategory>=0) h2D[1]->Fill(erecmr,tmvaMR,fluxWeight[1]);

        if(sigCategory>=0 && ((abs(mode)==1)||(abs(mode)==2)) ) h2D[2]->Fill(erecmr,tmvaMR,fluxWeight[1]);
        if(bkgCategory>=0 && ((abs(mode)==1)||(abs(mode)==2)) ) h2D[3]->Fill(erecmr,tmvaMR,fluxWeight[1]);
        if(sigCategory>=0 && ((abs(mode)==11)||(abs(mode)==13)||(abs(mode)==16))) h2D[4]->Fill(erecmr,tmvaMR,fluxWeight[1]);
        if(bkgCategory>=0 && (abs(mode)>30)) h2D[5]->Fill(erecmr,tmvaMR,fluxWeight[1]);

	for(Int_t ii=0;ii<60;ii++){
		if(erecmr<1 && tmvaMR > -0.3 + 0.01*ii) {if(sigCategory>=0) c_ss[0][ii]++; if(bkgCategory>=0) c_bb[0][ii]++;}
		if(erecmr<2 && erecmr>1 && tmvaMR > -0.3 + 0.01*ii) {if(sigCategory>=0)c_ss[1][ii]++; if(bkgCategory>=0)c_bb[1][ii]++;}
		if(erecmr<3 && erecmr>2 && tmvaMR > -0.3 + 0.01*ii) {if(sigCategory>=0)c_ss[2][ii]++; if(bkgCategory>=0)c_bb[2][ii]++;}
	       	if(erecmr<4 && erecmr>3 && tmvaMR > -0.3 + 0.01*ii) {if(sigCategory>=0)c_ss[3][ii]++; if(bkgCategory>=0)c_bb[3][ii]++;}
	        if(erecmr<5 && erecmr>4 && tmvaMR > -0.3 + 0.01*ii) {if(sigCategory>=0)c_ss[4][ii]++; if(bkgCategory>=0)c_bb[4][ii]++;}
	        if(erecmr<6 && erecmr>5 && tmvaMR > -0.3 + 0.01*ii) {if(sigCategory>=0)c_ss[5][ii]++; if(bkgCategory>=0)c_bb[5][ii]++;}
	        if(erecmr<7 && erecmr>6 && tmvaMR > -0.3 + 0.01*ii) {if(sigCategory>=0)c_ss[6][ii]++; if(bkgCategory>=0)c_bb[6][ii]++;}
	        if(erecmr<8 && erecmr>7 && tmvaMR > -0.3 + 0.01*ii) {if(sigCategory>=0)c_ss[7][ii]++; if(bkgCategory>=0)c_bb[7][ii]++;}
	        if(erecmr>8 && tmvaMR > -0.3 + 0.01*ii) {if(sigCategory>=0)c_ss[8][ii]++; if(bkgCategory>=0)c_bb[8][ii]++;}
	}

	//std::cout<<"tmva for ipnu[0] and mode "<<ipnu[0]<<" "<<mode<<" "<<tmvaMR<<std::endl;
        if(tmvaMR > 0.){

	if((abs(mode)==1)||(abs(mode)==2)) {h2[0]->Fill(pnu[0],erecmr);}
	if((abs(mode)==11)||(abs(mode)==13)||(abs(mode)==16)) {h2[1]->Fill(pnu[0],erecmr);}
	else if((abs(mode)<30)) {h2[2]->Fill(pnu[0],erecmr);}
	else if((abs(mode)>30)) {h2[3]->Fill(pnu[0],erecmr);}

        if(sigCategory>=0) h1[2]->Fill(erecmr, fluxWeight[1]);
        if(bkgCategory>=0) h1[3]->Fill(erecmr, fluxWeight[1]);
	}
      }

   }
	
   double curr_sOb[8]={-100,-100,-100,-100,-100,-100,-100,-100};
   double locTMVA[8]={};
   std::cout<<"trying to see the results of tmva cuts.. "<<std::endl;
   for(Int_t ii=0;ii<9;ii++){
	for(Int_t jj=0;jj<60;jj++){
		if(c_ss[ii][jj]/TMath::Sqrt(c_ss[ii][jj]+c_bb[ii][jj])>curr_sOb[ii] ) {curr_sOb[ii] = c_ss[ii][jj]/TMath::Sqrt(c_ss[ii][jj]+c_bb[ii][jj]); locTMVA[ii] = jj; std::cout<<ii<<" "<<c_ss[ii][jj]/TMath::Sqrt(c_ss[ii][jj]+c_bb[ii][jj])<<std::endl; }
	}
   }
   std::cout<<std::endl;
   std::cout<<"locations of TMVAs for 0-1, 1-2, .... 7-8, >8 are:  ";
   for(Int_t ii=0;ii<9;ii++){cout<< " "<< locTMVA[ii]*0.01 - 0.3 <<"  ";}
   std::cout<<std::endl;

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

   new TCanvas();
   h2D[0]->GetXaxis()->SetTitle("erec [GeV]");
   h2D[0]->GetYaxis()->SetTitle("TMVA");
   h2D[0]->Draw("colz");

   new TCanvas();
   h2D[1]->GetXaxis()->SetTitle("erec [GeV]");
   h2D[1]->GetYaxis()->SetTitle("TMVA");
   h2D[1]->Draw("colz");

   TCanvas* c2 = new TCanvas();
   c2->Divide(2,2);
   for(Int_t i=0;i<4;i++){
   c2->cd(i+1);
   h2D[i+2]->Draw("colz");
   }

   TCanvas* c1 = new TCanvas();
   c1->Divide(2,2);
   for(Int_t i=0;i<4;i++){
   c1->cd(i+1);
   h2[i]->Draw("colz");
   }
}
