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
@file src/gp/IndividualFactory.h
 */
 
#ifndef GENETIK_GP_INDIVIDUALFACTORY
#define GENETIK_GP_INDIVIDUALFACTORY

#include "../IndividualFactory.h"

namespace genetiK
{

namespace gp
{


/*! @brief Tree initialisation

You can specify to the factory how to initializate the tree.
@ingroup gp
@see IndividualFactory(unsigned char maxHeight,ETreeInitialization treeInitialization)
*/

typedef enum{
	/*! It fills the tree with random node.
	*/
	GROW=0,
	/*! It fills the tree with functions until the maxHeigth is reached.
	*/
	FULL
}ETreeInitialization;

class Gene;

/*! @brief IndividualFactory: GP-specific Individual Factory.

This class extends the generic genetiK::IndividualFactory to generate individuals to
be used with Genetic Algorithms.
@ingroup gp
*/
class IndividualFactory : public genetiK::IndividualFactory
{
private:

	unsigned char					maxHeight;
	ETreeInitialization 				treeInitialization;
public:
	/*! @brief Creates a factory that generates Individual objects for the Genetic Programming

	@param maxHeight max height of the tree
	@param treeInitialization Tree initialization method: FULL or GROW
	@see EGenerateGeneFlags
	 */
	IndividualFactory(unsigned char maxHeight,ETreeInitialization treeInitialization);
	/*! @brief destructor

	 */
	virtual ~IndividualFactory();

	/*! @brief abstract generate function

	This function must be extended by sublcasses to generate appropriate individuals.
	@return a new Individual
	 */	
	genetiK::Individual*				generate()=0;
	
	/*! @brief Node flags
	
	These flags specifies what generateGene should generate.
	@ingroup gp
	@see generateGene(EGenerateGeneFlags flags)
	*/
	typedef enum{
		/*!
			The next gene might be a terminal
		*/
		TERMINAL=1,
		/*!
			The next gene might be a function
		*/
		FUNCTION=2
	}EGenerateGeneFlags;
	/*! @brief abstract generate gene function

	This function must be extended by sublcasses to generate appropriate gene.
	This function returns a random gene obeying the rules specified in flags.
	@param flags TERMINAL for a gene with arity equal to 1 and FUNCTION for a gene with greter or equal to 1. If both the flags are specified, you should return a random gene (TERMINAL or FUNCTION)
	@return a random gene
	 */		
	virtual Gene*					generateGene(EGenerateGeneFlags flags)=0;
	/*! @brief generate a new branch

	This function generate a new branch.
	@param height the max height of the new branch
	@param treeInitialization GROW or FULL
	@return the new branch
	 */	
	virtual Gene*					generateBranch(unsigned char height,ETreeInitialization treeInitialization);
	/*! @brief generate a new tree

	It simply calls the generateBranch with the appropriate height
	
	@return the new tree
	@see generateBranch
	*/		
	virtual Gene*					generateTree();

	/*! @brief max heigth of a tree

	return the upper bound of a tree height
	@return the upper bound
	@see generateBranch
	 */			
	unsigned char 					getMaxHeight() const{ return maxHeight;}
	
	/*! @brief return the tree initialization method

	return the tree initialization method
	@return the tree initialization method
	@see ETreeInitialization
	 */			
	ETreeInitialization				getTreeInitialization() const{ return treeInitialization;}
protected:

	/*!@brief populate a node generating all its subbranches

	This method generates all branchRoot subbranches.
	@param branchRoot the gene to be populated
	@param height the max height of the subbranches
	*/
	virtual void					generateChildren(Gene* branchRoot, unsigned char height);
	
};

}	
}

#endif
