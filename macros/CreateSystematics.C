# include "TCanvas.h"
# include "TDirectory.h"
# include "TF1.h"
# include "TFile.h"
# include "TGraphErrors.h"
# include "TH1.h"
# include "TLegend.h"
# include "TLine.h"
# include "TList.h"
# include "TPaveText.h"
# include "TString.h"
# include <iostream>
# include <stdio.h>

using namespace std;

double maxR(double val);

TCanvas *  CreateSystematics2( string replay = "", TGraphErrors * gDefault = 0, TGraphErrors * gSys1 = 0, string stattype1 = "", TGraphErrors * gSys2 = 0, string stattype2 = "", TGraphErrors * gRatio = 0, TGraphErrors * gRatio2 = 0, TGraphErrors * gDiff = 0, TGraphErrors * gDiff2 = 0, string etarange = "", string centrange = "", string xlabel = "", string ylabel = "",  string title = "" );

void CreateSystematics(string name) {
    TFile * fin = new TFile(name.data(),"update");

    TList * l = (TList *) fin->GetListOfKeys();
    int indx = 0;
    bool defaultFound = false;
    bool tightFound = false;
    bool looseFound = false;
    bool wideFound = false;
    bool narrowFound = false;
    string base;
    while( true) {
        base = l->At(indx)->GetName();
        if (base=="default") {
            defaultFound = true;
            //  cout<<"default found"<<endl;
        }
        if (base=="tight" || base=="tight2") {
            tightFound = true;
            // cout<<"tight found"<<endl;
        }
        if (base=="loose") {
            looseFound = true;
            // cout<<"loose found"<<endl;
        }
        if (base=="wide") {
            wideFound = true;
            // cout<<"wide found"<<endl;
        }
        if (base=="narrow") {
            narrowFound = true;
            // cout<<"narrowFound"<<endl;
        }
        if (l->At(indx)==l->Last()) break;
        ++indx;
    }
    if (defaultFound) {
        TDirectory * defaultDir = (TDirectory *) fin->Get("default");
        indx = 0;
        l = (TList *) defaultDir->GetListOfKeys();
        while (true) {
            string base2 = l->At(indx)->GetName();
            cout<<"******************************** "<<base2<<" **************************************"<<endl;
            if (base2=="N1SUB2") {++indx; continue;}
            if (base2=="N1SUB3") {++indx; continue;}
            if (base2=="N1SUB3_decor") {++indx; continue;}
            TDirectory * subdir = (TDirectory *) defaultDir->Get(base2.data());
            TList * lsub = (TList *) subdir->GetListOfKeys();
            int subindx = 0;
            string subbase = lsub->At(subindx)->GetName();
            while (true) {
	            TDirectory * subsubdir = (TDirectory *) subdir->Get(subbase.data());
            	TList * lsubsub = (TList *) subsubdir->GetListOfKeys();
            	int subsubindx = 0;
            	while (true) {
	                string subsubbase = lsubsub->At(subsubindx)->GetName();
                	string stight = "tight2/"+base2;
                	// if (base=="tight2") stight = "tight2/"+base2;
                	string sloose = "loose/"+base2;
                	string swide = "wide/"+base2;
                	string snarrow = "narrow/"+base2;
                    stight+="/"+subbase;
                    sloose+="/"+subbase;
                	swide+="/"+subbase;
                	snarrow+="/"+subbase;
                	stight+="/"+subsubbase;
                	sloose+="/"+subsubbase;
                	swide+="/"+subsubbase;
                	snarrow+="/"+subsubbase;
                	TDirectory * subsubsubdir = (TDirectory *) subsubdir->Get(subsubbase.data());
                	TList * lsubsubsub = (TList *) subsubsubdir->GetListOfKeys();
                	int subsubsubindx = 0;
                	string ytitle = "";
	                while (true) {
	                    string subsubsubbase = lsubsubsub->At(subsubsubindx)->GetName();
	                    if (subsubsubbase=="h") {
                	        ytitle = ((TH1D *) subsubsubdir->Get("h"))->GetYaxis()->GetTitle();
                	        ytitle = ytitle.substr(0,ytitle.find("}")+1);
	                    }
    	                if (subsubsubbase=="g"||subsubsubbase=="gA"||subsubsubbase=="gB") {
            	            TGraphErrors * g = (TGraphErrors *) subsubsubdir->Get(subsubsubbase.data());
                	        if (tightFound && looseFound) {
                        		TGraphErrors * gSys1 = (TGraphErrors *) fin->Get(Form("%s/%s",sloose.data(),subsubsubbase.data()));
                        		TGraphErrors * gSys2 = (TGraphErrors *) fin->Get(Form("%s/%s",stight.data(),subsubsubbase.data()));
                                TGraphErrors * gDiff = (TGraphErrors *) gSys1->Clone(Form("Difference_%s_%s_%s_%s",sloose.data(),subbase.data(),subsubbase.data(),subsubsubbase.data()));
                                TGraphErrors * gDiff2 = (TGraphErrors *) gSys2->Clone(Form("Difference_%s_%s_%s_%s",stight.data(),subbase.data(),subsubbase.data(),subsubsubbase.data()));
                                TGraphErrors * gRatio = (TGraphErrors *) gSys1->Clone(Form("Ratio_%s_%s_%s_%s",sloose.data(),subbase.data(),subsubbase.data(),subsubsubbase.data()));
                                TGraphErrors * gRatio2 = (TGraphErrors *) gSys2->Clone(Form("Ratio_%s_%s_%s_%s",stight.data(),subbase.data(),subsubbase.data(),subsubsubbase.data()));
                        		TCanvas * can =  CreateSystematics2( base2 ,g, gSys1, "loose", gSys2, "tight", gRatio, gRatio2, gDiff, gDiff2, subbase, subsubbase,"p_{T} (GeV/c)", ytitle, subsubsubbase.data() );
                                gDiff->SetMarkerColor(kBlue);
                                gDiff->SetLineColor(kBlue);
                                gDiff2->SetMarkerColor(kGreen+2);
                                gDiff2->SetLineColor(kGreen+2);
                                gRatio->SetMarkerColor(kBlue);
                                gRatio->SetLineColor(kBlue);
                                gRatio2->SetMarkerColor(kGreen+2);
                                gRatio2->SetLineColor(kGreen+2);
        		                subsubsubdir->cd();
                                gDiff->Write();
                                gDiff2->Write();
                                gRatio->Write();
                                gRatio2->Write();
                        		can->Write();
                        		can->Close();
        	                }
                	        if (narrowFound && wideFound) {
                		        TGraphErrors * gSys1 = (TGraphErrors *) fin->Get(Form("%s/%s",swide.data(),subsubsubbase.data()));
                        		TGraphErrors * gSys2 = (TGraphErrors *) fin->Get(Form("%s/%s",snarrow.data(),subsubsubbase.data()));
                                TGraphErrors * gDiff = (TGraphErrors *) gSys1->Clone(Form("Difference_%s_%s_%s_%s",swide.data(),subbase.data(),subsubbase.data(),subsubsubbase.data()));
                                TGraphErrors * gDiff2 = (TGraphErrors *) gSys2->Clone(Form("Difference_%s_%s_%s_%s",snarrow.data(),subbase.data(),subsubbase.data(),subsubsubbase.data()));
                                TGraphErrors * gRatio = (TGraphErrors *) gSys1->Clone(Form("Ratio_%s_%s_%s_%s",swide.data(),subbase.data(),subsubbase.data(),subsubsubbase.data()));
                                TGraphErrors * gRatio2 = (TGraphErrors *) gSys2->Clone(Form("Ratio_%s_%s_%s_%s",snarrow.data(),subbase.data(),subsubbase.data(),subsubsubbase.data()));
                        		TCanvas * can =  CreateSystematics2(base2, g, gSys1, "wide", gSys2, "narrow", gRatio, gRatio2, gDiff, gDiff2, subbase, subsubbase, "p_{T} (GeV/c)", ytitle, subsubsubbase.data() );
                                gDiff->SetMarkerColor(kBlue);
                                gDiff->SetLineColor(kBlue);
                                gDiff2->SetMarkerColor(kGreen+2);
                                gDiff2->SetLineColor(kGreen+2);
                                gRatio->SetMarkerColor(kBlue);
                                gRatio->SetLineColor(kBlue);
                                gRatio2->SetMarkerColor(kGreen+2);
                                gRatio2->SetLineColor(kGreen+2);
                        		subsubsubdir->cd();
                                gDiff->Write();
                                gDiff2->Write();
                                gRatio->Write();
                                gRatio2->Write();
                        		can->Write();
                        		can->Close();
        	                }
    	                }
    	                if (subsubsubbase=="gint"||subsubsubbase=="gintA"||subsubsubbase=="gintB") {
                	        TGraphErrors * g = (TGraphErrors *) subsubsubdir->Get(subsubsubbase.data());
                	        if (tightFound && looseFound) {
                        		TGraphErrors * gSys1 = (TGraphErrors *) fin->Get(Form("%s/%s",sloose.data(),subsubsubbase.data()));
                        		TGraphErrors * gSys2 = (TGraphErrors *) fin->Get(Form("%s/%s",stight.data(),subsubsubbase.data()));
                                TGraphErrors * gDiff = (TGraphErrors *) gSys1->Clone(Form("Difference_%s_%s_%s_%s",sloose.data(),subbase.data(),subsubbase.data(),subsubsubbase.data()));
                                TGraphErrors * gDiff2 = (TGraphErrors *) gSys2->Clone(Form("Difference_%s_%s_%s_%s",stight.data(),subbase.data(),subsubbase.data(),subsubsubbase.data()));
                                TGraphErrors * gRatio = (TGraphErrors *) gSys1->Clone(Form("Ratio_%s_%s_%s_%s",sloose.data(),subbase.data(),subsubbase.data(),subsubsubbase.data()));
                                TGraphErrors * gRatio2 = (TGraphErrors *) gSys2->Clone(Form("Ratio_%s_%s_%s_%s",stight.data(),subbase.data(),subsubbase.data(),subsubsubbase.data()));
                        		TCanvas * can =  CreateSystematics2( base2, g, gSys1, "loose", gSys2, "tight", gRatio, gRatio2, gDiff, gDiff2, subbase, subsubbase, "#eta", ytitle, subsubsubbase.data() );
                                gDiff->SetMarkerColor(kBlue);
                                gDiff->SetLineColor(kBlue);
                                gDiff2->SetMarkerColor(kGreen+2);
                                gDiff2->SetLineColor(kGreen+2);
                                gRatio->SetMarkerColor(kBlue);
                                gRatio->SetLineColor(kBlue);
                                gRatio2->SetMarkerColor(kGreen+2);
                                gRatio2->SetLineColor(kGreen+2);
                        		subsubsubdir->cd();
                                gDiff->Write();
                                gDiff2->Write();
                                gRatio->Write();
                                gRatio2->Write();
                        		can->Write();
                        		can->Close();
        	                }
        	                if (narrowFound && wideFound) {
                        		TGraphErrors * gSys1 = (TGraphErrors *) fin->Get(Form("%s/%s",swide.data(),subsubsubbase.data()));
                        		TGraphErrors * gSys2 = (TGraphErrors *) fin->Get(Form("%s/%s",snarrow.data(),subsubsubbase.data()));
                                TGraphErrors * gDiff = (TGraphErrors *) gSys1->Clone(Form("Difference_%s_%s_%s_%s",swide.data(),subbase.data(),subsubbase.data(),subsubsubbase.data()));
                                TGraphErrors * gDiff2 = (TGraphErrors *) gSys2->Clone(Form("Difference_%s_%s_%s_%s",snarrow.data(),subbase.data(),subsubbase.data(),subsubsubbase.data()));
                                TGraphErrors * gRatio = (TGraphErrors *) gSys1->Clone(Form("Ratio_%s_%s_%s_%s",swide.data(),subbase.data(),subsubbase.data(),subsubsubbase.data()));
                                TGraphErrors * gRatio2 = (TGraphErrors *) gSys2->Clone(Form("Ratio_%s_%s_%s_%s",snarrow.data(),subbase.data(),subsubbase.data(),subsubsubbase.data()));
                        		TCanvas * can =  CreateSystematics2( base2, g, gSys1, "wide", gSys2, "narrow", gRatio, gRatio2, gDiff, gDiff2, subbase, subsubbase, "#eta", ytitle, subsubsubbase.data() );
                                gDiff->SetMarkerColor(kBlue);
                                gDiff->SetLineColor(kBlue);
                                gDiff2->SetMarkerColor(kGreen+2);
                                gDiff2->SetLineColor(kGreen+2);
                                gRatio->SetMarkerColor(kBlue);
                                gRatio->SetLineColor(kBlue);
                                gRatio2->SetMarkerColor(kGreen+2);
                                gRatio2->SetLineColor(kGreen+2);
                        		subsubsubdir->cd();
                                gDiff->Write();
                                gDiff2->Write();
                                gRatio->Write();
                                gRatio2->Write();
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

double maxR(double val) {
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

TCanvas *  CreateSystematics2( string replay, TGraphErrors * gDefault, TGraphErrors * gSys1, string systype1, TGraphErrors * gSys2, string systype2, TGraphErrors * gRatio, TGraphErrors * gRatio2, TGraphErrors * gDiff, TGraphErrors * gDiff2, string etarange, string centrange, string xlabel, string ylabel, string title ) {
    //cout<<"In Create: "<<endl;
    //cout<<"        ranges: "<<etarange<<"\t"<<centrange<<endl;
    //cout<<"   axis labels: "<<xlabel<<"\t"<<ylabel<<"\t"<<endl;
    //cout<<"         title: "<<title<<endl;
    string gname="trackQuality";
    if (systype2=="wide"||systype2=="narrow") gname = "vtxRange";
    string rep2=systype2;
    string canname = "syserr_"+replay+"_"+title+"_"+etarange+"_"+centrange+"_"+gname;
    //cout<<"       canname: "<<canname<<endl;
    //cout<<gDefault<<"\t"<<gSys1<<"\t"<<gSys2<<endl;
    TCanvas * c = new TCanvas(canname.data(), canname.data(), 600, 900);
    c->Draw();
    c->Divide(1,3,0.0,0.0);
    c->cd(1);
    string erange = etarange;
    erange.replace(erange.find("_"),1,"< #eta <");
    string crange = centrange;
    crange.replace(centrange.find("_"),1," - ");
    crange=crange+"%";
    gDefault->SetMarkerStyle(25);
    gDefault->SetMarkerColor(kRed);
    gDefault->SetLineColor(kRed);
    double xminDefault, yminDefault, xmaxDefault, ymaxDefault;
    gDefault->ComputeRange(xminDefault, yminDefault, xmaxDefault, ymaxDefault);
    gSys1->SetMarkerStyle(20);
    gSys1->SetMarkerColor(kBlue);
    gSys1->SetLineColor(kBlue);
    double xminSys1, yminSys1, xmaxSys1, ymaxSys1;
    gSys1->ComputeRange(xminSys1, yminSys1, xmaxSys1, ymaxSys1);
    double xminSys2 = 0;
    double yminSys2 = 0;
    double xmaxSys2 = 0;
    double ymaxSys2 = 0;
    if (systype2!="") {
        gSys2->SetMarkerStyle(20);
        gSys2->SetMarkerColor(kGreen+2);
        gSys2->SetLineColor(kGreen+2);
        gSys2->ComputeRange(xminSys2, yminSys2, xmaxSys2, ymaxSys2);
    }

    double minx = 0;
    double maxx = 10;
    string rng = erange;
    if (title.find("int")!=std::string::npos) {
        minx = -3;
        maxx = 3;
        rng = crange;
    }

    TH1D * h = new TH1D("h", "h", 100, minx, maxx);
    h->SetDirectory(0);
    double setymin = 0;
    if (min(yminSys1,yminDefault)<0) setymin = min(yminDefault,yminSys1);
    double setymax = max(ymaxDefault,ymaxSys1);
    if (rep2!="") {
        if (yminSys2<setymin) setymin = yminSys2;
        setymax = max(setymax,ymaxSys2);
    }
    if (setymin==0) setymin=0.0001*setymax;
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
    TPaveText * lcalc = new TPaveText(0.24, 0.68, 0.45, 0.96, "NDC");
    lcalc->SetTextFont(43);
    lcalc->SetTextSize(24);
    lcalc->SetTextAlign(12);
    lcalc->SetFillColor(0);
    lcalc->SetBorderSize(0);
    lcalc->AddText(Form("%s",replay.data()));
    lcalc->AddText(Form("%s",crange.data()));
    if (title.find("gint")==std::string::npos) lcalc->AddText(Form("%s",erange.data()));
    lcalc->Draw();
    gSys1->Draw("p");
    gDefault->Draw("p");
    TLegend * leg = new TLegend(0.75, 0.75, 0.89, 0.95);
    leg->SetBorderSize(0);
    leg->SetFillColor(kWhite);
    leg->SetTextFont(43);
    leg->SetTextSize(24);
    leg->AddEntry(gSys1,systype1.data(),"lp");
    if (rep2!="") {
        gSys2->Draw("p");
        leg->AddEntry(gSys2,systype2.data(),"lp");
    }
    leg->AddEntry(gDefault,"default","lp");
    leg->Draw();
    // TGraphErrors * gRatio = (TGraphErrors *) gSys1->Clone("Ratio");
    for (int i = 0; i<gSys1->GetN(); i++){
        if (gDefault->GetY()[i]!=0) {
            double y1 = gSys1->GetY()[i];
            double ey1 = gSys1->GetEY()[i];
            double y2 = gDefault->GetY()[i];
            double ey2 = gDefault->GetEY()[i];
            gRatio->GetY()[i]=y1/y2;
            double try1 = pow(ey1/y1,2) + pow(ey2/y2,2) - 2*pow(ey1,2)/y1/y2;
            double try2 = pow(ey1/y1,2) + pow(ey2/y2,2) - 2*pow(ey2,2)/y1/y2;
            double try3 =  pow(ey1/y1,2) + pow(ey2/y2,2);
            double err = 0;
            if (try1>0) {
	            err = sqrt(try1);
            } else if (try2>0) {
	            err = sqrt(try2);
            } else if (try3>0) {
    	        err = sqrt(try3);
            } else {
	            cout<<"unable to calculate sys error 1:"<<gSys1->GetX()[i]<<"\t"<<y1<<"\t"<<ey1<<"\t"<<y2<<"\t"<<ey2<<"\t"<<err<<"\t"<<endl;
	            err = ey1*gRatio->GetY()[i]/y1;
            }
            gRatio->GetEY()[i] = err;
        }
    }
    // gRatio2 = (TGraphErrors *) gSys2->Clone("Ratio2");
    if (systype2!="") {
        for (int i = 0; i<gSys2->GetN(); i++){
            if (gDefault->GetY()[i]!=0) {
            	double y1 = gSys2->GetY()[i];
            	double ey1 = gSys2->GetEY()[i];
            	double y2 = gDefault->GetY()[i];
            	double ey2 = gDefault->GetEY()[i];
            	gRatio2->GetY()[i]=y1/y2;
            	double try1 = pow(ey1/y1,2)+pow(ey2/y2,2)-2*pow(ey1,2)/y1/y2;
            	double try2 = pow(ey1/y1,2)+pow(ey2/y2,2)-2*pow(ey2,2)/y1/y2;
            	double try3 =  pow(ey1/y1,2)+pow(ey2/y2,2);
            	double err = 0;
	            if (try1>0) {
	                err = sqrt(try1);
            	} else if (try2>0) {
            	    err = sqrt(try2);
            	} else if (try3>0) {
            	    err = sqrt(try3);
            	} else {
            	    cout<<"unable to calculate sys error 2:"<<gSys1->GetX()[i]<<"\t"<<y1<<"\t"<<ey1<<"\t"<<y2<<"\t"<<ey2<<"\t"<<err<<"\t"<<endl;
            	    err = ey1*gRatio2->GetY()[i]/y1;
	            }
	            gRatio2->GetEY()[i] = err;
            }
        }
    }
    c->cd(2);
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
        if (gRatio->GetY()[i]+gRatio->GetEY()[i]>1.2) {
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
    if (rep2!="" ) gRatio2->Draw("p");

    //TGraphErrors * gDiff = (TGraphErrors *) gSys1->Clone("Difference");
    // gDiff = (TGraphErrors *) gSys1->Clone("Difference");
    for (int i = 0; i<gSys1->GetN(); i++){
        gDiff->GetY()[i]=1000.*(gSys1->GetY()[i]-gDefault->GetY()[i]);
        double eA = gSys1->GetEY()[i];
        double eB = gDefault->GetEY()[i];
        double e = sqrt(fabs(pow(eA,2)-pow(eB,2)));
        gDiff->GetEY()[i] = 1000.*e;
    }
    gDiff->ComputeRange(xminSys1, yminSys1, xmaxSys1, ymaxSys1);
    // TGraphErrors * gDiff2 = 0;
    if (rep2!="") {
        // gDiff2 = (TGraphErrors *) gSys2->Clone("Difference2");
        for (int i = 0; i<gSys2->GetN(); i++){
            gDiff2->GetY()[i]=1000.*(gSys2->GetY()[i]-gDefault->GetY()[i]);
            double eA = gSys2->GetEY()[i];
            double eB = gDefault->GetEY()[i];
            double e = sqrt(fabs(pow(eA,2)-pow(eB,2)));
            gDiff2->GetEY()[i] = 1000.*e;
        }
        gDiff->ComputeRange(xminSys2, yminSys2, xmaxSys2, ymaxSys2);
    }
    c->cd(3);
    TH1D * hd = new TH1D("hd", "hd", 100, minx, maxx);
    hd->SetDirectory(0);
    setymin = 0;
    if (yminSys1<0) setymin = yminSys1;
    if (rep2!="" && yminSys2<setymin) setymin = yminSys2;
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
    if (systype2!="") gDiff2->Draw("p");
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
