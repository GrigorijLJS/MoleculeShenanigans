#include "Molecule.h"

Molecule::Molecule(std::string moleculeName)
	:m_moleculeName(moleculeName)
	,m_textualProperties(std::map<std::string, std::string>())
	,m_numericProperties(std::map<std::string, int>())
	,m_numPrecisionProperties(std::map<std::string, float>())
{
}

Molecule::~Molecule()
{
	//clean up duty
	m_textualProperties.clear();
	m_numericProperties.clear();
	m_numPrecisionProperties.clear();
	m_moleculeName = "";
}

//prints all the data know about this molecule
//starts with the name and then prints all the properties per type
void Molecule::printAllTheData()
{
	std::cout << m_moleculeName + ": ";
	printerOfData(m_numericProperties);
	printerOfData(m_numPrecisionProperties);
	printerOfData(m_textualProperties);
}

//---//maybe make the following functions inline

//returns the name of the molecule
const std::string Molecule::name() const 
{
	return m_moleculeName;
}

//returns the string properties and their names
const std::map<std::string, std::string> Molecule::textualProperties() const
{
	return m_textualProperties;
}

//returns the numeric (ints) properties and their names
const std::map<std::string, int> Molecule::numericProperties() const
{
	return m_numericProperties;
}

//returns the precision properties (floats) and their names
const std::map<std::string, float> Molecule::precisionProperties() const
{
	return m_numPrecisionProperties;
}
//---//