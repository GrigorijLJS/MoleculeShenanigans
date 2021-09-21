#ifndef MoleculeCollection_H
#define MoleculeCollection_H

#include <vector>
#include <string>
#include <memory>

class Molecule;

class MoleculeCollection
{
public:
	//only allow the construction of MoleculeCollections with a name
	MoleculeCollection() = delete;
	MoleculeCollection(std::string name);
	//you might want to cover other constructor types...
	////copy constructor
	//MoleculeCollection(const MoleculeCollection& theOther);
	////copy assign. operator
	//MoleculeCollection& operator=(const MoleculeCollection& theOther);
	~MoleculeCollection();

	void addMolecule(const Molecule& mole);
	void printCollection();
	std::vector<Molecule> const& data() const;


private:
	std::string m_name;
	std::vector<Molecule> m_molecules;
};

#endif