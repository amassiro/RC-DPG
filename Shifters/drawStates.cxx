
#include <iostream>
#include <fstream>


void drawStates(std::string nameFile) {
  
  
  
  std::ifstream indata;
  
  std::cerr << "File " << nameFile << std::endl;
  
  indata.open(nameFile); // opens the file
  if(!indata) { // file couldn't be opened
    std::cerr << "Error: file " << nameFile << " could not be opened" << std::endl;
    return 1;
  }
  
  TH1F* histo = new TH1F ("histo", "", 44, 0, 44);
  
  int iter = 0;
  
  
  
  char buffer[2000];
  float num;
  std::string name;
  
  while(!indata.eof()) {
     indata.getline(&buffer[0],2000);
    std::stringstream line( buffer );    
    line >> name; 
    line >> name; 

    line >> num; 
    line >> num; 
    line >> num; 
    line >> num; 
    line >> num; 


    line >> num; 
    
    histo->Fill(iter, num);
    
    iter++;
    
    //     if (! iter%10)
    std::cout << " name = " << name << "  iter = " << iter << " num = " << num << std::endl;
    
  }
    

  indata.close();
  
//   TH1F
  histo->Draw("histo");
  histo->SetLineWidth(2);
  histo->SetLineColor(kTeal);
  histo->SetFillColor(kTeal);
  
  
  histo->GetXaxis()->SetTitle("index");
  histo->GetYaxis()->SetTitle("done/expected");
  histo->GetYaxis()->SetRangeUser(0, 1);
  
  
}

