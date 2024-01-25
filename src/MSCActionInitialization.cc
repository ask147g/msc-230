#include "MSCActionInitialization.hh"

MSCActionInitialization::MSCActionInitialization() {
}

MSCActionInitialization::~MSCActionInitialization() {
}

void MSCActionInitialization::BuildForMaster() const {
    MSCHistoManager*  histo = new MSCHistoManager();
    SetUserAction(new MSCRunAction(histo));
}

void MSCActionInitialization::Build() const {
    MSCHistoManager*  histo = new MSCHistoManager();

    SetUserAction(new MSCPrimaryGenerator());

    MSCRunAction* runAction = new MSCRunAction(histo);
    SetUserAction(runAction);

    MSCEventAction* eventAction = new MSCEventAction(histo);
    SetUserAction(eventAction);
    
    MSCSteppingAction* stepAction = new MSCSteppingAction(histo, eventAction);
    SetUserAction(stepAction);
}