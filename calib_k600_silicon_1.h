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

double oPsides[64], gPsides[64];
double oNsides[64], gNsides[64];

using std::cout;
using std::endl;
using std::sort;

//double alpha3_E[3]={5156.59,5485.56,5804.77};
//double alpha_E[7] = {5340.36, 5423.15, 5685.37, 6050.78, 6288.08, 6778.3, 8784.86};
double alpha_E[5] = {5423.15, 5685.37, 6288.08, 6778.3, 8784.86};
//double alpha_E[4] = {4784.34,5489.48,6002.35,7686.82};

void mOutput()
{
  ofstream output;
  output.open("calib_pars_1.h");
  
  if(i==0) {
	output << " oPsides["<<c-1<<"] = "<<oPsides[c-1]<<";"<<endl;
	output << " gPsides["<<c-1<<"] = "<<gPsides[c-1]<<";"<<endl;
  }
  else if(i==1) {
	output << " oPsides["<<c+32-1<<"] = "<<oPsides[c+32-1]<<";"<<endl;
	output << " gPsides["<<c+32-1<<"] = "<<gPsides[c+32-1]<<";"<<endl;
  }
  else if(i==2) {
	output << " oNsides["<<c-1<<"] = "<<oNsides[c-1]<<";"<<endl;
	output << " gNsides["<<c-1<<"] = "<<gNsides[c-1]<<";"<<endl;
  }
  else if(i==3) {
	output << " oNsides["<<c+32-1<<"] = "<<oNsides[c+32-1]<<";"<<endl;
	output << " gNsides["<<c+32-1<<"] = "<<gNsides[c+32-1]<<";"<<endl;
  }

}
