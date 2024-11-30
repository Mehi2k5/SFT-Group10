#include "pch.h"
#include "CppUnitTest.h"
#include "extraStructure.h"
#include "assert.h"
extern "C" {
#include "extraStructure.h"
#include "mapping.h"
}
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace WhiteboxTest
{
    TEST_CLASS(WhiteboxTest)
    {
    public:

        // test addPackage
        TEST_METHOD(TestAddPackage) 
        {
            Truck truck = { 0, 1000, 15, 0, {}, {} };
            Package pkg = { 500, 3 }; // Within capacity

            addPackage(&truck, pkg);

            Assert::AreEqual(1500, truck.tempWeight); 
            Assert::AreEqual(18, truck.tempVolume);  
            Assert::AreEqual(1, truck.numPackage);   

            truck.tempWeight = MAX_WEIGHT; 
            addPackage(&truck, pkg);
            Assert::AreEqual(2000, truck.tempWeight); 
        }

        // test calculateCapacity
        TEST_METHOD(TestCalculateCapacity) 
        {
            Truck truck = { 0, 1000, 15, {} };

            double capacity = calculateCapacity(&truck);
            Assert::AreEqual(25, capacity, 0.01); 

            // Max weight
            truck.tempWeight = MAX_WEIGHT;
            capacity = calculateCapacity(&truck);
            Assert::AreEqual(0.0, capacity, 0.01);

            // Max volume
            truck.tempVolume = MAX_VOLUME;
            capacity = calculateCapacity(&truck);
            Assert::AreEqual(0.0, capacity, 0.01);
        }


        // test canAddPackage
        TEST_METHOD(TestCanAddPackage) {
            Truck truck = { 0, 1000, 15, {} };
            Package pkg = { 500, 3 };

            Assert::AreEqual(1, canAddPackage(&truck, &pkg)); // Package fits

            pkg.weight = 1500; // Exceeds remaining weight
            Assert::AreEqual(0, canAddPackage(&truck, &pkg)); // Should reject

            pkg.weight = 500;
            pkg.size = 10; // Exceeds remaining volume
            Assert::AreEqual(0, canAddPackage(&truck, &pkg)); // Should reject
        }


        // test calculatePath
        TEST_METHOD(TestCalculatePath) 
        {
            Map map; // Assume initialized map
            Point start = { 0, 0 };
            Point dest = { 3, 3 };

            Path path = calculatePath(&map, start, dest);

            Assert::AreEqual(6, path.length); 
            Assert::AreEqual(1, (int)path.point[3].row); 
            Assert::AreEqual(3, (int)path.point[3].col);
        }

        // test countPackages
        TEST_METHOD(TestCountPackages)
        {
            Truck truck = { 0, 1000, 15, 3, {}, {} };
            Assert::AreEqual(3, countPackages(&truck)); 
            truck.numPackage = 0;
            Assert::AreEqual(0, countPackages(&truck));
        }


    };
}
