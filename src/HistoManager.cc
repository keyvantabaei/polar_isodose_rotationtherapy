#include "HistoManager.hh"
#include <TTree.h>
#include <TFile.h>
#include <TH3D.h>
//there is another way to include following header .
#include <CLHEP/Units/SystemOfUnits.h>
HistoManager::HistoManager():rootfile(0)
{


_histo3Ddose_cart=0;
_histo3Ddose_polar=0;
_3ddoseCART=0;
 _x=_y=_z=_dose=0;
}
HistoManager::~HistoManager(){if(rootfile)delete rootfile;}

void HistoManager::Save()
{
    if(!rootfile)return;
    rootfile->Write();
    rootfile->Close();
}

void HistoManager::Book()
{
rootfile = new TFile("result.root","RECREATE");



_histo3Ddose_cart = new TH3D("3d_doseCART", "3d_doseCART", 200, 0, 200, 200,0, 200,100,0,100);
_histo3Ddose_polar= new TH3D("3d_dosePOLAR", "3d_dosePOLAR",100, 0, 100, 96, 0, 96,100,0,100); // r phi z

_3ddoseCART = new TTree("3ddoseCART", "3ddoseCART");
_3ddoseCART->Branch("x", &_x, "x/D");
_3ddoseCART->Branch("z", &_z, "z/D");
_3ddoseCART->Branch("y", &_y, "y/D");
_3ddoseCART->Branch("dose", &_dose, "dose/D");

}


void HistoManager::Fill_3D_Histogram_Polar(G4double r,G4double phi,G4double z,G4double pdd)
{

  _histo3Ddose_polar->SetBinContent(r,phi,z,pdd);

}


void HistoManager::Fill_3D_Histogram_CART(G4double x,G4double y,G4double z,G4double pdd)
{

  _histo3Ddose_cart->SetBinContent(x,y,z,pdd);

}

void HistoManager::Fill_3D_TTree_CART(G4double x,G4double y,G4double z,G4double pdd)
{
_z=z;
_y=y;
_x=x;
_dose=pdd;
_3ddoseCART->Fill();
}