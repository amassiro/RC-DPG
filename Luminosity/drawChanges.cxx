{
  std::vector<TDatime> v_time;
  v_time.push_back(TDatime(2023, 4, 21, 0, 0, 0)); 
  v_time.push_back(TDatime(2023, 4, 22, 0, 0, 0)); 
  v_time.push_back(TDatime(2023, 4, 27, 0, 0, 0));
  v_time.push_back(TDatime(2023, 4, 29, 0, 0, 0));
  v_time.push_back(TDatime(2023, 5,  6, 0, 0, 0));
  v_time.push_back(TDatime(2023, 6,  4, 0, 0, 0));
  v_time.push_back(TDatime(2023, 6,  7, 0, 0, 0));
  v_time.push_back(TDatime(2023, 6,  8, 0, 0, 0));
  v_time.push_back(TDatime(2023, 6,  9, 0, 0, 0));
  v_time.push_back(TDatime(2023, 6, 10, 0, 0, 0));
  v_time.push_back(TDatime(2023, 6, 29, 0, 0, 0));
  
  
//   22/04/2023 - Fill 8642: -1.9%
//   27/04/2023 - Fill 8675: -2.8%
//   29/04/2023 - Fill 8686: -2.0%
//   06/05/2023 - Fill 8728: +1%
//   04/06/2023 - Fill 8873: +0.5%
//   07/06/2023 - Fill 8882: -1% (PLT bestlumi, HFET eventing bus issue)
//   08/06/2023 - Fill 8887: +1.2% (back to HFET)
//   09/06/2023 - Fill 8891: -1.1% (PLT bestlumi, Clock instability)
//   10/06/2023 - Fill 8894: +1.3% (back to HFET)
//   10/06/2023 - Fill     : +2.5% post VdM
  
  std::vector<double> changes = {1., -1.9, -2.8, -2.0, 1, 0.5, -1., 1.2, -1.1, 1.3, 2.5};
  
  for (size_t i = 0; i < changes.size(); i++) {
    if (i>0) changes.at(i) = (1.+changes.at(i)/100.) * changes.at(i-1);
    else changes.at(i) = 1.;
  }
  
  // Create a TGraph object
  TGraph* graph = new TGraph(v_time.size());
  
  for (size_t i = 0; i < v_time.size(); i++) {
    graph->SetPoint(i, v_time[i].Convert(), changes[i]);
  }
  
  // Set graph title and axis labels
  graph->SetTitle("Changes vs Time");
  graph->GetXaxis()->SetTitle("Time");
  graph->GetYaxis()->SetTitle("Response");
  
  // Create a canvas to display the graph
  TCanvas* canvas = new TCanvas("canvas", "Graph", 800, 600);
  canvas->SetGrid();
  
  // Draw the graph
  graph->Draw("APL");
  graph->SetMarkerSize(1);
  graph->SetMarkerStyle(20);
  graph->SetMarkerColor(kRed);
  graph->SetLineColor(kRed);
  
  
  graph->GetXaxis()->SetTimeDisplay(1);
//   graph->GetXaxis()->SetTimeFormat("%Y-%m-%d");
  graph->GetXaxis()->SetTimeFormat("%d/%m");
  
  TGaxis::SetMaxDigits(4);  // Increase the maximum number of digits for better spacing
  graph->GetXaxis()->SetLabelOffset(0.015);  // Adjust the label offset if needed
  graph->GetXaxis()->LabelsOption("v");  // Vertically align the labels

//   graph->GetXaxis()->SetTitleAngle(45);  // Rotate the title by 45 degrees
  

  
  // Update the canvas
  canvas->Update();

  
}

