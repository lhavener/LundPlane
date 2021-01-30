void Reweighting(std::string file_mc, std::string file_data, std::string date)
{
  TFile* fmc = new TFile(file_mc.c_str());
  TH3D* h3_mc = (TH3D*)fmc->Get("true_match");
  h3_mc->SetName("h3_mc");
  TFile* fdata = new TFile(file_data.c_str());
  TH3D* h3_data = (TH3D*)fdata->Get("true_match");
  h3_data->SetName("h3_data");
  std::stringstream ss;

  TCanvas* c = new TCanvas("c", "c", 1200, 500);
  c->Divide(3, 1);
  gStyle->SetOptStat(0);
  //  gPad->SetLogz();

  TLegend* leg = new TLegend(0.52, 0.6, 0.7, 0.8);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  leg->SetTextSize(0.045);

  c->cd(1);
  TH1D* h1_mc_x = (TH1D*)h3_mc->ProjectionX("h1_mc_x", 2, 12, 2, 5);
  TH1D* h1_data_x = (TH1D*)h3_data->ProjectionX("h1_data_x", 2, 12, 2, 5);
  h1_mc_x->Scale(1./h1_mc_x->Integral(), "width");
  h1_data_x->Scale(1./h1_data_x->Integral(), "width");
  h1_mc_x->GetXaxis()->SetTitle("ln(#it{R}/#Delta#it{R}^{true})");
  h1_mc_x->SetLineColor(kBlue);
  h1_mc_x->SetMarkerColor(kBlue);
  h1_mc_x->SetTitle("");
  h1_mc_x->Draw();
  h1_data_x->SetLineColor(kRed);
  h1_data_x->SetMarkerColor(kRed);
  h1_data_x->Draw("same");
  leg->AddEntry(h1_mc_x, "Before weighting");
  leg->AddEntry(h1_data_x, "After weighting");
  leg->Draw("same");

  c->cd(2);
  TH1D* h1_mc_y = (TH1D*)h3_mc->ProjectionY("h1_mc_y", 1, 7, 2, 5);
  TH1D* h1_data_y = (TH1D*)h3_data->ProjectionY("h1_data_y", 1, 7, 2, 5);
  h1_mc_y->Scale(1./h1_mc_y->Integral(), "width");
  h1_data_y->Scale(1./h1_data_y->Integral(), "width");
  h1_mc_y->GetXaxis()->SetTitle("ln(#it{k}_{T}^{true})");
  h1_mc_y->SetLineColor(kBlue);
  h1_mc_y->SetMarkerColor(kBlue);
  h1_mc_y->SetTitle("");
  h1_mc_y->Draw();
  h1_data_y->SetLineColor(kRed);
  h1_data_y->SetMarkerColor(kRed);
  h1_data_y->Draw("same");

  c->cd(3);
  gPad->SetLogy();
  TH1D* h1_mc_z = (TH1D*)h3_mc->ProjectionZ("h1_mc_z", 1, 7, 2, 12);
  TH1D* h1_data_z = (TH1D*)h3_data->ProjectionZ("h1_data_z", 1, 7, 2, 12);
  h1_mc_z->Scale(1./h1_mc_z->Integral(), "width");
  h1_data_z->Scale(1./h1_data_z->Integral(), "width");
  h1_mc_z->GetXaxis()->SetTitle("#it{p}_{T}^{true}");
  h1_mc_z->SetLineColor(kBlue);
  h1_mc_z->SetMarkerColor(kBlue);
  h1_mc_z->SetTitle("");
  h1_mc_z->Draw();
  h1_data_z->SetLineColor(kRed);
  h1_data_z->SetMarkerColor(kRed);
  h1_data_z->Draw("same");

  
  
  

  ss << "figures/Reweighting";
  ss << "_" << date << ".pdf";
  c->SaveAs(ss.str().c_str());
}
  
