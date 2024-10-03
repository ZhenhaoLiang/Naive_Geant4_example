#include "G4VUserDetectorConstruction.hh"

class BeginnerDetectorConstruction : public G4VUserDetectorConstruction {
public:
	virtual G4VPhysicalVolume* Construct();
};
