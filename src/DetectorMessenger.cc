#include "DetectorMessenger.hh"
#include "DetectorConstruction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorMessenger::DetectorMessenger(DetectorConstruction * Det)
:fDetector(Det)
{ 
  fGparameter = new G4UIdirectory("/GeometryParameter/");
  fGparameter->SetGuidance("Geometry parameter control.");
  
  fRadiusCmd = new G4UIcmdWithADouble("/GeometryParameter/setXeradius",this);
  fRadiusCmd->SetGuidance("Set radius of Xe cyclinder.");
  fRadiusCmd->SetParameterName("Xeradius",false);
  fRadiusCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  fLengthCmd = new G4UIcmdWithADouble("/GeometryParameter/setXehalflength",this);
  fLengthCmd->SetGuidance("Set half length of Xe cyclinder.");
  fLengthCmd->SetParameterName("Xehalflength",false);
  fLengthCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorMessenger::~DetectorMessenger()
{
  delete fRadiusCmd;
  delete fLengthCmd;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
  if( command == fRadiusCmd )
   { fDetector->setXeradius(fRadiusCmd->GetNewDoubleValue(newValue));}

  if( command == fLengthCmd )
   { fDetector->setXehalflength(fLengthCmd->GetNewDoubleValue(newValue));}
}
