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
@file src/StopCriterionMaxIteration.h
@brief MaxIteration StopCriterion header file
 */

#ifndef GENETIK_STOPCRITERIONMAXITERATION
#define GENETIK_STOPCRITERIONMAXITERATION

#include "StopCriterion.h"

namespace genetiK{

/*! @brief iteration count stop condition for an EvolutionaryAlgorithm
This class encapsulates an iteration count stop condition for an EvolutionaryAlgorithm. It stops when a fixed number of iterations has been performed.
@ingroup genetiK
 */
class StopCriterionMaxIteration : public StopCriterion
{
	private:
		unsigned int maxIteration;
		unsigned int iteration;
	
	public:
		/*! @brief creates a new StopCriterionMaxIteration that stops after <b>maxIteration</b> iterations
		@param maxIteration the number of iterations to perform
		*/
		StopCriterionMaxIteration(unsigned int maxIteration) : 
			maxIteration(maxIteration),
			iteration(0){}
	
		/*! @brief default destructor
		*/
		~StopCriterionMaxIteration( );

		/*! @brief actual stop criterion
		@return true if EvolutionaryAlgorithm <b>maxIteration</b> have been performed, false otherwise
		*/
		virtual bool							reached(){ return iteration++ >= maxIteration; }
};
}

#endif
