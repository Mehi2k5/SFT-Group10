#include <stdio.h>
#include <assert.h>
#include "extraStructure.h"
#include "extraFunctions.h"
#include "mapping.h"


// Function prototype
double calculateCapacity(const struct Truck* tr);

// The test function
void testCalculateCapacity() {
    struct Truck truck;

    // Test 1: Truck is empty (no load)
    truck.tempWeight = 0;
    truck.tempVolume = 0;
    double result = calculateCapacity(&truck);
    assert(result == 100.0);  // Expected output: 100% capacity remaining
    printf("Test 1 passed: Truck is empty, remaining capacity: %.2f%%\n", result);

    // Test 2: Truck is at full capacity (weight)
    truck.tempWeight = MAX_WEIGHT;
    truck.tempVolume = 0;
    result = calculateCapacity(&truck);
    assert(result == 0.0);  // Expected output: 0% capacity remaining (weight full)
    printf("Test 2 passed: Truck is at full weight, remaining capacity: %.2f%%\n", result);

    // Test 3: Truck is at full capacity (volume)
    truck.tempWeight = 0;
    truck.tempVolume = MAX_VOLUME;
    result = calculateCapacity(&truck);
    assert(result == 0.0);  // Expected output: 0% capacity remaining (volume full)
    printf("Test 3 passed: Truck is at full volume, remaining capacity: %.2f%%\n", result);

    // Test 4: Truck has some load, but not full
    truck.tempWeight = 1000;  // Half of the maximum weight
    truck.tempVolume = 10;    // Half of the maximum volume
    result = calculateCapacity(&truck);
    assert(result == 50.0);  // Expected output: 50% capacity remaining (weight and volume are the same)
    printf("Test 4 passed: Truck has some load, remaining capacity: %.2f%%\n", result);

    // Test 5: Truck has more weight than volume
    truck.tempWeight = 1600;  // 80% of the maximum weight
    truck.tempVolume = 4;     // 20% of the maximum volume
    result = calculateCapacity(&truck);
    assert(result == 20.0);  // Expected output: 20% capacity remaining (volume is the limiting factor)
    printf("Test 5 passed: Truck has more weight than volume, remaining capacity: %.2f%%\n", result);

    // Test 6: Truck has more volume than weight
    truck.tempWeight = 400;   // 20% of the maximum weight
    truck.tempVolume = 16;    // 80% of the maximum volume
    result = calculateCapacity(&truck);
    assert(result == 20.0);  // Expected output: 20% capacity remaining (weight is the limiting factor)
    printf("Test 6 passed: Truck has more volume than weight, remaining capacity: %.2f%%\n", result);

    // Test 7: Truck is half full (with varying weight and volume)
    truck.tempWeight = 1200;  // 60% of the maximum weight
    truck.tempVolume = 8;     // 40% of the maximum volume
    result = calculateCapacity(&truck);
    assert(result == 40.0);  // Expected output: 40% capacity remaining (volume is the limiting factor)
    printf("Test 7 passed: Truck is half full, remaining capacity: %.2f%%\n", result);
}
