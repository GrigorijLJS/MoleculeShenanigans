#include "pch.h"
#include "CppUnitTest.h"

#include "../MoleculeShenanigans/Molecule.h"
#include "../MoleculeShenanigans/MoleculeCollection.h"
#include "../MoleculeShenanigans/MoleculeOperations.h"
#include "../MoleculeShenanigans/Molecule.cpp"
#include "../MoleculeShenanigans/MoleculeCollection.cpp"
#include "../MoleculeShenanigans/MoleculeOperations.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MoleculeShenanigansTests
{
	TEST_CLASS(MoleculeShenanigansTests)
	{
	public:

		TEST_METHOD(MakingAMolecule)
		{
			//make the following test extendable by adding the data\properties for comparison in collections
			const std::string name = "Indomethacin";

			const std::string property1Name = "solubility";
			const float property1Value = 0.4f;
			const std::string property2Name = "molecular weight";
			const int property2Value = 358;
			const std::string property3Name = "text prop";
			const std::string property3Value = "jibber jabber";

			//the following should not be added to the molecule
			const std::string missingProperty1Name = "miss1";
			const float missingProperty1Value = 0.1f;
			const std::string missingProperty2Name = "miss2";
			const int missingProperty2Value = 111;
			const std::string missingProperty3Name = "miss3";
			const std::string missingProperty3Value = "AAA";

			Molecule indomethacin = Molecule(name);
			indomethacin.addProperty<float>(property1Name, property1Value);
			indomethacin.addProperty<int>(property2Name, property2Value);
			indomethacin.addProperty<std::string>(property3Name, property3Value);

			Assert::AreEqual(name, indomethacin.name());
			for (const auto item : indomethacin.precisionProperties())//there is only 1 property for now...
			{
				Assert::AreEqual(property1Name, item.first);
				Assert::AreEqual(property1Value, item.second);

				Assert::AreNotEqual(missingProperty1Name, item.first);
				Assert::AreNotEqual(missingProperty1Value, item.second);
			}
			for (const auto item : indomethacin.numericProperties())//there is only 1 property for now...
			{
				Assert::AreEqual(property2Name, item.first);
				Assert::AreEqual(property2Value, item.second);

				Assert::AreNotEqual(missingProperty2Name, item.first);
				Assert::AreNotEqual(missingProperty2Value, item.second);
			}
			for (const auto item : indomethacin.textualProperties())//there is only 1 property for now...
			{
				Assert::AreEqual(property3Name, item.first);
				Assert::AreEqual(property3Value, item.second);

				Assert::AreNotEqual(missingProperty3Name, item.first);
				Assert::AreNotEqual(missingProperty3Value, item.second);
			}
		}

		//tests if some molecules are equal or not
		TEST_METHOD(EqualityOfMolecules)
		{
			const std::string nameOf1stAnd2nd = "Molecule 1";

			const std::string property1Name = "solubility";
			const float property1Value = 0.4f;
			const std::string property2Name = "molecular weight";
			const int property2Value = 358;
			const std::string property3Name = "text prop";
			const std::string property3Value = "jibber jabber";

			Molecule molec1 = Molecule(nameOf1stAnd2nd);
			molec1.addProperty<float>(property1Name, property1Value);
			molec1.addProperty<int>(property2Name, property2Value);
			molec1.addProperty<std::string>(property3Name, property3Value);

			Molecule molec2 = Molecule(nameOf1stAnd2nd);
			molec2.addProperty<float>(property1Name, property1Value);
			molec2.addProperty<int>(property2Name, property2Value);
			molec2.addProperty<std::string>(property3Name, property3Value);

			bool areEqual = (molec1 == molec2);
			Assert::IsTrue(areEqual);

			const std::string nameOf3rd = "Molecule 3";
			const std::string prop1Name = "mock property";
			const float prop1Value = 0.9f;
			Molecule molec3 = Molecule(nameOf3rd);
			molec3.addProperty<float>(prop1Name, prop1Value);

			areEqual = (molec1 == molec3);
			Assert::IsFalse(areEqual);
			areEqual = (molec2 == molec3);
			Assert::IsFalse(areEqual);
		}

		//tests the adding a molecule to a collection
		TEST_METHOD(AddingMoleculeToACollection)
		{
			const std::string name = "Indomethacin";

			const std::string property1Name = "solubility";
			const float property1Value = 0.4f;
			const std::string property2Name = "molecular weight";
			const int property2Value = 358;

			Molecule indomethacin = Molecule(name);
			indomethacin.addProperty<float>(property1Name, property1Value);
			indomethacin.addProperty<int>(property2Name, property2Value);

			MoleculeCollection table1 = MoleculeCollection("table 1");
			table1.addMolecule(indomethacin);

			bool equalOnPosition0 = false;
			Assert::IsTrue(table1.data().size() == 1);
			Assert::IsTrue(table1.data().at(0) == indomethacin);

		}

		//tests the union of two tables
		TEST_METHOD(TheUnion)
		{
			//for table 1
			Molecule caffeine = Molecule("Caffeine");
			caffeine.addProperty<float>("solubility", 5.05f);
			caffeine.addProperty<int>("molecular weight", 194);
			caffeine.addProperty<int>("3rd property", 111);

			Molecule indomethacin = Molecule("Indomethacin");
			indomethacin.addProperty<float>("solubility", 0.4f);
			indomethacin.addProperty<int>("molecular weight", 358);

			Molecule trimethoprim = Molecule("Trimethoprim");
			trimethoprim.addProperty<float>("solubility", 3.14f);
			trimethoprim.addProperty<int>("molecular weight", 290);

			Molecule protoMolecule = Molecule("Proto");
			protoMolecule.addProperty<float>("psych", 3.14f);
			protoMolecule.addProperty<int>("some prop", 290);

			MoleculeCollection table1 = MoleculeCollection("table 1");
			table1.addMolecule(caffeine);
			table1.addMolecule(indomethacin);
			table1.addMolecule(trimethoprim);
			table1.addMolecule(protoMolecule);

			//for table 2
			Molecule paracetamol = Molecule("Paracetamol");
			paracetamol.addProperty<int>("molecular weight", 151);
			paracetamol.addProperty<float>("solubility", 4.97f);
			paracetamol.addProperty<float>("precision", 1.111f);
			paracetamol.addProperty<std::string>("potency", "A");

			Molecule protoMolecule2 = Molecule("Proto");
			protoMolecule2.addProperty<float>("psych", 3.14f);
			protoMolecule2.addProperty<int>("some prop", 290);

			Molecule trimethoprim2 = Molecule("Trimethoprim");
			trimethoprim2.addProperty<float>("solubility", 3.14f);
			trimethoprim2.addProperty<int>("molecular weight", 290);

			MoleculeCollection table2 = MoleculeCollection("table 1");
			table2.addMolecule(paracetamol);
			table2.addMolecule(protoMolecule2);
			table2.addMolecule(trimethoprim2);
			
			MoleculeOperations anOperator = MoleculeOperations();
			auto theUnion = anOperator.findUnion(table1, table2);
			bool equalOnPosition0 = false;

			Assert::IsTrue(theUnion.data().size() == 5);
			//check if the expected elements are there
			Assert::IsTrue(std::find(theUnion.data().begin(), theUnion.data().end(), caffeine) != theUnion.data().end());
			Assert::IsTrue(std::find(theUnion.data().begin(), theUnion.data().end(), indomethacin) != theUnion.data().end());
			Assert::IsTrue(std::find(theUnion.data().begin(), theUnion.data().end(), trimethoprim) != theUnion.data().end());
			Assert::IsTrue(std::find(theUnion.data().begin(), theUnion.data().end(), protoMolecule) != theUnion.data().end());
			Assert::IsTrue(std::find(theUnion.data().begin(), theUnion.data().end(), paracetamol) != theUnion.data().end());

			//technically the following is also true because of how the == operator works on Molecule objects
			Assert::IsTrue(std::find(theUnion.data().begin(), theUnion.data().end(), protoMolecule2) != theUnion.data().end());
		}

		//tests the difference of two tables
		TEST_METHOD(TheDifference)
		{
			//for table 1
			Molecule caffeine = Molecule("Caffeine");
			caffeine.addProperty<float>("solubility", 5.05f);
			caffeine.addProperty<int>("molecular weight", 194);
			caffeine.addProperty<int>("3rd property", 111);

			Molecule trimethoprim = Molecule("Trimethoprim");
			trimethoprim.addProperty<float>("solubility", 3.14f);
			trimethoprim.addProperty<int>("molecular weight", 290);

			Molecule protoMolecule = Molecule("Proto");
			protoMolecule.addProperty<float>("psych", 3.14f);
			protoMolecule.addProperty<int>("some prop", 290);

			MoleculeCollection table1 = MoleculeCollection("table 1");
			table1.addMolecule(trimethoprim);
			table1.addMolecule(protoMolecule);
			table1.addMolecule(caffeine);

			//for table 2
			Molecule paracetamol = Molecule("Paracetamol");
			paracetamol.addProperty<int>("molecular weight", 151);
			paracetamol.addProperty<float>("solubility", 4.97f);
			paracetamol.addProperty<float>("precision", 1.111f);
			paracetamol.addProperty<std::string>("potency", "A");

			Molecule protoMolecule2 = Molecule("Proto");
			protoMolecule2.addProperty<float>("psych", 3.14f);
			protoMolecule2.addProperty<int>("some prop", 290);

			Molecule trimethoprim2 = Molecule("Trimethoprim");
			trimethoprim2.addProperty<float>("solubility", 3.14f);
			trimethoprim2.addProperty<int>("molecular weight", 290);

			MoleculeCollection table2 = MoleculeCollection("table 1");
			table2.addMolecule(paracetamol);
			table2.addMolecule(protoMolecule2);
			table2.addMolecule(trimethoprim2);

			MoleculeOperations anOperator = MoleculeOperations();
			auto theDifference = anOperator.findDifference(table1, table2);
			bool equalOnPosition0 = false;

			Assert::IsTrue(theDifference.data().size() == 2);

			Assert::IsTrue(std::find(theDifference.data().begin(), theDifference.data().end(), caffeine) != theDifference.data().end());
			Assert::IsTrue(std::find(theDifference.data().begin(), theDifference.data().end(), paracetamol) != theDifference.data().end());

			//the rest of the items should not be in the difference
			Assert::IsTrue(std::find(theDifference.data().begin(), theDifference.data().end(), protoMolecule2) == theDifference.data().end());
			Assert::IsTrue(std::find(theDifference.data().begin(), theDifference.data().end(), protoMolecule) == theDifference.data().end());
			Assert::IsTrue(std::find(theDifference.data().begin(), theDifference.data().end(), trimethoprim) == theDifference.data().end());
			Assert::IsTrue(std::find(theDifference.data().begin(), theDifference.data().end(), trimethoprim2) == theDifference.data().end());
		}

		//tests the intersection of two tables
		TEST_METHOD(theIntersection)
		{
			//for table 1
			Molecule caffeine = Molecule("Caffeine");
			caffeine.addProperty<float>("solubility", 5.05f);
			caffeine.addProperty<int>("molecular weight", 194);
			caffeine.addProperty<int>("3rd property", 111);

			Molecule trimethoprim = Molecule("Trimethoprim");
			trimethoprim.addProperty<float>("solubility", 3.14f);
			trimethoprim.addProperty<int>("molecular weight", 290);

			Molecule protoMolecule = Molecule("Proto");
			protoMolecule.addProperty<float>("psych", 3.14f);
			protoMolecule.addProperty<int>("some prop", 290);

			MoleculeCollection table1 = MoleculeCollection("table 1");
			table1.addMolecule(trimethoprim);
			table1.addMolecule(protoMolecule);
			table1.addMolecule(caffeine);

			//for table 2
			Molecule paracetamol = Molecule("Paracetamol");
			paracetamol.addProperty<int>("molecular weight", 151);
			paracetamol.addProperty<float>("solubility", 4.97f);
			paracetamol.addProperty<float>("precision", 1.111f);
			paracetamol.addProperty<std::string>("potency", "A");

			Molecule protoMolecule2 = Molecule("Proto");
			protoMolecule2.addProperty<float>("psych", 3.14f);
			protoMolecule2.addProperty<int>("some prop", 290);

			Molecule trimethoprim2 = Molecule("Trimethoprim");
			trimethoprim2.addProperty<float>("solubility", 3.14f);
			trimethoprim2.addProperty<int>("molecular weight", 290);

			MoleculeCollection table2 = MoleculeCollection("table 1");
			table2.addMolecule(paracetamol);
			table2.addMolecule(protoMolecule2);
			table2.addMolecule(trimethoprim2);

			MoleculeOperations anOperator = MoleculeOperations();
			auto theIntersection = anOperator.findIntersection(table1, table2);
			bool equalOnPosition0 = false;

			Assert::IsTrue(theIntersection.data().size() == 2);

			Assert::IsTrue(std::find(theIntersection.data().begin(), theIntersection.data().end(), protoMolecule) != theIntersection.data().end());
			Assert::IsTrue(std::find(theIntersection.data().begin(), theIntersection.data().end(), trimethoprim) != theIntersection.data().end());

			Assert::IsTrue(std::find(theIntersection.data().begin(), theIntersection.data().end(), paracetamol) == theIntersection.data().end());
			Assert::IsTrue(std::find(theIntersection.data().begin(), theIntersection.data().end(), caffeine) == theIntersection.data().end());
		}
	};
}
