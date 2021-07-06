#if !defined(__CINT__) || defined(__MAKECINT__)
#include <TInterpreter.h>
#include <TString.h>
#include <TObjString.h>
#include <TObjArray.h>
#include <TMath.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TH1D.h>
#include <TString.h>
#include <TF1.h>
#include <TStyle.h>
#include <TLegend.h>
#include <TLegendEntry.h>
#include <TDatabasePDG.h>
#include <TGraph.h>
#include <TTree.h>
#include <TMath.h>
#endif







void DrawLatex(Float_t x, Float_t y, Int_t color, const char* text, Float_t textSize = 0.06)
{
  TLatex* latex = new TLatex(x, y, text);
  latex->SetNDC();
  latex->SetTextSize(textSize);
  latex->SetTextColor(color);
  latex->SetTextFont(42);
  latex->Draw();
}



void plotRawTriggeredData(){
  Int_t option=0; 
  TCanvas *canv[20];
   TCanvas *canv_alter[20];

   TCanvas *canvej1[20];
   TCanvas *canvej1_alter[20];

    TCanvas *canvej2[20];
   TCanvas *canvej2_alter[20];
   
   TCanvas *canv2;
   TPad *pad;
   TLegend *leg;
  
  
  
   // gStyle->SetOptTitle(0);
    gStyle->SetOptStat(0);
   
    TString fname[5];
    TFile *input[5];
 
         fname[0]="CheckStats18+17_merged.root";
         input[0]=TFile::Open(fname[0]);
	     
	 TH1D *specmb;
	 TH1D *specej1;
	 TH1D *specej2;
          TH1D *specmbR;
	 TH1D *specej1R;
	 TH1D *specej2R;

	 
	 TH3D *mb;
	 TH3D *ej1;
	 TH3D *ej2; 
         TH3D *mb_alter;
	 TH3D *ej1_alter;
	 TH3D *ej2_alter; 
	 
	 TH2D *mb2d[20];
	   TH2D *ej12d[20];
	   TH2D *ej22d[20];

	   TH2D *mb2d_alter[20];
	   TH2D *ej12d_alter[20];
	   TH2D *ej22d_alter[20];
	   
	 
         double xbin[13]={20,24,28,34,40,50,60,70,80,100,120,160,200};
	 

	 
	        	 mb=(TH3D*)input[0]->Get("rmb3");
                         ej1=(TH3D*)input[0]->Get("rej13");
			 ej2=(TH3D*)input[0]->Get("rej23");


			 mb_alter=(TH3D*)input[0]->Get("rmb3_alter");
                         ej1_alter=(TH3D*)input[0]->Get("rej13_alter");
			 ej2_alter=(TH3D*)input[0]->Get("rej23_alter");

			 
			 for(Int_t j=1;j<=11;j++){
			   mb->GetZaxis()->SetRange(j,j);
			    ej1->GetZaxis()->SetRange(j,j);
			     ej2->GetZaxis()->SetRange(j,j);
			     
			   mb2d[j]=(TH2D*)mb->Project3D("yx");  
			   ej12d[j]=(TH2D*)ej1->Project3D("yx");
			   ej22d[j]=(TH2D*)ej2->Project3D("yx");
			   mb2d[j]->SetName(Form("mb2d[%d]",j));
			    ej12d[j]->SetName(Form("ej12d[%d]",j));
			    ej22d[j]->SetName(Form("ej22d[%d]",j));

			   mb_alter->GetZaxis()->SetRange(j,j);
			    ej1_alter->GetZaxis()->SetRange(j,j);
			     ej2_alter->GetZaxis()->SetRange(j,j);

			   mb2d_alter[j]=(TH2D*)mb_alter->Project3D("yx");  
			   ej12d_alter[j]=(TH2D*)ej1_alter->Project3D("yx");
			   ej22d_alter[j]=(TH2D*)ej2_alter->Project3D("yx");
			    mb2d_alter[j]->SetName(Form("mb2d_alter[%d]",j));
			     ej12d_alter[j]->SetName(Form("ej12d_alter[%d]",j));
			      ej22d_alter[j]->SetName(Form("ej22d_alter[%d]",j));
			 }



			 specmb=(TH1D*)input[0]->Get("h1_raw_mb");
                         specej1=(TH1D*)input[0]->Get("h1_raw_ej1");
			 specej2=(TH1D*)input[0]->Get("h1_raw_ej2");
		
	  
			 specej1R=(TH1D*)specej1->Rebin(12,"specej1R",xbin);
			  specej2R=(TH1D*)specej2->Rebin(12,"specej2R",xbin);
			   specmbR=(TH1D*)specmb->Rebin(12,"specmb1R",xbin);


			 specej1R->Divide(specmbR);
			 
			 specej2R->Divide(specmbR);

  	  canv2= new TCanvas(Form("canvas2"),Form("canvas2") ,1100,1100);
          canv2->SetTicks();
  	  canv2->cd();
  	  pad=new TPad("pad0","this is pad",0,0,1,1);
  	  pad->SetFillColor(0);
	 
  	  pad->SetMargin(0.15,0.12,0.25,0.9);
  	  pad->Draw();
  	  pad->SetTicks(1,1);
  	  pad->cd();
  	  //   gPad->SetLogy();
	     
     specej1R->GetYaxis()->SetTitleOffset(0.9);
     specej1R->GetXaxis()->SetTitleOffset(0.9);
  
   specej1R->GetXaxis()->SetLabelFont(42);
   specej1R->GetYaxis()->SetLabelFont(42);
   specej1R->GetXaxis()->SetLabelSize(0.04);
   specej1R->GetYaxis()->SetLabelSize(0.04); 
    
  specej1R->GetXaxis()->SetTitleFont(42);

  specej1R->GetYaxis()->SetRangeUser(0,2);
  specej1R->GetXaxis()->SetTitleSize(0.065);
  specej1R->GetYaxis()->SetTitleSize(0.065);

   
  	   specej1R->GetXaxis()->SetTitle("p_{T,jet}");
  	  specej1R->GetYaxis()->SetTitle("Ratio to mb");
  	  specej1R->SetLineColor(1);
	  specej1R->SetLineWidth(3);
	  specej2R->SetLineWidth(3);
  	  specej1R->Draw("");
          specej2R->SetLineColor(2); 
	  specej2R->Draw("same");
	  
  	   leg = new TLegend(0.6, 0.28, 0.7, 0.53);
     	  leg->SetBorderSize(0);
          leg->SetTextSize(0.02);
          leg->SetTextFont(42);
	  
     
         
      	   leg->AddEntry(specej1R," ej1", "PEL");
	    leg->AddEntry(specej2R," ej2", "PEL");
    	  
     	
	  
  	  

      	        leg->Draw();
      		leg->SetFillColor(0);
	  
 
   	  
   
    DrawLatex(0.2, 0.8, 1,"pp 13 TeV",0.03);
    DrawLatex(0.2, 0.75, 1,"Anti-k_{T}, R=0.4",0.03);
   	  canv2->SaveAs("RawSpec_downscaled.pdf");




	  for(Int_t k=1;k<11;k++){

	    canv[k]= new TCanvas(Form("canvas[%d]",k),Form("canvas[%d]",k) ,1100,1100);
          canv[k]->SetTicks();
  	  canv[k]->cd();
  	  pad=new TPad("pad0","this is pad",0,0,1,1);
  	  pad->SetFillColor(0);
	 
  	  pad->SetMargin(0.15,0.12,0.25,0.9);
  	  pad->Draw();
  	  pad->SetTicks(1,1);
  	  pad->cd();
  	
	     
     mb2d[k]->GetYaxis()->SetTitleOffset(0.9);
     mb2d[k]->GetXaxis()->SetTitleOffset(0.9);
  
   mb2d[k]->GetXaxis()->SetLabelFont(42);
   mb2d[k]->GetYaxis()->SetLabelFont(42);
   mb2d[k]->GetXaxis()->SetLabelSize(0.04);
   mb2d[k]->GetYaxis()->SetLabelSize(0.04); 
    
  mb2d[k]->GetXaxis()->SetTitleFont(42);

 
  mb2d[k]->GetXaxis()->SetTitleSize(0.065);
  mb2d[k]->GetYaxis()->SetTitleSize(0.065);
  if(k==1) mb2d[k]->SetTitle("mb, 20<p_{T,jet}<40 GeV");
  if(k==2) mb2d[k]->SetTitle("mb, 40<p_{T,jet}<60 GeV");
  if(k==3) mb2d[k]->SetTitle("mb, 60<p_{T,jet}<80 GeV");
  if(k==4) mb2d[k]->SetTitle("mb, 80<p_{T,jet}<100 GeV");
  if(k==5) mb2d[k]->SetTitle("mb, 100<p_{T,jet}<120 GeV");
  if(k==6) mb2d[k]->SetTitle("mb, 120<p_{T,jet}<140 GeV");
  if(k==7) mb2d[k]->SetTitle("mb, 140<p_{T,jet}<160 GeV");
  if(k==8) mb2d[k]->SetTitle("mb, 160<p_{T,jet}<180 GeV");
  if(k==9) mb2d[k]->SetTitle("mb, 180<p_{T,jet}<200 GeV");
  if(k==10) mb2d[k]->SetTitle("mb, 200<p_{T,jet}<220 GeV");
  if(k==11) mb2d[k]->SetTitle("mb, 220<p_{T,jet}<240 GeV");
   
  	   mb2d[k]->GetXaxis()->SetTitle("ln(R/#theta)");
  	  mb2d[k]->GetYaxis()->SetTitle("ln(k_{T})");
  	  mb2d[k]->GetYaxis()->SetRangeUser(0,4);
  	  mb2d[k]->Draw("text");
       
	  
  	   leg = new TLegend(0.6, 0.28, 0.7, 0.53);
     	  leg->SetBorderSize(0);
          leg->SetTextSize(0.02);
          leg->SetTextFont(42);
	  
     
         
      	   
    	  
     	
	  
      		leg->SetFillColor(0);
	  
 
   
		canv[k]->SaveAs(Form("RawStats_mb_%d.pdf",k));






      canv_alter[k]= new TCanvas(Form("canvas_alter[%d]",k),Form("canvas_alter[%d]",k) ,1100,1100);
          canv_alter[k]->SetTicks();
  	  canv_alter[k]->cd();
  	  pad=new TPad("pad0","this is pad",0,0,1,1);
  	  pad->SetFillColor(0);
	 
  	  pad->SetMargin(0.15,0.12,0.25,0.9);
  	  pad->Draw();
  	  pad->SetTicks(1,1);
  	  pad->cd();
  	
	     
     mb2d_alter[k]->GetYaxis()->SetTitleOffset(0.9);
     mb2d_alter[k]->GetXaxis()->SetTitleOffset(0.9);
  
   mb2d_alter[k]->GetXaxis()->SetLabelFont(42);
   mb2d_alter[k]->GetYaxis()->SetLabelFont(42);
   mb2d_alter[k]->GetXaxis()->SetLabelSize(0.04);
   mb2d_alter[k]->GetYaxis()->SetLabelSize(0.04); 
    
  mb2d_alter[k]->GetXaxis()->SetTitleFont(42);

 
  mb2d_alter[k]->GetXaxis()->SetTitleSize(0.065);
  mb2d_alter[k]->GetYaxis()->SetTitleSize(0.065);
  if(k==1) mb2d_alter[k]->SetTitle("mb, 20<p_{T,jet}<40 GeV");
  if(k==2) mb2d_alter[k]->SetTitle("mb, 40<p_{T,jet}<60 GeV");
  if(k==3) mb2d_alter[k]->SetTitle("mb, 60<p_{T,jet}<80 GeV");
  if(k==4) mb2d_alter[k]->SetTitle("mb, 80<p_{T,jet}<100 GeV");
  if(k==5) mb2d_alter[k]->SetTitle("mb, 100<p_{T,jet}<120 GeV");
  if(k==6) mb2d_alter[k]->SetTitle("mb, 120<p_{T,jet}<140 GeV");
  if(k==7) mb2d_alter[k]->SetTitle("mb, 140<p_{T,jet}<160 GeV");
  if(k==8) mb2d_alter[k]->SetTitle("mb, 160<p_{T,jet}<180 GeV");
  if(k==9) mb2d_alter[k]->SetTitle("mb, 180<p_{T,jet}<200 GeV");
  if(k==10) mb2d_alter[k]->SetTitle("mb, 200<p_{T,jet}<220 GeV");
  if(k==11) mb2d_alter[k]->SetTitle("mb, 220<p_{T,jet}<240 GeV");

   
  	   mb2d_alter[k]->GetXaxis()->SetTitle("ln(R/#theta)");
  	  mb2d_alter[k]->GetYaxis()->SetTitle("ln(1/z)");
  	  //mb2d_alter[k]->GetYaxis()->SetRangeUser(0,4);
  	  mb2d_alter[k]->Draw("text");
       
	  
  	   leg = new TLegend(0.6, 0.28, 0.7, 0.53);
     	  leg->SetBorderSize(0);
          leg->SetTextSize(0.02);
          leg->SetTextFont(42);
	  
     
         
      	   
    	  
     	
      		leg->SetFillColor(0);
	  
 
   	
   
		canv_alter[k]->SaveAs(Form("RawStats_mb_alter_%d.pdf",k));




		//////////////////////////////////////


			    canvej1[k]= new TCanvas(Form("canvasej1[%d]",k),Form("canvasej1[%d]",k) ,1100,1100);
          canvej1[k]->SetTicks();
  	  canvej1[k]->cd();
  	  pad=new TPad("pad0","this is pad",0,0,1,1);
  	  pad->SetFillColor(0);
	 
  	  pad->SetMargin(0.15,0.12,0.25,0.9);
  	  pad->Draw();
  	  pad->SetTicks(1,1);
  	  pad->cd();
  	
	     
     ej12d[k]->GetYaxis()->SetTitleOffset(0.9);
     ej12d[k]->GetXaxis()->SetTitleOffset(0.9);
  
   ej12d[k]->GetXaxis()->SetLabelFont(42);
   ej12d[k]->GetYaxis()->SetLabelFont(42);
   ej12d[k]->GetXaxis()->SetLabelSize(0.04);
   ej12d[k]->GetYaxis()->SetLabelSize(0.04); 
    
  ej12d[k]->GetXaxis()->SetTitleFont(42);

 
  ej12d[k]->GetXaxis()->SetTitleSize(0.065);
  ej12d[k]->GetYaxis()->SetTitleSize(0.065);
if(k==1) ej12d_alter[k]->SetTitle("ej1, 20<p_{T,jet}<40 GeV");
  if(k==2) ej12d[k]->SetTitle("ej1, 40<p_{T,jet}<60 GeV");
  if(k==3) ej12d[k]->SetTitle("ej1, 60<p_{T,jet}<80 GeV");
  if(k==4) ej12d[k]->SetTitle("ej1, 80<p_{T,jet}<100 GeV");
  if(k==5) ej12d[k]->SetTitle("ej1, 100<p_{T,jet}<120 GeV");
  if(k==6) ej12d[k]->SetTitle("ej1, 120<p_{T,jet}<140 GeV");
  if(k==7) ej12d[k]->SetTitle("ej1, 140<p_{T,jet}<160 GeV");
  if(k==8) ej12d[k]->SetTitle("ej1, 160<p_{T,jet}<180 GeV");
  if(k==9) ej12d[k]->SetTitle("ej1, 180<p_{T,jet}<200 GeV");
  if(k==10) ej12d[k]->SetTitle("ej1, 200<p_{T,jet}<220 GeV");
  if(k==11) ej12d[k]->SetTitle("ej1, 220<p_{T,jet}<240 GeV");
   
  	   ej12d[k]->GetXaxis()->SetTitle("ln(R/#theta)");
  	  ej12d[k]->GetYaxis()->SetTitle("ln(k_{T})");
  	  ej12d[k]->GetYaxis()->SetRangeUser(0,4);
  	  ej12d[k]->Draw("text");
       
	  
  	   leg = new TLegend(0.6, 0.28, 0.7, 0.53);
     	  leg->SetBorderSize(0);
          leg->SetTextSize(0.02);
          leg->SetTextFont(42);
	  
     
         
      	   
    	  
     	
	  
      		leg->SetFillColor(0);
	  
 
   
		canvej1[k]->SaveAs(Form("RawStats_ej1_%d.pdf",k));






      canvej1_alter[k]= new TCanvas(Form("canvasej1_alter[%d]",k),Form("canvasej1_alter[%d]",k) ,1100,1100);
          canvej1_alter[k]->SetTicks();
  	  canvej1_alter[k]->cd();
  	  pad=new TPad("pad0","this is pad",0,0,1,1);
  	  pad->SetFillColor(0);
	 
  	  pad->SetMargin(0.15,0.12,0.25,0.9);
  	  pad->Draw();
  	  pad->SetTicks(1,1);
  	  pad->cd();
  	
	     
     ej12d_alter[k]->GetYaxis()->SetTitleOffset(0.9);
     ej12d_alter[k]->GetXaxis()->SetTitleOffset(0.9);
  
   ej12d_alter[k]->GetXaxis()->SetLabelFont(42);
   ej12d_alter[k]->GetYaxis()->SetLabelFont(42);
   ej12d_alter[k]->GetXaxis()->SetLabelSize(0.04);
   ej12d_alter[k]->GetYaxis()->SetLabelSize(0.04); 
    
  ej12d_alter[k]->GetXaxis()->SetTitleFont(42);

 
  ej12d_alter[k]->GetXaxis()->SetTitleSize(0.065);
  ej12d_alter[k]->GetYaxis()->SetTitleSize(0.065);

    if(k==1) ej12d_alter[k]->SetTitle("ej1, 20<p_{T,jet}<40 GeV");
  if(k==2) ej12d_alter[k]->SetTitle("ej1, 40<p_{T,jet}<60 GeV");
  if(k==3) ej12d_alter[k]->SetTitle("ej1, 60<p_{T,jet}<80 GeV");
  if(k==4) ej12d_alter[k]->SetTitle("ej1, 80<p_{T,jet}<100 GeV");
  if(k==5) ej12d_alter[k]->SetTitle("ej1, 100<p_{T,jet}<120 GeV");
  if(k==6) ej12d_alter[k]->SetTitle("ej1, 120<p_{T,jet}<140 GeV");
  if(k==7) ej12d_alter[k]->SetTitle("ej1, 140<p_{T,jet}<160 GeV");
  if(k==8) ej12d_alter[k]->SetTitle("ej1, 160<p_{T,jet}<180 GeV");
  if(k==9) ej12d_alter[k]->SetTitle("ej1, 180<p_{T,jet}<200 GeV");
  if(k==10) ej12d_alter[k]->SetTitle("ej1, 200<p_{T,jet}<220 GeV");
  if(k==11) ej12d_alter[k]->SetTitle("ej1, 220<p_{T,jet}<240 GeV");

   
  	   ej12d_alter[k]->GetXaxis()->SetTitle("ln(R/#theta)");
  	  ej12d_alter[k]->GetYaxis()->SetTitle("ln(1/z)");
  	  //ej12d_alter[k]->GetYaxis()->SetRangeUser(0,4);
  	  ej12d_alter[k]->Draw("text");
       
	  
  	   leg = new TLegend(0.6, 0.28, 0.7, 0.53);
     	  leg->SetBorderSize(0);
          leg->SetTextSize(0.02);
          leg->SetTextFont(42);
	  
     
         
      	   
    	  
     	
      		leg->SetFillColor(0);
	  
 
   	
   
		canvej1_alter[k]->SaveAs(Form("RawStats_ej1_alter_%d.pdf",k));




		///////////////////////////////////////////




		
			    canvej2[k]= new TCanvas(Form("canvasej2[%d]",k),Form("canvasej2[%d]",k) ,1100,1100);
          canvej2[k]->SetTicks();
  	  canvej2[k]->cd();
  	  pad=new TPad("pad0","this is pad",0,0,1,1);
  	  pad->SetFillColor(0);
	 
  	  pad->SetMargin(0.15,0.12,0.25,0.9);
  	  pad->Draw();
  	  pad->SetTicks(1,1);
  	  pad->cd();
  	
	     
     ej22d[k]->GetYaxis()->SetTitleOffset(0.9);
     ej22d[k]->GetXaxis()->SetTitleOffset(0.9);
  
   ej22d[k]->GetXaxis()->SetLabelFont(42);
   ej22d[k]->GetYaxis()->SetLabelFont(42);
   ej22d[k]->GetXaxis()->SetLabelSize(0.04);
   ej22d[k]->GetYaxis()->SetLabelSize(0.04); 
    
  ej22d[k]->GetXaxis()->SetTitleFont(42);

 
  ej22d[k]->GetXaxis()->SetTitleSize(0.065);
  ej22d[k]->GetYaxis()->SetTitleSize(0.065);

    if(k==1) ej22d[k]->SetTitle("ej2, 20<p_{T,jet}<40 GeV");
  if(k==2) ej22d[k]->SetTitle("ej2, 40<p_{T,jet}<60 GeV");
  if(k==3) ej22d[k]->SetTitle("ej2, 60<p_{T,jet}<80 GeV");
  if(k==4) ej22d[k]->SetTitle("ej2, 80<p_{T,jet}<100 GeV");
  if(k==5) ej22d[k]->SetTitle("ej2, 100<p_{T,jet}<120 GeV");
  if(k==6) ej22d[k]->SetTitle("ej2, 120<p_{T,jet}<140 GeV");
  if(k==7) ej22d[k]->SetTitle("ej2, 140<p_{T,jet}<160 GeV");
  if(k==8) ej22d[k]->SetTitle("ej2, 160<p_{T,jet}<180 GeV");
  if(k==9) ej22d[k]->SetTitle("ej2, 180<p_{T,jet}<200 GeV");
  if(k==10) ej22d[k]->SetTitle("ej2, 200<p_{T,jet}<220 GeV");
  if(k==11) ej22d[k]->SetTitle("ej2, 220<p_{T,jet}<240 GeV");
   
  	   ej22d[k]->GetXaxis()->SetTitle("ln(R/#theta)");
  	  ej22d[k]->GetYaxis()->SetTitle("ln(k_{T})");
  	  ej22d[k]->GetYaxis()->SetRangeUser(0,4);
  	  ej22d[k]->Draw("text");
       
	  
  	   leg = new TLegend(0.6, 0.28, 0.7, 0.53);
     	  leg->SetBorderSize(0);
          leg->SetTextSize(0.02);
          leg->SetTextFont(42);
	  
     
         
      	   
    	  
     	
	  
      		leg->SetFillColor(0);
	  
 
   
		canvej2[k]->SaveAs(Form("RawStats_ej2_%d.pdf",k));






      canvej2_alter[k]= new TCanvas(Form("canvasej2_alter[%d]",k),Form("canvasej2_alter[%d]",k) ,1100,1100);
          canvej2_alter[k]->SetTicks();
  	  canvej2_alter[k]->cd();
  	  pad=new TPad("pad0","this is pad",0,0,1,1);
  	  pad->SetFillColor(0);
	 
  	  pad->SetMargin(0.15,0.12,0.25,0.9);
  	  pad->Draw();
  	  pad->SetTicks(1,1);
  	  pad->cd();
  	
	     
     ej22d_alter[k]->GetYaxis()->SetTitleOffset(0.9);
     ej22d_alter[k]->GetXaxis()->SetTitleOffset(0.9);
  
   ej22d_alter[k]->GetXaxis()->SetLabelFont(42);
   ej22d_alter[k]->GetYaxis()->SetLabelFont(42);
   ej22d_alter[k]->GetXaxis()->SetLabelSize(0.04);
   ej22d_alter[k]->GetYaxis()->SetLabelSize(0.04); 
    
  ej22d_alter[k]->GetXaxis()->SetTitleFont(42);

 
  ej22d_alter[k]->GetXaxis()->SetTitleSize(0.065);
  ej22d_alter[k]->GetYaxis()->SetTitleSize(0.065);

    if(k==1) ej22d_alter[k]->SetTitle("ej2, 20<p_{T,jet}<40 GeV");
  if(k==2) ej22d_alter[k]->SetTitle("ej2, 40<p_{T,jet}<60 GeV");
  if(k==3) ej22d_alter[k]->SetTitle("ej2, 60<p_{T,jet}<80 GeV");
  if(k==4) ej22d_alter[k]->SetTitle("ej2, 80<p_{T,jet}<100 GeV");
  if(k==5) ej22d_alter[k]->SetTitle("ej2, 100<p_{T,jet}<120 GeV");
  if(k==6) ej22d_alter[k]->SetTitle("ej2, 120<p_{T,jet}<140 GeV");
  if(k==7) ej22d_alter[k]->SetTitle("ej2, 140<p_{T,jet}<160 GeV");
  if(k==8) ej22d_alter[k]->SetTitle("ej2, 160<p_{T,jet}<180 GeV");
  if(k==9) ej22d_alter[k]->SetTitle("ej2, 180<p_{T,jet}<200 GeV");
  if(k==10) ej22d_alter[k]->SetTitle("ej2, 200<p_{T,jet}<220 GeV");
  if(k==11) ej22d_alter[k]->SetTitle("ej2, 220<p_{T,jet}<240 GeV");
   
  	   ej22d_alter[k]->GetXaxis()->SetTitle("ln(R/#theta)");
  	  ej22d_alter[k]->GetYaxis()->SetTitle("ln(1/z)");
  	  //ej22d_alter[k]->GetYaxis()->SetRangeUser(0,4);
  	  ej22d_alter[k]->Draw("text");
       
	  
  	   leg = new TLegend(0.6, 0.28, 0.7, 0.53);
     	  leg->SetBorderSize(0);
          leg->SetTextSize(0.02);
          leg->SetTextFont(42);
	  
     
         
      	   
    	  
     	
      		leg->SetFillColor(0);
	  
 
   	
   
		canvej2_alter[k]->SaveAs(Form("RawStats_ej2_alter_%d.pdf",k));




		
		

	  }

	  



	  
  
	  
}

