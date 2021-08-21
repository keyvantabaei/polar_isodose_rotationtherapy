#include "phantomSD.hh"


#include "G4VSensitiveDetector.hh"
#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "k1DC.hh"
#include "G4RunManager.hh"
#include "G4ThreeVector.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "Run.hh"
#include "G4Gamma.hh"
#include "G4Electron.hh"

phantomSD::phantomSD(const G4String& name,const G4String& HCname):
G4VSensitiveDetector(name),
_phantomHC(NULL)
{
collectionName.insert(HCname);

}

phantomSD::~phantomSD(){}

void phantomSD::Initialize(G4HCofThisEvent* hc)
{
_phantomHC = new phantomHC(SensitiveDetectorName,collectionName[0]);
G4int hcID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
hc->AddHitsCollection(hcID,_phantomHC);
}
G4bool phantomSD::ProcessHits(G4Step* step,G4TouchableHistory*)
{
    auto edep = step->GetTotalEnergyDeposit()/joule;
    if (edep==0.) return false;

    const G4VTouchable* touchable = step->GetPreStepPoint()->GetTouchable();

    //0 for R
    G4int iz =touchable->GetReplicaNumber(1);
    //2 for Phi
    G4int iphi =touchable->GetReplicaNumber(2);
    //1 for Z
    G4int ir =touchable->GetReplicaNumber(0);

    auto mass =touchable->GetVolume(0)->GetLogicalVolume()->GetMass()/kg;
    G4double dose =edep/mass;
    // G4cout
    // <<" -------------------->>  0 :" 
    // <<G4endl;
    // G4cout
    // <<" -------------------->>  R :" <<ir
    // <<" -------------------->>  Z :" <<iz
    // <<" -------------------->>  Phi :" <<iphi
    // <<G4endl;

    G4int copyNo = iphi*1e4 + iz*1e2 + ir;
    Run* run = static_cast<Run*>(G4RunManager::GetRunManager()->GetNonConstCurrentRun());
    run->AddData(dose,copyNo);

    return true;

}
void phantomSD::EndOfEvent(G4HCofThisEvent*)
{
}