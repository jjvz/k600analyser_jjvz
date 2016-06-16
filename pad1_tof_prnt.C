{
// Usage: in ROOT[] .x pad1_tof_prnt.C  
// NOTE this script must be run on runfiles with initial 0 offsets, else offsets have already been shifted!
//
  ofstream outf;

  char name[128], buffer[128], buffer2[128], lab[128], lab2[128];
  Double_t sigmaTOF;
  Float_t diff=0., offs[71], peak0=3040.;
  Int_t run_no[]={6001,6002,6003,6004,6005,6006,6007,6008,6009,6010,6011,6012,6013,6014,6015,6016,6017,6018,6019,6020,6021,6022,6023,6024,6025,6026,6027,6028,6029,6030,6032,6033,6034,6035,6036,6037,6038,6039,6040,6041,6042,6043,6044,6045,6046,6047,6048,6049,6050,6052,6054,6055,6056,6070,6071};
//  Int_t run_no[]={139,140,245};
  Int_t nrofruns=sizeof(run_no)/sizeof(run_no[0]);
  Int_t runi=6001, runf=6071, runlim=6071;	// max run number, e.g. run sorted00276.root
  
  Int_t k=0;
    
  for(Int_t j=0;j<(runf-runi+2);j++) offs[j]=0.;

  outf.open("tof_offsets_tmp.dat");

  TCanvas *c1 = new TCanvas("c1","c1",1200,600);
  c1->Divide(2,1);

  for(Int_t i=0;i<(runf-runi+2);i++) {
    if(i+runi==run_no[k]) {
      sprintf(name,"/media/jjvz/PR2312/PR231/ROOT_DATA/sorted0%d.root",run_no[k]);
      TFile *f1 = TFile::Open(name);
//      cout<<"k: "<<k<<"\ti: "<<i<<"\tfile: "<<name<<endl;
      f1->cd();

      c1_1->cd();
      TH2F *hpad1vstof = new TH2F("hpad1vstof","Scint 1 vs time of flight",1000,2000.,6000.,2000,0.,4000.);
      DATA->Draw("pad1:tof>>hpad1vstof","pad1>500 && pad1<1500 && tof>2500 && tof<3500","col");

      hpad1vstof->GetXaxis()->SetRangeUser(2900,3500);
      hpad1vstof->GetYaxis()->SetRangeUser(500,2000);
      TH2F *h2D = (TH2F*)f1->FindObjectAny("hpad1vstof");
	      
      sprintf(buffer,"PICS/tof_spect_run_%d.jpg",run_no[k]);
      sprintf(buffer2,"PICS/pad1vstof_spect_run_%d.jpg",run_no[k]);

      c1_2->cd();
      TH1D *histop = new TH1D();
      histop = h2D->ProjectionX("proj",348,424);   //ProjectionX (const char *name="_px", Int_t firstybin=0, Int_t lastybin=-1, Option_t *option="")
      histop->Draw();
//      histop->Rebin(4);
      histop->GetXaxis()->SetRangeUser(2500,3500);

      TSpectrum *sp = new TSpectrum(2,1);
      sp->Search(histop,2,"",0.05);
//      double *chan = sp->GetPositionX();
      Float_t *chan = sp->GetPositionX();
      Float_t xp1 = chan[0];
      Float_t xp2 = chan[1];
      diff = peak0 - xp1;
      offs[i] = diff;

      cout <<sp->GetNPeaks()<< " peaks found at " << xp1 << " and "<< xp2 << endl;	// chan[0] is first TOF peak - to be shifted to 3040 !
      cout <<" offsets = "<< diff<<" and "<< peak0-xp2 << endl;					// offset = 3586 - chan[0]

   
      TPaveText *pt = new TPaveText(0.1,0.80,0.6,0.7,"brNDC");
      pt->SetBorderSize(0);
      pt->SetFillColor(0);
      pt->SetFillStyle(0);
      pt->SetTextFont(42);
      pt->SetTextSize(0.04);
      sprintf(lab,"%.0f \n(offset=%.0f)",xp1,diff);
      sprintf(lab2,"\n(run: %d)",run_no[k]);

      TText *text = pt->AddText(lab);
      TText *text2 = pt->AddText(lab2);
      pt->Draw();

      c1->Update();
      c1->SaveAs(buffer);    
      
      delete sp;
      delete histop;
      
      k++;
    }
    outf << diff  << endl;
   }
//   for(j=0;j<(runf-runi+2);j++) outf << offs[j]  << endl;

   outf.close();    
    
   cout << "DONE IT!  -> PUB" << endl;
}


