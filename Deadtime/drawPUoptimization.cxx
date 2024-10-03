
#include "tdrstyle.C"
#include "CMS_lumi.C"

//


void drawPUoptimization () {
  
  
  
  //   
  //  https://cmsoms.cern.ch/cms/fills/report?cms_fill=10197
  //   

  
  float deadtime[500] = {
  };
    
  float triggerL1preDeadtime[500]  = {
      
  };
    
  float LS[500]  = {  
  };
  
  float PU[500]  = {  
  };
  
  
  
  int numPoints = 500;
  
  TCanvas* cc_lumiRecorded_vs_pileup = new TCanvas ("cc_lumiRecorded_vs_pileup","cc_lumiRecorded_vs_pileup",800,600);
  setTDRStyle();
  
  TGraph* gr_lumiRecorded_vs_pileup = new TGraph ();
  for (int i=0; i<numPoints; i++) {
    gr_lumiRecorded_vs_pileup->SetPoint(i, PU[i],  PU[i] * (1-deadtime[i]/100) );
  }
  
  gr_lumiRecorded_vs_pileup->SetLineColor(kRed);
  gr_lumiRecorded_vs_pileup->SetMarkerColor(kRed);
  gr_lumiRecorded_vs_pileup->SetMarkerStyle(8);
  gr_lumiRecorded_vs_pileup->SetMarkerSize(2);
  
  cc_lumiRecorded_vs_pileup->cd();
  
  gr_lumiRecorded_vs_pileup->Draw("APL");
  gr_lumiRecorded_vs_pileup->GetXaxis()->SetTitle("pileup");
  gr_lumiRecorded_vs_pileup->GetYaxis()->SetTitle("luminosity recorded [a.u.]");
  
  
  
  TCanvas* cc_lumiRecorded_vs_L1ratePreDT = new TCanvas ("cc_lumiRecorded_vs_L1ratePreDT","cc_lumiRecorded_vs_L1ratePreDT",800,600);
  setTDRStyle();
  
  TGraph* gr_lumiRecorded_vs_L1ratePreDT = new TGraph ();
  for (int i=0; i<numPoints; i++) {
    gr_lumiRecorded_vs_L1ratePreDT->SetPoint(i, triggerL1preDeadtime[i]/1000.,  PU[i] * (1-deadtime[i]/100) );
  }
  
  gr_lumiRecorded_vs_L1ratePreDT->SetLineColor(kRed);
  gr_lumiRecorded_vs_L1ratePreDT->SetMarkerColor(kRed);
  gr_lumiRecorded_vs_L1ratePreDT->SetMarkerStyle(8);
  gr_lumiRecorded_vs_L1ratePreDT->SetMarkerSize(2);
  
  cc_lumiRecorded_vs_L1ratePreDT->cd();
  
  gr_lumiRecorded_vs_L1ratePreDT->Draw("APL");
  gr_lumiRecorded_vs_L1ratePreDT->GetXaxis()->SetTitle("L1 rate pre-deadtime [kHz]");
  gr_lumiRecorded_vs_L1ratePreDT->GetYaxis()->SetTitle("luminosity recorded [a.u.]");
  
  
  
  
  
  TCanvas* cc_lumiRecorded_vs_L1ratePreDT_multiPU = new TCanvas ("cc_lumiRecorded_vs_L1ratePreDT_multiPU","cc_lumiRecorded_vs_L1ratePreDT_multiPU",800,600);
  setTDRStyle();
  
  TGraph* gr_lumiRecorded_vs_L1ratePreDT_multiPU[10];
  
  for (int pu=0; pu<10; pu++) {
    gr_lumiRecorded_vs_L1ratePreDT_multiPU[pu] = new TGraph();
    
    gr_lumiRecorded_vs_L1ratePreDT_multiPU[pu]->SetLineColor(kRed+pu);
    gr_lumiRecorded_vs_L1ratePreDT_multiPU[pu]->SetMarkerColor(kRed+pu);
    gr_lumiRecorded_vs_L1ratePreDT_multiPU[pu]->SetMarkerStyle(8+pu);
    gr_lumiRecorded_vs_L1ratePreDT_multiPU[pu]->SetMarkerSize(2);
    
    for (int i=0; i<numPoints; i++) {
      if ( PU[i] > (59.5+pu) && PU[i] <= (59.5+1+pu)) {
        gr_lumiRecorded_vs_L1ratePreDT_multiPU[pu]->SetPoint(i, triggerL1preDeadtime[i]/1000.,  PU[i] * (1-deadtime[i]/100) );
      }
    } 
  }
  
  TLegend* legend = new TLegend(0.15, 0.60, 0.50, 0.80);
  legend->SetBorderSize(0);
  
  TMultiGraph* mgr = new TMultiGraph();
  for (int pu=0; pu<10; pu++) {
    mgr->Add (gr_lumiRecorded_vs_L1ratePreDT_multiPU[pu] ); 
    TString leg_value = Form ("pu = %d #pm 0.5, ",60+pu );
    legend->AddEntry(gr_lumiRecorded_vs_L1ratePreDT_multiPU[pu],  leg_value.Data()  ,"p"); 
  }
  
  cc_lumiRecorded_vs_L1ratePreDT_multiPU->cd();
  
  mgr->Draw("APL");
  mgr->GetXaxis()->SetTitle("L1 rate pre-deadtime [kHz]");
  mgr->GetYaxis()->SetTitle("luminosity recorded [a.u.]");
  
  //   mgr->GetYaxis()->SetRangeUser(1,20);
  
  legend->Draw();
  
  
  //---- CMS labels
  CMS_lumi( cc_lumiRecorded_vs_L1ratePreDT_multiPU, 4, 0 );
  cc_lumiRecorded_vs_L1ratePreDT_multiPU->SetGrid();
  
  
  //---- save
  
  cc_lumiRecorded_vs_L1ratePreDT_multiPU->SaveAs("deadtimeTotal.png");
  cc_lumiRecorded_vs_L1ratePreDT_multiPU->SaveAs("deadtimeTotal.pdf");
  
  
  
}

