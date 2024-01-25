#include <TMath.h> 
#include <iostream>
#include <fstream> 

void plot() {
    TFile *fe = new TFile("msc-230_1.root");

    TCanvas* c1=new TCanvas("c1","show profile", 900, 600);
    TTree *trN = (TTree*)fe->Get("neutron");
    double time;
    trN->SetBranchAddress("t", &time);
    int entr = trN->GetEntries();
    
    TH1* h1 = new TH1F("h1", "", 1000, 0.0, 3500);
    h1->GetYaxis()->SetTitle("N, neutrons");
    h1->GetXaxis()->SetTitle("t, #mus");
    h1->SetFillColor(1);
    h1->SetLineColor(1);
    
    
    for (int i = 0; i < entr; i++) {
        trN->GetEntry(i);
        h1->Fill(time);
    }
    gPad->SetLogy();
    gPad->SetGridx();
    gPad->SetGridy();

    h1->Draw();

    TCanvas* c2=new TCanvas("c2","show profile", 900, 600);
    TTree *trP = (TTree*)fe->Get("proton");
    double delta;
    trP->SetBranchAddress("dt", &delta);
    int entrP = trP->GetEntries();
    TH1* h2 = new TH1F("h2", "", 1000, 0.0, 50);
    h2->GetYaxis()->SetTitle("N, protons");
    h2->GetXaxis()->SetTitle("#Deltat, ns");
    h2->SetFillColor(1);
    h2->SetLineColor(1);

    for (int i = 0; i < entrP; i++) {
        trP->GetEntry(i);
        h2->Fill(delta);
    }
    gPad->SetLogy();
    gPad->SetGridx();
    gPad->SetGridy();
    h2->Draw();
}