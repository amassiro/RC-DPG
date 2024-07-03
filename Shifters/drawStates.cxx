
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
    std::cout << "num =";
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
    std::cout << " iter = " << iter << std::endl;
    
  }
    

  indata.close();
  
//   TH1F
  histo->Draw();
  histo->SetLineWidth(2);
  histo->SetLineColor(kRed);
  histo->SetFillColor(kRed);
  
  
  histo->GetXaxis()->SetTitle("index");
  histo->GetYaxis()->SetTitle("done/expected");
  
  
}

