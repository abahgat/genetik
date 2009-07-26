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
#include <stdlib.h>
using namespace std;

#include "TournamentSelection.h"

#include "Population.h"
#include "Individual.h"

#include "util/util.h"

using namespace genetiK::util;

namespace genetiK {

TournamentSelection::TournamentSelection(unsigned int size):
population(NULL),
size(size),
best(NULL)
{
}

TournamentSelection::~TournamentSelection(void)
{
	
}

Individual* TournamentSelection::getBest()
{
	if (!best)
	{
		Log::getInstance()->debug("Best individual not cached, calculating");
		best = population->getBest();
	}

	return best;
}

Individual* TournamentSelection::select()
{
	if (!population) throw IllegalStateException("Called RouletteWheel::select() without calling init() before.");

	Individual* tempBest = NULL;
	Individual** individuals = population->getIndividuals();

	double maxFitness = -1;
	for (unsigned int i = 0; i < size; ++i)
	{
		unsigned int randomIndex = Random::getImplementation()->getNextInt(population->getSize());
	
		double fitness = individuals[randomIndex]->fitness();
		if (fitness>maxFitness){
			maxFitness = fitness;
			tempBest = individuals[randomIndex];
		}
	}
	return tempBest;
}

}
