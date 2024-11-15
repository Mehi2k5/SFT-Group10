#include <stdio.h>
#include "extraFunctions.h" // include header file
#include "extraStructure.h" // include header file
#include "mapping.h" // include header file

/*
 * Adding a package to the truck if it fits within the truck's remaining capacity
 * @parameter tr: Pointer to the truck where the package will be added
 * @parameter pkg: The package to add the weight and the size
 */
void addPackage(struct Truck* tr, struct Package pkg)
{
	if (tr->numPackage < MAX_PACKAGE && tr->tempWeight + pkg.weight <= MAX_WEIGHT && tr->tempVolume + pkg.size <= MAX_VOLUME)
	{
		tr->package[tr->numPackage] = pkg; // add package
		tr->tempWeight += pkg.weight;      // add weight to the current weight
		tr->tempVolume += pkg.size;        // add volume to the current volume
		tr->numPackage++;                  // increase the package + 1
	}
	else
	{
		printf("Cannot add! Truck %d is full", tr->colorID); // message when can not add to truck
	}
}

/*
 * Calculating the remaining capacity of a truck
 * @parameter tr: Pointer to the truck
 * @return Remaining capacity as a percentage
 */
double calculateCapacity(const struct Truck* tr)
{
	double remainWeight = ((double)(MAX_WEIGHT - tr->tempWeight) / MAX_WEIGHT) * 100; // calculating the remaining of weight
	double remainVolume = ((double)(MAX_VOLUME - tr->tempVolume) / MAX_VOLUME) * 100; // calculating the remaining of volume
	return (remainWeight < remainVolume) ? remainWeight : remainVolume; // return the current weight or current volume based on the condition
}

/*
 * Calculating the shortest path from the start point to the destination on mapp
 * @parameter m: Pointer to the map
 * @parameter begin: Starting point
 * @parameter dest: Destination point
 * @return Struct Path containing the calculated path
 */
struct Path calculatePath(const struct Map* m, struct Point begin, struct Point dest)
{
	struct Path path; // use struct Path
	path.length = 0;  // assign with 0 first

	if (begin.row == dest.row && begin.col == dest.col) // check the condition when the begin point and destination point at the same place
	{
		path.point[path.length++] = begin; // increase 
		return path;
	}

	struct Point temp = begin; 

	while (temp.col != dest.col)   // check if the current column different from the destination point
	{
		if (temp.col < dest.col)
		{
			temp.col++;
		}
		else
		{
			temp.col--;
		}
		path.point[path.length++] = temp;
	}

	while (temp.row != dest.row) // check if the current row different from the destination point
	{
		if (temp.row < dest.row)
		{
			temp.row++; 
		}
		else
		{
			temp.row--;
		}
		path.point[path.length++] = temp;
	}
	return path; // return the current path
}

/*
 * Checking if the package can be added to the truck or not
 * @parameter tr: Pointer to the truck
 * @parameter pkg: The package to check
 * @return 1 if the package can be added, 0 if not
 */
int canAddPackage(const struct Truck* tr, const struct Package* pkg) {
	int remainingWeight = MAX_WEIGHT - tr->tempWeight;
	int remainingVolume = MAX_VOLUME - tr->tempVolume;

	if (pkg->weight < 0 || pkg->size < 0) {
		return 0;  // Invalid package (reject negative values)
	}

	if (pkg->weight <= remainingWeight && pkg->size <= remainingVolume) {
		return 1;  // Package can be added
	}

	return 0;  
}

/*
 * Counting the number of packages on the truck now
 * @parameter tr: Pointer to the truck
 * @return the number of packages on the truck 
 */
int countPackages(const struct Truck* tr) 
{
	return tr->numPackage;  // return the current number of package
}
