/// \file DetectorConstruction.cc
/// \brief Implementation of the DetectorConstruction class

#include "DetectorConstruction.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include <G4Tubs.hh>
#include <G4RotationMatrix.hh>
#include <G4ThreeVector.hh>
#include <G4UnionSolid.hh>
#include <G4SubtractionSolid.hh>
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include <G4VisAttributes.hh>

#define pi 3.14159265359

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction()
{
    fDetectorMessenger = new DetectorMessenger(this);
    Xeradius = 4.0;
    Xehalflength = 4.0;
    DefineMaterial();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{
    delete fDetectorMessenger;
 }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetectorConstruction::DefineMaterial()
{
  G4Element *Xe = new G4Element("Xenon", "Xe", 54., 131.293 * g / mole);
  LXe = new G4Material("LXe", 2.862 * g / cm3, 1, kStateLiquid,
                                   177.05 * kelvin, 1.5 * atmosphere);
  
  // DR 20180518 - Density according to:
  // -
  // https://xe1t-wiki.lngs.infn.it/doku.php?id=xenon:xenon1t:deg:tpc:targetmass
  // -
  // https://xe1t-wiki.lngs.infn.it/doku.php?id=xenon:xenon1t:analysis:sciencerun1:sc_summary
  LXe->AddElement(Xe, 1);
  G4NistManager* nist = G4NistManager::Instance();
  Air = nist->FindOrBuildMaterial("G4_AIR");
  Water = nist->FindOrBuildMaterial("G4_WATER");
}
G4VPhysicalVolume* DetectorConstruction::Construct()
{  
  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;
 
  // World
  G4double world_sizeXYZ = 0.2*m;
  
  G4Box* solidWorld =    
    new G4Box("World",                       //its name
       0.5*world_sizeXYZ, 0.5*world_sizeXYZ, 0.5*world_sizeXYZ);     //its size
      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        Air,           //its material
                        "World");            //its name
                                   
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking   
  // LXe cyclinder
  // 

  G4Tubs* solidXecylinder =    
    new G4Tubs("solidXecylinder",                    //its name
        0, Xeradius*cm, Xehalflength*cm,0, 360*deg); //its size
      
  G4LogicalVolume* logicXecylinder =                         
    new G4LogicalVolume(solidXecylinder,            //its solid
                        LXe,             //its material
                        "logicXecylinder");         //its name
               
  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(0,0,0),         //at (0,0,0)
                    logicXecylinder,                //its logical volume
                    "Xecylinder",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking  

  return physWorld;
}

void DetectorConstruction::setXeradius(G4float value)
{
  Xeradius = value; 
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}

void DetectorConstruction::setXehalflength(G4float value)
{
  Xehalflength = value; 
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
