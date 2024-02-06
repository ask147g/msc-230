#include "MSCPhysicalConstruction.hh"

MSCPhysicalConstruction::MSCPhysicalConstruction() {
    DefineMaterials();
}

MSCPhysicalConstruction::~MSCPhysicalConstruction() {
}

void MSCPhysicalConstruction::DefineMaterials() {
    G4NistManager* nist = G4NistManager::Instance();
    
    G4Element *C = nist->FindOrBuildElement("C");
    G4Element *N = nist->FindOrBuildElement("N");
    G4Element *O = nist->FindOrBuildElement("O");
    G4Element *Ar = nist->FindOrBuildElement("Ar");
    G4Element *H = nist->FindOrBuildElement("H");
    G4Element *Na = nist->FindOrBuildElement("Na");
    G4Element *Mg = nist->FindOrBuildElement("Mg");
    G4Element *Al = nist->FindOrBuildElement("Al");
    G4Element *Si = nist->FindOrBuildElement("Si");
    G4Element *K = nist->FindOrBuildElement("K");
    G4Element *Ca = nist->FindOrBuildElement("Ca");
    G4Element *Fe = nist->FindOrBuildElement("Fe");
    G4Element *Mn = nist->FindOrBuildElement("Mn");
    G4Element *Ni = nist->FindOrBuildElement("Ni");
    G4Element *S = nist->FindOrBuildElement("S");
    G4Element *P = nist->FindOrBuildElement("P");
    G4Element *Cr = nist->FindOrBuildElement("Cr");
    G4Element *As = nist->FindOrBuildElement("As");
    G4Element *Cu = nist->FindOrBuildElement("Cu");
    
    G4Material* airDry = new G4Material("airDry" , 0.00120484*CLHEP::g/CLHEP::cm3, 4, kStateGas);
    airDry->AddElement(C, 0.0001248);
    airDry->AddElement(N, 0.755267);
    airDry->AddElement(O, 0.231781);
    airDry->AddElement(Ar, 0.012827);

    G4Material* airWet = new G4Material("airWet" , 0.000756182*CLHEP::g/CLHEP::cm3, 2, kStateGas);
    airWet->AddElement(H, 2);
    airWet->AddElement(O, 1);

    air = new G4Material ("air", 0.00120484*CLHEP::g/CLHEP::cm3, 2, kStateGas); 
    air->AddMaterial(airDry, 0.98);
    air->AddMaterial(airWet, 0.02);


    concrete = new G4Material("concrete" , 2.3*CLHEP::g/CLHEP::cm3, 10, kStateSolid);
    concrete->AddElement(H, 0.0221);
    concrete->AddElement(C, 0.002484);
    concrete->AddElement(O, 0.574931);
    concrete->AddElement(Na, 0.015208);
    concrete->AddElement(Mg, 0.001266);
    concrete->AddElement(Al, 0.019953);
    concrete->AddElement(Si, 0.304627);
    concrete->AddElement(K, 0.010045);
    concrete->AddElement(Ca, 0.042951);
    concrete->AddElement(Fe, 0.006435);

    steel = new G4Material("steel" , 7.85*CLHEP::g/CLHEP::cm3, 11, kStateSolid);
    steel->AddElement(Fe, 0.97748);
    steel->AddElement(C, 0.0022);
    steel->AddElement(Si, 0.003);
    steel->AddElement(Mn, 0.0065);
    steel->AddElement(Ni, 0.003);
    steel->AddElement(S, 0.0005);
    steel->AddElement(P, 0.0004);
    steel->AddElement(Cr, 0.003);
    steel->AddElement(N, 0.00012);
    steel->AddElement(As, 0.0008);
    steel->AddElement(Cu, 0.003);
}

G4VPhysicalVolume* MSCPhysicalConstruction::Construct() {

    G4NistManager* nist = G4NistManager::Instance();
    //G4Material* env_mat = nist->FindOrBuildMaterial("G4_Galactic");
    G4Box *solidWorld = 
        new G4Box(
            "solidWorld", 
            500/2*CLHEP::cm, 
            500/2*CLHEP::cm, 
            1420/2*CLHEP::cm);

	logicWorld = 
        new G4LogicalVolume(
            solidWorld, 
            air, 
            "logicWorld");
	
	G4VPhysicalVolume* physWorld = 
        new G4PVPlacement(
            0, 
			G4ThreeVector(0., 0., 0.), 
			logicWorld, 
			"physWorld", 
			0, 
			false, 
			0, 
			false); 

    BuildCatcher();
    BuildDetector();
    //BuildProtonDetector();
    
	return physWorld;
}

void MSCPhysicalConstruction::BuildCatcher() {
    G4Box *solidConcreteBox = 
        new G4Box(
            "solidSteelBox", 
            500/2*CLHEP::cm, 
            500/2*CLHEP::cm, 
            450/2*CLHEP::cm);

    G4Tubs *ConcreteHole = new G4Tubs("ConcreteHole",
                                0,
                                15/2*CLHEP::cm,
                                100/2*CLHEP::cm,
                                0,
                                360*CLHEP::degree);

    G4VSolid* concreteSolid = new G4SubtractionSolid("concreteSolid",
                                                    solidConcreteBox,
                                                    ConcreteHole,
                                                    0,
                                                    G4ThreeVector(0, 0, (-450/2+100/2)*CLHEP::cm));

    concreteLogic = 
        new G4LogicalVolume(
            concreteSolid, 
            concrete, 
            "logicConcreteCatcher");

    G4VPhysicalVolume* physConcrete = 
        new G4PVPlacement(
            0, 
			G4ThreeVector(0., 0., 0.), 
			concreteLogic, 
			"physConcrete", 
			logicWorld, 
			false, 
			0, 
			false); 


    G4Box *solidSteelBox = 
        new G4Box(
            "solidSteelBox", 
            100/2*CLHEP::cm, 
            100/2*CLHEP::cm, 
            100/2*CLHEP::cm);

    G4Tubs *SteelHole = new G4Tubs("SteelHole",
                                0,
                                15/2*CLHEP::cm,
                                50/2*CLHEP::cm,
                                0,
                                360*CLHEP::degree);

    G4VSolid* solidSteel = new G4SubtractionSolid("solidSteel",
                                                    solidSteelBox,
                                                    SteelHole,
                                                    0,
                                                    G4ThreeVector(0, 0, (-100/2+50/2)*CLHEP::cm));

    steelLogic = 
        new G4LogicalVolume(
            solidSteel, 
            steel, 
            "logicSteelCatcher");

    G4VPhysicalVolume* physSteel = 
        new G4PVPlacement(
            0, 
			G4ThreeVector(0., 0., -125*CLHEP::cm), 
			steelLogic, 
			"physSteel", 
			concreteLogic, 
			false, 
			0, 
			false); 
}

void MSCPhysicalConstruction::BuildDetector() {
    G4Box *detBox = 
        new G4Box(
            "solidSteelBox", 
            100/2*CLHEP::cm, 
            100/2*CLHEP::cm, 
            1.0/2*CLHEP::cm);

    detectorLogic = 
        new G4LogicalVolume(
            detBox, 
            air, 
            "detectorLogic");

    G4VPhysicalVolume* physDet = 
        new G4PVPlacement(
            0, 
			G4ThreeVector(0., 0., (450/2+1.0/2)*CLHEP::cm), 
			detectorLogic, 
			"physDet", 
			logicWorld, 
			false, 
			0, 
			false); 
}

void MSCPhysicalConstruction::BuildProtonDetector() {
    G4Box *detBox = 
        new G4Box(
            "solidProtonBox", 
            100/2*CLHEP::cm, 
            100/2*CLHEP::cm, 
            1.0/2*CLHEP::cm);

    detectorProtonLogic = 
        new G4LogicalVolume(
            detBox, 
            air, 
            "detectorProtonLogic");

    G4VPhysicalVolume* physDet = 
        new G4PVPlacement(
            0, 
			G4ThreeVector(0., 0., (-580)*CLHEP::cm), 
			detectorProtonLogic, 
			"physProtonDet", 
			logicWorld, 
			false, 
			0, 
			false); 
}