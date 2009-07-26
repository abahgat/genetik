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

#include <iostream>
#include <math.h>
using namespace std;

#include "RankingSelection.h"

#include "Population.h"
#include "Individual.h"

#include "util/util.h"

using namespace genetiK::util;

namespace genetiK{

RankingSelection::RankingSelection(void):
population(NULL),
ripartition(NULL),
size(0)
{
}

RankingSelection::~RankingSelection(void)
{
	if (ripartition)
		delete [] ripartition;
}

void RankingSelection::init(Population* population)
{
	this->population = population;
	population->sort();
	unsigned int populationSize = population->getSize();
	if (populationSize != size) {
		if (ripartition)
			delete [] ripartition;
		ripartition = new double[populationSize+1];
		ripartition[0]=0;
	
		for (unsigned int i=1; i <= populationSize; ++i)
		{
			double phiValue = phi(i);
			ripartition[i] = ripartition[i-1] + phiValue;
		}
		size = populationSize;
	}
}

Individual*	RankingSelection::getBest()
{
	return population->getIndividuals()[population->getSize()-1];
}

Individual*	RankingSelection::select()
{
	if (!population) throw IllegalStateException("Called RouletteWheel::select() without calling init() before.");
	double random = Random::getImplementation()->getNextReal() * ripartition[population->getSize()];

	int left = 0;
	int right = population->getSize();
	  
	while(true){
		if (right - left == 1){
			if (ripartition[left]<=random && ripartition[right]>random)
				return population->getIndividuals()[left];
			return NULL;
		  }
		int middle = (right + left)>>1;
		if (ripartition[middle]<random)
			left = middle;
		else
			right = middle;
	}

	Log::getInstance()->error("Error, Ranking selection could not select any individual");
	return NULL;
}

double	RankingSelection::phi(unsigned int rank)
{
	return exp(rank);
}

}
