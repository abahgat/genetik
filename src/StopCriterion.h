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
@file src/StopCriterion.h
@brief Generic StopCriterion header file
 */

#ifndef GENETIK_STOPCRITERION
#define GENETIK_STOPCRITERION

namespace genetiK{

/*! @brief stop condition for an EvolutionaryAlgorithm
This class encapsulates a stop condition for an EvolutionaryAlgorithm. In particular, it may be extended to implement specific stop conditions.
@ingroup genetiK
 */
class StopCriterion
{
	public:
		/*! @brief default constructor
		*/
		StopCriterion(void);
	
		/*! @brief default destructor
		*/
		virtual ~StopCriterion(void);
	
		/*! @brief actual stop criterion
		@return true if EvolutionaryAlgorithm must stop, false otherwise
		*/
		virtual bool							reached()=0;
};

}

#endif
