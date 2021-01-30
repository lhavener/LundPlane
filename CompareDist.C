void CompareDist(std::string file1, std::string file2, std::string axis, std::string tag)
{
  TCanvas* c = new TCanvas("c", "c", 500, 400);
  gStyle->SetOptStat(0);
  if (axis == "z") gPad->SetLogy();
  
  TLegend* leg = new TLegend(0.7, 0.75, 0.85, 0.85);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  leg->SetTextSize(0.035);
  
  TFile* f1 = new TFile(file1.c_str());
  TH3D* h3_1 = (TH3D*)f1->Get("Bayesian_Unfoldediter5");
  h3_1->SetName("h3_1");
  TFile* f2 = new TFile(file2.c_str());
  TH3D* h3_2 = (TH3D*)f2->Get("Bayesian_Unfoldediter5");
  h3_2->SetName("h3_2");

  TH1D* h1_1;
  TH1D* h1_2;
  if (axis == "x")
    {
      h1_1 = h3_1->ProjectionX("h1_1");
      h1_2 = h3_2->ProjectionX("h1_2");
      h1_1->GetXaxis()->SetTitle("ln(R/#DeltaR)");
    }
  else if (axis == "y")
    {
      h1_1 = h3_1->ProjectionY("h1_1");
      h1_2 = h3_2->ProjectionY("h1_2");
      h1_1->GetXaxis()->SetTitle("ln(#it{k}_{T})");
    }
  else
    {
      h1_1 = h3_1->ProjectionZ("h1_1");
      h1_2 = h3_2->ProjectionZ("h1_2");
      h1_1->GetXaxis()->SetTitle("#it{p}_{T}");
    }

  h1_1->Scale(1./h1_1->Integral(), "width");
  h1_2->Scale(1./h1_2->Integral(), "width");

  h1_1->SetMarkerStyle(20);
  h1_1->SetMarkerSize(1);
  h1_1->SetLineColor(kBlack);
  h1_1->SetMarkerColor(kBlack);

  h1_1->Draw();
  h1_2->SetMarkerStyle(20);
  h1_2->SetMarkerSize(1);
  h1_2->SetLineColor(kRed);
  h1_2->SetMarkerColor(kRed);
  h1_2->Draw("same");

  leg->AddEntry(h1_1, "No outlier");
  leg->AddEntry(h1_2, "Outlier");
  leg->Draw("same");

  std::stringstream ss;
  ss << "CompareDist_" << axis << "_" << tag;
  ss << "_12_10_20.pdf";
  
  c->SaveAs(ss.str().c_str());
  
}
		 
  
  
  
			
