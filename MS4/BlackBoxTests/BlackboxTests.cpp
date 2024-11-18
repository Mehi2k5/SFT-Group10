#include "pch.h"
#include "CppUnitTest.h"

// Include the C headers in an extern "C" block for C++ compatibility
extern "C" {
#include "extraStructure.h"
#include "mapping.h"
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BlackboxTests
{
    TEST_CLASS(BlackboxTests)
    {
    public:

        TEST_METHOD(Test_canAddPackage_ValidPackage)
        {
            
            Truck truck;
            truck.tempWeight = 1500;    
            truck.tempVolume = 15;      
            truck.numPackage = 0;       
            truck.colorID = 1;          

            
            Package pkg;
            pkg.weight = 300;           
            pkg.size = 3;               


            addPackage(&truck, pkg);


            Assert::AreEqual(1, truck.numPackage, L"Expected the truck to have 1 package.");
            Assert::AreEqual(1800, truck.tempWeight, L"Expected truck weight to be 1800 after adding the package.");
            Assert::AreEqual(18, truck.tempVolume, L"Expected truck volume to be 18 after adding the package.");
        }


        TEST_METHOD(Test_canAddPackage_almostFull)
        {
            Truck truck;
            truck.tempWeight = 1500;
            truck.tempVolume = 15;
            truck.numPackage = 0;
            truck.colorID = 1;

            Package pkg;
            pkg.weight = 500;
            pkg.size = 5;

            addPackage(&truck, pkg);

            Assert::AreEqual(1, truck.numPackage, L"Expected the truck to have 1 package.");
            
        }


        TEST_METHOD(Test_canAddPackage_Full)
        {
            Truck truck;
            truck.tempWeight = 1500;
            truck.tempVolume = 15;
            truck.numPackage = 0;
            truck.colorID = 1;
            
            Package pkg;
            pkg.weight = 200;
            pkg.size = 10;

            addPackage(&truck, pkg);

            Assert::AreEqual(0, truck.numPackage, L"The truck should not be able to add a package");

        }


        TEST_METHOD(Test_canAddPackage_zeroValues)
        {
            Truck truck;
            truck.tempWeight = MAX_WEIGHT;
            truck.tempVolume = MAX_VOLUME;
            truck.numPackage = 1;
            truck.colorID = 1;

            Package pkg;
            pkg.weight = 200;
            pkg.size = 10;

            addPackage(&truck, pkg);

            Assert::AreEqual(1, truck.numPackage, L"The truck should not be able to add a package");

        }

        TEST_METHOD(Test_countPackages_zeroValue)
        {
            Truck truck;
            truck.numPackage = 0;

            countPackages(&truck);

            Assert::AreEqual(0, truck.numPackage, L"The truck should have no packages");

        }


        
        TEST_METHOD(Test_countPackages_fifty)
        {
            Truck truck;
            truck.numPackage = 50;

            countPackages(&truck);

            Assert::AreEqual(50, truck.numPackage, L"The truck should have 50 packages");

        }

        TEST_METHOD(Test_countPackages_max)
        {
            Truck truck;
            truck.numPackage = MAX_PACKAGE;

            countPackages(&truck);

            Assert::AreEqual(100, truck.numPackage, L"The truck should have 100 packages");

        }


        TEST_METHOD(Test_countPackages_negative)
        {
            Truck truck;
            truck.numPackage = -1;

            countPackages(&truck);

            Assert::AreEqual(-1, truck.numPackage, L"numPackage should be -1");

        }

        
        TEST_METHOD(Test_CalculateCapacity_EmptyTruck)
        {
            Truck truck;
            truck.tempWeight = 0;
            truck.tempVolume = 0;

            double result = calculateCapacity(&truck);

            Assert::AreEqual(100.0, result, L"Expected 100% capacity remaining for an empty truck.");
        }

        TEST_METHOD(Test_CalculateCapacity_ProperFunctioning)
        {
            Truck truck;
            truck.tempWeight = 1000;
            truck.tempVolume = 18;

            double result = calculateCapacity(&truck);

            Assert::AreEqual(10.0, result, L"Expected 10% capacity remaining for an empty truck.");
        }

        TEST_METHOD(Test_CalculateCapacity_EdgeCase_NoWeight)
        {
            Truck truck;
            truck.tempWeight = 0;
            truck.tempVolume = 18;

            double result = calculateCapacity(&truck);

            Assert::AreEqual(10.0, result, L"Expected 10% capacity remaining for an empty truck.");
        }

        TEST_METHOD(Test_CalculateCapacity_EdgeCase_AlmostFull)
        {
            Truck truck;
            truck.tempWeight = 1999;
            truck.tempVolume = 18;

            double result = calculateCapacity(&truck);

            Assert::AreEqual(0.05, result, L"Expected 0.05% capacity remaining for an empty truck.");
        }

        TEST_METHOD(Test_CalculateCapacity_EdgeCase_Full)
        {
            Truck truck;
            truck.tempWeight = 2000;
            truck.tempVolume = 18;

            double result = calculateCapacity(&truck);

            Assert::AreEqual(0.0, result, L"Expected 0.0% capacity remaining for an empty truck.");
        }

        TEST_METHOD(Test_CalculateCapacity_FullWeight)
        {
            Truck truck;
            truck.tempWeight = MAX_WEIGHT;
            truck.tempVolume = 0;

            double result = calculateCapacity(&truck);

            Assert::AreEqual(0.0, result, L"Expected 0% capacity remaining when the truck is at full weight.");
        }

        TEST_METHOD(Test_CalculateCapacity_FullVolume)
        {
            Truck truck;
            truck.tempWeight = 0;
            truck.tempVolume = MAX_VOLUME;

            double result = calculateCapacity(&truck);

            Assert::AreEqual(0.0, result, L"Expected 0% capacity remaining when the truck is at full volume.");
        }

        TEST_METHOD(Test_CalculateCapacity_HalfLoad)
        {
            Truck truck;
            truck.tempWeight = 1000;  // Half of the maximum weight
            truck.tempVolume = 10;    // Half of the maximum volume

            double result = calculateCapacity(&truck);

            Assert::AreEqual(50.0, result, L"Expected 50% capacity remaining for half load.");
        }

        TEST_METHOD(Test_CalculateCapacity_WeightGreaterThanVolume)
        {
            Truck truck;
            truck.tempWeight = 1600;  // 80% of the maximum weight
            truck.tempVolume = 4;     // 20% of the maximum volume

            double result = calculateCapacity(&truck);

            Assert::AreEqual(20.0, result, L"Expected 20% capacity remaining (volume is the limiting factor).");
        }

        TEST_METHOD(Test_CalculateCapacity_VolumeGreaterThanWeight)
        {
            Truck truck;
            truck.tempWeight = 400;   // 20% of the maximum weight
            truck.tempVolume = 16;    // 80% of the maximum volume

            double result = calculateCapacity(&truck);

            Assert::AreEqual(20.0, result, L"Expected 20% capacity remaining (weight is the limiting factor).");
        }

        TEST_METHOD(Test_CalculateCapacity_VaryingLoad)
        {
            Truck truck;
            truck.tempWeight = 1200;  // 60% of the maximum weight
            truck.tempVolume = 8;     // 40% of the maximum volume

            double result = calculateCapacity(&truck);

            Assert::AreEqual(40.0, result, L"Expected 40% capacity remaining (volume is the limiting factor).");
        }

        TEST_METHOD(Test_distance_function)
        {
            Point a;
            Point b;

            a.row = '3';
            a.col = '5';
            
            b.row = '3';
            b.col = '5';

            double result = distance(&a, &b);

            Assert::AreEqual(0.0, result, L"Expected 0 length");
        }

        TEST_METHOD(Test_distance_changeCol)
        {
            Point a;
            Point b;

            a.row = '1';
            a.col = '5';

            b.row = '1';
            b.col = '10';

            double result = distance(&a, &b);

            Assert::AreEqual(5.0, result, L"Expected 5.0 length");
        }


        TEST_METHOD(Test_distance_changeRow)
        {
            Point a;
            Point b;

            a.row = '6';
            a.col = '1';

            b.row = '12';
            b.col = '1';

            double result = distance(&a, &b);

            Assert::AreEqual(4.0, result, L"Expected 6.0 length");
        }



        TEST_METHOD(Test_eqpt_diffPoints)
        {
            Point a;
            Point b;

            a.row = '5';
            a.col = '3';

            b.row = '7';
            b.col = '3';

            int result = eqPt(a, b);

            Assert::AreEqual(0, result, L"Suppose to be not equal");
        }


        TEST_METHOD(Test_eqpt_diffPoints2)
        {
            Point a;
            Point b;

            a.row = '7';
            a.col = '2';

            b.row = '7';
            b.col = '3';

            int result = eqPt(a, b);

            Assert::AreEqual(0, result, L"Suppose to be not equal");
        }


        TEST_METHOD(Test_eqpt_equal)
        {
            Point a;
            Point b;

            a.row = '7';
            a.col = '7';

            b.row = '7';
            b.col = '7';

            int result = eqPt(a, b);

            Assert::AreEqual(1, result, L"Suppose to be equal");
        }

        
        
        TEST_METHOD(Test_eqpt_notValid)
        {
            Point a;
            Point b;

            a.row = '+';
            a.col = ';';

            b.row = '*';
            b.col = '/';

            int result = eqPt(a, b);

            Assert::AreEqual(0, result, L"Suppose to be not equal");
        }



        TEST_METHOD(Test_getNumRows_normal)
        {
            Map map;

            map.numRows = 5;

            int result = getNumRows(&map);

            Assert::AreEqual(5, result, L"Suppose to be 5");
        }



        TEST_METHOD(Test_getNumRows_normal2)
        {
            Map map;

            map.numRows = 50;

            int result = getNumRows(&map);

            Assert::AreEqual(50, result, L"Suppose to be 50");
        }


        TEST_METHOD(Test_getNumRows_fail)
        {
            Map map;

            map.numRows = 'a';

            int result = getNumRows(&map);

            Assert::AreEqual(97, result, L"A non-integer should cause the test to fail");
        }

        TEST_METHOD(Test_getNumRows_negative)
        {
            Map map;

            map.numRows = -1;

            int result = getNumRows(&map);

            Assert::AreEqual(-1, result, L"Negative value should cause test to fail");
        }








    };
}
