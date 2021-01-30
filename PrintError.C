void PrintError(std::string file, std::string err, std::string up)
{
  TFile* f = new TFile(file.c_str());
  TH1D* h1 = (TH1D*)f->Get("h1_nom");
  std::stringstream ss;
  ss << "h1_" << err << "_delta_" << up;
  TH1D* h_err = (TH1D*)f->Get(ss.str().c_str());
  ss.str("");
  double err1 = h_err->GetBinContent(7);
  double err2 = h_err->GetBinContent(9);
  double err3 = h_err->GetBinContent(12);
  double nom1 = h1->GetBinContent(7);
  double nom2 = h1->GetBinContent(9);
  double nom3 = h1->GetBinContent(12);

  err1 = (sqrt(err1)/nom1)*100.;
  err2 = (sqrt(err2)/nom2)*100.;
  err3 = (sqrt(err3)/nom3)*100.;

  std::cout << "% Rel. Error: " << err1 << ", " << err2 << ", " << err3 << std::endl;
}
  
