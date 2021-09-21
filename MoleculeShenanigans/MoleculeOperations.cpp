#include "MoleculeOperations.h"
#include "MoleculeCollection.h"
#include "Molecule.h"

MoleculeOperations::MoleculeOperations()
{
}

MoleculeOperations::~MoleculeOperations()
{
}

//finds the union of the passed collections of molecules (marked as 'left' and 'right')
//returns a collection of molecules
MoleculeCollection MoleculeOperations::findUnion(const MoleculeCollection& left, const MoleculeCollection& right)
{
    MoleculeCollection forZeUnion = MoleculeCollection("Union");
    differenceAlgorithm(left, right, forZeUnion);
    intersectionAlgorithm(left, right, forZeUnion);
    return forZeUnion;
}

//finds the differences between the passed molecule collections
//returns a collection of molecules, which might be empty
MoleculeCollection MoleculeOperations::findDifference(const MoleculeCollection& left, const MoleculeCollection& right)
{
    MoleculeCollection diff = MoleculeCollection("Difference");
    differenceAlgorithm(left, right, diff);
    return diff;
}

//finds the intersection between the two molecule collections that are passed to it
//returns a collection of molecules, which might be empty
MoleculeCollection MoleculeOperations::findIntersection(const MoleculeCollection& left, const MoleculeCollection& right)
{
    MoleculeCollection intersect = MoleculeCollection("Intersection");
    intersectionAlgorithm(left, right, intersect);
    return intersect;
}

void MoleculeOperations::differenceAlgorithm(const MoleculeCollection& left, const MoleculeCollection& right, MoleculeCollection& diff)
{
    //the next pieces of code could be handled in a better way... by something from <algorithm> like std::set_difference
    //first left leads...
    for (const Molecule& leftItem : left.data())
    {
        bool elementFound = false;
        for (const Molecule& rightItem : right.data())
        {
            if (leftItem == rightItem)
                elementFound = true;
        }
        if (!elementFound)
            diff.addMolecule(leftItem);
    }
    //...then right leads
    for (const Molecule& rightItem : right.data())
    {
        bool elementFound = false;
        for (const Molecule& leftItem : left.data())
        {
            if (leftItem == rightItem)
                elementFound = true;
        }
        if (!elementFound && !(std::find(diff.data().begin(), diff.data().end(), rightItem) != diff.data().end()))
            diff.addMolecule(rightItem);
    }
}

void MoleculeOperations::intersectionAlgorithm(const MoleculeCollection& left, const MoleculeCollection& right, MoleculeCollection& inter)
{
    //<algorithm> has std::set_intersection which could be used instead of this; set_intersection is probably optimised and faster :)
    for (const Molecule& leftItem : left.data())
    {
        for (const Molecule& rightItem : right.data())
        {
            if (leftItem == rightItem)
                inter.addMolecule(rightItem);
        }
    }
}
