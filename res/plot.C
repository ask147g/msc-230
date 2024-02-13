#include <TMath.h> 
#include <iostream>
#include <fstream> 

void plot() {
    TFile *fe = new TFile("energy/msc-230r.root");

    TCanvas* c1=new TCanvas("c1","show profile", 900, 600);
    TTree *trN = (TTree*)fe->Get("T");
    Float_t time, energy;
    trN->SetBranchAddress("nt", &time);
    trN->SetBranchAddress("ne", &energy);
    int entr = trN->GetEntries();
    
    TH1* h1 = new TH1F("h1", "", 1000, 47, 52);
    h1->GetYaxis()->SetTitle("N, neutrons");
    h1->GetXaxis()->SetTitle("t, ns");
    h1->SetFillColor(1);
    h1->SetLineColor(1);

    TH1* h2 = new TH1F("h2", "", 500, 0, 220);
    h2->GetYaxis()->SetTitle("N, neutrons");
    h2->GetXaxis()->SetTitle("E, MeV");
    h2->SetFillColor(1);
    h2->SetLineColor(1);

    TH2* h3 = new TH2F("h3","",100,0,0.1,100,0,220);

    auto gr = new TGraph();
    gr->SetMarkerStyle(7);
    gr->SetMarkerSize(2);
    gr->GetYaxis()->SetTitle("E, MeV");
    gr->GetXaxis()->SetTitle("t, ns");
    
    
    for (int i = 0; i < entr; i++) {
        trN->GetEntry(i);
        std::cout << time*1000 << " " << energy << std::endl;
        h1->Fill(time*1000);
        h2->Fill(energy);
        h3->Fill(time, energy);
        //if (time < 0.1) {
            gr->AddPoint(time, energy);
        //}
    }
    //gPad->SetLogy();
    gPad->SetGridx();
    gPad->SetGridy();

    h1->Draw();

    TCanvas* c2 = new TCanvas("c2","show profile", 900, 600);
    gPad->SetGridx();
    gPad->SetGridy();
    h2->Draw();

    TCanvas* c3 = new TCanvas("c3","show profile", 900, 600);
    //h3->Draw("COL");
    gr->Draw("AP");
    gPad->SetGridx();
    gPad->SetGridy();
    //gPad->SetLogy();
    //gPad->SetLogx();
}