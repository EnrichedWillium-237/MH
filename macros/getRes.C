# include "TFile.h"
# include "TH1.h"
# include "TH2.h"
# include <iostream>

using namespace std;

static const int ncbins = 11;
static const int cmin[] = {0,  5, 10, 15, 20, 25, 30, 35, 40, 50, 60};
static const int cmax[] = {5, 10, 15, 20, 25, 30, 35, 40, 50, 60, 70};

TH2D * res1;
TH2D * resw1;
TH2D * resep1;
TH2D * rescnt1;
TH2D * res12;
TH2D * resw12;
TH2D * resep12;
TH2D * rescnt12;
TH2D * res2;
TH2D * resw2;
TH2D * resep2;
TH2D * rescnt2;

TFile * fin;
TFile * fout;
TDirectory * td;
TDirectory * tdcent;

void getRes() {

    fin = new TFile("../MH.root","read");
    fout = new TFile("Resolutions.root","recreate");
    td = (TDirectory *) fout->mkdir("default");
    td->cd();

    for (int cbin = 0; cbin<ncbins; cbin++) {
        res1 = (TH2D *) fin->Get(Form("vnanalyzer/Resolutions/%d_%d/res1",cmin[cbin],cmax[cbin]));
        resw1 = (TH2D *) fin->Get(Form("vnanalyzer/Resolutions/%d_%d/resw1",cmin[cbin],cmax[cbin]));
        resep1 = (TH2D *) fin->Get(Form("vnanalyzer/Resolutions/%d_%d/resep1",cmin[cbin],cmax[cbin]));
        rescnt1 = (TH2D *) fin->Get(Form("vnanalyzer/Resolutions/%d_%d/rescnt1",cmin[cbin],cmax[cbin]));
        res12 = (TH2D *) fin->Get(Form("vnanalyzer/Resolutions/%d_%d/res12",cmin[cbin],cmax[cbin]));
        resw12 = (TH2D *) fin->Get(Form("vnanalyzer/Resolutions/%d_%d/resw12",cmin[cbin],cmax[cbin]));
        resep12 = (TH2D *) fin->Get(Form("vnanalyzer/Resolutions/%d_%d/resep12",cmin[cbin],cmax[cbin]));
        rescnt12 = (TH2D *) fin->Get(Form("vnanalyzer/Resolutions/%d_%d/rescnt12",cmin[cbin],cmax[cbin]));
        res2 = (TH2D *) fin->Get(Form("vnanalyzer/Resolutions/%d_%d/res2",cmin[cbin],cmax[cbin]));
        resw2 = (TH2D *) fin->Get(Form("vnanalyzer/Resolutions/%d_%d/resw2",cmin[cbin],cmax[cbin]));
        resep2 = (TH2D *) fin->Get(Form("vnanalyzer/Resolutions/%d_%d/resep2",cmin[cbin],cmax[cbin]));
        rescnt2 = (TH2D *) fin->Get(Form("vnanalyzer/Resolutions/%d_%d/rescnt2",cmin[cbin],cmax[cbin]));

        tdcent = (TDirectory *) td->mkdir(Form("%d_%d",cmin[cbin],cmax[cbin]));
        tdcent->cd();

        res1->Write();
        resw1->Write();
        resep1->Write();
        rescnt1->Write();
        res12->Write();
        resw12->Write();
        resep12->Write();
        rescnt12->Write();
        res2->Write();
        resw2->Write();
        resep2->Write();
        rescnt2->Write();

        res1->Delete();
        resw1->Delete();
        resep1->Delete();
        rescnt1->Delete();
        res12->Delete();
        resw12->Delete();
        resep12->Delete();
        rescnt12->Delete();
        res2->Delete();
        resw2->Delete();
        resep2->Delete();
        rescnt2->Delete();
    }

    cout << "First- and second-order resolutions written out to Resolutions.root... " << endl;

    //fout->Close();
    //fin->Close();

}
