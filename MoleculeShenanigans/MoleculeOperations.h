#ifndef MoleculeOperations_H
#define MoleculeOperations_H

class MoleculeCollection;

class MoleculeOperations
{
public:
	MoleculeOperations();
	~MoleculeOperations();

	///---
	//the following operations could easily be changed to use std::move on pointers and steal from 'left' and 'right'
	//and give the resources to the returned MoleculeCollection object
	MoleculeCollection findUnion(const MoleculeCollection& left, const MoleculeCollection& right);
	MoleculeCollection findDifference(const MoleculeCollection& left, const MoleculeCollection& right);
	MoleculeCollection findIntersection(const MoleculeCollection& left, const MoleculeCollection& right);
	///---

private:
	void differenceAlgorithm(const MoleculeCollection& left, const MoleculeCollection& right, MoleculeCollection& diff);
	void intersectionAlgorithm(const MoleculeCollection& left, const MoleculeCollection& right, MoleculeCollection& inter);
};

#endif
