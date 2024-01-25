#include <TMath.h> 
#include <iostream>
#include <fstream> 
#include <vector>
#include <algorithm>

void table() {
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
    

    // Output neutron histogram
    std::ofstream neutron;
    neutron.open("neutron.csv");

    std::vector<double> neutronTime;
    for (int i = 0; i < entr; i++) {
        trN->GetEntry(i);
        if (time <= 3500) {
            neutronTime.push_back(time);
        }
        h1->Fill(time);
    }

    std::sort(neutronTime.begin(), neutronTime.end());

    double n_max = *(neutronTime.end()-1);
    double step = n_max/1000;

    double min = 0.0;
    int evt = 0;
    int steps = 0;

    for (auto i = neutronTime.begin(); i != neutronTime.end(); i++) {
        if ((*i > min + step*steps) && (*i <= min + step*(steps+1))) {
            evt++;
        }
        else {
            while (1) {
                steps++;
                if ((*i > min + step*steps) && (*i <= min + step*(steps+1))) {
                    break;
                }
            }
            neutron << min + 0.5*step*(2*steps+1) << " " << evt << std::endl;
            evt = 1;
        }
    }

    neutron.close();

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

    // Output neutron histogram
    std::ofstream proton;
    proton.open("proton.csv");

    std::vector<double> protonTime;

    for (int i = 0; i < entrP; i++) {
        trP->GetEntry(i);
        if ((delta <= 50) && (delta != 0)) {
            protonTime.push_back(delta);
        }
        h2->Fill(delta);
    }

    std::sort(protonTime.begin(), protonTime.end());

    n_max = *(protonTime.end()-1);
    std::cout << n_max << std::endl;
    step = n_max/1000;

    min = 0.0;
    evt = 0;
    steps = 0;

    for (auto i = protonTime.begin(); i != protonTime.end(); i++) {
        if ((*i > min + step*steps) && (*i <= min + step*(steps+1))) {
            evt++;
        }
        else {
            while (1) {
                steps++;
                if ((*i > min + step*steps) && (*i <= min + step*(steps+1))) {
                    break;
                }
            }
            proton << min + 0.5*step*(2*steps+1) << " " << evt << std::endl;
            evt = 1;
        }
    }

    proton.close();

    gPad->SetLogy();
    gPad->SetGridx();
    gPad->SetGridy();
    h2->Draw();
}