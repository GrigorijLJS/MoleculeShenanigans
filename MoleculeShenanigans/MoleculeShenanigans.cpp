#include <iostream>
#include <map>
#include "Molecule.h"
#include "MoleculeCollection.h"
#include "MoleculeOperations.h"

//a big abuse of the main() fuction follows below... :)
int main()
{
    std::cout << "Hello Friend...\n\n";

    //reading from file or other location is less cumbersome than adding properties one-by-one

    //avoid magic names or values - at least add them as consts somewhere :)
    auto paracetamol = Molecule("Paracetamol");
    paracetamol.addProperty<int>("molecular weight", 151);
    paracetamol.addProperty<float>("solubility", 4.97f);
    paracetamol.addProperty<float>("precision", 1.111f);
    paracetamol.addProperty<std::string>("potency", "A");
    paracetamol.addProperty<std::string>("test", "jibber");
    paracetamol.addProperty<std::string>("que?", "jabber");

    //not added because of the supported types
    paracetamol.addProperty<double>("double! how dare you!", 1.121212);


    auto caffeine = Molecule("Caffeine");
    caffeine.addProperty<float>("solubility", 5.05f);
    caffeine.addProperty<int>("molecular weight", 194);

    //this has an extra property compared to the molecule above, so currently they are not equal
    auto caffeine2 = Molecule("Caffeine");
    caffeine2.addProperty<float>("solubility", 5.05f);
    caffeine2.addProperty<int>("molecular weight", 194);
    caffeine2.addProperty<int>("3rd property", 111);

    //naive comparison
    if (caffeine2 == caffeine)
    {
        std::cout << "\nsame";
    }
    else
    {
        std::cout << "\nnot the same";
    }


    auto indomethacin = Molecule("Indomethacin");
    indomethacin.addProperty<float>("solubility", 0.4f);
    indomethacin.addProperty<int>("molecular weight", 358);

    auto trimethoprim = Molecule("Trimethoprim");
    trimethoprim.addProperty<float>("solubility", 3.14f);
    trimethoprim.addProperty<int>("molecular weight", 290);

    auto protoMolecule = Molecule("Proto");
    protoMolecule.addProperty<float>("psych", 3.14f);
    protoMolecule.addProperty<int>("some prop", 290);

    std::cout << "\n\n";

    MoleculeCollection firstTable = MoleculeCollection("tab1");
    firstTable.addMolecule(paracetamol);
    firstTable.addMolecule(indomethacin);
    firstTable.addMolecule(protoMolecule);
    firstTable.addMolecule(caffeine2);
    firstTable.addMolecule(caffeine);

    std::cout << "tab1\n";
    firstTable.printCollection();


    MoleculeCollection secondTable = MoleculeCollection("tab1");
    secondTable.addMolecule(paracetamol);
    secondTable.addMolecule(trimethoprim);
    secondTable.addMolecule(caffeine);

    std::cout << "tab2\n";
    secondTable.printCollection();

    MoleculeOperations theOperator = MoleculeOperations();
    auto inter = theOperator.findIntersection(firstTable, secondTable);

    std::cout << "\n\n";
    if (inter.data().size() > 0)
        inter.printCollection();
    else
        std::cout << "\nthe intersection is empty";

    auto diff = theOperator.findDifference(firstTable, secondTable);
    std::cout << "\n\n";
    if (diff.data().size() > 0)
        diff.printCollection();
    else
        std::cout << "\nthe difference is empty";


    auto unio = theOperator.findUnion(firstTable, secondTable);
    std::cout << "\n\n";
    if (unio.data().size() > 0)
        unio.printCollection();
    else
        std::cout << "\nthe union is empty";

    std::cout << "\n\n";
    std::cout << "\n\n";
}
