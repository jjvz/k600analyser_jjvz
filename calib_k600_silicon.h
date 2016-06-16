#include <TF1.h>
#include <TFile.h>
#include <TROOT.h>
#include <TTree.h>
#include <TChain.h>
#include <TCanvas.h>
#include <TH1.h>
#include <TH2.h>
#include <string>
#include <iostream>
#include <TCutG.h>
#include <fstream>
#include <TSpectrum.h>
#include <algorithm>
#include <TF1.h>
#include <TGraph.h>
#include <TSystem.h>

double offsets[4*32], gains[4*32];

using std::cout;
using std::endl;
using std::sort;

TFile *ffile;

double alpha_E[5] = {5423.15, 5685.37, 6288.08, 6778.3, 8784.86};	// Note: Si energies in keV
double alpha_E4[4] = {5423.15, 6288.08, 6778.3, 8784.86};

void mOutput()
{
  ofstream output;
  output.open("Si_calib_pars.h");
  for(int i=0;i<4*32;i++) output << i <<"\t"<< offsets[i] <<"\t"<< gains[i] << endl;
}
