// **** For some reason ROOT can't read the TTree after I called a script like .L save_cut.C and LoadCuts() - I have to load them 1st then load the TFile..!!!
{
    ofstream outf;

    Char_t fname[128], buffer[128], buffer2[128], textX1[128], textX2[128];
    Double_t sigmaX1;
    Double_t offs[18], peak1=688.;
    Int_t run_no[]={6028,6029,6036,6037,6038,6039,6040,6042,6043,6044,6045,6048,6049,6050,6052,6054,6055,6056};
    Int_t nrofruns=sizeof(run_no)/sizeof(run_no[0]);
    Int_t k=0;

    for(Int_t j=0;j<nrofruns;j++) offs[j]=0;
    outf.open("x1pos_offsets_tmp.dat");

    for(Int_t i=0;i<nrofruns;i++) {
    	sprintf(fname,"/media/jjvz/PR2312/PR231/ROOT_DATA/sorted0%d.root",run_no[i]);
    	TFile *f = TFile::Open(fname);

    	f->cd();
		TH1F *hX1pos = new TH1F("hX1pos","X1 Position",2000,100.,800.);   
   		DATA->Draw("X1posC>>hX1pos","CUTpad1tof","");

  		hX1pos->GetXaxis()->SetRangeUser(520,780);
   		hX1pos->Draw();
   		hX1pos->Fit("gaus","","",683,693);	// 688.
   
   		TPaveText* legendX1 = new TPaveText(0.11,0.6,0.4,0.75,"brNDC");
   		legendX1->SetShadowColor(0);  
   		legendX1->SetLineColor(0);  

   		sigmaX1=hX1pos->GetFunction("gaus")->GetParameter(1);
   		offs[i]=sigmaX1-peak1;
   		cout<<"offs["<<i<<"] = "<<offs[i]<<endl;

   		sprintf(textX1,"mean = %5.2f mm",sigmaX1);
   		sprintf(textX2,"runno.: %d",run_no[i]);
   		legendX1->SetTextFont(40);
   		legendX1->AddText(textX1);
   		legendX1->AddText(textX2);
   		legendX1->Draw();
   
   		sprintf(buffer,"PICS/X1pos_test_run_%d.png",run_no[i]);
   		c1->Print(buffer);
   		sprintf(buffer2,"PICS/X1pos_test_run_%d.C",run_no[i]);
   		c1->Print(buffer2);
    }

    for(j=0;j<nrofruns;j++) outf << run_no[j] << "\t"<< offs[j]  << endl;
    outf.close();
}

