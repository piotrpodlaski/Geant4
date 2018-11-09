#include <GeometryConfig.h>

//#include "globals.hh"
#include "G4SystemOfUnits.hh"
#include "globals.hh"



GeometryConfig* GeometryConfig::instance=nullptr;

GeometryConfig* GeometryConfig::GetInstance()
{
	if(instance==nullptr)
		instance=new GeometryConfig();
	return instance;
}

GeometryConfig::GeometryConfig()
{
	central_config=CentralConfig::GetInstance();
	if(central_config->Has("geometry_config_path"))
		config_name=central_config->Get<std::string>("geometry_config_path");
	config_file.open(config_name);
	if(config_file.is_open())
	{
		ParseGeometry(); //reads config file
		CleanupSolids(); //removes solids without instances
		config_file.close();
	}
	else
		std::cerr<<"\e[31mError opening geometry config. Check if file exists!\e[0m"<<std::endl;
}

void GeometryConfig::ParseGeometry()
{
	std::string line;
	while(getline(config_file,line))
	{
		if(line[0]=='#'||line.size()==0) //skip comments and empty lines
			continue;
		if(line[0]=='+') //initialize instances of solids
		{
			if(solids.size()==0)
			{
				std::cerr<<"\e[31mWrong formatting of config file! Solid placement (+) added before any solid is defined!\nSkipping line in config file...\e[0m";
				continue;
			}
			line.erase(0,1);
			ParseLine(line, solids.back());
		}
		else
			solids.push_back(ParseLine(line)); //initialize solids
	}
}

SolidDescriptor GeometryConfig::ParseLine(std::string line)
{
	SolidDescriptor s;
	std::istringstream iss(line);
	std::string name, filename, material;
	G4int r,g,b;
	iss>>name;
	iss>>filename;
	iss>>material;
	iss>>r;
	iss>>g;
	iss>>b;
	s.name=name;
	s.filename=filename;
	s.material=material;
	s.color=G4Color(r/255.,g/255.,b/255.);
	return s;
}

void GeometryConfig::ParseLine(std::string line, SolidDescriptor& sd)
{
	std::istringstream iss(line);
	double x,y,z,rx,ry,rz;
	iss>>x;
	iss>>y;
	iss>>z;
	iss>>rx;
	iss>>ry;
	iss>>rz;
	sd.pos.push_back(G4ThreeVector(x*mm,y*mm,z*mm));
	G4RotationMatrix *rm = new G4RotationMatrix();
	G4double angle_unit;
	if(central_config->Has("angle_unit"))
	{
		std::string unit=central_config->Get<std::string>("angle_unit");
		if(unit=="deg")
		{
			angle_unit=radian*M_PI/180.;
		}
		else
		{
			angle_unit=radian;
		}
		if(unit!="deg"&&unit!="rad")
		{
			std::cerr<<"Angle unit not recognized, using radians!"<<std::endl;
		}
	}
	else
	{
		angle_unit=radian;
	}
	rm->rotateX(rx*angle_unit);
	rm->rotateY(ry*angle_unit);
	rm->rotateZ(rz*angle_unit);
	sd.rot.push_back(rm);
	/*
	rm->rotateX(rx*radian);
	rm->rotateY(ry*radian);
	rm->rotateZ(rz*radian);
	sd.rot.push_back(rm);*/
	
}

std::vector<SolidDescriptor> GeometryConfig::GetSolids()
{
	return solids;
}

void GeometryConfig::CleanupSolids()
{
	for(auto it=solids.begin();it!=solids.end();)
	{
		if(it->pos.size()==0)
			it=solids.erase(it);
		else
			++it;
	}
}