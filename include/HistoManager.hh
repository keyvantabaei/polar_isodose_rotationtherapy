#ifndef HistoManager_h
#define HistoManager_h 1

#include "globals.hh"

class TFile;
class TTree;
class TH3D;

class HistoManager
{
public:
 HistoManager();
~HistoManager();

void Book();
void Save();
void Draw();
void Fill_3D_Histogram_CART(G4double,G4double,G4double,G4double);
void Fill_3D_Histogram_Polar(G4double,G4double,G4double,G4double);
void Fill_3D_TTree_CART(G4double,G4double,G4double,G4double);

private:

TH3D*   _histo3Ddose_cart;
TH3D*   _histo3Ddose_polar;
TTree*   _3ddoseCART;    


TFile* rootfile;

G4double _x,_y,_z,_dose;

};
#endif