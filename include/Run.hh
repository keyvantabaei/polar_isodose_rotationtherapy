#ifndef Run_h
#define Run_h 1

#include "G4Run.hh"
#include "G4DataVector.hh"
#include <array>

struct Svoxel
{
  G4int copyNo;
  G4double dose;
  G4double X;
  G4double Y;
};
class Run : public G4Run
{
    public:
    Run();
    virtual ~Run();
    virtual void Merge(const G4Run*);
    void EndOfRun();
    void AddData(G4double,G4int);
    // void CountPhoton(G4double p,G4double s){primary+=p;scaterred+=s;all=primary+scaterred;}
    // std::tuple<G4double,G4double,G4double> GetCountedPhotons(){return std::make_tuple(primary,scaterred,all);}
    G4double* GetDose(){return voxels;}
    private:
    G4double* voxels;
};

#endif