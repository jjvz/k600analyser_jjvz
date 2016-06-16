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

  TH1F *hU2res_0 = new TH1F("hU2res_0","U2 Resolution; hU2res0",200,-0.1,1.1);
  TH1F *hU2res_1 = new TH1F("hU2res_1","U2 Resolution; hU2res1",200,-8.,8.);
  TH2F *hU2Res2djj5 = new TH2F("hU2Res2djj5","iTL-jj style resolution plot for U2; hU2res1", 200,-3.,3.,200,-0.1,1.1);
//  TH2F *hU2Res2djj2 = new TH2F("hU2Res2djj2","iTL-jj style resolution plot for U2; hU2res2", 200,-3.,3.,200,-0.1,1.1);
//  TH1F *hU2res2 = new TH1F("hU2res2","U2 Resolution",200,-8.,8.);
//  TH2F *hU2res2diTL = new TH2F("hU2res2diTL","U2 2D Resolution - helions",200,-3.,3.,200,-0.1,1.1);
//  TH2F *hU2res2diTL = new TH2F("hU2res2diTL","U2 2D Resolution - helions",200,-0.1,1.1,200,-3.,3.);
//  TH1F *hU2res2 = new TH1F("hU2res2","U2 Resolution",320,-8.,8.);

  TPad* pad2 = new TPad("pad2","Spectra",0.01,0.01,0.99,0.99);
  pad2->SetFillColor(0);
  pad2->Draw();
  pad2->cd();
  pad2->Divide(2,2);

  pad2->cd(1);
  DATA->Draw("U2pos>>hU2pos","CUTpad1tof","");
//  DATA->Draw("Eexcit>>hEexcit","CUTpad1tof","");
//  hEexcit->GetXaxis()->SetRangeUser(limX_min,limX_max);
//  DATA->Draw("U2res5>>hU2res2","pad1>1000 && pad1<1680 && tof>3530 && tof<3618","");
//  DATA->Draw("U2res2>>hU2res2","pad1>1000 && pad1<1680 && tof>3530 && tof<3618","");

  pad2->cd(2);
//  DATA->Draw("U2res1>>hU2res2","pad1>1000 && pad1<1680 && tof>3530 && tof<3618","");
//  DATA->Draw("U2res1>>hU2res2","pad1>1000 && pad1<1680 && tof>3530 && tof<3618","");
//  DATA->Draw("U2res1>>hU2res2","CUTpad1tof","same");
  DATA->Draw("U2res1>>hU2res_1","CUTpad1tof","");

  pad2->cd(4);
  gStyle->SetPalette(1);
//  DATA->Draw("U2res0:U2res1>>hU2Res2djj","CUTpad1tof","col");
  DATA->Draw("U2res0:U2res1>>hU2Res2djj5","CUTpad1tof","col");
//  DATA->Draw("U2res0:U2res1>>hU2Res2djj","pad1>1000 && pad1<1680 && tof>3530 && tof<3618","col");
//  hU2Res2djj->SetStats(0);
//  hU2_Res2diTL->Draw("col");

  pad2->cd(3);
  gStyle->SetPalette(1);
//  DATA->Draw("Y1:Eexcit>>hY1vsEx","CUTpad1tof","col");
  DATA->Draw("Y2:U2pos>>hY2vsU2","CUTpad1tof","col");
//  hY1vsEx->GetXaxis()->SetRangeUser(limX_min,limX_max);
/*
  pad2->cd(5);
  gStyle->SetPalette(1);
  DATA->Draw("U2res0>>hU2res_0","CUTpad1tof","");

  pad2->cd(6);
  gStyle->SetPalette(1);
  DATA->Draw("U2res0:U2res1>>hU2Res2djj","CUTpad1tof","col");
*/
  double sigmaU2, sigmaU2;
  Char_t textU2[100],textU2[100];
  Char_t resU2[100],resU2[100];
  TPaveText* legendU2 = new TPaveText(0.11,0.6,0.4,0.75,"brNDC");
//  TPaveText* legendU2 = new TPaveText(0.11,0.6,0.4,0.8,"brNDC");
  legendU2->SetShadowColor(0);  
  legendU2->SetLineColor(0);  
//  legendU2->SetFillColor(0);  
//  legendU2->SetShadowColor(0);  
//  legendU2->SetLineColor(0);  
//  legendU2->SetFillColor(0);  

  pad2->cd(2);
  hU2res_1->Fit("gaus","","",-4.,4.);
  sigmaU2=hU2res_1->GetFunction("gaus")->GetParameter(2);
  gaus->SetLineColor(2);
  gaus->SetLineWidth(2);
  sprintf(textU2,"sigma = %f mm",sigmaU2);
  sprintf(resU2,"FWHM(x) = %f mm ",2.35*sigmaU2/(2*sqrt(6)));
  legendU2->SetTextFont(40);
  legendU2->AddText(textU2);
  legendU2->AddText("For 5 wires:");
  legendU2->AddText(resU2);
  legendU2->Draw();

/*
  pad2->cd(5);
  hU2res_0->Fit("gaus","","",-4.,4.);
  sigmaU2=hU2res_0->GetFunction("gaus")->GetParameter(2);
  gaus->SetLineColor(2);
  gaus->SetLineWidth(2);
  sprintf(textU2,"sigma = %f mm",sigmaU2);
  sprintf(resU2,"FWHM(x) = %f mm ",2.35*sigmaU2/(2*sqrt(6)));
  legendU2->SetTextFont(40);
  legendU2->AddText(textU2);
  legendU2->AddText("For 5 wires:");
  legendU2->AddText(resU2);
  legendU2->Draw();
*/
  pad2->cd(4);

}
