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

/*! 
@file src/Population.h
@brief Header file for Population class
 */

#ifndef GENETIK_POPULATION
#define GENETIK_POPULATION

/*
	This class rapresents the population, as a collection of individual.
*/

namespace genetiK{

class Individual;

/*! @brief Population is a collection of Individual objects

The Population class represents a single generation of Individuals in a given stage of the execution of an EvolutionaryAlgorithm

@see Individual
@ingroup genetiK
 */
class Population
{

private:
	unsigned int									size;
	Individual**									individuals; /* array of Individual*/

public:
	/*! @brief creates a new Population able to hold <b>size</b> Individuals
	*/
	Population(unsigned int size);

	/*! @brief destroys this population and the Idividual objects it contains
	@see Individual::~Individual(void);
	*/
	virtual ~Population(void);

	/*! @brief retrieves the size of the population
	@return the size
	*/
	unsigned int									getSize() const { return size; }

	/*! @brief retrieves the Individual collection
	@deprecated This method should be changed soon
	@return all the Individual objects
	*/
	Individual**									getIndividuals(){ return individuals; }

	/*! @brief retrieves the Individual having highest fitness in the Population
	@return the best Individual
	@see Individual::fitness()
	*/
	Individual* 									getBest();

	/*! @brief sort individuals by fitness

	Sorts the Individuals in this Population by fitness, in ascending or descending order
	@param ascending specifies if sorting is ascending or not
	@see fitness
	*/
	void										sort(bool ascending=true);

};

}

#endif
