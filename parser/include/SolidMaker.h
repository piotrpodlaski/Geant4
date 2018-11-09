#ifndef SOLIDMAKER_H
#define SOLIDMAKER_H
#include "SolidDescriptor.h"
#include "globals.hh"
#include "G4ThreeVector.hh"
#include "CadMesh.hh"

class SolidMaker
{

public:
	static G4VSolid MakeSolid(SolidDescriptor solid);
};

#endif