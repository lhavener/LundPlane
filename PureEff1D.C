void PureEff(std::string file, std::string file2, std::string date, std::string axis)
{
  TFile* f = new TFile(file.c_str());
  TFile* f2 = new TFile(file2.c_str());  
  
  TH1D* h2_eff;
  TH1D* h2_eff_den;
  TH1D* h2_pur;
  TH1D* h2_pur_den;
  TH1D* h2_match;
  TH1D* h2_match_den;
  TH3D* h3_eff_num = (TH3D*)f->Get("true_match");
  if (axis == "x") h2_eff = (TH1D*)h3_eff_num->ProjectionX("h1", 2, 12, 2, 5);
  else h2_eff = (TH1D*)h3_eff_num->ProjectionY("h1", 1, 7, 2, 5);
  TH3D* h3_eff_den = (TH3D*)f->Get("truef");
  if (axis == "x") h2_eff_den = (TH1D*)h3_eff_den->ProjectionX("h1_den", 2, 12, 2, 5);
  else h2_eff_den = (TH1D*)h3_eff_den->ProjectionY("h1_den", 1, 7, 2, 5);
  h2_eff->Divide(h2_eff_den);
  TH3D* h3_pur_num = (TH3D*)f->Get("reco");
  if (axis == "x") h2_pur = (TH1D*)h3_pur_num->ProjectionX("h2");
  else h2_pur = (TH1D*)h3_pur_num->ProjectionY("h2");
  TH3D* h3_pur_den = (TH3D*)f->Get("recof");
  if (axis == "x") h2_pur_den = (TH1D*)h3_pur_den->ProjectionX("h2_den");
  else h2_pur_den = (TH1D*)h3_pur_den->ProjectionY("h2_den");
  h2_pur->Divide(h2_pur_den);

  std::stringstream ss;
  ss << "h_2";
  TH3D* h3_match_num = (TH3D*)f2->Get(ss.str().c_str());
  ss.str("");
  if (axis == "x") h2_match = (TH1D*)h3_match_num->ProjectionX("h3", 2, 12, 2, 5);
  else h2_match = (TH1D*)h3_match_num->ProjectionY("h3", 1, 7, 2, 5);
  TH3D* h3_match_den = (TH3D*)f2->Get("h");
  if (axis == "x") h2_match_den = (TH1D*)h3_match_den->ProjectionX("h3_den", 2, 12, 2, 5);
  else h2_match_den = (TH1D*)h3_match_den->ProjectionY("h3_den", 1, 7, 2, 5);
  h2_match->Sumw2();
  h2_match_den->Sumw2();
  h2_match->Divide(h2_match_den);
  
  TCanvas* c = new TCanvas("c", "c", 700, 500);
  gStyle->SetOptStat(0);
  c->SetRightMargin(0.12);
  c->SetBottomMargin(0.12);
  c->SetTopMargin(0.15);
  
  TLegend* leg = new TLegend(0.5, 0.25, 0.75, 0.4);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  leg->SetTextSize(0.045);
  TLatex* lat = new TLatex();
  lat->SetTextFont(42);
  lat->SetNDC(true);
  lat->SetTextSize(0.045);
  lat->SetTextAlign(11);


  h2_eff->GetYaxis()->SetTitle("Efficiency or Purity");
  h2_eff->GetYaxis()->SetLabelSize(0.05);
  h2_eff->GetXaxis()->SetLabelSize(0.05);
  h2_eff->GetYaxis()->SetTitleSize(0.05);
  h2_eff->GetXaxis()->SetTitleSize(0.05);
  h2_eff->SetLineColor(kRed-4);
  h2_eff->SetMarkerColor(kRed-4);
  //  h2_eff->SetMaximum(10);
  h2_eff->SetMarkerStyle(33);
  h2_eff->SetMarkerSize(1.5);
  h2_eff->GetXaxis()->SetTitleOffset(1.0);
  h2_eff->GetYaxis()->SetTitleOffset(0.8);
  if (axis == "x") h2_eff->GetXaxis()->SetTitle("ln(#it{R}/#Delta#it{R})");
  else   h2_eff->GetXaxis()->SetTitle("ln(#it{k}_{T})");
  if (axis == "x") h2_eff->GetXaxis()->SetRangeUser(0, 1.4);
  else   h2_eff->GetXaxis()->SetRangeUser(-1, 1.5);
  h2_eff->GetYaxis()->SetTitleSize(0.055);
  h2_eff->SetTitle("");
  h2_eff->GetYaxis()->SetRangeUser(0, 1);
  h2_eff->Draw();
  h2_pur->SetLineColor(kAzure-4);
  h2_pur->SetMarkerColor(kAzure-4);
  h2_pur->SetMarkerStyle(20);
  h2_pur->SetMarkerSize(1);
  h2_pur->Draw("same");
  h2_match->SetLineColor(kBlack);
  h2_match->SetMarkerColor(kBlack);
  h2_match->SetMarkerStyle(21);
  h2_match->Draw("same");

  leg->AddEntry(h2_eff, "Efficiency");
  leg->AddEntry(h2_pur, "Purity");
  leg->AddEntry(h2_match, "Subjet Matching Purity");
  leg->Draw("same");
  
  lat->DrawLatex(0.15, 0.38, "ALICE Preliminary");
  lat->DrawLatex(0.15, 0.28, "#sqrt{#it{s}} = 13 TeV");
  lat->DrawLatex(0.15, 0.33, "Charged-particle jets anti-#it{k}_{T}");
  lat->DrawLatex(0.15, 0.23, "#it{R} = 0.4, |#it{#eta}_{jet}| < 0.5");
  lat->DrawLatex(0.15, 0.17, "20 < #it{p}_{T, ch jet} < 120 GeV/#it{c}");
  
  ss.str("");
  ss << "fig_pubnote/PureEff1D_" << axis << ".pdf";
  c->SaveAs(ss.str().c_str());
}
