{
// Usage: in ROOT[] .x pad1_tof_prnt.C  
// NOTE this script must be run on runfiles with initial 0 offsets, else offsets have already been shifted!
//

  char name[128], buffer[128], buffer2[128], lab[128], lab2[128];
  Double_t sigmaTOF;
  Float_t diff=0., offs[71], peak0=3006.;
  Int_t run_no[]={6028,6029,6030,6032,6033,6034,6035,6036,6037,6038,6039,6040,6041,6042,6043,6044,6045,6046,6047,6048,6049,6050,6052,6054,6055,6056};
//  Int_t run_no[]={139,140,245};
  Int_t nrofruns=sizeof(run_no)/sizeof(run_no[0]);
  
  Int_t k=0;
    
  TCanvas *c1 = new TCanvas("c1","c1",1200,600);
  c1->Divide(2,1);

  gROOT->ProcessLine(".L save_cut.C");
  gROOT->ProcessLine("LoadCuts()");
  gROOT->ProcessLine(".x histosPR231.C");

  for(Int_t i=0;i<nrofruns;i++) {
      sprintf(name,"/media/jjvz/PR2312/PR231/ROOT_DATA/sorted0%d.root",run_no[i]);
      TFile *f1 = TFile::Open(name);
//      cout<<"k: "<<k<<"\ti: "<<i<<"\tfile: "<<name<<endl;
      f1->cd();

      c1_1->cd();
      TH2F *hpad1vstof = new TH2F("hpad1vstof","Scint 1 vs time of flight",1000,2000.,6000.,2000,0.,4000.);
      hpad1vstof->GetXaxis()->SetRangeUser(2950,3050);
      hpad1vstof->GetYaxis()->SetRangeUser(600,950);
      DATA->Draw("pad1:tof>>hpad1vstof","CUTpad1tof","col");

      TH2F *h2D = (TH2F*)f1->FindObjectAny("hpad1vstof");
      sprintf(buffer2,"PICS/pad1vstof_new_run_%d.jpg",run_no[i]);

      c1_2->cd();
      TH1D *histop = new TH1D();
      histop = h2D->ProjectionX("proj",361,380);   //ProjectionX (const char *name="_px", Int_t firstybin=0, Int_t lastybin=-1, Option_t *option="")
      histop->Draw();
//      histop->Rebin(4);
      histop->GetXaxis()->SetRangeUser(2950,3050);

      TSpectrum *sp = new TSpectrum(2,1);
      sp->Search(histop,1,"",0.05);
//      double *chan = sp->GetPositionX();
      Float_t *chan = sp->GetPositionX();
      Float_t xp1 = chan[0];
      diff = peak0 - xp1;
      cout <<sp->GetNPeaks()<< " peaks found at " << xp1 << endl;	// chan[0] is first TOF peak - to be shifted to 3040 !
      cout <<" offset = "<< diff<< endl;					// offset = 3586 - chan[0]

   
      TPaveText *pt = new TPaveText(0.1,0.80,0.6,0.7,"brNDC");
      pt->SetBorderSize(0);
      pt->SetFillColor(0);
      pt->SetFillStyle(0);
      pt->SetTextFont(42);
      pt->SetTextSize(0.04);
      sprintf(lab,"%.0f \n(offset=%.0f)",xp1,diff);
      sprintf(lab2,"\n(run: %d)",run_no[i]);

      TText *text = pt->AddText(lab);
      TText *text2 = pt->AddText(lab2);
      pt->Draw();

      c1->Update();
      c1->SaveAs(buffer2);    
      
      delete sp;
      delete histop;
    }
    
   cout << "DONE IT!  -> PUB" << endl;
}


