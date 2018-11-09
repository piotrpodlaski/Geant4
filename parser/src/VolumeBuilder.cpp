#include "VolumeBuilder.h"
#include "G4VSolid.hh"
#include "globals.hh"
#include "G4ThreeVector.hh"
#include "G4Transform3D.hh"

#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4VisAttributes.hh"
#include "SolidDescriptor.h"
#include "MaterialBuilder.h"

#include "CADMesh.hh"
#include "GeometryConfig.h"


VolumeBuilder::VolumeBuilder()
{
	material_builder=MaterialBuilder::GetInstance();
}

G4VSolid* VolumeBuilder::BuildSolid(SolidDescriptor solid)
{
	CADMesh * mesh = new CADMesh((char*) solid.filename.c_str());
	G4VSolid* cad_solid=mesh->TessellatedMesh();
	solids[solid.name]=cad_solid;
	return cad_solid;
}

G4LogicalVolume* VolumeBuilder::BuildLogical(SolidDescriptor solid)
{	
	G4LogicalVolume* log_vol=new G4LogicalVolume(BuildSolid(solid),material_builder->GetMaterial(solid.material),G4String(solid.name+"_logical"));
	G4VisAttributes* attrs = new G4VisAttributes(solid.color);
	attrs->SetForceSolid(true);
	log_vol->SetVisAttributes(attrs);
	logical_volumes[solid.name]=log_vol;
	vis_attributes[solid.name]=attrs;
	return log_vol;
}

void VolumeBuilder::BuildVolumes(G4LogicalVolume* world_log)
{
	GeometryConfig* geo_config=GeometryConfig::GetInstance();
	for(auto solid: geo_config->GetSolids())
	{
		G4LogicalVolume* log_vol=BuildLogical(solid);
		for(unsigned int instance=0;instance<solid.pos.size();instance++)
		{
			G4VPhysicalVolume* phys_vol = new G4PVPlacement(
				solid.rot[instance], 
				solid.pos[instance],
				//G4Transform3D(G4RotationMatrix(), G4ThreeVector()),
				log_vol,
				solid.name+"_phys",
				world_log,
				0,
				instance
				);
			physical_volumes[solid.name+G4String(std::to_string(instance))]=phys_vol;
		}
	}
}