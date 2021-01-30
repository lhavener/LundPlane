
void SystematicPlots(std::string file, int pt1, int pt2, std::string var)
{
  TCanvas* c = new TCanvas("c", "c", 500, 400);
  gStyle->SetOptStat(0);
  
  TLegend* leg = new TLegend(0.18, 0.5, 0.5, 0.9);
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
  TGraphAsymmErrors* g_nom_err = (TGraphAsymmErrors*)f->Get("h1_pp_err");
  TH1D* hnom = (TH1D*)f->Get("h1_pp");
  TH1D* hnom_err = (TH1D*)hnom->Clone("hpp_err");
  hnom_err->Reset();

  for (int i = 1; i <= hnom_err->GetNbinsX(); i++)
    {
      double x  = 0;
      double y = 0;
      g_nom_err->GetPoint(i-1, x, y);
      double y_low = g_nom_err->GetErrorYlow(i-1)/y;
      double y_high = g_nom_err->GetErrorYhigh(i-1)/y;
      double err = std::sqrt(y_low*y_low + y_high*y_high);
      hnom_err->SetBinContent(i, err);
    }

  std::string sys[6] = {"eff", "trunc", "iter", "bin", "untag", "weight"};
  std::string label[6] = {"Tracking Inefficiency", "Truncation", "Iterations", "Binning", "Untagged Bin", "Reweight"};
  int  col[6] = {kRed-3, kViolet-5, kTeal-1, kPink+7, kYellow-3, kOrange-3};

  hnom_err->SetTitle("");
  if (var == "nsd") hnom_err->GetXaxis()->SetTitle("#it{n}_{SD}");
  else if (var == "zg") {hnom_err->GetXaxis()->SetTitle("#it{z}_{g}"); hnom_err->GetXaxis()->SetRangeUser(0.2, 0.5);}
  else {hnom_err->GetXaxis()->SetTitle("#it{R}_{g}"); hnom_err->GetXaxis()->SetRangeUser(0, 0.35);}
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
      TH1D* hratio;
      if ((sys[i] != "trunc") && (sys[i] != "iter"))
        {
	  ss << "h1_" << sys[i] << "_pp";
	  cout <<ss.str()<<endl;
	  h1 = (TH1D*)f->Get(ss.str().c_str());
	  cout << h1->Integral() << endl;
	  ss << "_ratiio";
	  hratio =(TH1D*)h1->Clone(ss.str().c_str());
	  ss.str("");
	  hratio->Add(hnom, -1);
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
	  if (sys[i] == "trunc") { ty1 = "truncup"; ty2 = "truncdown";}
	  else {ty1 = "iterhigh"; ty2 = "iterlow";}
	  ss << "h1_" << ty1 << "_pp";
	  cout << ss.str() <<endl;
	  h1 = (TH1D*)f->Get(ss.str().c_str());
	  ss << "_ratiio";
          hratio =(TH1D*)h1->Clone(ss.str().c_str());
          ss.str("");
	  hratio->Add(hnom, -1);
	  ss <<"h1_" << ty2 << "_pp";
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
              hratio->SetBinContent(i, std::sqrt(cont*cont+cont1*cont1));
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
  
  if (pt1 == 4) lat->DrawLatex(0.88, 0.88, "60 < #it{p}_{T} < 80 GeV/c");
  else lat->DrawLatex(0.88, 0.88, "80 < #it{p}_{T} < 120 GeV/c");
  lat->DrawLatex(0.88, 0.83, "pp");
  lat->DrawLatex(0.88, 0.78, "Event-by-Event");
  lat->DrawLatex(0.88, 0.73, "Soft Drop z = 0.2");

  ss << "figures_postQM/SysOverlayPP_" << var << "_" <<  pt1  <<  "to"<< pt2 << "5_3_20.pdf";
  c->SaveAs(ss.str().c_str());
}
