void DrawResp(std::string file, std::string date)
{
  TFile* f = new TFile(file.c_str());
  std::stringstream ss;
  ss << "h3_pT";
  TH2D* h2 = (TH2D*)f->Get(ss.str().c_str());
  ss.str("");

  TCanvas* c = new TCanvas("c", "c", 600, 500);
  gStyle->SetOptStat(0);
  gPad->SetLogz();
  
  //  TH2D* h2 = (TH2D*)h3->Project3D("zy");
  h2->GetXaxis()->SetTitleSize(0.05);
  h2->GetYaxis()->SetTitleSize(0.05);
  h2->SetTitle("");
  ss.str("");
  h2->GetZaxis()->SetRangeUser(1e-10, 1e-6);
  h2->GetXaxis()->SetTitle("p_{T}^{true}");
  h2->GetYaxis()->SetTitle("p_{T}^{reco}");
  h2->Draw("colz");

  ss << "figures/Resp_pT";
  ss << "_" << date << ".pdf";
  c->SaveAs(ss.str().c_str());
}
  
