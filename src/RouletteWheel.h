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
@file src/RouletteWheel.h
@brief RouletteWheel SelectionMethod header file
 */

#ifndef GENETIK_ROULETTEWHEEL
#define	GENETIK_ROULETTEWHEEL

#include "SelectionMethod.h"

namespace genetiK{

class Population;
class Individual;

/*! @brief selects an Individual from a Population using <i>Roulette Wheel</i> policy

This class encapsulates the &quot;Roulette Wheel&quot; policy to select individuals from a population.

Roulette Wheel selection is defined as follows: 
each Individual <i>i</i> in the Population can be selected with probability
\f[
P_i = \frac{f_i}{\sum\limits_{j=0}^{N-1}f_j}
\f]
where \f$f_j\f$ is the fitness of <i>i</i>

@see Individual::fitness(), SelectionMethod, RankingSelection and TournamentSelection
@ingroup genetiK
 */
class RouletteWheel : public SelectionMethod 
{
private:
	Population*							population;
	double*								fitnessRipartition;
	Individual*							best;
public:
	/*! @brief default constructor
	*/
	RouletteWheel(void);

	/*! @brief default destructor
	*/
	virtual ~RouletteWheel(void);

	/*! @brief initializes the RouletteWheel selection method with a specific Population

	When initializing, the Cumulative Distribution Function (CDF) associated to the probability distribution defined by the previously mentioned \f$P_i\f$ is calculated.
	@param population the Population to select the Individuals from
	*/
	void								init(Population* population);

	/*! @brief selects an Individual from the current Population

	An Individual <i>i</i> will be selected with probability
	\f[
	P_i = \frac{f_i}{\sum\limits_{j=0}^{N-1}f_j}
	\f]
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
