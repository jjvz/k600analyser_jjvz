// to fix only 1 Si channel at a time with manual 5 peak centroid values - JJvZ, Dec2014

#include "calib_mod_ch.h"
#include "calib_k600_silicon_1.h"


void calib()
{
  TFile *f1 = TFile::Open("/media/jjvz/PR2312/PR231/ROOT_DATA/sorted05034.root");

//  int i=0;	// select ADC module (0-3)
//  int c=23;	// Select Si channel number inside ADC module (1-32)

//  spect();

  TCanvas *c1 = new TCanvas("c1","c1",600,600);
   
  char buffer[128];
  sprintf(buffer,"hADC2DModule%d",i);
  cout << buffer << endl;
  TH2F *h2D = (TH2F*)f1->FindObjectAny(buffer);
  h2D->Draw("col");
  
  TH1D *histop = new TH1D();
  histop = h2D->ProjectionX("proj",c,c);
  histop->Draw();
  histop->Rebin(4);
  histop->GetXaxis()->SetRangeUser(500,4000);

  sprintf(buffer,"PICS/spectrum_%d_%d.jpg",i,c);
  TSpectrum *sp = new TSpectrum(6);   

// assuming the number of peaks is 5, as required
  double chan[5] = {1107.,1158.,1256.,1389.,1790.};
		  
  for(int n=0;n<4;n++) {	// Ensure that the peaks are in the right order...
	for(int nn=n+1;nn<5;nn++) {
	  if(chan[nn]<chan[n]) {
	    float chan_tmp = chan[n];
	    chan[n]=chan[nn];
	    chan[nn]=chan_tmp;
          }
	}
  }
		  
  TGraph *g = new TGraph();
  for(int n=0;n<5;n++) g->SetPoint(n,chan[n],alpha_E[n]);
  
  TF1 *fit = new TF1("fit","pol1(0)",0,10000);
  g->Fit(fit,"Q");

  float maxE = fit->Eval(histop->GetXaxis()->GetXmax());
  float scale = histop->GetMaximum()/maxE * 0.7;

  for(int kk=0;kk<5;kk++) {
        double x,y;
        g->GetPoint(kk,x,y);
        g->SetPoint(kk,x,y * scale);
  }
  g->Draw("L* ][sames");

  c1->SaveAs(buffer);
	      
  if(i==0) {oPsides[c-1] = fit->GetParameter(0); gPsides[c-1] = fit->GetParameter(1);}
  else if(i==1) {oPsides[c+32-1] = fit->GetParameter(0); gPsides[c+32-1] = fit->GetParameter(1);}
  else if(i==2) {oNsides[c-1] = fit->GetParameter(0); gNsides[c-1] = fit->GetParameter(1);}
  else if(i==3) {oNsides[c+32-1] = fit->GetParameter(0); gNsides[c+32-1] = fit->GetParameter(1);}
  else cout << "FUUUUUCK" << endl;
              
//  delete histop;
  
  mOutput();
  
  cout << "DONE IT! ALPHAS -> PUB" << endl;
}



