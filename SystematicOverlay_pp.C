
void SystematicPlots(std::string file, int pt1, int pt2, int y1, int y2, std::string var)
{
  TCanvas* c = new TCanvas("c", "c", 500, 400);
  gStyle->SetOptStat(0);
  
  TLegend* leg = new TLegend(0.16, 0.55, 0.4, 0.9);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  leg->SetTextSize(0.035);
  // leg->SetNDC(true);                                                                                                       
  TLatex* lat = new TLatex();
  lat->SetTextFont(42);
  lat->SetNDC(true);
  lat->SetTextSize(0.035);
  lat->SetTextAlign(33);
  
  TFile* f = new TFile(file.c_str());
  TGraphAsymmErrors* g_nom_err = (TGraphAsymmErrors*)f->Get("h1_nom_err");
  TH1D* hnom = (TH1D*)f->Get("h1_nom");
  TH1D* hnom_err = (TH1D*)hnom->Clone("hom_err");
  hnom_err->Reset();

  for (int i = 1; i <= hnom_err->GetNbinsX(); i++)
    {
      double x  = 0;
      double y = 0;
      g_nom_err->GetPoint(i-1, x, y);
      double y_low = g_nom_err->GetErrorYlow(i-1)/y;
      double y_high = g_nom_err->GetErrorYhigh(i-1)/y;
      double err = (y_low + y_high)/2.;
      hnom_err->SetBinContent(i, err);
    }

  std::string sys[6] = {"eff", "matchup","close", "herwig2", "iter", "truncup"};
  std::string label[6] = {"Tracking Inefficiency", "Matching", "Non-closure", "Model Dependence", "Iterations", "Truncation"};
  int  col[8] = {kRed-3, kViolet-5,kGreen-2, kBlue, kOrange-3, kTeal-1, kPink+7, kYellow-3};

  hnom_err->SetTitle("");
  if (var == "dR") {hnom_err->GetXaxis()->SetTitle("ln(#it{R}/#Delta#it{R})"); hnom_err->GetXaxis()->SetRangeUser(0, 1.4);}
  else if (var == "kT") {hnom_err->GetXaxis()->SetTitle("ln(#it{k}_{T})"); hnom_err->GetXaxis()->SetRangeUser(-1, 1.5);}
  hnom_err->GetYaxis()->SetTitleSize(0.04);
  hnom_err->GetYaxis()->SetTitle("Relative  Systematic");
  hnom_err->GetYaxis()->SetRangeUser(0, 0.5);
  hnom_err->SetLineColor(kBlack);
  hnom_err->SetLineWidth(4);
  hnom_err->SetMarkerColor(kBlack);
  hnom_err->SetMarkerStyle(20);
  hnom_err->Draw("Hist");
  leg->AddEntry(hnom_err, "Total", "l");

  std::stringstream ss;
  for (int i = 0; i  < 6; i++)
    {
      TH1D* h1;
      TH1D* hcl;
      TH1D* hratio;
      if ((sys[i] != "match") && (sys[i] != "iter") && (sys[i] != "trunc"))
        {
	  ss << "h1_" << sys[i];
	  cout <<ss.str()<<endl;
	  h1 = (TH1D*)f->Get(ss.str().c_str());
	  ss << "_ratiio";
	  hratio =(TH1D*)h1->Clone(ss.str().c_str());
	  ss.str("");
	  if (sys[i] == "close")
	    {
	      ss << "h1_close1";
	      hcl = (TH1D*)f->Get(ss.str().c_str());
	      hratio->Add(hcl, -1);
	      ss.str("");
	    }
	  else if (sys[i] == "truncup")
	    {
	      ss << "h1_nom2";
	      hcl = (TH1D*)f->Get(ss.str().c_str());
	      hratio->Add(hcl, -1);
	      ss.str("");
	    }
	  else if (sys[i] == "matchup")
            {
              ss << "h1_matchdown";
              hcl = (TH1D*)f->Get(ss.str().c_str());
              hratio->Add(hcl, -1);
              ss.str("");
            }
	  else hratio->Add(hnom, -1);
	  for (int i = 1; i <= hratio->GetNbinsX(); i++) 
	    {
	      double cont = hratio->GetBinContent(i);
	      hratio->SetBinContent(i, std::sqrt(cont*cont));
	    }
	}
      else 
	{
	  std::string ty1;
	  std::string ty2;
	  if (sys[i] == "match") { ty1 = "matchup"; ty2 = "matchdown";}
	  else if (sys[i] == "trunc") {ty1 = "truncup"; ty2 = "truncdown";}
	  else {ty1 = "iterhigh"; ty2 = "iterlow";}
	  ss << "h1_" << ty1;
	  cout << ss.str() <<endl;
	  h1 = (TH1D*)f->Get(ss.str().c_str());
	  ss << "_ratiio";
          hratio =(TH1D*)h1->Clone(ss.str().c_str());
          ss.str("");
	  hratio->Add(hnom, -1);
	  ss <<"h1_" << ty2;
	  cout << ss.str() <<endl;

          TH1D* h11 = (TH1D*)f->Get(ss.str().c_str());
          ss << "_ratiio";
          TH1D* hratio1 =(TH1D*)h11->Clone(ss.str().c_str());
          ss.str("");
	  hratio1->Add(hnom, -1);
	  for (int i = 1; i <= hratio->GetNbinsX(); i++)
            {
              double cont =  hratio->GetBinContent(i);
	      double cont1 =  hratio1->GetBinContent(i);
              hratio->SetBinContent(i, (cont + cont1)/2.);
            }
	}
      hratio->Divide(hnom);
      hratio->SetLineColor(col[i]);
      hratio->SetLineWidth(4);
      hratio->Draw("same Hist");
      leg->AddEntry(hratio, label[i].c_str(), "l");
    }
	  

  //  leg->AddEntry(hnom, "Nominal");
  //  leg->AddEntry(h1, label.c_str());
  ss.str("");
  leg->Draw("same");

  if ((pt1 == 2) && (pt2 == 5)) lat->DrawLatex(0.85, 0.85, "20 < #it{p}_{T} < 120 GeV/#it{c}");
  else if ((pt1 == 2) && (pt2 == 2)) lat->DrawLatex(0.85, 0.85, "20 < #it{p}_{T, ch jet} < 40 GeV/#it{c}");
  else if ((pt1 == 5) && (pt2 == 5)) lat->DrawLatex(0.85, 0.85, "80 < #it{p}_{T, ch jet} < 120 GeV/#it{c}");
  if (var == "dR") {
    if (y1 == 2) ss << "-1.0";
    else if (y1 == 7) ss << "0";
    ss << " < ln(#it{k}_{T}) < ";
    if (y2 == 12) ss << "1.5";
    else if (y2 == 6) ss << "0";
  }
  else {
    if (y1 == 1) ss << "0";
    else if (y1 == 2) ss << "0.2";
    else if (y1 == 5) ss << "0.8";
    else if (y1 == 6) ss << "1.0";
  ss << " < ln(#it{R}/#Delta#it{R}) < ";
  if (y2 == 7) ss << "1.4";
  else if (y2 == 2) ss << "0.4";
  else if (y2 == 6) ss << "1.2";
  }
  lat->DrawLatex(0.85, 0.8, ss.str().c_str());
  ss.str("");
  //  lat->DrawLatex(0.88, 0.83, "30-50%");
  //  lat->DrawLatex(0.88, 0.78, "Event-by-Event");
  //  lat->DrawLatex(0.88, 0.73, "Soft Drop z = 0.2");

  ss << "figures/SysOverlay_" << var << "_" <<  pt1  <<  "to"<< pt2 << "_" << y1 << "to" << y2 << "_12_10_20.pdf";
  c->SaveAs(ss.str().c_str());
}
