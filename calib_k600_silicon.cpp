#include "calib_k600_silicon.h"

void calib()
{
  //TFile *f1 = TFile::Open("/k600user/PR231/data/sorted00035.root");
  //TFile *f1 = TFile::Open("output.root");
  TFile *f1 = TFile::Open("/media/jjvz/PR2312/PR231/ROOT_DATA/sorted05034.root");

  TCanvas *c1 = new TCanvas("c1","c1",600,600);

  for(int i=0;i<4;i++) {//Loop over ADC modules
      char buffer[128];
      sprintf(buffer,"hADC2DModule%d",i);
      cout << buffer << endl;
      TH2F *h2D = (TH2F*)f1->FindObjectAny(buffer);
      h2D->Draw("col");
      for(int c=0;c<32;c++) {//Loop over channels inside the ADC module
//	  	cout << i << "\t" << c+1 << endl;
	    
	  	TH1D *histop = new TH1D();
	  	histop = h2D->ProjectionX("proj",c+1,c+1);
	  	histop->Draw();
	  	histop->Rebin(4);
	  	histop->GetXaxis()->SetRangeUser(500,4000);
	      
	  	sprintf(buffer,"PICS/spectrum_%d_%d.jpg",i,c+1);

	  	TSpectrum *sp = new TSpectrum(6);
	  	sp->Search(histop,6,"",0.2);
	  	c1->SaveAs(buffer);    

//--------------------------------------------------------------------------------------------------	  	
	  	if(sp->GetNPeaks()==4) {
       	  cout << "           peaks found: " << sp->GetNPeaks() << " in channel " << c+1 << endl;
	      float *chan = sp->GetPositionX();
		  
	      for(int n=0;n<3;n++){//Ensure that the peaks are in the right order...
			for(int nn=n+1;nn<4;nn++){
		  		if(chan[nn]<chan[n]){
		    		float chan_tmp = chan[n];
		    		chan[n]=chan[nn];
		    		chan[nn]=chan_tmp;
		  		}
		  	}
		  }
      	  	  
	      TGraph *g = new TGraph();
	      for(int n=0;n<4;n++){g->SetPoint(n,chan[n],alpha_E4[n]);}
		  
	      TF1 *fit = new TF1("fit","pol1(0)",0,10000);
	      g->Fit(fit,"Q");
	      
	      float maxE = fit->Eval(histop->GetXaxis()->GetXmax());
	      float scale = histop->GetMaximum()/maxE * 0.7;

	      for(int kk=0;kk<4;kk++){
		  	double x,y;
		  	g->GetPoint(kk,x,y);
		  	g->SetPoint(kk,x,y * scale);
		  }
	      g->Draw("L* ][sames");

	      c1->SaveAs(buffer);
	      
//	      cout << "ADCModule= " << i << " Channel= " << c+1 << " offset= " << fit->GetParameter(0) << " gain= " << fit->GetParameter(1) << endl;
	      
	      offsets[i*32+c] = fit->GetParameter(0); 
	      gains[i*32+c] = fit->GetParameter(1);
	       
	    }
//--------------------------------------------------------------------------------------------------	  
	  	else if(sp->GetNPeaks()==5) {
       	  cout << "           peaks found: " << sp->GetNPeaks() << " in channel " << c+1 << endl;
	      float *chan = sp->GetPositionX();
		  
	      for(int n=0;n<4;n++){//Ensure that the peaks are in the right order...
			for(int nn=n+1;nn<5;nn++){
		  		if(chan[nn]<chan[n]){
		    		float chan_tmp = chan[n];
		    		chan[n]=chan[nn];
		    		chan[nn]=chan_tmp;
		  		}
		  	}
		  }

	      TGraph *g = new TGraph();
	      for(int n=0;n<5;n++){g->SetPoint(n,chan[n],alpha_E[n]);}

//-------------  for single case  -------------------------------------------------------------------	  
          if(i==3 && (c+1)==24){ 
          	chan[0]=1219.;
          	chan[1]=1406.;
          	chan[2]=1513.;
          	chan[3]=1961.;       	
 			for(int n=0;n<4;n++){g->SetPoint(n,chan[n],alpha_E4[n]);}
          }
//--------------------------------------------------------------------------------------------------	  
    		  
	      TF1 *fit = new TF1("fit","pol1(0)",0,10000);
	      g->Fit(fit,"Q");
	      
	      float maxE = fit->Eval(histop->GetXaxis()->GetXmax());
	      float scale = histop->GetMaximum()/maxE * 0.7;

	      for(int kk=0;kk<5;kk++){
		  	double x,y;
		  	g->GetPoint(kk,x,y);
		  	g->SetPoint(kk,x,y * scale);
		  }
	      g->Draw("L* ][sames");

	      c1->SaveAs(buffer);
	      
//	      cout << "ADCModule= " << i << " Channel= " << c+1 << " offset= " << fit->GetParameter(0) << " gain= " << fit->GetParameter(1) << endl;
	      
	      offsets[i*32+c] = fit->GetParameter(0); 
	      gains[i*32+c] = fit->GetParameter(1);
	       
	    }
	    
//--------------------------------------------------------------------------------------------------	  
		else if(sp->GetNPeaks()==6){
          cout << "           peaks found: " << sp->GetNPeaks() << " in channel " << c+1 << endl;
	      float *chan = sp->GetPositionX();

		  
	      for(int n=0;n<5;n++){//Ensure that the peaks are in the right order...
			for(int nn=n+1;nn<6;nn++){
		  		if(chan[nn]<chan[n]){
		    		float chan_tmp = chan[n];
		    		chan[n]=chan[nn];
		    		chan[nn]=chan_tmp;
		  		}
		  	}
		  }
  
	      TGraph *g = new TGraph();
	      for(int n=0;n<6;n++){
			if(n<2){g->SetPoint(n,chan[n],alpha_E[n]);cout << n << "\t" << chan[n] << "\t" << alpha_E[n] << endl;}
			else if(n>2){g->SetPoint(n-1,chan[n],alpha_E[n-1]);cout << n << "\t" << chan[n] << "\t" << alpha_E[n-1] << endl;}
	      }
		  
	      TF1 *fit = new TF1("fit","pol1(0)",0,10000);
	      g->Fit(fit,"Q");
	      
	      float maxE = fit->Eval(histop->GetXaxis()->GetXmax());
	      float scale = histop->GetMaximum()/maxE * 0.7;

	      for(int kk=0;kk<6;kk++){
		  double x,y;
		  if(kk<2){
		     g->GetPoint(kk,x,y);
		     g->SetPoint(kk,x,y * scale);
		  }
		  else if(kk>2){
		     g->GetPoint(kk-1,x,y);
		     g->SetPoint(kk-1,x,y * scale);
		  }
	      }
	      g->Draw("L* ][sames");

	      c1->SaveAs(buffer);
	      //cout << "ADCModule= " << i << " Channel= " << c+1 << " offset= " << fit->GetParameter(0) << " gain= " << fit->GetParameter(1) << endl;
	      
	      offsets[i*32+c] = fit->GetParameter(0); 
	      gains[i*32+c] = fit->GetParameter(1);
	    }
//----------------------------------------------------------------------------------------
		else {
		  	if(sp->GetNPeaks()<4){cout << "                                not enough peaks found... only " << sp->GetNPeaks() << " in channel " << c << endl;}
			else {cout << "----------------too many peaks found " << sp->GetNPeaks() << " in channel " << c+1 << endl;}
			offsets[i*32+c] = 0; 
			gains[i*32+c] = -1.;
		}
	
	  delete sp;
	  delete histop;
	  }
  }
  
  mOutput();

  cout << "DONE IT! ALPHAS -> PUB" << endl;
  //gROOT->ProcessLine(".q");
}

