/* 
 * 		genetik - Genetic Kernel Library 
 *
 * Copyright (C) 2006 Alessandro Bahgat Shehata, Daniele Castagna
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 * 
 * Alessandro Bahgat Shehata - ale (DOT) bahgat (AT) gmail (DOT) com
 * Daniele Castagna - daniele (DOT) castagna (AT) gmail (DOT) com
 * 
 */

#include <algorithm>

using namespace std;

#include "Population.h"
#include "Individual.h"
#include "util/util.h"

namespace genetiK {

Population::Population(unsigned int size) :
	size( size )
{
	individuals = new Individual*[size];
	if (!individuals) {
		genetiK::util::Log::getInstance()->fatal("Cannot create individuals array");
		throw util::Exception("Population: Failure in individual array creation");
	}

	memset(individuals,0,size);

}

Population::~Population(void)
{
	for (unsigned int i=0; i<size; i++)
		if (individuals[i]) 
			delete individuals[i];
	delete [] individuals;
}

Individual* Population::getBest()
{
	Individual* best = NULL;
	double maxFitness = -1;
	for (unsigned int i = 0; i < size; ++i) {
		double fitness = individuals[i]->fitness();
		if (fitness>maxFitness) {
			maxFitness = fitness;
			best = individuals[i];
		}
	}
	return best;
}

class DescendingIndividualComparer
{
public:
	//Return true if i1 >= s2; otherwise, return false.
	bool operator() (Individual* i1, Individual* i2) { return *i2 < *i1; }
};

class AscendingIndividualComparer
{
public:
	//Return true if i1 < s2; otherwise, return false.
	bool operator() (Individual* i1, Individual* i2) { return *i1 < *i2; }
};

void Population::sort(bool ascending)
{	
	if (ascending)
		std::sort(individuals, individuals+size, AscendingIndividualComparer());
	else
		std::sort(individuals, individuals+size, DescendingIndividualComparer());
}

}
