//#include "magma.cc"
#include "plasma.cc"
//#include "YlGnBu_r_cut_25.cc"
//#include "viridis.cc"
//#include "BuGn.cc"
//#include "bwr.cc"
//#include "GnBu_d.cc"
//#include "New_GnBu.cc"
//#include "GnBu_r.cc"
//#include "Purple_Pink.cc"
//#include "Purple_Pinkan_Trunc.cc"
void Lund(std::string file, std::string type, float min, float max, float pt1, float pt2, std::string date)
{
  std::stringstream ss;
  ss << type;
  TFile* f = new TFile(file.c_str());
  f->ls();
  TH3D* h3 = (TH3D*)f->Get(ss.str().c_str());
  ss.str("");
  if ((type != "truef") && (type != "Bayesian_Unfoldediter5"))  ss << "h1_" << type;
  else if (type == "truef") ss << "h1_fulleff";
  else  ss << "Bayesian_Unfolded1Diter5";
  TH1D* h1 = (TH1D*)f->Get(ss.str().c_str());
  ss.str("");
  
  if (type == "Bayesian_Unfoldediter5")
    {
      TH3D* h3_den = (TH3D*)f->Get("truef");
      TH3D* h3_eff = (TH3D*)f->Get("true_match");
      h3_eff->Divide(h3_den);
      h3->Divide(h3_eff);
      TH1D* h1_den = (TH1D*)f->Get("h1_fulleff");
      TH1D* h1_eff = (TH1D*)f->Get("h1_true");
      h1_eff->Divide(h1_den);
      h1->Divide(h1_eff);
    }
  
  int bin1 = h3->GetZaxis()->FindBin(pt1);
  int bin2 = h3->GetZaxis()->FindBin(pt2);
  if (type == "raw")
    {
      bin1 = 1;
      bin2 = 4;
    }
  
  h3->GetZaxis()->SetRange(bin1, bin2);
  TH2D* h2old = (TH2D*)h3->Project3D("yx");
  h2old->SetName("h2old");
  h2old->Sumw2();
  float tot = h1->Integral(bin1, bin2);
  //  std::cout << "tot" << tot << std::endl;
  //  std::cout << h2->Integral() << std::endl;
  //  std::cout << h2->Integral()/tot << std::endl;
  h2old->Scale(1./tot, "width");
  //  std::cout << h2->Integral() << std::endl;

  TH3D* h3_raw = (TH3D*)f->Get("raw");
  TH1D* h1_raw = (TH1D*)f->Get("h1_raw");
  h3_raw->GetZaxis()->SetRange(1,4);
  TH2D* h2_raw = (TH2D*)h3_raw->Project3D("yx");
  h2_raw->SetName("h2_raw");
  float tot_raw = h1_raw->Integral(1,4);
  h2_raw->Scale(1./tot_raw, "width");

  TH2D* h2 = (TH2D*)h2_raw->Clone("h2");
  h2->Reset();
  for (int i = 1; i <= h2->GetNbinsX(); i++)
    {
      for (int j = 1; j <= h2->GetNbinsY(); j++)
	{
	  h2->SetBinContent(i, j, h2old->GetBinContent(i, j+1));
	  h2->GetYaxis()->SetRangeUser(-1, 1.5);
	}
    }
  h2->GetXaxis()->SetRangeUser(0, 1.4);
  h2->Divide(h2_raw);



  
  Int_t res = TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
  gStyle->SetNumberContours(NCont);

  TCanvas* c = new TCanvas("c", "c", 700, 500);
  gStyle->SetOptStat(0);
  c->SetRightMargin(0.16);
  c->SetBottomMargin(0.12);
  c->SetTopMargin(0.18);

   gPad->SetTickx();
  gPad->SetTicky();
  //  TGaxis *axis1 = new TGaxis(0, 1.5, 1.4, 1.5, 0.1, 0.4, 8,"-");
  //  axis1->SetName("axis1");
  //  axis1->SetLabelSize(0.05);
  //  axis1->SetTitle("#Delta#it{R}");
  //  axis1->SetTitleSize(0.05);
  //  axis1->SetTitleOffset(0.8);
  //  axis1->SetLabelFont(42);
  //  axis1->SetTitleFont(42);
  //  axis1->SetTickLength(0.01);
  
  TLegend* leg = new TLegend(0.69, 0.7, 0.86, 0.8);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  leg->SetTextSize(0.045);
  // leg->SetNDC(true);
  TLatex* lat = new TLatex();
  lat->SetTextFont(42);
  lat->SetNDC(true);
  lat->SetTextSize(0.04);
  lat->SetTextAlign(13);

  h2->GetXaxis()->SetTitleSize(0.05);
  h2->GetXaxis()->SetTitleOffset(1.0);
  h2->GetYaxis()->SetTitleOffset(0.8);
  h2->GetXaxis()->SetLabelSize(0.05);					   
  // h2_data->GetXaxis()->SetLabelOffset(1.0);					   
  h2->GetYaxis()->SetLabelSize(0.05);					   
  h2->GetXaxis()->SetTitle("ln(#it{R}/#Delta#it{R})");
  
  h2->GetYaxis()->SetTitleSize(0.055);
  h2->GetZaxis()->SetTitleSize(0.05);
  h2->GetZaxis()->SetLabelSize(0.05);
  h2->GetYaxis()->SetLabelOffset(0.01);
  h2->GetXaxis()->SetLabelOffset(0.01);
  //  h2_data->GetXaxis()->SetRangeUser(0, 0.5);
  //  h1_data->GetYaxis()->SetRangeUser(0, h1_data->GetMaximum()*1.2);  
  h2->GetYaxis()->SetTitle("ln(#it{k}_{T}/GeV)");
  //  h2->GetZaxis()->SetTitle("(1/#it{N}_{jets})d^{2}#it{N}_{emissions}/(dln(#it{k}_{T})dln(#it{R}/#Delta#it{R})) Unfolded/Raw");
  h2->GetZaxis()->SetTitle("Unfolded/Raw");
  h2->SetTitle("");
  if (max != -1) h2->SetMaximum(max);
  if (min != -1) h2->SetMinimum(min);
  h2->Draw("colz1");
  //    axis1->Draw();

  
  lat->DrawLatex(0.15, 0.99, "ALICE Preliminary");
  lat->DrawLatex(0.15, 0.94, "pp #sqrt{#it{s}} = 13 TeV");

  lat->SetTextAlign(33);
  //  lat->DrawLatex(0.9, 0.99, "Soft drop splitting, #it{z}_{cut} = 0.1 #it{#beta} = 0");
  lat->DrawLatex(0.9, 0.99, "Charged-particle jets anti-#it{k}_{T} #it{R} = 0.4");
  lat->DrawLatex(0.9, 0.94, "|#eta_{jet}| < 0.5, 20 < #it{p}_{T, jet}^{ch} < 120 GeV/#it{c}");
  //  if (type == "raw") lat->DrawLatex(0.9, 0.89, "Data");
  //  else if (type == "smeared")lat->DrawLatex(0.9, 0.89, "Detector Level");
  //  else if ((type == "truef")|| (type == "true")) lat->DrawLatex(0.9, 0.89, "Particle Level");
  //  else if (type == "Bayesian_Unfoldediter8") lat->DrawLatex(0.9, 0.89, "Unfolded");
  lat->SetTextAlign(31);

  TLatex* lat2 = new TLatex();
  lat2->SetTextFont(42);
  //  lat2->SetNDC(true);
  lat2->SetTextSize(0.05);
  lat2->DrawLatex(0 ,1.55, "0.4");
  lat2->DrawLatex(0.13 ,1.55, "0.35");
  lat2->DrawLatex(0.29, 1.55, "0.3");
  lat2->DrawLatex(0.47, 1.55, "0.25");
  lat2->DrawLatex(0.69, 1.55, "0.2");
  lat2->DrawLatex(0.98, 1.55, "0.15");
  lat2->DrawLatex(1.38, 1.55, "0.1");
  //  lat2->DrawLatex(0.87, 0.9, "50");

  lat2->DrawLatex(1.3, 1.65, "#Delta#it{R}");

  ss.str("");


  
  ss << "figures/LundPlane_UFtoRaw_";
  ss << type << "_";
  ss << date << ".pdf";
  c->SaveAs(ss.str().c_str());
}
