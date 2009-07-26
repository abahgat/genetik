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

#include <sstream>

#include "EvolutionaryAlgorithm.h"
#include "Population.h"
#include "IndividualFactory.h"
#include "Individual.h"
#include "StopCriterion.h"
#include "StopCriterionMaxIteration.h"
#include "RouletteWheel.h"

#include "util/util.h"

using namespace std;

using namespace genetiK::util;

namespace genetiK
{
EvolutionaryAlgorithm::EvolutionaryAlgorithm(const unsigned int populationSize,IndividualFactory* factory,
                                       StopCriterion* stopCriterion,SelectionMethod* selectionMethod,
                                       const double mutationProbabilty, const double crossOverProbabilty,const bool elitism) :
                stopCriterion( stopCriterion ),
                population( NULL ),
		individualFactory( factory ),
                selectionMethod( selectionMethod ),
                populationSize( populationSize ),
                crossOverProbabilty ( crossOverProbabilty ),
                mutationProbabilty ( mutationProbabilty ),
                elitism(elitism)
{}

EvolutionaryAlgorithm::~EvolutionaryAlgorithm(void)
{
	delete individualFactory;
	delete stopCriterion;
	delete selectionMethod;
	delete population;
}

int EvolutionaryAlgorithm::run()
{

	if (!selectionMethod) {
		Log::getInstance()->warn("Warning, selectionMethod not set, using default roulette wheel");
		selectionMethod = new RouletteWheel();
	}
	
	if (!util::Random::getImplementation()){
		Log::getInstance()->warn("Warning, Random::implementation not set, using default");
		util::Random::setDefaultImplementation();
	}
	
	if (!stopCriterion) {
		Log::getInstance()->warn("Warning, no stopCriterion, using default StopCriterionMaxIteration(1024)");
		stopCriterion = new StopCriterionMaxIteration(1024);
	}
	
        if (generatePopulation()) {
                Log::getInstance()->fatal("Problems generating population");
                return 1;
        }


        unsigned int iteration = 0;
        while(!stopCriterion->reached()) {
                if(evolve()) {
                        Log::getInstance()->fatal("Problems evolving population");
                        return 2;
                }
                iteration++;

		if (Log::getInstance()->isInfoEnabled()) {
			// TODO find a more efficient way (function in util?)
			stringstream os;
			os << "Completed iteration number " << iteration;
                	Log::getInstance()->info(os.str());
		}
        }
        return 0;
}


int EvolutionaryAlgorithm::generatePopulation()
{
        if (!individualFactory) {
                Log::getInstance()->fatal("You must set individualFactory before generating the population");
                return 1;
        }

        population = new Population(populationSize);


        Individual** individuals = population->getIndividuals();
        for (unsigned int i=0; i<population->getSize(); i++) {
                individuals[i] = individualFactory->generate();
                if (!individuals[i]) {
                        Log::getInstance()->fatal("Problems generating one individual");
                        return 2;
                }
        }

        return 0;
}

int EvolutionaryAlgorithm::evolve()
{
	if (!population) throw IllegalStateException("Called EvolutionaryAlgorithm::evolve() without having called generatePopulation() before");

        Population* tempPopulation = new Population(populationSize);

        selectionMethod->init( population );


        unsigned int tempPopulationElements = 0;
        Individual** tempIndividuals = tempPopulation->getIndividuals();
        if (elitism) {
		tempIndividuals[tempPopulationElements++] = selectionMethod->getBest()->copy();
		if (Log::getInstance()->isInfoEnabled())
		{	
			stringstream ss;
			ss << "Selected for survival individual " << *tempIndividuals[0] << " as best (" << tempIndividuals[0]->fitness() << ")";
			Log::getInstance()->info(ss.str());
		}
	}

	util::Random* random = util::Random::getImplementation();

	Log::getInstance()->debug("Evolution: initiating crossover/reproduction phase");

        while(tempPopulationElements<populationSize) {
                Individual* i1 = selectionMethod->select();
                Individual* i2 = selectionMethod->select();

		if (random->getNextReal() < crossOverProbabilty) {
                        Individual* newI1 = NULL;
                        Individual* newI2 = NULL;

                        i1->crossOver(i2,&newI1,&newI2);

                        if (newI1)
                                tempIndividuals[tempPopulationElements++] = newI1;
                        if (newI2 && tempPopulationElements<populationSize)	{
				tempIndividuals[tempPopulationElements++] = newI2;
                        } else if (newI2)
                                delete newI2;

	} else {
                        tempIndividuals[tempPopulationElements++] =  i1->copy();
                        if (tempPopulationElements<populationSize)
				tempIndividuals[tempPopulationElements++] =  i2->copy();
                }
        }

	Log::getInstance()->debug("Evolution: crossover/reproduction complete, beginning mutation");

	delete population;
        population = tempPopulation;

        for (unsigned int i=elitism?1:0; i<populationSize; i++)
                tempIndividuals[i]->mutate(mutationProbabilty);


        return 0;
}
}
