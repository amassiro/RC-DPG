
#include "tdrstyle.C"
#include "CMS_lumi.C"


// 
// PU xx
// Fill 9653
//      
// Pre-deadtime trigger rate     Dead time     TTS deadtime
// 
// 100 kHz                                  3.4%              0.1%
// 105 kHz                                  3.6%              0.2%
// 110 kHz                                  5.4%              2.0%  (all from Tracker FED 68)
// 120 kHz                                  ~15%             ~10% from Tracker FED 68
//      


//
// Fill https://cmsoms.cern.ch/cms/fills/report?cms_fill=9883
//    pu ~ 64 +/- 1
//
//


void draw2024 () {

  TCanvas* cc = new TCanvas ("cc","Deadtime",800,600);
  setTDRStyle();
  
  
  //   
  //   error = 0.1 - 0.2, reasonably, given the fluctuations
  //   
  
  float deadtime_64[9] = { 5.78,   5.86,    6.31,    6.23,    6.61,    6.69,     7.11 };
  float trigger_64[9]  = {112.5,  113.5,   114.5,   115.5,   116.5,   117.5,    118.5 };
  
  int numPoints = 7;  
  
  TGraph* gr_deadtime_64 = new TGraph ();
  for (int i=0; i<numPoints; i++) {
    deadtime_64[i] = deadtime_64[i] - 0.98; // from bunch mask
    gr_deadtime_64->SetPoint(i, trigger_64[i],  deadtime_64[i] );
  }
  
  gr_deadtime_64->SetLineColor(kRed);
  gr_deadtime_64->SetMarkerColor(kRed);
  gr_deadtime_64->SetMarkerStyle(8);
  gr_deadtime_64->SetMarkerSize(2);
  
  
  
  TMultiGraph* mgr = new TMultiGraph();
  mgr->Add (gr_deadtime_64           );
  
  
  cc->cd();
  mgr->Draw("APL");
  mgr->GetXaxis()->SetTitle("L1 rate [kHz]");
  mgr->GetYaxis()->SetTitle("Deadtime [%]");
  
  mgr->GetYaxis()->SetRangeUser(1,20);
  
  
  TLegend* legend = new TLegend(0.15, 0.60, 0.50, 0.80);
  legend->SetBorderSize(0);
  legend->AddEntry(gr_deadtime_64,            "pu = 64#pm1,   2340 colliding at P5","p");
  legend->Draw();
  
  
  //---- CMS labels
  //  CMS_lumi( cc, iPeriod, iPos );
  //  
  CMS_lumi( cc, 4, 0 );
  //   cc->Update();
  //   cc->RedrawAxis();
  //   cc->GetFrame()->Draw();
  
  
  TLine* l_3 = new TLine(trigger_64[0],3.0,trigger_64[numPoints_64-1],3.0);
  l_3->Draw();
  
  TLine* l_4 = new TLine(trigger_64[0],4.0,trigger_64[numPoints_64-1],4.0);
  l_4->Draw();
  
  TLine* l_5 = new TLine(trigger_64[0],5.0,trigger_64[numPoints_64-1],5.0);
  l_5->Draw();
  
  TLine* l_6 = new TLine(trigger_64[0],6.0,trigger_64[numPoints_64-1],6.0);
  l_6->Draw();
  
  
  
  
  
  
  
// //   
// //   error = 0.1 - 0.2, reasonably, given the fluctuations
// //   
//   
//   // https://cmsoms.cern.ch/cms/fills/report?cms_fill=9653
//   float deadtime_65[9] = {4.7, 5.8,   6.3};
//   float trigger_65[9]  = {97,  109,   114};
//   
//   int numPoints = 3;  
//   
//   TGraph* gr_deadtime_65 = new TGraph ();
//   for (int i=0; i<numPoints; i++) {
//     gr_deadtime_65->SetPoint(i, trigger_65[i],  deadtime_65[i] );
//   }
//   
//   gr_deadtime_65->SetLineColor(kRed);
//   gr_deadtime_65->SetMarkerColor(kRed);
//   gr_deadtime_65->SetMarkerStyle(8);
//   gr_deadtime_65->SetMarkerSize(2);
//   
//   
//   
//   // https://cmsoms.cern.ch/cms/fills/report?cms_fill=9651
//   float deadtime_62_140b[9] = {1.38, 2.9,   3.01,   3.2,    3.3};
//   float trigger_62_140b[9]  = {10.4,   98,   104.5,  114.3, 119};
//   
//   int numPoints_62_140b = 5;  
//   
//   TGraph* gr_deadtime_62_140b = new TGraph ();
//   for (int i=0; i<numPoints_62_140b; i++) {
//     gr_deadtime_62_140b->SetPoint(i, trigger_62_140b[i],  deadtime_62_140b[i] );
//   }
//   
//   gr_deadtime_62_140b->SetLineColor(kBlue);
//   gr_deadtime_62_140b->SetMarkerColor(kBlue);
//   gr_deadtime_62_140b->SetMarkerStyle(4);
//   gr_deadtime_62_140b->SetMarkerSize(2);
//   
//   
//   
//   
//   
//   
//   TMultiGraph* mgr = new TMultiGraph();
//   mgr->Add (gr_deadtime_65           );
//   mgr->Add (gr_deadtime_62_140b      );
//   
//   
//   cc->cd();
//   mgr->Draw("APL");
//   mgr->GetXaxis()->SetTitle("L1 rate [kHz]");
//   mgr->GetYaxis()->SetTitle("Deadtime [%]");
//   
//   mgr->GetYaxis()->SetRangeUser(1,20);
//     
//   
//   TLegend* legend = new TLegend(0.15, 0.60, 0.50, 0.80);
//   legend->SetBorderSize(0);
//   legend->AddEntry(gr_deadtime_65,            "pu = 65,   2198b","p");
//   legend->AddEntry(gr_deadtime_62_140b,       "pu = 61-63, 140b","p");
//   legend->Draw();
//   
//   
//   //---- CMS labels
//   //  CMS_lumi( cc, iPeriod, iPos );
//   //  
//   CMS_lumi( cc, 4, 0 );
// //   cc->Update();
// //   cc->RedrawAxis();
// //   cc->GetFrame()->Draw();
//   
//   
//   TLine* l_3 = new TLine(trigger_62_140b[0],3.0,trigger_62_140b[numPoints_62_140b-1],3.0);
//   l_3->Draw();
// 
//   TLine* l_4 = new TLine(trigger_62_140b[0],4.0,trigger_62_140b[numPoints_62_140b-1],4.0);
//   l_4->Draw();
// 
//   TLine* l_5 = new TLine(trigger_62_140b[0],5.0,trigger_62_140b[numPoints_62_140b-1],5.0);
//   l_5->Draw();
// 
//   TLine* l_6 = new TLine(trigger_62_140b[0],6.0,trigger_62_140b[numPoints_62_140b-1],6.0);
//   l_6->Draw();
  
   //---- save
  
  cc->SaveAs("deadtime.png");
  cc->SaveAs("deadtime.pdf");
  
  
  
}

