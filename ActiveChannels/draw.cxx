

TCanvas *draw() {
   
  TCanvas *c1 = new TCanvas("c1","",700,800);
  
  TH1F* h_active_channel = new TH1F ("h_active_channel", "", 10, 0, 10);
  
//   h_active_channel
  
//   Pixel   Strip   EB+EE   EB      EE      ES      HCAL    HB      HE      HF      HO      DT      RPC     CSC     GEM
//   Pixel   Strip           EB      EE      ES      HCAL                                    DT      RPC     CSC     GEM
  
  const Int_t ny = 10;
  const char   *detectors [ny] = {"Pixel", "Strip",   "EB",   "EE",    "ES", "HCAL", "DT", "RPC", "CSC",  "GEM"};
  
  // beginning 2023
  const double  efficiency[ny] = {    1.0,    1.0,   98.79,  97.97,   99.91,    1.0,  1.0,   1.0,   1.0,  90.0 };
  
  c1->SetGrid();
  c1->SetLeftMargin(0.15);
  c1->SetBottomMargin(0.15);

  h_active_channel->SetCanExtend(TH1::kAllAxes);
  h_active_channel->SetStats(0);
  for (Int_t i=0;i<ny;i++) {
//     h_active_channel->SetBinContent(i+1, efficiency[i]);
    h_active_channel->Fill(detectors[i], efficiency[i]);
  }
  
  
  h_active_channel->LabelsDeflate("X");
  h_active_channel->LabelsOption("v");
//   h_active_channel->Draw("hbar");
  h_active_channel->GetYaxis()->SetTitle("Fraction (%)");
  h_active_channel->SetFillColor(kGreen+2);
  h_active_channel->GetYaxis()->SetRangeUser(0, 110);
  h_active_channel->Draw("hbar1");
  
  

   TLegend *legend = new TLegend(0.65,0.90,0.96,0.95);
   legend->AddEntry(h_active_channel,"Beginning 2023","f");
//    legend->AddEntry(h2,"French only","f");
   legend->Draw();

   
   c1->cd();
   
   return c1;
}
