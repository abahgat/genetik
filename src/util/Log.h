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
@file src/util/Log.h
@brief Log class header file
 */

#ifndef GENETIK_UTIL_LOG
#define GENETIK_UTIL_LOG

#include <string>
#include <iosfwd>

using std::string;
using std::ostream;

namespace genetiK
{
namespace util
{
/*! @brief Default log priority levels

Log levels are defined such that <b>DEBUG &lt; INFO &lt; WARN &lt; ERROR &lt; FATAL</b>
@ingroup util
*/
typedef enum{
	/*! Debug-specific messages, providing information about detailed program execution
	*/
	DEBUG,
	/*! Informative messages about program execution
	*/
	INFO,
	/*! Warning messages (Default level)
	*/
	WARN,
	/*! Error messages
	*/
	ERROR,
	/*!
	Fatal, program blocking errors that force program exit
	*/
	FATAL,
	/*!
	This level is used to disable logging
	*/
	NONE
} ELogLevel;

/*! @brief Provided basic logging functionalities.

This class is a sort of lightweight standalone logger. It can be used to selectively log all messages having priority greater or equal than a specified level (see ELogLevel for more details) to a specific target (file or output stream).
Default behaviour is to log messages having priority &gt;= than genetiK::util::WARN to standard output.

The Log class also exposes a set of is{ELogLevel}Enabled() methods, to check if a particular log level is enabled. These methods are useful to avoid the overhead needed to generate the actual log messages when the appropriate log level is disabled.
@see ELogLevel
@ingroup util
*/
class Log
{
private:
	Log();

	Log(const Log&) {}

	Log& 					operator= (const Log&) { return *self; }

	virtual ~Log();

	static Log* 				self;

	ELogLevel				threshold;	

	ostream*				target;

public:
	/*! @brief Retrieve the Log instance
	As in classes that implement Singleton pattern, this method retrieves the (unique) instance of the Log class.
	If the instance doesn't already exist, it is created.

	@return a reference to the Log class
	*/
	static Log*				getInstance();

	/*! @brief Delete the Log instance
	*/
	static void				deleteInstance();

	/*! @brief Set the Log threshold
	Sets the ELogLevel used to filter incoming messages. Only messages having ELogLevel &gt;= level will be logged.
	@param level the threshold to use when logging messages
	@see ELogLevel
	*/
	void					setLevel (ELogLevel level) { threshold = level; }

	/*! @brief Get the current Log threshold
	Retrieves ELogLevel used to filter incoming messages. Only messages having level &gt;= are be logged.
	@return the threshold use to logging messages
	@see ELogLevel
	*/
	ELogLevel				getLevel() const { return threshold; }

	/*! @brief Set the output stream to use for log messages
	@return 0 if operation was succesful
	@see ELogLevel
	*/
	int					setTarget (ostream* targetStream);

	/*! @brief Set the output file to use for log messages
	Opens the specified file and writes log messages to it. The boolean argument permits to specify if output messages should be appended or not.
	@param filename the nome of the file 
	@param append true for append mode, false otherwise
	@return 0 if operation was succesful
	*/
	int					setTarget (const char* filename, bool append);

	/*! @brief Get the log's target stream
	@return output stream
	*/
	ostream*				getTarget() const { return target; }

	/*! @brief Demands logging of a message with the specified priority level
	
	Messages will be logged if <b>level</b> &gt;= threshold.
	@param level priority of the message
	@param message the message to be logged
	@return 1 if the message was logged, 0 otherwise
	@see ELogLevel
	*/
	int					output(ELogLevel level, const string& message);
	
	/*! @brief Log message with DEBUG level
	@param message message to log
	@return 1 if the message was logged, 0 otherwise
	@see ELogLevel and output
	*/
	int					debug(const string& message) { return output(DEBUG, message); }

	/*! @brief Log message with INFO level
	@param message message to log
	@return 1 if the message was logged, 0 otherwise
	@see ELogLevel and output
	*/
	int					info(const string& message) { return output(INFO, message); }

	/*! @brief Log message with WARN level
	@param message message to log
	@return 1 if the message was logged, 0 otherwise
	@see ELogLevel and output
	*/
	int					warn(const string& message) { return output(WARN, message); }

	/*! @brief Log message with ERROR level
	@param message message to log
	@return 1 if the message was logged, 0 otherwise
	@see ELogLevel and output
	*/
	int					error(const string& message) { return output(ERROR, message); }

	/*! @brief Log message with FATAL level
	@param message message to log
	@return 1 if the message was logged, 0 otherwise
	@see ELogLevel and output
	*/
	int					fatal(const string& message) { return output(FATAL, message); }

	/*! @brief Check if DEBUG messages are logged
	@return true if DEBUG messages are currently stored in Log
	@see ELogLevel and output
	*/
	bool					isDebugEnabled() const { return threshold <= DEBUG; }

	/*! @brief Check if INFO messages are logged
	@return true if INFO messages are currently stored in Log
	@see ELogLevel and output
	*/
	bool					isInfoEnabled() const { return threshold <= INFO; }

	/*! @brief Check if WARN messages are logged
	@return true if WARN messages are currently stored in Log
	@see ELogLevel and output
	*/
	bool					isWarnEnabled() const { return threshold <= WARN; }

	/*! @brief Check if ERROR messages are logged
	@return true if ERROR messages are currently stored in Log
	@see ELogLevel and output
	*/
	bool					isErrorEnabled() const { return threshold <= ERROR; }

	/*! @brief Check if FATAL messages are logged
	@return true if FATAL messages are currently stored in Log
	@see ELogLevel and output
	*/
	bool					isFatalEnabled() const { return threshold <= FATAL; }

	/*! @brief Check if messages having specified priority are logged
	@param level the ELogLevel priority
	@return true if messages having <b>level</b> priority are currently stored in Log
	@see ELogLevel and output
	*/
	bool					isEnabled(ELogLevel level) const { return threshold <= level; }

};

}
}

#endif
