void EvaluateRatio(std::string file)
{
  TFile* f = new TFile(file.c_str());
  TH3D* h3_num = (TH3D*)f->Get("raw2");
  TH3D* h3_den = (TH3D*)f->Get("smeared2");
  TH3D* h3_rw = (TH3D*)h3_num->Clone("h3_rw");
  h3_rw->Divide(h3_den);

  TH3D* h3_smooth = (TH3D*)h3_rw->Clone("h3_smooth");
  h3_smooth->Reset();
  std::stringstream ss;
  for (int i = 1; i <= h3_smooth->GetNbinsX(); i++)
    {
      for (int j = 1; j <= h3_smooth->GetNbinsZ(); j++)
	{
	  ss << "proj_" << i << "_" << j;
	  TH1D* h1 = (TH1D*)h3_rw->ProjectionY(ss.str().c_str(), i, i, j, j);
	  h1->Smooth();
	  ss.str("");
	  for (int k = 1; k <= h1->GetNbinsX(); k++)
	    {
	      h3_smooth->SetBinContent(i, k, j, h1->GetBinContent(k));
	    }
	}
    }

  
  TFile* fout = new TFile("Reweight_full_Nov24.root", "recreate");
  fout->cd("/");
  //  h3_num->SetName("h3_rw");
  //h3_num->Smooth();
  h3_num->Write();
  h3_den->Write();
  h3_rw->Write();
  h3_smooth->Write();
  fout->Close();
}
