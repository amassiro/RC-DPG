
#include "tdrstyle.C"
#include "CMS_lumi.C"

//


void drawDeadtime () {

  TCanvas* cc = new TCanvas ("cc","Deadtime",800,600);
  setTDRStyle();
  

  std::vector<float> v_deadtime_total;
  std::vector<float> v_deadtime_EBp;
  std::vector<float> v_deadtime_EBm;
  std::vector<float> v_L1;
  

  
  
  FILE *f = fopen("L1rate_Jul2024.csv", "r");
//  FILE *f = fopen("L1rate_preDT_Jul2024.csv", "r");
  // Create the time graph
  TGraph* gr_L1 = new TGraph();
  char line[80];
  float v;
  char dt[20];
  int i = 0;
  while (fgets(line, 80, f)) {
    sscanf(&line[20], "%f", &v);
    strncpy(dt, line, 18);
    dt[19] = '\0';
    gr_L1->SetPoint(i, TDatime(dt).Convert(), v);
    v_L1.push_back(v);
    i++;
  }
  fclose(f);
  
  
  //--------------------------------------------------------
  FILE *f_dt_EBp = fopen("deadtime_EBp_Jul2024.csv", "r");
  // Create the time graph
  TGraph* gr_dt_EBp = new TGraph();
  i = 0;
  while (fgets(line, 80, f_dt_EBp)) {
    sscanf(&line[20], "%f", &v);
    strncpy(dt, line, 18);
    dt[19] = '\0';
    
    
    v_deadtime_EBp.push_back(v);
    // deadtime x100
    v = v*100;
    
    gr_dt_EBp->SetPoint(i, TDatime(dt).Convert(), v);
    i++;
  }
  fclose(f_dt_EBp);
  
  
  //--------------------------------------------------------
  FILE *f_dt_EBm = fopen("deadtime_EBm_Jul2024.csv", "r");
  // Create the time graph
  TGraph* gr_dt_EBm = new TGraph();
  i = 0;
  while (fgets(line, 80, f_dt_EBm)) {
    sscanf(&line[20], "%f", &v);
    strncpy(dt, line, 18);
    dt[19] = '\0';
    
    
    v_deadtime_EBm.push_back(v);
    // deadtime x100
    v = v*100;
    
    gr_dt_EBm->SetPoint(i, TDatime(dt).Convert(), v);
    i++;
  }
  fclose(f_dt_EBm);
  
  
  
  
  //--------------------------------------------------------
  FILE *f_dt_tot = fopen("deadtime_total_Jul2024.csv", "r");
  // Create the time graph
  TGraph* gr_dt_tot = new TGraph();
  i = 0;
  while (fgets(line, 80, f_dt_tot)) {
    sscanf(&line[20], "%f", &v);
    strncpy(dt, line, 18);
    dt[19] = '\0';
    
    
    v_deadtime_total.push_back(v);
    v = v;
    
    gr_dt_tot->SetPoint(i, TDatime(dt).Convert(), v);
    i++;
  }
  fclose(f_dt_tot);
  
  
  
  
  
  
  gr_L1->SetMarkerColor(kBlue);
  gr_dt_EBp->SetMarkerColor(kRed);
  gr_dt_tot->SetMarkerColor(kOrange);
  
  gr_L1->SetMarkerStyle(20);
  gr_dt_EBp->SetMarkerStyle(22);
  gr_dt_tot->SetMarkerStyle(24);
  
  
  
  TMultiGraph* mgr = new TMultiGraph();
  mgr->Add (gr_L1     );
  mgr->Add (gr_dt_EBp     );
  mgr->Add (gr_dt_tot );
  
  cc->cd();
  mgr->Draw("AP");
  mgr->GetXaxis()->SetTitle("Time");
  mgr->GetYaxis()->SetTitle("Deadtime beam active EB+ [%] / deadtime tot / L1 rate [kHz]");
  
  mgr->GetYaxis()->SetRangeUser(0,120);
  
  mgr->GetXaxis()->SetTimeDisplay(1);
  mgr->GetXaxis()->SetTimeFormat("%a %d");
  
  
  
  
//   L1rate_Jul2024.csv
//   deadtime_Jul2024.csv
  
   
//   
  //---- CMS labels
  //  CMS_lumi( cc, iPeriod, iPos );
  //  
  CMS_lumi( cc, 4, 0 );
  //   cc->Update();
  //   cc->RedrawAxis();
  //   cc->GetFrame()->Draw();
  
  
  cc->SetGrid();
  
  
   //---- save
  
  cc->SaveAs("all.png");
  cc->SaveAs("all.pdf");
  
 
  
  
  
  TCanvas* cc_correlation = new TCanvas ("cc_correlation","Deadtime vs L1",800,600);
  setTDRStyle();
  
  
  TGraph* gr_dt_EBp_L1 = new TGraph();
  
  i=0;
  for (int ii=0; ii<v_deadtime_EBp.size(); ii++){
    if (v_L1.at(ii) > 50 && v_L1.at(ii) < 130 && v_deadtime_total.at(ii) < 100*0.999) {
      if (v_L1.at(ii) / (1. - v_deadtime_total.at(ii)/100.) < 130) {
        gr_dt_EBp_L1->SetPoint(i, v_L1.at(ii) / (1. - v_deadtime_total.at(ii)/100.) , v_deadtime_EBp.at(ii) );
        i++;
      }
    }
  }
  gr_dt_EBp_L1->SetMarkerColor(kBlue);  
  gr_dt_EBp_L1->SetMarkerStyle(20);
  
  //   gr_dt_EBp_L1->Draw ("AP");  
  //   gr_dt_EBp_L1->GetXaxis()->SetTitle("L1 rate pre deadtime [kHz] ");
  //   gr_dt_EBp_L1->GetYaxis()->SetTitle("Deadtime beam active [%]");
  
  
  TGraph* gr_dt_EBm_L1 = new TGraph();
  
  i=0;
  for (int ii=0; ii<v_deadtime_EBm.size(); ii++){
    if (v_L1.at(ii) > 50 && v_L1.at(ii) < 130 && v_deadtime_total.at(ii) < 100*0.999) {
      if (v_L1.at(ii) / (1. - v_deadtime_total.at(ii)/100.) < 130) {
        gr_dt_EBm_L1->SetPoint(i, v_L1.at(ii) / (1. - v_deadtime_total.at(ii)/100.) , v_deadtime_EBm.at(ii) );
        i++;
      }
    }
  }
  gr_dt_EBm_L1->SetMarkerColor(kBlue-3);  
  gr_dt_EBm_L1->SetMarkerStyle(21);
  
  //   gr_dt_EBm_L1->Draw ("AP");  
  //   gr_dt_EBm_L1->GetXaxis()->SetTitle("L1 rate pre deadtime [kHz] ");
  //   gr_dt_EBm_L1->GetYaxis()->SetTitle("Deadtime beam active [%]");
  
  
  
  
  TMultiGraph* mgr_L1 = new TMultiGraph();
  mgr_L1->Add (gr_dt_EBp_L1     );
  mgr_L1->Add (gr_dt_EBm_L1     );
  
  mgr_L1->Draw("AP");
  mgr_L1->GetXaxis()->SetTitle("L1 rate pre deadtime [kHz] ");
  mgr_L1->GetYaxis()->SetTitle("Deadtime [%]");
  
  

  CMS_lumi( cc_correlation, 4, 0 );
  
  cc_correlation->SetGrid();
  



  TCanvas* cc_correlation_L1 = new TCanvas ("cc_correlation_L1","Deadtime vs L1",800,600);
  setTDRStyle();
  
  
  TGraph* gr_dt_EBp_L1_tot = new TGraph();
  
  i=0;
  for (int ii=0; ii<v_deadtime_EBp.size(); ii++){
    if (v_L1.at(ii) > 50 && v_L1.at(ii) < 130 && v_deadtime_total.at(ii) < 100*0.999) {
      if (v_L1.at(ii) / (1. - v_deadtime_total.at(ii)/100.) < 130) {
        gr_dt_EBp_L1_tot->SetPoint(i, v_L1.at(ii), v_deadtime_EBp.at(ii) );
        i++;
      }
    }
  }
  gr_dt_EBp_L1_tot->SetMarkerColor(kRed);  
  gr_dt_EBp_L1_tot->SetMarkerStyle(20);
  
  //   gr_dt_EBp_L1_tot->Draw ("AP");   
  //   gr_dt_EBp_L1_tot->GetXaxis()->SetTitle("L1 rate [kHz] ");
  //   gr_dt_EBp_L1_tot->GetYaxis()->SetTitle("Deadtime beam active [%]");
  
  
  TGraph* gr_dt_EBm_L1_tot = new TGraph();
  
  i=0;
  for (int ii=0; ii<v_deadtime_EBm.size(); ii++){
    if (v_L1.at(ii) > 50 && v_L1.at(ii) < 130 && v_deadtime_total.at(ii) < 100*0.999) {
      if (v_L1.at(ii) / (1. - v_deadtime_total.at(ii)/100.) < 130) {
        gr_dt_EBm_L1_tot->SetPoint(i, v_L1.at(ii), v_deadtime_EBm.at(ii) );
        i++;
      }
    }
  }
  gr_dt_EBm_L1_tot->SetMarkerColor(kRed-3);  
  gr_dt_EBm_L1_tot->SetMarkerStyle(21);
  
  //   gr_dt_EBm_L1_tot->Draw ("AP");   
  //   gr_dt_EBm_L1_tot->GetXaxis()->SetTitle("L1 rate [kHz] ");
  //   gr_dt_EBm_L1_tot->GetYaxis()->SetTitle("Deadtime beam active [%]");
  
  
  
  TMultiGraph* mgr_L1_tot = new TMultiGraph();
  mgr_L1_tot->Add (gr_dt_EBp_L1_tot     );
  mgr_L1_tot->Add (gr_dt_EBm_L1_tot     );
  
  mgr_L1_tot->Draw("AP");
  mgr_L1_tot->GetXaxis()->SetTitle("L1 rate [kHz] ");
  mgr_L1_tot->GetYaxis()->SetTitle("Deadtime [%]");
  
  
  
  
  
  CMS_lumi( cc_correlation_L1, 4, 0 );
  
  cc_correlation_L1->SetGrid();
  
  
}

