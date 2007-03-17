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
@file src/TournamentSelection.h
@brief RouletteWheel SelectionMethod header file
 */

#ifndef GENETIK_TOURNAMENTSELECTION
#define	GENETIK_TOURNAMENTSELECTION

#include "SelectionMethod.h"

namespace genetiK{

class Population;
class Individual;

/*! @brief selects an Individual from a Population using <i>Tournament</i> policy

This class encapsulates the &quot;Tournament&quot; policy to select individuals from a population.

Tournament selection chooses <i>size</i> individuals from the population, with uniform probability, and then selects the best among them.


@see Individual::fitness(), SelectionMethod, RankingSelection and TournamentSelection
@ingroup genetiK
 */
class TournamentSelection : public SelectionMethod 
{
private:
	Population*							population;
	uint								size;
	Individual*							best;
public:
	
	/*! @brief sets size as the Tournament size
	@param size desired Tournament size
	*/
	TournamentSelection(unsigned int size);

	/*! @brief default destructor
	*/
	virtual ~TournamentSelection(void);

	/*! @brief initializes the RouletteWheel selection method with a specific Population

	@param population the Population to select the Individuals from
	*/
	void								init(Population* population) { this->population = population; best = NULL; };

	/*! @brief selects an Individual from the current Population

	Chooses <i>size</i> individuals from the Populations and selects the best among them.
	@return the selected Individual
	@throw IllegalStateException if the Population has not been previously initialized with init(Population* population)
	@see init(Population* population), IllegalStateException
	*/
	Individual*							select();

	/*! @brief retrieves the Individual having highest fitness in the Population
	@return the best Individual
	@see Individual::fitness()
	*/
	Individual*							getBest();
};

}

#endif
