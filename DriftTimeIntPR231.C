//#include <iostream>
// usage:
//	TFile *f = TFile::Open("/media/jjvz/PR231/PR231/ROOT_DATA/sorted00256.root");
//	.x DriftTimeIntPR231.C
//
{
TH1F *hx1 = new TH1F("hx1","drifttime X1",14999,0.,14999.);
TH1F *hx2 = new TH1F("hx2","drifttime X2",14999,0.,14999.);
TH1F *hu1 = new TH1F("hu1","drifttime U1",14999,0.,14999.);
TH1F *hu2 = new TH1F("hu2","drifttime U2",14999,0.,14999.);
  hX1_DriftTimeGood->Draw();	//from this spectrum the LUT is calculated
  hx1 = hX1_DriftTimeGood;		//h1 used locally in this code
  hu1 = hU1_DriftTimeGood;		//h2 used locally in this code
  hx2 = hX2_DriftTimeGood;		//h1 used locally in this code
  hu2 = hU2_DriftTimeGood;		//h2 used locally in this code

  ofstream outx1;
  ofstream outu1;
  ofstream outx2;
  ofstream outu2;

  Float_t lutx1,lutu1,lutx2,lutu2;
  Int_t nbinsx1,nbinsu1,nbinsx2,nbinsu2;

  outx1.open("lut-newdaq-x1.dat");	//file saved to dir from which called

  nbinsx1 = hx1->GetNbinsX();
  cout << nbinsx1  << endl;
  // First set bincontent to 0 for those bins that should not form
  // part of the integration
  // Dec2010: X1:6400 8250   U1:6500 8200
  // this is off course made redundent if you take the spectra made clean
  // in the analysis
  // TH1F *h1 = new TH1F("h1","drifttime",14999,0.,14999.);
//-------now for X1 detector--------------
  for(Int_t j=0;j<6300;j++) {
    hx1->SetBinContent(j,0);
  }
  for(Int_t j=8050;j<nbinsx1;j++) {
    hx1->SetBinContent(j,0);
  }
  // Now do the integration
  for(Int_t i=0;i<nbinsx1;i++) {
    lutx1 = 1.0-(hx1->Integral(0,i)/hx1->Integral(0,nbinsx1));
  //printf("%g\n",1.0-(h1->Integral(0,i)/h1->Integral(0,nbins)));
    outx1 << lutx1  << endl;
  }

  outx1.close();
  
//-------now for U1 detector--------------
  outu1.open("lut-newdaq-u1.dat");
  nbinsu1 = hu1->GetNbinsX();
  cout << nbinsu1  << endl;
  for(Int_t j=0;j<6300;j++) {
    hu1->SetBinContent(j,0);
  }
  for(Int_t j=8050;j<nbinsu1;j++) {
    hu1->SetBinContent(j,0);
  }
  // Now do the integration
  for(Int_t i=0;i<nbinsu1;i++) {
    lutu1 = 1.0-(hu1->Integral(0,i)/hu1->Integral(0,nbinsu1));
  //printf("%g\n",1.0-(h1->Integral(0,i)/h1->Integral(0,nbins)));
    outu1 << lutu1  << endl;
  }
  outu1.close();

//-------now for X2 detector--------------
  outx2.open("lut-newdaq-x2.dat");
  nbinsx2 = hx2->GetNbinsX();
  cout << nbinsx2  << endl;
  for(Int_t j=0;j<6300;j++) {
    hx2->SetBinContent(j,0);
  }
  for(Int_t j=8050;j<nbinsx2;j++) {
    hx2->SetBinContent(j,0);
  }
  // Now do the integration
  for(Int_t i=0;i<nbinsx2;i++) {
    lutx2 = 1.0-(hx2->Integral(0,i)/hx2->Integral(0,nbinsx2));
  //printf("%g\n",1.0-(h1->Integral(0,i)/h1->Integral(0,nbins)));
    outx2 << lutx2  << endl;
  }

  outx2.close();
  
//-------now for U2 detector--------------
  outu2.open("lut-newdaq-u2.dat");
  nbinsu2 = hu2->GetNbinsX();
  cout << nbinsu2  << endl;
  for(Int_t j=0;j<6300;j++) {
    hu2->SetBinContent(j,0);
  }
  for(Int_t j=8050;j<nbinsu2;j++) {
    hu2->SetBinContent(j,0);
  }
  // Now do the integration
  for(Int_t i=0;i<nbinsu2;i++) {
    lutu2 = 1.0-(hu2->Integral(0,i)/hu2->Integral(0,nbinsu2));
  //printf("%g\n",1.0-(h1->Integral(0,i)/h1->Integral(0,nbins)));
    outu2 << lutu2  << endl;
  }
  outu2.close();

}


