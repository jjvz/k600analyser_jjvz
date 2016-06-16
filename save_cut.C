// Usage:
// (1) Draw the histo
// (2) create the cut
// (3) save the cut:
//      root[0] .L save_cut.C
// 	root[1] SaveCuts()	// to save the cut
// 	root[2] LoadCuts()	// to load the cut

#include "TFile.h"
#include "TCutG.h"

void SaveCuts(void)
{
  TFile *fcut = new TFile("CUTpad1tof_PR231_we3.root","recreate");
  fcut->cd();
  gROOT->FindObject("CUTpad1tof")->Write();
//  gROOT->FindObject("CUTa0")->Write();
  fcut->Close();
}

void LoadCuts(void)
{
  TFile *fcut = new TFile("CUTpad1tof_PR231_we3.root");
  TCutG *CUTEC = (TCutG*) fcut->Get("CUTpad1tof");
//  TCutG *CUTNI69 = (TCutG*) fcut->Get("CUTa0");
  fcut->Close();
}

