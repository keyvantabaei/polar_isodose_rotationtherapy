#ifndef chamberHit_h
#define chamberHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "tls.hh"

class chamberHit : public G4VHit
{
public:
//Construct and De-Construct Methods
chamberHit();
virtual ~chamberHit();
chamberHit(const chamberHit&);

//Virtual Method
virtual void Print();
virtual void Draw();

//operators
const chamberHit& operator=(const chamberHit&);
G4bool operator==(const chamberHit&) const;
inline void* operator new (size_t);
inline void operator delete(void*);

void SetCharge(G4double c){charge=c;}
G4double GetCharge(){return charge;}


private:
G4double charge;
};

typedef G4THitsCollection<chamberHit> chamberHC;
extern G4ThreadLocal G4Allocator<chamberHit>* chamberAllocator;
inline void* chamberHit::operator new (size_t)
{
if(!chamberAllocator)
chamberAllocator = new G4Allocator<chamberHit>;
return (void*)chamberAllocator->MallocSingle();
}

inline void chamberHit::operator delete(void *hit)
{
    chamberAllocator->FreeSingle((chamberHit*) hit);
}
#endif