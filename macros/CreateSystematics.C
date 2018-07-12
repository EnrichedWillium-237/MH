# include "TCanvas.h"
# include "TDirectory.h"
# include "TF1.h"
# include "TFile.h"
# include "TGraphErrors.h"
# include "TH1.h"
# include "TLatex.h"
# include "TLegend.h"
# include "TLine.h"
# include "TList.h"
# include "TString.h"
# include <iostream>
# include <stdio.h>

# include "SystematicsPlots.h"

using namespace std;

TH1D * hpercent = 0;
TH1D * hpercentint = 0;
TH1D * hdifferr = 0;
TH1D * hdifferrint = 0;

double maxR(double val);

TCanvas *  CreateSystematics2( string replay = "", TGraphErrors * gDefault = 0, TGraphErrors * gSys1 = 0, string stattype1 = "", TGraphErrors * gSys2 = 0, string stattype2 = "", string etarange = "", string centrange = "", string xlabel = "", string ylabel = "",  string title = "" , bool pt = true );

void CreateSystematics( string name = "systPlots.root" ) {
    TFile * fin = new TFile(name.data(),"update");

    TList * l = (TList *) fin->GetListOfKeys();
    int indx = 0;
    bool defaultFound = false;
    bool tightFound = false;
    bool tight2Found = false;
    bool looseFound = false;
    bool wideFound = false;
    bool narrowFound = false;
    bool eposFound = false;
    string base;
    while (true) {
        base = l->At(indx)->GetName();
        cout<<" --- "<<base<<endl;
        if (base=="default") {
            defaultFound = true;
            cout<<"default found"<<endl;
        }
        if (base=="epos") {
            eposFound = true;
            cout<<"epos found"<<endl;
        }
        if (base=="tight" || base=="tight2") {
            tightFound = true;
            cout<<"tight found"<<endl;
            if (base=="tight2") tight2Found = true;
            if (tight2Found) cout<<"tight2Found"<<endl;
        }
        if (base=="loose") {
            looseFound = true;
            cout<<"loose found"<<endl;
        }
        if (base=="wide") {
            wideFound = true;
            cout<<"wide found"<<endl;
        }
        if (base=="narrow") {
            narrowFound = true;
            cout<<"narrowFound"<<endl;
        }
        if (l->At(indx)==l->Last()) break;
        ++indx;
    }
    if (defaultFound) {
        TDirectory * defaultDir = (TDirectory *) fin->Get("default");
        l = (TList *) defaultDir->GetListOfKeys();
        indx = 0;
        while (true) {
            string base2 = l->At(indx)->GetName();
            cout<<"******************************** "<<base2<<" **************************************"<<endl;
            TDirectory * subdir = (TDirectory *) defaultDir->Get(base2.data());
            TList * lsub = (TList *) subdir->GetListOfKeys();
            int subindx = 0;
            while (true) {
                string subbase = lsub->At(subindx)->GetName();
            	TDirectory * syserrdir = 0;
                TDirectory * subsubdir = (TDirectory *) subdir->Get(subbase.data());
                TList * lsubsub = (TList *) subsubdir->GetListOfKeys();
                int subsubindx = 0;
                while (true) {
                    string subsubbase = lsubsub->At(subsubindx)->GetName();
                    TDirectory * subsubsubdir = (TDirectory *) subsubdir->Get(subsubbase.data());
      	            TList * lsubsubsub = (TList *) subsubsubdir->GetListOfKeys();
	                syserrdir = (TDirectory *) subsubsubdir->Get("systematics");
                    if (syserrdir==0) {
                        syserrdir = (TDirectory *) subsubsubdir->mkdir("systematics");
                    }
      	            string stight="tight/"+base2;
                    if (tight2Found) stight="tight2/"+base2;
                    string sloose="loose/"+base2;
                  	string swide="wide/"+base2;
                  	string snarrow="narrow/"+base2;
	                string sepos = "epos/"+base2;
                    stight+="/"+subbase;
                    sloose+="/"+subbase;
                    swide+="/"+subbase;
                    snarrow+="/"+subbase;
                    sepos+="/"+subbase;
                    stight+="/"+subsubbase;
                    sloose+="/"+subsubbase;
                    swide+="/"+subsubbase;
                    snarrow+="/"+subsubbase;
                    sepos+="/"+subsubbase;
      	            int subsubsubindx = 0;
      	            string ytitle = "";
	                bool pt = true;
      	            while (true) {
                        string subsubsubbase = lsubsubsub->At(subsubsubindx)->GetName();
                        if (subsubsubbase=="h") {
                            ytitle = ((TH1D *) subsubsubdir->Get("h"))->GetYaxis()->GetTitle();
                            ytitle=ytitle.substr(0,ytitle.find("}")+1);
                        }
      	                if (subsubsubbase=="g") {
                            TGraphErrors * g = (TGraphErrors *) subsubsubdir->Get(subsubsubbase.data());
	                        if (tightFound && looseFound) {
                          		string s1 = Form("%s/%s",sloose.data(),subsubsubbase.data());
                          		string s2 = Form("%s/%s",stight.data(),subsubsubbase.data());
                          		TGraphErrors * gSys1 = (TGraphErrors *) fin->Get(Form("%s/%s",sloose.data(),subsubsubbase.data()));
                          		TGraphErrors * gSys2 = (TGraphErrors *) fin->Get(Form("%s/%s",stight.data(),subsubsubbase.data()));
                        		if (gSys1==0 || gSys2==0) cout<<"ERROR: "<<s1<<"\t"<<gSys1<<"\t"<<s2<<"\t"<<gSys2<<endl;
                                pt = true;
                         		TCanvas * can =  CreateSystematics2(base2, g, gSys1, "loose", gSys2, "tight", subbase, subsubbase, "p_{T} (GeV/c)", ytitle, subsubsubbase.data(), pt);
                          		syserrdir->cd();
                          		can->Write();
                          		can->Close();
                            }
        	                if (eposFound) {
                          		string s1 = Form("%s/%s",sloose.data(),subsubsubbase.data());
                          		TGraphErrors * gSys1 = (TGraphErrors *) fin->Get(Form("%s/%s",sepos.data(),subsubsubbase.data()));
                    		    TGraphErrors * gSys2 = 0;
                        		if (gSys1==0) cout<<"ERROR: "<<s1<<"\t"<<gSys1<<"\t"<<endl;
                                pt=true;
                         		TCanvas * can =  CreateSystematics2(base2, g, gSys1, "epos", gSys2, "", subbase, subsubbase, "p_{T} (GeV/c)", ytitle, subsubsubbase.data(), pt);
                          		syserrdir->cd();
                          		can->Write();
                          		can->Close();
                            }
             	            if (narrowFound && wideFound) {
                          		string s1 = Form("%s/%s",swide.data(),subsubsubbase.data());
                          		string s2 = Form("%s/%s",snarrow.data(),subsubsubbase.data());
                          		TGraphErrors * gSys1 = (TGraphErrors *) fin->Get(Form("%s/%s",swide.data(),subsubsubbase.data()));
                          		TGraphErrors * gSys2 = (TGraphErrors *) fin->Get(Form("%s/%s",snarrow.data(),subsubsubbase.data()));
                        		if (gSys1==0 || gSys2==0) cout<<"ERROR: "<<s1<<"\t"<<gSys1<<"\t"<<s2<<"\t"<<gSys2<<endl;
                                pt = true;
              		            TCanvas * can =  CreateSystematics2(base2, g, gSys1, "wide", gSys2, "narrow", subbase, subsubbase, "p_{T} (GeV/c)", ytitle, subsubsubbase.data(), pt);
                          		syserrdir->cd();
                          		can->Write();
                          		can->Close();
                            }
                        }
      	                if (subsubsubbase=="gint") {
                            TGraphErrors * g = (TGraphErrors *) subsubsubdir->Get(subsubsubbase.data());
              	            if (tightFound && looseFound) {
                          		string s1 = Form("%s/%s",sloose.data(),subsubsubbase.data());
                          		string s2 = Form("%s/%s",stight.data(),subsubsubbase.data());
                          		TGraphErrors * gSys1 = (TGraphErrors *) fin->Get(Form("%s/%s",sloose.data(),subsubsubbase.data()));
                          		TGraphErrors * gSys2 = (TGraphErrors *) fin->Get(Form("%s/%s",stight.data(),subsubsubbase.data()));
                        		if (gSys1==0 || gSys2==0) cout<<"ERROR: "<<s1<<"\t"<<gSys1<<"\t"<<s2<<"\t"<<gSys2<<endl;
                                pt = false;
                          		TCanvas * can =  CreateSystematics2(base2, g, gSys1, "loose", gSys2, "tight", subbase, subsubbase, "#eta", ytitle, subsubsubbase.data(), pt);
                          		syserrdir->cd();
                          		can->Write();
                          		can->Close();
                            }
	                        if (eposFound) {
                          		string s1 = Form("%s/%s",sloose.data(),subsubsubbase.data());
                          		TGraphErrors * gSys1 = (TGraphErrors *) fin->Get(Form("%s/%s",sepos.data(),subsubsubbase.data()));
                          		TGraphErrors * gSys2 = 0;
                        		if (gSys1==0 || gSys2==0) cout<<"ERROR: "<<s1<<"\t"<<gSys1<<endl;
                                pt = false;
                          		TCanvas * can =  CreateSystematics2(base2, g, gSys1, "epos", gSys2, "", subbase, subsubbase, "#eta", ytitle, subsubsubbase.data(), pt);
                          		syserrdir->cd();
                          		can->Write();
                          		can->Close();
                            }
          	                if (narrowFound && wideFound) {
                           		string s1 = Form("%s/%s",swide.data(),subsubsubbase.data());
                          		string s2 = Form("%s/%s",snarrow.data(),subsubsubbase.data());
                         		TGraphErrors * gSys1 = (TGraphErrors *) fin->Get(Form("%s/%s",swide.data(),subsubsubbase.data()));
                          		TGraphErrors * gSys2 = (TGraphErrors *) fin->Get(Form("%s/%s",snarrow.data(),subsubsubbase.data()));
                        		if (gSys1==0 || gSys2==0) cout<<"ERROR: "<<s1<<"\t"<<gSys1<<"\t"<<s2<<"\t"<<gSys2<<endl;
                                pt = false;
                          		TCanvas * can =  CreateSystematics2(base2, g, gSys1, "wide", gSys2, "narrow", subbase, subsubbase, "#eta", ytitle, subsubsubbase.data(), pt);
                          		syserrdir->cd();
                          		can->Write();
                          		can->Close();
                            }
                        }
                        if (lsubsubsub->At(subsubsubindx)==lsubsubsub->Last()) {break;}
      	                ++subsubsubindx;
                    }
                    if (lsubsub->At(subsubindx)==lsubsub->Last()) {break;}
                    ++subsubindx;
                }
                if (lsub->At(subindx)==lsub->Last()) {break;}
      	        ++subindx;
            }
            if (l->At(indx)==l->Last()) { break;}
            ++indx;
        }
    }
}

double maxR( double val ){
    double sign = 1.;
    if (val<0) sign = -1.;
    val = abs(val);
    double ex = trunc(log10(val));
    double rem = log10(val)- trunc(log10(val));
    double rn = 0;
    double remck = 0.8*rem;
    //cout<<val<<"\t"<<remck<<endl;
    if (remck>0) {
        if (remck<log10(1)) {
            rn = log10(1);
        } else if (remck<log10(2)){
            rn = log10(2);
        } else if (remck<log10(4)){
            rn = log10(4);
        } else if (remck<log10(5)){
            rn = log10(5);
        } else if (remck<log10(10)){
            rn = log10(10);
        }
    } else {
        if (remck<log10(0.1)) {
            rn = log10(0.1);
        } else if (remck<log10(.2)){
            rn = log10(.2);
        } else if (remck<log10(.4)){
            rn = log10(.4);
        } else if (remck<log10(.5)){
            rn = log10(.5);
        } else if (remck<log10(1.)){
            rn = log10(1.0);
        }
    }
    //cout<<rn<<endl;
    double ret = sign*pow(10,ex+rn);
    return ret;
}

TCanvas *  CreateSystematics2( string replay, TGraphErrors * gDefault, TGraphErrors * gSys1, string systype1, TGraphErrors * gSys2, string systype2, string etarange, string centrange, string xlabel, string ylabel, string title, bool pt ) {
    string gname = "trackQuality";
    if (systype2=="wide"||systype2=="narrow") gname = "vtxRange";
    if (systype1=="epos") gname="epos";
    string rep2 = systype2;
    string canname = title+"_"+gname;
    TCanvas * c = new TCanvas(canname.data(), canname.data(), 1200, 900);
    c->Draw();
    c->Divide(2,3);
    //==============================================================================
    c->cd(1);
    gPad->SetBottomMargin(0.008);
    string erange = etarange;
    erange.replace(erange.find("_"),1,"< #eta <");
    string crange = centrange;
    crange.replace(centrange.find("_"),1," - ");
    crange = crange+"%";
    gDefault->SetMarkerStyle(25);
    gDefault->SetMarkerColor(kRed);
    gDefault->SetLineColor(kRed);
    double xminDefault,yminDefault,xmaxDefault,ymaxDefault;
    gDefault->ComputeRange(xminDefault,yminDefault,xmaxDefault,ymaxDefault);
    gSys1->SetMarkerStyle(20);
    gSys1->SetMarkerColor(kBlue);
    gSys1->SetLineColor(kBlue);
    double xminSys1,yminSys1,xmaxSys1,ymaxSys1;
    gSys1->ComputeRange(xminSys1,yminSys1,xmaxSys1,ymaxSys1);
    double xminSys2=0;
    double yminSys2=0;
    double xmaxSys2=0;
    double ymaxSys2=0;
    if (gSys2) {
        gSys2->SetMarkerStyle(20);
        gSys2->SetMarkerColor(kGreen+2);
        gSys2->SetLineColor(kGreen+2);
        gSys2->ComputeRange(xminSys2,yminSys2,xmaxSys2,ymaxSys2);
    }
    double minx = 0;
    double maxx = 10;
    double minxdata = 0.3;
    double maxxdata = 8;
    double minxdata2 = 0.3;
    double maxxdata2 = 3.0;

    string rng = erange;
    //cout<<"title: "<<title<<endl;
    if (title.find("int")!=std::string::npos) {
        minx = -3;
        maxx = 3;
        minxdata = -2.4;
        maxxdata = 2.4;
        minxdata2 = 0.3;
        maxxdata2 = 3.0;
        rng = crange;
        //cout<<"set minx: "<<minx<<endl;
    }

    TH1D * h = new TH1D("h", "h", 100, minx, maxx);
    h->SetDirectory(0);
    double setymin = 0;
    if (min(yminSys1,yminDefault)<0) setymin = min(yminDefault,yminSys1);
    double setymax = max(ymaxDefault,ymaxSys1);
    if (gSys2) {
        if (yminSys2<setymin) setymin = yminSys2;
        setymax = max(setymax,ymaxSys2);
    }
    if (setymin==0) setymin = 0.0001*setymax;
    h->SetMinimum(setymin);
    h->SetMaximum(1.3998*setymax);
    h->SetXTitle(xlabel.data());
    h->SetYTitle(ylabel.data());
    h->GetXaxis()->SetLabelFont(43);
    h->GetXaxis()->SetLabelSize(14);
    h->GetXaxis()->SetTitleFont(43);
    h->GetXaxis()->SetTitleSize(20);
    h->GetXaxis()->SetTitleOffset(2.5);
    h->GetXaxis()->CenterTitle(1);
    h->GetYaxis()->SetLabelFont(43);
    h->GetYaxis()->SetLabelSize(14);
    h->GetYaxis()->SetTitleFont(43);
    h->GetYaxis()->SetTitleSize(20);
    h->GetYaxis()->SetTitleOffset(2.8);
    h->GetYaxis()->CenterTitle(1);
    h->Draw();
    TLatex * lcalc = new TLatex(0.1*(maxx-minx)+minx,0.92*(1.4*setymax-setymin)+setymin,replay.data());
    lcalc->SetTextFont(43);
    lcalc->SetTextSize(26);
    lcalc->Draw();
    TLatex * lr = new TLatex(0.1*(maxx-minx)+minx, 0.82*(1.4*setymax-setymin)+setymin, crange.data());
    lr->SetTextFont(43);
    lr->SetTextSize(26);
    lr->Draw();
    TLatex * lr2 = new TLatex(0.1*(maxx-minx)+minx, 0.72*(1.4*setymax-setymin)+setymin, erange.data());
    lr2->SetTextFont(43);
    lr2->SetTextSize(26);
    if (title.find("gint")==std::string::npos) lr2->Draw();
    gSys1->Draw("p");
    gDefault->Draw("p");
    TLegend * leg = new TLegend(0.75, 0.75, 0.89, 0.95);
    leg->SetBorderSize(0);
    leg->SetFillColor(kWhite);
    leg->SetTextFont(43);
    leg->SetTextSize(24);
    leg->AddEntry(gSys1,systype1.data(),"lp");
    if (gSys2) {
        gSys2->Draw("p");
        leg->AddEntry(gSys2,systype2.data(),"lp");
    }
    leg->AddEntry(gDefault,"default","lp");
    leg->Draw();
    TGraph * grmin0 = 0;
    TGraph * grmax0 = 0;
    TGraph * grshade0 = 0;
    TGraph * grmin1 = 0;
    TGraph * grmax1 = 0;
    TGraph * grshade1 = 0;
    string gname1 = canname+"_"+systype1;
    string gname2 = canname+"_"+systype2;
    TGraphErrors * gRatio = ErrorPlot(gname1.data(), pt, true, 0, gSys1, gDefault, grshade0, grmin0, grmax0, 20, kBlue);
    TGraphErrors * gRatio2 = 0;
    if (gSys2) gRatio2 = ErrorPlot(gname2.data(), pt, true, 0, gSys2, gDefault, grshade1, grmin1, grmax1, 20, kGreen+2);
    TGraph * gdmin0 = 0;
    TGraph * gdmax0 = 0;
    TGraph * gdshade0 = 0;
    TGraph * gdmin1 = 0;
    TGraph * gdmax1 = 0;
    TGraph * gdshade1 = 0;
    string gdname1 = canname+"_"+systype1+"_dif";
    string gdname2 = "";
    if (gSys2) gdname2 = canname+"_"+systype2+"_dif";
    TGraphErrors * gDiff = ErrorPlot(gdname1.data(), pt, false, 0, gSys1, gDefault, gdshade0, gdmin0, gdmax0, 20, kBlue);
    TGraphErrors * gDiff2 = 0;
    if (gSys2) gDiff2 = ErrorPlot(gdname2.data(), pt, false, 0, gSys2, gDefault, gdshade1, gdmin1, gdmax1, 20, kGreen+2);
    //==============================================================================
    c->cd(3);
    gPad->SetBottomMargin(0.008);
    TH1D * hr = new TH1D("hr", "hr", 100, minx, maxx);
    hr->SetDirectory(0);
    hr->SetMinimum(0.901);
    hr->SetMaximum(0.99*1.1);
    for (int i = 0; i<gRatio->GetN(); i++) {
        if (gRatio->GetY()[i]+gRatio->GetEY()[i] >1.1) {
            hr->SetMinimum(0.801);
            hr->SetMaximum(0.99*1.2);
        }
    }
    for (int i = 0; i<gRatio->GetN(); i++) {
        if (gRatio->GetY()[i]+gRatio->GetEY()[i] >1.2) {
            hr->SetMinimum(0.501);
            hr->SetMaximum(0.99*1.5);
        }
    }
    hr->SetXTitle(xlabel.data());
    hr->SetYTitle(Form("%s/%s{default}",ylabel.data(),ylabel.data()));
    hr->GetXaxis()->SetLabelFont(43);
    hr->GetXaxis()->SetLabelSize(14);
    hr->GetXaxis()->SetTitleFont(43);
    hr->GetXaxis()->SetTitleSize(20);
    hr->GetXaxis()->SetTitleOffset(2.5);
    hr->GetXaxis()->CenterTitle(1);
    hr->GetYaxis()->SetLabelFont(43);
    hr->GetYaxis()->SetLabelSize(14);
    hr->GetYaxis()->SetTitleFont(43);
    hr->GetYaxis()->SetTitleSize(20);
    hr->GetYaxis()->SetTitleOffset(2.8);
    hr->GetYaxis()->CenterTitle(1);
    gPad->SetGrid(1,1);
    hr->Draw();
    TLine * hrline = new TLine(minx,1.,maxx,1.);
    hrline->SetLineColor(kBlack);
    hrline->SetLineWidth(1);
    hrline->Draw();
    gRatio->Draw("p");
    if (gSys2 ) gRatio2->Draw("p");
    gDiff->ComputeRange(xminSys1,yminSys1,xmaxSys1,ymaxSys1);
    if (gSys2) gDiff2->ComputeRange(xminSys2,yminSys2,xmaxSys2,ymaxSys2);
    //==============================================================================
    c->cd(4);
    gPad->SetBottomMargin(0.008);
    crange = crange+"%";
    if (setymin==0) setymin=0.0001*setymax;
    if (hpercent==0 && pt) {
        hpercent = new TH1D("hpercent","hpercent",100,minx,maxx);
        hpercent->SetXTitle(hr->GetXaxis()->GetTitle());
        hpercent->SetYTitle("% uncertainty");
        hpercent->SetMinimum(-20);
        hpercent->SetMaximum(40);
    }
    if (hpercentint==0 && !pt) {
        hpercentint = new TH1D("hpercent","hpercent",100,minx,maxx);
        hpercentint->SetXTitle(hr->GetXaxis()->GetTitle());
        hpercentint->SetYTitle("% uncertainty");
        hpercentint->SetMinimum(-20);
        hpercentint->SetMaximum(40);
    }
    if (pt) {
        hpercent->Draw();
    } else {
        hpercentint->Draw();
    }
    grshade0->Draw("f");
    grmin0->Draw("l");
    grmax0->Draw("l");
    if (gSys2) {
        grshade1->Draw("f");
        grmin1->Draw("l");
        grmax1->Draw("l");
    }
    //=========================================================================================
    c->cd(5);
    TH1D * hd = new TH1D("hd", "hd", 100, minx, maxx);
    hd->SetDirectory(0);
    setymin = 0;
    if (yminSys1<0) setymin = yminSys1;
    if (gSys2 && yminSys2<setymin) setymin = yminSys2;
    setymax = max(ymaxSys1,ymaxSys2);
    hd->SetMinimum(setymin-0.1*(setymax-setymin));
    hd->SetMaximum(setymax+0.1*(setymax-setymin));
    hd->SetXTitle(xlabel.data());
    hd->SetYTitle(Form("%s - %s{default} (#times 1000)",ylabel.data(),ylabel.data()));
    hd->GetXaxis()->SetLabelFont(43);
    hd->GetXaxis()->SetLabelSize(14);
    hd->GetXaxis()->SetTitleFont(43);
    hd->GetXaxis()->SetTitleSize(20);
    hd->GetXaxis()->SetTitleOffset(2.5);
    hd->GetXaxis()->CenterTitle(1);
    hd->GetYaxis()->SetLabelFont(43);
    hd->GetYaxis()->SetLabelSize(14);
    hd->GetYaxis()->SetTitleFont(43);
    hd->GetYaxis()->SetTitleSize(20);
    hd->GetYaxis()->SetTitleOffset(2.8);
    hd->GetYaxis()->CenterTitle(1);
    gPad->SetGrid(1,1);
    hd->Draw();
    gDiff->Draw("p");
    if (gSys2) gDiff2->Draw("p");

    //==============================================================================
    c->cd(6);
    crange = crange+"%";
  if (setymin==0) setymin=0.0001*setymax;
  if (hdifferr==0 && pt) {
      hdifferr = new TH1D("hdifferr","hdifferr",100,minx,maxx);
      hdifferr->SetXTitle(hr->GetXaxis()->GetTitle());
      hdifferr->SetYTitle("Absolute Uncertainty (x1000)");
      hdifferr->SetMinimum(-1);
      hdifferr->SetMaximum(1);
    }
    if (hdifferrint==0 && !pt) {
        hdifferrint = new TH1D("hdifferr","hdifferr",100,minx,maxx);
        hdifferrint->SetXTitle(hr->GetXaxis()->GetTitle());
        hdifferrint->SetYTitle("Absolute Uncertainty (x 1000)");
        hdifferrint->SetMinimum(-1);
        hdifferrint->SetMaximum(1);
    }
    if (pt) {
        hdifferr->Draw();
    } else {
        hdifferrint->Draw();
    }

    gdshade0->Draw("f");
    gdmin0->Draw("l");
    gdmax0->Draw("l");
    if (gSys2) {
        gdshade1->Draw("f");
        gdmin1->Draw("l");
        gdmax1->Draw("l");
    }
    string outdir = Form("systematics/%s",replay.data());
    FILE * ftest = fopen(outdir.data(),"r");
    if (ftest==NULL) {
        system(Form("mkdir %s",outdir.data()));
    } else {
        fclose(ftest);
    }
    if (title.find("int")!=std::string::npos) {
        c->Print(Form("systematics/%s/%s_%s_%s.pdf",replay.data(),gname.data(),title.data(),centrange.data()),"pdf");
    } else {
        c->Print(Form("systematics/%s/%s_%s_%s_%s.pdf",replay.data(),gname.data(),title.data(),etarange.data(),centrange.data()),"pdf");
    }
    return c;
}
