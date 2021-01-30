void SubjetPurity(std::string file, std::string date, int pt1, int pt2, int sub1, int sub2)
{
  TFile* f = new TFile(file.c_str());
  
  std::stringstream ss;
  ss << "h_";
  if ((sub1 == 1) && (sub2 == -1)) ss << "1";
  else if ((sub1 == -1) && (sub2 == 1)) ss << "2";
  else ss << sub1 << sub2;
  TH3D* h3_eff_num = (TH3D*)f->Get(ss.str().c_str());
  ss.str("");
  h3_eff_num->GetZaxis()->SetRange(pt1, pt2);
  TH2D* h2_eff = (TH2D*)h3_eff_num->Project3D("yx");
  h2_eff->SetName("h2_eff");
  TH3D* h3_eff_den = (TH3D*)f->Get("h");
  h3_eff_den->GetZaxis()->SetRange(pt1, pt2);
  TH2D* h2_eff_den = (TH2D*)h3_eff_den->Project3D("yx");
  h2_eff_den->SetName("h2_eff_den");
  h2_eff->Divide(h2_eff_den);
  
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
  if (sub1 == -1) ss << "Emission ";
  else if (sub2 == -1) ss << "Leading subjet ";
  else {
    if (sub1 == 1) ss << "Leading matched, ";
    else ss << "Leading unmatched, ";
    if (sub2 == 1) ss << "Emission matched ";
    else ss << "Emission unmatched ";
  }
  ss << "purity";
  h2_eff->SetTitle(ss.str().c_str());
  ss.str("");

  h2_eff->Draw("TEXT");


  ss << "SubjetPurity_";
  if (sub1 != -1){
    if (sub2 == -1) ss << 1;
    else ss << sub1;}
  if (sub2 != -1) {
    if (sub1 == -1) ss << 2;
    else ss << sub2;
  }
  ss << "_" << date << ".pdf";
  c->SaveAs(ss.str().c_str());
}
