void DetermineIter(std::string file, std::string file_rw, std::string var, int pt1, int pt2)
{
  TFile* f = new TFile(file.c_str());
  TFile* f_rw = new TFile(file_rw.c_str());

  TH1D* h1_iter_tot = new TH1D("h1_tot", "h1_tot", 9, 0.5, 9.5);
  TH1D* h1_iter_stat = new TH1D("h1_iter_stat", "h1_iter_stat", 9, 0.5, 9.5);
  TH1D* h1_iter_rw = new TH1D("h1_iter_rw", "h1_iter_rw", 9, 0.5, 9.5);
  TH1D* h1_iter_iter = new TH1D("h1_iter_iter", "h1_iter_iter", 9, 0.5, 9.5);
  
  std::stringstream ssn;
  std::stringstream ss;
  for (int i = 1; i <= 9; i++)
    {
      ssn << "Bayesian_Unfoldediter" << i;
      TH3D* h2_nom = (TH3D*)f->Get(ssn.str().c_str());
      ss << ssn.str() << "_nom";
      h2_nom->SetName(ss.str().c_str());
      ss << "_proj";
      TH1D* h1_nom = (TH1D*)h2_nom->ProjectionY(ss.str().c_str(), 1, 7, pt1, pt2);
      h1_nom->Scale(1./h1_nom->Integral(), "width");
      ss.str("");
      TH3D* h2_rw = (TH3D*)f_rw->Get(ssn.str().c_str());
      ss << ssn.str() << "_rw";
      h2_rw->SetName(ss.str().c_str());
      ss << "_proj";
      TH1D* h1_rw = (TH1D*)h2_rw->ProjectionY(ss.str().c_str(), 1, 7, pt1, pt2);
      h1_rw->Scale(1./h1_rw->Integral(), "width");
      ss.str("");
      ssn.str("");
      ssn << "Bayesian_Unfoldediter" << i-1;
      TH3D* h2_iterdown;
      TH1D* h1_iterdown;
      if (i > 1) {h2_iterdown = (TH3D*)f->Get(ssn.str().c_str());
	ss << ssn.str() << "_iterdown";
	h2_iterdown->SetName(ss.str().c_str());
	ss << "_proj";
	h1_iterdown = (TH1D*)h2_iterdown->ProjectionY(ss.str().c_str(), 1, 7, pt1, pt2);
	h1_iterdown->Scale(1./h1_iterdown->Integral(), "width");
      }
      ss.str("");
      ssn.str("");
      ssn << "Bayesian_Unfoldediter" << i+1;
      TH3D* h2_iterup;
      TH1D* h1_iterup;
      if (i < 9) {h2_iterup = (TH3D*)f->Get(ssn.str().c_str());
	ss << ssn.str() << "_iterup";
	h2_iterup->SetName(ss.str().c_str());
	ss << "_proj";
	h1_iterup = (TH1D*)h2_iterup->ProjectionY(ss.str().c_str(), 1, 7, pt1, pt2);
	h1_iterup->Scale(1./h1_iterup->Integral(), "width");
      }
      ss.str("");
      ssn.str("");


      double stat = 0.;
      double rw = 0.;
      double iter = 0.;
      double tot = 0.;
      for (int j = 2; j <= h1_nom->GetNbinsX()-1; j++)
	{
	  double val = h1_nom->GetBinContent(j);
	  double stat_err = h1_nom->GetBinError(j);
	  stat_err = stat_err*stat_err;
	  stat+=stat_err;
	  //	  tot+=stat_err;
	  double delta = (h1_nom->GetBinContent(j) - h1_rw->GetBinContent(j));
	  delta = delta*delta;
	  rw+=delta;
	  //tot+=delta;
	  double iter_down = 0;
	  if (i > 1) iter_down = h1_nom->GetBinContent(j) - h1_iterdown->GetBinContent(j);
	  double iter_up = 0;
	  if (i < 9) iter_up   = h1_nom->GetBinContent(j) - h1_iterup->GetBinContent(j);
	  double iter_err= sqrt(iter_up*iter_up + iter_down*iter_down);
	  iter_err = iter_err*iter_err;
	  iter+=iter_err;
	}
      //      stat*=(1./h1_nom->GetNbinsX);
      tot+=stat;
      tot+=rw;
      tot+=iter;
      h1_iter_tot->SetBinContent(i, sqrt(tot));
      h1_iter_stat->SetBinContent(i, sqrt(stat));
      h1_iter_rw->SetBinContent(i, sqrt(rw));
      h1_iter_iter->SetBinContent(i, sqrt(iter));
    }
  TCanvas* c = new TCanvas("c", "c", 500, 400);
  gStyle->SetOptStat(0);
  TLegend* leg = new TLegend(0.6, 0.65, 0.9, 0.9);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  leg->SetTextSize(0.05);
  TLatex* lat = new TLatex();
  lat->SetTextFont(42);
  lat->SetNDC(true);
  lat->SetTextSize(0.04);
  lat->SetTextAlign(33);
  
  //  if (var == "zg") ss << "z_{g}";
  //  else if (var == "rg") ss << "R_{g}";
  //  else ss << "n_{SD}";
  //  if (pt1 == 4)
  ss << "20 < p_{T} < 120 GeV/c";
    //  elase ss << " 80 < p_{T} < 120 GeV";

  h1_iter_tot->SetTitle(ss.str().c_str());
  ss.str("");
  h1_iter_tot->GetXaxis()->SetTitleSize(0.05);
  h1_iter_tot->GetYaxis()->SetTitleSize(0.05);
  h1_iter_tot->GetYaxis()->SetTitleOffset(1.0);
  h1_iter_tot->GetXaxis()->SetTitle("Iterations");
  h1_iter_tot->GetYaxis()->SetTitle("Summed Error");
  h1_iter_tot->GetYaxis()->SetRangeUser(0., h1_iter_tot->GetMaximum()*1.5);
  h1_iter_tot->SetLineColor(kBlack);
  h1_iter_tot->Draw();
  leg->AddEntry(h1_iter_tot, "Total");
  h1_iter_stat->SetLineColor(kGreen-2);
  h1_iter_stat->Draw("same");
  leg->AddEntry(h1_iter_stat, "Statistical");
  h1_iter_rw->SetLineColor(kRed);
  h1_iter_rw->Draw("same");
  leg->AddEntry(h1_iter_rw, "Prior");
  h1_iter_iter->SetLineColor(kBlue);
  h1_iter_iter->Draw("same");
  leg->AddEntry(h1_iter_iter, "Regularization");
  leg->Draw("same");

  ss.str("");
  ss << "figures/IterationsDet_kt_11_22_20.pdf";
  c->SaveAs(ss.str().c_str());
}
      
	  
	  
      
  
