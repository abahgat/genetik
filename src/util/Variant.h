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

//
// File: Variant.h
// Created by: Daniele Castagna <Email>
// Created on: Fri Jan  6 16:06:44 2006
//

#ifndef GENETIK_UTIL_VARIANT
#define GENETIK_UTIL_VARIANT

namespace genetiK
{
namespace util
{
	
class Variant
{
private:
	typedef enum VariantType{
		UNDEFINED = -1,
		INTEGER = 0,
		BOOLEAN,
		CHARACTER,
		REAL,
		USER_DATA,
		TYPES_NUMBER
		}VariantType;



	typedef union{
		bool boolean;
		int integer;
		char character;
		double real;
		void* userData;
	}Data;


		
	Data								data;	
	VariantType							type;
		
public:
	Variant();
	Variant(bool boolean);
	Variant(int integer);
	Variant(char character);
	Variant(double real);
	Variant(void* userData);
	virtual ~Variant();

	VariantType 						getType() const;

	bool 							getBoolean() const;	
	int 							getInteger() const;
	char							getCharacter() const;
	double							getReal() const;
	void* 							getUserData() const;



	void 							setBoolean(bool boolean);	
	void 							setInteger(int integer);
	void							setCharacter(char character);
	void							setReal(double real);
	void 							setUserData(void* userData);

};

}
}

#endif
