/// \file include/SteppingAction.hh
/// \brief Definition of the SteppingAction class

#ifndef MSCSteppingAction_h
#define MSCSteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "G4Step.hh"
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"

#include "MSCHistoManager.hh"
#include "MSCPhysicalConstruction.hh"
#include "MSCEventAction.hh"

class MSCHistoManager;

/// Describes alghoritms for step in volume.

class MSCSteppingAction : public G4UserSteppingAction {
public:
    MSCSteppingAction(MSCHistoManager*, MSCEventAction* evt);
    ~MSCSteppingAction() override;

    void UserSteppingAction(const G4Step*) override;
private:
    G4LogicalVolume* wall = nullptr;
    G4LogicalVolume* concrete = nullptr;
    G4LogicalVolume* steel = nullptr;
    G4LogicalVolume* proton = nullptr;
    G4LogicalVolume* air = nullptr;

    MSCHistoManager* fHistoManager  = nullptr;
    MSCEventAction* fEvtAction = nullptr;
};

#endif