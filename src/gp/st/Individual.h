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
@file src/gp/st/Individual.h
 */


#ifndef GENETIK_GP_ST_INDIVIDUAL
#define GENETIK_GP_ST_INDIVIDUAL

/*Inlcue the standard GenetiK::Individual*/
#include "../Individual.h"

#include <list>

using namespace std;
namespace genetiK
{
namespace gp
{
namespace st
{

/*! @brief The strongly typed type
The GeneType type, is used to add the stronly typed paradigm to the classical genetic programming

@ingroup st
*/
typedef unsigned char GeneType;
class IndividualFactory;
class Gene;

/*! @brief Individual: GP-ST-specific %Individual.

This class extends the generic genetiK::Individual. It represents an individual as a
gene tree, with the type constraints.

@ingroup st
*/

class Individual : public gp::Individual
{
protected:
public:
	/*! @brief creates an Individual and generates its tree.

	@param individualFactory specifies the individualFactory used to generate the tree
	@see Individual(const Individual& individual)
	 */
	Individual(IndividualFactory* individualFactory);
	
	/*! @brief creates a copy of an Individual

	@param individual the Individual to be copied
	@see Individual(const Individual& individual)
	 */
	Individual(const Individual& individual);
	/*! @brief destructor
	 */	
	virtual ~Individual(void);
	
	/*! @brief The fitness function
	
	a function that quantifies the optimality of a solution.
	You should override this function in your Individual implementation, and evaluate your own fitness.
	 */	
	virtual double							fitness()=0;
	
	/*! @brief Copy this individual
	
	copy this Individual.
	You should override this function in your Individual implementation, and return the appropriate new Individual, possibly, using the copy constructor.
	@see Individual(const Individual& individual)
	 */		
	virtual genetiK::Individual*					copy()const=0;
	/*! @brief mutate the individual

	This function is very similar to the gp::Individual::mutate, it only adds the type constraints.	
	@param mutationProbabilty the probability of the mutation, GP mutate each Individual with this probability. Note that GA mutate each bit with this probability.
	This function is very similar to the gp::Individual::mutate, it only adds the type constraints.
	@see gp::Individual::mutate(const double mutationProbabilty)
	 */	


	virtual int							mutate(const double mutationProbabilty);

	/*! @brief Cross over

	This is the same as gp::Individual::crossOver with the type constraint.
	@param i the partner of the cross over. 
	@param child1 the first child. 
	@param child2 the second child. 
	@see gp::Individual::crossOver(genetiK::Individual* i,genetiK::Individual** child1,genetiK::Individual** child2)
	 */	

	virtual int							crossOver(genetiK::Individual* i,genetiK::Individual** child1,genetiK::Individual** child2);
	/*! @brief Extract a typed list from the tree
	
	This method is used by the cross over, to excract a list of gene by type.
	@param geneType the type
	*/
	virtual list<Gene*>						extractListByType(GeneType geneType);
};

}
}
}

#endif
