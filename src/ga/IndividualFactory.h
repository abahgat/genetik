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
@file src/ga/IndividualFactory.h
 */

#ifndef GENETIK_GA_INDIVIDUALFACTORY
#define GENETIK_GA_INDIVIDUALFACTORY

#include "../IndividualFactory.h"

namespace genetiK
{

namespace ga
{

class Individual;

/*! @brief IndividualFactory: GA-specific Individual Factory.

This class extends the generic genetiK::IndividualFactory to generate individuals to
be used with Genetic Algorithms.
@ingroup ga
@{
 */
class IndividualFactory : public genetiK::IndividualFactory
{
private:
	unsigned int							length;

public:
	/*! @brief Creates a factory that creates Individual objects having specified length
	@param length length of the individuals to generate
	@see Individual(unsigned int length)
	*/
	IndividualFactory(unsigned int length);

	/*! @brief returns length set for this Factory

	@return this.length
	*/
	unsigned int							getLength() { return length; }

	/*! @brief destructor
	*/
	virtual ~IndividualFactory();

	/*! @brief abstract generate function

	This function must be extended by sublcasses to generate appropriate individuals.
	@return a new Individual
	*/
	virtual genetiK::Individual*					generate()=0;
};

}	
}
/** @} */ // end of group

#endif


