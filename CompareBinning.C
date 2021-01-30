void CompareBinning(std::string file1, std::string file2, std::string axis, bool rebin)
{
  TCanvas* c = new TCanvas("c", "c", 500, 400);
  gStyle->SetOptStat(0);

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

  Double_t tbins[4];
  tbins[0]=0;
  tbins[1]=20;
  tbins[2]=120;
  tbins[3]=160;

  /*   Double_t tbins[5];
  tbins[0]=0;
  tbins[1]=20;
  tbins[2]=60;
  tbins[3]=120;
  tbins[4]=160;*/

  Double_t ybinst[6];
  ybinst[0] = 0.;
  ybinst[1] = 0.4;
  ybinst[2] = 0.6;
  ybinst[3] = 1.0;
  ybinst[4] = 1.4;
  ybinst[5] = 2.5;

  /*Double_t ybinst[7];
  ybinst[0] = 0.;
  ybinst[1] = 0.3;
  ybinst[2] = 0.6;
  ybinst[3] = 0.9;
  ybinst[4] = 1.1;
  ybinst[5] = 1.4;
  ybinst[6] = 2.5;*/

  Double_t zbinst[11];
  zbinst[0]=-3.0;
  zbinst[1]=-0.5;
  zbinst[2]=-0.1;
  zbinst[3] = 0.0;
  zbinst[4] = 0.1;
  zbinst[5] = 0.3;
  zbinst[6] = 0.5;
  zbinst[7] = 0.75;
  zbinst[8] = 1.0;
  zbinst[9] = 1.5;
  zbinst[10] = 3.0;

  /*   Double_t zbinst[12];
  zbinst[0]=-3.0;
  zbinst[1]=-1.0;
  zbinst[2]=-0.5;
  zbinst[3]=-0.1;
  zbinst[4] = 0.0;
  zbinst[5] = 0.1;
  zbinst[6] = 0.3;
  zbinst[7] = 0.5;
  zbinst[8] = 0.75;
  zbinst[9] = 1.0;
  zbinst[10] = 1.5;
  zbinst[11] = 3.0;*/


  
  TH1D* h1_2_temp;
  TH1D* h1_1;
  TH1D* h1_2;
  if (axis == "x")
    {
      h1_1 = h3_1->ProjectionX("h1_1");
      h1_2_temp = h3_2->ProjectionX("h1_2_temp");
      if (rebin) h1_2 = (TH1D*)h1_2_temp->Rebin(5,"h1_2",ybinst);
      else h1_2 = h1_2_temp;
      h1_1->GetXaxis()->SetTitle("ln(R/#DeltaR)");
    }
  else if (axis == "y")
    {
      h1_1 = h3_1->ProjectionY("h1_1");
      h1_2_temp = h3_2->ProjectionY("h1_2_temp");
      if (rebin) h1_2 = (TH1D*)h1_2_temp->Rebin(10,"h1_2",zbinst);
      else h1_2	= h1_2_temp;
      h1_1->GetXaxis()->SetTitle("ln(#it{k}_{T})");
    }
  else
    {
      h1_1 = h3_1->ProjectionZ("h1_1");
      h1_2_temp = h3_2->ProjectionZ("h1_2_temp");
      if (rebin) h1_2 = (TH1D*)h1_2_temp->Rebin(3,"h1_2",tbins);
      else h1_2	= h1_2_temp;
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

  leg->AddEntry(h1_1, "New bins");
  leg->AddEntry(h1_2, "Old bins");
  leg->Draw("same");

  std::stringstream ss;
  ss << "CompareBinning_" << axis;
  if (!rebin) ss << "_norebin_";
  ss << "_12_8_20.pdf";
  
  c->SaveAs(ss.str().c_str());
  
}
		 
  
  
  
			
