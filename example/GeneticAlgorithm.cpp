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

#include "../include/libGenetiK.h"

#include "GeneticAlgorithm.h"

using namespace std;
using namespace genetiK;

namespace genetiKEx
{

class ExampleGAIndividual : public ga::Individual {

public:
	ExampleGAIndividual(unsigned int length) :
	genetiK::ga::Individual(length)
 	{
	}

	ExampleGAIndividual(const ExampleGAIndividual& individual) :
	genetiK::ga::Individual(individual)
 	{
	}

	double fitness() {
		double fitness = 0;

		const int blockSize = sizeof(unsigned int)<<3;

		for (int i = 0; i < blockNum; ++i) {
			int last = i < blockNum - 1 || !(length%blockSize) ? 0 : blockSize - length%blockSize;
			int tempBlock = bitArray[i];
			for (int j = (sizeof(int)<<3) - 1; j >= last; --j) {
				if (((tempBlock >> j) & 1))
					++fitness;
			}
		}
	
		return fitness;
	}

	genetiK::Individual* copy() const {
		return new ExampleGAIndividual::ExampleGAIndividual(*this);
	}
};

class ExampleGAIndividualFactory : public ga::IndividualFactory {

public:
	ExampleGAIndividualFactory(unsigned int length) :
	ga::IndividualFactory(length)
	{
	}

	Individual* generate(){
		return new ExampleGAIndividual(getLength());
	}
};

GeneticAlgorithm::GeneticAlgorithm()
{
}

GeneticAlgorithm::~GeneticAlgorithm()
{
}

int GeneticAlgorithm::run(){
	
	util::Log* log = util::Log::getInstance();
	log->setLevel(util::INFO);

	ExampleGAIndividualFactory* individualFactory = new ExampleGAIndividualFactory(32);
	StopCriterionMaxIteration* stopCriterion = new StopCriterionMaxIteration(8);
	//RouletteWheel* rouletteWheel= new RouletteWheel();
	SelectionMethod* selectionMethod = new TournamentSelection(8);
	
	EvolutionaryAlgorithm alg(64,individualFactory,stopCriterion,selectionMethod);
	
	alg.run();

	log->info( alg.getPopulation()->getBest()->toString() );
	
	util::Log::deleteInstance();
	util::Random::deleteImplementation();
	return 0;
}

}
