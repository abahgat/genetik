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
@file src/util/IllegalStateException.h
@brief IllegalStateException class header file
 */

#ifndef GENETIK_UTIL_ILLEGALSTATEEXCEPTION
#define GENETIK_UTIL_ILLEGALSTATEEXCEPTION

#include <string>
#include "Exception.h"

namespace genetiK {

namespace util {

/*! @brief Signals that an objects is in an illegal state

This class is used thrown to signal that an object is in an unexpected state.
For example, it is thrown by classes that require specific prior initialization before calling certain methods.

@ingroup util
 */
class IllegalStateException : public Exception
{
public:
	/*! Creates an IllegalStateException associating it the specified string as message.
	@param mess a message describing the cause of the exception
	*/
	explicit IllegalStateException(const std::string& mess);

	/*! Deletes the IllegalStateException instance
	*/
	virtual ~IllegalStateException() throw();
};

}
}

#endif
