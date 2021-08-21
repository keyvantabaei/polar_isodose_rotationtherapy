#ifndef chamberSD_h
#define chamberSD_h 1

#include "G4VSensitiveDetector.hh"
#include "chamberHit.hh"
class G4Step;
class G4HCofThisEvent;
class chamberSD : public G4VSensitiveDetector
{
public:
chamberSD(const G4String& name,const G4String& HCname);
virtual ~chamberSD();
virtual void Initialize(G4HCofThisEvent* hc);
virtual G4bool ProcessHits(G4Step* step,G4TouchableHistory*);
virtual void EndOfEvent(G4HCofThisEvent*);
private:
chamberHC* _chamberHC;
};
#endif