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
@file src/Individual.h
@brief Generic Individual header file
 */

#ifndef GENETIK_INDIVIDUAL
#define GENETIK_INDIVIDUAL

#include <string>


/*
	This class rapresents the individual.
*/
namespace genetiK{

/*! @brief Individual: generic %Individual.

Generic individual to be used with evolutionary algorithms. It is extended by ga::Individual and gp::Individual
to provide specific functions oriented towards Genetic Algorithms and Genetic Programming, respectively.

@see IndividualFactory
@ingroup genetiK
 */
class Individual
{
protected:
public:
	/*! @brief default void constructor

	Does nothing
	*/
	Individual(void);

	/*! @brief default copy constructor

	Does nothing
	*/
	Individual(const Individual& individual);

	/*! @brief default destructor

	Does nothing (class is abstract)
	*/
	virtual ~Individual(void);

	/*! @brief abstract fitness function

	This function must be extended by sublcasses to calculate the fitness of the individual.
	@return the fitness of the current individual
	*/
	virtual double									fitness()=0;

	/*! @brief abstract copy function

	This function must be extended by sublcasses to perform copy.
	@return a copy of the individual
	@see Individual(const Individual& individual)
	*/
	virtual Individual*								copy()const=0;

	/*! @brief abstract mutation

	Must be overridden in subclasses to perform actual mutation.
	@param mutationProbability the probability that mutation occurs
	@return 0 if the operation was successful
	@see crossOver
	*/
	virtual int									mutate(const double mutationProbability)=0;

	/*! @brief abstract crossover

	Performs crossover between this and individual i, saving the resulting children in child1 and child2.
	Subclasses must override this method to perform actual crossover

	@param i the partner to use to perform crossover.
	@param child1 first child.
	@param child2 second child.
	@return 0 if the operation was successful
	@see mutate(double mutationProbabilty)
	*/
	virtual int									crossOver(Individual* i,Individual** child1,Individual** child2)=0;


	/*! @brief creates a string representing the individual

	Subclasses must override this method to output an appropriate representation of the Individual.

	@return a string representation of the individual
	*/
	virtual std::string								toString()const;

	/*! @brief compares fitness between individuals

	Defines an total order relation among Individuals using their fitness.

	@param i2 the individual to use in the comparison
	@return true if this Individual has a fitness that is less than i2's one
	@see fitness()
	*/
	virtual bool									operator < (Individual& i2) { return this->fitness() < i2.fitness(); }
};

/*! @brief &lt;&lt; operator

Put to stream operator. Outputs the individual as a string. It's behaviour is specified by Individual::toString() method.
@param os the stream to output the individual to
@param ind the individual to output
@return the output stream
@see genetiK::Individual::toString()
@ingroup genetiK
*/
std::ostream& operator<<(std::ostream& os, const Individual& ind);

}


#endif
