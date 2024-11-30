#include "pch.h"
#include "CppUnitTest.h"

extern "C" {
#include "extraStructure.h"  // Include your C files with structure definitions and function declarations
#include "mapping.h"
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IntegrationTests
{
    TEST_CLASS(IntegrationTests)
    {
    public:

        TEST_METHOD(testCanAddAndAddPackage)
        {
            struct Truck truck = { 1, 1500, 15, 60 };
            struct Package pkg;

            struct {
                int weight;
                int size;
                int volume;
                int expectedResult;
                char* description;
            } testCases[] = {
                {100, 1, 2, 1, "normal value test"},
                {600, 1, 2, 0, "over weight capacity"},
                {1900, 1, 20, 0, "over volume capacity"},
                {-50, -1, 0, 0, "invalid"}
            };

            for (int i = 0; i < sizeof(testCases) / sizeof(testCases[0]); i++) {

                pkg.weight = testCases[i].weight;
                pkg.size = testCases[i].size;
                int result = canAddPackage(&truck, &pkg);

                // Assert if canAddPackage result is correct
                Assert::AreEqual(testCases[i].expectedResult, result);

                if (result == 1) {
                    addPackage(&truck, pkg);
                }

                // No print state, just checking results
                Assert::AreEqual(testCases[i].expectedResult, result);
            }
        }


        TEST_METHOD(testCanAddAndCountPackages)
        {
            struct Truck truck = { 1, 0, 0, 0 };
            struct Package pkg;

            struct {
                int weight;
                int size;
                int expectedResult;
                int expectedCount;
                char* description;
            } testCases[] = {
                {100, 1, 1, 1, "normal value test"},
                {2000, 1, 0, 1, "over weight capacity"},
                {100, 20, 0, 1, "over volume capacity"},
                {-50, -1, 0, 1, "Reject negative package"}
            };

            for (int i = 0; i < sizeof(testCases) / sizeof(testCases[0]); i++) {

                int pkgCount;
                if (i == sizeof(testCases) / sizeof(testCases[0]) - 1) {
                    truck.numPackage = MAX_PACKAGE;  // Simulate full truck
                }

                pkg.weight = testCases[i].weight;
                pkg.size = testCases[i].size;

                // Validate canAddPackage result
                int result = canAddPackage(&truck, &pkg);
                if (result) {
                    addPackage(&truck, pkg);
                    pkgCount = countPackages(&truck);
                }

                // Assert the result
                Assert::AreEqual(testCases[i].expectedResult, result);
                Assert::AreEqual(testCases[i].expectedCount, countPackages(&truck));
            }
        }


        TEST_METHOD(TestAddValidPackageAndCalculateCapacity)
        {
            // Arrange
            Truck truck = { 0, 0, 0, 0, {}, {} }; // Empty truck
            Package pkg = { 500, 5, {} };         // Valid package

            // Act
            int canAdd = canAddPackage(&truck, &pkg);

            // Update the truck if the package can be added
            if (canAdd) {
                truck.tempWeight += pkg.weight;
                truck.tempVolume += pkg.size;
            }

            double capacity = calculateCapacity(&truck);

            // Assert
            Assert::AreEqual(1, canAdd);         // Package should be addable
            Assert::AreEqual(75.0, capacity);    // Remaining capacity should be 75%
        }

        TEST_METHOD(TestAddMultiplePackagesAndCalculateCapacity)
        {
            // Arrange
            Truck truck = { 0, 0, 0, 0, {}, {} }; // Empty truck
            Package pkg1 = { 500, 5, {} };        // Valid package 1
            Package pkg2 = { 1000, 10, {} };      // Valid package 2

            // Act
            int canAdd1 = canAddPackage(&truck, &pkg1);
            if (canAdd1) {
                truck.tempWeight += pkg1.weight;
                truck.tempVolume += pkg1.size;
            }

            int canAdd2 = canAddPackage(&truck, &pkg2);
            if (canAdd2) {
                truck.tempWeight += pkg2.weight;
                truck.tempVolume += pkg2.size;
            }

            double capacity = calculateCapacity(&truck);

            // Assert
            Assert::AreEqual(1, canAdd1);        // Package 1 should be addable
            Assert::AreEqual(1, canAdd2);        // Package 2 should be addable
            Assert::AreEqual(25.0, capacity);    // Remaining capacity should be 25% after adding both packages
        }

        TEST_METHOD(TestAddPackageThatBarelyFits)
        {
            // Arrange
            Truck truck = { 0, 1500, 15, 2, {}, {} }; // Truck with partial load (weight: 1500, volume: 15)
            Package pkg = { 500, 5, {} };            // Package that fits exactly in the remaining capacity

            // Act
            int canAdd = canAddPackage(&truck, &pkg);

            // Update the truck if the package can be added
            if (canAdd) {
                truck.tempWeight += pkg.weight;
                truck.tempVolume += pkg.size;
            }

            double capacity = calculateCapacity(&truck);

            // Assert
            Assert::AreEqual(1, canAdd);         // Package should be addable
            Assert::AreEqual(0.0, capacity);     // Remaining capacity should be 0% after adding the package
        }

        TEST_METHOD(TestAddInvalidPackage)
        {
            // Arrange
            Truck truck = { 0, 0, 0, 0, {}, {} };  // Empty truck
            Package invalidPkg = { -500, -5, {} };  // Invalid package (negative weight and size)

            // Act
            int canAdd = canAddPackage(&truck, &invalidPkg);

            // Assert
            Assert::AreEqual(0, canAdd);          // Package should not be addable (invalid package)
        }

        TEST_METHOD(testEmptyTruck) {
            // Arrange
            struct Truck truck = { 0, 0.0, 0.0 }; // No packages, no weight, no volume

            // Act
            int packageCount = countPackages(&truck);
            double capacity = calculateCapacity(&truck);

            // Assert
            Assert::AreEqual(0, packageCount, L"Expected package count to be 0 for an empty truck.");
            Assert::AreEqual(100.0, capacity, L"Expected capacity to be 100% for an empty truck.");
        }

        TEST_METHOD(testHalfCapacityTruck) {
            // Arrange
            struct Truck truck = { 50, MAX_WEIGHT / 2, MAX_VOLUME / 2 }; // Half weight and volume used

            // Act
            int packageCount = countPackages(&truck);
            double capacity = calculateCapacity(&truck);

            // Assert
            Assert::AreEqual(0, packageCount, L"Expected package count to be 0 for half capacity truck.");
            Assert::AreEqual(50.0, capacity, L"Expected capacity to be 50% for half capacity truck.");
        }


        TEST_METHOD(testMaxWeightTruck) {
            // Arrange
            struct Truck truck = { 100, MAX_WEIGHT, MAX_VOLUME / 2 }; // Full weight, half volume used

            // Act
            int packageCount = countPackages(&truck);
            double capacity = calculateCapacity(&truck);

            // Assert
            Assert::AreEqual(0, packageCount, L"Expected package count to be 100 for truck at max weight.");
            Assert::AreEqual(0.0, capacity, L"Expected capacity to be 50% for truck at max weight.");
        }

        TEST_METHOD(testMaxVolumeTruck) {
            // Arrange
            struct Truck truck = { 75, MAX_WEIGHT - 500, MAX_VOLUME }; // 75% weight, full volume used

            // Act
            int packageCount = countPackages(&truck);
            double capacity = calculateCapacity(&truck);

            // Assert
            Assert::AreEqual(0, packageCount, L"Expected package count to be  for truck at max volume.");
            Assert::AreEqual(0.0, capacity, L"Expected capacity to be 0% for truck at max volume.");
        }



    };
}
