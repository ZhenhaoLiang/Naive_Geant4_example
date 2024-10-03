#include "QGSP_BERT_HP.hh"
#include "G4MTRunManager.hh"
#include "Geometry.hh"
#include "ParticleSource.hh"
#include "G4VUserActionInitialization.hh"
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"

class BeginnerActionInitialization : public G4VUserActionInitialization {
public:
    virtual void Build() const{
        SetUserAction(new BeginnerGeneratorAction);
    }
};

int main(int argc, char** argv){
    G4UIExecutive* ui = nullptr;
    if (argc == 1)
        ui = new G4UIExecutive(argc, argv);

    auto runManager = new G4MTRunManager;

    // geometry construction
    runManager->SetUserInitialization(new BeginnerDetectorConstruction());
    // physics list
    runManager->SetUserInitialization(new QGSP_BERT_HP());
    // User action
    runManager->SetUserInitialization(new BeginnerActionInitialization());

    auto visManager = new G4VisExecutive;
    visManager->Initialize();

    auto UImanager = G4UImanager::GetUIpointer();
    if (!ui) {
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);
    } else {
        UImanager->ApplyCommand("/control/execute vis.mac");
        ui->SessionStart();
        delete ui;
    }
    //UImanager->ApplyCommand("/control/execute auto.mac");

    delete visManager;
    delete runManager;
    return 0;
}
