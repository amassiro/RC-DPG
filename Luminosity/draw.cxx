{
  
  gROOT->Reset();
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1);
  gStyle->SetOptStat(111111);
  gStyle->SetOptFit(1111);
  
  #include "TROOT.h"
  #include "TStyle.h"
  #include "TColor.h"
  const Int_t __NRGBs = 5;
  const Int_t __NCont = 400;
//   const Int_t __NCont = 999;
  //   const Int_t __NCont = 76;
  Double_t __stops[__NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
  Double_t __red[__NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
  Double_t __green[__NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
  Double_t __blue[__NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
  
  //UInt_t Number = 5;
  //Double_t Red[5]   = { 0.00, 0.09, 0.18, 0.09, 0.00 };
  //Double_t Green[5] = { 0.01, 0.02, 0.39, 0.68, 0.97 };
  //Double_t Blue[5]  = { 0.17, 0.39, 0.62, 0.79, 0.97 };
  //Double_t Stops[5] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
  //UInt_t NColors = 999;
  //TColor::CreateGradientColorTable(Number,Stops,Red,Green,Blue,NColors);
  
  Int_t FI = TColor::CreateGradientColorTable(__NRGBs, __stops, __red, __green, __blue, __NCont);
  gStyle->SetNumberContours(__NCont);
  
  // TGaxis::SetMaxDigits(2);
  // gStyle->SetNdivisions(100);
  // gStyle->SetOptTitle(0);
  //  gStyle->cd(); 
  
//   Int_t FI = TColor::CreateGradientColorTable(3,Length,Red,Green,Blue,50);
//   for (int i=0; i<50; i++) colors[i] = FI+i;
  
  
  
  
  TChain* fChain = new TChain ("newtree");
  fChain->Add("newfile.root");
  
  TMultiGraph* mg = new TMultiGraph();
  TGraph* grs[3564];

  TMultiGraph* mg_8b4e = new TMultiGraph();
  TMultiGraph* mg_train = new TMultiGraph();

  std::vector<double> x;
  std::vector<double> y_8b4e;
  std::vector<double> y_train;
  
  
//   for (int iBX=0; iBX<100; iBX++) {
  for (int iBX=0; iBX<3564; iBX++) {
    TString toDraw = Form("bx_%d:time", iBX);
    fChain->Draw(toDraw, "1", "GOFF");
    
    grs[iBX] = new TGraph (fChain->GetSelectedRows(), fChain->GetV2(), fChain->GetV1());
    
    grs[iBX]->SetMarkerSize  (0.5);               
    grs[iBX]->SetMarkerStyle (21);              
    grs[iBX]->SetMarkerColor (FI+iBX);            
    grs[iBX]->SetLineWidth (1);                 
    grs[iBX]->SetLineColor (FI+iBX);              
    
    std::cout << " here " << std::endl;
    
//     if (iBX<100) mg->Add(grs[iBX]);
    if (iBX>147 && iBX<312) mg->Add(grs[iBX]);
    
    if (iBX>147 && iBX<228) mg_8b4e->Add(grs[iBX]);
    if (iBX>232 && iBX<312) mg_train->Add(grs[iBX]);
    
    std::cout << " fChain->GetSelectedRows() = " << fChain->GetSelectedRows() << std::endl;
    
    if (x.size() == 0) {
      for (itime=0; itime<fChain->GetSelectedRows(); itime++) {
        x.push_back(fChain->GetV1()[itime]);
      }       
    }
    
    
    //---- 8b4e
    if (iBX>147 && iBX<228) {
      if (y_8b4e.size()==0) {
        for (itime=0; itime<fChain->GetSelectedRows(); itime++) {     
          y_8b4e.push_back(fChain->GetV1()[itime]);
        }
      }
      else {
        for (itime=0; itime<fChain->GetSelectedRows(); itime++) {     
          y_8b4e.at(itime) =  y_8b4e.at(itime) + (fChain->GetV1()[itime]);
        }
      }
    }
      
   
   //---- train
   if (iBX>147 && iBX<228) {
     if (y_train.size()==0) {
       for (itime=0; itime<fChain->GetSelectedRows(); itime++) {     
         y_train.push_back(fChain->GetV1()[itime]);
       }
     }
     else {
       for (itime=0; itime<fChain->GetSelectedRows(); itime++) {     
         y_train.at(itime) =  y_train.at(itime) + (fChain->GetV1()[itime]);
       }
     }
   }
   
   
  }
  
  TCanvas* cc = new TCanvas ("cc", "all", 800, 600);
  mg->Draw("APL");
  mg->GetXaxis()->SetTitle("time");
  mg->GetYaxis()->SetTitle("Lumi Delivered /#mub");

  
  
  
  TCanvas* cc_8b4e = new TCanvas ("cc_8b4e", "8b4e", 800, 600);
  mg_8b4e->Draw("APL");
  mg_8b4e->GetXaxis()->SetTitle("time");
  mg_8b4e->GetYaxis()->SetTitle("Lumi Delivered /#mub");
  
  TGraph* gr_8b4e = new TGraph (x.size(), x.data(), y_8b4e.data());
  gr_8b4e->Draw();

  TCanvas* cc_train = new TCanvas ("cc_train", "train", 800, 600);
  mg_train->Draw("APL");
  mg_train->GetXaxis()->SetTitle("time");
  mg_train->GetYaxis()->SetTitle("Lumi Delivered /#mub");
    
  TGraph* gr_train = new TGraph (x.size(), x.data(), y_train.data());
  gr_train->Draw();
  
  
  
  //  fChain->Draw ("bx_234:time");
  
  //  TH2F* histo = new TH2F("histo", "", 3564, 0, 3564, 100, 0.0, 2.0);
  //  
  //  int nEvt = fChain->GetEntries();
  //  for (int iEvt=0; iEvt<nEvt; iEvt++) {
  //    std::cout << " iEvt = " << iEvt << std::endl;
  //    fChain->GetEntry(iEvt);
  //    for (int iBX=0; iBX<3564; iBX++) {
  //      TString CommandToROOTSize = Form("histo->Fill(%d, bx_%d);", iBX, iBX);
  // //      std::cout << " CommandToROOTSize = " << CommandToROOTSize.Data() << std::endl;
  //      gROOT->ProcessLine(CommandToROOTSize);
  //    }
  //  }
  //   
  //   histo->Draw();
  //   
}



