void UnfoldClosure(std::string file, std::string var, std::string sd, std::string date, int x1, int x2, int y1, int y2, float min, float max)
{
  TFile* f = new TFile(file.c_str());
  
  TH3D* h2_true = (TH3D*)f->Get("truef");
  std::cout << h2_true->Integral() << std::endl;
  TH3D* h2_eff = (TH3D*)f->Get("true_match");
  std::cout << h2_eff->Integral() << std::endl;
  h2_eff->Divide(h2_true);
  std::cout << h2_eff->Integral() << std::endl;
  std::cout << h2_true->Integral() << std::endl;
  TH1D* h1_norm = (TH1D*)f->Get("Bayesian_Unfolded1Diter5");
  std::cout << h1_norm->Integral() << std::endl;
  TH1D* h1_true_norm = (TH1D*)f->Get("h1_fulleff");
  std::cout << h1_true_norm->Integral() << std::endl;
  TH1D* h1_eff = (TH1D*)f->Get("h1_true");
  std::cout << h1_eff->Integral() << std::endl;
  h1_eff->SetName("h1_eff");
  h1_eff->Divide(h1_true_norm);
  std::cout << h1_eff->Integral() << std::endl;
  //  h1_norm->Divide(h1_eff);
  std::cout << h1_norm->Integral() << std::endl;
  std::cout << h1_true_norm->Integral() << std::endl;
  TH1D* h1_true = (TH1D*)h2_true->ProjectionX("h1", x1, x2, y1, y2);
  h1_true->Sumw2();
  std::cout << h1_true->Integral() << std::endl;
  h1_true->Scale(1./h1_true_norm->Integral(y1, y2), "width");
  std::cout << h1_true->Integral() << std::endl;
  TH3D* h2_uf_i1 = (TH3D*)f->Get("Bayesian_Unfoldediter5");
  std::cout << h2_uf_i1->Integral() << std::endl;
  h2_uf_i1->Divide(h2_eff);
  std::cout << h2_uf_i1->Integral() << std::endl;
  TH1D* h1_uf_i1 = (TH1D*)h2_uf_i1->ProjectionX("h1_uf_i1", x1, x2, y1, y2);
  std::cout << h1_uf_i1->Integral() << std::endl;
  h1_uf_i1->Sumw2();
  h1_uf_i1->Scale(1./h1_norm->Integral(y1, y2), "width");
  std::cout << h1_uf_i1->Integral() << std::endl;

  TH3D* h2_reco = (TH3D*)f->Get("smeared");
  TH1D* h1_norm_reco = (TH1D*)f->Get("h1_reco");
  TH1D* h1_reco = (TH1D*)h2_reco->ProjectionX("h1_reco2", 1, 11, 1, 4);
  h1_reco->Scale(1./(h1_norm_reco->Integral(1, 4)/2.), "width");
  TH3D* h2_raw = (TH3D*)f->Get("raw");
  TH1D* h1_norm_raw = (TH1D*)f->Get("h1_raw");
  TH1D* h1_data = (TH1D*)h2_raw->ProjectionX("h1_data", 1, 11, 1, 4);
  h1_data->Scale(1./h1_norm_raw->Integral(1, 4), "width");
  
  
  TCanvas* c = new TCanvas("c", "c", 700, 600);
  gStyle->SetOptStat(0);
  //  gStyle->SetPadTicksy(1);                                                                                                                                             
  TPad* p1=new TPad("p1","p1",0,0,1,1);
  p1->SetMargin(0.15,0.05,0.4,0.1);
  TPad* p2=new TPad("p2","p2",0,0,1,1);
  p2->SetMargin(0.15,0.05,0.1,0.6);
  p2->SetFillStyle(4000);

  TLegend* leg = new TLegend(0.2, 0.75, 0.4, 0.9);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  leg->SetTextSize(0.045);

  TLegend* leg2 = new TLegend(0.4, 0.75, 0.6, 0.9);
  leg2->SetFillColor(0);
  leg2->SetBorderSize(0);
  leg2->SetTextFont(42);
  leg2->SetTextSize(0.045);

  TLatex* lat = new TLatex();
  lat->SetTextFont(42);
  lat->SetNDC(true);
  lat->SetTextSize(0.04);
  lat->SetTextAlign(33);

  p1->cd();
  h1_true->SetTitle("");
  h1_true->SetLineColor(kBlack);
  h1_true->SetMarkerColor(kBlack);
  h1_true->GetXaxis()->SetTitleSize(0.05);
  h1_true->GetYaxis()->SetTitleSize(0.05);
  h1_true->GetXaxis()->SetLabelSize(0);
  h1_true->GetYaxis()->SetLabelSize(0.05);
  h1_true->GetXaxis()->SetLabelOffset(0);
  h1_true->GetXaxis()->SetTitle("ln(#it{R}/#it{#DeltaR})");
  h1_true->GetYaxis()->SetTitle("#frac{1}{N_{jet}}#frac{dN}{dln(#it{R}/#it{#DeltaR})}");
  
  h1_true->SetTitle("");
  h1_true->SetMaximum(h1_true->GetMaximum()*2);
  //  if (var == "rg") h1_true->GetXaxis()->SetRangeUser(0, 0.35);
  h1_true->SetMarkerStyle(20);
  h1_true->SetMarkerSize(1);
  std::cout << h1_true->GetBinLowEdge(1) << endl;
  h1_true->GetXaxis()->SetRangeUser(0, 1.4);
  h1_true->Draw();
  leg->AddEntry(h1_true, "Pythia");
  h1_uf_i1->SetLineColor(kRed);
  h1_uf_i1->SetMarkerColor(kRed);
  h1_uf_i1->SetMarkerStyle(20);
  h1_uf_i1->SetMarkerSize(1);
  h1_uf_i1->Draw("same");
  leg->AddEntry(h1_uf_i1, "Data");
  h1_reco->SetLineColor(kGreen-2);
  h1_reco->SetMarkerColor(kGreen-2);
  h1_reco->SetMarkerStyle(1);
  h1_reco->Draw();
  leg->AddEntry(h1_reco, "Reco MC");
  h1_data->SetLineColor(kViolet);
  h1_data->SetMarkerColor(kViolet);
  h1_data->SetMarkerStyle(1);
  h1_data->Draw("same");
  leg->AddEntry(h1_data, "Raw data");
  lat->DrawLatex(0.93, 0.88, "20 < #it{p}_{T} < 120 GeV/c");
  std::stringstream ss;
  double dR[14] = {-3, -1, -0.75, -0.5, -0.3, -0.1, 0, 0.1, 0.3, 0.5, 0.75, 1, 1.5, 3};
  ss << dR[x1-1] << " < ln(k_{T}) < " << dR[x2];
  lat->DrawLatex(0.93, 0.83, ss.str().c_str());
  ss.str("");
  //  else lat->DrawLatex(0.93, 0.88, "80 < #it{p}_{T} < 120 GeV/c");
  //  if (cent == "semi") lat->DrawLatex(0.93, 0.83, "30-50%");
  //  else if (cent == "cent") lat->DrawLatex(0.93, 0.83, "0-10%");
  //  else lat->DrawLatex(0.93, 0.83, "pp");
  /*  if ((r1 == 1)&&(r2==1)) lat->DrawLatex(0.93, 0.68, "no SD bin");
  else if ((r1 == 2)&&(r2==2)) lat->DrawLatex(0.93, 0.68, "0 < #it{R}_{g} < 0.04");
  else if ((r1 == 3)&&(r2==3)) lat->DrawLatex(0.93, 0.68, "0.04 < #it{R}_{g} < 0.1");
  else if ((r1 == 4)&&(r2==4)) lat->DrawLatex(0.93, 0.68, "0.1 < #it{R}_{g} < 0.2");
  else if ((r1 == 5)&&(r2==5)) lat->DrawLatex(0.93, 0.68, "0.2 < #it{R}_{g} < 0.35");
  else if ((r1 == 4)&&(r2==5)) lat->DrawLatex(0.93, 0.68, "0.1 < #it{R}_{g} < 0.35");*/
  /*  if (cent != "pp")
    {
      if (type == "ebye") lat->DrawLatex(0.93, 0.73, "Event-by-Event");
      else lat->DrawLatex(0.93, 0.73, "Jet-by-Jet");
      }*/
  //  if (sd == "sd1") lat->DrawLatex(0.93, 0.78, "Soft Drop z = 0.1");
  //  else if (sd == "sd2") lat->DrawLatex(0.93, 0.78, "Soft Drop z = 0.2");
  //  else if (sd == "sd4") lat->DrawLatex(0.93, 0.78, "Soft Drop z = 0.4");


  p2->cd();
  TH1D* h1_i3toi1 = (TH1D*)h1_uf_i1->Clone("h1_i3toi1");
  h1_i3toi1->Divide(h1_true);
  //  if (var == "rg") h1_i3toi1->GetXaxis()->SetRangeUser(0, 0.35);
  h1_i3toi1->GetXaxis()->SetTitleSize(0.05);
  h1_i3toi1->GetYaxis()->SetTitleSize(0.045);
  h1_i3toi1->GetXaxis()->SetLabelSize(0.045);
  h1_i3toi1->GetYaxis()->SetLabelSize(0.045);
  h1_i3toi1->GetYaxis()->SetRangeUser(min, max);
  h1_i3toi1->GetXaxis()->SetRangeUser(0., 1.4);
  h1_i3toi1->GetYaxis()->SetNdivisions(606);
  h1_i3toi1->SetTitle("");
  h1_i3toi1->GetXaxis()->SetTitle("ln(#it{R}/#it{#DeltaR})");
  h1_i3toi1->GetYaxis()->SetTitle("Data/Pythia");
  h1_i3toi1->Draw();
  TH1D* h1_ratiodata = (TH1D*)h1_data->Clone("h1_ratiodata");
  h1_ratiodata->Divide(h1_reco);
  h1_ratiodata->Draw("same");
  
  TLine* line = new TLine(0, 1, 1.4, 1);
  line->SetLineStyle(2);
  line->SetLineWidth(3);
  line->Draw("same");

  c->cd();
  p1->Draw();
  p2->Draw();

  //  std::stringstream ss;
  ss << "figures/Slicex_" << x1 << "to" << x2 << "_dR" << y1 << "to" << y2 << "_" << sd << "_" << date << ".pdf";
  c->SaveAs(ss.str().c_str());
  ss.str("");
  
}

  
  
  
  
  
