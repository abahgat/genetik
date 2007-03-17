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

#include <sstream>

#include "../util/util.h"

using namespace std;
using genetiK::util::Random;
using genetiK::util::Log;

#include "Individual.h"

namespace genetiK
{
namespace ga
{

// TODO add a constructor that allocates memory but does not initialize with random data
Individual::Individual(unsigned int length) :
length(length)
{
	blockNum = length/(sizeof(unsigned int)<<3) + (length%((sizeof(unsigned int)<<3)) ? 1 : 0);

	bitArray = new unsigned int[blockNum];

	for (unsigned int i = 0; i < blockNum; ++i) {
		bitArray[i] = Random::getImplementation()->getNextInt();
	}
}

Individual::Individual(const Individual& individual) :
genetiK::Individual(individual),
length(individual.length),
blockNum(individual.blockNum)
{
	bitArray = new unsigned int[blockNum];

	for (unsigned int i = 0; i < blockNum; ++i) {
		bitArray[i] = individual.bitArray[i];
	}
}

Individual::~Individual(void)
{
        if (bitArray) {
		delete[] bitArray;
	}
}

int Individual::mutate(const double mutationProbability)
{
	for (unsigned int i = 0; i < blockNum; ++i) {
		unsigned int mutationMask = 0;
		for (unsigned int j = 0; j < sizeof(unsigned int)<<3; ++j) {
			if (Random::getImplementation()->getNextReal() < mutationProbability) {
				mutationMask |= 1;
			}
			mutationMask = mutationMask << 1;
		}
		bitArray[i] ^= mutationMask;
	}

        return 0;
}

int Individual::crossOver(genetiK::Individual* i, genetiK::Individual** child1, genetiK::Individual** child2)
{
	Log::getInstance()->debug("Entering GA crossover");

	Individual* gaPartner = static_cast<Individual*>(i);
	Individual* ind1 = static_cast<Individual*>(this->copy());
	Individual* ind2 = static_cast<Individual*>(gaPartner->copy());

	unsigned int crossOverPoint = 1+Random::getImplementation()->getNextInt(length-1);
	unsigned int middleBlock = crossOverPoint/(sizeof(unsigned int)<<3);

	for (unsigned int i = 0; i < blockNum; ++i) {
		if (i < middleBlock) {
			ind1->bitArray[i] = this->bitArray[i];
			ind2->bitArray[i] = gaPartner->bitArray[i];
		} else if (i > middleBlock) {
			ind1->bitArray[i] = gaPartner->bitArray[i];
			ind2->bitArray[i] = this->bitArray[i];
		} else {
			unsigned int inIndex = crossOverPoint%(sizeof(unsigned int)<<3);
			unsigned int mask = 0;

			if (inIndex + 1 < (sizeof(unsigned int)<<3)) {
				mask = (1 << (inIndex + 1)) - 1;
			} else {
				mask = ~0;
			}

			ind1->bitArray[i] = (this->bitArray[i] & ~mask) | (gaPartner->bitArray[i] & mask);
			ind2->bitArray[i] = (this->bitArray[i] & mask) | (gaPartner->bitArray[i] & ~mask);
		}
	}

	if (*child1 || *child2)
	{
		Log::getInstance()->warn("Warning, calling crossover with not null output parameters could result in memory leaks");
	}

	if (Log::getInstance()->isDebugEnabled()) {
		stringstream message;

		message << "crossover point " << crossOverPoint << '\n' <<
			"p1\t" << *this << '\n' <<
			"c1\t" << *ind1 << '\n' <<
			"p2\t" << *gaPartner << '\n' <<
			"c2\t" << *ind2;

		Log::getInstance()->debug(message.str());
	}

	*child1 = ind1;
	*child2 = ind2;

        return 0;
}

bool Individual::operator[] (unsigned int index) const {
	return bitArray[index/(sizeof(unsigned int)<<3)] & 1 << (index%(sizeof(unsigned int)<<3));
}

string Individual::toString() const {
	string rep;
	rep.resize(length+1);

	int index = 0;
	const int blockSize = sizeof(unsigned int)<<3;

	for (int i = 0; i < blockNum; ++i) {
		// segfault with bitArray[i] = 0x8000U;
		int last = i < blockNum - 1 || !(length%blockSize) ? 0 : blockSize - length%blockSize;
		int tempBlock = bitArray[i];
		for (int j = (sizeof(int)<<3) - 1; j >= last; --j) {
			rep[index++] = (((tempBlock >> j) & 1) ? '1' : '0');
		}
	}

	rep[length] = '\0';

	return rep;
}

}
}


