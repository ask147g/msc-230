/// \file src/SteppingAction.cc
/// \brief Implementation of the SteppingAction class

#include "MSCSteppingAction.hh"

MSCSteppingAction::MSCSteppingAction(MSCHistoManager* histo, MSCEventAction* evt) : fHistoManager(histo), fEvtAction(evt) {
}

MSCSteppingAction::~MSCSteppingAction() = default;

void MSCSteppingAction::UserSteppingAction(const G4Step* aStep) {
    G4int pdg = aStep->GetTrack()->GetParticleDefinition()->GetPDGEncoding();

    if (pdg == 2212) { // protons
        if (!steel) {
            const auto det = static_cast<const MSCPhysicalConstruction*>(
                G4RunManager::GetRunManager()->GetUserDetectorConstruction());
            steel = det->GetSteelLogic();
            air = det->GetAirLogic();
            proton = det->GetDetectorProtonLogic();
        }

        if (aStep->GetTrack()->GetParentID() == 0) {
            G4LogicalVolume* volume = 
            aStep->GetPreStepPoint()->GetTouchableHandle()
                ->GetVolume()->GetLogicalVolume();

            auto vol = aStep->GetPostStepPoint()->GetTouchableHandle()
                    ->GetVolume();

            if (!vol) return;
            G4LogicalVolume* volumePost = vol->GetLogicalVolume();
            
            auto mom = aStep->GetTrack()->GetMomentum().z();
            if (mom < 0) return;

            auto time = aStep->GetTrack()->GetGlobalTime()/CLHEP::nanosecond;
            // spect in the in of steel
            if ((volume == air) && (volumePost == proton)) {
                fHistoManager->FillNtupleProtonDelta(time);
                //if (time > fEvtAction->GetMaxValue()) fEvtAction->SetMaxValue(time);
                //if (time < fEvtAction->GetMinValue()) fEvtAction->SetMinValue(time);
            }
        }
    }

    if (pdg != 2112) return; // neutrons

    if (!wall) {
        const auto detConstruction = static_cast<const MSCPhysicalConstruction*>(
            G4RunManager::GetRunManager()->GetUserDetectorConstruction());
        concrete = detConstruction->GetConcreteLogic();
        wall = detConstruction->GetDetectorLogic();
    }

    G4LogicalVolume* volume = 
        aStep->GetPreStepPoint()->GetTouchableHandle()
            ->GetVolume()->GetLogicalVolume();
    
    auto vol = aStep->GetPostStepPoint()->GetTouchableHandle()
            ->GetVolume();

    if (!vol) return;
        G4LogicalVolume* volumePost = vol->GetLogicalVolume();
    
    auto time = aStep->GetTrack()->GetGlobalTime()/CLHEP::microsecond;
    //if (time == 0) return;

    //if ((volume != concrete) && (volume != steel)) {
    //    G4cout << volume->GetName() << G4endl;
    //}

    //G4cout << time << G4endl;

    // spect in the out of Al
    //if ((volume == wall) && (volumePost != wall)) {
    //    fHistoManager->FillNtuple(time);
    //}

    if ((volume == concrete) && (volumePost == wall)) {
        //G4cout << aStep->GetTrack()->GetMomentum().z() << " " << aStep->GetTrack()->GetPosition().z() << G4endl;
        //G4cout << aStep->GetTrack()->GetPosition().z() << G4endl;
        fHistoManager->FillNtuple(time);
    }
}