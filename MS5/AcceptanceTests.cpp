#include "pch.h"
#include "CppUnitTest.h"
#include "extraStructure.h"
#include "assert.h"
extern "C" {
#include "extraStructure.h"
#include "mapping.h"
}
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace AcceptanceTests
{
    TEST_CLASS(AcceptanceTests)
    {
    public:
        // Test Case 1 - validate package rejection for overweight
        TEST_METHOD(TestPackageRejectionOverweight)
        {
            Truck truck = { 0, 1500, 15, {} };
            Package pkg = { 600, 4 }; 

            int canAdd = canAddPackage(&truck, &pkg);
            Assert::AreEqual(0, canAdd);
        }

        // Test Case 2 - validate remaining capacity calculation
        TEST_METHOD(TestCalculateCapacity)
        {
            Truck truck = { 0, 1500, 16, {} };

            double capacity = calculateCapacity(&truck);
            Assert::AreEqual(20.0, capacity, 0.01);
        }

        // Test Case 3 - validate package successfully added
        TEST_METHOD(TestAddPackageSuccess) {
            Truck truck = { 0, 1000, 10, {} };
            Package pkg = { 500, 5 }; // Within remaining capacity

            addPackage(&truck, pkg);
            Assert::AreEqual(1500, truck.tempWeight); // Check updated weight
            Assert::AreEqual(15, truck.tempVolume);   // Check updated volume
            Assert::AreEqual(1, truck.numPackage);    // Check package count
        }

        // Test Case 4 - validate path calculation
        TEST_METHOD(TestPathCalculation) {
            Map map; // Assuming map is initialized with valid paths and obstacles
            Point start = { 0, 0 };
            Point dest = { 5, 5 };

            Path path = calculatePath(&map, start, dest);
            Assert::AreEqual(10, path.length); 
        }
    };
}
