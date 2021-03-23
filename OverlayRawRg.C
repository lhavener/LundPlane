void OverlayRawRg(std::string file1, std::string file2, std::string tag, std::string var)
{
  TFile* f1 = new TFile(file1.c_str());
  TH1D* h1_pyt = (TH1D*)f1->Get("h1_nom");
  h1_pyt->SetName("h1_pyt");
  TH1D* h1_her = (TH1D*)f1->Get("h1_herwig2");
  h1_her->SetName("h1_her");

  TFile* f2 = new TFile(file2.c_str());
  TH1D* h2_pyt = (TH1D*)f2->Get("h1_nom");
  h2_pyt->SetName("h2_pyt");
  TH1D* h2_her = (TH1D*)f2->Get("h1_herwig2");
  h2_her->SetName("h2_her");

  TCanvas* c = new TCanvas("c", "c", 1000, 600);
  gStyle->SetOptStat(0);
  c->Divide(2,1);

  TLegend* leg = new TLegend(0.5, 0.6, 0.84, 0.9);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  leg->SetTextSize(0.045);
  
  c->cd(1);
  if (var == "dR") h1_pyt->GetXaxis()->SetTitle("#ln(R/#DeltaR)");
  else h1_pyt->GetXaxis()->SetTitle("#ln(k_{T})");
  if (var == "dR") h1_pyt->GetXaxis()->SetRangeUser(0, 1.4);
  else h1_pyt->GetXaxis()->SetRangeUser(0, 1.5);
  h1_pyt->GetYaxis()->SetRangeUser(0, 1.5);
  h1_pyt->SetLineColor(kBlue);
  h1_pyt->SetMarkerColor(kBlue);
  h1_pyt->SetMarkerStyle(20);
  h1_pyt->SetMarkerSize(1);
  h1_pyt->Draw("same");
  h1_her->SetLineColor(kRed);
  h1_her->SetMarkerColor(kRed);
  h1_her->SetMarkerStyle(20);
  h1_her->SetMarkerSize(1);
  h1_her->Draw("same");
  h2_pyt->SetLineColor(kGreen-2);
  h2_pyt->SetMarkerColor(kGreen-2);
  h2_pyt->SetMarkerStyle(20);
  h2_pyt->SetMarkerSize(1);
  h2_pyt->Draw("same");
  h2_her->SetLineColor(kViolet);
  h2_her->SetMarkerColor(kViolet);
  h2_her->SetMarkerStyle(20);
  h2_her->SetMarkerSize(1);
  h2_her->Draw("same");

  //  leg->AddEntry(h1_raw, "Data");
  leg->AddEntry(h1_pyt, "Pythia, full production");
  leg->AddEntry(h1_her, "Herwig, full production");
  leg->AddEntry(h2_pyt, "Pythia, fast sim");
  leg->AddEntry(h2_her, "Herwig, fast sim");
  leg->Draw("same");

  c->cd(2);
  TH1D* h1_ratio1 = (TH1D*)h1_pyt->Clone("h1_ratio1");
  h1_ratio1->Divide(h1_her);
  h1_ratio1->GetYaxis()->SetTitle("Pythia/Herwig");
  h1_ratio1->GetYaxis()->SetRangeUser(0.5, 1.5);
  h1_ratio1->Draw();
  TH1D* h1_ratio3 = (TH1D*)h2_pyt->Clone("h1_ratio3");
  h1_ratio3->Divide(h2_her);
  h1_ratio3->Draw("same");

  std::stringstream ss;
  ss << "figures/FullvsFastSim_" << var << "_" << tag << ".pdf";
  c->SaveAs(ss.str().c_str());
}





  
