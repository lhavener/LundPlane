TGraphAsymmErrors* MakeError(TGraphAsymmErrors* f_data, TGraphAsymmErrors* f_mc, TH1D* h1);
std::pair<TH1D*, TH1D*> CalculateDeltaCut(TH1D* h, TH1D* h_up, TH1D* h_down, bool sym);
TGraphAsymmErrors* MakeAsymmError(std::vector<TH1D*> histvec_up, std::vector<TH1D*> histvec_down, TH1D* h);
TH1D* Norm(TH3D* h2, int y1, int y2, int pt1, int pt2, std::string name, TH1D* h1);
void EvaluateSys(int pt1, int pt2, int y1, int y2, bool ifpp);
void EvaluateSys(int pt1, int pt2, int y1, int y2, bool ifpp)
{
  //  std::string file_nom = "Unfold_nom_test_Dec6.root";
  std::string file_nom = "Unfold_FastSimPythia_fastsim_Feb28.root";
  std::string file_nom2 = "Unfold_nom_test_Dec5.root";
  std::string file_matchup = "Unfold3DLund_matchup_Nov8.root";
  std::string file_matchdown = "Unfold3DLund_matchdown_Nov8.root";
  std::string file_truncup = "Unfold_nom_truncup_test_Dec4.root";
  std::string file_truncdown = "Unfold_nom_truncup_test_Dec4.root";
  std::string file_rw = "Unfold_nom_rw_Dec6.root";
  std::string file_herwig2 = "Unfold_FastSimHerwig_fastsim_Feb28.root";
  std::string file_eff = "Unfold3DLund_eff_Nov16.root";
  std::string file_close = "UnfoldSplit_rwdata_Dec5.root";
  std::string file_sherpa = "SherpaHistograms_Ahadic.root";
  std::string file_sherpaL = "SherpaHistograms_lundstring.root";
  std::string file_herwig = "HerwigHistogramsPartLevel.root";
  std::string shherhist = "histokt";
  if (y1 == 2) shherhist = "histokt_wide";
  if (y1 == 5) shherhist = "histokt_narrow";
  
  std::string histnamecluf = "Bayesian_Unfoldediter5"; 
  std::string histnamecltrue = "true_match"; 

  std::string effname = "true_match";
  std::string effdenname = "truef";
  std::string histname = "Bayesian_Unfoldediter5";
  std::string histnameplus1 = "Bayesian_Unfoldediter6";
  std::string histnamemin2 = "Bayesian_Unfoldediter4";

  std::string eff1Dname = "h1_true";
  std::string eff1Ddenname = "h1_fulleff";
  std::string hist1Dname = "Bayesian_Unfolded1Diter5";
  
    
  std::vector<TH1D*> histvec;
  std::vector<TH1D*> histvec_up;
  std::vector<TH1D*> histvec_down;
  
  TGraphAsymmErrors* h1_mc_err = new TGraphAsymmErrors();

  TFile* fnom = new TFile(file_nom.c_str());
  TH3D* h2_nom = (TH3D*)fnom->Get(histname.c_str());
  h2_nom->SetName("h2_nom");
  TH1D* h1_norm = (TH1D*)fnom->Get(hist1Dname.c_str());
  h1_norm->SetName("h1_norm");
  TH3D* heff_nom = (TH3D*)fnom->Get(effname.c_str());
  heff_nom->SetName("heff_nom");
  TH3D* heff_nom_den = (TH3D*)fnom->Get(effdenname.c_str());
  heff_nom_den->SetName("heff_nom_den");
  heff_nom->Divide(heff_nom_den);
  h2_nom->Divide(heff_nom);
  TH1D* heff_norm = (TH1D*)fnom->Get(eff1Dname.c_str());
  heff_norm->SetName("heff_norm");
  TH1D* heff_norm_den = (TH1D*)fnom->Get(eff1Ddenname.c_str());
  heff_norm_den->SetName("heff_norm_den");
  heff_norm->Divide(heff_norm_den);
  h1_norm->Divide(heff_norm);
  TH1D* h1_nom = (TH1D*)Norm(h2_nom, y1, y2, pt1, pt2, "h1_nom", h1_norm);
  histvec.push_back(h1_nom);
  TH3D* h2_iterhigh = (TH3D*)fnom->Get(histnameplus1.c_str());
  h2_iterhigh->Divide(heff_nom);
  TH1D* h1_iterhigh = (TH1D*)Norm(h2_iterhigh, y1, y2, pt1, pt2, "h1_iterhigh", h1_norm);
  histvec.push_back(h1_iterhigh);
  TH3D* h2_iterlow = (TH3D*)fnom->Get(histnamemin2.c_str());
  h2_iterlow->Divide(heff_nom);
  TH1D* h1_iterlow = (TH1D*)Norm(h2_iterlow,y1, y2, pt1, pt2, "h1_iterlow", h1_norm);  
  histvec.push_back(h1_iterlow);
  std::pair<TH1D*, TH1D*> iter = CalculateDeltaCut(h1_nom, h1_iterhigh, h1_iterlow, false);
  histvec_up.push_back(iter.first);
  histvec_down.push_back(iter.second);

   TFile* fnom2 = new TFile(file_nom2.c_str());
  TH3D* h2_nom2 = (TH3D*)fnom2->Get(histname.c_str());
  h2_nom2->SetName("h2_nom2");
  TH1D* h1_norm2 = (TH1D*)fnom2->Get(hist1Dname.c_str());
  h1_norm2->SetName("h1_norm2");
  TH3D* heff_nom2 = (TH3D*)fnom2->Get(effname.c_str());
  heff_nom2->SetName("heff_nom2");
  TH3D* heff_nom2_den = (TH3D*)fnom2->Get(effdenname.c_str());
  heff_nom2_den->SetName("heff_nom2_den");
  heff_nom2->Divide(heff_nom2_den);
  h2_nom2->Divide(heff_nom2);
  TH1D* heff_norm2 = (TH1D*)fnom2->Get(eff1Dname.c_str());
  heff_norm2->SetName("heff_norm2");
  TH1D* heff_norm2_den = (TH1D*)fnom2->Get(eff1Ddenname.c_str());
  heff_norm2_den->SetName("heff_norm2_den");
  heff_norm2->Divide(heff_norm2_den);
  h1_norm2->Divide(heff_norm2);
  TH1D* h1_nom2 = (TH1D*)Norm(h2_nom2, y1, y2, pt1, pt2, "h1_nom2", h1_norm2);
  histvec.push_back(h1_nom2);

  
  TFile* fmatchup = new TFile(file_matchup.c_str());
  TH3D* h2_matchup = (TH3D*)fmatchup->Get(histname.c_str());
  h2_matchup->SetName("h2_matchup");
  TH1D* h1_norm_matchup = (TH1D*)fmatchup->Get(hist1Dname.c_str());
  h1_norm_matchup->SetName("h1_norm_matchup");
  TH3D* heff_matchup = (TH3D*)fmatchup->Get(effname.c_str());
  heff_matchup->SetName("heff_matchup");
  TH3D* heff_matchup_den = (TH3D*)fmatchup->Get(effdenname.c_str());
  heff_matchup_den->SetName("heff_matchup_den");
  heff_matchup->Divide(heff_matchup_den);
  h2_matchup->Divide(heff_matchup);
  TH1D* heff_norm_matchup = (TH1D*)fmatchup->Get(eff1Dname.c_str());
  heff_norm_matchup->SetName("heff_norm_matchup");
  TH1D* heff_norm_matchup_den = (TH1D*)fmatchup->Get(eff1Ddenname.c_str());
  heff_norm_matchup_den->SetName("heff_norm_matchup_den");
  heff_norm_matchup->Divide(heff_norm_matchup_den);
  h1_norm_matchup->Divide(heff_norm_matchup);
  TH1D* h1_matchup = (TH1D*)Norm(h2_matchup, y1, y2, pt1, pt2, "h1_matchup", h1_norm_matchup);
  histvec.push_back(h1_matchup);
  TFile* fmatchdown = new TFile(file_matchdown.c_str());
  TH3D* h2_matchdown = (TH3D*)fmatchdown->Get(histname.c_str());
  h2_matchdown->SetName("h2_matchdown");
  TH1D* h1_norm_matchdown = (TH1D*)fmatchdown->Get(hist1Dname.c_str());
  h1_norm_matchdown->SetName("h1_norm_matchdown");
  TH3D* heff_matchdown = (TH3D*)fmatchdown->Get(effname.c_str());
  heff_matchdown->SetName("heff_matchdown");
  TH3D* heff_matchdown_den = (TH3D*)fmatchdown->Get(effdenname.c_str());
  heff_matchdown_den->SetName("heff_matchdown_den");
  heff_matchdown->Divide(heff_matchdown_den);
  h2_matchdown->Divide(heff_matchdown);
  TH1D* heff_norm_matchdown = (TH1D*)fmatchdown->Get(eff1Dname.c_str());
  heff_norm_matchdown->SetName("heff_norm_matchdown");
  TH1D* heff_norm_matchdown_den = (TH1D*)fmatchdown->Get(eff1Ddenname.c_str());
  heff_norm_matchdown_den->SetName("heff_norm_matchdown_den");
  heff_norm_matchdown->Divide(heff_norm_matchdown_den);
  h1_norm_matchdown->Divide(heff_norm_matchdown);
  TH1D* h1_matchdown = (TH1D*)Norm(h2_matchdown, y1, y2, pt1, pt2, "h1_matchdown", h1_norm_matchdown);
  histvec.push_back(h1_matchdown);
  std::pair<TH1D*, TH1D*> match = CalculateDeltaCut(h1_matchup, h1_matchdown, h1_matchdown, true);
  histvec_up.push_back(match.first);
  histvec_down.push_back(match.second);
  
  TFile* ftruncup = new TFile(file_truncup.c_str());
  TH3D* h2_truncup = (TH3D*)ftruncup->Get(histname.c_str());
  h2_truncup->SetName("h2_truncup");
  TH1D* h1_norm_truncup = (TH1D*)ftruncup->Get(hist1Dname.c_str());
  h1_norm_truncup->SetName("h1_norm_truncup");
  TH3D* heff_truncup = (TH3D*)ftruncup->Get(effname.c_str());
  heff_truncup->SetName("heff_truncup");
  TH3D* heff_truncup_den = (TH3D*)ftruncup->Get(effdenname.c_str());
  heff_truncup_den->SetName("heff_truncup_den");
  heff_truncup->Divide(heff_truncup_den);
  h2_truncup->Divide(heff_truncup);
  TH1D* heff_norm_truncup = (TH1D*)ftruncup->Get(eff1Dname.c_str());
  heff_norm_truncup->SetName("heff_norm_truncup");
  TH1D* heff_norm_truncup_den = (TH1D*)ftruncup->Get(eff1Ddenname.c_str());
  heff_norm_truncup_den->SetName("heff_norm_truncup_den");
  heff_norm_truncup->Divide(heff_norm_truncup_den);
  h1_norm_truncup->Divide(heff_norm_truncup);                                                                                                                            
  TH1D* h1_truncup = (TH1D*)Norm(h2_truncup, y1, y2, pt1, pt2, "h1_truncup", h1_norm_truncup);
  histvec.push_back(h1_truncup);
  TFile* ftruncdown = new TFile(file_truncdown.c_str());
  TH3D* h2_truncdown = (TH3D*)ftruncdown->Get(histname.c_str());
  h2_truncdown->SetName("h2_truncdown");
  TH1D* h1_norm_truncdown = (TH1D*)ftruncdown->Get(hist1Dname.c_str());
  h1_norm_truncdown->SetName("h1_norm_truncdown");
  TH3D* heff_truncdown = (TH3D*)ftruncdown->Get(effname.c_str());
  heff_truncdown->SetName("heff_truncdown");
  TH3D* heff_truncdown_den = (TH3D*)ftruncdown->Get(effdenname.c_str());
  heff_truncdown_den->SetName("heff_truncdown_den");
  heff_truncdown->Divide(heff_truncdown_den);
  h2_truncdown->Divide(heff_truncdown);
  TH1D* heff_norm_truncdown = (TH1D*)ftruncdown->Get(eff1Dname.c_str());
  heff_norm_truncdown->SetName("heff_norm_truncdown");
  TH1D* heff_norm_truncdown_den = (TH1D*)ftruncdown->Get(eff1Ddenname.c_str());
  heff_norm_truncdown_den->SetName("heff_norm_truncdown_den");
  heff_norm_truncdown->Divide(heff_norm_truncdown_den);
  h1_norm_truncdown->Divide(heff_norm_truncdown);
  TH1D* h1_truncdown = (TH1D*)Norm(h2_truncdown, y1, y2, pt1, pt2, "h1_truncdown", h1_norm_truncdown);
  histvec.push_back(h1_truncdown);
  std::pair<TH1D*, TH1D*> trunc = CalculateDeltaCut(h1_nom, h1_truncup, h1_truncdown, true);
  histvec_up.push_back(trunc.first);
  histvec_down.push_back(trunc.second);
  
  TFile* frw = new TFile(file_rw.c_str());
  TH3D* h2_rw = (TH3D*)frw->Get(histname.c_str());
  std::cout << h2_rw->Integral() << std::endl;
  h2_rw->SetName("h2_rw");
  TH1D* h1_norm_rw = (TH1D*)frw->Get(hist1Dname.c_str());
  h1_norm_rw->SetName("h1_norm_rw");
  TH3D* heff_rw = (TH3D*)frw->Get(effname.c_str());
  heff_rw->SetName("heff_rw");
  TH3D* heff_rw_den = (TH3D*)frw->Get(effdenname.c_str());
  heff_rw_den->SetName("heff_rw_den");
  heff_rw->Divide(heff_rw_den);
  h2_rw->Divide(heff_rw);
  TH1D* heff_norm_rw = (TH1D*)frw->Get(eff1Dname.c_str());
  heff_norm_rw->SetName("heff_norm_rw");
  TH1D* heff_norm_rw_den = (TH1D*)frw->Get(eff1Ddenname.c_str());
  heff_norm_rw_den->SetName("heff_norm_rw_den");
  heff_norm_rw->Divide(heff_norm_rw_den);
  h1_norm_rw->Divide(heff_norm_rw);
  TH1D* h1_rw = (TH1D*)Norm(h2_rw, y1, y2, pt1, pt2, "h1_rw", h1_norm_rw);
  histvec.push_back(h1_rw);
  std::pair<TH1D*, TH1D*> rw = CalculateDeltaCut(h1_nom, h1_rw, h1_rw, true);
  histvec_up.push_back(rw.first);
  histvec_down.push_back(rw.second);

  TFile* fherwig = new TFile(file_herwig2.c_str());
  TH3D* h2_herwig = (TH3D*)fherwig->Get(histname.c_str());
  std::cout << h2_herwig->Integral() << std::endl;
  h2_herwig->SetName("h2_herwig");
  TH1D* h1_norm_herwig = (TH1D*)fherwig->Get(hist1Dname.c_str());
  h1_norm_herwig->SetName("h1_norm_herwig");
  TH3D* heff_herwig = (TH3D*)fherwig->Get(effname.c_str());
  heff_herwig->SetName("heff_herwig");
  TH3D* heff_herwig_den = (TH3D*)fherwig->Get(effdenname.c_str());
  heff_herwig_den->SetName("heff_herwig_den");
  heff_herwig->Divide(heff_herwig_den);
  h2_herwig->Divide(heff_herwig);
  TH1D* heff_norm_herwig = (TH1D*)fherwig->Get(eff1Dname.c_str());
  heff_norm_herwig->SetName("heff_norm_herwig");
  TH1D* heff_norm_herwig_den = (TH1D*)fherwig->Get(eff1Ddenname.c_str());
  heff_norm_herwig_den->SetName("heff_norm_herwig_den");
  heff_norm_herwig->Divide(heff_norm_herwig_den);
  h1_norm_herwig->Divide(heff_norm_herwig);
  TH1D* h1_herwig2 = (TH1D*)Norm(h2_herwig, y1, y2, pt1, pt2, "h1_herwig2", h1_norm_herwig);
  histvec.push_back(h1_herwig2);
  std::pair<TH1D*, TH1D*> herwig = CalculateDeltaCut(h1_nom, h1_herwig2, h1_herwig2, true);
  histvec_up.push_back(herwig.first);
  histvec_down.push_back(herwig.second);


  TFile* feff = new TFile(file_eff.c_str());
  TH3D* h2_eff = (TH3D*)feff->Get(histname.c_str());
  h2_eff->SetName("h2_eff");
  TH1D* h1_norm_eff = (TH1D*)feff->Get(hist1Dname.c_str());
  h1_norm_eff->SetName("h1_norm_eff");
  TH3D* heff_eff = (TH3D*)feff->Get(effname.c_str());
  heff_eff->SetName("heff_eff");
  TH3D* heff_eff_den = (TH3D*)feff->Get(effdenname.c_str());
  heff_eff_den->SetName("heff_eff_den");
  heff_eff->Divide(heff_eff_den);
  h2_eff->Divide(heff_eff);
  TH1D* heff_norm_eff = (TH1D*)feff->Get(eff1Dname.c_str());
  heff_norm_eff->SetName("heff_norm_eff");
  TH1D* heff_norm_eff_den = (TH1D*)feff->Get(eff1Ddenname.c_str());
  heff_norm_eff_den->SetName("heff_norm_eff_den");
  heff_norm_eff->Divide(heff_norm_eff_den);
  h1_norm_eff->Divide(heff_norm_eff);
  TH1D* h1_eff = (TH1D*)Norm(h2_eff, y1, y2, pt1, pt2, "h1_eff", h1_norm_eff);
  histvec.push_back(h1_eff);
  std::pair<TH1D*, TH1D*> eff = CalculateDeltaCut(h1_nom, h1_eff, h1_eff, true);
  histvec_up.push_back(eff.first);
  histvec_down.push_back(eff.second);

  TFile* fclose = new TFile(file_close.c_str());
  TH3D* h2_close = (TH3D*)fclose->Get(histnamecluf.c_str());
  h2_close->SetName("h2_close");
  TH1D* h1_norm_close = (TH1D*)h2_close->ProjectionZ("h1_norm_close", y1, y2, 2, 12);
  TH1D* h1_close = (TH1D*)Norm(h2_close, y1, y2, pt1, pt2, "h1_close", h1_norm_close);
  histvec.push_back(h1_close);
  TH3D* h2_close1 = (TH3D*)fclose->Get(histnamecltrue.c_str());
  h2_close1->SetName("h2_close1");
  TH1D* h1_norm2_close = (TH1D*)h2_close1->ProjectionZ("h1_norm2_close", y1, y2, 2, 12);
  TH1D* h1_close1 = (TH1D*)Norm(h2_close1, y1, y2, pt1, pt2, "h1_close1", h1_norm2_close);
  histvec.push_back(h1_close1);
  std::pair<TH1D*, TH1D*> close = CalculateDeltaCut(h1_close1, h1_close, h1_close, true);
  //  close.first->Smooth();
  //  close.second->Smooth();
  histvec_up.push_back(close.first);
  histvec_down.push_back(close.second);
  
  TGraphAsymmErrors* h1_nom_err = MakeAsymmError(histvec_up, histvec_down, h1_nom);
  h1_nom_err->SetName("h1_nom_err");

  TH3D* h2_true = (TH3D*)fnom->Get("truef");
  h2_true->SetName("h2_true");
  TH1D* h1_true_norm = (TH1D*)fnom->Get("h1_fulleff");
  TH1D* h1_true = (TH1D*)h2_true->ProjectionY("h1_true", y1, y2, pt1, pt2);
  double dx = h2_true->GetXaxis()->GetBinUpEdge(y2) - h2_true->GetXaxis()->GetBinLowEdge(y1);
  h1_true->Scale(1./(h1_true_norm->Integral(pt1, pt2)*dx), "width");
  TH1D* h_ratio = (TH1D*)h1_true->Clone("h1_nom_ratio");
  h_ratio->Divide(h1_nom);
  //else h_ratio->Divide(h1_pp);

  TFile* fsherpa = new TFile(file_sherpa.c_str());
  //  TH3D* h2_true_sherpa = (TH3D*)fsherpa->Get("h3_sherpa");                                                                                                             
  //  TH1D* h1_norm_sherpa = (TH1D*)fsherpa->Get("fHLundIterative_proj_2");                                                                                                
  //  TH1D* h1_sherpa = (TH1D*)h2_true_sherpa->ProjectionX("h1_true_sherpa", y1, y2, pt1, pt2);                                                                            
  //  int pt12 = h1_norm_sherpa->GetXaxis()->FindBin(h2_true_sherpa->GetZaxis()->GetBinCenter(pt1));                                                                       
  //  int pt22 = h1_norm_sherpa->GetXaxis()->FindBin(h2_true_sherpa->GetZaxis()->GetBinCenter(pt2));                                                                       
  //  double dxs = h2_true_sherpa->GetYaxis()->GetBinUpEdge(y2) - h2_true_sherpa->GetYaxis()->GetBinLowEdge(y1);                                                           
  //  h1_sherpa->Scale(1./(h1_norm_sherpa->Integral(pt12, pt22)*dxs), "width");                                                                                            
  TH1D* h1_sherpa = (TH1D*)fsherpa->Get(shherhist.c_str());
  h1_sherpa->SetName("h1_sherpa");
  TH1D* h_ratio_sherpa = (TH1D*)h1_sherpa->Clone("h1_sherpa_ratio");
  h_ratio_sherpa->Divide(h1_nom);

  std::cout << "before sherpa parton" << std::endl;
  
   TFile* fsherpaL = new TFile(file_sherpaL.c_str());
  TH1D* h1_sherpaL = (TH1D*)fsherpaL->Get(shherhist.c_str());
  h1_sherpaL->SetName("h1_sherpaL");
  //  h1_sherpaL->GetXaxis()->SetRange(1, 7);
  TH1D* h_ratio_sherpaL = (TH1D*)h1_sherpaL->Clone("h1_sherpaL_ratio");
  h_ratio_sherpaL->Divide(h1_nom);

  std::cout << "before herwig" << std::endl;
  
  TFile* fherwig2 = new TFile(file_herwig.c_str());
  TH1D* h1_herwig = (TH1D*)fherwig2->Get(shherhist.c_str());
  h1_herwig->SetName("h1_herwig");
  //  h1_herwig->GetXaxis()->SetRange(1, 7);
  TH1D* h_ratio_herwig = (TH1D*)h1_herwig->Clone("h1_herwig_ratio");
  h_ratio_herwig->Divide(h1_nom);
  
  std::cout << "HERE" << std::endl;
  h1_mc_err = NULL;
  TGraphAsymmErrors* h1_ratio_err = MakeError(h1_nom_err, h1_mc_err, h_ratio);
  std::cout << "after" << std::endl;

  TGraphAsymmErrors* h1_ratio_sherpa_err = MakeError(h1_nom_err, h1_mc_err, h_ratio_sherpa);
  TGraphAsymmErrors* h1_ratio_herwig_err = MakeError(h1_nom_err, h1_mc_err, h_ratio_herwig);

  TH1D* h_ratio_one = (TH1D*)h_ratio_sherpa->Clone("h_ratio_one");
  h_ratio_one->Reset();
  for (int i = 1; i <= h_ratio_one->GetNbinsX(); i++) h_ratio_one->SetBinContent(i, 1.0);

  TGraphAsymmErrors* h1_ratio_one_err = MakeError(h1_nom_err, h1_mc_err, h_ratio_one);

  std::stringstream name;
  name << "Resultslnkt_";
  name << y1 << "to" << y2 << "_" << pt1 <<"to" <<pt2 << "_fassim_Mar1.root";

  TFile* fout = new TFile(name.str().c_str(), "recreate");
  fout->cd("/");
  for (int i = 0; i < histvec.size(); i++) histvec.at(i)->Write();
  for (int i = 0; i < histvec_up.size(); i++) histvec_up.at(i)->Write();
  for (int i = 0; i < histvec_down.size(); i++) histvec_down.at(i)->Write();
  h1_true->Write();
  h_ratio->Write();
  h1_sherpa->Write();
  h1_sherpaL->Write();
  h1_herwig->Write();
  h1_herwig2->Write();
  h_ratio_sherpa->Write();
  h_ratio_sherpaL->Write();
  h_ratio_herwig->Write();
  h_ratio_one->Write();
  h1_ratio_one_err->Write();
  h1_nom_err->Write();
  //  h1_mc_err->Write();
  h1_ratio_err->Write();
  h1_ratio_sherpa_err->Write();
  h1_ratio_herwig_err->Write();
  fout->Close();

  name.str("");
}


TH1D* Norm(TH3D* h2, int y1, int y2, int pt1, int pt2, std::string name, TH1D* h1)
{
  
  TH1D* h = (TH1D*)h2->ProjectionY(name.c_str(), y1, y2, pt1, pt2);
  std::string effname;
  double dx = h2->GetXaxis()->GetBinUpEdge(y2) - h2->GetXaxis()->GetBinLowEdge(y1);
  h->Scale(1./(h1->Integral(pt1, pt2)*dx), "width");
  return h;
}

TGraphAsymmErrors* MakeAsymmError(std::vector<TH1D*> histvec_up, std::vector<TH1D*> histvec_down, TH1D* h)
{
  std::stringstream ss;

  ss << h->GetName() << "_tot_up";
  TH1D* h_up = (TH1D*)histvec_up.at(0)->Clone(ss.str().c_str());
  ss.str("");
  for (int i = 0; i < histvec_up.size(); i++)
    {
      std::cout <<  histvec_up.at(i)->GetName() << std::endl;
      h_up->Add(histvec_up.at(i));
    }

  ss << h->GetName() << "_tot_down";
  TH1D* h_down = (TH1D*)histvec_down.at(0)->Clone(ss.str().c_str());
  ss.str("");
  for (int i = 0; i < histvec_down.size(); i++)
    {
      h_down->Add(histvec_down.at(i));
    }

  ss << h->GetName() << "_sys";
  TGraphAsymmErrors* g = new TGraphAsymmErrors();
  g->SetName(ss.str().c_str());
  ss.str("");

  for (int i = 1; i <= h_up->GetNbinsX(); i++)
    {
      double y = h->GetBinContent(i);
      double x = h->GetBinCenter(i);
      double dx = h->GetBinWidth(i)*0.5;

      double dy_low = sqrt(h_down->GetBinContent(i));
      double dy_high = sqrt(h_up->GetBinContent(i));

      g->SetPoint(i-1, x, y);
      g->SetPointError(i-1, dx, dx, dy_low, dy_high);
    }
  return g;
}


std::pair<TH1D*, TH1D*> CalculateDeltaCut(TH1D* h, TH1D* h_up, TH1D* h_down, bool sym)
{
  std::stringstream name;

  name << h_up->GetName() << "_delta_up";
  TH1D* h_delta_up = (TH1D*)h_up->Clone(name.str().c_str());
  h_delta_up->Reset();
  name.str("");
  if (!h_down) name << h_up->GetName() << "_delta_down";
  else name << h_down->GetName() << "_delta_down";
  TH1D* h_delta_down = (TH1D*)h_up->Clone(name.str().c_str());
  h_delta_down->Reset();

  ;
  for (int i = 1; i <= h->GetNbinsX(); i++)
    {
      float cont = h->GetBinContent(i);
      float delta_up = cont - h_up->GetBinContent(i);
      float delta_down = 0.;
      if (h_down) delta_down = cont - h_down->GetBinContent(i);
      float delta_low =  0.;
      float delta_high =  0.;
      if (!sym)
	{
	  if ((delta_up < 0) &&  (delta_down < 0)){
	    delta_high = delta_up*delta_up + delta_down*delta_down;
	  }
	  else if ((delta_up < 0) && (delta_down > 0)) {
	    delta_high = delta_up*delta_up;
	    delta_low = delta_down*delta_down;
	  }
	  else if ((delta_up > 0) && (delta_down < 0)) {
	    delta_high = delta_down*delta_down;
	    delta_low = delta_up*delta_up;
	  }
	  else if ((delta_up > 0) && (delta_down > 0)) {
	    delta_low = delta_up*delta_up + delta_down*delta_down;
	  }
	  else;                                                                                                         
	}
      else 
	{
	  if (h_up && h_down)
	    {
	      delta_low = delta_up*delta_up;
	      delta_high = delta_down*delta_down;
	    }
	  else 
	    {
	      if (delta_up > 0) delta_low = delta_up*delta_up;
	      else             delta_high = delta_up*delta_up;
	    }	  
	}
	  
      h_delta_down->SetBinContent(i, delta_low);
      h_delta_up->SetBinContent(i, delta_high);
    }

  return std::pair<TH1D*, TH1D*> (h_delta_up, h_delta_down);
}  

TGraphAsymmErrors* MakeError(TGraphAsymmErrors* g_data, TGraphAsymmErrors* g_mc, TH1D* h1)
{
  std::stringstream ss;

  ss << h1->GetName() << "_err";
  TGraphAsymmErrors* g=new TGraphAsymmErrors();
  g->SetName(ss.str().c_str());
  ss.str("");

  for (int i = 1; i <= h1->GetNbinsX(); i++)
    {
      float x = h1->GetBinCenter(i);
      float y = h1->GetBinContent(i);
      float dx = h1->GetBinWidth(i)*0.5;
      double y_data = -1;
      double x_data = -1;
      g_data->GetPoint(i-1, x_data, y_data);
      double y_mc = -1;
      double x_mc = -1;
      if (g_mc) g_mc->GetPoint(i-1, x_mc, y_mc);
      double y_low_data = g_data->GetErrorYlow(i-1)/y_data;
      double y_high_data = g_data->GetErrorYhigh(i-1)/y_data;
      if (y_data == 0.) {y_low_data = 0.; y_high_data = 0.;}
      double y_low_mc = 0.;
      double y_high_mc = 0.;
      if (g_mc)
	{
	  y_low_mc =g_mc->GetErrorYlow(i-1)/y_mc;
	  y_high_mc =g_mc->GetErrorYhigh(i-1)/y_mc;
	}
      if (y_mc == 0.) {y_low_mc = 0.; y_high_mc = 0.;}
      double dy_low = 0;
      double dy_high = 0;
      if (!g_mc) {
	dy_low = sqrt(y_low_data*y_low_data)*y;
	dy_high = sqrt(y_high_data*y_high_data)*y;
      }
      else {
	dy_low = sqrt(y_low_data*y_low_data + y_high_mc*y_high_mc)*y;
	dy_high = sqrt(y_high_data*y_high_data + y_low_mc*y_low_mc)*y;
      }
      g->SetPoint(i-1, x, y);
      g->SetPointError(i-1, dx, dx, dy_low, dy_high);
    }
  return g;
}


