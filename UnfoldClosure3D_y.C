void UnfoldClosure(std::string file, std::string var, std::string sd, std::string date, int x1, int x2, int y1, int y2)
{
  TFile* f = new TFile(file.c_str());
  
  TH3D* h2_true = (TH3D*)f->Get("true_match");
  TH3D* h2_eff = (TH3D*)f->Get("true_match");
  //  h2_eff->Divide(h2_true);
  TH1D* h1_true = (TH1D*)h2_true->ProjectionY("h1_true", x1, x2, y1, y2);
  h1_true->Sumw2();
  h1_true->Scale(1./h1_true->Integral(), "width");
  TH3D* h2_uf_i1 = (TH3D*)f->Get("Bayesian_Unfoldediter1");
  //  h2_uf_i1->Divide(h2_eff);
  TH1D* h1_uf_i1 = (TH1D*)h2_uf_i1->ProjectionY("h1_uf_i1", x1, x2, y1, y2);
  h1_uf_i1->Sumw2();
  h1_uf_i1->Scale(1./h1_uf_i1->Integral(), "width");
  TH3D* h2_uf_i2 = (TH3D*)f->Get("Bayesian_Unfoldediter2");
  //  h2_uf_i2->Divide(h2_eff);
  TH1D* h1_uf_i2 = (TH1D*)h2_uf_i2->ProjectionY("h1_uf_i2", x1, x2, y1, y2);
  h1_uf_i2->Sumw2();
  h1_uf_i2->Scale(1./h1_uf_i2->Integral(), "width");
  TH3D* h2_uf_i3 = (TH3D*)f->Get("Bayesian_Unfoldediter3");
  //  h2_uf_i3->Divide(h2_eff);
  TH1D* h1_uf_i3 = (TH1D*)h2_uf_i3->ProjectionY("h1_uf_i3", x1, x2, y1, y2);
  h1_uf_i3->Sumw2();
  h1_uf_i3->Scale(1./h1_uf_i3->Integral(), "width");
  TH3D* h2_uf_i4 = (TH3D*)f->Get("Bayesian_Unfoldediter4");
  //  h2_uf_i4->Divide(h2_eff);
  TH1D* h1_uf_i4 = (TH1D*)h2_uf_i4->ProjectionY("h1_uf_i4", x1, x2, y1, y2);
  h1_uf_i4->Sumw2();
  h1_uf_i4->Scale(1./h1_uf_i4->Integral(), "width");
  TH3D* h2_uf_i5 = (TH3D*)f->Get("Bayesian_Unfoldediter5");
  //  h2_uf_i5->Divide(h2_eff);
  TH1D* h1_uf_i5 = (TH1D*)h2_uf_i5->ProjectionY("h1_uf_i5", x1, x2, y1, y2);
  h1_uf_i5->Sumw2();
  h1_uf_i5->Scale(1./h1_uf_i5->Integral(), "width");
  TH3D* h2_uf_i6 = (TH3D*)f->Get("Bayesian_Unfoldediter6");
  //  h2_uf_i6->Divide(h2_eff);
  TH1D* h1_uf_i6 = (TH1D*)h2_uf_i6->ProjectionY("h1_uf_i6", x1, x2, y1, y2);
  h1_uf_i6->Sumw2();
  h1_uf_i6->Scale(1./h1_uf_i6->Integral(), "width");
  TH3D* h2_uf_i7 = (TH3D*)f->Get("Bayesian_Unfoldediter7");
  //  h2_uf_i7->Divide(h2_eff);
  TH1D* h1_uf_i7 = (TH1D*)h2_uf_i7->ProjectionY("h1_uf_i7", x1, x2, y1, y2);
  h1_uf_i7->Sumw2();
  h1_uf_i7->Scale(1./h1_uf_i7->Integral(), "width");
  TH3D* h2_uf_i8 = (TH3D*)f->Get("Bayesian_Unfoldediter8");
  //  h2_uf_i8->Divide(h2_eff);
  TH1D* h1_uf_i8 = (TH1D*)h2_uf_i8->ProjectionY("h1_uf_i8", x1, x2, y1, y2);
  h1_uf_i8->Sumw2();
  h1_uf_i8->Scale(1./h1_uf_i8->Integral(), "width");
  TH3D* h2_uf_i9 = (TH3D*)f->Get("Bayesian_Unfoldediter9");
  //  h2_uf_i9->Divide(h2_eff);
  TH1D* h1_uf_i9 = (TH1D*)h2_uf_i9->ProjectionY("h1_uf_i9", x1, x2, y1, y2);
  h1_uf_i9->Sumw2();
  h1_uf_i9->Scale(1./h1_uf_i9->Integral(), "width");
  
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
  h1_true->SetTitle("Truth level");
  h1_true->SetLineColor(kBlack);
  h1_true->SetMarkerColor(kBlack);
  h1_true->GetXaxis()->SetTitleSize(0.05);
  h1_true->GetYaxis()->SetTitleSize(0.05);
  h1_true->GetXaxis()->SetLabelSize(0);
  h1_true->GetYaxis()->SetLabelSize(0.05);
  h1_true->GetXaxis()->SetLabelOffset(0);
  h1_true->GetXaxis()->SetTitle("ln(#it{k}_{T})");
  h1_true->GetYaxis()->SetTitle("#frac{1}{N_{jet}}#frac{dN}{dln(#it{k}_{T})}");
  
  h1_true->SetTitle("");
  h1_true->SetMaximum(h1_true->GetMaximum()*2);
  //  if (var == "rg") h1_true->GetXaxis()->SetRangeUser(0, 0.35);
  h1_true->SetMarkerStyle(20);
  h1_true->SetMarkerSize(1);
  std::cout << h1_true->GetBinLowEdge(1) << endl;
  h1_true->GetXaxis()->SetRangeUser(-1, 1.5);
  h1_true->Draw();
  leg->AddEntry(h1_true, "Prior split");
  h1_uf_i1->SetLineColor(kRed);
  h1_uf_i1->SetMarkerColor(kRed);
  h1_uf_i1->SetMarkerStyle(20);
  h1_uf_i1->SetMarkerSize(1);
  h1_uf_i1->Draw("same");
  leg->AddEntry(h1_uf_i1, "i = 1");
  h1_uf_i3->SetLineColor(kBlue);
  h1_uf_i3->SetMarkerColor(kBlue);
  h1_uf_i3->SetMarkerStyle(20);
  h1_uf_i3->SetMarkerSize(1);
  h1_uf_i3->Draw("same");
  leg->AddEntry(h1_uf_i3, "i = 3");
  h1_uf_i5->SetLineColor(kGreen-2);
  h1_uf_i5->SetMarkerColor(kGreen-2);
  h1_uf_i5->SetMarkerStyle(20);
  h1_uf_i5->SetMarkerSize(1);
  h1_uf_i5->Draw("same");
  leg2->AddEntry(h1_uf_i5, "i = 5");
  h1_uf_i7->SetLineColor(kViolet);
  h1_uf_i7->SetMarkerColor(kViolet);
  h1_uf_i7->SetMarkerStyle(20);
  h1_uf_i7->SetMarkerSize(1);
  h1_uf_i7->Draw("same");
  leg2->AddEntry(h1_uf_i7, "i = 7");
  h1_uf_i9->SetLineColor(kOrange-3);
  h1_uf_i9->SetMarkerColor(kOrange-3);
  h1_uf_i9->SetMarkerStyle(20);
  h1_uf_i9->SetMarkerSize(1);
  h1_uf_i9->Draw("same");
  leg2->AddEntry(h1_uf_i9, "i = 9");
  leg->Draw("same");
  leg2->Draw("same");
  //  if (pt1 == 4)
  lat->DrawLatex(0.93, 0.88, "20 < #it{p}_{T} < 120 GeV/c");
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
  h1_i3toi1->GetYaxis()->SetRangeUser(0.8, 1.2);
  h1_i3toi1->GetXaxis()->SetRangeUser(-1, 1.5);
  h1_i3toi1->GetYaxis()->SetNdivisions(606);
  h1_i3toi1->SetTitle("Closure test");
  h1_i3toi1->GetXaxis()->SetTitle("ln(#it{k}_{T})");
  h1_i3toi1->GetYaxis()->SetTitle("Ratio to prior");
  h1_i3toi1->Draw();
  TH1D* h1_i3toi3 = (TH1D*)h1_uf_i3->Clone("h1_i3toi3");
  h1_i3toi3->Divide(h1_true);
  h1_i3toi3->Draw("same");
  TH1D* h1_i5toi3 = (TH1D*)h1_uf_i5->Clone("h1_i5toi3");
  h1_i5toi3->Divide(h1_true);
  h1_i5toi3->Draw("same");
  TH1D* h1_i7toi3 = (TH1D*)h1_uf_i7->Clone("h1_i7toi3");
  h1_i7toi3->Divide(h1_true);
  h1_i7toi3->Draw("same");
  TH1D* h1_i9toi3 = (TH1D*)h1_uf_i9->Clone("h1_i9toi3");
  h1_i9toi3->Divide(h1_true);
  h1_i9toi3->Draw("same");
  
  TLine* line = new TLine(-1, 1, 1.5, 1);
  line->SetLineStyle(2);
  line->SetLineWidth(3);
  line->Draw("same");

  c->cd();
  p1->Draw();
  p2->Draw();

  std::stringstream ss;
  ss << "figures/Closurey_" << x1 << "to" << x2 << "_dR" << y1 << "to" << y2 << "_" << sd << "_" << date << ".pdf";
  c->SaveAs(ss.str().c_str());
  ss.str("");
  
}

  
  
  
  
  
