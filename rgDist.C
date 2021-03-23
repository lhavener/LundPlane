void rgDist_UF(std::string file_data, std::string date, int pt1, int pt2, int y1, int y2, bool ifpp)
{
  std::stringstream ss;

  TFile* f_data = new TFile(file_data.c_str());
  ss << "h1_nom";
  TH1D* h1_data = (TH1D*)f_data->Get(ss.str().c_str());
  h1_data->SetName("h1_data");
  ss.str("");
  if(!ifpp) ss << "h1_true";
  else ss << "h1_pp";
  TH1D* h1_mc = (TH1D*)f_data->Get(ss.str().c_str());
  h1_mc->SetName("h1_mc");
  ss.str("");

  TH1D* h1_her = (TH1D*)f_data->Get("h1_herwig");
  //  h1_mc->SetName("h1_mc");
  ss.str("");
  TH1D* h1_she = (TH1D*)f_data->Get("h1_sherpa");
  //  h1_mc->SetName("h1_mc");
  ss.str("");

  TH1D* h1_sheL = (TH1D*)f_data->Get("h1_sherpaL");
  //  h1_mc->SetName("h1_mc");
  ss.str("");

  ss << "h1_nom_err";
  TGraphAsymmErrors* g_data = (TGraphAsymmErrors*)f_data->Get(ss.str().c_str());
  g_data->SetName("g_data");
  ss.str("");

  ss << "h1_pp_err";
  TGraphAsymmErrors* g_mc;
  if (ifpp)
    {
      g_mc= (TGraphAsymmErrors*)f_data->Get(ss.str().c_str());
      g_mc->SetName("g_mc");
    }
  ss.str("");


  ss << "h1_nom_ratio";
  cout << ss.str() << endl;
  TH1D* h1_ratio = (TH1D*)f_data->Get(ss.str().c_str());
  ss.str("");
  ss << "h1_nom_ratio_err";
  cout << ss.str() << endl;
  TGraphAsymmErrors* g_ratio = (TGraphAsymmErrors*)f_data->Get(ss.str().c_str());
  ss.str("");
  

  ss << "h1_herwig_ratio";
  cout << ss.str() << endl;
  TH1D* h1_her_ratio = (TH1D*)f_data->Get(ss.str().c_str());
  ss.str("");
  ss << "h1_herwig_ratio_err";
  cout << ss.str() << endl;
  TGraphAsymmErrors* g_her_ratio = (TGraphAsymmErrors*)f_data->Get(ss.str().c_str());
  ss.str("");

  ss << "h1_sherpa_ratio";
  cout << ss.str() << endl;
  TH1D* h1_she_ratio = (TH1D*)f_data->Get(ss.str().c_str());
  ss.str("");
  ss << "h1_sherpa_ratio_err";
  cout << ss.str() << endl;
  TGraphAsymmErrors* g_she_ratio = (TGraphAsymmErrors*)f_data->Get(ss.str().c_str());
  ss.str("");

  ss << "h1_sherpaL_ratio";
  cout << ss.str() << endl;
  TH1D* h1_sheL_ratio = (TH1D*)f_data->Get(ss.str().c_str());
  ss.str("");
  
  ss << "h_ratio_one";
  cout << ss.str() << endl;
  TH1D* h1_o_ratio = (TH1D*)f_data->Get(ss.str().c_str());
  ss.str("");
  ss << "h_ratio_one_err";
  cout << ss.str() << endl;
  TGraphAsymmErrors* g_o_ratio = (TGraphAsymmErrors*)f_data->Get(ss.str().c_str());
  ss.str("");

  TCanvas* c = new TCanvas("c", "c", 750, 750);
  gStyle->SetOptStat(0);
  //  gStyle->SetPadTicksy(1);                                                                                                                                                                                                                               
  TPad* p1=new TPad("p1","p1",0,0,1,1);
  p1->SetMargin(0.19,0.05,0.4,0.1);
  TPad* p2=new TPad("p2","p2",0,0,1,1);
  p2->SetMargin(0.19,0.05,0.1,0.6);
  p2->SetFillStyle(4000);

  
  TLegend* leg = new TLegend(0.2, 0.66, 0.35, 0.88);
  leg->SetFillColor(0);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  leg->SetTextSize(0.04);
  // leg->SetNDC(true);
  TLatex* lat = new TLatex();
  lat->SetTextFont(42);
  lat->SetNDC(true);
  lat->SetTextSize(0.04);
  lat->SetTextAlign(33);

  p1->cd();
  gPad->SetTickx();
  gPad->SetTicky();
  /*  TGaxis *axis1 = new TGaxis(0,15.99,0.35, 15.99,0,0.875, 8,"-");
  axis1->SetName("axis1");
  axis1->SetLabelSize(0.05);
  axis1->SetTitle("#it{#theta}_{g}");
  axis1->SetTitleSize(0.05);
  axis1->SetTitleOffset(0.8);
  axis1->SetLabelFont(42);
  axis1->SetTitleFont(42);
  axis1->SetTickLength(0.01);*/
  

  h1_data->GetXaxis()->SetTitleSize(0.05);
  h1_data->GetYaxis()->SetTitleOffset(1.9);
  h1_data->GetXaxis()->SetLabelSize(0.05);					   
  h1_data->GetXaxis()->SetLabelOffset(0.95);					   
  h1_data->GetYaxis()->SetLabelSize(0.05);					   
  h1_data->GetXaxis()->SetTitle("#it{R}_{g}");
  h1_data->GetYaxis()->SetTitleSize(0.04);
  h1_data->GetYaxis()->SetTitle("#frac{1}{#it{N}_{jets}} #frac{d#it{N}_{emissions}}{dln(#it{k}_{T}/GeV)dln(#it{R}/#Delta#it{R})}");
  h1_data->GetXaxis()->SetTickLength(h1_data->GetYaxis()->GetTickLength()*0.5);
  h1_data->GetYaxis()->SetTickLength(h1_data->GetYaxis()->GetTickLength()*1.5);
  h1_data->SetLineColor(kBlack);
  h1_data->SetMarkerColor(kBlack);
  h1_data->SetMarkerStyle(20);
  h1_data->SetMarkerSize(1);
  h1_data->SetTitle("");
  h1_data->GetXaxis()->SetRangeUser(0, 1.4);
  h1_data->GetYaxis()->SetRangeUser(0, 2.25);
  h1_data->GetXaxis()->SetNdivisions(8);
  h1_data->GetYaxis()->SetNdivisions(505);
  h1_data->Draw("pe");

  //  axis1->Draw();
  h1_mc->SetLineColor(632-4);
  h1_mc->SetMarkerColor(632-4);
  h1_mc->SetMarkerStyle(21);
  h1_mc->SetMarkerSize(1);
  h1_mc->Draw("same");

  h1_her->SetLineColor(600-6);
  h1_her->SetMarkerColor(600-6);
  h1_her->SetMarkerStyle(33);
  h1_her->SetMarkerSize(1.6);
  h1_her->Draw("same");

  h1_she->SetLineColor(kGreen-2);
  h1_she->SetMarkerColor(kGreen-2);
  h1_she->SetMarkerStyle(34);
  h1_she->SetMarkerSize(1.2);
  h1_she->Draw("same");

  h1_sheL->SetLineColor(kViolet);
  h1_sheL->SetMarkerColor(kViolet);
  h1_sheL->SetMarkerStyle(29);
  h1_sheL->SetMarkerSize(1.6);
  h1_sheL->Draw("same");
  
  std::cout << "1" << std::endl;
  g_data->SetFillColorAlpha(kGray+3, 0.3);
  g_data->SetLineColor(kBlack);
  g_data->SetMarkerColor(kBlack);
  g_data->SetMarkerStyle(20);
  g_data->SetMarkerSize(1);
  g_data->SetLineWidth(1);
  g_data->Draw("2 same");
  std::cout << "1" << std::endl;
  std::cout << "1" << std::endl;
  h1_data->Draw("same");
  h1_mc->Draw("same");
  h1_her->Draw("same");
  h1_she->Draw("same");
  leg->AddEntry(h1_mc, "PYTHIA8 Monash");
  leg->AddEntry(h1_her, "Herwig 7");
  leg->AddEntry(h1_she, "Sherpa (AHADIC)");
  leg->AddEntry(h1_sheL, "Sherpa (Lund)");
  leg->AddEntry(h1_data, "pp");
  leg->AddEntry(g_data, "Sys. uncertainty", "f");

  std::cout << "1" << std::endl;
  leg->Draw("same");
  ss.str("");
  lat->DrawLatex(0.92, 0.88, "ALICE Preliminary");
  lat->DrawLatex(0.92, 0.835, "pp #sqrt{#it{s}} = 13 TeV");
  lat->DrawLatex(0.92, 0.79, "Charged-particle jets");
  lat->DrawLatex(0.92, 0.745, "anti-#it{k}_{T} #it{R} = 0.4, |#it{#eta}_{jet}| < 0.5");
  if ((pt1 == 2) && (pt2 == 5)) lat->DrawLatex(0.92, 0.695, "20 < #it{p}_{T, jet}^{ch} < 120 GeV/#it{c}");
  else if ((pt1 == 2) && (pt2 == 2)) lat->DrawLatex(0.92, 0.7, "20 < #it{p}_{T, ch jet} < 40 GeV/#it{c}");
  else if ((pt1 == 5) && (pt2 == 5)) lat->DrawLatex(0.92, 0.66, "80 < #it{p}_{T, ch jet} < 120 GeV/#it{c}");

  lat->SetTextAlign(11);
  if (y1 == 2) ss << "#font[122]{-}1.0";
  else if (y1 == 7) ss << "0";
  ss << " < ln(#it{k}_{T}/GeV) < ";
  if (y2 == 12) ss << "1.5";
  else if (y2 == 6) ss << "0";
  lat->DrawLatex(0.22, 0.455, ss.str().c_str());
  ss.str("");
  if (y1 == 2) ss << "0.4";
  else if (y1 == 7) ss << "1.0";
  ss << " < #it{k}_{T} < ";
  if (y2 == 12) ss << "4.5";
  else if (y2 == 6) ss << "1.0";
  ss << " GeV/#it{c}";
  lat->DrawLatex(0.22, 0.415, ss.str().c_str());
  
  //  lat->DrawLatex(0.92, 0.61, "Soft Drop #it{z}_{cut} = 0.2, #it{#beta} = 0");
  //  lat->DrawLatex(0.92, 0.56, "#it{f}^{ pp}_{tagged} = 0.89, #it{f}^{ AA}_{tagged} = 0.88");

  ss.str("");
  std::cout << "1" << std::endl;

  TLatex* lat2 = new TLatex();
  lat2->SetTextFont(42);
  lat2->SetTextAlign(21);
  lat2->SetTextSize(0.05);
  lat2->DrawLatex(0 , 2.33, "0.4");
  //  lat2->DrawLatex(0.13 ,3.1, "0.35");
  lat2->DrawLatex(0.29, 2.33, "0.3");
  lat2->DrawLatex(0.47, 2.33, "0.25");
  lat2->DrawLatex(0.69, 2.33, "0.2");
  lat2->DrawLatex(0.98, 2.33, "0.15");
  lat2->DrawLatex(1.38, 2.33, "0.1");
  //  lat2->DrawLatex(0.87, 0.9, "50");                                                                                                            

  lat2->DrawLatex(1.3, 2.53, "#Delta#it{R}");
    
  p2->cd();
  gPad->SetTickx();
  gPad->SetTicky();
  gPad->SetBottomMargin(0.11);
  h1_ratio->GetXaxis()->SetLabelSize(0.05);
  h1_ratio->GetYaxis()->SetLabelSize(0.05);
  h1_ratio->GetXaxis()->SetTitleSize(0.05);
  h1_ratio->GetYaxis()->SetTitleSize(0.05);
  h1_ratio->GetYaxis()->SetTitleOffset(1.5);
  h1_ratio->GetXaxis()->SetTickLength(h1_data->GetYaxis()->GetTickLength()*0.5);
  h1_ratio->GetYaxis()->SetTickLength(h1_data->GetYaxis()->GetTickLength()*1.5);
  h1_ratio->GetYaxis()->SetTitle("MC/Data");
  h1_ratio->GetXaxis()->SetTitle("ln(#it{R}/#Delta#it{R})");
  h1_ratio->GetXaxis()->SetRangeUser(0, 1.4);
  h1_ratio->SetTitle("");
  h1_ratio->GetYaxis()->SetRangeUser(0.3, 1.4);
  h1_ratio->GetXaxis()->SetLabelOffset(0.005);
  h1_ratio->GetXaxis()->SetNdivisions(8);
  h1_ratio->GetYaxis()->SetNdivisions(503);
  h1_ratio->SetLineColor(632-4);
  h1_ratio->SetMarkerColor(632-4);
  h1_ratio->SetMarkerStyle(21);
  h1_ratio->SetMarkerSize(1);
  h1_ratio->Draw();
  h1_her_ratio->SetLineColor(600-6);
  h1_her_ratio->SetMarkerColor(600-6);
  h1_her_ratio->SetMarkerStyle(33);
  h1_her_ratio->SetMarkerSize(1.6);
  h1_her_ratio->Draw("same:");
  h1_she_ratio->SetLineColor(kGreen-2);
  h1_she_ratio->SetMarkerColor(kGreen-2);
  h1_she_ratio->SetMarkerStyle(34);
  h1_she_ratio->SetMarkerSize(1.2);
  h1_she_ratio->Draw("same:");
  h1_sheL_ratio->SetLineColor(kViolet);
  h1_sheL_ratio->SetMarkerColor(kViolet);
  h1_sheL_ratio->SetMarkerStyle(29);
  h1_sheL_ratio->SetMarkerSize(1.6);
  h1_sheL_ratio->Draw("same:");
  std::cout << "1" << std::endl;

  h1_o_ratio->SetLineColor(kBlack);
  h1_o_ratio->SetMarkerColor(kBlack);
  h1_o_ratio->SetMarkerStyle(21);
  h1_o_ratio->SetMarkerSize(1);
  //  h1_o_ratio->Draw("same:");

  g_ratio->SetFillColorAlpha(632-4, 0.3);
  g_ratio->SetLineColor(632-4);
  g_ratio->SetMarkerColor(632-4);
  g_ratio->SetMarkerStyle(20);
  g_ratio->SetMarkerSize(1);
  g_ratio->SetLineWidth(1);
  g_ratio->GetXaxis()->SetLimits(1, 13);
  //  g_ratio->Draw("2 same");

  g_her_ratio->SetFillColorAlpha(600-6, 0.3);
  g_her_ratio->SetLineColor(600-6);
  g_her_ratio->SetMarkerColor(600-6);
  g_her_ratio->SetMarkerStyle(33);
  g_her_ratio->SetMarkerSize(1.6);
  g_her_ratio->SetLineWidth(1);
  g_her_ratio->GetXaxis()->SetLimits(1, 13);
  //  g_her_ratio->Draw("2 same");

  g_she_ratio->SetFillColorAlpha(kGreen-2, 0.3);
  g_she_ratio->SetLineColor(kGreen-2);
  g_she_ratio->SetMarkerColor(kGreen-2);
  g_she_ratio->SetMarkerStyle(34);
  g_she_ratio->SetMarkerSize(1.2);
  g_she_ratio->SetLineWidth(1);
  g_she_ratio->GetXaxis()->SetLimits(1, 13);
  //  g_she_ratio->Draw("2 same");


  
  g_o_ratio->SetFillColorAlpha(kGray+3, 0.3);
  g_o_ratio->SetLineColor(kBlack);
  g_o_ratio->SetMarkerColor(kBlack);
  g_o_ratio->SetMarkerStyle(20);
  g_o_ratio->SetMarkerSize(1);
  g_o_ratio->SetLineWidth(1);
  g_o_ratio->GetXaxis()->SetLimits(1, 13);
  g_o_ratio->Draw("2 same");
  
  TLine* line = new TLine(0, 1, 1.4, 1);
  line->SetLineStyle(2);
  line->Draw("same");
  std::cout << "1" << std::endl;

  c->cd();
  p1->Draw();
  std::cout << "1" << std::endl;
  p2->Draw();
    
    
    ss << "figures/lnRDist_" << pt1 << "to" << pt2 << "_" << y1 << "to" << y2;
  ss << "_" << date << ".pdf";
  c->SaveAs(ss.str().c_str());
}
