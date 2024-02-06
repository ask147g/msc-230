/// \file include/HistoManager.hh
/// \brief Definition of the HistoManager class

#ifndef MSCHistoManager_h
#define MSCHistoManager_h 1

#include "G4AnalysisManager.hh"
#include "G4SystemOfUnits.hh"

class MSCHistoManager {
public:
    MSCHistoManager();
    ~MSCHistoManager();

    void Book();
    void Save();

    void FillNtuple(G4double t, G4double e);
    //void FillNtupleProton(G4int id, G4double t);
    void FillNtupleProtonDelta(G4double t);
private:
    // used to define first object initialization
    // for initial setup ROOT trees
    G4bool fFactoryOn = false;
};

#endif