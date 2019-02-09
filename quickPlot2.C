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

   Int_t fqmrnring[100];
   Float_t fq1rmom[10][10],fq1rnll[10][10];

   Int_t fqmrnring2[100];
   Float_t fq1rmom2[10][10],fq1rnll2[10][10];   

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

   TFile f("outputTest_vector_FHC.root");
   TTree* t = (TTree*)f.Get("h1");

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
   t->SetBranchAddress("fqmrnring",&fqmrnring);
   t->SetBranchAddress("fq1rmom", &fq1rmom);
   t->SetBranchAddress("fq1rnll", &fq1rnll);


   TH1D* h1[10];
   TH1D* h2[10];
   TH1D* h3[10];
   TH2D* h2D[10];
   double c_ss[100][100]={};
   double c_bb[100][100]={};
    
   for(Int_t i=0;i<10;i++){ 
   h1[i] = new TH1D("","",nBin-2,binEdge);
   h2[i] = new TH1D("","",nBin-2,binEdge);
   h3[i] = new TH1D("","",nBin-2,binEdge);
   h2D[i]= new TH2D("","",100,0,10,100,-1,1);
   }


   TFile f2("/home/guang/Downloads/root-6.14.02/builddir/tutorials/tmva/outputTree_reinput_FHC_step3run1.root");
   TTree* t2 = (TTree*)f2.Get("h1");

   t2->SetBranchAddress("erecmr", &erecmr2);
   t2->SetBranchAddress("fluxWeight", &fluxWeight2);
   t2->SetBranchAddress("tmvaMR0", &tmvaMR2);
   t2->SetBranchAddress("fqwall", &fqwall2);
   t2->SetBranchAddress("towall", &towall2);
   t2->SetBranchAddress("evis", &evis2);
   t2->SetBranchAddress("nhitac", &nhitac2);
   t2->SetBranchAddress("sigCategory", &sigCategory2);
   t2->SetBranchAddress("bkgCategory", &bkgCategory2);
   t2->SetBranchAddress("pnu", &pnu2);
   t2->SetBranchAddress("mode", &mode2);
   t2->SetBranchAddress("fqnse",&fqnse2);
   t2->SetBranchAddress("ipnu", &ipnu2);
   t2->SetBranchAddress("wallv", &wallv2);
   t2->SetBranchAddress("fqmrnring",&fqmrnring2);
   t2->SetBranchAddress("fq1rmom", &fq1rmom2);
   t2->SetBranchAddress("fq1rnll", &fq1rnll2);

   Long64_t NofEvent = t->GetEntries();

/*
   for (Long64_t jentry=0; jentry<NofEvent;jentry++) {
      t->GetEntry(jentry);

      if (jentry % 100000 == 0) {std::cout << jentry << " events processed" << std::endl;}

        if(abs(mode)> 30 ) h1[0]->Fill(pnu[0]);
        if(mode==1  && ipnu[0]==12) h1[1]->Fill(pnu[0]);
        if(abs(mode)<30 && abs(ipnu[0])==14) h1[2]->Fill(pnu[0]);
        if(abs(mode)!=1  && abs(mode)!=2 && abs(ipnu[0])==12) h1[3]->Fill(pnu[0]);

        // 50,51 elastic, 46 DIS 31-36 single pi, 38-45 others (single gamma, multi-pi, single eta, single K)
        if(abs(mode)>50) h1[4]->Fill(pnu[0]);
        if(abs(mode)==46) h1[5]->Fill(pnu[0]);
        if(abs(mode)>=31 && abs(mode)<=36) h1[6]->Fill(pnu[0]);
        if(abs(mode)>=38 && abs(mode)<=45) h1[7]->Fill(pnu[0]);
   }

   Long64_t NofEvent2 = t2->GetEntries();

   for (Long64_t jentry=0; jentry<NofEvent2;jentry++) {
      t2->GetEntry(jentry);

      if (jentry % 100000 == 0) {std::cout << jentry << " events processed" << std::endl;}

        if(abs(mode2)> 30 ) h2[0]->Fill(pnu2[0]);
        if(mode2==1  && ipnu2[0]==12) h2[1]->Fill(pnu2[0]);
        if(abs(mode2)<30 && abs(ipnu2[0])==14) h2[2]->Fill(pnu2[0]);
        if(abs(mode2)!=1  && abs(mode2)!=2 && abs(ipnu2[0])==12) h2[3]->Fill(pnu2[0]);

        // 50,51 elastic, 46 DIS 31-36 single pi, 38-45 others (single gamma, multi-pi, single eta, single K)
        if(abs(mode2)>50) h2[4]->Fill(pnu2[0]);
        if(abs(mode2)==46) h2[5]->Fill(pnu2[0]);
        if(abs(mode2)>=31 && abs(mode2)<=36) h2[6]->Fill(pnu2[0]);
        if(abs(mode2)>=38 && abs(mode2)<=45) h2[7]->Fill(pnu2[0]);
   }
*/
   bool passing  = false;
   bool passing2 = false;

   for (Long64_t jentry=0; jentry<NofEvent;jentry++) {
      t->GetEntry(jentry);  

      if (jentry % 100000 == 0) {std::cout << jentry << " events processed" << std::endl;}

      if(nhitac<16 && fqwall > 200 && fq1rmom[0][1] > 30 && fq1rnll[0][2]-fq1rnll[0][1] > fq1rmom[0][1]*0.2 && fqmrnring[0] == 1 && fqnse == 1) passing = true;
      else passing = false;

      if(wallv > 200 && passing){
        if(abs(mode)> 30 ) h1[0]->Fill(pnu[0], fluxWeight[1] * (50/22.5) );
        if(mode==1  && ipnu[0]==12) h1[1]->Fill(pnu[0], fluxWeight[1]* (50/22.5));
        if(abs(mode)<30 && mode == 1 && abs(ipnu[0])==14) h1[2]->Fill(pnu[0], fluxWeight[1]* (50/22.5));
        if(abs(mode)<30 && abs(mode)>2 && abs(ipnu[0])==14) h1[3]->Fill(pnu[0], fluxWeight[1]* (50/22.5));

        //if(mode==1 && ipnu[0]==12) h1[8]->Fill(pnu[0], fluxWeight[0]* (50/22.5)* 10);
        //if(abs(mode)!=1  && abs(mode)!=2 && abs(mode) < 30 && abs(ipnu[0])==12) h1[9]->Fill(pnu[0], fluxWeight[0]* (50/22.5)* 10);

        // 50,51 elastic, 46 DIS 31-36 single pi, 38-45 others (single gamma, multi-pi, single eta, single K)
        if(abs(mode)>50) h1[4]->Fill(pnu[0], fluxWeight[1]* (50/50.000)* (50/22.5));
	if(abs(mode)==46) h1[5]->Fill(pnu[0], fluxWeight[1]* (50/50.000)* (50/22.5));
	if(abs(mode)>=31 && abs(mode)<=36) h1[6]->Fill(pnu[0], fluxWeight[1]* (50/50.000)* (50/22.5));
	if(abs(mode)>=38 && abs(mode)<=45) h1[7]->Fill(pnu[0], fluxWeight[1]* (50/50.000)* (50/22.5));
      }
   }

   Long64_t NofEvent2 = t2->GetEntries();
   for (Long64_t jentry=0; jentry<NofEvent2;jentry++) {
      t2->GetEntry(jentry);

      if (jentry % 100000 == 0) {std::cout << jentry << " events processed" << std::endl;}

      if(nhitac2<16 && fqwall2 > 200 && fq1rmom2[0][1] > 30 && fq1rnll2[0][2]-fq1rnll2[0][1] > fq1rmom2[0][1]*0.2 && fqmrnring2[0] == 2 && fqnse2 == 1 && tmvaMR2 > 0) passing2 = true;
      else passing2 = false;

      if(wallv2 > 200 && passing2){
        if(abs(mode2)> 30 ) h2[0]->Fill(pnu2[0], fluxWeight2[1]* (50/22.5) );
        if(mode2==1  && ipnu2[0]==12) h2[1]->Fill(pnu2[0], fluxWeight2[1]* (50/22.5) );
        if(abs(mode2)<30 && abs(ipnu2[0])==14) h2[2]->Fill(pnu2[0], fluxWeight2[1]* (50/22.5) );
        if(abs(mode2)!=1  && abs(mode2)!=2 && abs(mode2) < 30 && abs(ipnu2[0])==12) h2[3]->Fill(pnu2[0], fluxWeight2[1]* (50/22.5) );

        // 50,51 elastic, 46 DIS 31-36 single pi, 38-45 others (single gamma, multi-pi, single eta, single K)
        if(abs(mode2)>50) h2[4]->Fill(pnu2[0], fluxWeight2[1]* (50/22.5));
        if(abs(mode2)==46) h2[5]->Fill(pnu2[0], fluxWeight2[1]* (50/22.5));
        if(abs(mode2)>=31 && abs(mode2)<=36) h2[6]->Fill(pnu2[0], fluxWeight2[1]* (50/22.5));
        if(abs(mode2)>=38 && abs(mode2)<=45) h2[7]->Fill(pnu2[0], fluxWeight2[1]* (50/22.5));
      }
   }

   for(Int_t i=0;i<8;i++){
   h3[i]->Divide(h2[i],h1[i]);
   }
	
   TCanvas* c0 = new TCanvas();
   c0->Divide(2,2);
   c0->cd(1);
   h1[0]->GetXaxis()->SetTitle("nc energy [GeV]");
   h1[0]->GetYaxis()->SetTitle("Events");
   h1[0]->SetMarkerColor(2);
   h1[0]->SetLineColor(2);
   h1[0]->Draw("hist");
   TGraph* g1 = new TGraph("input/fromGLOBES_bg_v2.txt","%lg %*lg %lg %*lg %*lg","");
   g1->Draw("same");

   c0->cd(2);
   h1[1]->GetXaxis()->SetTitle("nue ccqe energy [GeV]");
   h1[1]->GetYaxis()->SetTitle("Events");
   h1[1]->SetMarkerColor(2);
   h1[1]->SetLineColor(2);
   h1[1]->Draw("hist");
   TGraph* g2 = new TGraph("input/fromGLOBES_signal_v2.txt","%lg %lg %*lg","");
   g2->Draw("same");

   c0->cd(3);
   h1[2]->GetXaxis()->SetTitle("numu energy [GeV]");
   h1[2]->GetYaxis()->SetTitle("Events");
   h1[2]->SetMarkerColor(2);
   h1[2]->SetLineColor(2);
   h1[2]->Draw("hist");
   TGraph* g3 = new TGraph("input/fromGLOBES_bg_v2.txt","%lg %lg ","");
   g3->Draw("same");

   c0->cd(4);
   h1[3]->GetXaxis()->SetTitle("nue ccnqe energy [GeV]");
   h1[3]->GetYaxis()->SetTitle("Events");
   h1[3]->SetMarkerColor(2);
   h1[3]->SetLineColor(2);
   h1[3]->Draw("hist");
   TGraph* g4 = new TGraph("input/fromGLOBES_signal_v2.txt","%lg %*lg %lg");
   g4->Draw("same");
/*
   c0->cd(5);
   h1[8]->GetXaxis()->SetTitle("nue CC nu unoscillated energy [GeV]");
   h1[8]->GetYaxis()->SetTitle("Events");
   h1[8]->SetMarkerColor(2);
   h1[8]->SetLineColor(2);
   h1[8]->Draw("hist");
   TGraph g5("input/fromGLOBES_bg_v2.txt");
   g5->Draw("same");

   c0->cd(6);
   h1[9]->GetXaxis()->SetTitle("nue CC non-QE unoscillated nu energy [GeV]");
   h1[9]->GetYaxis()->SetTitle("Events");
   h1[9]->SetMarkerColor(2);
   h1[9]->SetLineColor(2);
   h1[9]->Draw("hist");
   TGraph g6("input/fromGLOBES_nue_ccnqe_unoscillated.txt");
   g6->Draw("same");
*/
   TFile *ff = new TFile("simpleRatio.root","RECREATE"); 
   TCanvas* c1 = new TCanvas();
   c1->Divide(2,2);
   c1->cd(1);
   h3[0]->SetXTitle("NC nu energy");
   h3[0]->Draw("");

   c1->cd(2);
   h3[1]->SetXTitle("nue CCQE energy");
   h3[1]->Draw("");

   c1->cd(3);
   h3[2]->SetXTitle("numu CC energy");
   h3[2]->Draw("");

   c1->cd(4);
   h3[3]->SetXTitle("nue CC non-QE energy");
   h3[3]->Draw("");

   h3[0]->Write("nc");
   h3[1]->Write("nueccqe");
   h3[2]->Write("numu");
   h3[3]->Write("nueccnqe");
   ff->Write();


   TCanvas* c2 = new TCanvas();
   c2->Divide(2,2);
   c2->cd(1);
   h3[4]->SetXTitle("NC elastic energy");
   h3[4]->Draw("");

   c2->cd(2);
   h3[5]->SetXTitle("NC DIS energy");
   h3[5]->Draw("");

   c2->cd(3);
   h3[6]->SetXTitle("NC single pi energy");
   h3[6]->Draw("");

   c2->cd(4);
   h3[7]->SetXTitle("NC other energy");
   h3[7]->Draw("");


   TCanvas* c3 = new TCanvas();
   c3->Divide(2,2);
   c3->cd(1);
   h2[4]->SetXTitle("NC elastic energy");
   h2[4]->Draw("");

   c3->cd(2);
   h2[5]->SetXTitle("NC DIS energy");
   h2[5]->Draw("");

   c3->cd(3);
   h2[6]->SetXTitle("NC single pi energy");
   h2[6]->Draw("");

   c3->cd(4);
   h2[7]->SetXTitle("NC other energy");
   h2[7]->Draw("");


}
