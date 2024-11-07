#include <stdio.h>
#include "extraFunctions.h"
#include "extraStructure.h"
#include "mapping.h"
void addPackage(struct Truck* tr, struct Package pkg)
{
	if (tr->numPackage < MAX_PACKAGE && tr->tempWeight + pkg.weight <= MAX_WEIGHT && tr->tempVolume + pkg.size <= MAX_VOLUME)
	{
		tr->package[tr->numPackage] = pkg; // add package
		tr->tempWeight += pkg.weight;      // add weight to the current weight
		tr->tempVolume += pkg.size;        // add volume to the current volume
		tr->numPackage++;
	}
	else
	{
		printf("Cannot add! Truck %d is full", tr->colorID);
	}
}

double calculateCapacity(const struct Truck* tr)
{
	double remainWeight = ((double)(MAX_WEIGHT - tr->tempWeight) / MAX_WEIGHT) * 100;
	double remainVolume = ((double)(MAX_VOLUME - tr->tempVolume) / MAX_VOLUME) * 100;
	return (remainWeight < remainVolume) ? remainWeight : remainVolume;
}

struct Path calculatePath(const struct Map* m, struct Point begin, struct Point dest)
{
	struct Path path;
	path.length = 0;

	if (begin.row == dest.row && begin.col == dest.col)
	{
		path.point[path.length++] = begin;
		return path;
	}

	struct Point temp = begin;

	while (temp.col != dest.col)
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

	while (temp.row != dest.row)
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
	return path;
}

int canAddPackage(const struct Truck* tr, const struct Package* pkg) {
	int remainingWeight = MAX_WEIGHT - tr->tempWeight;
	int remainingVolume = MAX_VOLUME - tr->tempVolume;

	if (pkg->weight < 0 || pkg->size < 0) {
		return 0;  // Invalid package (reject negative values)
	}

	if (pkg->weight <= remainingWeight && pkg->size <= remainingVolume) {
		return 1;  // Package can be added
	}

	return 0;  // Package cannot be added
}

int countPackages(const struct Truck* tr) 
{
	return tr->numPackage; 
}
