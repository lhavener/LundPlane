void CompareUF(std::string file1, std::string file2, std::string tag1, std::string tag2, std::string date, int x1, int x2, int y1, int y2)
{
  TFile* f1 = new TFile(file1.c_str());
  TH3D* h2_true1 = (TH3D*)f1->Get("truef");
  h2_true1->SetName("h2_true1");
  TH3D* h2_eff1 = (TH3D*)f1->Get("true_match");
  h2_eff1->SetName("h2_eff1");
  h2_eff1->Divide(h2_true1);
  TH3D* h2_uf1 = (TH3D*)f1->Get("Bayesian_Unfoldediter8");
  h2_uf1->SetName("h2_uf1");
  h2_uf1->Divide(h2_eff1);
  TH1D* h1_uf1 = (TH1D*)h2_uf1->ProjectionY("h1_uf1", x1, x2, y1, y2);
  h1_uf1->Sumw2();
  h1_uf1->Scale(1./h1_uf1->Integral(), "width");

  TFile* f2 = new TFile(file2.c_str());
  TH3D* h2_true2 = (TH3D*)f2->Get("truef");
  h2_true2->SetName("h2_true1");
  TH3D* h2_eff2 = (TH3D*)f2->Get("true_match");
  h2_eff2->SetName("h2_eff2");
  h2_eff2->Divide(h2_true2);
  TH3D* h2_uf2 = (TH3D*)f2->Get("Bayesian_Unfoldediter8");
  h2_uf2->SetName("h2_uf2");
  h2_uf2->Divide(h2_eff2);
  TH1D* h1_uf2 = (TH1D*)h2_uf2->ProjectionY("h1_uf2", x1, x2, y1, y2);
  h1_uf2->Sumw2();
  h1_uf2->Scale(1./h1_uf2->Integral(), "width");
  
  TCanvas* c = new TCanvas("c", "c", 700, 600);
  gStyle->SetOptStat(0);
  //  gStyle->SetPadTicksy(1);                                                                                                    \
                                                                                                                                   
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
  gPad->SetLogz();
  h1_uf1->SetTitle("Truth level");
  h1_uf1->SetLineColor(kBlack);
  h1_uf1->SetMarkerColor(kBlack);
  h1_uf1->GetXaxis()->SetTitleSize(0.05);
  h1_uf1->GetYaxis()->SetTitleSize(0.05);
  h1_uf1->GetXaxis()->SetLabelSize(0);
  h1_uf1->GetYaxis()->SetLabelSize(0.05);
  h1_uf1->GetXaxis()->SetLabelOffset(0);
  h1_uf1->GetXaxis()->SetTitle("ln(#it{k}_{T})");
  h1_uf1->GetYaxis()->SetTitle("#frac{1}{N_{jet}}#frac{dN}{dln(#it{k}_{T})}");
  h1_uf1->SetTitle("");
  h1_uf1->SetMaximum(h1_uf1->GetMaximum()*2);
  h1_uf1->SetMarkerStyle(20);
  h1_uf1->SetMarkerSize(1);
  h1_uf1->Draw();
  leg->AddEntry(h1_uf1, tag1.c_str());
  h1_uf2->SetLineColor(kRed);
  h1_uf2->SetMarkerColor(kRed);
  h1_uf2->SetMarkerStyle(20);
  h1_uf2->SetMarkerSize(1);
  h1_uf2->Draw("same");
  leg->AddEntry(h1_uf2, tag2.c_str());
  leg->Draw("same");

  p2->cd();
  TH1D* h1_i3toi1 = (TH1D*)h1_uf2->Clone("h1_i3toi1");
  h1_i3toi1->Divide(h1_uf1);
  h1_i3toi1->GetXaxis()->SetTitleSize(0.05);
  h1_i3toi1->GetYaxis()->SetTitleSize(0.045);
  h1_i3toi1->GetXaxis()->SetLabelSize(0.045);
  h1_i3toi1->GetYaxis()->SetLabelSize(0.045);
  h1_i3toi1->GetYaxis()->SetNdivisions(404);
  h1_i3toi1->GetYaxis()->SetRangeUser(0.9, 1.1);
  h1_i3toi1->SetTitle("");
  h1_i3toi1->GetXaxis()->SetTitle("ln(#it{k}_{T})");
  h1_i3toi1->GetYaxis()->SetTitle("Ratio");
  h1_i3toi1->Draw();

  TLine* line = new TLine(0, 1, 160, 1);
  line->SetLineStyle(2);
  line->SetLineWidth(3);
  line->Draw("same"); 

  c->cd();
  p1->Draw();
  p2->Draw();

  std::stringstream ss;
  ss << "figures/CompUF3Dy_" << tag1 << "_" << tag2 << "_"<< x1 << "to" << x2 << "_"<< y1 << "to" << y2 << "_" << date << ".pdf";
  c->SaveAs(ss.str().c_str());
  ss.str("");
  
}

  
  
  
  
  
