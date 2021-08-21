#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4UnitsTable.hh"

#include "k1EA.hh"
#include "k1RA.hh"
#include "HistoManager.hh"


k1EA::k1EA(k1RA* ra,HistoManager* histo)
 : G4UserEventAction(),_edep_HCID(-1),_histo(histo),_charge_HCID(-1),_runAction(ra)
{

  }


k1EA::~k1EA()
{}

phantomHC*  k1EA::GetphantomHitsCollection(G4int hcID,const G4Event* event) const
{
  auto hitsCollection = static_cast<phantomHC*>(event->GetHCofThisEvent()->GetHC(hcID));
  
  if ( ! hitsCollection ) 
  {
    G4ExceptionDescription msg;
    msg << "Cannot access hitsCollection ID " << hcID; 
    G4Exception("B4cEventAction::GetHitsCollection()","MyCode0003", FatalException, msg);
  }         

  return hitsCollection;
}  
chamberHC*  k1EA::GetchamberHitsCollection(G4int hcID,const G4Event* event) const
{
  auto hitsCollection = static_cast<chamberHC*>(event->GetHCofThisEvent()->GetHC(hcID));
  
  if ( ! hitsCollection ) 
  {
    G4ExceptionDescription msg;
    msg << "Cannot access hitsCollection ID " << hcID; 
    G4Exception("B4cEventAction::GetHitsCollection()","MyCode0003", FatalException, msg);
  }         

  return hitsCollection;
} 

void k1EA::BeginOfEventAction(const G4Event* event)
{
  G4int evtNb = event->GetEventID();
  if (evtNb%100000 == 0) 
    G4cout << "\n---> Begin of event: " << evtNb/100000 <<" "<< G4endl;
 
}

void k1EA::EndOfEventAction(const G4Event* event)
{  
  
}  
