void PureEff(std::string file, std::string tag, std::string date, int pt1, int pt2)
{
  TFile* f = new TFile(file.c_str());

  TH2D* h2_eff;
  if (tag == "Efficiency")
    {
      TH3D* h3_eff_num = (TH3D*)f->Get("true_match");
      h3_eff_num->GetZaxis()->SetRange(pt1, pt2);
      h2_eff = (TH2D*)h3_eff_num->Project3D("yx");
      TH3D* h3_eff_den = (TH3D*)f->Get("truef");
      h3_eff_den->GetZaxis()->SetRange(pt1, pt2);
      TH2D* h2_eff_den = (TH2D*)h3_eff_den->Project3D("yx");
      h2_eff->Divide(h2_eff_den);
    }
  else
    {
      TH3D* h3_pur_num = (TH3D*)f->Get("reco");
      h2_eff = (TH2D*)h3_pur_num->Project3D("yx");
      TH3D* h3_pur_den = (TH3D*)f->Get("recof");
      TH2D* h2_pur_den = (TH2D*)h3_pur_den->Project3D("yx");
      h2_eff->Divide(h2_pur_den);
    }

  
  TCanvas* c = new TCanvas("c", "c", 700, 500);
  gStyle->SetOptStat(0);
  c->SetRightMargin(0.12);
  c->SetBottomMargin(0.12);
  c->SetTopMargin(0.15);

  h2_eff->GetXaxis()->SetTitleSize(0.05);
  h2_eff->GetXaxis()->SetTitleOffset(1.0);
  h2_eff->GetYaxis()->SetTitleOffset(0.8);
  h2_eff->GetXaxis()->SetLabelSize(0.05);
  h2_eff->GetYaxis()->SetLabelSize(0.05);
  h2_eff->GetXaxis()->SetTitle("ln(#it{R}/#Delta#it{R})");
  h2_eff->GetXaxis()->SetRangeUser(0, 1.4);
  h2_eff->GetYaxis()->SetTitleSize(0.055);
  h2_eff->GetYaxis()->SetTitle("ln(#it{k}_{T})");
  h2_eff->GetYaxis()->SetRangeUser(-1, 1.5);
  h2_eff->SetTitle(tag.c_str());

  h2_eff->Draw("TEXT");

  std::stringstream ss;
  ss << tag << "_" << date << ".pdf";
  c->SaveAs(ss.str().c_str());
}
