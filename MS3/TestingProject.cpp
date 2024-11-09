#include "pch.h"
#include "CppUnitTest.h"
#include "extraStructure.h"
#include "extraFunctions.h"

using namespace Microsoft::VisualStudio::TestingProject;

namespace TestingProject
{
	TEST_MODULE_INITIALIZE(ModuleInitialize)
	{
		Logger::WriteMessage("In Module Initialize");
	}

	TEST_MODULE_CLEANUP(ModuleCleanup)
	{
		Logger::WriteMessage("In Module Cleanup");
	}

	TEST_CLASS(TestingProject)
	{
	public:
        // test for adding package successful
        TEST_METHOD(TestAddPackage_Successful)
        {
            Truck truck = { 1, 1500, 15, 0 };
            Package pkg = { 300, 3, { 'A', '1' } };
            addPackage(&truck, pkg);
            Assert::AreEqual(1, truck.numPackage);
            Assert::AreEqual(1800, truck.tempWeight);
            Assert::AreEqual(18, truck.tempVolume);
        }
        // test for adding package fail
        TEST_METHOD(TestAddPackage_Fail)
        {
            Truck truck = { 1, MAX_WEIGHT - 100, 10, 0 };
            Package pkg = { 200, 5, { 'B', '2' } };
            addPackage(&truck, pkg);
            Assert::AreEqual(0, truck.numPackage); 
        }

        // test for calculating capacity
        TEST_METHOD(TestCalculateCapacity)
        {
            Truck truck = { 1, 500, 5, 0 };
            double remainingCapacity = calculateCapacity(&truck);
            Assert::IsTrue(remainingCapacity > 0);  
        }

        // test for calculating the path in samepoint
        TEST_METHOD(TestCalculatePath_SamePoint)
        {
            Map map;
            Point start = { 0, 0 };
            Point destination = { 0, 0 };
            Path path = calculatePath(&map, start, destination);
            Assert::AreEqual(1, path.length);
            Assert::AreEqual(start.row, path.point[0].row);
            Assert::AreEqual(start.col, path.point[0].col);
        }
        // test for calculating the path at different point
        TEST_METHOD(TestCalculatePath_DifferentPoint)
        {
            Map map;
            Point start = { 0, 0 };
            Point destination = { 2, 2 };
            Path path = calculatePath(&map, start, destination);
            Assert::AreEqual(5, path.length); 
        }

        // test for canAddPackage successful
        TEST_METHOD(TestCanAddPackage_Successful)
        {
            Truck truck = { 1, 1500, 15, 0 };
            Package pkg = { 300, 3, { 'A', '1' } };

            int result = canAddPackage(&truck, &pkg);
            Assert::AreEqual(1, result); 
        }

        // test for caddAddPackage fail
        TEST_METHOD(TestCanAddPackage_Fail)
        {
            Truck truck = { 1, 1500, MAX_VOLUME - 1, 0 };
            Package pkg = { 10, 2, { 'C', '3' } };
            int result = canAddPackage(&truck, &pkg);
            Assert::AreEqual(0, result); 
        }

        // test for countPackages in the empty truck
        TEST_METHOD(TestCountPackages_EmptyTruck)
        {
            Truck truck = { 1, 1500, 15, 0 };
            int result = countPackages(&truck);
            Assert::AreEqual(0, result); 
        }
        // test for counting package has non empty truck
        TEST_METHOD(TestCountPackages_NonEmptyTruck)
        {
            Truck truck = { 1, 1500, 15, 5 };
            int result = countPackages(&truck);
            Assert::AreEqual(5, result); 
        }
    };
}
