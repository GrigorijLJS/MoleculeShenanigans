#ifndef Molecule_H
#define Molecule_H

#include <string>
#include <map>
#include <iostream>

class Molecule
{
public:
	//only allow the construction of MoleculeCollections with a name, since names are important
	Molecule() = delete;
	Molecule(std::string moleculeName);
	//you might want to cover other constructor types...
	~Molecule();

	//decides in which container the property value and its name need to be added; C++ 17 only
	template <typename T>
	void addProperty(const std::string& propertyName, const T& propertyValue)
	{
		if constexpr (std::is_same_v<T, int>)
		{
			m_numericProperties.insert(std::make_pair(propertyName, propertyValue));
		}
		else if constexpr (std::is_same_v<T, float>)
		{
			m_numPrecisionProperties.insert(std::make_pair(propertyName, propertyValue));
		}
		else if constexpr (std::is_same_v<T, std::string>)
		{
			m_textualProperties.insert(std::make_pair(propertyName, propertyValue));
		}
		//could also be extended by adding more member containers in the class and covering their types here
		else
		{
			//C++20 has template constraints and concepts, which, if used, would make the 'else' obsolete...
		}
	}

	void printAllTheData();
	const std::string name() const;
	const std::map<std::string, std::string> textualProperties() const;
	const std::map<std::string, int> numericProperties() const;
	const std::map<std::string, float> precisionProperties() const;

	//---
	//some operator overloading to allow comparison of Molecules

	//a somewhat naive comparison operators follow; these might require some reworking based on various requirements
	//at the moment they compare all the elements (name and properties) contained in two Molecule objects
	friend inline bool operator==(const Molecule& left, const Molecule& right)
	{
		return (left.m_moleculeName == right.m_moleculeName)
			&& (left.m_numericProperties == right.m_numericProperties)
			&& (left.m_numPrecisionProperties == right.m_numPrecisionProperties)
			&& (left.m_textualProperties == right.m_textualProperties);
	}
	friend inline bool operator!=(const Molecule& left, const Molecule& right)
	{
		return (left.m_moleculeName != right.m_moleculeName)
			&& (left.m_numericProperties != right.m_numericProperties)
			&& (left.m_numPrecisionProperties != right.m_numPrecisionProperties)
			&& (left.m_textualProperties != right.m_textualProperties);
	}
	//---

private:

	//generic print function (console output only) useful for any of the map container types in this class
	template <typename T>
	void printerOfData(const T& container)
	{
		for (const auto [key, value] : container)
			std::cout << key << " - " << value << " ; ";
	}

	//generic function that can be used to find if a key is within any of the member (map) containers in this class
	template <typename T>
	bool finderOfData(const T& container, const std::string& targetedKey)
	{
		return container.find(targetedKey) == container.end();
	}

	std::string m_moleculeName;
	std::map<std::string, std::string> m_textualProperties;
	std::map<std::string, int> m_numericProperties;
	//one could use double i.s.o. float to increase precision...
	std::map<std::string, float> m_numPrecisionProperties;
};

#endif
