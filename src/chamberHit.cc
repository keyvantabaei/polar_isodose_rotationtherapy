#include "chamberHit.hh"
#include "G4VHit.hh"
#include "G4ThreeVector.hh"
#include "G4Allocator.hh"
#include <iomanip>
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
G4ThreadLocal G4Allocator<chamberHit>* chamberAllocator=0;

chamberHit::chamberHit():G4VHit()
{
charge=0;
}

chamberHit::~chamberHit(){}

chamberHit::chamberHit(const chamberHit& K1BH):G4VHit()
{
    charge=K1BH.charge;

}
const chamberHit& chamberHit::operator=(const chamberHit& K1BH)
{
    charge=K1BH.charge;
    return *this;
}

G4bool chamberHit::operator==(const chamberHit& K1BH) const
{
    return (this == &K1BH) ? true : false;
}

void chamberHit::Print()
{
}

void chamberHit::Draw()
{
}