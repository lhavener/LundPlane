void varResid(std::string tree, std::string var)
{
  TCanvas* c = new TCanvas("c", "c", 1000, 1000);
  c->Divide(2,2);
  gStyle->SetOptStat(0);

  TLegend* leg = new TLegend(0.52, 0.6, 0.7, 0.8);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  leg->SetTextSize(0.045);
  // leg->SetNDC(true);                                                                                                                                             
  TLatex* lat = new TLatex();
  lat->SetTextFont(42);
  lat->SetNDC(true);
  lat->SetTextSize(0.04);
  lat->SetTextAlign(33);


  TFile *ftr = new TFile(tree.c_str());

  std::stringstream ss;
  ss << "h3_dtheta";
  TH3D* h3 = (TH3D*)ftr->Get(ss.str().c_str());
  //  h3->GetYaxis()->SetRange(5, 6);
  TH2D* h2 = (TH2D*)h3->Project3D("zy");
  h2->SetName("h2");
  ss.str("");


  c->cd(1);
  gPad->SetLogz();
  h2->GetYaxis()->SetTitle("(ln(R/#DeltaR^{reco})-ln(R/#DeltaR^{true}))/ln(R/#DeltaR^{true})");
  h2->GetXaxis()->SetTitle("ln(R/#DeltaR^{true})");
  //  h2->SetMinimum(0.0001);
  //  h2->SetMaximum(10000);
  h2->SetTitle("Residuals (detector to particle), 20 < #it{p}_{T}^{true} < 120 GeV/c");
  //  h_r->GetXaxis()->SetRangeUser(10, 150);
  h2->Draw("colz");
  TH1D* h1_JES = (TH1D*)h2->ProfileX("h1_JES");
  h1_JES->SetName("h1_JES");
  h1_JES->Draw("same");

  c->cd(2);
  TH1D* h1 = (TH1D*)h2->ProjectionY("h1");
  //  TH1D* h1_fluc = (TH1D*)h2_fluc->ProjectionY("h1_fluc");
  h1->SetLineColor(kBlack);
  h1->SetMarkerColor(kBlack);
  h1->SetMarkerStyle(20);
  h1->SetMarkerSize(1);
  h1->GetXaxis()->SetRangeUser(-1, 3);
  h1->SetTitle("Residual distribution");
  h1->RebinX(2);
  h1->Scale(1./h1->Integral());
  h1->GetYaxis()->SetTitle("Probability");
  //h1->SetMaximum(h1_det->GetMaximum());
  h1->Draw("Hist Cp");

  c->cd(3);
  h1_JES->SetLineColor(kBlack);
  h1_JES->SetMarkerColor(kBlack);
  h1_JES->SetMarkerStyle(20);
  h1_JES->SetMarkerSize(1);
  h1_JES->GetYaxis()->SetRangeUser(-0.5, 1);
  h1_JES->SetTitle("Mean residuals");
  //  h1_JES->GetYaxis()->SetTitle();
  h1_JES->Draw();
  
  c->cd(4);
  TH1D* h1_JER = (TH1D*)h2->ProjectionX("h1_JER");
  h1_JER->Reset();
  for (int i = 1; i <= h2->GetNbinsX(); i++)
    {
      ss << "proj" << i;
      TH1D* hproj = (TH1D*)h2->ProjectionY(ss.str().c_str(), i, i);
      ss.str("");
      //      hproj->Fit("gaus");
      //      TF1* fit = (TF1*)hproj->GetFunction("gaus");
      //      ss << "fit_" << i;
      //      fit->SetName(ss.str().c_str());      
      //      h1_JER->SetBinContent(i, fit->GetParameter(2));
      //      h1_JER->SetBinError(i, fit->GetParError(2));
      std::cout << hproj->GetStdDev() << std::endl;
      h1_JER->SetBinContent(i, hproj->GetStdDev());
      h1_JER->SetBinError(i, hproj->GetRMSError());
    }
  h1_JER->SetMarkerStyle(20);
  h1_JER->SetMarkerSize(1);
  h1_JER->SetLineColor(kBlack);
  h1_JER->SetMarkerColor(kBlack);

  ss << "#sigma ln(R/#DeltaR)";
  h1_JER->GetYaxis()->SetTitle(ss.str().c_str());
  ss.str("");
  h1_JER->SetTitle("Resolution");
  h1_JER->SetName("h6");
  h1_JER->GetYaxis()->SetRangeUser(0, 3);
  h1_JER->Draw();

  ss << "figures/ResidlnR_11_8_20.pdf";
  c->SaveAs(ss.str().c_str());
  ss.str("");
}



  
  
  
  
  


