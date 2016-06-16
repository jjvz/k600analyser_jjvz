{
// Usage: in ROOT[] .x TDC_offset.C  
// NOTE this script must be run on runfiles with initial 0 offsets, else offsets have already been shifted!
//
  ofstream outf;

  char name[128], buffer[128], buffer2[128], lab[128];
  Double_t sigmaTOF;
  Double_t offs[276], peak0=2222;
//  Int_t run_no[]={245,246,247,248,249,251,253,255,256,258,259,260,262,263,264,266,267,268,269,271,272,273,276,277,278,279};
  Int_t run_no[]={245,246,247,248,249,251,253,255,256,258,259,260,262,263,264};
//  Int_t run_no[]={139,140,245};
  Int_t nrofruns=sizeof(run_no)/sizeof(run_no[0]);
  Int_t runlim=276;	// max run number, e.g. run sorted00276.root
  
  Int_t k=0;
    
  for(Int_t j=0;j<276;j++) offs[j]=0;

  outf.open("TDC_offsets_tmp.dat");

  for(Int_t i=1;i<=276;i++) {
    if(i==run_no[k]) {
      sprintf(name,"/media/jjvz/PR2312/PR231/ROOT_DATA/sorted0%d.root",run_no[k]);
      TFile *f1 = TFile::Open(name);
      
      f1->cd();

//      TH2F *hpad1vstof = new TH2F("hpad1vstof","Scint 1 vs time of flight",1000,2000.,6000.,2000,0.,4000.);
//      TCanvas *c2 = new TCanvas("c2","c2",600,600);
//      DATA->Draw("pad1:tof>>hpad1vstof","pad1>500 && pad1<2000 && tof>3400 && tof<3900","col");

//      hpad1vstof->GetXaxis()->SetRangeUser(3400,3900);
//      hpad1vstof->GetYaxis()->SetRangeUser(500,2000);
      TH2F *h2D = (TH2F*)f1->FindObjectAny("TDC2DModule_006");
      
	for(Int_t j=0;j<16;j++) {	      
      sprintf(buffer,"pics/TDC_spect_run_%d_ch_%d.jpg",run_no[k],j+1);

      TCanvas *c1 = new TCanvas("c1","c1",600,600);
//      TH1D *histop = new TH1D();
//      histop = h2D->ProjectionX("proj",610,620);
//      histop->Draw();
//      histop->Rebin(4);
//      histop->GetXaxis()->SetRangeUser(3400,3900);
//      TDC2DModule_006->GetYaxis()->SetRangeUser(3400,3900);
//      TDC2DModule_006->Draw("col");

      TH1D *histop = new TH1D();
      sprintf(buffer2,"histop = h2D->ProjectionX(\"proj\",65+j,65+j);",j);
	  gROOT->ProcessLine(buffer2);
//      histop = h2D->ProjectionX("proj",65,66);
      histop->GetXaxis()->SetRangeUser(1000,3500);
      histop->Draw();

      TSpectrum *sp = new TSpectrum(6);
      sp->Search(histop,2,"",25.);
      c1->SaveAs(buffer);    
      double *chan = sp->GetPositionX();
      
      offs[i-1] = peak0 - chan[0];

      cout <<sp->GetNPeaks()<< " peaks found at " << chan[0] << " and "<<chan[1]<< endl;	// chan[0] is first TOF peak - to be shifted to 3586 !
      cout <<" offsets = "<< offs[i-1]<<" and "<< peak0-chan[1]<< endl;					// offset = 3586 - chan[0]

   
      TPaveText *pt = new TPaveText(0.1,0.80,0.6,0.7,"brNDC");
      pt->SetBorderSize(0);
      pt->SetFillColor(0);
      pt->SetFillStyle(0);
      pt->SetTextFont(42);
      pt->SetTextSize(0.04);
      sprintf(lab,"%.0f \n(offset=%.0f)",chan[0],offs[i-1]);

      TText *text = pt->AddText(lab);
      pt->Draw();
      c1->Update();
		  
      c1->SaveAs(buffer);
	      
      delete sp;
      delete histop;
      }
      k++;
    }
   }
   for(j=0;j<276;j++) outf << offs[j]  << endl;

   outf.close();    
    
   cout << "DONE IT! ALPHAS -> PUB" << endl;
}


