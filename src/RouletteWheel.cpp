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
using namespace std;

#include "RouletteWheel.h"

#include "Population.h"
#include "Individual.h"

#include "util/util.h"

using genetiK::util::Random;
using genetiK::util::Log;
using genetiK::util::IllegalStateException;

namespace genetiK{

RouletteWheel::RouletteWheel(void):
population(NULL),
fitnessRipartition(NULL),
best(NULL)
{
}

RouletteWheel::~RouletteWheel(void)
{
	if (fitnessRipartition)
		delete [] fitnessRipartition;
}

void RouletteWheel::init(Population* population)
{
	this->population = population;
	Individual** individuals=population->getIndividuals();
	unsigned int populationSize = population->getSize();
	if (fitnessRipartition)
		delete [] fitnessRipartition;
	fitnessRipartition = new double[populationSize+1];
	fitnessRipartition[0]=0;

	double maxFitness = -1;
	for (unsigned int i=1; i<=populationSize; i++)
	{
		double fitness = individuals[i-1]->fitness();
		fitnessRipartition[i] = fitnessRipartition[i-1] + fitness;
		
		if (fitness>maxFitness){
			maxFitness = fitness;
			best = individuals[i-1];
		}
	}
	
	//Log::getInstance()->info("RouletteWheel selected as best " + best->toString());
}

Individual*	RouletteWheel::getBest()
{
	return best;
}

Individual*	RouletteWheel::select()
{
	if (!population) throw IllegalStateException("Called RouletteWheel::select() without calling init() before.");
		 
	double random = Random::getImplementation()->getNextReal() * fitnessRipartition[population->getSize()];

	int left = 0;
	int right = population->getSize();
	  
	while(true){
		if (right - left == 1){
			if (fitnessRipartition[left]<=random && fitnessRipartition[right]>random)
				  return population->getIndividuals()[left];
			  return NULL;
		  }
		  
		  int middle = (right + left)>>1;
		  if (fitnessRipartition[middle]<random)
			  left = middle;
		  else
			  right = middle;
	}

	unsigned int popSize = population->getSize();
	if (popSize > 0 && fitnessRipartition[popSize] == 0) {
		Log::getInstance()->info("RouletteWheel: all individuals having 0 fitness score. Random selection.");
		return population->getIndividuals()[Random::getImplementation()->getNextInt(popSize)];
	}
	
	Log::getInstance()->error("Error, Roulette Wheel selection could not select any individual");
	return NULL;
}
}
