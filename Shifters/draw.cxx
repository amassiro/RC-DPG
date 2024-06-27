
#include <iostream>
#include <fstream>


void draw(std::string nameFile) {
  
  
  
  std::ifstream indata;
  
  std::cerr << "File " << nameFile << std::endl;
  
  indata.open(nameFile); // opens the file
  if(!indata) { // file couldn't be opened
    std::cerr << "Error: file " << nameFile << " could not be opened" << std::endl;
    return 1;
  }
  
  TH1F* histo = new TH1F ("histo", "", 50, 0, 50);
  
  int iter = 0;
  
  
  
  char buffer[200];
  int num;
  
  
  while(!indata.eof()) {
    std::cout << "num =";
    indata.getline(&buffer[0],200);
 
    indata.getline(&buffer[0],200);
    std::stringstream line( buffer );    
    line >> num; 
    
    indata.getline(&buffer[0],200);
    
    histo->Fill(num);
    
    iter++;
    
    //     if (! iter%10)
    std::cout << " iter = " << iter << std::endl;
    
  }
    
    
    
//   while ( !indata.eof() ) { // keep reading until end-of-file
//     indata >> num;
//     indata >> num;
// //     std::cout << "Number read is " << num << std::endl;
//     histo->Fill(num);
//     indata >> num;
//     
//     iter++;
//     
// //     if (! iter%10)
//     std::cout << " iter = " << iter << std::endl;
//     
//   }
    
    
  indata.close();
  
//   TH1F
  histo->Draw();
  histo->SetLineWidth(2);
  histo->SetLineColor(kRed);
  histo->SetFillColor(kRed);
  
  
  histo->GetXaxis()->SetTitle("Number of shifts per person");
  
}

