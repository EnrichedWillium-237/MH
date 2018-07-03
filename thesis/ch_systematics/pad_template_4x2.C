
//------------------- 4 by 2

TCanvas * c0 = new TCanvas("c0", "c0", 1100, 580);
TPad * pad0[8];
c0->cd();
pad0[0] = new TPad("pad0_0", "pad0_0", 0.0, 0.5, 0.28, 1.0);
pad0[0]->SetLeftMargin(0.22);
pad0[0]->SetTopMargin(0.15);
pad0[0]->SetBottomMargin(0);
pad0[0]->SetRightMargin(0);
pad0[0]->Draw();

c0->cd();
pad0[1] = new TPad("pad0_1", "pad0_1", 0.28, 0.5, 0.50, 1.0);
pad0[1]->SetLeftMargin(0);
pad0[1]->SetRightMargin(0);
pad0[1]->SetTopMargin(0.15);
pad0[1]->SetBottomMargin(0);
pad0[1]->Draw();

c0->cd();
pad0[2] = new TPad("pad0_2", "pad0_2", 0.50, 0.5, 0.72, 1.0);
pad0[2]->SetLeftMargin(0);
pad0[2]->SetRightMargin(0);
pad0[2]->SetTopMargin(0.15);
pad0[2]->SetBottomMargin(0);
pad0[2]->Draw();

c0->cd();
pad0[3] = new TPad("pad0_3", "pad0_3", 0.72, 0.5, 0.99, 1.0);
pad0[3]->SetLeftMargin(0);
pad0[3]->SetRightMargin(0.20);
pad0[3]->SetTopMargin(0.15);
pad0[3]->SetBottomMargin(0);
pad0[3]->Draw();

c0->cd();
pad0[4] = new TPad("pad0_4", "pad0_4", 0.0, 0, 0.28, 0.5);
pad0[4]->SetLeftMargin(0.22);
pad0[4]->SetRightMargin(0);
pad0[4]->SetTopMargin(0);
pad0[4]->SetBottomMargin(0.18);
pad0[4]->SetGrid();
pad0[4]->Draw();

c0->cd();
pad0[5] = new TPad("pad0_5", "pad0_5", 0.28, 0, 0.50, 0.5);
pad0[5]->SetLeftMargin(0);
pad0[5]->SetRightMargin(0);
pad0[5]->SetTopMargin(0);
pad0[5]->SetBottomMargin(0.18);
pad0[5]->SetGrid();
pad0[5]->Draw();

c0->cd();
pad0[6] = new TPad("pad0_6", "pad0_6", 0.50, 0, 0.72, 0.5);
pad0[6]->SetLeftMargin(0);
pad0[6]->SetRightMargin(0);
pad0[6]->SetTopMargin(0);
pad0[6]->SetBottomMargin(0.18);
pad0[6]->SetGrid();
pad0[6]->Draw();

c0->cd();
pad0[7] = new TPad("pad0_3", "pad0_3", 0.72, 0, 0.99, 0.5);
pad0[7]->SetLeftMargin(0);
pad0[7]->SetRightMargin(0.20);
pad0[7]->SetTopMargin(0);
pad0[7]->SetBottomMargin(0.18);
pad0[7]->SetGrid();
pad0[7]->Draw();
