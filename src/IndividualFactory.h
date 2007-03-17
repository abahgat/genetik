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
@file src/IndividualFactory.h
@brief Generic IndividualFactory header file
 */

#ifndef GENETIK_INDIVIDUALFACTORY
#define GENETIK_INDIVIDUALFACTORY

namespace genetiK{

class Individual;

/*! @brief IndividualFactory: generic Individual Factory.

This <b>abstract</b> class is used to generate the individual to be used in a specific evolutionary algorithm.
When extending the Individual class, this class should be extended as well, to give EvolutionaryAlgorithm
to create individuals of the appropriate type.

@see Individual
@ingroup genetiK
 */
class IndividualFactory
{
public:
	/*! @brief default void constructor

	Does nothing (class is abstract)
	*/
	IndividualFactory(void);

	/*! @brief default destructor

	Does nothing (class is abstract)
	*/
	virtual ~IndividualFactory(void);

	/*! @brief abstract generate function

	This function must be extended by sublcasses to generate appropriate individuals.
	@return a new Individual
	*/
	virtual Individual*									generate() =0;
};

}


#endif
