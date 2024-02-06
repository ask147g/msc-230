#include <TMath.h> 
#include <iostream>
#include <fstream> 

void plot() {
    TFile *fe = new TFile("msc-230r.root");

    TCanvas* c1=new TCanvas("c1","show profile", 900, 600);
    TTree *trN = (TTree*)fe->Get("T");
    Float_t time;
    trN->SetBranchAddress("nt", &time);
    int entr = trN->GetEntries();
    
    TH1* h1 = new TH1F("h1", "", 1000, 46.0, 80);
    h1->GetYaxis()->SetTitle("N, neutrons");
    h1->GetXaxis()->SetTitle("t, ns");
    h1->SetFillColor(1);
    h1->SetLineColor(1);
    
    
    for (int i = 0; i < entr; i++) {
        trN->GetEntry(i);
        //std::cout << time << std::endl;
        h1->Fill(time*1000);
    }
    //gPad->SetLogy();
    gPad->SetGridx();
    gPad->SetGridy();

    h1->Draw();
}