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


#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "Random.h"
#include "util.h"

#include <iostream>

using namespace std;

using genetiK::util::Log;

namespace genetiK
{
namespace util
{

Random* Random::implementation = NULL;

Random::Random()
{}

Random::~Random()
{}

void Random::deleteImplementation()
{
        if (implementation)
                delete implementation;
        implementation=NULL;
}
void Random::setImplementation(Random* random)
{
        deleteImplementation();
        implementation = random;
}

void Random::setDefaultImplementation()
{
        setImplementation( new RandomDefault(time(NULL)) );
}


RandomDefault::RandomDefault(unsigned int seed) : Random()
{
	stateVector[0] = seed;
	for (stateVectorIndex=1; stateVectorIndex < MERS_N; stateVectorIndex++) {
		stateVector[stateVectorIndex] = (1812433253UL * (stateVector[stateVectorIndex-1] ^ (stateVector[stateVectorIndex-1] >> 30)) + stateVectorIndex);
	}
}

RandomDefault::~RandomDefault()
{}

unsigned int RandomDefault::getNextInt()
{
	// generate 32 random bits
	unsigned int n;

	if (stateVectorIndex >= MERS_N) {
		// generate MERS_N words at one time
		const unsigned int LOWER_MASK = (1LU << MERS_R) - 1; // lower MERS_R bits
		const unsigned int UPPER_MASK = -1L  << MERS_R;      // upper (32 - MERS_R) bits
		static const unsigned int mag01[2] = {0, MERS_A};
    
		unsigned int kk;
		for (kk=0; kk < MERS_N-MERS_M; kk++) {
			n = (stateVector[kk] & UPPER_MASK) | (stateVector[kk+1] & LOWER_MASK);
			stateVector[kk] = stateVector[kk+MERS_M] ^ (n >> 1) ^ mag01[n & 1];
		}
		
		for (; kk < MERS_N-1; kk++) {
			n = (stateVector[kk] & UPPER_MASK) | (stateVector[kk+1] & LOWER_MASK);
			stateVector[kk] = stateVector[kk+(MERS_M-MERS_N)] ^ (n >> 1) ^ mag01[n & 1];
		}
		
		n = (stateVector[MERS_N-1] & UPPER_MASK) | (stateVector[0] & LOWER_MASK);
		stateVector[MERS_N-1] = stateVector[MERS_M-1] ^ (n >> 1) ^ mag01[n & 1];
		stateVectorIndex = 0;
	}

	n = stateVector[stateVectorIndex++];

	// Tempering (May be omitted):
	n ^=  n >> MERS_U;
	n ^= (n << MERS_S) & MERS_B;
	n ^= (n << MERS_T) & MERS_C;
	n ^=  n >> MERS_L;
  	return n;
}

unsigned int RandomDefault::getNextInt(unsigned int max)
{
	unsigned int n;
	n = int(max * getNextReal()); // multiply interval with random and truncate
	return n;
}

double RandomDefault::getNextReal()
{	
	unsigned int n;
        double f;
        
        n = getNextInt();
        f = (double)n * (1./((double)(unsigned int)(-1L)+1.));
        
        return f;
}



}
}

