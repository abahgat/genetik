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
@file src/gp/st/Gene.h
 */


#ifndef GENETIK_GP_ST_GENE
#define GENETIK_GP_ST_GENE


#include <vector>
#include <list>
using namespace std;

#include "../Gene.h"



namespace genetiK
{
namespace gp
{
namespace st
{

typedef unsigned char GeneType;

/*! @brief Gene: The node of the genetic programming tree.

This class extends the gp::Gene and adds the type constraints.

@ingroup st
 */
class Gene : public gp::Gene
{
private:
	GeneType						type;
	GeneType*						argumentType;

public:
	/*! @brief creates a Gene
	
	Gene default contructor
	@param type specifies the type of the node
	@param arity specifies the arity of the node
	@param ... specifies a list with the types of the node's children
 	*/
	Gene(GeneType type,unsigned char arity,...);
	/*! @brief destructor
 	*/
 	virtual ~Gene();

	/*! @brief return the type of the node
	
	return the type of the node
	@return the type of the node
 	*/
	GeneType						getType() const{ return type; }
	
	/*! @brief return the type of one child
	
	return the type of one child
	@param i the child index
	@return the type of the child node
 	*/	
	GeneType						getArgumentType(unsigned char i) const{ return argumentType[i]; }
	/*! @brief Extract a typed list from this branch
	
	@param geneType the type
	@see gp::st::Individual::extractListByType(GeneType geneType)
	*/
	virtual list<Gene*>					extractListByType(GeneType geneType);

};

}
}
}

#endif
