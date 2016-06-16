{
// make sure a default TFile is open, like _file0 where gate will be saved
// you have to first plot the relevant histogram
TCutG *cut = new TCutG();
CUTpad1tof = (TCutG*) gPad -> WaitPrimitive("CUTG");	//this waits for mouse input:
CUTpad1tof -> SetName("CUTpad1tof"); 
CUTpad1tof -> SetVarX("tof");
CUTpad1tof -> SetVarY("pad1");
//CUTpad1tof -> Write();	//should work once a root file has been opened
// uncomment next section only if you want to write the gate to somewhere
//TFile *_file0 = TFile::Open("test.root","UPDATE");
//file20 = new TFile("PR153/CUTpad1tof_run12692.root","NEW");
_file0->Append(CUTpad1tof);  //Assuming the current root file opened is _file0 (by default) 
_file0->Write();
//file20 -> ls();
//file20 -> Close();

// in order to get back to the root file you were looking at
// you should cd back into that file:     _file0->cd()

/* ---- to read this gate back, run the code below: -----
{

TFile * file20 = new TFile("PR153/CUTpad1tof_run12692.root","OLD");
TCutG *cut   = (TCutG*) file20 -> Get( "CUTpad1tof" );
cut->SetVarX("tof");
cut->SetVarY("pad1");

// in order to get back to the root file you were looking at
// you should cd back into that file:     file->cd()
}
*/

}
