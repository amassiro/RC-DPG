

TCanvas *draw() {
   
  TCanvas *c1 = new TCanvas("c1","",700,800);
  
  TH1F* h_active_channel = new TH1F ("h_active_channel", "", 10, 0, 10);
  
//   h_active_channel
  
//   Pixel   Strip   EB+EE   EB      EE      ES      HCAL    HB      HE      HF      HO      DT      RPC     CSC     GEM
//   Pixel   Strip           EB      EE      ES      HCAL                                    DT      RPC     CSC     GEM
  
  const Int_t ny = 11;
  const char   *detectors [ny] = {"BPIX", "FPIX",  "Strip",   "EB",   "EE",    "ES", "HCAL",   "DT",   "RPC", "CSC",  "GEM"};
  
  //
  // beginning 2023
  // https://indico.cern.ch/event/1237819/timetable/?view=standard
  // https://indico.cern.ch/event/1237819/contributions/5206529/attachments/2603238/4495495/Pixel_RCworkshop_2Mar23_Negro.pdf --> pix
  // https://indico.cern.ch/event/1237819/contributions/5206532/attachments/2603270/4495556/tracker-run-coordination-2023.pdf --> strips
  // https://indico.cern.ch/event/1237819/contributions/5206468/attachments/2603139/4511784/RC_workshop_20230302%20(1).pdf --> ECAL
  // https://indico.cern.ch/event/1237819/contributions/5206542/attachments/2603359/4496049/DTOperationSummary_RunCoordinationWorkshop1stto3rdMarch2023.pdf --> dt
  // https://indico.cern.ch/event/1237819/contributions/5206465/attachments/2603497/4495991/RPC%20Operation%20report.pdf --> RPC (@ 2022)
  // https://indico.cern.ch/event/1237819/contributions/5206540/attachments/2603295/4496235/230302_CSC%20Operations_RCworkshop.pdf --> CSC 
  // https://indico.cern.ch/event/1237819/contributions/5206539/attachments/2603311/4495716/20230302_GEMOperations_V5.pdf --> GEM
  
  
  
  
//                               {"BPIX", "FPIX", "Strip",    "EB",   "EE",    "ES",   "HCAL",    "DT",   "RPC", "CSC",  "GEM"};
  const double  efficiency[ny] = { 98.4 ,   98.8,    96,   98.79,  97.97,   99.91,      99   ,   99.75,   87.45,   99,  90.0 };
  
//   - EB: 98.79% active
//   - EE: 97.97% active
//   - ES: 99.91% active
  
//   - RPC  87.45% (77.85% barrel, 99.24% endcap).
  
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
  h_active_channel->GetYaxis()->SetTitle("Fraction active channels (%)");
  h_active_channel->SetFillColor(kGreen+2);
//   h_active_channel->GetYaxis()->SetRangeUser(90, 110);
  h_active_channel->GetYaxis()->SetRangeUser(80, 102);
  h_active_channel->Draw("hbar1");
  
  

   TLegend *legend = new TLegend(0.65,0.82,0.90,0.88);
   legend->AddEntry(h_active_channel,"Beginning 2023","f");
//    legend->Draw();

   
   TLatex* tex = new TLatex(0.15,0.91,"CMS Preliminary");
   tex->SetNDC();
   tex->SetTextSize(0.0455);
   tex->SetLineWidth(2);
   tex->Draw();
   
   
   TLatex* tex2 = new TLatex(0.90,0.91,"2023");
   tex2->SetNDC();
   tex2->SetTextAlign(31);
   tex2->SetTextFont(42);
   tex2->SetTextSize(0.042);
   tex2->SetLineWidth(2);
   tex2->Draw();
   
   c1->cd();
   
   return c1;
}
