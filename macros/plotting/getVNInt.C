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
static const int ncentbins = 11;
static const int centBins[] = {0, 5, 10, 15, 20, 25, 30, 35, 40, 50, 60, 70};
static const double centRefBins[] = {0, 5, 10, 15, 20, 25, 30, 35, 40, 50, 60, 70};
static const int ncbins = 14;
static const int cmin[] = {0,  5, 10, 15, 20, 25, 30, 35, 40, 50, 60,  0, 30,  50};
static const int cmax[] = {5, 10, 15, 20, 25, 30, 35, 40, 50, 60, 70, 30, 50, 100};
static const int nanals = 22;
enum AnalType {
    N1MCm22SUB3, N1MCm18SUB3, N1MCm14SUB3, N1MCm10SUB3, N1MCm06SUB3, N1MCm02SUB3,
    N1MCp22SUB3, N1MCp18SUB3, N1MCp14SUB3, N1MCp10SUB3, N1MCp06SUB3, N1MCp02SUB3,
    N112ASUB2,   N112ASUB3,   N123ASUB2,   N123ASUB3,   N1SUB2,      N1SUB3,
    N2SUB2,      N2SUB3,      N3SUB2,      N3SUB3,      LAST};
string AnalNames[] = {
    "N1MCm22SUB3", "N1MCm18SUB3", "N1MCm14SUB3", "N1MCm10SUB3", "N1MCm06SUB3", "N1MCm02SUB3",
    "N1MCp22SUB3", "N1MCp18SUB3", "N1MCp14SUB3", "N1MCp10SUB3", "N1MCp06SUB3", "N1MCp02SUB3",
    "N112ASUB2",   "N112ASUB3",   "N123ASUB2",   "N123ASUB3",   "N1SUB2",      "N1SUB3",
    "N2SUB2",      "N2SUB3",      "N3SUB2",      "N3SUB3",      "LAST"};

using namespace std;

//  track cut, analysis type, centbin
TH1D * vnA[3][nanals][ncbins];
TH1D * vnB[3][nanals][ncbins];
TH1D * vnAB[3][nanals][ncbins];

void getVNInt()
{

    bool processAll = false; // make true if you want to process the full data set

    for (int i = 0; i<3; i++) {
        for (int anal = 0; anal<nanals; anal++) {
            for (int cbin = 0; cbin<ncbins-1; cbin++) {
                string tcut = "";
                if (i == 0) tcut = "useTight";
                else if (i == 1) tcut = "useTightB";
                else tcut = "useLoose";
                string htag = Form("_%s_%s_%d_%d",AnalNames[anal].data(),tcut.data(),cmin[cbin],cmax[cbin]);
                vnA[i][anal][cbin] = new TH1D(Form("vnA_%s",htag.data()), "", netabins, etabins);
                vnB[i][anal][cbin] = new TH1D(Form("vnB_%s",htag.data()), "", netabins, etabins);
                vnAB[i][anal][cbin] = new TH1D(Form("vnAB_%s",htag.data()), "", netabins, etabins);
            }
        }
    }

    string prevname = "";

    // for (int i = 0; i<2; i++) {
    //     for (int anal = 0; anal<nanals; anal++) {
    //         if (!processAll) {
    //             if (anal == 16 || anal == 17 || anal == 18 || anal == 19) {
    //                 string tcut = "";
    //                 if (i == 0) tcut = "useTight";
    //                 else tcut = "useLoose";
    //                 for (int ebin = 0; ebin<netabins; ebin++) {
    //                     prevname = Form("../figures/figures_%s_%1.1f_%1.1f/%s/data/pT_integral.dat",tcut.data(),etabins[ebin],etabins[ebin+1],AnalNames[anal].data());
    //                     if (prevname.length()>1) {
    //                         int centmin[40];
    //                         int centmax[40];
    //                         double y[40];
    //                         double stat[40];
    //                         FILE * fin = fopen(prevname.data(),"r");
    //                         char buf[80];
    //                         int cbin = 0;
    //                         while (fgets(buf,80,fin)!=NULL) {
    //                             sscanf(buf,"%d\t%d\t%lf\t%lf\n",&centmin[cbin],&centmax[cbin],&y[cbin],&stat[cbin]);
    //                             // cout<<centmin[cbin]<<"\t"<<centmax[cbin]<<"\t"<<y[cbin]<<"\t"<<syst[cbin]<<endl;
    //                             vnAB[i][anal][cbin]->SetBinContent(ebin+1,y[cbin]);
    //                             vnAB[i][anal][cbin]->SetBinError(ebin+1,stat[cbin]);
    //                             ++cbin;
    //                         }
    //
    //                     }
    //                 }
    //             }
    //         }
    //     }
    // }

    int test = 17;
    int ctest = 8;

    string tcut = "";
    for (int i = 0; i<3; i++) {
        if (i == 0) tcut = "useTight";
        else if (i == 1) tcut = "useTightB";
        else tcut = "useLoose";
        for (int anal = 16; anal<20; anal++) {
            for (int ebin = 0; ebin<netabins; ebin++) {
                prevname = Form("../figures/figures_%s_%1.1f_%1.1f/%s/data/integral.dat",tcut.data(),etabins[ebin],etabins[ebin+1],AnalNames[anal].data());
                if (prevname.length()>1) {
                    int centmin[40];
                    int centmax[40];
                    double y[40];
                    double stat[40];
                    FILE * fin = fopen(prevname.data(),"r");
                    char buf[80];
                    int cbin = 0;
                    //cout<<prevname<<endl;
                    while (fgets(buf,80,fin)!=NULL) {
                        sscanf(buf,"%d\t%d\t%lf\t%lf\n",&centmin[cbin],&centmax[cbin],&y[cbin],&stat[cbin]);
                        //cout<<cbin<<"\t"<<centmin[cbin]<<"\t"<<centmax[cbin]<<"\t"<<y[cbin]<<"\t"<<stat[cbin]<<endl;
                        vnAB[i][anal][cbin]->SetBinContent(ebin+1,y[cbin]);
                        vnAB[i][anal][cbin]->SetBinError(ebin+1,stat[cbin]);
                        //cout<<vnAB[i][anal][cbin]->GetBinContent(ebin+1)<<"\t"<<vnAB[i][anal][cbin]->GetBinError(ebin+1)<<endl;
                        ++cbin;
                    }
                    fclose(fin);
                }

                prevname = Form("../figures/figures_%s_%1.1f_%1.1f/%s/data/integralA.dat",tcut.data(),etabins[ebin],etabins[ebin+1],AnalNames[anal].data());
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
                        //cout<<centmin[cbin]<<"\t"<<centmax[cbin]<<"\t"<<y[cbin]<<"\t"<<syst[cbin]<<endl;
                        vnA[i][anal][cbin]->SetBinContent(ebin+1,y[cbin]);
                        vnA[i][anal][cbin]->SetBinError(ebin+1,stat[cbin]);
                        ++cbin;
                    }
                    fclose(fin);
                }

                prevname = Form("../figures/figures_%s_%1.1f_%1.1f/%s/data/integralB.dat",tcut.data(),etabins[ebin],etabins[ebin+1],AnalNames[anal].data());
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
                        // cout<<centmin[cbin]<<"\t"<<centmax[cbin]<<"\t"<<y[cbin]<<"\t"<<syst[cbin]<<endl;
                        vnB[i][anal][cbin]->SetBinContent(ebin+1,y[cbin]);
                        vnB[i][anal][cbin]->SetBinError(ebin+1,stat[cbin]);
                        ++cbin;
                    }
                    fclose(fin);
                }
            }
        }
    }
    for (int ebin = 0; ebin<netabins; ebin++) {
        //cout<<vnAB[0][test][ctest]->GetBinContent(ebin+1)<<"\t"<<vnAB[0][test][ctest]->GetBinError(ebin+1)<<endl;
        //cout<<vnAB[0][18][ctest]->GetBinContent(ebin+1) - vnAB[0][19][ctest]->GetBinContent(ebin+1)<<endl;
    }

    # include "../data/HIN-10-002.h"
    TH1D * v2HIN_10_002_eta[12];
    for (int cbin = 0; cbin<12; cbin++) {
        v2HIN_10_002_eta[cbin] = new TH1D(Form("v2HIN_10_002_eta_%d",cbin), "", netabins, etabins);
    }
    for (int ebin = 0; ebin<netabins; ebin++) {
        v2HIN_10_002_eta[0]->SetBinContent(ebin+1, v2Ecent0to5[ebin]);
        v2HIN_10_002_eta[0]->SetBinError(ebin+1, v2Ecent0to5Err[ebin]);

        v2HIN_10_002_eta[1]->SetBinContent(ebin+1, v2Ecent5to10[ebin]);
        v2HIN_10_002_eta[1]->SetBinError(ebin+1, v2Ecent5to10Err[ebin]);

        v2HIN_10_002_eta[2]->SetBinContent(ebin+1, v2Ecent10to15[ebin]);
        v2HIN_10_002_eta[2]->SetBinError(ebin+1, v2Ecent10to15Err[ebin]);

        v2HIN_10_002_eta[3]->SetBinContent(ebin+1, v2Ecent15to20[ebin]);
        v2HIN_10_002_eta[3]->SetBinError(ebin+1, v2Ecent15to20Err[ebin]);

        v2HIN_10_002_eta[4]->SetBinContent(ebin+1, v2Ecent20to25[ebin]);
        v2HIN_10_002_eta[4]->SetBinError(ebin+1, v2Ecent20to25Err[ebin]);

        v2HIN_10_002_eta[5]->SetBinContent(ebin+1, v2Ecent25to30[ebin]);
        v2HIN_10_002_eta[5]->SetBinError(ebin+1, v2Ecent25to30Err[ebin]);

        v2HIN_10_002_eta[6]->SetBinContent(ebin+1, v2Ecent30to35[ebin]);
        v2HIN_10_002_eta[6]->SetBinError(ebin+1, v2Ecent30to35Err[ebin]);

        v2HIN_10_002_eta[7]->SetBinContent(ebin+1, v2Ecent35to40[ebin]);
        v2HIN_10_002_eta[7]->SetBinError(ebin+1, v2Ecent35to40Err[ebin]);

        v2HIN_10_002_eta[8]->SetBinContent(ebin+1, v2Ecent40to50[ebin]);
        v2HIN_10_002_eta[8]->SetBinError(ebin+1, v2Ecent40to50Err[ebin]);

        v2HIN_10_002_eta[9]->SetBinContent(ebin+1, v2Ecent50to60[ebin]);
        v2HIN_10_002_eta[9]->SetBinError(ebin+1, v2Ecent50to60Err[ebin]);

        v2HIN_10_002_eta[10]->SetBinContent(ebin+1, v2Ecent60to70[ebin]);
        v2HIN_10_002_eta[10]->SetBinError(ebin+1, v2Ecent60to70Err[ebin]);
    }
    cout<<"!!! "<<__LINE__<<endl;

    Double_t kongv1x[] = {-2.23411858350128, -1.7877622910562785, -1.2992023303470126, -0.9321049333581732, -0.6699408945416376, -0.4511998916117679, -0.2382170135654662, -0.019476010635596896, 0.19350686741070566, 0.40405101021220213, 0.6227920131420714, 0.8857689637068771, 1.2536792724439842, 1.7520619167781573, 2.191847172591324};
    Double_t kongv1val[] = {0.002035836, 0.007582604, 0.008014124, 0.006602368, 0.005003641, 0.003643877, 0.002034989, 0.000675225, -0.000933663, -0.002295121, -0.003654885, -0.005336088, -0.006830322, -0.006562061, -0.00118194};
    Double_t kongxerr[15] = {0};
    Double_t kongvalerr[15] = {0.0002};
    TGraphErrors * kongv1 = new TGraphErrors(15, kongv1x, kongv1val, kongxerr, kongvalerr);



    //vnAB[0][16][ctest]->Draw();
    TCanvas * c0 = new TCanvas("c0","c0",650,600);
    TPad * padtest = (TPad *) c0->cd();
    padtest->SetGrid();
    vnAB[0][18][ctest]->SetMarkerColor(kRed);
    vnAB[0][18][ctest]->SetLineColor(kRed);
    vnAB[0][18][ctest]->SetMarkerStyle(20);
    vnAB[0][18][ctest]->SetMarkerSize(1.2);
    vnAB[0][18][ctest]->SetXTitle("#eta");
    vnAB[0][18][ctest]->SetYTitle("v_{2}");
    vnAB[0][18][ctest]->GetYaxis()->SetRangeUser(0.085, 0.12);
    vnAB[0][18][ctest]->Draw();
    vnAB[0][19][ctest]->SetMarkerColor(kBlue);
    vnAB[0][19][ctest]->SetLineColor(kBlue);
    vnAB[0][19][ctest]->SetMarkerStyle(25);
    vnAB[0][19][ctest]->SetMarkerSize(1.2);
    vnAB[0][19][ctest]->Draw("same");
    v2HIN_10_002_eta[ctest]->Draw("same");
    TLine * ltest = new TLine(-2.4, 0, 2.4, 0);
    ltest->Draw();
    TLegend * legtest = new TLegend(0.21, 0.19, 0.41, 0.39);
    SetLegend(legtest, 18);
    legtest->SetHeader(Form("%d-%d%%",cmin[ctest],cmax[ctest]));
    legtest->AddEntry(vnAB[0][18][ctest],"N2SUB2","p");
    legtest->AddEntry(vnAB[0][19][ctest],"N2SUB3","p");
    legtest->AddEntry(v2HIN_10_002_eta[ctest],"HIN-10-002","p");
    legtest->Draw();
    c0->Print("v2.png","png");



    TCanvas * c1 = new TCanvas("c1","c1",650,600);
    TPad * padtest1 = (TPad *) c1->cd();
    padtest1->SetGrid();
    vnAB[0][16][ctest]->SetMarkerColor(kRed);
    vnAB[0][16][ctest]->SetLineColor(kRed);
    vnAB[0][16][ctest]->SetMarkerStyle(20);
    vnAB[0][16][ctest]->SetMarkerSize(1.2);
    vnAB[0][16][ctest]->SetXTitle("#eta");
    vnAB[0][16][ctest]->SetYTitle("v_{1}");
    vnAB[0][16][ctest]->GetYaxis()->SetRangeUser(-0.015, 0.015);
    vnAB[0][16][ctest]->Draw();
    vnAB[0][16][ctest-1]->SetMarkerColor(kBlue);
    vnAB[0][16][ctest-1]->Draw("same");
    vnAB[0][16][ctest-2]->SetMarkerColor(kGreen+2);
    vnAB[0][16][ctest-2]->Draw("same");
    kongv1->SetMarkerStyle(24);
    kongv1->SetMarkerSize(1.2);
    kongv1->Draw("same p");
    vnAB[0][17][ctest]->SetMarkerColor(kBlue);
    vnAB[0][17][ctest]->SetLineColor(kBlue);
    vnAB[0][17][ctest]->SetMarkerStyle(25);
    vnAB[0][17][ctest]->SetMarkerSize(1.2);
    //vnAB[0][17][ctest]->Draw("same");
    TLine * ltest1 = new TLine(-2.4, 0, 2.4, 0);
    ltest1->Draw();
    TLegend * legtest1 = new TLegend(0.21, 0.19, 0.41, 0.39);
    SetLegend(legtest1, 18);
    legtest1->SetHeader(Form("%d-%d%%",cmin[ctest],cmax[ctest]));
    legtest1->AddEntry(vnAB[0][16][ctest],"N1SUB2","p");
    legtest1->AddEntry(kongv1,"Kong","p");
    //legtest1->AddEntry(vnAB[0][17][ctest],"N2SUB3","p");
    legtest1->Draw();
    c1->Print("v1.png","png");


    TCanvas * c2 = new TCanvas("c2","c2",650,600);
    TPad * padtest2 = (TPad *) c2->cd();
    padtest2->SetGrid();
    vnAB[0][16][ctest]->Draw();
    vnAB[1][16][ctest]->SetMarkerStyle(25);
    vnAB[1][16][ctest]->SetMarkerSize(1.2);
    vnAB[1][16][ctest]->Draw("same");
    vnAB[2][16][ctest]->SetMarkerStyle(24);
    vnAB[2][16][ctest]->SetMarkerSize(1.2);
    vnAB[2][16][ctest]->SetMarkerColor(kMagenta);
    vnAB[2][16][ctest]->Draw("same");
    vnAB[0][17][ctest]->SetMarkerColor(kBlue);
    vnAB[0][17][ctest]->SetLineColor(kBlue);
    vnAB[0][17][ctest]->SetMarkerStyle(25);
    vnAB[0][17][ctest]->SetMarkerSize(1.2);
    //vnAB[0][17][ctest]->Draw("same");
    TLine * ltest2 = new TLine(-2.4, 0, 2.4, 0);
    ltest2->Draw();
    TLegend * legtest2 = new TLegend(0.21, 0.19, 0.41, 0.39);
    SetLegend(legtest2, 18);
    legtest2->SetHeader(Form("%d-%d%%",cmin[ctest],cmax[ctest]));
    legtest2->AddEntry(vnAB[0][16][ctest],"N1SUB2 Tight","p");
    legtest2->AddEntry(vnAB[1][16][ctest],"N1SUB2 TightB","p");
    legtest2->AddEntry(vnAB[2][16][ctest],"N1SUB2 Loose","p");
    legtest2->Draw();
    c2->Print("v1_cuts.png","png");



    TCanvas * c3 = new TCanvas("c3","c3",650,600);
    TPad * padtest3 = (TPad *) c3->cd();
    padtest3->SetGrid();
    vnA[0][16][ctest]->GetYaxis()->SetRangeUser(-0.1, 0.1);
    vnA[0][16][ctest]->SetMarkerColor(kBlue);
    vnA[0][16][ctest]->SetLineColor(kBlue);
    vnA[0][16][ctest]->SetMarkerStyle(25);
    vnA[0][16][ctest]->SetMarkerSize(1.2);
    vnA[0][16][ctest]->Draw("same");
    vnB[0][16][ctest]->SetMarkerColor(kMagenta);
    vnB[0][16][ctest]->SetLineColor(kMagenta);
    vnB[0][16][ctest]->SetMarkerStyle(24);
    vnB[0][16][ctest]->SetMarkerSize(1.2);
    vnB[0][16][ctest]->Draw("same");
    vnAB[0][16][ctest]->Draw("same");
    //vnAB[0][17][ctest]->Draw("same");
    TLine * ltest3 = new TLine(-2.4, 0, 2.4, 0);
    ltest3->Draw();
    TLegend * legtest3 = new TLegend(0.21, 0.19, 0.41, 0.39);
    SetLegend(legtest3, 18);
    legtest3->SetHeader(Form("%d-%d%%",cmin[ctest],cmax[ctest]));
    legtest3->AddEntry(vnAB[0][16][ctest],"N1SUB2 HF","p");
    legtest3->AddEntry(vnA[0][16][ctest],"N1SUB2 HF+ only","p");
    legtest3->AddEntry(vnB[0][16][ctest],"N1SUB2 HF- only","p");
    legtest3->Draw();
    c3->Print("v1AB.png","png");



    TH1D * hv1dummy = (TH1D *) vnAB[0][16][12]->Clone("hv1dummy");
    for (int ebin = 0; ebin<vnAB[0][16][12]->GetNbinsX(); ebin++) {
        cout<<ebin<<"\t"<<vnAB[0][16][12]->GetBinContent(ebin+1)<<"\t"<<vnAB[0][16][12]->GetBinError(ebin+1)<<endl;
    }
    //hv1dummy->SetBinContent(8, -0.003601);
    TCanvas * cdummy = new TCanvas("cdummy","cdummy",650,600);
    TPad * paddummy = (TPad *) cdummy->cd();
    paddummy->SetGrid();
    hv1dummy->GetYaxis()->SetRangeUser(-0.015, 0.015);
    hv1dummy->SetMarkerColor(kBlue);
    hv1dummy->SetLineColor(kBlue);
    hv1dummy->SetMarkerStyle(21);
    hv1dummy->SetMarkerSize(1.2);
    hv1dummy->Draw();
    kongv1->Draw("same p");
    ltest1->Draw();
    TLegend * legtestdummy = new TLegend(0.71, 0.75, 0.88, 0.92);
    SetLegend(legtestdummy, 20);
    legtestdummy->SetHeader(Form("%d-%d%%",cmin[12],cmax[12]));
    legtestdummy->AddEntry(hv1dummy,"N1SUB2","p");
    legtestdummy->AddEntry(kongv1,"Kong","p");
    legtestdummy->Draw();
    cdummy->Print("v1kong.png","png");


}
