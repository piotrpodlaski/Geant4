#ifndef GEOMETRYCONFIG_H
#define GEOMETRYCONFIG_H

#include <iostream>
#include <SolidDescriptor.h>
#include <G4String.hh>
#include <fstream>
#include <sstream>
#include <string>
#include <G4ThreeVector.hh>
#include <G4Color.hh>
#include <CentralConfig.h>
#include "globals.hh"

class GeometryConfig
{
public:
	static GeometryConfig* GetInstance();
	std::vector<SolidDescriptor> GetSolids();

private:
	GeometryConfig();
	static GeometryConfig* instance;
	std::vector<SolidDescriptor> solids;
	void ParseGeometry();
	SolidDescriptor ParseLine(std::string line);
	void ParseLine(std::string line, SolidDescriptor& sd);
	void CleanupSolids();
	std::string config_name="geometry.cfg";
	std::ifstream config_file;
	CentralConfig* central_config;
	
};

#endif