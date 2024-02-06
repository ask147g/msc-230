#include <TMath.h>

void proton() {
    TCanvas* c1=new TCanvas("c1","show profile", 900, 600);

    TH1* h1 = new TH1F("h1", "", 20, -0.5, 0.5);
    h1->GetYaxis()->SetTitle("N, protons");
    h1->GetXaxis()->SetTitle("t, ns");
    h1->SetFillColor(1);
    h1->SetLineColor(1);
    
    Float_t entr = 120000000;
    
    for (int i = 0; i < entr; i++) {
        h1->Fill(0.00);
    }
    //gPad->SetLogy();
    gPad->SetGridx();
    gPad->SetGridy();

    h1->Draw();
}