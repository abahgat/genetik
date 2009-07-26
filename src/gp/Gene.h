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
@file src/gp/Gene.h
 */


#ifndef GENETIK_GP_GENE
#define GENETIK_GP_GENE


#include <string>

#include "../util/Variant.h"
using namespace std;


namespace genetiK
{
namespace gp
{
class IndividualFactory;


/*! @brief Gene: The node of the genetic programming tree.

This class represents the node of the genetic programming tree.

@ingroup gp
 */
class Gene
{
private:
        unsigned int						cardinality; 
        unsigned char						height; 
        unsigned char						branchDepth;
        unsigned int						label; 

	unsigned char						arity;
	Gene**							argument;

public:

	/*! @brief creates a Gene

	Gene default contructor
	@todo add the copy constructor
	@param arity specifies the arity of the node
 	*/
	Gene(unsigned char arity);
	/*! @brief destructor

	Destroys this gene and all its child, recursively
	 */
	virtual ~Gene();
	
	
	/*! @brief Evaluate the tree

	The cardinality of the node is the number of all descendant plus one (itself).
	@return the evaluated expression
	@see %Variant
	*/
	virtual util::Variant					evaluate()=0;


	/*! @brief outputs the children.

	@return .string containing all the children toString() strings.
	 */
	virtual std::string					toString()const;
	
	/*! @brief Arity

	The number of children of the node.
	@return the arity
	*/
	unsigned char						getArity() const
	{
		return arity;
	}
	/*! @brief Return children

	@return The index of the child
	 */	
	Gene*							getArgument(unsigned char i);
	/*! @brief Sets a child

	@param i The index of the child
	@param newArgument The child to be set
	 */		
	void							setArgument(unsigned char i, Gene* newArgument);

	/*! @brief Cardinality of the node

	The cardinality of the node is the number of all descendant plus one (itself).
	The cardinality of the root is exactly the number of the node in the tree.
	@return the cardinality
	 */
        unsigned int						getCardinality() const
        {
                return cardinality;
        }
 	/*! @brief Label of the node

	The label of the node is an ID used to perform crossover.
	@return the label
	@see setLabels
	 */
	unsigned int						getLabel() const
        {
                return label;
        }
	
	/*! @brief Height of the node

	The height of the node in the tree, starting from 0.
	The root has an height of 0, his children of 1, and so on...
	@return the height
	@see setHeight
	 */
	unsigned char						getHeight() const
        {
                return height;
        }
	/*! @brief Set the current height of the node

	@see getHeight
	 */	
	void							setHeight(unsigned char height)
	{
		this->height = height;
	}
	/*! @brief Branch depth

	The branch depth is
	@return the height
	 */
	unsigned char						getBranchDepth() const
        {
                return branchDepth;
        }

	/*! @brief Extract a branch

	Try to find and extract a branch labelled label
	@param label the label of the node to be extracted
	@return the extracted node
	@see getLabel()
	 */
        Gene*							extract( unsigned int label);
	/*! @brief Substitute a branch

	Try to find, and substitute a branch.
	@param label the label of the node to be extracted
	@param newSubTree the new branch
	@return the old branch, be careful for possible memory leak.
	@see getLabel()
	 */
	Gene*							substituteBranch( unsigned int label, Gene* newSubTree);

	/*! @brief Sets the labels to all the tree

	Sets the labels to all the tree
	@param label the next free label to be set to 
	@return the next free label.
	@see getLabel()
	 */
        unsigned int						setLabels(unsigned int label);

	/*! @brief Copy the branch

	Copy the node and his children, recursively
	@return the copyed branch.
	 */
        virtual Gene*						copyBranch() const;

	/*! @brief Copy the Gene

	Copy this node.
	@return the copyed node.
	 */
        virtual Gene*						copy() const=0;

};

}
}

#endif
