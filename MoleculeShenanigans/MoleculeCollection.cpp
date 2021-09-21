#include "MoleculeCollection.h"
#include "Molecule.h"
#include <algorithm>

MoleculeCollection::MoleculeCollection(std::string name)
	:m_name(name)
	,m_molecules(std::vector<Molecule>())
{
}

MoleculeCollection::~MoleculeCollection()
{
	//clean up duty
	m_molecules.clear();
	m_name = "";
}

//tries to add a molecule to the collection but also does some checks
//after a molecule is added the collection is sorted based on the names (of the molecules)
void MoleculeCollection::addMolecule(const Molecule& mole)//could be changed to use std::move to steal the Molecules for itself
{
	bool sortingNeeded = false;

	//checks if the item is already in the collection by using a naive == operator
	auto itemIter = std::find(m_molecules.begin(), m_molecules.end(), mole);
	if (itemIter == m_molecules.end())
	{
		m_molecules.push_back(mole);
		sortingNeeded = true;//we changed something so sort the collection
	}
	//else //if we decide that two molecules that have the same name but different properties can be merged into one something like the following could be done
	//{
		////if the item is present, see what properties might be added from the passed object
		//std::cout << "\nItem is already known: " << mole.name();
		//std::cout << "\n trying to merge data...";
		////assuming that "item" below contains the element that we already found before
		//if (itemIter->name() == mole.name())//let us assume that equal names means that the two molecules need to become the same
		//{
		//	std::vector<std::pair<std::string, std::string>> missingTextProperties;
		//	std::set_difference(itemIter->textualProperties().begin(), itemIter->textualProperties().end(),
		//		mole.textualProperties().begin(), mole.textualProperties().end(), std::back_inserter(missingTextProperties));
		//	for (auto prop : missingTextProperties)
		//		itemIter->addProperty(prop.first, prop.second);
		//	//...do the same procedure for the other property types in the Molecule class
		//}
	//}

	if (m_molecules.size() > 1 && sortingNeeded)
	{
		//sorts the collection based on the Molecule name
		std::sort(m_molecules.begin(), m_molecules.end(), 
			[](const auto& left, const auto& right)//C++ 14 only
			{
				return left.name() < right.name();
			});
	}
}

//goes through all the data in the collection and prints it
void MoleculeCollection::printCollection()
{
	std::cout << "Collection " + m_name + " contains: \n";
	for (auto molecule : m_molecules)
	{
		molecule.printAllTheData();
		std::cout << std::endl;
	}
}

//returns all the molecules within this collection
std::vector<Molecule> const& MoleculeCollection::data() const
{
	return m_molecules;
}
