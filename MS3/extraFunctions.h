#ifndef NEW_STRUCTURE_H
#define NEW_STRUCTURE_H
#include "mapping.h" 

// CUSTOM FUNCTIONS
void addPackage(struct Truck* tr, struct Package pkg); 
double calculateCapacity(const struct Truck* tr);
struct Path calculatePath(const struct Map* m, struct Point begin, struct Point dest);
int canAddPackage(const struct Truck* tr, const struct Package* pkg);
int countPackages(const struct Truck* tr);

#endif // !NEW_STRUCTURE_H
