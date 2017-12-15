# include "TFile.h"
# include "TGraphErrors.h"
# include "TCanvas.h"
# include "TF1.h"
# include "TH1.h"
# include "TH2.h"
# include "TLatex.h"
# include "TLegend.h"
# include "TMath.h"
# include "TPaveText.h"
# include "TStyle.h"
# include <fstream>
# include <iostream>

# include "style.h"

using namespace std;

static const int nptbins = 18;
static const double ptbins[] = {0.30,  0.40,  0.50,  0.60,  0.80,  1.00,  1.25,  1.50,  2.00,  2.50,  3.00,
                     3.50,  4.00,  5.00,  6.00,  7.00,  8.00,  10.00,  12.00};
static const int netabins = 12;
static const double etabins[] = {-2.4, -2.0, -1.6, -1.2, -0.8, -0.4,  0.0,
                     0.4,  0.8,  1.2,  1.6, 2.0,  2.4};
static const int ncbins = 13;
static const int cmin[] = {0,  5, 10, 15, 20, 25, 30, 35, 40, 50, 60,  0, 30,  50};
static const int cmax[] = {5, 10, 15, 20, 25, 30, 35, 40, 50, 60, 70, 30, 50, 100};
static const int nanals = 14;
enum AnalType {
    N1ASUB2,     N1ASUB3,     N1BSUB2,   N1BSUB3,   N112ASUB2,   N112ASUB3,   N123ASUB2, N123ASUB3,
    N1MCm22SUB3, N1MCp22SUB3, N2SUB2,    N2SUB3,    N3SUB2,      N3SUB3,      LAST
};
string AnalNames[] = {
    "N1ASUB2",     "N1ASUB3",     "N1BSUB2",   "N1BSUB3",   "N112ASUB2",   "N112ASUB3",   "N123ASUB2", "N123ASUB3",
    "N1MCm22SUB3", "N1MCp22SUB3", "N2SUB2",    "N2SUB3",    "N3SUB2",      "N3SUB3",      "LAST"
};

static const bool gridlines = false;

TH1D * vnA_eta[nanals][ncbins];
TH1D * vnB_eta[nanals][ncbins];
TH1D * vnAB_eta[nanals][ncbins];
TH1D * N1SUB2_eta[ncbins];
TH1D * N1SUB3_eta[ncbins];

TH1D * vnA_pt[nanals][ncbins];
TH1D * vnB_pt[nanals][ncbins];
TH1D * vnAB_pt[nanals][ncbins];
TH1D * N1SUB2_pt[ncbins];
TH1D * N1SUB3_pt[ncbins];

// symeterized vn
TH1D * N1SUB2_Sym_eta[ncbins];
TH1D * N1SUB3_Sym_eta[ncbins];
TH1D * N1MC22SUB3_Sym_eta[ncbins];

TH1D * N1SUB2_RelErr_eta[ncbins];
TH1D * N1SUB3_RelErr_eta[ncbins];
TH1D * N1MC22SUB3_RelErr_eta[ncbins];

TH1D * systN1SUB2_eta;
TH1D * systN1SUB3_eta;
TH1D * systN1MC22SUB3_eta;

TH1D * N1SUB2_Sym_pt[ncbins];
TH1D * N1SUB3_Sym_pt[ncbins];
TH1D * N1MC22SUB3_Sym_pt[ncbins];

TH1D * N1SUB2_RelErr_pt[ncbins];
TH1D * N1SUB3_RelErr_pt[ncbins];
TH1D * N1MC22SUB3_RelErr_pt[ncbins];

TH1D * systN1SUB2_pt;
TH1D * systN1SUB3_pt;
TH1D * systN1MC22SUB3_pt;

TF1 * fit_N1SUB2_RelErr_eta[ncbins];
TF1 * fit_N1SUB3_RelErr_eta[ncbins];
TF1 * fit_N1MC22SUB3_RelErr_eta[ncbins];

TF1 * fit_N1SUB2_RelErr_pt[ncbins];
TF1 * fit_N1SUB3_RelErr_pt[ncbins];
TF1 * fit_N1MC22SUB3_RelErr_pt[ncbins];

TFile * tfin;
TFile * tfout;

void symStudy()
{

    TH1::SetDefaultSumw2();

    for (int anal = 0; anal<nanals; anal++) {
        for (int cbin = 0; cbin<ncbins; cbin++) {
            string htag = Form("_%s_%d_%d",AnalNames[anal].data(),cmin[cbin],cmax[cbin]);
            vnA_eta[anal][cbin]  = new TH1D(Form("vnA_eta_%s",htag.data()), "", netabins, etabins);
            vnB_eta[anal][cbin]  = new TH1D(Form("vnB_eta_%s",htag.data()), "", netabins, etabins);
            vnAB_eta[anal][cbin] = new TH1D(Form("vnAB_eta_%s",htag.data()), "", netabins, etabins);
        }
    }
    for (int cbin = 0; cbin<ncbins; cbin++) {
        N1SUB2_Sym_eta[cbin] = new TH1D(Form("N1SUB2_Sym_eta_%d_%d",cmin[cbin],cmax[cbin]), "", netabins, etabins);
        N1SUB3_Sym_eta[cbin] = new TH1D(Form("N1SUB3_Sym_eta_%d_%d",cmin[cbin],cmax[cbin]), "", netabins, etabins);
        N1MC22SUB3_Sym_eta[cbin] = new TH1D(Form("N1MC22SUB3_Sym_eta_%d_%d",cmin[cbin],cmax[cbin]), "", netabins, etabins);

        N1SUB2_RelErr_eta[cbin] = new TH1D(Form("N1SUB2_RelErr_eta_%d_%d",cmin[cbin],cmax[cbin]), "", netabins, etabins);
        N1SUB3_RelErr_eta[cbin] = new TH1D(Form("N1SUB3_RelErr_eta_%d_%d",cmin[cbin],cmax[cbin]), "", netabins, etabins);
        N1MC22SUB3_RelErr_eta[cbin] = new TH1D(Form("N1MC22SUB3_RelErr_eta_%d_%d",cmin[cbin],cmax[cbin]), "", netabins, etabins);

        N1SUB2_Sym_pt[cbin] = new TH1D(Form("N1SUB2_Sym_pt_%d_%d",cmin[cbin],cmax[cbin]), "", nptbins, ptbins);
        N1SUB3_Sym_pt[cbin] = new TH1D(Form("N1SUB3_Sym_pt_%d_%d",cmin[cbin],cmax[cbin]), "", nptbins, ptbins);
        N1MC22SUB3_Sym_pt[cbin] = new TH1D(Form("N1MC22SUB3_Sym_pt_%d_%d",cmin[cbin],cmax[cbin]), "", nptbins, ptbins);

        N1SUB2_RelErr_pt[cbin] = new TH1D(Form("N1SUB2_RelErr_pt_%d_%d",cmin[cbin],cmax[cbin]), "", nptbins, ptbins);
        N1SUB3_RelErr_pt[cbin] = new TH1D(Form("N1SUB3_RelErr_pt_%d_%d",cmin[cbin],cmax[cbin]), "", nptbins, ptbins);
        N1MC22SUB3_RelErr_pt[cbin] = new TH1D(Form("N1MC22SUB3_RelErr_pt_%d_%d",cmin[cbin],cmax[cbin]), "", nptbins, ptbins);
    }
    systN1SUB2_eta = new TH1D("systN1SUB2_eta", "", ncbins, 0, ncbins);
    systN1SUB3_eta = new TH1D("systN1SUB3_eta", "", ncbins, 0, ncbins);
    systN1MC22SUB3_eta = new TH1D("systN1MC22SUB3_eta", "", ncbins, 0, ncbins);

    systN1SUB2_pt = new TH1D("systN1SUB2_pt", "", ncbins, 0, ncbins);
    systN1SUB3_pt = new TH1D("systN1SUB3_pt", "", ncbins, 0, ncbins);
    systN1MC22SUB3_pt = new TH1D("systN1MC22SUB3_pt", "", ncbins, 0, ncbins);

    string prevname = "";
    for (int anal = 0; anal<nanals; anal++) {
        for (int ebin = 0; ebin<netabins; ebin++) {
            prevname = Form("figures/figures_useTight_%1.1f_%1.1f/%s/data/integral.dat",etabins[ebin],etabins[ebin+1],AnalNames[anal].data());
            if (prevname.length()>1) {
                int centmin[40];
                int centmax[40];
                double y[40];
                double stat[40];
                FILE * fin = fopen(prevname.data(),"r");
                char buf[80];
                int cbin = 0;
                while (fgets(buf,80,fin)!=NULL) {
                    sscanf(buf,"%d\t%d\t%lf\t%lf\n",&centmin[cbin],&centmax[cbin],&y[cbin],&stat[cbin]);
                    vnAB_eta[anal][cbin]->SetBinContent(ebin+1,y[cbin]);
                    vnAB_eta[anal][cbin]->SetBinError(ebin+1,stat[cbin]);
                    ++cbin;
                }
                fclose(fin);
            }

            prevname = Form("figures/figures_useTight_%1.1f_%1.1f/%s/data/integralA.dat",etabins[ebin],etabins[ebin+1],AnalNames[anal].data());
            if (prevname.length()>1) {
                int centmin[40];
                int centmax[40];
                double y[40];
                double stat[40];
                FILE * fin = fopen(prevname.data(),"r");
                char buf[80];
                int cbin = 0;
                while (fgets(buf,80,fin)!=NULL) {
                    sscanf(buf,"%d\t%d\t%lf\t%lf\n",&centmin[cbin],&centmax[cbin],&y[cbin],&stat[cbin]);
                    vnA_eta[anal][cbin]->SetBinContent(ebin+1,y[cbin]);
                    vnA_eta[anal][cbin]->SetBinError(ebin+1,stat[cbin]);
                    ++cbin;
                }
                fclose(fin);
            }

            prevname = Form("figures/figures_useTight_%1.1f_%1.1f/%s/data/integralB.dat",etabins[ebin],etabins[ebin+1],AnalNames[anal].data());
            if (prevname.length()>1) {
                int centmin[40];
                int centmax[40];
                double y[40];
                double stat[40];
                FILE * fin = fopen(prevname.data(),"r");
                char buf[80];
                int cbin = 0;
                while (fgets(buf,80,fin)!=NULL) {
                    sscanf(buf,"%d\t%d\t%lf\t%lf\n",&centmin[cbin],&centmax[cbin],&y[cbin],&stat[cbin]);
                    vnB_eta[anal][cbin]->SetBinContent(ebin+1,y[cbin]);
                    vnB_eta[anal][cbin]->SetBinError(ebin+1,stat[cbin]);
                    ++cbin;
                }
                fclose(fin);
            }
        }

        tfin = new TFile(Form("results/results_useTight_-2.4_2.4/%s.root",AnalNames[anal].data()));
        for (int cbin = 0; cbin<ncbins; cbin++) {
            vnA_pt[anal][cbin]  = (TH1D *) tfin->Get(Form("%d_%d/vnA",cmin[cbin],cmax[cbin]));
            vnB_pt[anal][cbin]  = (TH1D *) tfin->Get(Form("%d_%d/vnB",cmin[cbin],cmax[cbin]));
            vnAB_pt[anal][cbin] = (TH1D *) tfin->Get(Form("%d_%d/vnAB",cmin[cbin],cmax[cbin]));
        }
    }


    //-- average N1SUB2 and N1SUB3
    for (int cbin = 0; cbin<ncbins; cbin++) {
        N1SUB2_eta[cbin] = (TH1D *) vnAB_eta[N1ASUB2][cbin]->Clone(Form("N1SUB2_eta_%d_%d",cmin[cbin],cmax[cbin]));
        N1SUB2_pt[cbin] = (TH1D *) vnAB_pt[N1ASUB2][cbin]->Clone(Form("N1SUB2_pt_%d_%d",cmin[cbin],cmax[cbin]));

        N1SUB3_eta[cbin] = (TH1D *) vnAB_eta[N1ASUB3][cbin]->Clone(Form("N1SUB3_eta_%d_%d",cmin[cbin],cmax[cbin]));
        N1SUB3_eta[cbin]->Add(vnAB_eta[N1BSUB3][cbin]);
        N1SUB3_eta[cbin]->Scale(0.5);
        N1SUB3_pt[cbin] = (TH1D *) vnAB_pt[N1ASUB3][cbin]->Clone(Form("N1SUB3_pt_%d_%d",cmin[cbin],cmax[cbin]));
        N1SUB3_pt[cbin]->Add(vnAB_pt[N1BSUB3][cbin]);
        N1SUB3_pt[cbin]->Scale(0.5);

        N1MC22SUB3_Sym_eta[cbin] = (TH1D *) vnAB_eta[N1MCp22SUB3][cbin]->Clone(Form("N1MC22SUB3_Sym_eta_%d_%d",cmin[cbin],cmax[cbin]));
        N1MC22SUB3_Sym_pt[cbin] = (TH1D *) vnAB_pt[N1MCp22SUB3][cbin]->Clone(Form("N1MC22SUB3_Sym_pt_%d_%d",cmin[cbin],cmax[cbin]));
    }


    //-- symmeterize v1
    for (int cbin = 0; cbin<ncbins; cbin++) {
        for (int ebin = 0; ebin<netabins; ebin++) {
            double pos = N1SUB2_eta[cbin]->GetBinContent(netabins - ebin);
            double neg = N1SUB2_eta[cbin]->GetBinContent(ebin + 1);
            double posErr = N1SUB2_eta[cbin]->GetBinError(netabins - ebin);
            double negErr = N1SUB2_eta[cbin]->GetBinError(ebin + 1);
            double vnsym = 0.5*(pos - neg);
            double vnsymErr = 0.5*sqrt( posErr*posErr + negErr*negErr );
            N1SUB2_Sym_eta[cbin]->SetBinContent(netabins - ebin, vnsym);
            N1SUB2_Sym_eta[cbin]->SetBinError(netabins - ebin, vnsymErr);

            double rel = (fabs(pos) - fabs(neg)) / (fabs(pos) + fabs(neg));
            double relErr = pow(posErr/pos,2) + pow(negErr/neg,2) - 2*fabs((posErr/pos)*(negErr/neg));
            relErr = rel * sqrt( relErr );
            N1SUB2_RelErr_eta[cbin]->SetBinContent(netabins - ebin, rel);
            N1SUB2_RelErr_eta[cbin]->SetBinError(netabins - ebin, relErr);
        }
        for (int ebin = 0; ebin<netabins; ebin++) {
            double pos = N1SUB3_eta[cbin]->GetBinContent(netabins - ebin);
            double neg = N1SUB3_eta[cbin]->GetBinContent(ebin + 1);
            double posErr = N1SUB3_eta[cbin]->GetBinError(netabins - ebin);
            double negErr = N1SUB3_eta[cbin]->GetBinError(ebin + 1);
            double vnsym = 0.5*(pos - neg);
            double vnsymErr = 0.5*sqrt( posErr*posErr + negErr*negErr );
            N1SUB3_Sym_eta[cbin]->SetBinContent(netabins - ebin, vnsym);
            N1SUB3_Sym_eta[cbin]->SetBinError(netabins - ebin, vnsymErr);

            double rel = (fabs(pos) - fabs(neg)) / (fabs(pos) + fabs(neg));
            double relErr = pow(posErr/pos,2) + pow(negErr/neg,2) - 2*fabs((posErr/pos)*(negErr/neg));
            relErr = rel * sqrt( relErr );
            N1SUB3_RelErr_eta[cbin]->SetBinContent(netabins - ebin, rel);
            N1SUB3_RelErr_eta[cbin]->SetBinError(netabins - ebin, relErr);
        }

        for (int pbin = 0; pbin<nptbins; pbin++) {
            double pos = vnA_pt[N1MCp22SUB3][cbin]->GetBinContent(pbin+1);
            double neg = vnB_pt[N1MCp22SUB3][cbin]->GetBinContent(pbin+1);
            double posErr = vnA_pt[N1MCp22SUB3][cbin]->GetBinError(pbin+1);
            double negErr = vnB_pt[N1MCp22SUB3][cbin]->GetBinError(pbin+1);
            double rel = (fabs(pos) - fabs(neg)) / (fabs(pos) + fabs(neg));
            double relErr = pow(posErr/pos,2) + pow(negErr/neg,2) - 2*fabs((posErr/pos)*(negErr/neg));
            relErr = rel * sqrt( relErr );
            N1MC22SUB3_RelErr_pt[cbin]->SetBinContent(pbin+1, rel);
            N1MC22SUB3_RelErr_pt[cbin]->SetBinError(pbin+1, relErr);
        }

        // get percent error
        fit_N1SUB2_RelErr_eta[cbin] = new TF1(Form("fit_N1SUB2_RelErr_eta_%d",cbin), "pol0", 0, 2.4);
        N1SUB2_RelErr_eta[cbin]->Fit(fit_N1SUB2_RelErr_eta[cbin],"QR");
        systN1SUB2_eta->SetBinContent(cbin+1, fit_N1SUB2_RelErr_eta[cbin]->GetParameter(0));
        systN1SUB2_eta->SetBinError(cbin+1, fit_N1SUB2_RelErr_eta[cbin]->GetChisquare());

        fit_N1SUB3_RelErr_eta[cbin] = new TF1(Form("fit_N1SUB3_RelErr_eta_%d",cbin), "pol0", 0, 2.4);
        N1SUB3_RelErr_eta[cbin]->Fit(fit_N1SUB3_RelErr_eta[cbin],"QR");
        systN1SUB3_eta->SetBinContent(cbin+1, fit_N1SUB3_RelErr_eta[cbin]->GetParameter(0));
        systN1SUB3_eta->SetBinError(cbin+1, fit_N1SUB3_RelErr_eta[cbin]->GetChisquare());

        fit_N1MC22SUB3_RelErr_pt[cbin] = new TF1(Form("fit_N1MC22SUB3_RelErr_pt_%d",cbin), "pol0", 0, 12);
        N1MC22SUB3_RelErr_pt[cbin]->Fit(fit_N1MC22SUB3_RelErr_pt[cbin],"QR");
        systN1MC22SUB3_pt->SetBinContent(cbin+1, fit_N1MC22SUB3_RelErr_pt[cbin]->GetParameter(0));
        systN1MC22SUB3_pt->SetBinError(cbin+1, fit_N1MC22SUB3_RelErr_pt[cbin]->GetChisquare());
    }




    //-- write out to file

    if (!fopen("figures/integralVN","r")) system("mkdir figures/integralVN");
    if (!fopen("figures/integralVN/data","r")) system("mkdir figures/integralVN/data");

    tfout = new TFile("figures/integralVN/data/symmetrizedVN.root","recreate");
    tfout->cd();
    // TDirectory * symdir = (TDirectory *) tfout->mkdir("symmeterizedVN");
    // symdir->cd();
    systN1SUB2_eta->Write();
    systN1SUB3_eta->Write();
    systN1MC22SUB3_eta->Write();
    systN1SUB2_pt->Write();
    systN1SUB3_pt->Write();
    systN1MC22SUB3_pt->Write();
    for (int cbin = 0; cbin<ncbins; cbin++) {
        TDirectory * cdir = (TDirectory *) tfout->mkdir(Form("%d_%d",cmin[cbin],cmax[cbin]));
        cdir->cd();
        N1SUB2_Sym_eta[cbin]->Write();
        N1SUB3_Sym_eta[cbin]->Write();
        N1MC22SUB3_Sym_eta[cbin]->Write();
        N1SUB2_RelErr_eta[cbin]->Write();
        N1SUB3_RelErr_eta[cbin]->Write();
        N1MC22SUB3_RelErr_eta[cbin]->Write();
        N1SUB2_Sym_pt[cbin]->Write();
        N1SUB3_Sym_pt[cbin]->Write();
        N1MC22SUB3_Sym_pt[cbin]->Write();
        N1SUB2_RelErr_pt[cbin]->Write();
        N1SUB3_RelErr_pt[cbin]->Write();
        N1MC22SUB3_RelErr_pt[cbin]->Write();
        fit_N1SUB2_RelErr_eta[cbin]->Write();
        fit_N1SUB3_RelErr_eta[cbin]->Write();
        // fit_N1MC22SUB3_RelErr_eta[cbin]->Write();
        // fit_N1SUB2_RelErr_pt[cbin]->Write();
        //fit_N1SUB3_RelErr_pt[cbin]->Write();
        fit_N1MC22SUB3_RelErr_pt[cbin]->Write();
    }
    tfout->Close();


    //-- make plots ---------------//

    TLine * lnEta = new TLine(-2.4, 0.0, 2.4, 0.0);
    TLine * lnPt  = new TLine(0.0, 0.0, 12.0, 0.0);

    if (!fopen("figures/integralVN/systematics","r")) system("mkdir figures/integralVN/systematics");


    TCanvas * cN1SUB2_eta = new TCanvas("cN1SUB2_eta", "cN1SUB2_eta", 1300, 650);
    cN1SUB2_eta->Divide(5,2,0,0);
    for (int cbin = 0; cbin<10; cbin++) {
        TPad * padN1SUB2_eta = (TPad *) cN1SUB2_eta->cd(cbin+1);
        if (gridlines) padN1SUB2_eta->SetGrid();
        if (cbin == 4 || cbin == 9) padN1SUB2_eta->SetRightMargin(0.02);
        if (cbin <= 4) padN1SUB2_eta->SetTopMargin(0.1);
        if (cbin > 4) padN1SUB2_eta->SetBottomMargin(0.25);

        TH1D * hN1SUB2_eta = new TH1D(Form("hN1SUB2_eta_%d",cbin), "", 50, 0, 2.6);
        hN1SUB2_eta->SetXTitle("|#eta|");
        hN1SUB2_eta->SetYTitle("");
        hN1SUB2_eta->GetXaxis()->CenterTitle();
        hN1SUB2_eta->GetYaxis()->CenterTitle();
        hN1SUB2_eta->GetYaxis()->SetRangeUser(-0.2, 0.2);
        hN1SUB2_eta->GetYaxis()->SetNdivisions(509);
        hN1SUB2_eta->GetYaxis()->SetTitleSize(0.07);
        hN1SUB2_eta->GetYaxis()->SetLabelSize(0.05);
        hN1SUB2_eta->GetYaxis()->SetTitleOffset(1.20);
        hN1SUB2_eta->GetYaxis()->SetLabelOffset(0.010);
        if (cbin == 5) {
            hN1SUB2_eta->GetXaxis()->SetTitleSize(0.07);
            hN1SUB2_eta->GetXaxis()->SetLabelSize(0.05);
            hN1SUB2_eta->GetXaxis()->SetTitleOffset(1.00);
            hN1SUB2_eta->GetXaxis()->SetLabelOffset(0.019);
        }
        if (cbin >= 6) {
            hN1SUB2_eta->GetXaxis()->SetTitleSize(0.08);
            hN1SUB2_eta->GetXaxis()->SetLabelSize(0.06);
            hN1SUB2_eta->GetXaxis()->SetTitleOffset(0.83);
            hN1SUB2_eta->GetXaxis()->SetLabelOffset(0.011);
        }
        hN1SUB2_eta->Draw();

        N1SUB2_RelErr_eta[cbin]->Draw("same");

        TPaveText * txN1SUB2_eta_cent;
        if (cbin == 0) txN1SUB2_eta_cent = new TPaveText(0.80, 0.77, 0.95, 0.86, "NDC");
        else if (cbin >= 1 && cbin <=4) txN1SUB2_eta_cent = new TPaveText(0.40, 0.77, 0.60, 0.86, "NDC");
        else if (cbin == 5) txN1SUB2_eta_cent = new TPaveText(0.50, 0.87, 0.70, 0.97, "NDC");
        else txN1SUB2_eta_cent = new TPaveText(0.40, 0.87, 0.60, 0.97, "NDC");
        SetTPaveTxt(txN1SUB2_eta_cent, 17);
        txN1SUB2_eta_cent->AddText(Form("%d - %d%%",cmin[cbin],cmax[cbin]));
        txN1SUB2_eta_cent->Draw();

        TPaveText * txtxN1SUB2_eta_fit;
        if (cbin == 0) txtxN1SUB2_eta_fit = new TPaveText(0.23, 0.03, 0.60, 0.12, "NDC");
        else if (cbin >= 1 && cbin <=4) txtxN1SUB2_eta_fit = new TPaveText(0.04, 0.03, 0.49, 0.12, "NDC");
        else if (cbin == 5) txtxN1SUB2_eta_fit = new TPaveText(0.23, 0.29, 0.60, 0.35, "NDC");
        else txtxN1SUB2_eta_fit = new TPaveText(0.04, 0.29, 0.49, 0.35, "NDC");
        SetTPaveTxt(txtxN1SUB2_eta_fit, 16);
        txtxN1SUB2_eta_fit->AddText(Form("mean = %1.4f",systN1SUB2_eta->GetBinContent(cbin+1)));
        txtxN1SUB2_eta_fit->Draw();
    }
    cN1SUB2_eta->cd(1);
    TPaveText * txN1SUB2_eta_CMS = new TPaveText(0.19, 0.91, 0.66, 1.0,"NDC");
    SetTPaveTxt(txN1SUB2_eta_CMS, 18);
    txN1SUB2_eta_CMS->AddText("#bf{CMS} #it{Preliminary}");
    txN1SUB2_eta_CMS->Draw();

    TPaveText * txN1SUB2_eta_label = new TPaveText(0.23, 0.67, 0.60, 0.85, "NDC");
    SetTPaveTxt(txN1SUB2_eta_label, 16);
    txN1SUB2_eta_label->AddText("PbPb #sqrt{s_{NN}} = 5.02 TeV");
    txN1SUB2_eta_label->AddText("0.3 < p_{T} < 3.0 GeV/c");
    txN1SUB2_eta_label->Draw();

    cN1SUB2_eta->cd(6);
    TPaveText * txN1SUB2_eta_label2 = new TPaveText(0.22, 0.36, 0.72, 0.54, "NDC");
    SetTPaveTxt(txN1SUB2_eta_label2, 16);
    txN1SUB2_eta_label2->AddText("#frac{|v_{1}^{odd}(+#eta)| - |v_{1}^{odd}(-#eta)|}{|v_{1}^{odd}(+#eta)| + |v_{1}^{odd}(-#eta)|}");
    txN1SUB2_eta_label2->Draw();

    cN1SUB2_eta->Print("figures/integralVN/systematics/symmetry_N1SUB2_eta.pdf","pdf");



    TCanvas * cN1SUB3_eta = new TCanvas("cN1SUB3_eta", "cN1SUB3_eta", 1300, 650);
    cN1SUB3_eta->Divide(5,2,0,0);
    for (int cbin = 0; cbin<10; cbin++) {
        TPad * padN1SUB3_eta = (TPad *) cN1SUB3_eta->cd(cbin+1);
        if (gridlines) padN1SUB3_eta->SetGrid();
        if (cbin == 4 || cbin == 9) padN1SUB3_eta->SetRightMargin(0.02);
        if (cbin <= 4) padN1SUB3_eta->SetTopMargin(0.1);
        if (cbin > 4) padN1SUB3_eta->SetBottomMargin(0.25);

        TH1D * hN1SUB3_eta = new TH1D(Form("hN1SUB3_eta_%d",cbin), "", 50, 0, 2.6);
        hN1SUB3_eta->SetXTitle("|#eta|");
        hN1SUB3_eta->SetYTitle("");
        hN1SUB3_eta->GetXaxis()->CenterTitle();
        hN1SUB3_eta->GetYaxis()->CenterTitle();
        hN1SUB3_eta->GetYaxis()->SetRangeUser(-0.2, 0.2);
        hN1SUB3_eta->GetYaxis()->SetNdivisions(509);
        hN1SUB3_eta->GetYaxis()->SetTitleSize(0.07);
        hN1SUB3_eta->GetYaxis()->SetLabelSize(0.05);
        hN1SUB3_eta->GetYaxis()->SetTitleOffset(1.20);
        hN1SUB3_eta->GetYaxis()->SetLabelOffset(0.010);
        if (cbin == 5) {
            hN1SUB3_eta->GetXaxis()->SetTitleSize(0.07);
            hN1SUB3_eta->GetXaxis()->SetLabelSize(0.05);
            hN1SUB3_eta->GetXaxis()->SetTitleOffset(1.00);
            hN1SUB3_eta->GetXaxis()->SetLabelOffset(0.019);
        }
        if (cbin >= 6) {
            hN1SUB3_eta->GetXaxis()->SetTitleSize(0.08);
            hN1SUB3_eta->GetXaxis()->SetLabelSize(0.06);
            hN1SUB3_eta->GetXaxis()->SetTitleOffset(0.83);
            hN1SUB3_eta->GetXaxis()->SetLabelOffset(0.011);
        }
        hN1SUB3_eta->Draw();

        N1SUB3_RelErr_eta[cbin]->Draw("same");

        TPaveText * txN1SUB3_eta_cent;
        if (cbin == 0) txN1SUB3_eta_cent = new TPaveText(0.80, 0.77, 0.95, 0.86, "NDC");
        else if (cbin >= 1 && cbin <=4) txN1SUB3_eta_cent = new TPaveText(0.40, 0.77, 0.60, 0.86, "NDC");
        else if (cbin == 5) txN1SUB3_eta_cent = new TPaveText(0.50, 0.87, 0.70, 0.97, "NDC");
        else txN1SUB3_eta_cent = new TPaveText(0.40, 0.87, 0.60, 0.97, "NDC");
        SetTPaveTxt(txN1SUB3_eta_cent, 17);
        txN1SUB3_eta_cent->AddText(Form("%d - %d%%",cmin[cbin],cmax[cbin]));
        txN1SUB3_eta_cent->Draw();

        TPaveText * txtxN1SUB3_eta_fit;
        if (cbin == 0) txtxN1SUB3_eta_fit = new TPaveText(0.23, 0.03, 0.60, 0.12, "NDC");
        else if (cbin >= 1 && cbin <=4) txtxN1SUB3_eta_fit = new TPaveText(0.04, 0.03, 0.49, 0.12, "NDC");
        else if (cbin == 5) txtxN1SUB3_eta_fit = new TPaveText(0.23, 0.29, 0.60, 0.35, "NDC");
        else txtxN1SUB3_eta_fit = new TPaveText(0.04, 0.29, 0.49, 0.35, "NDC");
        SetTPaveTxt(txtxN1SUB3_eta_fit, 16);
        txtxN1SUB3_eta_fit->AddText(Form("mean = %1.4f",systN1SUB3_eta->GetBinContent(cbin+1)));
        txtxN1SUB3_eta_fit->Draw();
    }
    cN1SUB3_eta->cd(1);
    TPaveText * txN1SUB3_eta_CMS = new TPaveText(0.19, 0.91, 0.66, 1.0,"NDC");
    SetTPaveTxt(txN1SUB3_eta_CMS, 18);
    txN1SUB3_eta_CMS->AddText("#bf{CMS} #it{Preliminary}");
    txN1SUB3_eta_CMS->Draw();

    TPaveText * txN1SUB3_eta_label = new TPaveText(0.23, 0.67, 0.60, 0.85, "NDC");
    SetTPaveTxt(txN1SUB3_eta_label, 16);
    txN1SUB3_eta_label->AddText("PbPb #sqrt{s_{NN}} = 5.02 TeV");
    txN1SUB3_eta_label->AddText("0.3 < p_{T} < 3.0 GeV/c");
    txN1SUB3_eta_label->Draw();

    cN1SUB3_eta->cd(6);
    TPaveText * txN1SUB3_eta_label2 = new TPaveText(0.22, 0.36, 0.72, 0.54, "NDC");
    SetTPaveTxt(txN1SUB3_eta_label2, 16);
    txN1SUB3_eta_label2->AddText("#frac{|v_{1}^{odd}(+#eta)| - |v_{1}^{odd}(-#eta)|}{|v_{1}^{odd}(+#eta)| + |v_{1}^{odd}(-#eta)|}");
    txN1SUB3_eta_label2->Draw();

    cN1SUB3_eta->Print("figures/integralVN/systematics/symmetry_N1SUB3_eta.pdf","pdf");



    TCanvas * cN1MC22SUB3_pt = new TCanvas("cN1MC22SUB3_pt", "cN1MC22SUB3_pt", 1300, 650);
    cN1MC22SUB3_pt->Divide(5,2,0,0);
    for (int cbin = 0; cbin<10; cbin++) {
        TPad * padN1MC22SUB3_pt = (TPad *) cN1MC22SUB3_pt->cd(cbin+1);
        if (gridlines) padN1MC22SUB3_pt->SetGrid();
        if (cbin == 4 || cbin == 9) padN1MC22SUB3_pt->SetRightMargin(0.02);
        if (cbin <= 4) padN1MC22SUB3_pt->SetTopMargin(0.1);
        if (cbin > 4) padN1MC22SUB3_pt->SetBottomMargin(0.25);

        TH1D * hN1MC22SUB3_pt = new TH1D(Form("hN1MC22SUB3_pt_%d",cbin), "", 50, 0, 12);
        hN1MC22SUB3_pt->SetXTitle("p_{T} (GeV/c)");
        hN1MC22SUB3_pt->SetYTitle("");
        hN1MC22SUB3_pt->GetXaxis()->CenterTitle();
        hN1MC22SUB3_pt->GetYaxis()->CenterTitle();
        hN1MC22SUB3_pt->GetYaxis()->SetRangeUser(-0.2, 0.2);
        hN1MC22SUB3_pt->GetYaxis()->SetNdivisions(509);
        hN1MC22SUB3_pt->GetYaxis()->SetTitleSize(0.07);
        hN1MC22SUB3_pt->GetYaxis()->SetLabelSize(0.05);
        hN1MC22SUB3_pt->GetYaxis()->SetTitleOffset(1.20);
        hN1MC22SUB3_pt->GetYaxis()->SetLabelOffset(0.010);
        if (cbin == 5) {
            hN1MC22SUB3_pt->GetXaxis()->SetTitleSize(0.07);
            hN1MC22SUB3_pt->GetXaxis()->SetLabelSize(0.05);
            hN1MC22SUB3_pt->GetXaxis()->SetTitleOffset(1.00);
            hN1MC22SUB3_pt->GetXaxis()->SetLabelOffset(0.019);
        }
        if (cbin >= 6) {
            hN1MC22SUB3_pt->GetXaxis()->SetTitleSize(0.08);
            hN1MC22SUB3_pt->GetXaxis()->SetLabelSize(0.06);
            hN1MC22SUB3_pt->GetXaxis()->SetTitleOffset(0.83);
            hN1MC22SUB3_pt->GetXaxis()->SetLabelOffset(0.011);
        }
        hN1MC22SUB3_pt->Draw();

        N1MC22SUB3_RelErr_pt[cbin]->Draw("same");

        TPaveText * txN1MC22SUB3_pt_cent;
        if (cbin == 0) txN1MC22SUB3_pt_cent = new TPaveText(0.80, 0.77, 0.95, 0.86, "NDC");
        else if (cbin >= 1 && cbin <=4) txN1MC22SUB3_pt_cent = new TPaveText(0.40, 0.77, 0.60, 0.86, "NDC");
        else if (cbin == 5) txN1MC22SUB3_pt_cent = new TPaveText(0.50, 0.87, 0.70, 0.97, "NDC");
        else txN1MC22SUB3_pt_cent = new TPaveText(0.40, 0.87, 0.60, 0.97, "NDC");
        SetTPaveTxt(txN1MC22SUB3_pt_cent, 17);
        txN1MC22SUB3_pt_cent->AddText(Form("%d - %d%%",cmin[cbin],cmax[cbin]));
        txN1MC22SUB3_pt_cent->Draw();

        TPaveText * txtxN1MC22SUB3_pt_fit;
        if (cbin == 0) txtxN1MC22SUB3_pt_fit = new TPaveText(0.23, 0.03, 0.60, 0.12, "NDC");
        else if (cbin >= 1 && cbin <=4) txtxN1MC22SUB3_pt_fit = new TPaveText(0.04, 0.03, 0.49, 0.12, "NDC");
        else if (cbin == 5) txtxN1MC22SUB3_pt_fit = new TPaveText(0.23, 0.29, 0.60, 0.35, "NDC");
        else txtxN1MC22SUB3_pt_fit = new TPaveText(0.04, 0.29, 0.49, 0.35, "NDC");
        SetTPaveTxt(txtxN1MC22SUB3_pt_fit, 16);
        txtxN1MC22SUB3_pt_fit->AddText(Form("mean = %1.4f",systN1MC22SUB3_pt->GetBinContent(cbin+1)));
        txtxN1MC22SUB3_pt_fit->Draw();
    }
    cN1MC22SUB3_pt->cd(1);
    TPaveText * txN1MC22SUB3_pt_CMS = new TPaveText(0.19, 0.91, 0.66, 1.0,"NDC");
    SetTPaveTxt(txN1MC22SUB3_pt_CMS, 18);
    txN1MC22SUB3_pt_CMS->AddText("#bf{CMS} #it{Preliminary}");
    txN1MC22SUB3_pt_CMS->Draw();

    TPaveText * txN1MC22SUB3_pt_label = new TPaveText(0.23, 0.67, 0.60, 0.85, "NDC");
    SetTPaveTxt(txN1MC22SUB3_pt_label, 16);
    txN1MC22SUB3_pt_label->AddText("PbPb #sqrt{s_{NN}} = 5.02 TeV");
    txN1MC22SUB3_pt_label->AddText("0.3 < p_{T} < 3.0 GeV/c");
    txN1MC22SUB3_pt_label->Draw();

    cN1MC22SUB3_pt->cd(6);
    TPaveText * txN1MC22SUB3_pt_label2 = new TPaveText(0.22, 0.36, 0.72, 0.54, "NDC");
    SetTPaveTxt(txN1MC22SUB3_pt_label2, 16);
    txN1MC22SUB3_pt_label2->AddText("#frac{|v_{1}^{even}(+#eta)| - |v_{1}^{even}(-#eta)|}{|v_{1}^{even}(+#eta)| + |v_{1}^{even}(-#eta)|}");
    txN1MC22SUB3_pt_label2->Draw();

    cN1MC22SUB3_pt->Print("figures/integralVN/systematics/symmetry_N1MC22SUB3_eta.pdf","pdf");


}
