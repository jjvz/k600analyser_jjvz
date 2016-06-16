{
//  gROOT->Reset();
  gStyle->SetOptStat(0);
  
  Float_t limX_min=14.5;
  Float_t limX_max=15.5;

//  gROOT->ProcessLine(".L save_cut.C");
//  gROOT->ProcessLine("LoadCuts()");
//  TFile *f = TFile::Open("/media/jjvz/PR231/PR231/ROOT_DATA/sorted00256.root");
//  TFile *f = TFile::Open("/home/jjvz/codes/k600analyser/output.root");
//  gROOT->ProcessLine(".x histosPR231.C");

  c2 = new TCanvas("c2","Resolution for 6(X) wire events - jjvz",600,10,800,800);
  c2->SetFillColor(0);
  c2->SetGridy(0);

  TH1F *hX1res_0 = new TH1F("hX1res_0","X1 Resolution; hX1res0",200,-0.1,1.1);
  TH1F *hX1res_1 = new TH1F("hX1res_1","X1 Resolution; hX1res1",200,-8.,8.);
  TH2F *hX1Res2djj5 = new TH2F("hX1Res2djj5","iTL-jj style resolution plot for X1; hX1res1", 200,-3.,3.,200,-0.1,1.1);
//  TH2F *hX1Res2djj2 = new TH2F("hX1Res2djj2","iTL-jj style resolution plot for X1; hX1res2", 200,-3.,3.,200,-0.1,1.1);
//  TH1F *hX1res2 = new TH1F("hX1res2","X1 Resolution",200,-8.,8.);
//  TH2F *hX1res2diTL = new TH2F("hX1res2diTL","X1 2D Resolution - helions",200,-3.,3.,200,-0.1,1.1);
//  TH2F *hX1res2diTL = new TH2F("hX1res2diTL","X1 2D Resolution - helions",200,-0.1,1.1,200,-3.,3.);
//  TH1F *hU1res2 = new TH1F("hU1res2","U1 Resolution",320,-8.,8.);

  TPad* pad2 = new TPad("pad2","Spectra",0.01,0.01,0.99,0.99);
  pad2->SetFillColor(0);
  pad2->Draw();
  pad2->cd();
  pad2->Divide(2,2);

  pad2->cd(1);
  DATA->Draw("X1pos>>hX1pos","CUTpad1tof","");
//  DATA->Draw("Eexcit>>hEexcit","CUTpad1tof","");
//  hEexcit->GetXaxis()->SetRangeUser(limX_min,limX_max);
//  DATA->Draw("U2res5>>hU1res2","pad1>1000 && pad1<1680 && tof>3530 && tof<3618","");
//  DATA->Draw("U2res2>>hU1res2","pad1>1000 && pad1<1680 && tof>3530 && tof<3618","");

  pad2->cd(2);
//  DATA->Draw("X1res1>>hX1res2","pad1>1000 && pad1<1680 && tof>3530 && tof<3618","");
//  DATA->Draw("X1res1>>hX1res2","pad1>1000 && pad1<1680 && tof>3530 && tof<3618","");
//  DATA->Draw("X1res1>>hX1res2","CUTpad1tof","same");
  DATA->Draw("X1res1>>hX1res_1","CUTpad1tof","");

  pad2->cd(4);
  gStyle->SetPalette(1);
//  DATA->Draw("X1res0:X1res1>>hX1Res2djj","CUTpad1tof","col");
  DATA->Draw("X1res0:X1res1>>hX1Res2djj5","CUTpad1tof","col");
//  DATA->Draw("X2res0:X2res1>>hX1Res2djj","pad1>1000 && pad1<1680 && tof>3530 && tof<3618","col");
//  hX1Res2djj->SetStats(0);
//  hX1_Res2diTL->Draw("col");

  pad2->cd(3);
  gStyle->SetPalette(1);
//  DATA->Draw("Y1:Eexcit>>hY1vsEx","CUTpad1tof","col");
  DATA->Draw("Y1:X1pos>>hY1vsX1","CUTpad1tof","col");
//  hY1vsEx->GetXaxis()->SetRangeUser(limX_min,limX_max);
/*
  pad2->cd(5);
  gStyle->SetPalette(1);
  DATA->Draw("X1res0>>hX1res_0","CUTpad1tof","");

  pad2->cd(6);
  gStyle->SetPalette(1);
  DATA->Draw("X1res0:X1res1>>hX1Res2djj","CUTpad1tof","col");
*/
  double sigmaX1, sigmaU1;
  Char_t textX1[100],textU1[100];
  Char_t resX1[100],resU1[100];
  TPaveText* legendX1 = new TPaveText(0.11,0.6,0.4,0.75,"brNDC");
//  TPaveText* legendU1 = new TPaveText(0.11,0.6,0.4,0.8,"brNDC");
  legendX1->SetShadowColor(0);  
  legendX1->SetLineColor(0);  
//  legendX1->SetFillColor(0);  
//  legendU1->SetShadowColor(0);  
//  legendU1->SetLineColor(0);  
//  legendU1->SetFillColor(0);  

  pad2->cd(2);
  hX1res_1->Fit("gaus","","",-4.,4.);
  sigmaX1=hX1res_1->GetFunction("gaus")->GetParameter(2);
  gaus->SetLineColor(2);
  gaus->SetLineWidth(2);
  sprintf(textX1,"sigma = %f mm",sigmaX1);
  sprintf(resX1,"FWHM(x) = %f mm ",2.35*sigmaX1/(2*sqrt(6)));
  legendX1->SetTextFont(40);
  legendX1->AddText(textX1);
  legendX1->AddText("For 5 wires:");
  legendX1->AddText(resX1);
  legendX1->Draw();

/*
  pad2->cd(5);
  hX1res_0->Fit("gaus","","",-4.,4.);
  sigmaX1=hX1res_0->GetFunction("gaus")->GetParameter(2);
  gaus->SetLineColor(2);
  gaus->SetLineWidth(2);
  sprintf(textX1,"sigma = %f mm",sigmaX1);
  sprintf(resX1,"FWHM(x) = %f mm ",2.35*sigmaX1/(2*sqrt(6)));
  legendX1->SetTextFont(40);
  legendX1->AddText(textX1);
  legendX1->AddText("For 5 wires:");
  legendX1->AddText(resX1);
  legendX1->Draw();
*/
  pad2->cd(4);

}
