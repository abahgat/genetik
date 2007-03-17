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

#include <iostream>
#include <stdlib.h>

using namespace std;

#include "Variant.h"
#include "Log.h"

namespace genetiK
{
namespace util
{

Variant::Variant():
type(UNDEFINED)
{
}

Variant::Variant(bool boolean)
{
	setBoolean( boolean );
}
Variant::Variant(int integer)
{
	setInteger( integer );
}
Variant::Variant(char character)
{
	setCharacter( character );
}
Variant::Variant(double real)
{
	setReal( real );
}
Variant::Variant(void* userData)
{
	setUserData( userData );
}

	
Variant::~Variant()
{
}
	
bool Variant::getBoolean() const
{
	if (type != BOOLEAN)
		Log::getInstance()->error("Error!! this Variant is not BOOLEAN");
	return data.boolean;
}

int Variant::getInteger() const
{
	if (type != INTEGER)
		Log::getInstance()->error("Error!! this Variant is not INTEGER");
	return data.integer;
}

char Variant::getCharacter() const
{
	if (type != CHARACTER)
		Log::getInstance()->error("Error! this Variant is not CHARACTER");
	return data.character;
}

double Variant::getReal() const
{
	if (type != REAL)
		Log::getInstance()->error("Error! this Variant is not REAL");
	return data.real;
}

void* Variant::getUserData() const
{
	if (type != USER_DATA)
		Log::getInstance()->error("Error! this Variant is not USER_DATA");
	return data.userData;
}

void Variant::setBoolean(bool boolean)
{
	type=BOOLEAN;
	data.boolean = boolean;
}
	
void Variant::setInteger(int integer)
{
	type=INTEGER;
	data.integer = integer;
}

void Variant::setCharacter(char character)
{
	type = CHARACTER;
	data.character = character;
}

void Variant::setReal(double real)
{
	type = REAL;
	data.real = real;
}

void Variant::setUserData(void* userData)
{
	type = USER_DATA;
	data.userData = userData;
}

}
}

