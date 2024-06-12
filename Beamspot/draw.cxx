
#include "tdrstyle.C"
#include "CMS_lumi.C"




void draw () {
  
  TCanvas* cc = new TCanvas ("cc","Beamspot",800,600);
  setTDRStyle();
  
  //   
  //   error = 0.1 - 0.2, reasonably, given the fluctuations
  //   
  
  float Z[80];
  int counts[80]  = {0, 0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    4,    4,    11,   17,   12,   26,   40,   44,   64,   85,   98,   147,   164,   205,   216,   258,   314,   333,   407,   391,   432,   437,   525,   454,   488,   439,   437,   431,   407,   360,   345,   293,   259,   221,   179,   162,   112,   117,   87,   62,   53,   33,   33,   23,   14,   10,   2,    5,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0};
  
  for (int i=0; i<80; i++) {
    Z[i] = -20 + (20*2)/80. * i;
  }
  
  TH1F* histo = new TH1F ("histo", "histo", 80, -20, 20);
  
  for (int i=0; i<80; i++) {
    histo->SetBinContent (i+1,  counts[i]);
    histo->SetBinError (i+1,  sqrt(counts[i]));
    
  }
  
  histo->GetXaxis()->SetTitle("Z [cm]");
  histo->Draw();
  
  
  
  //---- CMS labels
  //  CMS_lumi( cc, iPeriod, iPos );
  //  
  CMS_lumi( cc, 4, 0 );
  //   cc->Update();
  //   cc->RedrawAxis();
  //   cc->GetFrame()->Draw();
  
  //---- save
  
  cc->SaveAs("beamspot.png");
  cc->SaveAs("beamspot.pdf");

  
  TFitResultPtr r  = histo->Fit("gaus", "S");
  TMatrixDSym cov = r->GetCovarianceMatrix();   //  to access the covariance matrix
  Double_t chi2   = r->Chi2();                  // to retrieve the fit chi2
  Double_t par1   = r->Parameter(1);            // retrieve the value for the parameter 1
  Double_t err1   = r->ParError(1);
  Double_t par2   = r->Parameter(2);            // retrieve the value for the parameter 2
  
  
  
  std::cout << " RMS    = " << histo->GetRMS() << std::endl;
  std::cout << " #sigma = " << par2 << std::endl;
  std::cout << " #mu = " << par1 << std::endl;
  
  
}

