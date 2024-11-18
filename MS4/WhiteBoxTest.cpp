#include "pch.h"
#include "CppUnitTest.h"

extern "C" {
#include "extraStructure.h"
#include "mapping.h"
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace WhiteBox
{
    TEST_CLASS(WhiteBox)
    {
    public:
        // whitebox test for addPackage function
        TEST_METHOD(AddPackageTest)
        {
            Truck truck = { 0, 0, 0, {} };
            Package pkg = { 20, 10 };
            addPackage(&truck, pkg);
            Assert::AreEqual(1, truck.numPackage);
            Assert::AreEqual(20, truck.tempWeight);
            Assert::AreEqual(10, truck.tempVolume);

            // testing the boundary condition for maximum packages
            truck.numPackage = MAX_PACKAGE - 1;
            addPackage(&truck, pkg);
            Assert::AreEqual(MAX_PACKAGE, truck.numPackage);

            // if add a package when truck is full
            addPackage(&truck, pkg);
            Assert::AreEqual(MAX_PACKAGE, truck.numPackage);
        }

        // whitebox test for calculateCapacity function
        TEST_METHOD(CalculateCapacityTest)
        {
            Truck truck = { 1, 2000, 20, 0, {}, {} };

            double capacity = calculateCapacity(&truck);
            Assert::AreEqual(0, capacity, 0.01); // small decimal for double comparison

            // testing edge case where truck is max weight
            truck.tempWeight = MAX_WEIGHT;
            capacity = calculateCapacity(&truck);
            Assert::AreEqual(0.0, capacity, 0.01);

            // testing edge case where truck is max volume
            truck.tempVolume = MAX_VOLUME;
            capacity = calculateCapacity(&truck);
            Assert::AreEqual(0.0, capacity, 0.01);
        }        

        // whitebox test for canAddPackage function
        TEST_METHOD(CanAddPackageTest)
        {
            Truck truck = { 0, 500, 400, {} };
            Package pkg = { 100, 50 };

            // test adding a package that fits
            int canAdd = canAddPackage(&truck, &pkg);
            Assert::AreEqual(0, canAdd); //  return 0

            // test adding a package that exceeds weight
            pkg.weight = 600;
            canAdd = canAddPackage(&truck, &pkg);
            Assert::AreEqual(0, canAdd); //  return 0 

            // test adding a package that exceeds volume
            pkg.weight = 50;
            pkg.size = 300;
            canAdd = canAddPackage(&truck, &pkg);
            Assert::AreEqual(0, canAdd); //  return 0 
        }

        // whitebox test for countPackages function
        TEST_METHOD(CountPackagesTest)
        {
            Truck truck = { 0, 0, 0, {} };
            Assert::AreEqual(0, countPackages(&truck));

            // adding packages and testing the count
            truck.numPackage = 3;
            Assert::AreEqual(3, countPackages(&truck));

            // boundary test
            truck.numPackage = MAX_PACKAGE;
            Assert::AreEqual(MAX_PACKAGE, countPackages(&truck));
        }
    };
}
