# include "TDirectory.h"
# include "TFile.h"
# include "TH1.h"
# include <iostream>

using namespace std;

static const int ncbins = 14;
static const int cmin[]={0, 5,10,15,20,25,30,35,40,50,60,  0,20, 60};
static const int cmax[]={5,10,15,20,25,30,35,40,50,60,70, 20,60,100};

TFile * fout;
TDirectory * dirOdd;
TDirectory * dirEven;
TH1D * v1oddErr[ncbins];
TH1D * v1evenErr[ncbins];

void getSystematics() {

    double oddErr[ncbins] = {0.14, 0.14, 0.12, 0.11, 0.10, 0.09, 0.07, 0.06, 0.06, 0.05, 0.05, 0.13, 0.07};
    double evenErr[ncbins] = {0.11, 0.09, 0.08, 0.08, 0.08, 0.07, 0.09, 0.09, 0.07, 0.09, 0.23, 0.06, 0.08};

    fout = new TFile("data_systematics.root","recreate");
    dirOdd = (TDirectory *) fout->mkdir("odd_errors");
    dirEven = (TDirectory *) fout->mkdir("even_errors");

    for (int i = 0; i<ncbins; i++) {
        dirOdd->cd();
        v1oddErr[i] = new TH1D(Form("odd_%d_%d",cmin[i],cmax[i]), "", 1, 0, 1);
        v1oddErr[i]->SetBinContent(1, oddErr[i]);
        v1oddErr[i]->Write();

        dirEven->cd();
        v1evenErr[i] = new TH1D(Form("even_%d_%d",cmin[i],cmax[i]), "", 1, 0, 1);
        v1evenErr[i]->SetBinContent(1, evenErr[i]);
        v1evenErr[i]->Write();
    }

    fout->Close();

}
