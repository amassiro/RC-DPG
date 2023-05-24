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
//   fChain->Add("newfile.root");
//   fChain->Add("fill_8817.root");
//   
//   int min_8b4e = 147;
//   int max_8b4e = 228;
//   
//   int min_train = 232;
//   int max_train = 313;
  
  
  
  fChain->Add("fill_8786.root");
  
  int min_8b4e = 108;
  int max_8b4e = 191;
  
  int min_train = 195;
  int max_train = 236;


  
  
  TMultiGraph* mg = new TMultiGraph();
  TMultiGraph* mg_8b4e = new TMultiGraph();
  TMultiGraph* mg_train = new TMultiGraph();
  
  TGraph* grs[3564];
  
//   std::cout << " here 0 " << std::endl;
  
  
  
  std::vector<double> vx;
  std::vector<double> vy_8b4e;
  std::vector<double> vy_8b4e_up_1sigma;
  std::vector<double> vy_8b4e_down_1sigma;
  std::vector<double> vy_train;
  std::vector<double> vy_train_up_1sigma;
  std::vector<double> vy_train_down_1sigma;

  std::vector< TH1F* > vy_map_8b4e;
  std::vector< TH1F* > vy_map_train;
  
  
  
//   std::cout << " here 1 " << std::endl;
  
//   for (int iBX=0; iBX<100; iBX++) {
  for (int iBX=0; iBX<3564; iBX++) {
    TString toDraw = Form("bx_%d:time", iBX);
    fChain->Draw(toDraw, "1", "GOFF");
    
    grs[iBX] = new TGraph (fChain->GetSelectedRows(), fChain->GetV2(), fChain->GetV1());
    
    grs[iBX]->SetMarkerSize  (0.3);               
    grs[iBX]->SetMarkerStyle (21);              
    grs[iBX]->SetMarkerColor (FI+iBX);            
    grs[iBX]->SetLineWidth (1);                 
    grs[iBX]->SetLineColor (FI+iBX);              
    
    
    //     if (iBX<100) mg->Add(grs[iBX]);
    if (iBX>min_8b4e && iBX<max_train) mg->Add(grs[iBX]);
    
    if (iBX>min_8b4e && iBX<max_8b4e)   mg_8b4e->Add(grs[iBX]);
    if (iBX>min_train && iBX<max_train) mg_train->Add(grs[iBX]);
    
    
//     std::cout << " fChain->GetSelectedRows() = " << fChain->GetSelectedRows() << std::endl;
    
    if (vx.size() == 0) {
//       std::cout << " grs[iBX]->GetN() = " << grs[iBX]->GetN() << std::endl;
      for (int itime=0; itime<grs[iBX]->GetN(); itime++) {
        vx.push_back(fChain->GetV2()[itime]);
      }       
    }
    
    
    //---- 8b4e
    if (iBX>147 && iBX<228) {
      if (vy_8b4e.size()==0) {
        for (int itime=0; itime<fChain->GetSelectedRows(); itime++) {     
          vy_8b4e.push_back(fChain->GetV1()[itime]);
          TString histoName = Form("histo_8b4e_%d", itime);
          TH1F* histo = new TH1F (histoName.Data(), "", 600, 0, 300);
          if (fChain->GetV1()[itime] > 2.5) histo->Fill(fChain->GetV1()[itime]);    //---- reasonable threshold ... 0.5, to remove empty bunches
          vy_map_8b4e.push_back(histo);      
        }
      }
      else {
        for (int itime=0; itime<fChain->GetSelectedRows(); itime++) {     
          vy_8b4e.at(itime) =  vy_8b4e.at(itime) + (fChain->GetV1()[itime]);
          if (fChain->GetV1()[itime] > 2.5) vy_map_8b4e.at(itime)->Fill(fChain->GetV1()[itime]); 
        }
      }
    }
      
    
    //---- train
    if (iBX>232 && iBX<313) {
     if (vy_train.size()==0) {
       for (int itime=0; itime<fChain->GetSelectedRows(); itime++) {     
         vy_train.push_back(fChain->GetV1()[itime]);      
         TString histoName = Form("histo_train_%d", itime);
         TH1F* histo = new TH1F (histoName.Data(), "", 600, 0, 300);
         if (fChain->GetV1()[itime] > 2.5) histo->Fill(fChain->GetV1()[itime]);
         vy_map_train.push_back(histo);      
       }
     }
     else {
       for (int itime=0; itime<fChain->GetSelectedRows(); itime++) {     
         vy_train.at(itime) =  vy_train.at(itime) + (fChain->GetV1()[itime]);
         if (fChain->GetV1()[itime] > 2.5) vy_map_train.at(itime)->Fill(fChain->GetV1()[itime]); 
       }
     }
     
    }
    
   
  }
    
  
  for (int itime=0; itime<vy_8b4e.size(); itime++) {    
    // 7 trains of 8 bunches
//     vy_8b4e.at(itime) /= (7*8);
    vy_8b4e.at(itime) = vy_map_8b4e.at(itime)->GetMean();
    //     
    vy_8b4e_up_1sigma.push_back(  vy_map_8b4e.at(itime)->GetMean() + vy_map_8b4e.at(itime)->GetRMS());
    vy_8b4e_down_1sigma.push_back(vy_map_8b4e.at(itime)->GetMean() - vy_map_8b4e.at(itime)->GetRMS());
//     
//     std::cout << " vy_map_8b4e.at(" << itime << ")->GetMean() + vy_map_8b4e.at(" << itime << ")->GetRMS() = " << vy_map_8b4e.at(itime)->GetMean() + vy_map_8b4e.at(itime)->GetRMS() << std::endl;
//     std::cout << " vy_map_8b4e.at(" << itime << ")->GetMean() - vy_map_8b4e.at(" << itime << ")->GetRMS() = " << vy_map_8b4e.at(itime)->GetMean() - vy_map_8b4e.at(itime)->GetRMS() << std::endl;
  }
  for (int itime=0; itime<vy_train.size(); itime++) {    
    // 2 trains of 35 bunches
//     vy_train.at(itime) /= (35*2);
    vy_train.at(itime) = vy_map_train.at(itime)->GetMean();
    //     std::cout << " vy_train.at(" << itime <<") = " << vy_train.at(itime) << " --> 8b4e = " << vy_8b4e.at(itime) << std::endl;
    vy_train_up_1sigma.push_back(  vy_map_train.at(itime)->GetMean() + vy_map_train.at(itime)->GetRMS());
    vy_train_down_1sigma.push_back(vy_map_train.at(itime)->GetMean() - vy_map_train.at(itime)->GetRMS());
  }
  
  TCanvas* cc = new TCanvas ("cc", "all", 800, 600);
  mg->Draw("APL");
  mg->GetXaxis()->SetTitle("time");
  mg->GetYaxis()->SetTitle("Lumi Delivered /#mub");

  
  
  
  TCanvas* cc_8b4e = new TCanvas ("cc_8b4e", "8b4e", 800, 600);
  mg_8b4e->Draw("APL");
  mg_8b4e->GetXaxis()->SetTitle("time");
  mg_8b4e->GetYaxis()->SetTitle("Lumi Delivered /#mub");
  
  TGraph* gr_8b4e = new TGraph (vx.size(), vx.data(), vy_8b4e.data());
  gr_8b4e->SetMarkerSize  (1.5);               
  gr_8b4e->SetMarkerStyle (22);              
  gr_8b4e->SetMarkerColor (kRed);            
  gr_8b4e->SetLineWidth (1);                 
  gr_8b4e->SetLineColor (kRed);              
  gr_8b4e->Draw("PL"); 
  
  TGraph* gr_8b4e_up = new TGraph (vx.size(), vx.data(), vy_8b4e_up_1sigma.data());
  gr_8b4e_up->SetMarkerSize  (0.2);               
  gr_8b4e_up->SetMarkerStyle (22);              
  gr_8b4e_up->SetMarkerColor (kRed);            
  gr_8b4e_up->SetLineWidth (2);                 
  gr_8b4e_up->SetLineColor (kRed);              
  gr_8b4e_up->Draw("L"); 
  
  TGraph* gr_8b4e_down = new TGraph (vx.size(), vx.data(), vy_8b4e_down_1sigma.data());
  gr_8b4e_down->SetMarkerSize  (0.2);               
  gr_8b4e_down->SetMarkerStyle (22);              
  gr_8b4e_down->SetMarkerColor (kRed);            
  gr_8b4e_down->SetLineWidth (2);                 
  gr_8b4e_down->SetLineColor (kRed);              
  gr_8b4e_down->Draw("L"); 
  
  TCanvas* cc_8b4e_ave = new TCanvas ("cc_8b4e_ave", "8b4e", 800, 600);
  gr_8b4e->Draw("APL"); 
  gr_8b4e_up->Draw("L"); 
  gr_8b4e_down->Draw("L"); 
  gr_8b4e->GetXaxis()->SetTitle("time");
  gr_8b4e->GetYaxis()->SetTitle("Lumi Delivered /#mub");
  
  
  TCanvas* cc_train = new TCanvas ("cc_train", "train", 800, 600);
  mg_train->Draw("APL");
  mg_train->GetXaxis()->SetTitle("time");
  mg_train->GetYaxis()->SetTitle("Lumi Delivered /#mub");
    
  TGraph* gr_train = new TGraph (vx.size(), vx.data(), vy_train.data());
  gr_train->SetMarkerSize  (1.5);               
  gr_train->SetMarkerStyle (22);              
  gr_train->SetMarkerColor (kBlue);            
  gr_train->SetLineWidth (1);                 
  gr_train->SetLineColor (kBlue);              
  gr_train->Draw("PL"); 

  TGraph* gr_train_up = new TGraph (vx.size(), vx.data(), vy_train_up_1sigma.data());
  gr_train_up->SetMarkerSize  (0.2);               
  gr_train_up->SetMarkerStyle (22);              
  gr_train_up->SetMarkerColor (kBlue);            
  gr_train_up->SetLineWidth (2);                 
  gr_train_up->SetLineColor (kBlue);              
  gr_train_up->Draw("L"); 
  
  TGraph* gr_train_down = new TGraph (vx.size(), vx.data(), vy_train_down_1sigma.data());
  gr_train_down->SetMarkerSize  (0.2);               
  gr_train_down->SetMarkerStyle (22);              
  gr_train_down->SetMarkerColor (kBlue);            
  gr_train_down->SetLineWidth (2);                 
  gr_train_down->SetLineColor (kBlue);              
  gr_train_down->Draw("L"); 
  
  
  
  TCanvas* cc_train_ave = new TCanvas ("cc_train_ave", "train", 800, 600);
  gr_train->Draw("APL"); 
  gr_train->GetXaxis()->SetTitle("time");
  gr_train->GetYaxis()->SetTitle("Lumi Delivered /#mub");
  gr_train_up->Draw("L"); 
  gr_train_down->Draw("L"); 
  
  
  
  TCanvas* cc_all_ave = new TCanvas ("cc_all_ave", "train", 800, 600);
  gr_8b4e->Draw("APL"); 
  gr_8b4e_up->Draw("L"); 
  gr_8b4e_down->Draw("L"); 
  gr_train->Draw("PL"); 
  gr_train_up->Draw("L"); 
  gr_train_down->Draw("L"); 
  
  
  TLegend* legend = new TLegend(0.65,0.70,0.90,0.90);
  legend->AddEntry(gr_8b4e,"8b4e with +/- 1 #sigma","PL");
  legend->AddEntry(gr_train,"train with +/- 1 #sigma","PL");
  legend->Draw();
  
  
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



