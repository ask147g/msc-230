/// \file include/MSCPhysicalConstruction.hh
/// \brief Definition of the MSCPhysicalConstruction class

#ifndef MSCPhysicalConstruction_h
#define MSCPhysicalConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4RotationMatrix.hh"

#include "G4UnionSolid.hh"
#include "G4SubtractionSolid.hh"
#include "G4IntersectionSolid.hh"

class MSCPhysicalConstruction : public G4VUserDetectorConstruction {
public:
    MSCPhysicalConstruction();
    ~MSCPhysicalConstruction();

    G4LogicalVolume* GetConcreteLogic() const {return concreteLogic;};
    G4LogicalVolume* GetSteelLogic() const {return steelLogic;};
    G4LogicalVolume* GetDetectorLogic() const {return detectorLogic;};
    G4LogicalVolume* GetDetectorProtonLogic() const {return detectorProtonLogic;};
    G4LogicalVolume* GetAirLogic() const {return logicWorld;};

    virtual G4VPhysicalVolume* Construct();

private:
    G4LogicalVolume* logicWorld = nullptr;
    G4LogicalVolume* concreteLogic = nullptr;
    G4LogicalVolume* steelLogic = nullptr;
    G4LogicalVolume* detectorLogic = nullptr;
    G4LogicalVolume* detectorProtonLogic = nullptr;
    
    void DefineMaterials();
    void BuildCatcher();
    void BuildDetector();
    void BuildProtonDetector();

    G4Material* concrete = nullptr;
    G4Material* steel = nullptr;
    G4Material* air = nullptr;
};

#endif