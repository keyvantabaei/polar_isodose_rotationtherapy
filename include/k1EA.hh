#ifndef k1EA_h
#define k1EA_h 1

#include "G4UserEventAction.hh"
#include "phantomHit.hh"
#include "chamberHit.hh"


#include "globals.hh"

class HistoManager;
class k1RA;
class k1EA : public G4UserEventAction
{
public:
  k1EA(k1RA*,HistoManager*);
  virtual ~k1EA();

  virtual void  BeginOfEventAction(const G4Event* event);
  virtual void    EndOfEventAction(const G4Event* event);
  phantomHC* GetphantomHitsCollection(G4int hcID,const G4Event* event) const;
  chamberHC* GetchamberHitsCollection(G4int hcID,const G4Event* event) const;

private:
HistoManager* _histo;
G4double _edep_HCID;
G4double _charge_HCID;
k1RA* _runAction;
};
#endif

    