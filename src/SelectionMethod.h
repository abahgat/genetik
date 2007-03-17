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
@file src/SelectionMethod.h
@brief Generic SelectionMethod header file
 */

#ifndef GENETIK_SELECTIONMETHOD
#define	GENETIK_SELECTIONMETHOD

#include "util/IllegalStateException.h"

namespace genetiK{

class Population;
class Individual;

/*! @brief selects an Individual from a Population

This <b>abstract</b> class encapsulates a policy to select individuals from a population. It should be extended to implement specific selection methods.

@see Individual::fitness(), RankingSelection, RouletteWheel and TournamentSelection
@ingroup genetiK
 */
class SelectionMethod
{
private:
	Population*							population;

public:
	/*! @brief default constructor
	*/
	SelectionMethod(void);

	/*! @brief default destructor
	*/
	virtual ~SelectionMethod(void);

	/*! @brief initializes the SelectionMethod with a specific Population
	@param population the Population to select the Individuals from
	*/
	virtual void						init(Population* population){ this->population = population; }

	/*! @brief selects an Individual from the current Population

	Subclasses override this method to implement a specific selection policy
	@throw IllegalStateException if the Population has not been previously initialized with init(Population* population)
	@return the selected Individual
	@see init(Population* population), IllegalStateException
	*/
	virtual Individual*					select()=0;

	/*! @brief retrieves the Individual having highest fitness in the Population
	@return the best Individual
	@see Individual::fitness()
	*/
	virtual Individual*					getBest()=0;
};

}

#endif
