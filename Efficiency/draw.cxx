
#include "tdrstyle.C"
#include "CMS_lumi.C"


void draw () {

  TCanvas* cc = new TCanvas ("cc","Efficiency",800,600);
  setTDRStyle();
  
  
//   TGraph *gr_efficiency = new TGraph("data_filtered.txt", "%lg-%lg-%lg %lg:%lg:%lg , %lg");
//   TGraph *gr_efficiency = new TGraph("data_filtered.txt", "%s %lg");
//   TGraph *gr_efficiency = new TGraph("data_filtered.txt", "%[^,],%lf");
//   TGraph *gr_efficiency = new TGraph("data_filtered.txt", "%10[^ ] %8[^,],%lf");
  
  
  std::ifstream file("data_filtered.txt");
  
  // Check if the file was opened successfully
  if (!file.is_open()) {
    std::cerr << "Error opening file" << std::endl;
    return 1;
  }
  
  std::string line;
  
  TGraph *gr_efficiency = new TGraph();
  
  // Read the file line by line
  while (std::getline(file, line)) {
    std::stringstream ss(line);
    std::string date_year;
    std::string date_month;
    std::string date_day;
    std::string date_hour;
    std::string date_min;
    std::string date_sec;
//     std::string date;
    std::string value;
    
    // Read the date (first part before the comma)
//     std::getline(ss, date, ',');
    
    std::getline(ss, date_year, '-');
    std::getline(ss, date_month, '-');
    std::getline(ss, date_day, ' ');
    
    std::getline(ss, date_hour, ':');
    std::getline(ss, date_min, ':');
    std::getline(ss, date_sec, ',');
    
    // Read the value (second part after the comma)
    std::getline(ss, value, ',');
    
    // Output the extracted data
//     std::cout << "Date: " << date << ", Value: " << value << std::endl;
//     TDatime da1(date);
    
    TDatime da1(std::stoi(date_year), std::stoi(date_month), std::stoi(date_day), std::stoi(date_hour), std::stoi(date_min), std::stoi(date_sec));
    
    
    gr_efficiency->SetPoint(gr_efficiency->GetN(), (double) da1.Convert(), std::stof(value) );
    
  }
  

  
  
  
//   TGraph *gr_efficiency = new TGraph("data_filtered.txt", "%19[^,],%lf");
    
  
  std::cout << " gr_efficiency = " << gr_efficiency->GetN() << std::endl;
  
  for (int i=0; i<gr_efficiency->GetN(); i++) {
    std::cout << " [" << i << "] = " << gr_efficiency->GetX()[i] << " :: "  << gr_efficiency->GetY()[i] << std::endl;
  }
  
  gr_efficiency->SetLineColor(kRed);
  gr_efficiency->SetMarkerColor(kRed);
  gr_efficiency->SetMarkerStyle(8);
  gr_efficiency->SetMarkerSize(1);
  
  
  TMultiGraph* mgr = new TMultiGraph();
  mgr->Add (gr_efficiency           );
    
  cc->cd();
  mgr->Draw("APL");
  mgr->GetYaxis()->SetTitle("Efficiency");
  mgr->GetXaxis()->SetTitle("Time");
  
//   mgr->GetYaxis()->SetRangeUser(0.5,1.0);
  
  mgr->GetXaxis()->SetTimeDisplay(1);
  mgr->GetXaxis()->SetTimeFormat("#splitline{%y-%m-%d}{}%F1970-01-01 00:00:00");
//   mgr->GetXaxis()->SetTimeFormat("#splitline{%y-%m-%d}{%H:%M:%S}");
  //   mgr->GetXaxis()->SetTimeFormat("#splitline{%y-%m-%d}{%H:%M:%S}%F1970-01-01 00:00:00");
  mgr->GetXaxis()->SetLabelOffset(0.025);
  
    
  TLegend* legend = new TLegend(0.15, 0.60, 0.50, 0.80);
  legend->SetBorderSize(0);
  legend->AddEntry(gr_efficiency,            "2024","p");
  legend->Draw();
  
  
  //---- CMS labels
  //  CMS_lumi( cc, iPeriod, iPos );
  //  
  CMS_lumi( cc, 4, 0 );
  //   cc->Update();
  //   cc->RedrawAxis();
  //   cc->GetFrame()->Draw();
  
  
  cc->SetGrid();
  
  
   //---- save
  
  cc->SaveAs("efficiency.png");
  cc->SaveAs("efficiency.pdf");
  
  
  
}

