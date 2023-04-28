
#include "tdrstyle.C"
#include "CMS_lumi.C"


// 
// PU 68
// 
//      
// Pre-deadtime trigger rate     Dead time     TTS deadtime
// 
// 100 kHz                                  3.4%              0.1%
// 105 kHz                                  3.6%              0.2%
// 110 kHz                                  5.4%              2.0%  (all from Tracker FED 68)
// 120 kHz                                  ~15%             ~10% from Tracker FED 68
//      


void draw2023 () {

  TCanvas* cc = new TCanvas ("cc","Deadtime",800,600);
  setTDRStyle();
  
//   
//   error = 0.1 - 0.2, reasonably, given the fluctuations
//   
  
  float deadtime_68[9] = {3.4, 3.6, 5.4, 15};
  float trigger_68[9]  = {100, 105, 110, 120};
  
  
  
  
  TGraph* gr_deadtime_68 = new TGraph ();
  for (int i=0; i<4; i++) {
    gr_deadtime_68->SetPoint(i, trigger_68[i],  deadtime_68[i] );
  }
  
  gr_deadtime_68->SetLineColor(kRed);
  gr_deadtime_68->SetMarkerColor(kRed);
  gr_deadtime_68->SetMarkerStyle(8);
  gr_deadtime_68->SetMarkerSize(2);
  
  
   
  
  TMultiGraph* mgr = new TMultiGraph();
  mgr->Add (gr_deadtime_68           );
  
  
  cc->cd();
  mgr->Draw("APL");
  mgr->GetXaxis()->SetTitle("L1 rate [kHz]");
  mgr->GetYaxis()->SetTitle("Deadtime [%]");
  
  mgr->GetYaxis()->SetRangeUser(1,20);
    
  
  TLegend* legend = new TLegend(0.15, 0.60, 0.50, 0.80);
  legend->SetBorderSize(0);
  legend->AddEntry(gr_deadtime_68,            "pu = 68, 400b","p");
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

