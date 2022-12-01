
#include "tdrstyle.C"
#include "CMS_lumi.C"


// 
// PU 60
// 
//      
//      with CTPPS OUT
//      
//      100 kHZ    3.2%
//      105 kHz    3.8%
//      106 kHz    3.8-3.9%
//      109 kHz    4.1-4.2%   
//      110 kHz    4.2 %
//      111 kHz    4.3-4.5%
//      112 kHz    4.6-4.7%
//      115 kHz    5.1-5.2%
//      118 kHz    6.2-6.3%
//      
//      
//      with CTPPS IN
//      
//      102 kHz    3.8-4%      PPS_TOT: 0.7%
//      106 kHz    4.1-4.2      PPS_TOT: 1.1%
//      110 kHz    5.6-5.7%   PPS_TOT: 2.7%
//      114 kHz    7.4-7.6%    PPS_TOT: 4.4%
//      118 kHz    9.6-9.8%    PPS_TOT: 6.5%
//      
//      


// 
// PU 55
// 

//      
//      Deadtime (without CTPPS and CTPPS_TOT):
//      
//      99 kHz             3.5%
//      102 kHz           3.8%
//      105 kHz           3.8-4%
//      114 kHz           5.2%
//      116 kHz           5.5 - 6.5% 
//      120 kHz           6-8% 
//      
//      Deadtime (with all subsystems):
//      
//      102 kHz        4%    (CTPPS_TOT 0.5-0.6%)
//      105 kHz        5%      (CTPPS_TOT 1%)
//      108 kHz        5.3-5.5%  (CTPPS_TOT 1.6-1.7%)
//      109 kHz        5.6-6%   (CTPPS_TOT 2.1%)           
//      111 kHz         6.2-6.5%    (CTPPS_TOT 2.6%)
//      113 kHz         7%     (CTPPS_TOT  3.7%
//      117 kHz         9-10%     (CTPPS_TOT 5.5%)
//      120 kHz        11-13%     (CTPPS_TOT 7.5%)
//      
//      


void draw () {

  TCanvas* cc = new TCanvas ("cc","Deadtime",800,600);
  setTDRStyle();
  
//   
//   error = 0.1 - 0.2, reasonably, given the fluctuations
//   
  
  float deadtime_60[9] = {3.2, 3.8, 3.85, 4.15, 4.2, 4.4, 4.65, 5.15, 6.25};
  float trigger_60[9]  = {100, 105, 106, 109, 110, 111, 112, 115, 118};
  
  
  float deadtime_60_with_CTPPS[5] = {3.9, 4.15, 5.65, 7.5, 9.7};
  float trigger_60_with_CTPPS[5]  = {102, 106, 110, 114, 118};
  
  
  
  float deadtime_55[6] = {3.5, 3.8, 3.9, 5.2, 6.0, 7.0};
  float trigger_55[6]  = {99, 102, 105, 114, 116, 120};
  
  
  float deadtime_55_with_CTPPS[8] = {4.0, 5.0, 5.4, 5.8, 6.35, 7.0, 9.5, 12.0};
  float trigger_55_with_CTPPS[8]  = {102, 105, 108, 109, 111, 113, 117, 120};
  
  
  
  
  TGraph* gr_deadtime_60 = new TGraph ();
  for (int i=0; i<9; i++) {
    gr_deadtime_60->SetPoint(i, trigger_60[i],  deadtime_60[i] );
  }
  
  gr_deadtime_60->SetLineColor(kRed);
  gr_deadtime_60->SetMarkerColor(kRed);
  gr_deadtime_60->SetMarkerStyle(8);
  gr_deadtime_60->SetMarkerSize(2);
  
  
  
  
  TGraph* gr_deadtime_60_with_CTPPS = new TGraph ();
  for (int i=0; i<5; i++) {
    gr_deadtime_60_with_CTPPS->SetPoint(i, trigger_60_with_CTPPS[i],  deadtime_60_with_CTPPS[i] );
  }
  
  gr_deadtime_60_with_CTPPS->SetLineColor(kRed);
  gr_deadtime_60_with_CTPPS->SetMarkerColor(kRed);
  gr_deadtime_60_with_CTPPS->SetMarkerStyle(4);
  gr_deadtime_60_with_CTPPS->SetMarkerSize(2);
  

  
  
  TGraph* gr_deadtime_55 = new TGraph ();
  for (int i=0; i<6; i++) {
    gr_deadtime_55->SetPoint(i, trigger_55[i],  deadtime_55[i] );
  }
  
  gr_deadtime_55->SetLineColor(kBlue);
  gr_deadtime_55->SetMarkerColor(kBlue);
  gr_deadtime_55->SetMarkerStyle(22);
  gr_deadtime_55->SetMarkerSize(2);
  
  
  
  
  TGraph* gr_deadtime_55_with_CTPPS = new TGraph ();
  for (int i=0; i<8; i++) {
    gr_deadtime_55_with_CTPPS->SetPoint(i, trigger_55_with_CTPPS[i],  deadtime_55_with_CTPPS[i] );
  }
  
  gr_deadtime_55_with_CTPPS->SetLineColor(kBlue);
  gr_deadtime_55_with_CTPPS->SetMarkerColor(kBlue);
  gr_deadtime_55_with_CTPPS->SetMarkerStyle(26);
  gr_deadtime_55_with_CTPPS->SetMarkerSize(2);
  
  
  TMultiGraph* mgr = new TMultiGraph();
  mgr->Add (gr_deadtime_60           );
  mgr->Add (gr_deadtime_60_with_CTPPS);
  mgr->Add (gr_deadtime_55           );
  mgr->Add (gr_deadtime_55_with_CTPPS);
  
  
  cc->cd();
  mgr->Draw("APL");
  mgr->GetXaxis()->SetTitle("L1 rate [kHz]");
  mgr->GetYaxis()->SetTitle("Deadtime [%]");
  
  mgr->GetYaxis()->SetRangeUser(3,13);
    
  
  TLegend* legend = new TLegend(0.15, 0.60, 0.50, 0.80);
  legend->SetBorderSize(0);
  legend->AddEntry(gr_deadtime_60,            "pu = 60, w/o CTPPS","p");
  legend->AddEntry(gr_deadtime_60_with_CTPPS, "pu = 60, w/ CTPPS" ,"p");
  legend->AddEntry(gr_deadtime_55,            "pu = 55, w/o CTPPS","p");
  legend->AddEntry(gr_deadtime_55_with_CTPPS, "pu = 55, w/ CTPPS" ,"p");
  legend->Draw();
  
  
  //---- CMS labels
  //  CMS_lumi( cc, iPeriod, iPos );
  //  
  CMS_lumi( cc, 4, 0 );
//   cc->Update();
//   cc->RedrawAxis();
//   cc->GetFrame()->Draw();
  
   //---- save
  
  cc->SaveAs("deadtime.png");
  cc->SaveAs("deadtime.pdf");
  
  
  
}

