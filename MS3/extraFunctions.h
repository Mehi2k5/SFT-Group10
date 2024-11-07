#ifndef EXTRA_FUNCTIONS_H
#define EXTRA_FUNCTIONS_H
#include "mapping.h" 

// CUSTOM FUNCTIONS
/*
 * Adding a package to the truck if it fits within the truck's remaining capacity
 * @parameter tr: Pointer to the truck where the package will be added
 * @parameter pkg: The package to add the weight and the size
 */
void addPackage(struct Truck* tr, struct Package pkg); 

/*
 * Calculating the remaining capacity of a truck
 * @parameter tr: Pointer to the truck
 * @return Remaining capacity as a percentage
 */
double calculateCapacity(const struct Truck* tr);

/*
 * Calculating the shortest path from the start point to the destination on mapp
 * @parameter m: Pointer to the map
 * @parameter begin: Starting point
 * @parameter dest: Destination point
 * @return Struct Path containing the calculated path
 */
struct Path calculatePath(const struct Map* m, struct Point begin, struct Point dest);

/*
 * Checking if the package can be added to the truck or not
 * @parameter tr: Pointer to the truck
 * @parameter pkg: The package to check
 * @return 1 if the package can be added, 0 if not
 */
int canAddPackage(const struct Truck* tr, const struct Package* pkg);

/*
 * Counting the number of packages on the truck now
 * @parameter tr: Pointer to the truck
 * @return the number of packages on the truck 
 */
int countPackages(const struct Truck* tr);

#endif // !EXTRA_FUNCTIONS_H
