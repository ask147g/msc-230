#include "G4RunManagerFactory.hh"
#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "QGSP_BERT_HP.hh"
#include "G4ParallelWorldPhysics.hh"

#include "MSCPhysicalConstruction.hh"
#include "MSCActionInitialization.hh"

int main(int argc, char** argv) {
    G4UIExecutive* ui = nullptr;
    if (argc == 1) {
        ui = new G4UIExecutive(argc, argv);
    }

    int seed = (unsigned)clock();
    if (argc == 3) {
        seed = std::atoi(argv[2]);
    }

    CLHEP::HepRandom::setTheEngine(new CLHEP::MTwistEngine); 
    CLHEP::HepRandom::setTheSeed(seed); 

    auto runManager = G4RunManagerFactory::CreateRunManager();

    MSCPhysicalConstruction* world = new MSCPhysicalConstruction();
    runManager->SetUserInitialization(world);

    auto physics = new QGSP_BERT_HP();
    runManager->SetUserInitialization(physics);
    runManager->SetUserInitialization(new MSCActionInitialization());
    runManager->Initialize();

    G4VisManager *visManager = new G4VisExecutive();
	visManager->Initialize();
	
	G4UImanager *UImanager = G4UImanager::GetUIpointer();
	
	if ( ! ui ) {
    // batch mode
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command+fileName);
    }
    else {
    // interactive mode
        UImanager->ApplyCommand("/control/execute init_vis.mac");
        ui->SessionStart();
        delete ui;
    }

    G4cout << seed << G4endl;
	
    delete visManager;
    delete runManager;
	return 0;
}