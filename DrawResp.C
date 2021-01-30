void DrawResp(std::string file, std::string tag, int det, int part, std::string date)
{
  TFile* f = new TFile(file.c_str());
  std::stringstream ss;
  ss << "h3_";
  if (tag == "z") ss << "z";
  else ss << "theta";
  if (det != -1) ss << "_" << det;
  TH3D* h3 = (TH3D*)f->Get(ss.str().c_str());
  ss.str("");
  if (det != -1)
    {
      if (tag == "z") {
	if (det == 1) ss << "0 < ln(R/#DeltaR^{reco}) < 0.4, ";
	else if (det == 2) ss << "0.4 < ln(R/#DeltaR^{reco}) < 0.8, ";
	else if (det == 3) ss << "0.8 < ln(R/#DeltaR^{reco}) < 1.4, ";
      }
      else {
	if (det == 1) ss << "-1.0 < ln(k_{T}^{reco}) < 0., ";
	else if (det == 2) ss << "0. < ln(k_{T}^{reco}) < 1.0, ";
	else if (det == 3) ss << "1.0 < ln(k_{T}^{reco}) < 1.5, ";
      }
    }
  if (part!=-1)
    {
      if (tag == "z")
	{
	  if (part == 1) {h3->GetXaxis()->SetRange(1,2); ss << "0 < ln(R/#DeltaR^{true}) < 0.4";}
	  else if (part == 2) {h3->GetXaxis()->SetRange(3,4); ss << "0.4 < ln(R/#DeltaR^{true}) < 0.8";}
	  else if (part == 3) {h3->GetXaxis()->SetRange(5,7); ss << "0.8 < ln(R/#DeltaR^{true}) < 1.4";}
	}
      else
	{
	  if (part == 1) {h3->GetXaxis()->SetRange(1,5); ss << "-1.0 < ln(k_{T}^{reco}) < 0.";}
	  else if (part == 2) {h3->GetXaxis()->SetRange(6, 8); ss << "0. < ln(k_{T}^{reco}) < 1.0";}
	  else if (part == 3) {h3->GetXaxis()->SetRange(9, 11); ss << "1.0 < ln(k_{T}^{reco}) < 1.5";}
	}
    }

 TCanvas* c = new TCanvas("c", "c", 700, 500);
 gStyle->SetOptStat(0);
 c->SetRightMargin(0.15);
 c->SetBottomMargin(0.12);
 c->SetTopMargin(0.2);
  
  TH2D* h2 = (TH2D*)h3->Project3D("zy");
  h2->GetXaxis()->SetTitleSize(0.05);
  h2->GetYaxis()->SetTitleSize(0.05);
  h2->GetYaxis()->SetLabelSize(0.05);
  h2->GetXaxis()->SetLabelSize(0.05);
  h2->GetZaxis()->SetLabelSize(0.05);
  h2->GetZaxis()->SetTitleSize(0.05);
  h2->SetTitle(ss.str().c_str());
  ss.str("");
  if (tag == "z")
    {
      h2->GetXaxis()->SetTitle("ln(#it{k}_{T}^{true})");
      h2->GetYaxis()->SetTitle("ln(#it{k}_{T}^{reco})");
    }
  else
    {
      h2->GetXaxis()->SetTitle("ln(#it{R}/#Delta#it{R}^{true})");
      h2->GetYaxis()->SetTitle("ln(#it{R}/#Delta#it{R}^{reco})");
    }
  h2->GetZaxis()->SetTitle("Counts");
  h2->Draw("colz");

  TLatex* lat = new TLatex();
  lat->SetTextFont(42);
  lat->SetNDC(true);
  lat->SetTextSize(0.045);
  lat->SetTextAlign(11);
  lat->DrawLatex(0.15, 0.95, "ALICE Preliminary");
  lat->DrawLatex(0.15, 0.90, "PYTHIA8 pp #sqrt{s_{NN}} = 13 TeV");
  lat->DrawLatex(0.15, 0.83, "#it{R} = 0.4, |#it{#eta}_{jet}| < 0.5");
  lat->SetTextAlign(31);
  lat->DrawLatex(0.85, 0.95, "Charged-particle jets anti-#it{k}_{T}");
  lat->DrawLatex(0.85, 0.90, "20 < #it{p}_{T, ch jet} < 120 GeV/#it{c}");
  if (tag == "theta") lat->DrawLatex(0.85, 0.83, "#font[122]{-}1.0 < ln(#it{k}_{T}^{true, reco}) < 1.5 GeV/#it{c}");
  else lat->DrawLatex(0.85, 0.83, "#font[122]{-}1.0 < ln(#it{R}/#Delta#it{R}^{true, reco}) < 1.4");
  ss << "figures/Resp_" << tag;
  if (det != -1) ss << "_det" << det;
  if (part != -1) ss << "_part" << part;
  ss << "_" << date << ".pdf";
  c->SaveAs(ss.str().c_str());
}
  
