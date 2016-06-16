// !!! Assume spectrum h01 !!!!
// Define number of peaks, min1, max1, sig, delt, peak centroids and heights

{
   Int_t nrpeaks=3;
   Double_t par[9]; 
   Float_t min1=500, max1=2000, sig=1.7, delt=7.; //for 120 MeV, 35 deg
   Float_t cent[3]={662.,1173.,1332.}; 
   Float_t N0[3]={60000,50000,50000};

//   Float_t min1=450, max1=470, sig=1.7, delt=6.; //for 120 MeV, 30 deg
//   Float_t cent[nrpeaks]={455.0,460.5,463.6}; 
//   Float_t N0[nrpeaks]={3.,18.,60.};

//   Float_t min1=450, max1=470, sig=1.7, delt=6.; //for 120 MeV, 25 deg
//   Float_t cent[nrpeaks]={455.0,460.5,463.6}; 
//   Float_t N0[nrpeaks]={3.,18.,60.};

//   Float_t min1=548, max1=570, sig=1.7, delt=5.;  //for 100 MeV, 25 deg
//   Float_t cent[nrpeaks]={553.5,557.9,561.5}; 
//   Float_t N0[nrpeaks]={14.,60.,212.};

//   Float_t min1=313, max1=330, sig=2.1, delt=7., res=14.83, ch0=321.6; //for 80 MeV, 25 deg
   // 14.83 keV / mm rel. to central peak at 321.6 mm  
//   Float_t cent[nrpeaks]={ch0-41./res,321.6,ch0+66./res}; 
//   Float_t N0[nrpeaks]={30,120,30};
   Float_t parg[3][3], minR=0.99*min1, maxR=1.01*max1;
   Int_t i,j,k,m,n,p,q,r;
   Char_t tempcom0[128],tempcom1[128],tempcom2[128],tempcom3[128],tempcom4[128],tempcom5[128];   
   Float_t min2=min1, max2=max1;
   
/*   TCanvas *Canvas_1 = new TCanvas("Canvas_1", "Canvas_1",0,0,500,500);
   Canvas_1->SetLeftMargin(0.12);
   Canvas_1->SetRightMargin(0.07);
   Canvas_1->SetTopMargin(0.07);
   Canvas_1->SetBottomMargin(0.11);
   
   gStyle->SetOptStat(0);
*/   
   for(r=0;r<nrpeaks;r++) {
       sprintf(tempcom0,"TF1 *g%d = new TF1(\"g%d\",\"gaus(0)\",cent[%d]-delt,cent[%d]+delt);",r+1,r+1,r,r);
       gROOT->ProcessLine(tempcom0);
   }
   sprintf(tempcom4,"TF1 *total = new TF1(\"total\",\"gaus(0)");
   for(n=36,r=1;r<nrpeaks;r++,n=n+8) {
       sprintf(tempcom5,"+gaus(%d)",3*r);
       for(i=1;i<9;i++) tempcom4[n+i] = tempcom5[i-1];
   }
   sprintf(tempcom5,"\",min1,max2);");
   for(j=1;j<14;j++) tempcom4[n+j] = tempcom5[j-1];
   cout<<tempcom4<<endl;

   gROOT->ProcessLine(tempcom4);
   total->SetLineColor(1);
   total->SetLineWidth(2);
   total->SetLineStyle(1);
    
   for(j=0,k=0;j<3*nrpeaks;j=j+3,k++) {
       par[j]   = N0[k];   // amplitude 1
       par[j+1] = cent[k];  // centroid/mean 1
       par[j+2] = sig;   // sigma 1
   }
   total->SetParameters(par);

   for(i=0;i<3*nrpeaks;i=i+3) {
       total->SetParLimits(i+1,1.,1.);
       total->SetParLimits(i+2,1.,1.);
   }
   h01->Fit(total,"","",min1,max2);
/*   h01->GetXaxis()->SetTitle("FP position (mm)");
   h01->GetYaxis()->SetTitle("Counts / bin");
   h01->GetXaxis()->SetLabelFont(42);
   h01->GetYaxis()->SetLabelFont(42);
   h01->GetXaxis()->SetTitleFont(42);
   h01->GetXaxis()->SetRangeUser(minR,maxR);
   h01->GetYaxis()->SetTitleFont(42);
   h01->GetXaxis()->CenterTitle();
   h01->GetYaxis()->CenterTitle();
   h01->GetXaxis()->SetLabelSize(0.04);
   h01->GetXaxis()->SetTitleSize(0.05);
   h01->GetYaxis()->SetLabelSize(0.04);
   h01->GetYaxis()->SetTitleSize(0.05);
   h01->GetXaxis()->SetTitleOffset(1.0);
   h01->GetYaxis()->SetTitleOffset(1.2);
   h01->SetTitle(0);
   h01->SetLineColor(1);
*/   
         // Some details on graphs:
	Char_t text1[128], text2[128];
	TPaveText *leg1=new TPaveText(0.25,0.70,0.35,0.80,"NDC");
	sprintf(text1,"E_{beam} = 80 MeV");
	sprintf(text2,"#theta = 25^{o}");
	leg1->SetTextSize(0.04);
	leg1->SetTextFont(42);
	leg1->SetBorderSize(0);
	leg1->SetFillColor(0);
	leg1->SetFillStyle(0);
	leg1->AddText(text1);
	leg1->AddText(text2);
	leg1->Draw();
	c1->Update();
   
   total->GetParameters(&par[]);

   for(m=0,n=0;m<nrpeaks;++m) {
       for(p=0;p<3;++n,++p) {
           parg[m][p]=par[n];
           //cout<<"parg["<<m<<"]["<<p<<"] = "<<parg[m][p]<<endl;
       }
   }
	for(q=0;q<nrpeaks;q++) {
		sprintf(tempcom1,"g%d->SetParameters(parg[%d][0],parg[%d][1],parg[%d][2]);",q+1,q,q,q);
		sprintf(tempcom2,"g%d->SetLineColor(1);",q+1);
		gROOT->ProcessLine(tempcom2);
		sprintf(tempcom2,"g%d->SetLineStyle(%0.f);",q+1,(q+2));
		gROOT->ProcessLine(tempcom2);
		sprintf(tempcom2,"g%d->SetLineWidth(2);",q+1);
		sprintf(tempcom3,"g%d->Draw(\"SAME\");",q+1);
		//cout<<tempcom2<<endl;
		gROOT->ProcessLine(tempcom1);
		gROOT->ProcessLine(tempcom2);
		gROOT->ProcessLine(tempcom3);
	}
//total->Draw("SAME");

}

