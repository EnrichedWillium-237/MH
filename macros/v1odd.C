# include "TCanvas.h"
# include "TDirectory.h"
# include "TFile.h"
# include "TGraphErrors.h"
# include "TH1.h"
# include "TH2.h"
# include "TLatex.h"
# include "TLegend.h"
# include "TMath.h"
# include "TPaveText.h"
# include "Riostream.h"
# include <iostream>
# include <string>

# include "src/style.h"

TFile * tf = new TFile("MH_hists.root");
TGraphErrors * gintc;
TGraphErrors * gintd;
TGraphErrors * ginte;
TGraphErrors * gintf;
TGraphErrors * gc;
TGraphErrors * gd;
TGraphErrors * ge;
TGraphErrors * gf;
TGraphErrors * g_new;

void v1odd(string cent="10_70",string eta="-1.2_1.2" ,string sub = "SUB3"){
    gintc = (TGraphErrors *) tf->Get(Form("N1HFc%s/%s/%s/gint",sub.data(),eta.data(),cent.data()));
    gintd = (TGraphErrors *) tf->Get(Form("N1HFd%s/%s/%s/gint",sub.data(),eta.data(),cent.data()));
    ginte = (TGraphErrors *) tf->Get(Form("N1HFe%s/%s/%s/gint",sub.data(),eta.data(),cent.data()));
    gintf = (TGraphErrors *) tf->Get(Form("N1HFf%s/%s/%s/gint",sub.data(),eta.data(),cent.data()));
    gc = (TGraphErrors *) tf->Get(Form("N1HFc%s/%s/%s/g",sub.data(),eta.data(),cent.data()));
    cout<<gc<<endl;
    gd = (TGraphErrors *) tf->Get(Form("N1HFd%s/%s/%s/g",sub.data(),eta.data(),cent.data()));
    ge = (TGraphErrors *) tf->Get(Form("N1HFe%s/%s/%s/g",sub.data(),eta.data(),cent.data()));
    gf = (TGraphErrors *) tf->Get(Form("N1HFf%s/%s/%s/g",sub.data(),eta.data(),cent.data()));
    g_new = (TGraphErrors *) tf->Get(Form("N1HFf%s/%s/-0.8_0.8/g",sub.data(),cent.data()));
    int minc = 0;
    int maxc = 0;
    if(cent=="0_5") {minc=0; maxc=5;}
    if(cent=="5_10") {minc=5; maxc=10;}
    if(cent=="10_15") {minc=10; maxc=15;}
    if(cent=="15_20") {minc=15; maxc=20;}
    if(cent=="20_25") {minc=20; maxc=25;}
    if(cent=="25_30") {minc=25; maxc=30;}
    if(cent=="30_35") {minc=30; maxc=35;}
    if(cent=="35_40") {minc=35; maxc=40;}
    if(cent=="40_50") {minc=40; maxc=50;}
    if(cent=="50_60") {minc=50; maxc=60;}
    if(cent=="60_70") {minc=60; maxc=70;}
    if(cent=="0_20") {minc=0; maxc=20;}
    //if(cent=="20_60") {minc=20; maxc=60;}
    if(cent=="10_70") {minc=20; maxc=60;}
    TCanvas * c = new TCanvas("c","c",750,700);
    TPad * p = (TPad *) c->cd();
    TH1D * h = new TH1D("h","h",100,-3,3);
    h->SetMinimum(-0.02);
    h->SetMaximum(0.02);
    h->SetXTitle("#eta");
    h->SetYTitle("v_{1}");
    h->Draw();
    gintc->SetMarkerColor(kBlack);
    gintc->SetLineColor(kBlack);
    gintc->SetMarkerStyle(20);
    gintc->SetMarkerSize(1.1);
    gintc->Draw("p");
    gintd->SetMarkerStyle(24);
    gintd->SetMarkerColor(kRed);
    gintd->SetLineColor(kRed);
    gintd->SetMarkerSize(1.1);
    gintd->Draw("p");
    ginte->SetMarkerStyle(24);
    ginte->SetMarkerColor(kGreen+2);
    ginte->SetLineColor(kGreen+2);
    ginte->SetMarkerSize(1.1);
    ginte->Draw("p");
    gintf->SetMarkerStyle(21);
    gintf->SetMarkerColor(kBlue);
    gintf->SetLineColor(kBlue);
    gintf->SetMarkerSize(1.1);
    gintf->Draw("p");
    TLatex * l1 = new TLatex(-2.6,0.016,Form("%d - %d%c",minc,maxc,'%'));
    l1->SetTextFont(43);
    l1->SetTextSize(30);
    l1->Draw();
    TLegend * leg = new TLegend(0.53, 0.73, 0.78, 0.92);
    leg->SetBorderSize(0);
    leg->SetFillColor(kWhite);
    leg->SetTextFont(43);
    leg->SetTextSize(24);
    leg->AddEntry(gintc,"3.0 < |#eta_{EP}| < 3.5","lp");
    leg->AddEntry(gintd,"3.5 < |#eta_{EP}| < 4.0","lp");
    leg->AddEntry(ginte,"4.0 < |#eta_{EP}| < 4.5","lp");
    leg->AddEntry(gintf,"4.5 < |#eta_{EP}| < 5.0","lp");
    leg->Draw();
    c->Print(Form("v1odd/v1odd_%s_%s.png",cent.data(),sub.data()),"png");

    gc->SetMarkerColor(kBlack);
    gc->SetLineColor(kBlack);
    gc->SetMarkerStyle(20);
    gc->SetMarkerSize(1.1);
    gd->SetMarkerStyle(24);
    gd->SetMarkerColor(kRed);
    gd->SetLineColor(kRed);
    gd->SetMarkerSize(1.1);
    ge->SetMarkerStyle(24);
    ge->SetMarkerColor(kGreen+2);
    ge->SetLineColor(kGreen+2);
    ge->SetMarkerSize(1.1);
    gf->SetMarkerStyle(21);
    gf->SetMarkerColor(kBlue);
    gf->SetLineColor(kBlue);
    gf->SetMarkerSize(1.1);

    TCanvas * c0 = new TCanvas("c0","c0",750,700);
    TPad * p0 = (TPad *) c0->cd();
    TH1D * h0 = new TH1D("h","h",100,0,12);
    h0->SetMinimum(-0.02);
    h0->SetMaximum(0.02);
    h0->SetXTitle("#eta");
    h0->SetYTitle("v_{1}");
    h0->Draw();
    gc->Draw("same p");
    gd->Draw("same p");
    ge->Draw("same p");
    gf->Draw("same p");
    leg->Draw();
    c0->Print(Form("v1odd/v1odd_pT_%s_%s.png",cent.data(),sub.data()),"png");

    # include "../../published_results/PHOBOS_AuAu.h" // participant v1

    TH1D * PHOBOS_AuAu_Mixed_200GeV = new TH1D("PHOBOS_AuAu_Mixed_200GeV", "", PHOBOS_AuAu_nebins, PHOBOS_AuAu_eta);
    TH1D * PHOBOS_AuAu_2sub_200GeV = new TH1D("PHOBOS_AuAu_2sub_200GeV", "", PHOBOS_AuAu_nebins, PHOBOS_AuAu_eta);
    for (int i = 0; i<PHOBOS_AuAu_nebins; i++) {
        PHOBOS_AuAu_Mixed_200GeV->SetBinContent(i+1, PHOBOS_AuAu_mixed_v1_3[i]);
        PHOBOS_AuAu_Mixed_200GeV->SetBinError(i+1, PHOBOS_AuAu_mixed_v1Err_3[i]);

        PHOBOS_AuAu_Mixed_200GeV->SetMarkerColor(kGreen+2);
        PHOBOS_AuAu_Mixed_200GeV->SetLineColor(kGreen+2);
        PHOBOS_AuAu_Mixed_200GeV->SetMarkerStyle(24);
        PHOBOS_AuAu_Mixed_200GeV->SetMarkerSize(1.2);

        PHOBOS_AuAu_2sub_200GeV->SetBinContent(i+1, PHOBOS_AuAu_sym_v1_3[i]);
        PHOBOS_AuAu_2sub_200GeV->SetBinError(i+1, PHOBOS_AuAu_sym_v1Err_3[i]);

        PHOBOS_AuAu_2sub_200GeV->SetMarkerColor(kBlack);
        PHOBOS_AuAu_2sub_200GeV->SetLineColor(kBlack);
        PHOBOS_AuAu_2sub_200GeV->SetMarkerStyle(21);
        PHOBOS_AuAu_2sub_200GeV->SetMarkerSize(1.2);
    }

    # include "../../published_results/PhysRevLett_92_062301.h" // participant v1

    TGraphErrors * STAR_v1_3PC_200GeV = new TGraphErrors(24, STAR_v1_3PC_200GeV_eta, STAR_v1_3PC_200GeV_val, 0, STAR_v1_3PC_200GeV_err);
    STAR_v1_3PC_200GeV->SetMarkerColor(kBlack);
    STAR_v1_3PC_200GeV->SetLineColor(kBlack);
    STAR_v1_3PC_200GeV->SetMarkerStyle(30);
    STAR_v1_3PC_200GeV->SetMarkerSize(1.5);


    # include "../../published_results/PhysRevC72_14904.h" // participant v1

    TGraphErrors * STAR_v1_mix_200GeV = new TGraphErrors(STAR_AuAu_Mixed_neta, STAR_AuAu_Mixed_eta, STAR_AuAu_Mixed_v1, 0, STAR_AuAu_Mixed_v1Err);
    STAR_v1_mix_200GeV->SetMarkerColor(kRed);
    STAR_v1_mix_200GeV->SetLineColor(kRed);
    STAR_v1_mix_200GeV->SetMarkerStyle(20);
    STAR_v1_mix_200GeV->SetMarkerSize(1.2);


    # include "../../published_results/PhysRevC73_034903.h" // participant and spectator v1 (62.3 GeV)

    TGraphErrors * STAR_v1_3PC_62GeV_eta = new TGraphErrors(STAR_AuAu_62GeV_Fig1_3PC_n, STAR_AuAu_62GeV_Fig1_3PC_eta, STAR_AuAu_62GeV_Fig1_3PC_v1, 0, STAR_AuAu_62GeV_Fig1_3PC_v1err);
    STAR_v1_3PC_62GeV_eta->SetMarkerColor(kRed);
    STAR_v1_3PC_62GeV_eta->SetLineColor(kRed);
    STAR_v1_3PC_62GeV_eta->SetMarkerStyle(29);
    STAR_v1_3PC_62GeV_eta->SetMarkerSize(1.5);

    TGraphErrors * STAR_v1_mix_62GeV_eta = new TGraphErrors(STAR_AuAu_62GeV_Fig1_mix_n, STAR_AuAu_62GeV_Fig1_mix_eta, STAR_AuAu_62GeV_Fig1_mix_v1, 0, STAR_AuAu_62GeV_Fig1_mix_v1err);
    STAR_v1_mix_62GeV_eta->SetMarkerColor(kCyan+2);
    STAR_v1_mix_62GeV_eta->SetLineColor(kCyan+2);
    STAR_v1_mix_62GeV_eta->SetMarkerStyle(24);
    STAR_v1_mix_62GeV_eta->SetMarkerSize(1.2);

    TGraphErrors * STAR_v1_ZDC_62GeV_eta = new TGraphErrors(STAR_AuAu_62GeV_Fig1_ZDC_n, STAR_AuAu_62GeV_Fig1_ZDC_eta, STAR_AuAu_62GeV_Fig1_ZDC_v1, 0, STAR_AuAu_62GeV_Fig1_ZDC_v1err);
    STAR_v1_ZDC_62GeV_eta->SetMarkerColor(kBlue);
    STAR_v1_ZDC_62GeV_eta->SetLineColor(kBlue);
    STAR_v1_ZDC_62GeV_eta->SetMarkerStyle(25);
    STAR_v1_ZDC_62GeV_eta->SetMarkerSize(1.1);

    TGraphErrors * STAR_v1_3PC_62GeV_pT = new TGraphErrors(STAR_AuAu_62GeV_3PC_pT_n, STAR_AuAu_62GeV_3PC_pTval, STAR_AuAu_62GeV_3PC_pT_v1, 0, STAR_AuAu_62GeV_3PC_pT_v1_err);
    STAR_v1_3PC_62GeV_eta->SetMarkerColor(kRed);
    STAR_v1_3PC_62GeV_eta->SetLineColor(kRed);
    STAR_v1_3PC_62GeV_eta->SetMarkerStyle(29);
    STAR_v1_3PC_62GeV_eta->SetMarkerSize(1.5);


    # include "../../published_results/PhysRevLett101_252301.h" // spectator v1

    TGraphErrors * STAR_v1_ZDC_200GeV_eta_0_5 = new TGraphErrors(16, STAR_AuAu_200_ZDC_cent0_5_eta, STAR_AuAu_200_ZDC_cent0_5_v1eta, 0, STAR_AuAu_200_ZDC_cent0_5_v1etaErr);
    STAR_v1_ZDC_200GeV_eta_0_5->SetMarkerColor(kRed);
    STAR_v1_ZDC_200GeV_eta_0_5->SetLineColor(kRed);
    STAR_v1_ZDC_200GeV_eta_0_5->SetMarkerStyle(20);
    STAR_v1_ZDC_200GeV_eta_0_5->SetMarkerSize(1.2);

    TGraphErrors * STAR_v1_ZDC_200GeV_eta_5_40 = new TGraphErrors(16, STAR_AuAu_200_ZDC_cent5_40_eta, STAR_AuAu_200_ZDC_cent5_40_v1eta, 0, STAR_AuAu_200_ZDC_cent5_40_v1etaErr);
    STAR_v1_ZDC_200GeV_eta_5_40->SetMarkerColor(kCyan+2);
    STAR_v1_ZDC_200GeV_eta_5_40->SetLineColor(kCyan+2);
    STAR_v1_ZDC_200GeV_eta_5_40->SetMarkerStyle(29);
    STAR_v1_ZDC_200GeV_eta_5_40->SetMarkerSize(1.5);

    TGraphErrors * STAR_v1_ZDC_200GeV_eta_40_80 = new TGraphErrors(16, STAR_AuAu_200_ZDC_cent40_80_eta, STAR_AuAu_200_ZDC_cent40_80_v1eta, 0, STAR_AuAu_200_ZDC_cent40_80_v1etaErr);
    STAR_v1_ZDC_200GeV_eta_40_80->SetMarkerColor(kBlue);
    STAR_v1_ZDC_200GeV_eta_40_80->SetLineColor(kBlue);
    STAR_v1_ZDC_200GeV_eta_40_80->SetMarkerStyle(21);
    STAR_v1_ZDC_200GeV_eta_40_80->SetMarkerSize(1.1);

    TGraphErrors * STAR_v1_ZDC_200GeV_pt_0_5 = new TGraphErrors(16, STAR_AuAu_200_ZDC_TPC_cent0_5_pbin, STAR_AuAu_200_ZDC_TPC_cent0_5_pT, 0, STAR_AuAu_200_ZDC_TPC_cent0_5_pTerr);
    STAR_v1_ZDC_200GeV_pt_0_5->SetMarkerColor(kRed);
    STAR_v1_ZDC_200GeV_pt_0_5->SetLineColor(kRed);
    STAR_v1_ZDC_200GeV_pt_0_5->SetMarkerStyle(20);
    STAR_v1_ZDC_200GeV_pt_0_5->SetMarkerSize(1.2);

    TGraphErrors * STAR_v1_ZDC_200GeV_pt_5_40 = new TGraphErrors(16, STAR_AuAu_200_ZDC_TPC_cent5_40_pbin, STAR_AuAu_200_ZDC_TPC_cent5_40_pT, 0, STAR_AuAu_200_ZDC_TPC_cent5_40_pTerr);
    STAR_v1_ZDC_200GeV_pt_5_40->SetMarkerColor(kCyan+2);
    STAR_v1_ZDC_200GeV_pt_5_40->SetLineColor(kCyan+2);
    STAR_v1_ZDC_200GeV_pt_5_40->SetMarkerStyle(29);
    STAR_v1_ZDC_200GeV_pt_5_40->SetMarkerSize(1.5);

    TGraphErrors * STAR_v1_ZDC_200GeV_pt_40_80 = new TGraphErrors(16, STAR_AuAu_200_ZDC_TPC_cent40_80_pbin, STAR_AuAu_200_ZDC_TPC_cent40_80_pT, 0, STAR_AuAu_200_ZDC_TPC_cent40_80_pTerr);
    STAR_v1_ZDC_200GeV_pt_40_80->SetMarkerColor(kRed);
    STAR_v1_ZDC_200GeV_pt_40_80->SetLineColor(kRed);
    STAR_v1_ZDC_200GeV_pt_40_80->SetMarkerStyle(24);
    STAR_v1_ZDC_200GeV_pt_40_80->SetMarkerSize(1.2);


    # include "../../published_results/PhysRevLett111_232302.h" // spectator v1

    TH1D * ALICE_v1odd_c10_60 = new TH1D("ALICE_v1odd_c10_60", "", 5, etarap);
    for (int i = 0; i<5; i++) {
        ALICE_v1odd_c10_60->SetBinContent(i+1, ALICE_v1odd_10_60[i]);
        ALICE_v1odd_c10_60->SetBinError(i+1, ALICE_v1odd_10_60_err[i]);
    }
    ALICE_v1odd_c10_60->SetMarkerColor(kMagenta);
    ALICE_v1odd_c10_60->SetLineColor(kMagenta);
    ALICE_v1odd_c10_60->SetMarkerStyle(21);
    ALICE_v1odd_c10_60->SetMarkerSize(1.2);

    TH1D * ALICE_v1odd_pT_5_80 = new TH1D("ALICE_v1odd_pT_5_80", "", 10, ALICEpTbins);
    for (int i = 0; i<10; i++) {
        ALICE_v1odd_pT_5_80->SetBinContent(i+1, ALICE_v1odd_pT[i]);
        ALICE_v1odd_pT_5_80->SetBinError(i+1, ALICE_v1odd_pT_err[i]);
    }
    ALICE_v1odd_pT_5_80->SetMarkerColor(kMagenta);
    ALICE_v1odd_pT_5_80->SetLineColor(kMagenta);
    ALICE_v1odd_pT_5_80->SetMarkerStyle(21);
    ALICE_v1odd_pT_5_80->SetMarkerSize(1.1);

    TH1D * ALICE_v1even_pT_5_80 = new TH1D("ALICE_v1even_pT_5_80", "", 10, ALICEpTbins);
    for (int i = 0; i<10; i++) {
        ALICE_v1even_pT_5_80->SetBinContent(i+1, ALICE_v1even_pT[i]);
        ALICE_v1even_pT_5_80->SetBinError(i+1, ALICE_v1even_pT_err[i]);
    }
    ALICE_v1even_pT_5_80->SetMarkerColor(kMagenta);
    ALICE_v1even_pT_5_80->SetLineColor(kMagenta);
    ALICE_v1even_pT_5_80->SetMarkerStyle(20);
    ALICE_v1even_pT_5_80->SetMarkerSize(1.2);




    TCanvas * cSTAR_200GeV = new TCanvas("cSTAR_200GeV","cSTAR_200GeV",750,700);
    TPad * padSTAR_200GeV = (TPad *) cSTAR_200GeV->cd();
    padSTAR_200GeV->SetGrid();
    TH1D * hSTAR_200GeV = new TH1D("hSTAR_200GeV", "", 100, -2.0, 2.0);
    hSTAR_200GeV->SetXTitle("#eta");
    hSTAR_200GeV->SetYTitle("v_{1}^{odd}");
    hSTAR_200GeV->GetYaxis()->SetRangeUser(-0.05, 0.05);
    hSTAR_200GeV->Draw();
    STAR_v1_3PC_200GeV->Draw("same p");
    STAR_v1_mix_200GeV->Draw("same p");
    gintf->SetMarkerColor(kBlue);
    gintf->SetLineColor(kBlue);
    gintf->SetMarkerStyle(21);
    gintf->SetMarkerSize(1.2);
    gintf->Draw("same p");
    TLegend * legSTAR_200GeV = new TLegend(0.2, 0.18, 0.5, 0.32);
    SetLegend(legSTAR_200GeV, 18);
    legSTAR_200GeV->AddEntry(gintf,"CMS PbPb 5.02 TeV, SP (20-60%)","p");
    legSTAR_200GeV->AddEntry(STAR_v1_3PC_200GeV,"STAR 3PC #sqrt{s_{NN}}=200 GeV (10-70%)","p");
    legSTAR_200GeV->AddEntry(STAR_v1_mix_200GeV,"STAR mixed #sqrt{s_{NN}}=200 GeV (20-60%)","p");
    legSTAR_200GeV->Draw();
    cSTAR_200GeV->Print("plot_comparison_STAR200GeV.png","png");


    TCanvas * c1 = new TCanvas("c1","c1",750,700);
    TPad * pad1 = (TPad *) c1->cd();
    pad1->SetGrid();
    TH1D * h1 = new TH1D("h1", "", 100, -2.0, 2.0);
    h1->SetXTitle("#eta");
    h1->SetYTitle("v_{1}^{odd}");
    h1->GetYaxis()->SetRangeUser(-0.015, 0.015);
    h1->Draw();
    STAR_v1_3PC_62GeV_eta->Draw("same p");
    STAR_v1_mix_62GeV_eta->Draw("same p");
    STAR_v1_ZDC_62GeV_eta->Draw("same p");
    //ALICE_v1odd_c10_60->Draw("same");
    gintf->Draw("same p");
    TLegend * leg1 = new TLegend(0.20, 0.18, 0.60, 0.38);
    SetLegend(leg1, 18);
    leg1->AddEntry(gintf,"CMS PbPb 5.02 TeV, SP (20-60%)","p");
    //leg1->AddEntry(ALICE_v1odd_c10_60,"ALICE PbPb 2.76TeV, SP (10-60%)","p");
    leg1->AddEntry(STAR_v1_3PC_62GeV_eta,"STAR AuAu 62.4GeV, 3PC (10-70%)","p");
    leg1->AddEntry(STAR_v1_mix_62GeV_eta,"STAR AuAu 62.4GeV, mixed (10-70%)","p");
    leg1->AddEntry(STAR_v1_ZDC_62GeV_eta,"STAR AuAu 62.4GeV, ZDC (10-70%)","p");
    leg1->Draw();
    c1->Print("plot_comparison_01.png","png");


    TCanvas * c2 = new TCanvas("c2","c2",750,700);
    TPad * pad2 = (TPad *) c2->cd();
    pad2->SetGrid();
    TH1D * h2 = new TH1D("h2", "", 100, 0, 12);
    h2->GetXaxis()->SetRangeUser(0, 5);
    h2->SetXTitle("p_{T} (GeV/c)");
    h2->SetYTitle("v_{1}^{odd}");
    h2->GetYaxis()->SetRangeUser(-0.008, 0.01);
    h2->Draw();
    STAR_v1_ZDC_200GeV_pt_5_40->Draw("same p");
    STAR_v1_ZDC_200GeV_pt_40_80->Draw("same p");
    ALICE_v1odd_pT_5_80->Draw("same");
    gf->Draw("same p");
    TLegend * leg2 = new TLegend(0.19, 0.75, 0.59, 0.92);
    SetLegend(leg2, 18);
    leg2->AddEntry(gf,"CMS 5.02TeV, SP |#eta|<0.8 (20-60%)","p");
    leg2->AddEntry(ALICE_v1odd_pT_5_80,"ALICE PbPb 2.76TeV, SP |#eta|<0.8 (5-80%)","p");
    leg2->AddEntry(STAR_v1_ZDC_200GeV_pt_5_40,"STAR AuAu 200GeV, ZDC |#eta|<1.3 (5-40%)","p");
    leg2->AddEntry(STAR_v1_ZDC_200GeV_pt_40_80,"STAR AuAu 200GeV, ZDC |#eta|<1.3 (40-80%)","p");
    leg2->Draw();
    c2->Print("plot_comparison_02.png","png");


    TCanvas * c3 = new TCanvas("c3","c3",750,700);
    TPad * pad3 = (TPad *) c3->cd();
    pad3->SetGrid();
    TH1D * h3 = new TH1D("h3", "", 100, -2.0, 2.0);
    h3->SetXTitle("#eta");
    h3->SetYTitle("v_{1}^{odd}");
    h3->GetYaxis()->SetRangeUser(-0.015, 0.015);
    h3->Draw();
    ALICE_v1odd_c10_60->Draw("same");
    gintf->Draw("same p");
    TLegend * leg3 = new TLegend(0.20, 0.18, 0.60, 0.27);
    SetLegend(leg3, 18);
    leg3->AddEntry(gintf,"CMS PbPb 5.02 TeV, SP (20-60%)","p");
    leg3->AddEntry(ALICE_v1odd_c10_60,"ALICE PbPb 2.76TeV, SP (10-60%)","p");
    leg3->Draw();
    c3->Print("plot_comparison_03.png","png");

}
