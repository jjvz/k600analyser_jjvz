{
//  gROOT->Reset();
  gStyle->SetOptStat(0);
  
  Float_t limX_min=14.5;
  Float_t limX_max=15.5;

  gROOT->ProcessLine(".L save_cut.C");
  gROOT->ProcessLine("LoadCuts()");
//  TFile *f = TFile::Open("/media/jjvz/PR231/PR231/ROOT_DATA/sorted00256.root");
  TFile *f = TFile::Open("/home/jjvz/codes/k600analyser/output.root");
  gROOT->ProcessLine(".x histosPR231.C");

  c2 = new TCanvas("c2","Resolution for 6(X) wire events - jjvz",600,10,800,800);
  c2->SetFillColor(0);
  c2->SetGridy(0);

  TH1F *hX2res_0 = new TH1F("hX2res_0","X2 Resolution; hX2res0",200,-0.1,1.1);
  TH1F *hX2res_1 = new TH1F("hX2res_1","X2 Resolution; hX2res1",200,-8.,8.);
  TH2F *hX2Res2djj5 = new TH2F("hX2Res2djj5","iTL-jj style resolution plot for X2; hX2res1", 200,-3.,3.,200,-0.1,1.1);
//  TH2F *hX2Res2djj2 = new TH2F("hX2Res2djj2","iTL-jj style resolution plot for X2; hX2res2", 200,-3.,3.,200,-0.1,1.1);
//  TH1F *hX2res2 = new TH1F("hX2res2","X2 Resolution",200,-8.,8.);
//  TH2F *hX2res2diTL = new TH2F("hX2res2diTL","X2 2D Resolution - helions",200,-3.,3.,200,-0.1,1.1);
//  TH2F *hX2res2diTL = new TH2F("hX2res2diTL","X2 2D Resolution - helions",200,-0.1,1.1,200,-3.,3.);
//  TH1F *hX2res2 = new TH1F("hX2res2","X2 Resolution",320,-8.,8.);

  TPad* pad2 = new TPad("pad2","Spectra",0.01,0.01,0.99,0.99);
  pad2->SetFillColor(0);
  pad2->Draw();
  pad2->cd();
  pad2->Divide(2,2);

  pad2->cd(1);
  DATA->Draw("X2pos>>hX2pos","CUTpad1tof","");
//  DATA->Draw("Eexcit>>hEexcit","CUTpad1tof","");
//  hEexcit->GetXaxis()->SetRangeUser(limX_min,limX_max);
//  DATA->Draw("U2res5>>hX2res2","pad1>1000 && pad1<1680 && tof>3530 && tof<3618","");
//  DATA->Draw("U2res2>>hX2res2","pad1>1000 && pad1<1680 && tof>3530 && tof<3618","");

  pad2->cd(2);
//  DATA->Draw("X2res1>>hX2res2","pad1>1000 && pad1<1680 && tof>3530 && tof<3618","");
//  DATA->Draw("X2res1>>hX2res2","pad1>1000 && pad1<1680 && tof>3530 && tof<3618","");
//  DATA->Draw("X2res1>>hX2res2","CUTpad1tof","same");
  DATA->Draw("X2res1>>hX2res_1","CUTpad1tof","");

  pad2->cd(4);
  gStyle->SetPalette(1);
//  DATA->Draw("X2res0:X2res1>>hX2Res2djj","CUTpad1tof","col");
  DATA->Draw("X2res0:X2res1>>hX2Res2djj5","CUTpad1tof","col");
//  DATA->Draw("X2res0:X2res1>>hX2Res2djj","pad1>1000 && pad1<1680 && tof>3530 && tof<3618","col");
//  hX2Res2djj->SetStats(0);
//  hX2_Res2diTL->Draw("col");

  pad2->cd(3);
  gStyle->SetPalette(1);
//  DATA->Draw("Y1:Eexcit>>hY1vsEx","CUTpad1tof","col");
  DATA->Draw("Y2:X2pos>>hY2vsX2","CUTpad1tof","col");
//  hY1vsEx->GetXaxis()->SetRangeUser(limX_min,limX_max);
/*
  pad2->cd(5);
  gStyle->SetPalette(1);
  DATA->Draw("X2res0>>hX2res_0","CUTpad1tof","");

  pad2->cd(6);
  gStyle->SetPalette(1);
  DATA->Draw("X2res0:X2res1>>hX2Res2djj","CUTpad1tof","col");
*/
  double sigmaX2, sigmaX2;
  Char_t textX2[100],textX2[100];
  Char_t resX2[100],resX2[100];
  TPaveText* legendX2 = new TPaveText(0.11,0.6,0.4,0.75,"brNDC");
//  TPaveText* legendX2 = new TPaveText(0.11,0.6,0.4,0.8,"brNDC");
  legendX2->SetShadowColor(0);  
  legendX2->SetLineColor(0);  
//  legendX2->SetFillColor(0);  
//  legendX2->SetShadowColor(0);  
//  legendX2->SetLineColor(0);  
//  legendX2->SetFillColor(0);  

  pad2->cd(2);
  hX2res_1->Fit("gaus","","",-4.,4.);
  sigmaX2=hX2res_1->GetFunction("gaus")->GetParameter(2);
  gaus->SetLineColor(2);
  gaus->SetLineWidth(2);
  sprintf(textX2,"sigma = %f mm",sigmaX2);
  sprintf(resX2,"FWHM(x) = %f mm ",2.35*sigmaX2/(2*sqrt(6)));
  legendX2->SetTextFont(40);
  legendX2->AddText(textX2);
  legendX2->AddText("For 5 wires:");
  legendX2->AddText(resX2);
  legendX2->Draw();

/*
  pad2->cd(5);
  hX2res_0->Fit("gaus","","",-4.,4.);
  sigmaX2=hX2res_0->GetFunction("gaus")->GetParameter(2);
  gaus->SetLineColor(2);
  gaus->SetLineWidth(2);
  sprintf(textX2,"sigma = %f mm",sigmaX2);
  sprintf(resX2,"FWHM(x) = %f mm ",2.35*sigmaX2/(2*sqrt(6)));
  legendX2->SetTextFont(40);
  legendX2->AddText(textX2);
  legendX2->AddText("For 5 wires:");
  legendX2->AddText(resX2);
  legendX2->Draw();
*/
  pad2->cd(4);

}
