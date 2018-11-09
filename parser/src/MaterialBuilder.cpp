#include "MaterialBuilder.h"
#include "G4NistManager.hh"
#include "globals.hh"

MaterialBuilder* MaterialBuilder::instance=nullptr;

MaterialBuilder* MaterialBuilder::GetInstance()
{
	if(instance==nullptr)
		instance=new MaterialBuilder();
	return instance;
}

MaterialBuilder::MaterialBuilder()
{
	nist_manager=G4NistManager::Instance();
	BuildMaterials();
}

void MaterialBuilder::BuildMaterials()
{
	//Build air:
	G4Material* air = nist_manager->FindOrBuildMaterial("G4_AIR");
	materials["air"]=air;
	//Build water
	G4Material* water = nist_manager->FindOrBuildMaterial("G4_WATER");
	materials["water"]=water;
}

G4Material* MaterialBuilder::GetMaterial(G4String material_name)
{
	if(!materials.count(material_name))
		G4Exception("MaterialBuilder::GetMaterial", "No such material",
                    FatalException, "Requested material does not exist. Check config for typos and make sure that the material is defined properly in MaterialBuilder::BuildMaterials");
	return materials[material_name];
}