
#include "tdrstyle.C"
#include "CMS_lumi.C"




void drawBSvsBetaStar () {
  
  TCanvas* cc = new TCanvas ("cc","Beamspot",800,600);
  setTDRStyle();
  
  int maxStep = 10;
   
  float sigma_Z[80]  = {3.97, 3.92, 3.87, 3.83, 3.75, 3.65, 3.69, 3.57, 3.54, 3.60}; // cm
  float sigma_X[80]  = {1.18, 1.17, 1.16, 1.13, 1.12, 1.13, 1.11, 1.09, 1.07, 1.08}; // cm/1000
  float sigma_Y[80]  = {1.15, 1.14, 1.12, 1.12, 1.12, 1.10, 1.11, 1.07, 1.01, 1.03}; // cm/1000
  float betaStar[80] = {60,   56,     52,   49,   45,  42,   39,   36,   33,   30 };
  
  
  for (int i=0; i<maxStep; i++) {
    sigma_X[i] *= (10); // mu m
    sigma_Y[i] *= (10); // mu m
  }
  
  //
  // data from: https://cmsoms.cern.ch/cms/fills/report?cms_fill=10226
  //
  
  TGraph* gr_sigma_X = new TGraph ();
  for (int i=0; i<maxStep; i++) {
    gr_sigma_X->SetPoint(i, betaStar[i],  sigma_X[i] );
  }
  
  gr_sigma_X->SetLineColor(kRed);
  gr_sigma_X->SetMarkerColor(kRed);
  gr_sigma_X->SetMarkerStyle(8);
  gr_sigma_X->SetMarkerSize(2);
  
  
  
  TGraph* gr_sigma_Y = new TGraph ();
  for (int i=0; i<maxStep; i++) {
    gr_sigma_Y->SetPoint(i, betaStar[i],  sigma_Y[i] );
  }
  
  gr_sigma_Y->SetLineColor(kBlue);
  gr_sigma_Y->SetMarkerColor(kBlue);
  gr_sigma_Y->SetMarkerStyle(22);
  gr_sigma_Y->SetMarkerSize(2);
  
  
  
  TGraph* gr_sigma_Z = new TGraph ();
  for (int i=0; i<maxStep; i++) {
    gr_sigma_Z->SetPoint(i, betaStar[i],  sigma_Z[i] );
  }
  
  gr_sigma_Z->SetLineColor(kGreen);
  gr_sigma_Z->SetMarkerColor(kGreen);
  gr_sigma_Z->SetMarkerStyle(23);
  gr_sigma_Z->SetMarkerSize(2);
  
  
  
  
  TMultiGraph* mgr_width = new TMultiGraph();
  mgr_width->Add (gr_sigma_X     );
  mgr_width->Add (gr_sigma_Y     );
  mgr_width->Add (gr_sigma_Z     );
  
  mgr_width->Draw("AP");
  mgr_width->GetXaxis()->SetTitle("#beta* [cm] ");
  mgr_width->GetYaxis()->SetTitle("width [#mum X/Y, cm Z]");
  
 
  TLegend* legend = new TLegend(0.45, 0.60, 0.65, 0.80);
  legend->SetBorderSize(0);
  
  legend->AddEntry(gr_sigma_X,  "#sigma_X"  ,"p"); 
  legend->AddEntry(gr_sigma_Y,  "#sigma_Y"  ,"p"); 
  legend->AddEntry(gr_sigma_Z,  "#sigma_Z"  ,"p"); 
  
  legend->Draw();
  
  
  
  
  CMS_lumi( cc, 4, 0 );
  
  cc->SetGrid();
  
  //---- save
  
  cc->SaveAs("beamspotVsBetaStar.png");
  cc->SaveAs("beamspotVsBetaStar.pdf");
  
    
  
}

