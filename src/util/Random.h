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
@file src/util/Random.h
@brief Random class header file
*/

#ifndef GENETIK_UTIL_RANDOM
#define GENETIK_UTIL_RANDOM

#include "Log.h"

namespace genetiK
{
namespace util
{

/*!
@brief This class represents both the interface and the container of the Random implementation used in the genetiK library .
 
This class represents both the interface and the container of the Random implementation used in the genetiK library.
You can redefine your own Random, extending this class and passing it to the setImplementation method.
@ingroup util
*/
class Random
{
protected:

	/*! @brief creates the default Random implementation.
	
	This constructor is protected because you don't need to create any instance of this class.
	You can set this class as the Random imlementation by calling Random::SetDefaultImplementation();
	*/
        Random();

        virtual ~Random();
private:
        static Random*			implementation;

public:
	/*! @brief sets an implementation of the Random.
	
	Call this function to set a new implementation of the random for the GenetiK Library.
	@param random The implementation of the random
	 */
        static void			setImplementation(Random* random);
	
 	/*! @brief sets the default implementation of the Random.
 	
	Call this function to set the default implementation of the random.
	This method will be automatically called by the EvolutionaryAlgorithm if no Random implementation is set.

	 */
	static void			setDefaultImplementation();
	
	/*! @brief returns the current implementation of the random.
	
	The framework call this method to retrieve the current implementation of the random.
	
	*/
	inline static Random*		getImplementation()
        {
		if (!implementation)
			Log::getInstance()->warn("Warning: You should call setImplementation before calling Random::getImplentation().");
                return implementation;
        }
	/*! @brief destroy the current implementation.
	
	Call this method to free the memory.
	 */
        static void			deleteImplementation();

	/*! @brief Returns the next pseudorandom integer.
	
	This method returns the next pseudorandom integer, you can override it in your random implementation.
	Returns an unsigned int greater than or equal to 0 and less than 4294967296;
	 */
        virtual unsigned int		getNextInt()=0;
	
	/*! @brief Returns the next pseudorandom integer.
	
	This method returns the next pseudorandom integer, you can override it in your random implementation.
	Returns an unsigned int greater than or equal to 0 and less than max;
	
	@param max The return value upperbound
	 */        
	virtual unsigned int		getNextInt(unsigned int max)=0;
	
	/*! @brief Returns the next pseudorandom integer.
	
	 This method returns the next pseudorandom double, you can override this method in your random implementation.
	Returns a double greater than or equal to 0.0 and less than 1.0;
	 */
        virtual double			getNextReal()=0;

};

/*
*  Random Number generator 'Mersenne Twister'                                *
*                                                                            *
*  This random number generator is described in the article by               *
*  M. Matsumoto & T. Nishimura, in:                                          *
*  ACM Transactions on Modeling and Computer Simulation,                     *
*  vol. 8, no. 1, 1998, pp. 3-30.                                            *
*  Details on the initialization scheme can be found at                      *
*  http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html                  *
*                                                                            *
*  Experts consider this an excellent random number generator.               */

/*!
@brief This class is the default random implementation with the 'Mersenne Twister' algorithm.
 

*  Random Number generator 'Mersenne Twister'                                *
*                                                                            *
*  This random number generator is described in the article by               *
*  M. Matsumoto & T. Nishimura, in:                                          *
*  ACM Transactions on Modeling and Computer Simulation,                     *
*  vol. 8, no. 1, 1998, pp. 3-30.                                            *
*  Details on the initialization scheme can be found at                      *
*  http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html                  *
*                                                                            *
*  Experts consider this an excellent random number generator.               *

@ingroup util
*/

class RandomDefault : public Random{
private:

#if 0
	// constants for MT11213A:
	// (32 bit constants cannot be defined as enum in 16-bit compilers)
	static const unsigned int MERS_N   351
	static const unsigned int MERS_M   175
	static const unsigned int MERS_R   19
	static const unsigned int MERS_U   11
	static const unsigned int MERS_S   7
	static const unsigned int MERS_T   15
	static const unsigned int MERS_L   17
	static const unsigned int MERS_A   0xE4BD75F5
	static const unsigned int MERS_B   0x655E5280
	static const unsigned int MERS_C   0xFFD58000
#else    
	// constants for MT19937:
	static const unsigned int MERS_N = 624;
	static const unsigned int MERS_M = 397;
	static const unsigned int MERS_R = 31;
	static const unsigned int MERS_U = 11;
	static const unsigned int MERS_S = 7;
	static const unsigned int MERS_T = 15;
	static const unsigned int MERS_L = 18;
	static const unsigned int MERS_A = 0x9908B0DF;
	static const unsigned int MERS_B = 0x9D2C5680;
	static const unsigned int MERS_C = 0xEFC60000;
#endif

	unsigned int 				stateVector[MERS_N];
	unsigned short int 			stateVectorIndex;

	unsigned long int 			seed;
public:
	/*!@brief RandomDefault constructor
	@param seed the random seed
	*/
        RandomDefault(unsigned int seed);
        virtual ~RandomDefault();
	/*! @brief Returns the next pseudorandom integer.
	
	This method returns the next pseudorandom integer.
	Returns an unsigned int greater than or equal to 0 and less than 4294967296;
	 */
        virtual unsigned int		getNextInt();
	
	/*! @brief Returns the next pseudorandom integer.
	
	This method returns the next pseudorandom integer.
	Returns an unsigned int greater than or equal to 0 and less than max;
	
	@param max The return value upperbound
	 */
	virtual unsigned int		getNextInt(unsigned int max);
	
	/*! @brief Returns the next pseudorandom real.
	
	 This method returns the next pseudorandom double.
	Returns a double greater than or equal to 0.0 and less than 1.0;
	 */
        virtual double			getNextReal();
};

}
}

#endif
