// Chain run for pr231 - JJvZ, 	Oct2014

//CHAINING will chain all TTree data values, i.e. ROOT Leafs, not histograms filled during analyses
//To call sertain spectra for this "chained run, call:
//DATAChain->Draw("X1pos>>hX1pos","","");
// or
//DATAChain->Draw("X1pos>>hX1pos","tof>5360 && tof<5480 && pad1>1000 && pad1<2250","");


{
  TChain *ch = new TChain("DATA");
  char name[128], buff[128];

  Int_t run_no[]={6028,6029,6036,6037,6038,6039,6040,6042,6043,6044,6045,6048,6049,6050,6052,6054,6055,6056};
//  Int_t run_no[3]={277,278,279};
//  Int_t run_no[]={228,229};
//  Int_t run_no[]={139,140};
  Int_t nrofruns=sizeof(run_no)/sizeof(run_no[0]);

  for(Int_t i=0;i<nrofruns;i++) {
      sprintf(name,"/media/jjvz/PR2312/PR231/ROOT_DATA/sorted0%4d.root",run_no[i]);
      if(!name) { cout<< "!!!! error... no such file... !!!!" <<endl; break; }
      cout<< name <<endl;
      ch->Add(name);
      cout<<"root file added.."<<endl;
  }
//  TFile *fChain = new TFile("/media/jjvz/PR231/PR231/ROOT_DATA/chain256.root","RECREATE");
//  ch->Write();

}

