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
@file src/gp/Individual.h
 */


#ifndef GENETIK_GP_INDIVIDUAL
#define GENETIK_GP_INDIVIDUAL

/*Include the standard genetiK::Individual*/
#include "../Individual.h"


namespace genetiK
{
namespace gp
{


class IndividualFactory;
class Gene;

/*! @brief Individual: GP-specific %Individual.

This class extends the generic genetiK::Individual. It represents an individual as a
gene tree.

@ingroup gp
*/
class Individual : public genetiK::Individual
{
private:

	IndividualFactory*						individualFactory;
	

	Gene*								root;

protected:
	/*! @brief Extract a branch

	Try to find and extract a branch labelled label
	@param label the label of the node to be extracted
	@return the extracted node
	@see getLabel() gp::Gene::extract( const unsigned int label ) const
	 */	
	Gene*								extract( const unsigned int label ) const;
	
	/*! @brief Substitute a branch

	Try to find, and substitute a branch.
	@param label the label of the node to be extracted
	@param newSubTree the new branch
	@return the old branch, be careful for possible memory leak.
	@see getLabel() gp::Gene::substituteBranch( const unsigned int label, Gene* newSubTree )
	 */	
	Gene*								substituteBranch( const unsigned int label, Gene* newSubTree );

	/*! @brief Sets the labels to all the tree

	Sets the labels to all the tree, and compute the cardinality and the eight of each node.
	@see gp::Gene::setLabel()
	 */
	void								setLabels();
	
	/*! @brief Return the cardinality of the tree

	Return the cardinality of the tree.
	The cardinality of the tree is computed when you call setLabels().
	You should call setLabels() before getCardinality(). 
	@return the number of all the genes in the tree
	@see setLabels()
	*/
	unsigned int							getCardinality() const;
	
	/*! @brief Return the factory which generated this individual

	This fuction is used to retrieve the IndividualFactory which generated this individual.
	The IndividualFactory is needed for the cross-over and mutation.
	@return the number of all the genes in the tree
	*/
	IndividualFactory*						getIndividualFactory() const;
	
	/*! @brief Return the root gene of the genetic programming tree

	Return the root gene of the genetic programming tree.
	@return the root gene
	*/
	Gene*								getRoot() const{ return root; }
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
	
	@param mutationProbabilty the probability of the mutation, GP mutate each Individual with this probability. Note that GA mutate each bit with this probability.
	@see crossOver( genetiK::Individual* i,genetiK::Individual** child1,genetiK::Individual** child2)
	 */	
	virtual int							mutate(const double mutationProbabilty);
	
	/*! @brief Cross over
	
	@param i the partner of the cross over. 
	@param child1 the first child. 
	@param child2 the second child. 
	 */	
	virtual int							crossOver( genetiK::Individual* i,genetiK::Individual** child1,genetiK::Individual** child2);


	/*! @brief outputs the individual.

	@return the representation of the individual.
	 */
	virtual std::string						toString()const;
};

}
}

#endif
