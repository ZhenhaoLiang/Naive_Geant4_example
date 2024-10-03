#include "Geometry.hh"
#include "G4Box.hh"
#include "G4SystemOfUnits.hh"
#include "G4LogicalVolume.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"

G4VPhysicalVolume* BeginnerDetectorConstruction::Construct() {
	auto nist = G4NistManager::Instance();
	// Solid
	auto solid_world = new G4Box("world", 0.5 * m, 0.5 * m, 0.5 * m);
	// Logic
	auto logic_world = new G4LogicalVolume(solid_world, nist->FindOrBuildMaterial("G4_Pd"), "world");
	// Physics
	auto physical_world = new G4PVPlacement(
		0,
		G4ThreeVector(0, 0, 0),
		logic_world,
		"world",
		0,    //its mother  volume
		false,
		0,
		true
	);

	auto solid_sheild = new G4Box("sheild", 5 * cm, 5 * cm, 2 * cm);
	// Logic
	auto logic_sheild = new G4LogicalVolume(solid_sheild, nist->FindOrBuildMaterial("G4_AIR"), "sheild");
	// Physics
	auto physical_sheild = new G4PVPlacement(
		0,
		G4ThreeVector(0, 0, 10*cm),
		logic_sheild,
		"sheild",
		logic_world,    //its mother  volume
		false,
		0,
		true
	);
	return physical_world;
}

