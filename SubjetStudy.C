void SubjetStudy(TString cFiles2, std::string date)
{
  
  ifstream infile2;
  infile2.open(cFiles2.Data());
  char filename2[300];

  Double_t ptjet, lnR, lnkt, ptjet_part, lnR_part, lnkt_part;
  Double_t sub1, sub2;

  Double_t xbins[5];
  xbins[0]=20;
  xbins[1]=40;
  xbins[2]=60;
  xbins[3]=80;
  xbins[4]=120;

  Double_t ybins[8];
  ybins[0] = 0.;
  ybins[1] = 0.2;
  ybins[2] = 0.4;
  ybins[3] = 0.6;
  ybins[4] = 0.8;
  ybins[5] = 1.0;
  ybins[6] = 1.2;
  ybins[7] = 1.4;

  Double_t zbins[12];
  zbins[0]=-1;
  zbins[1]=-0.75;
  zbins[2]=-0.5;
  zbins[3]=-0.3;
  zbins[4]=-0.1;
  zbins[5] = 0.;
  zbins[6] = 0.1;
  zbins[7] = 0.3;
  zbins[8] = 0.5;
  zbins[9] = 0.75;
  zbins[10] = 1;
  zbins[11] = 1.5;
  
  TH3D* h = new TH3D("h", "h", 7, ybins, 11, zbins, 4, xbins);
  h->Sumw2();
  TH3D* h_1 = new TH3D("h_1", "h_1", 7, ybins, 11, zbins, 4, xbins);
  h_1->Sumw2();
  TH3D* h_2 = new TH3D("h_2", "h_2", 7, ybins, 11, zbins, 4, xbins);
  h_2->Sumw2();
  TH3D* h_10 = new TH3D("h_10", "h_10", 7, ybins, 11, zbins, 4, xbins);
  h_10->Sumw2();
  TH3D* h_11 = new TH3D("h_11", "h_11", 7, ybins, 11, zbins, 4, xbins);
  h_11->Sumw2();
  TH3D* h_00 = new TH3D("h_00", "h_00", 7, ybins, 11, zbins, 4, xbins);
  h_00->Sumw2();
  TH3D* h_01 = new TH3D("h_01", "h_01", 7, ybins, 11, zbins, 4, xbins);
  h_01->Sumw2();
  
  while(infile2>>filename2){
    int pthardbin=0;

    TFile *input=TFile::Open(filename2);
    TList *list=(TList*) input->Get("JetSubstructure_Jet_AKTChargedR040_tracks_pT0150_E_scheme_TCRaw_PythiaDef_NoSub_Incl");
    //    TList *list2=(TList*) list->FindObject("EventCuts");
    //    TH1D *hcent=(TH1D*)list2->FindObject("Centrality_selected");
    TProfile *hcross=(TProfile*)list->FindObject("fHistXsection");
    TH1D *htrials=(TH1D*)list->FindObject("fHistTrials");
    TH1D *hpthard=(TH1D*)list->FindObject("fHistPtHard");
    TH1D *hnevent=(TH1D*)list->FindObject("fHistEventCount");
    for(Int_t i=1;i<=htrials->GetNbinsX();i++){
      if(htrials->GetBinContent(i)!=0) pthardbin=i;}
    cout  << pthardbin << endl;
    double scalefactor=(hcross->Integral(pthardbin,pthardbin)*hcross->GetEntries())/htrials->Integral(pthardbin,pthardbin);

    TFile *input2=TFile::Open(filename2);
    TTree *mc=(TTree*)input2->Get("JetSubstructure_Jet_AKTChargedR040_tracks_pT0150_E_scheme_TCRawTree_PythiaDef_NoSub_Incl");
    Int_t nEv=mc->GetEntries();

    mc->SetBranchAddress("ptjet", &ptjet);
    mc->SetBranchAddress("ptjet_part", &ptjet_part);
    mc->SetBranchAddress("lnR", &lnR);
    mc->SetBranchAddress("lnR_part", &lnR_part);
    mc->SetBranchAddress("lnkt", &lnkt);
    mc->SetBranchAddress("lnkt_part", &lnkt_part);
    mc->SetBranchAddress("sub1", &sub1);
    mc->SetBranchAddress("sub2", &sub2);
    Int_t countm=0;
    for(int iEntry=0; iEntry< nEv; iEntry++){
      mc->GetEntry(iEntry);
      h->Fill(lnR, lnkt, ptjet, scalefactor);
      if (sub1 == 1){
	h_1->Fill(lnR, lnkt, ptjet, scalefactor);
	if (sub2 == 1) h_11->Fill(lnR, lnkt, ptjet, scalefactor);
	else h_10->Fill(lnR, lnkt, ptjet, scalefactor);
      }
      if (sub2 == 1){
	h_2->Fill(lnR, lnkt, ptjet, scalefactor);
	if (sub1 == 0) h_01->Fill(lnR, lnkt, ptjet, scalefactor);
      }
      if ((sub1 == 0) && (sub2 == 0)) h_00->Fill(lnR, lnkt, ptjet, scalefactor);
    }
  }

  TFile* fout = new TFile("SubjetStudies_hist_Oct6.root", "recreate");
  fout->cd("/");
  h->Write();
  h_1->Write();
  h_2->Write();
  h_11->Write();
  h_10->Write();
  h_01->Write();
  h_00->Write();
  fout->Close();
}


   
   
   

   
   
