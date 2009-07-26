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
@file src/gp/st/IndividualFactory.h
 */

#ifndef GENETIK_GP_ST_INDIVIDUALFACTORY
#define GENETIK_GP_ST_INDIVIDUALFACTORY

#include "../IndividualFactory.h"

namespace genetiK
{
namespace gp
{
namespace st
{

	
typedef unsigned char GeneType;

/*! @brief IndividualFactory: GP-ST-specific %IndividualFactory.

This class extends the genetiK::gp::Individual class. It represents an individual as a
typed gene tree.

@ingroup st

*/

class IndividualFactory : public gp::IndividualFactory
{

private:
	GeneType			rootType;
	GeneType			nextGeneType;
	
	unsigned char			maxHeight;
public:
	
	/*! @brief Creates a factory that creates Individual objects for the Strongly Typed Genetic Programming

	@param maxHeight max height of the tree
	@param treeInitialization Tree initialization method: FULL or GROW
	@param rootType the type of the root gene
	@see ETreeInitialization
	@see gp::IndividualFactory
	*/
	IndividualFactory(unsigned char maxHeight,gp::ETreeInitialization treeInitialization,GeneType rootType);
	/*! @brief Destructor
	 */
	virtual ~IndividualFactory();
	
	/*! @brief abstract generate function

	This function must be extended by sublcasses to generate appropriate individuals.
	@return a new Individual
	*/
	genetiK::Individual*							generate()=0;

	
	/*! @brief return the type of the next gene to be created
	
	Specifies the type of the next gene to be created.
	@return the type of the next gene
	@see generateGene(EGenerateGeneFlags flags)
	 */		
	GeneType								getNextType() const{ return nextGeneType; }
	
	/*! @brief set the type of the next gene to be created
	
	Specifies the next type of the gene to be created.
	@param nextGeneType the type of the next gene
	@see generateGene(EGenerateGeneFlags flags)
	 */		
	void									setNextType(const GeneType nextGeneType) { this->nextGeneType = nextGeneType; }

	/*! @brief generate a new branch

	This function generate a new branch.
	@param height the max height of the new branch
	@param treeInitialization GROW or FULL
	@return the new branch
	*/	
	virtual gp::Gene*							generateBranch(unsigned char height,ETreeInitialization treeInitialization);
		
	 
protected:
	
	/*! @brief abstract generate gene function

	This function must be extended by sublcasses to generate appropriate gene.
	This function returns a random gene obeying the rules specified in flags and the nextGeneType returning a new random gene of type getNextType().
	
	If the new created gene doesn't satisfy the specified rules, an Exception will be thrown
	@param flags TERMINAL for a gene with arity equal to 1 and FUNCTION for a gene with greter or equal to 1. If both the flags are specified, you should return a random gene (TERMINAL or FUNCTION)
	@return a random gene
	@see getNextType();
		 */		
	virtual gp::Gene*							generateGene(EGenerateGeneFlags flags)=0;

	/*! @brief generate a new tree
	It simply calls the generateBranch with the appropriate height and root type.
	@return the new tree
	@see generateBranch
	 */
	virtual gp::Gene*							generateTree();

	/*!@brief populate a node generating all its subbranches
	This method generates all branchRoot subbranches.
	@param branchRoot the gene to be populated
	@param height the max height of the subbranches
	*/
	virtual void								generateChildren(gp::Gene* branchRoot, unsigned char height);
	
};

}	
}
}

#endif
