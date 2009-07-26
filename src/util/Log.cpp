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

#include "Log.h"

#include <iostream>
#include <fstream>

using namespace std;

namespace genetiK
{
namespace util
{
Log* Log::self = NULL;

Log::Log() :
threshold(WARN),
target(&cout)
{}

Log::~Log() {
	if (!target && target != &cout) {
		delete target;
	}
}

Log* Log::getInstance()
{
	if (!self)
		self=new Log();

	return self;
}

void Log::deleteInstance() {
	if (self)
		delete self;
	self = NULL;
}

int Log::setTarget (ostream* targetStream) {
	if (target && target != &cout) {
		delete target;
	}

	target = targetStream;
	return 0;
}

int Log::setTarget(const char* filename, bool append) {
	if (target && target != &cout) {
		delete target;
	}

	target = new ofstream(filename, (append ? ios_base::out|ios_base::app : ios_base::out));

	if (*target)
		return 0;
	else
		return 1;
}

int Log::output(ELogLevel level, const string& message) {
	if (level >= threshold) {
		(*target) << "[" << level << "]: " << message << endl;
		return 0;
	}

	return 1;
}

}
}
