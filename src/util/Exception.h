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

/*! 
@file src/util/Exception.h
@brief Exception class header file
 */

#ifndef GENETIK_UTIL_EXCEPTION
#define GENETIK_UTIL_EXCEPTION

#include <string>
#include <exception>

namespace genetiK {

namespace util {

/*! @brief Exception is the base class of all exceptions thrown by classes in the GenetiK library

@ingroup util
 */
class Exception : public std::exception
{
private:
	std::string message;
public:
	/*! Creates an Exception associating it the specified string as message.
	@param mess a message describing the cause of the exception
	*/
	explicit Exception(const std::string& mess);

	/*! Deletes the Exception instance
	*/
	virtual ~Exception() throw();
	
	/*! @brief Returns the cause of the exception
	
	The cause message is returned as a C-style character string, for compatibiliy with classes derived from std:exception classes.
	@return the cause, as character string
	*/
	virtual const char* what() const throw() { return message.c_str(); }
	
	/*! @brief Returns the cause of the exception as a std::string
	@return the cause, as an std::string
	*/
	virtual const std::string& getMessage() const throw() { return message; } 
};

}
}

#endif
