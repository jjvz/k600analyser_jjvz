{
   Int_t nrpeaks=4;	// number of gaus peaks to fit
   Int_t nrpar=3;	// number of parameters = 3: N0, cent, sig
   Double_t par[12]; // = nrpeaks*nrpar
//   Float_t min1=500, max1=2000, sig=70., delt_cent=200., delt_plot=300.; //for 120 MeV, 35 deg
   Float_t min1=100, max1=500, sig=10., delt_N=10000, delt_cent=10., delt_sig=5., delt_plot=30.; //for 120 MeV, 35 deg
   Float_t cent[4]={159.,215.,255.,295.}; 
//   Float_t cent[4]={662.,1173.,1332.}; 
   Float_t N0[4]={90000,140000,5000,10000};

   Float_t parg[4][3], minR=0.99*min1, maxR=1.01*max1;
   Int_t i,j,k,m,n,p,q,r;
   Char_t tempcom0[128],tempcom1[128],tempcom2[128],tempcom3[128],tempcom4[128],tempcom5[128];   
   Float_t min2=min1, max2=max1;

   memset (tempcom4,0,sizeof(tempcom4));

   for(r=0;r<nrpeaks;r++) {
       sprintf(tempcom0,"TF1 *g%d = new TF1(\"g%d\",\"gaus(0)\",cent[%d]-delt_plot,cent[%d]+delt_plot);",r+1,r+1,r,r);
       gROOT->ProcessLine(tempcom0);
   }

   sprintf(tempcom4,"TF1 *total = new TF1(\"total\",\"gaus(0)");
   for(n=36,r=1;r<nrpeaks;r++,n=n+8) {
       sprintf(tempcom5,"+gaus(%d)",nrpar*r);
       for(i=1;i<nrpar*nrpeaks;i++) tempcom4[n+i] = tempcom5[i-1];
   }
   sprintf(tempcom5,"\",min1,max2);");
   for(j=1;j<14;j++) tempcom4[n+j] = tempcom5[j-1];
   cout<<tempcom4<<endl;	// TF1 *total = new TF1("total","gaus(0)+gaus(3)+gaus(6)",min1,max2);

   gROOT->ProcessLine(tempcom4);
   total->SetLineColor(1);
   total->SetLineWidth(2);
   total->SetLineStyle(1);

//	func->SetParameter(4,10);	// these two statements fix parameter 4 at 10.
//	func->SetParLimits(4,10,10);	// setting upper and lower limits the same, implies fixing the parameter, or alternatively:

//	func->SetParameter(4,12);
//	func->FixParameter(4,12);

//  ....or setting 9 parameters to values, only fixing some:..........
// func->SetParameters(N0[0],cent[0],sig,N0[1],cent[1],sig,N0[2],cent[2],sig);
// func->SetParLimits(2,cent[0]-delt_cent,cent[0]+delt_cent);
// func->FixParameter(4,0);

// total->SetParameters(N0[0],cent[0],sig,N0[1],cent[1],sig,N0[2],cent[2],sig);
   for(j=0,k=0;j<nrpar*nrpeaks;j=j+nrpar,k++) {
       par[j]   = N0[k];   	// amplitude 1
       par[j+1] = cent[k];  // centroid/mean 1
       par[j+2] = sig;   	// sigma 1
   }
   total->SetParameters(par);

   for(j=0,k=0;j<nrpar*nrpeaks;j=j+nrpar,k++) {
	   total->SetParLimits(j+0,N0[k]-delt_N,N0[k]+delt_N);
	   total->SetParLimits(j+1,cent[k]-delt_cent,cent[k]+delt_cent);
	   total->SetParLimits(j+2,sig-delt_sig,sig+delt_sig);
   }

// .................... Fixing parameters: ........................................
// par[0]=60178.2;  par[1]=770.3;  par[2]=181.767;  par[3]=39471.1;  par[4]=1168.57;  par[5]=70;  par[6]=41550.4;  par[7]=1365.15;  par[8]=70;  

// ....amplitudes:
// total->FixParameter(0,N0[0]);
// total->FixParameter(3,N0[1]);
// total->FixParameter(6,N0[2]);
// total->FixParameter(9,N0[3]);

// ....centroids:
 total->FixParameter(1,cent[0]);
// total->FixParameter(4,cent[1]);
 total->FixParameter(7,cent[2]);
 total->FixParameter(10,cent[3]);

 
// ....widths:
// total->FixParameter(2,sig);
 total->FixParameter(5,sig);
 total->FixParameter(8,sig);
 total->FixParameter(11,sig);


/*
   for(i=0;i<nrpar*nrpeaks;i=i+nrpar) {
       total->SetParLimits(i+1,1.,1.);
       total->SetParLimits(i+2,1.,1.);
   }
*/
   h01->Fit(total,"","",min1,max2);

   total->GetParameters(&par[]);
   for(m=0;m<nrpar*nrpeaks;++m) { cout<<"par["<<m<<"]="<<par[m]<<";  "; }
   cout<<endl;

   for(m=0,n=0;m<nrpeaks;++m) {
       for(p=0;p<nrpar;++n,++p) {
           parg[m][p]=par[n];
//           cout<<"parg["<<m<<"]["<<p<<"] = "<<parg[m][p]<<endl;
       }
   }
	for(q=0;q<nrpeaks;q++) {
		sprintf(tempcom1,"g%d->SetParameters(parg[%d][0],parg[%d][1],parg[%d][2]);",q+1,q,q,q);
		sprintf(tempcom2,"g%d->SetLineColor(%d);",q+1,q+2);
		gROOT->ProcessLine(tempcom2);
		sprintf(tempcom2,"g%d->SetLineStyle(%0.f);",q+1,q+2);
		gROOT->ProcessLine(tempcom2);
		sprintf(tempcom2,"g%d->SetLineWidth(2);",q+1);
		sprintf(tempcom3,"g%d->Draw(\"same\");",q+1);
		//cout<<tempcom2<<endl;
		gROOT->ProcessLine(tempcom1);
		gROOT->ProcessLine(tempcom2);
		gROOT->ProcessLine(tempcom3);
	}

// ..................................................................................
  cout << "........... some string stuff ..............." << '\n';
   std::string str;
   std::string str2="Writing ";
   std::string str3="print 10 and then 5 more";
   str.append(str2);                       // "Writing "
  str.append(str3,6,3);                   // "10 "
  str.append("dots are cool",5);          // "dots "
  str.append("here: ");                   // "here: "
  str.append(10u,'.');                    // ".........."
//  str.append(str3.begin()+8,str3.end());  // " and then 5 more"
//  str.append<int>(5,0x2E);                // "....."
  std::cout << str << '\n';

  std::string a = "Robert ";
  std::string b = "is not ";
  char *c = "superb ";
  char d = 'd';
  a.append(b); /* a is “Robert is not ” */
  cout<<a<<endl;
  a = "Robert ";
  a.append(b, 0, 3); /* a is “Robert is ” */
  a.append(c, 6); /* a is “Robert is superb” */
  cout<<a<<endl;
  a = "Robert ";
  a.append(5, d); /* a is “Robert ddddd” */
  cout<<a<<endl;
  cout << "........... some string stuff ..............." << '\n';


}
