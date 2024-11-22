/// \file DetectorConstruction.hh
/// \brief Definition of the DetectorConstruction class

#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4NistManager.hh"

#include "DetectorMessenger.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;

/// Detector construction class to define materials and geometry.

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
    DetectorConstruction();
    virtual ~DetectorConstruction();

    virtual G4VPhysicalVolume* Construct();
    void DefineMaterial();
    //G4LogicalVolume* GetScoringVolume() const { return fScoringVolume; }
    void setXehalflength(G4float);
    void setXeradius(G4float);
    G4float GetXeradius () {return Xeradius;};
    G4float GetXehalflength () {return Xehalflength;};
    G4float Xeradius,Xehalflength;
  protected:
    G4LogicalVolume*  fScoringVolume;
    G4Material *Air,*Water,*LXe;
    DetectorMessenger* fDetectorMessenger;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

