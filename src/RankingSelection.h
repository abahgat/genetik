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
@file src/RankingSelection.h
@brief Ranking selection header file
 */

#ifndef GENETIK_RANKINGSELECTION
#define	GENETIK_RANKINGSELECTION

#include "SelectionMethod.h"

namespace genetiK{

class Population;
class Individual;

/*! @brief Ranking Selection method

This selection scheme is designed to select to individuals with a probability that is function of their specific rank in the population, sorted by (ascending) fitness.

More formally, for a generic individual <i>i</i>
\f[
P_i \propto \phi(f_i)
\f]
This class uses by default an exponential function to calculate probability (\f$\phi(x) = e^x\f$). The probability itself is proportional to phi (it is proportional, but not equal, because the class itself encapsulates normalization).
It is possible to override phi to define different selection policies.

@see Individual::fitness(), SelectionMethod, RouletteWheel and TournamentSelection
@ingroup genetiK
 */
class RankingSelection : public SelectionMethod 
{
private:
	Population*							population;
	double*								ripartition;
	unsigned int							size;
public:
	/*! @brief default constructor
	*/
	RankingSelection(void);

	/*! @brief default destructor
	*/
	virtual ~RankingSelection(void);

	/*! @brief initializes the Ranking Selection method with a specific Population

	When initializing, the Cumulative Distribution Function (CDF) associated to the probability distribution defined by the previously mentioned function \f$\phi(f_i)\f$ is calculated.
	@param population the Population to select the Individuals from
	*/
	void								init(Population* population);

	/*! @brief selects an Individual from the current Population

	An Individual <i>i</i> will be selected with probability
	\f[
	P_i = \frac{\phi(f_i)}{max(f_j)}
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

	/*! @brief used to calculate the probability to select an Invididual
	
	It is possible to override this function to customize the schema used to calculate probability to select an Individual.
	This implementation, in particular, defines \f$\phi(x)\f$ as \f$e^x\f$.
	@param rank the position of the Individual in the sorted Population
	@return the value function \f$\phi\f$ described above
	@see Individual::fitness()
	*/
	double								phi(unsigned int rank);
};

}

#endif
