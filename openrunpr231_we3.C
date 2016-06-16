// Chain run for pr231 - JJvZ, 	Oct2014

//CHAINING will chain all TTree data values, i.e. ROOT Leafs, not histograms filled during analyses
//To call sertain spectra for this "chained run, call:
//DATAChain->Draw("X1pos>>hX1pos","","");
// or
//DATAChain->Draw("X1pos>>hX1pos","tof>5360 && tof<5480 && pad1>1000 && pad1<2250","");


{
  char name[128], buff[128];

//  Int_t run_no[]={246,247,248,249,251,253,255,256,258,259,260,262,263,264,266,267,268,269,271,272,273,276};
//  Int_t run_no[3]={277,278,279};
  Int_t run_no=6028;
//  Int_t run_no[]={139,140};

  sprintf(name,"/media/jjvz/PR2312/PR231/ROOT_DATA/sorted0%4d.root",run_no);
  TFile *runfile = TFile::Open(name);
  cout<<"root file "<< name << " opened.."<<endl;

//  TFile *fChain = new TFile("/media/jjvz/PR231/PR231/ROOT_DATA/chain256.root","RECREATE");
//  ch->Write();

}

