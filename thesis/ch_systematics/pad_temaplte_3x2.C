
//-------------- 3 by 2

TCanvas * c2 = new TCanvas("c2", "c2", 830, 580);
TPad * pad2[6];
c2->cd();
pad2[0] = new TPad("pad2_0", "pad2_0", 0.0, 0.5, 0.38, 1.0);
pad2[0]->SetLeftMargin(0.22);
pad2[0]->SetTopMargin(0.15);
pad2[0]->SetBottomMargin(0);
pad2[0]->SetRightMargin(0);
pad2[0]->Draw();

c2->cd();
pad2[1] = new TPad("pad2_1", "pad2_1", 0.38, 0.5, 0.69, 1.0);
pad2[1]->SetLeftMargin(0);
pad2[1]->SetRightMargin(0);
pad2[1]->SetTopMargin(0.15);
pad2[1]->SetBottomMargin(0);
pad2[1]->Draw();

c2->cd();
pad2[2] = new TPad("pad2_2", "pad2_2", 0.69, 0.5, 1.0, 1.0);
pad2[2]->SetLeftMargin(0);
pad2[2]->SetRightMargin(0.05);
pad2[2]->SetTopMargin(0.15);
pad2[2]->SetBottomMargin(0);
pad2[2]->Draw();

c2->cd();
pad2[3] = new TPad("pad2_3", "pad2_3", 0.0, 0, 0.38, 0.5);
pad2[3]->SetLeftMargin(0.22);
pad2[3]->SetRightMargin(0);
pad2[3]->SetTopMargin(0);
pad2[3]->SetBottomMargin(0.18);
pad2[3]->SetGrid();
pad2[3]->Draw();

c2->cd();
pad2[4] = new TPad("pad2_4", "pad2_4", 0.38, 0, 0.69, 0.5);
pad2[4]->SetLeftMargin(0);
pad2[4]->SetRightMargin(0);
pad2[4]->SetTopMargin(0);
pad2[4]->SetBottomMargin(0.18);
pad2[4]->SetGrid();
pad2[4]->Draw();

c2->cd();
pad2[5] = new TPad("pad2_5", "pad2_5", 0.69, 0, 1.0, 0.5);
pad2[5]->SetLeftMargin(0);
pad2[5]->SetRightMargin(0.05);
pad2[5]->SetTopMargin(0);
pad2[5]->SetBottomMargin(0.18);
pad2[5]->SetGrid();
pad2[5]->Draw();
