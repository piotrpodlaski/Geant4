#ifndef CENTRALCONFIG_H
#define CENTRALCONFIG_H

#include <iostream>
#include "pugixml.hpp"

#include <SolidDescriptor.h>
#include <G4String.hh>
#include <fstream>
#include <sstream>
#include <string>
#include <G4ThreeVector.hh>
#include <G4Color.hh>
#include <G4ThreeVector.hh>

class CentralConfig
{
public:
	static CentralConfig* GetInstance();
	template<typename T>
	T Get(std::string field_name);
	bool Has(std::string field_name);

private:
	CentralConfig();
	static CentralConfig* instance;
	pugi::xml_document config;
	pugi::xml_parse_result result;
	std::string config_file="config.xml";
};

#endif