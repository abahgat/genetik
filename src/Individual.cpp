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

#include "Individual.h"
#include <sstream>
#include <string>

using std::string;
using std::stringstream;

namespace genetiK{
Individual::Individual(void) 
{
}

Individual::Individual(const Individual& /*individual*/)
{
}

Individual::~Individual(void)
{
}

string Individual::toString() const {
	stringstream ss;
	// print address
	ss << this;
	return ss.str();
}

std::ostream& operator<<(std::ostream& os, const Individual& ind)
{
	const string s = ind.toString();
	os << s;
	return os;
}

}
