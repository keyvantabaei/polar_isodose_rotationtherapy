#include "chamberSD.hh"

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
chamberSD::chamberSD(const G4String& name,const G4String& HCname):
G4VSensitiveDetector(name),
_chamberHC(NULL)
{
collectionName.insert(HCname);

}

chamberSD::~chamberSD(){}

void chamberSD::Initialize(G4HCofThisEvent* hc)
{
_chamberHC = new chamberHC(SensitiveDetectorName,collectionName[0]);
G4int hcID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
hc->AddHitsCollection(hcID,_chamberHC);
}
G4bool chamberSD::ProcessHits(G4Step* step,G4TouchableHistory*)
{
    return false;
}
void chamberSD::EndOfEvent(G4HCofThisEvent*)
{

}