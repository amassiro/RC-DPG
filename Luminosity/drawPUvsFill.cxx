{
  
  
  //   
  //   read from OMS
  //   data.csv
  //   
  
  
  std::vector<int> v_fill {
    7920, 7921, 7923, 7960, 7963, 7965, 7966, 7967, 7969, 7978, 8007, 8016, 8017, 8018, 8019, 8020, 8022, 8023, 8027, 8030, 8033, 8043, 8046, 8057, 8058, 8059, 8062, 8063, 8067, 8068, 8072, 8073, 8076, 8078, 8079, 8081, 8083, 8087, 8088, 8091, 8094, 8098, 8099, 8100, 8102, 8103, 8106, 8108, 8111, 8112, 8113, 8115, 8118, 8120, 8121, 8124, 8125, 8128, 8132, 8136, 8142, 8143, 8144, 8146, 8147, 8148, 8149, 8151, 8177, 8178, 8181, 8184, 8210, 8211, 8212, 8214, 8216, 8220, 8221, 8222, 8223, 8225, 8226, 8228, 8230, 8232, 8233, 8236, 8238, 8245, 8247, 8248, 8253, 8260, 8263, 8267, 8269, 8272, 8273, 8274, 8276, 8289, 8293, 8295, 8297, 8299, 8301, 8302, 8304, 8305, 8306, 8307, 8309, 8311, 8312, 8313, 8314, 8315, 8316, 8317, 8319, 8320, 8321, 8322, 8324, 8327, 8330, 8331, 8333, 8334, 8335, 8342, 8345, 8347, 8379, 8381, 8383, 8385, 8387, 8389, 8392, 8395, 8398, 8399, 8401, 8402, 8412, 8413, 8456, 8471, 8474, 8479, 8484, 8489, 8491, 8496, 8540, 8541, 8542, 8550, 8558, 8559, 8637, 8639, 8642, 8644, 8645, 8654, 8675, 8685, 8686, 8690, 8691, 8692, 8695, 8696, 8701, 8723, 8724, 8725, 8728, 8729, 8730, 8731, 8736, 8738, 8739, 8741, 8746, 8750, 8754, 8771, 8773, 8775, 8778, 8782, 8784, 8786, 8794, 8796, 8804, 8807, 8811, 8816, 8817, 8821, 8822, 8850, 8853, 8858, 8860, 8863, 8865, 8866, 8870, 8872, 8873, 8877, 8880, 8882, 8885, 8887, 8891, 8894, 8895, 8896, 8901, 8997, 8999, 9007, 9016, 9017, 9019, 9022, 9023, 9029, 9031, 9035, 9036, 9043, 9044, 9045, 9046, 9049, 9050, 9055, 9056, 9057, 9059, 9062, 9063, 9066, 9067, 9068, 9070, 9072, 9073
  };
  
  
  //   const char * DELIMS = "\t ,"; // Tab, space or comma.
  const char * DELIMS = ","; // comma.
  
  const int MAX_LINE_LENGTH = 1024;
  
  std::fstream fin("data.csv");
  
  // Prepare a C-string buffer to be used when reading lines.
  char buffer[MAX_LINE_LENGTH] = {};        
  
  // Prepare map.
  //   std::map< std::string, std::pair<int, TDatime> > map_fill_date;
  std::map< int, std::pair<int, TDatime> > map_fill_date;
  
  //   fill_number,duration,start_stable_beam,delivered_lumi,recorded_lumi,energy
  //   2023-07-16 22:50:23
  //
  // Read one line at a time.
  while ( fin.getline(buffer, MAX_LINE_LENGTH) ) {
    // Extract the three tokens:
    const char * row = strtok( buffer, DELIMS );
    const char * col = strtok( NULL,   DELIMS );
    const char * val = strtok( NULL,   DELIMS );
    
    //
    // 2023-07-16 22:50:23 --> (2023,07,16,22,50,23)
    //    
    
    //     std::cout << " val = " << val << std::endl;
    //     map_fill_date[std::string(row)] = std::pair<int, TDatime> ( std::atoi(col), TDatime(2023, 4, 21, 0, 0, 0) );
    //     map_fill_date[std::string(row)] = std::pair<int, TDatime> ( std::atoi(col), TDatime(val) );
    map_fill_date[std::atoi(row)] = std::pair<int, TDatime> ( std::atoi(col), TDatime(val) );
  }      
  
  // Cleanup
  fin.close();
  
  
  
  TChain* fChain = new TChain ("newtree");
  
  for (size_t i = 0; i < v_fill.size(); i++) {
    TString namefile = Form ("fill_%d.root", v_fill[i] );
    fChain->Add(namefile.Data());
  }
  
  
  
  //   for (size_t i = 0; i < v_fill.size(); i++) {
  //     TString toDraw = Form("avgpu");
  //     TString toCut  = Form("fill==%d", v_fill[i]);
  //     fChain->Draw(toDraw, "1", "GOFF");
  //   }  
  
  
  
  TString toDraw = Form("avgpu:datetime");
  fChain->Draw(toDraw, "1", "GOFF");
  
  
  
  // Create a TGraph object
  TGraph* graph_avgpu = new TGraph(v_fill.size());
  
  
  for (size_t i = 0; i < v_fill.size(); i++) {
    graph_avgpu->SetPoint(i, (map_fill_date[v_fill[i]].second).Convert(), 1.23456);
  }
  
  
  
  // Set graph_avgpu title and axis labels
  graph_avgpu->SetTitle("Avg PU vs Time");
  graph_avgpu->GetXaxis()->SetTitle("Time");
  graph_avgpu->GetYaxis()->SetTitle("avg pu");
  
  // Create a canvas to display the graph_avgpu
  TCanvas* canvas = new TCanvas("canvas", "Graph", 800, 600);
  canvas->SetGrid();
  
  // Draw the graph_avgpu
  graph_avgpu->Draw("APL");
  graph_avgpu->SetMarkerSize(1);
  graph_avgpu->SetMarkerStyle(20);
  graph_avgpu->SetMarkerColor(kRed);
  graph_avgpu->SetLineColor(kRed);
  
  
  graph_avgpu->GetXaxis()->SetTimeDisplay(1);
  //   graph_avgpu->GetXaxis()->SetTimeFormat("%Y-%m-%d");
  graph_avgpu->GetXaxis()->SetTimeFormat("%d/%m");
  
  TGaxis::SetMaxDigits(4);  // Increase the maximum number of digits for better spacing
  graph_avgpu->GetXaxis()->SetLabelOffset(0.015);  // Adjust the label offset if needed
  graph_avgpu->GetXaxis()->LabelsOption("v");  // Vertically align the labels
  
  //   graph_avgpu->GetXaxis()->SetTitleAngle(45);  // Rotate the title by 45 degrees
  
  
  
  // Update the canvas
  canvas->Update();
  
  
}



