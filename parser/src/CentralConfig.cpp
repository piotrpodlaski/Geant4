#include <CentralConfig.h>


CentralConfig* CentralConfig::instance=nullptr;

CentralConfig* CentralConfig::GetInstance()
{
	if(instance==nullptr)
		instance=new CentralConfig();
	return instance;
}

CentralConfig::CentralConfig()
{
	result = config.load_file(config_file.c_str());
	if (!result)
		std::cerr<<"\e[31mError opening central config file. Check if file exists!\e[0m"<<std::endl;
}

bool CentralConfig::Has(std::string field_name)
{
	return !config.child(field_name.c_str()).empty();
}

template<>
std::string CentralConfig::Get<std::string>(std::string field_name)
{
	std::string res;
	res=config.child(field_name.c_str()).text().as_string();
	return res;
}

template<>
double CentralConfig::Get<double>(std::string field_name)
{
	double res;
	res=config.child(field_name.c_str()).text().as_double();
	return res;
}

template<>
int CentralConfig::Get<int>(std::string field_name)
{
	int res;
	res=config.child(field_name.c_str()).text().as_int();
	return res;
}