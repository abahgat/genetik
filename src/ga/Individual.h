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
 * Alessandro Bahgat Shehata - skandar (AT) users (DOT) sourceforge (DOT) net
 * Daniele Castagna - dcastagna (AT) users (DOT) sourceforge (DOT) net
 * 
 */

/*! 
@file src/ga/Individual.h
 */

#ifndef GENETIK_GA_INDIVIDUAL
#define GENETIK_GA_INDIVIDUAL

/*Include the standard genetiK::Individual*/
#include "../Individual.h"

#include <iostream>
#include <string>

namespace genetiK
{
namespace ga
{

/*! @brief Individual: GA-specific %Individual.

This class extends the generic genetiK::Individual. It represents an individual as a
string of bits.

@ingroup ga
 */
class Individual : public genetiK::Individual
{
protected:
	/*! Invididual length (number of bits) */
	unsigned int							length;
	/*! array of the actual bits associated with the Individual (as array of int) */
	unsigned int*							bitArray;
	/*! number of int blocks allocated to store the Individual bits */
	unsigned char							blockNum;
public:
	/*! @brief creates an Individual by allocating <b>length</b> bits and filling them with random data.
	It should be called by subclasses' unsigned int constructors.

	@todo add a constructor that allocates memory but does not initialize with random data
	@param length specifies the length of the individual to be created
	@see Individual(const Individual& individual)
	*/
	Individual(unsigned int length);

	/*! @brief Copy constructor

	Creates this individual by copying individual.
	It should be called by subclasses' copy constructors.
	@param individual the individual to be copied
	@see copy and Individual(unsigned int length)
	*/
	Individual(const Individual& individual);

	/*! @brief destructor

	Destroys this instance, freeing the allocated bits
	@see Individual(unsigned int length) and Individual(const Individual& individual)
	*/
	virtual ~Individual(void);
	
	/*! @brief abstract fitness function

	This function must be extended by sublcasses to calculate the fitness of the individual.
	@return the fitness of the current individual
	*/
	virtual double							fitness()=0;

	/*! @brief abstract copy function

	This function must be extended by sublcasses to perform copy.
	@return a copy of the individual
	@see Individual(const Individual& individual)
	*/
	virtual genetiK::Individual*					copy()const=0;

	/*! @brief standard one-point mutation

	Performs one-point mutation: flips a each bit of the individual with mutationProbability probability.
	@param mutationProbability the probability to mutate a single bit of the Individual
	@return 0 if the operation was successful
	@see crossOver
	*/
	virtual int							mutate(const double mutationProbability);
	
	/*! @brief standard one-point crossover

	Performs one-point crossover between this and individual i, saving the resulting children in child1 and child2.

	@param i the partner to use to perform crossover.
	@param child1 first child.
	@param child2 second child.
	@return 0 if the operation was successful
	@see mutate(double mutationProbabilty)
	*/
	virtual int							crossOver(genetiK::Individual* i, genetiK::Individual** child1, genetiK::Individual** child2);

	/*! @brief Returns Individual's length

	@return this.length
	*/
	unsigned int							getLength() { return length; }

	/*! @brief [] operator

	Accesses a single bit of the individual bit string.
	@param index 0-based index of the bit to retrieve
	@return true if this[index] is 1, false otherwise
	*/
	bool 								operator[] (unsigned int index) const;

	/*! @brief outputs the individual as a sequence of 0s and 1s.

	@return a sequence of 0s and 1s, representing the bits of the current individual.
	*/
	virtual std::string							toString()const;
};

}
}

#endif
